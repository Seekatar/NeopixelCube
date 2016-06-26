#ifndef __NEOPIXELCUBE_H__
#define __NEOPIXELCUBE_H__


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

/*
  Class for controlling a cube of NeoPixels

  This currently uses 3x3

  This uses Adafruit_NeoPixel library to drive the neopixels.

  Call methods on this class to set the values, then call Show() to 
  actually change the leds.
*/
class NeoPixelCube
{

  private:
    Adafruit_NeoPixel _strip;
    byte _sides;
    unsigned int _cube[3][3][3];
    void dumpCube(const char *);
    inline unsigned int at(byte x,byte y,byte z) { return _cube[x][y][z]; }
    void writeErrorToSerial(const char *msg);
    bool checkArrayIndex(const char *from, byte x, byte y, byte z );
    
  public:

    uint32_t Color( byte r, byte g, byte b )
    {
      return _strip.Color(r, g, b);
    }

    // flags are passed to Adafruit_NeoPixel
    NeoPixelCube(byte sides = 3, unsigned int pin = 6, unsigned int flags =  NEO_RGB + NEO_KHZ800 );

    void Begin();

    // set one led per address
    void Set(byte ledNo, uint32_t color );

    // set one led x,y,z
    void Set(byte column, byte row, byte layer, uint32_t color );

    // set all the leds in the cube
    void SetAll(uint32_t color );

    // set all the leds in one layer
    void SetLayer(byte layer, uint32_t color );

    // set all the leds in one face (vertical layer)
    void SetFrontFace(byte y, uint32_t color );

    // set all the leds in one face (vertical layer)
    void SetSideFace(byte x, uint32_t color );

    // set all the leds in one row in one layer
    void SetRow(byte layer, byte row, uint32_t color );

    // set all the leds in one column in one layer
    void SetColumn(byte layer, byte column, uint32_t color );

    // set all the leds in one vertical stack (one pixel per layer)
    void SetStack(byte row, byte column, uint32_t color );

    // show all the changes made since last Show()
    void Show();
};

class AutoShow
{
  private:
    NeoPixelCube &_cube;

  public:
    AutoShow( NeoPixelCube &cube ) : _cube(cube) {}
    ~AutoShow() {
      _cube.Show();
    }
};
#endif
