#ifndef __NEOPIXELCUBE_H__
#define __NEOPIXELCUBE_H__


//#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define uint32_t unsigned int

class NeoPixelCube
{
   
private:
    //Adafruit_NeoPixel _strip;
    unsigned int _sides;
    unsigned int *** _cube;
    
public: 
    enum FACE {
        Front,
        Middle,
        Back,
        Left,
        Middle90,
        Right,
    };
    
    NeoPixelCube(unsigned int sides = 3, unsigned int pin = 6 );
  
    void SetLayer(unsigned int layer, uint32_t color );
    
    void SetFace(enum FACE face, uint32_t color );
    
    void SetRow(unsigned int layer, unsigned int row, uint32_t color );
      
    void SetColumn(unsigned int layer, unsigned int column, uint32_t color );
    
};

#endif 