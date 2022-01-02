/*
 * Based on Adafruit's Charlieplex Driver Adafruit_IS31FL3731,
 * but extensively stripped down for the Blinky.
 */

#include <Adafruit_IS31FL3731.h>

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) \
  {                         \
    int16_t t = a;          \
    a = b;                  \
    b = t;                  \
  }
#endif

/**************************************************************************/
/*!
    @brief Constructor for breakout version
    @param width Desired width of led display
    @param height Desired height of led display
*/
/**************************************************************************/

Adafruit_IS31FL3731::Adafruit_IS31FL3731(uint8_t width, uint8_t height) {}

void Adafruit_IS31FL3731::shutdown(bool f)
{
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, f ? 0x00 : 0x01);
}

/**************************************************************************/
/*!
    @brief Initialize hardware and clear display
    @param addr The I2C address we expect to find the chip at
    @param theWire The TwoWire I2C bus device to use, defaults to &Wire
    @returns True on success, false if chip isnt found
*/
/**************************************************************************/
bool Adafruit_IS31FL3731::begin(uint8_t addr, TwoWire *theWire)
{
  if (_i2c_dev)
  {
    delete _i2c_dev;
  }
  _i2c_dev = new Adafruit_I2CDevice(addr, theWire);

  if (!_i2c_dev->begin())
  {
    return false;
  }

  _i2c_dev->setSpeed(400000);
  _frame = 0;

  // shutdown
  shutdown(1);

  // picture mode
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG,
                 ISSI_REG_CONFIG_PICTUREMODE);

  displayFrame(_frame);

  // all LEDs on & 0 PWM
  clear(); // set each led to 0 PWM

  for (uint8_t f = 0; f < 8; f++)
  {
    for (uint8_t i = 0; i <= 0x11; i++)
      writeRegister8(f, i, 0xff); // each 8 LEDs on
  }

  audioSync(false);

  delay(10);

  // out of shutdown
  shutdown(0);

  return true;
}

/**************************************************************************/
/*!
    @brief Sets all LEDs on & 0 PWM for current frame.
*/
/**************************************************************************/
void Adafruit_IS31FL3731::clear(void)
{
  selectBank(_frame);
  uint8_t erasebuf[25];

  memset(erasebuf, 0, 25);

  for (uint8_t i = 0; i < 6; i++)
  {
    erasebuf[0] = 0x24 + i * 24;
    _i2c_dev->write(erasebuf, 25);
  }
}

/**************************************************************************/
/*!
    @brief Low level accesssor - sets a 8-bit PWM pixel value to a bank location
    does not handle rotation, x/y or any rearrangements!
    @param lednum The offset into the bank that corresponds to the LED
    @param bank The bank/frame we will set the data in
    @param pwm brightnes, from 0 (off) to 255 (max on)
*/
/**************************************************************************/
void Adafruit_IS31FL3731::setLEDPWM(uint8_t lednum, uint8_t pwm, uint8_t bank)
{
  if (lednum >= 144)
    return;
  writeRegister8(bank, 0x24 + lednum, pwm);
}

void Adafruit_IS31FL3731::drawEntireFrame(uint8_t *pframeBuffer)
{
  writeRegister144(_frame, 0x24, pframeBuffer);
}

/**************************************************************************/
/*!
    @brief Set's this object's frame tracker (does not talk to the chip)
    @param frame Ranges from 0 - 7 for the 8 frames
*/
/**************************************************************************/
void Adafruit_IS31FL3731::setFrame(uint8_t frame) { _frame = frame; }

/**************************************************************************/
/*!
    @brief Have the chip set the display to the contents of a frame
    @param frame Ranges from 0 - 7 for the 8 frames
*/
/**************************************************************************/
void Adafruit_IS31FL3731::displayFrame(uint8_t frame)
{
  if (frame > 7)
    frame = 0;
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_PICTUREFRAME, frame);
}

/**************************************************************************/
/*!
    @brief Go into autoplay mode, endlessly, showing all frames
    @param msDelay Sets delay in milliseconds, must be 11 - 704
*/
/**************************************************************************/
void Adafruit_IS31FL3731::autoPlay(uint16_t msDelay, uint8_t numFrames)
{

  // See datasheet for this math...
  // if you set the delay time A to 0, you get 704 ms delay
  // if you set the delay time A to 1-63, you get A × 11ms

  if (msDelay < 11)
    msDelay = 11;
  if (msDelay > 693)
    msDelay = 0;

  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUTOPLAY_WAY_OF_DISPLAY, numFrames & 7); // datasheet page 12 table 10
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUTOPLAY_DELAY_TIME, msDelay / 11);
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_AUTOPLAYMODE);
}

/**************************************************************************/
/*!
    @brief End autoplay
*/
/**************************************************************************/
void Adafruit_IS31FL3731::autoPlayStop()
{
  writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_CONFIG, ISSI_REG_CONFIG_PICTUREMODE);
  setFrame(0);
  displayFrame(0);
}

/**************************************************************************/
/*!
    @brief Switch to a given bank in the chip memory for future reads
    @param bank The IS31 bank to switch to
    @returns False if I2C command failed to be ack'd
*/
/**************************************************************************/
bool Adafruit_IS31FL3731::selectBank(uint8_t bank)
{
  uint8_t cmd[2] = {ISSI_COMMANDREGISTER, bank};
  return _i2c_dev->write(cmd, 2);
}

/**************************************************************************/
/*!
    @brief Enable the audio 'sync' for brightness pulsing (not really tested)
    @param sync True to enable, False to disable
*/
/**************************************************************************/
void Adafruit_IS31FL3731::audioSync(bool sync)
{
  if (sync)
  {
    writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x1);
  }
  else
  {
    writeRegister8(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0x0);
  }
}

/**************************************************************************/
/*!
    @brief Write one byte to a register located in a given bank
    @param bank The IS31 bank to write the register location
    @param reg the offset into the bank to write
    @param data The byte value
    @returns False if I2C command failed to be ack'd
*/
/**************************************************************************/
bool Adafruit_IS31FL3731::writeRegister8(uint8_t bank, uint8_t reg,
                                         uint8_t data)
{
  selectBank(bank);

  uint8_t cmd[2] = {reg, data};
  return _i2c_dev->write(cmd, 2);
}

// Writes 144 bytes of data to a register
// TRICKY THING: you must supply a 145 byte long array, with the data going from
// prg145[1] through prg145[144].
bool Adafruit_IS31FL3731::writeRegister144(uint8_t bank, uint8_t reg, uint8_t *prg145)
{
  selectBank(bank);

  prg145[0] = reg;
  return _i2c_dev->write(prg145, 145);
}
