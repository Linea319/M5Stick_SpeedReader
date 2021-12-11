#include "Circle.h"

void Circle::Draw(TFT_eSprite* canvas)
{
    DispVec2 dispPos = GetDisplayPos();
    int dispRadius = (int)radius;
    canvas->fillCircle(dispPos.x,dispPos.y,dispRadius * UNIT_PER_DOT,color);
}