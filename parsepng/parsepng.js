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
// Use a full range of greyscale, from 0x00000 to 0xFFFFFF.
//
// It converts to greyscale (ignoring Alpha) and generates a C++ array
// with the raw pixel data. This is simply compiled into the blinky
// code base using a "const" declaration, which, on ARM M0 chips, causes
// it to be stored in the flash/program area.
//

var path = require("path");
var getPixels = require("get-pixels");

var args = process.argv.slice(2);
if (args.length != 1) {
  console.error(`Usage: node parsepng <inputfile>`);
  return;
}

getPixels(args[0], function (err, pixels) {
  if (err) {
    console.error("Image file not found / not valid");
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

  const getOneByte = (x, y) => {
    const red = pixels.get(x, y, 0);
    const green = pixels.get(x, y, 0);
    const blue = pixels.get(x, y, 0);

    // luminosity formula, in case the incoming image isn't greyscale already
    const grey = Math.round(0.2126 * red + 0.7152 * green + 0.0722 * blue);
    if (grey > 255) grey = 255;

    return grey >> 4;
  };

  const formatTwoNibbles = (nib1, nib2) => {
    if (!nib1 && !nib2) return "____, ";
    else return `0x${nib1.toString(16)}${nib2.toString(16)}, `;
  };

  const variable_name = path.basename(args[0], ".png");

  console.log(`const uint8_t cframes_${variable_name} = ${number_of_frames};`);
  console.log(`const uint8_t bmp_${variable_name}[] = \{`);

  for (let frame = 0; frame < number_of_frames; frame++) {
    for (let x = 0; x <= 8; x++) {
      let row = "";
      for (let y = 0; y <= 15; y += 2) {
        // TODO get TWO bytes, pack them in one.
        row += formatTwoNibbles(
          getOneByte(frame * 9 + x, y),
          getOneByte(frame * 9 + x, y + 1)
        );
      }
      console.log(`\t${row}`);
    }
    console.log("");
  }

  console.log("};");
});
