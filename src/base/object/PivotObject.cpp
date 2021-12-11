#include "PivotObject.h"

PivotObj::PivotObj(Transform initTr, DispVec2 initSize) : Object::Object(initTr),
                                                          size(initSize),
                                                          isInv(false)
{
    // 画像用スプライト作成
    sprite = new TFT_eSprite(&M5.Lcd);
    sprite->createSprite(size.x, size.y);
    sprite->setSwapBytes(true);
}

PivotObj::~PivotObj()
{
    sprite->deleteSprite();
    delete sprite;
}

void PivotObj::Draw(TFT_eSprite *canvas)
{
    DispVec2 pivotPos = GetPivotDisplayPos();
    //canvas->setCursor(pivotPos.x, pivotPos.y);
    canvas->setPivot(pivotPos.x, pivotPos.y);
    sprite->pushRotated(canvas, transform.GetAngle(), TFT_TRANSPARENT);

#ifdef DEBUG_RENDER
    DispVec2 dispPos = GetDisplayPos();
    canvas->fillCircle(dispPos.x, dispPos.y, 10, TFT_PURPLE);
    canvas->fillCircle(pivotPos.x, pivotPos.y, 10, TFT_DARKCYAN);
    canvas->drawRect(pivotPos.x - size.x * 0.5f, pivotPos.y - size.y * 0.5f, size.x, size.y, TFT_CASET);
//Serial.printf("pivot pos x=%d, y=%d\n", dispPos.x, dispPos.y);
//Serial.printf("pivot draw start x=%d, y=%d\n", pivotPos.x, pivotPos.y);
#endif
}

DispVec2 PivotObj::GetPivotDisplayPos() const
{
    Vec2f normalizePivot = Vec2f(0.5) - pivot;
    DispVec2 pivPos = DispVec2(size.x * normalizePivot.x, size.y * normalizePivot.y);
    return GetDisplayPos() + pivPos;
}

void PivotObj::SetInverse(bool inv)
{
    if (isInv != inv)
        pivot.x = 1.0f - pivot.x;
    isInv = inv;
}