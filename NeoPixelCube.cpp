#include "NeoPixelCube.h"

NeoPixelCube::NeoPixelCube(unsigned int sides, unsigned int pin )
{
    //_strip =  Adafruit_NeoPixel(sides*sides*sides, pin, NEO_GRB + NEO_KHZ800);
    _sides = sides;
    _cube = new unsigned int **[_sides];
    for ( int x = 0; x < sides; x++ )
    {
        unsigned int **layer = new unsigned int *[_sides];
        for ( int y = 0; y < sides; y++ )
        {
            layer[y] = new unsigned int[_sides];
        }
                    
        _cube[x] = layer;

    }
}           


void NeoPixelCube::SetLayer(unsigned int layer, uint32_t color )
{
    
}

void NeoPixelCube::SetFace(enum FACE face, uint32_t color )
{
    
}

void NeoPixelCube::SetRow(unsigned int layer, unsigned int row, uint32_t color )
{
    
}
    
void NeoPixelCube::SetColumn(unsigned int layer, unsigned int column, uint32_t color )
{
    
}
