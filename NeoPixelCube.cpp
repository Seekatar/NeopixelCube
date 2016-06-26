#include "NeoPixelCube.h"

NeoPixelCube::NeoPixelCube(unsigned int sides, unsigned int pin, unsigned int flags )
{
    // Parameter 1 = number of pixels in strip
    // Parameter 2 = Arduino pin number (most are valid)
    // Parameter 3 = pixel type flags, add together as needed:
    //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
    //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
    //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
    //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)    
    _strip =  Adafruit_NeoPixel(sides*sides*sides, pin, flags);
    _sides = sides;
//    _cube = new unsigned int **[_sides];
//    for ( int x = 0; x < sides; x++ )
//    {
//        unsigned int **layer = new unsigned int *[_sides];
//        for ( int y = 0; y < sides; y++ )
//        {
//            layer[y] = new unsigned int[_sides];
//        }
//                    
//        _cube[x] = layer;
//
//    }
    
    // set the cube up with the default wiring
    /*
    Layer 0 (bottom) wire enters at 0
     2  1  0
     3  4  5
     8  7  6
    
    Layer 1
    15 16 17
    14 13 12
     9 10 11
     
    Layer 2
    20 19 18
    21 22 23
    26 25 24
    */
    static unsigned int cube[3][3][3] = 
            {{{8,7,6},
              {3,4,5},
              {2,1,0}},
              
              {{9,10,11},
               {14,13,12},
               {15,16,17}},
               
              {{26,25,24},
               {21,22,23},
               {20,19,18}} 
               };
               
    Serial.begin(57600);
               
    for ( int x = 0; x < _sides; x++ )
    {
      for ( int y = 0; y < _sides; y++ )
      {
        for ( int z = 0; z < _sides; z++ )
        {
          _cube[x][y][z] = cube[x][y][z];
        }
      }
    }
    dumpCube("constructor");

}           

void NeoPixelCube::dumpCube(const char *msg)
{
    Serial.print(msg);Serial.print(" dump ");
    for ( int x = 0; x < _sides; x++ )
    {
      for ( int y = 0; y < _sides; y++ )
      {
        for ( int z = 0; z < _sides; z++ )
        {
          Serial.print("_cube ");
          Serial.print(x);Serial.print(", ");
          Serial.print(y);Serial.print(", ");
          Serial.print(z);Serial.print(" = ");
          Serial.println(_cube[x][y][z]);
        }
      }
    }
    Serial.flush();
}

void NeoPixelCube::Begin()
{
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  _strip.begin();
  _strip.show(); // Initialize all pixels to 'off'  
  dumpCube("begin");
}

void NeoPixelCube::Set(unsigned int column, unsigned int row, unsigned int layer, uint32_t color )
{
    _strip.setPixelColor( at(column,row,layer), color );
}

void NeoPixelCube::Set(unsigned int ledNo, uint32_t color )
{
  _strip.setPixelColor( ledNo, color );
}

// set all the leds in the cube
void NeoPixelCube::SetAll(uint32_t color )
{
    for ( unsigned int x = 0; x < _sides; x++ )
    {
        for ( unsigned int y = 0; y < _sides; y++ )
        {
            for ( unsigned int z = 0; z < _sides; z++ )
            {
                _strip.setPixelColor( at(x,y,z), color );
            }
        }
    }
    // dumpCube("setAll");
}


void NeoPixelCube::SetLayer(unsigned int layer, uint32_t color )
{
    for ( unsigned int x = 0; x < _sides; x++ )
    {
        for ( unsigned int y = 0; y < _sides; y++ )
        {
            _strip.setPixelColor( at(x,y,layer), color );            
        }
    }
}

void NeoPixelCube::SetFrontFace(unsigned int y, uint32_t color )
{
    for ( unsigned int x = 0; x < _sides; x++ )
        SetStack(x,y,color);
}

void NeoPixelCube::SetSideFace(unsigned int x, uint32_t color )
{
    for ( unsigned int y = 0; y < _sides; y++ )
        SetStack(x,y,color);
}

void NeoPixelCube::SetRow(unsigned int layer, unsigned int row, uint32_t color )
{
    for ( unsigned int x = 0; x < _sides; x++ )
    {
        _strip.setPixelColor( at(x,row,layer), color );            
    }
    
}
    
void NeoPixelCube::SetColumn(unsigned int layer, unsigned int column, uint32_t color )
{
    for ( unsigned int y = 0; y < _sides; y++ )
    {
        _strip.setPixelColor( at(column,y,layer), color );            
    }
    
}

void NeoPixelCube::SetStack(unsigned int row, unsigned int column, uint32_t color )
{
    for ( unsigned int z = 0; z < _sides; z++ )
    {
        _strip.setPixelColor( at(row,column,z), color );            
    }
    
}

// show all the made since last show
void NeoPixelCube::Show()
{
    _strip.show();    
}
