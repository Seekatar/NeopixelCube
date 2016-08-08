#include "NeoPixelCube.h"

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, NeoPixelCube &cube) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return cube.Color((255 - WheelPos * 3) * .5, 0, (WheelPos * 3) * .5);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return cube.Color(0, (WheelPos * 3) * .5, (255 - WheelPos * 3) * .5);
  }
  WheelPos -= 170;
  return cube.Color((WheelPos * 3) * .5, (255 - WheelPos * 3) * .5, 0);
}

// sample sketch for NeoPixel cube

unsigned int sides = 3;
#define PIN 6

// construct it with the default wiring pattern
NeoPixelCube cube = NeoPixelCube(sides,PIN, NEO_RGB + NEO_KHZ800);

int wait = 100;
int layer = 0;
unsigned int x = 0, y = 0, z = 0;
byte c = 100;
unsigned int start;

void setup() {

  Serial.begin(57600);
  
  cube.Begin();
  start = millis();
//  cube.SetAll(cube.Color(20,0,0));
//  cube.Set( 1,1,1, cube.Color(0,0,255));
//  cube.Show();

}
int loopDelay = 1000;

void loop() {

  unsigned int _now = millis();
  if ( _now - start > loopDelay )
  {
    start = _now;
    uint32_t color = Wheel(c++, cube);
    Serial.print( "Color ");
    Serial.println(color, HEX);
    cube.SetAll(color); // cube.Color(20,0,0));  
    cube.Set( 1,1,1, cube.Color(0,0,255));
    cube.Show();
    delay(loopDelay);
  }
}

void loopTests() {
  runTests();
  stackRotate();
  rowRotate();
  columnRotate();
}

// rotating lines, stack, column, row coordinate
int rotatingLine [8][2] = {
      {0,0},{1,0},{2,0}, // right
      {2,1},{2,2},       // up
      {1,2},{0,2},       // left
      {0,1}              // down
    };

// rotate a stack of leds around vertical center
void stackRotate()
{
  for ( int i = 0; i < 5; i++ )
  {
      for ( int j = 0; j < 8; j++ )
      {
        cube.SetAll(0);
        cube.SetStack(rotatingLine[j][0], rotatingLine[j][1], cube.Color(110,10,10));
        cube.Show();
        delay(wait);
      }
  }
  
}

// rotate a row of leds around horizontal center
void rowRotate()
{
  for ( int i = 0; i < 5; i++ )
  {
      for ( int j = 0; j < 8; j++ )
      {
        cube.SetAll(0);
        cube.SetRow(rotatingLine[j][0], rotatingLine[j][1], cube.Color(110,0,150));
        cube.Show();
        delay(wait);
      }
  }
  
}

// rotate a column of leds around horizontal center
void columnRotate()
{
  for ( int i = 0; i < 5; i++ )
  {
      for ( int j = 0; j < 8; j++ )
      {
        cube.SetAll(0);
        cube.SetColumn(rotatingLine[j][0], rotatingLine[j][1], cube.Color(10,110,110));
        cube.Show();
        delay(wait);
      }
  }
  
}

void runTests() 
{
  // negative test out of range
  cube.Set( 99,99,99, 0);
  
  // individual test
  cube.SetAll(0);
  
  for ( int z = 0; z < sides*sides*sides; z++ )
  {
    cube.Set(z, cube.Color(127,50,50));
    cube.Show();
    delay(wait);
  }
  for ( int z = sides*sides*sides-1; z >= 0; z-- )
  {
    cube.Set(z, cube.Color(0,0,0));
    cube.Show();
    delay(wait);
  }
  
  cube.SetAll(0);
  
  for ( int z = 0; z < sides; z++ )
  {
    for ( int y = 0; y < sides; y++ )
    {
      for ( int x = 0; x < sides; x++ )
      {
        cube.Set(x,y,z, cube.Color(127,0,0));
        cube.Show();
        delay(wait);
      }
    }
  }
  for ( int z = sides-1; z >= 0; z-- )
  {
    for ( int y = sides-1; y >= 0; y-- )
    {
      for ( int x = sides-1; x >=0 ; x-- )
      {
        cube.Set(x,y,z, cube.Color(0,0,0));
        cube.Show();
        delay(wait);
      }
    }
  }
  
  // layer test
  for ( int i = 0; i < 10; i++ )
  {
    cube.SetAll(0);
    cube.SetLayer(layer, cube.Color(0,0,127));
    layer = layer < sides-1 ? ++layer : 0;
    cube.Show();
    delay(wait);
  }

  // front face test
  layer = 0;
  for ( int i = 0; i < 10; i++ )
  {
    cube.SetAll(0);
    cube.SetFrontFace(layer, cube.Color(0,127,0));
    layer = layer < sides-1 ? ++layer : 0;
    cube.Show();
    delay(wait);
  }


  // side face test
  layer = 0;
  for ( int i = 0; i < 10; i++ )
  {
    cube.SetAll(0);
    cube.SetSideFace(layer, cube.Color(110,110,0));
    layer = layer < sides-1 ? ++layer : 0;
    cube.Show();
    delay(wait);
  }

  // row test
  for ( int i = 0; i < sides; i++ )
  {
    for ( int row = 0; row < sides; row++ )
    {
      cube.SetAll(0);
      cube.SetRow(i, row, cube.Color(0,110,110));
      cube.Show();
      delay(wait);
    }
  }
  
  // column test
  for ( int i = 0; i < sides; i++ )
  {
    for ( int row = 0; row < sides; row++ )
    {
      cube.SetAll(0);
      cube.SetColumn(i, row, cube.Color(110,0,110));
      cube.Show();
      delay(wait);
    }
  }
  
  // stack test (vertical column of leds)
  for ( int i = 0; i < sides; i++ )
  {
    for ( int row = 0; row < sides; row++ )
    {
      cube.SetAll(0);
      cube.SetStack(i, row, cube.Color(110,110,110));
      cube.Show();
      delay(wait);
    }
  }

}    

