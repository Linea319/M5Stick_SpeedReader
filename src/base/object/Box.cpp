#include "Box.h"

void Box::Draw(TFT_eSprite *canvas)
{
    DispVec2 drawPos = GetDisplayPos();
    canvas->fillRect(drawPos.x, drawPos.y, size.x, size.y, color);

    Object::Draw(canvas);
}