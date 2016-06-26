#include "NeoPixelCube.h"

// sample sketch for NeoPixel cube

unsigned int sides = 3;
#define PIN 6

// construct it with the default wiring pattern
NeoPixelCube cube = NeoPixelCube(sides,PIN, NEO_RGB + NEO_KHZ800);

int wait = 100;
int layer = 0;
unsigned int x = 0, y = 0, z = 0;

void setup() {

  Serial.begin(57600);
  
  cube.Begin();

}

void loop() {
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

