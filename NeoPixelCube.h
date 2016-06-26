#ifndef __NEOPIXELCUBE_H__
#define __NEOPIXELCUBE_H__


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

class NeoPixelCube
{

  private:
    Adafruit_NeoPixel _strip;
    unsigned int _sides;
    unsigned int _cube[3][3][3];
    void dumpCube(const char *);
    inline unsigned int at(unsigned int x,unsigned int y,unsigned int z) { return _cube[z][y][x]; }
    
  public:

    uint32_t Color( byte r, byte g, byte b )
    {
      return _strip.Color(r, g, b);
    }

    NeoPixelCube(unsigned int sides = 3, unsigned int pin = 6, unsigned int flags =  NEO_RGB + NEO_KHZ800 );

    void Begin();

    // set the array of cube layout if yours doesn't use the default
    void SetLayout( int ***cube);

    // set one led per address
    void Set(unsigned int ledNo, uint32_t color );

    // set one led x,y,z
    void Set(unsigned int column, unsigned int row, unsigned int layer, uint32_t color );

    // set all the leds in the cube
    void SetAll(uint32_t color );

    // set all the leds in one layer
    void SetLayer(unsigned int layer, uint32_t color );

    // set all the leds in one face (vertical layer)
    void SetFrontFace(unsigned int y, uint32_t color );

    // set all the leds in one face (vertical layer)
    void SetSideFace(unsigned int x, uint32_t color );

    // set all the leds in one row in one layer
    void SetRow(unsigned int layer, unsigned int row, uint32_t color );

    // set all the leds in one column in one layer
    void SetColumn(unsigned int layer, unsigned int column, uint32_t color );

    // set all the leds in one vertical stack (one pixel per layer)
    void SetStack(unsigned int row, unsigned int column, uint32_t color );

    // show all the made since last show
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
