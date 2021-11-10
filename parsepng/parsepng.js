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

var getPixels = require("get-pixels");

var args = process.argv.slice(2);
if (args.length < 2) {
  console.error(`Usage: node parsepng <inputfile> <variablename>`);
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

  const getAndFormatByte = (x, y) => {
    const red = pixels.get(x, y, 0);
    const green = pixels.get(x, y, 0);
    const blue = pixels.get(x, y, 0);

    // luminosity formula, in case the incoming image isn't greyscale already
    const grey = Math.round(0.2126 * red + 0.7152 * green + 0.0722 * blue);
    if (grey > 255) grey = 255;

    if (grey === 0) return "____, ";
    // remember to #define ____ to 0.
    // this just makes it easier to see the shape

    return "0x" + ("0" + grey.toString(16)).slice(-2) + ", ";
  };

  console.log(`const uint8_t ${args[1]}[] = \{`);

  for (let frame = 0; frame < number_of_frames; frame++) {
    for (let y = 0; y <= 15; y++) {
      let row = "";
      for (let x = 0; x <= 8; x++) {
        row += getAndFormatByte(frame * 9 + x, y);
      }
      console.log(`\t${row}`);
    }
    console.log("");
  }

  console.log("};");
});
