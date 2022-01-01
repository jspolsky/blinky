//
// Blinky uses a charlieplexer that can display 9x16 bitmaps, where each
// pixel can be a shade of gray from 0 to 255. It can animate 8 frames of
// those bitmaps.
//
// This program reads a PNG file containing a strip of bitmaps
// in comic-strip-format. The strip is always 16 pixels high,
// and it is [9 x number_of_frames] pixels wide, for
// example, 72 pixels wide for the longest 8 pixel animation.
//
// The charlieplexer with LEDs really only shows about 16 shades of
// grey that are distinguishible to the human eye, so we only
// need 4 bits per pixel.
//
// For the input file, use a full range of greyscale, from 0x0 to 0xFFFFFF
// (or even color, which will be converted to greyscale).
//
// The output file format will be:
//
// byte 0 -- the number of frames, 1-8
// byte 1 -- high order byte - delay in milliseconds between frames
// byte 2 -- low order byte  - delay in milliseconds between frames
// followed by the raw pixel data, where each byte contains two pixels
//

const path = require("path");
const getPixels = require("get-pixels");
const SerialPort = require("serialport");
const fs = require("fs");
const Buffer = require("buffer").Buffer;

const args = process.argv.slice(2);

if (args.length === 0 || args[0] === "-h" || args[0] === "--help") {
  console.error(
    `Usage: node parsepng [-s speed] [-w] inputfile <outputfile>
       -s sets delay between frames in ms, must be between 11 and 704, default 55
       -w will keep running, watching the file for changes
       if outputfile is omitted, sends pixels to a Blinky Previewer via USB
       
       outputfile is a base name. Will generate .h and .bin versions.`
  );
  return;
}

// Parse the command line

let inputFileName = "";
let outputFileName = ""; // base name
let outputFileNameBinary = "";
let outputFileNameCCode = "";
let delay = 55;
let watch = false;

let ixArg = 0;
while (ixArg < args.length) {
  if (args[ixArg] === "-w") {
    watch = true;
  } else if (args[ixArg] === "-s") {
    delay = parseInt(args[++ixArg]);
    if (isNaN(delay) || delay < 11 || delay > 704) {
      console.error("invalid delay - must be 11 to 704 (in milliseconds)");
      return;
    }
  } else if (args[ixArg].startsWith("-")) {
    console.error(`invalid flag ${args[ixArg]}`);
    return;
  } else if (inputFileName === "") {
    inputFileName = args[ixArg];
  } else if (outputFileName === "") {
    outputFileName = args[ixArg];
    outputFileNameBinary = outputFileName + ".bin";
    outputFileNameCCode = outputFileName + ".h";
    variable_name = outputFileName;
  } else {
    console.error("too many arguments");
    return;
  }

  ixArg++;
}

getPixels(inputFileName, function (err, pixels) {
  if (err) {
    console.error(`input file ${inputFileName} not found or not a PNG file`);
    return;
  }

  if (pixels.shape[0] < 9 || pixels.shape[0] > 72 || pixels.shape[0] % 9 != 0) {
    console.error(
      "Image must be a multiple of 9 pixels wide, no more than 72 pixels"
    );
    return;
  }

  const number_of_frames = pixels.shape[0] / 9;

  if (pixels.shape[1] !== 16) {
    console.error("Image must be 16 pixels high");
    return;
  }

  const gamma_scale = [0, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 19, 24, 30, 37, 47];

  let luminositySum = 0;
  let luminosityCount = 0;

  const getOneByte = (x, y) => {
    const red = pixels.get(x, y, 0);
    const green = pixels.get(x, y, 0);
    const blue = pixels.get(x, y, 0);

    // luminosity formula, in case the incoming image isn't greyscale already
    const grey = Math.round(0.2126 * red + 0.7152 * green + 0.0722 * blue);
    if (grey > 255) grey = 255;

    const shade = grey >> 4;
    luminositySum += gamma_scale[shade];
    luminosityCount++;

    return shade;
  };

  const formatTwoNibbles = (nib1, nib2) => {
    if (!nib1 && !nib2) return "____, ";
    else return `0x${nib1.toString(16)}${nib2.toString(16)}, `;
  };

  var imageAsCCode = `const uint8_t bmp_${variable_name}[] = \{
        /* frames, delay (hi byte), delay (lo byte): */
        ${number_of_frames}, ${delay >> 8}, ${delay & 0xff},
        
        /* raw data: */\n`;

  var imageAsByteArray = [
    // first byte: number of frames
    number_of_frames,

    // second byte: hi order, delay in ms
    parseInt(delay / 256),

    // third byte: lo order, delay in ms
    delay % 256,
  ];

  console.log(imageAsByteArray);

  for (let frame = 0; frame < number_of_frames; frame++) {
    for (let x = 0; x <= 8; x++) {
      let row = "";
      for (let y = 0; y <= 15; y += 2) {
        row += formatTwoNibbles(
          getOneByte(frame * 9 + x, 16 - y),
          getOneByte(frame * 9 + x, 16 - (y + 1))
        );

        // the "16 - " logic below is because our
        // LED board is physically upside down :)
        imageAsByteArray.push(
          getOneByte(frame * 9 + x, 16 - y) * 16 +
            getOneByte(frame * 9 + x, 16 - (y + 1))
        );
      }
      imageAsCCode += `\t${row}\n`;
    }
    imageAsCCode += "\n";
  }

  imageAsCCode += "};\n";

  if (outputFileName !== "") {
    //
    // Write animation as binary to file
    //

    fs.writeFile(outputFileNameBinary, Buffer.from(imageAsByteArray), (err) => {
      if (err) {
        console.error(`Error writing output file ${outputFileNameBinary}`);
        console.error(err);
        return;
      }
    });

    fs.writeFile(outputFileNameCCode, imageAsCCode, (err) => {
      if (err) {
        console.error(`Error writing output file ${outputFileNameCCode}`);
        console.error(err);
        return;
      }
    });
  } else {
    //
    // Send output to USB port for preview
    //

    // find the path. If there is not exactly one Adafruit USB port,
    // give up

    var cPorts = 0;
    var sPath = "";

    SerialPort.list().then(
      (ports) => {
        ports.forEach((port) => {
          if (port.manufacturer && port.manufacturer.startsWith("Adafruit")) {
            sPath = port.path;
            cPorts++;
          }
        });
        if (cPorts > 1) {
          console.error(
            "More than one USB device found ... not sure who to talk to"
          );
          return;
        }

        if (cPorts < 1) {
          console.error("Can't find Blinky Previewer connected to USB");
          return;
        }

        // If we made it this far, send the data to the previewer
        const port = new SerialPort(sPath, function (err) {
          if (err) {
            console.error("Open port error ", err.message);
            return;
          }
        });

        port.write("!"); // starts transmission
        port.write(imageAsByteArray);
      },
      (err) => console.error(err)
    );
  }

  console.log(
    `Average luminosity: ${
      luminositySum / luminosityCount
    }\nEst mA consumption: ${
      2.5 + 0.60851064 * (luminositySum / luminosityCount)
    } `
  );
});
