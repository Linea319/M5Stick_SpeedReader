#include "TextObj.h"
#include <base/EfontSetting.h>

#define MAX_STR_NUM 8

TextObj::TextObj(Transform initTr, DispVec2 initSize, const char *initTxt) : PivotObj::PivotObj(initTr, initSize)
{
    color = TFT_TRANSPARENT;
    pivot = Vec2f(0, 0);
    SetText(initTxt);
}

void TextObj::SetText(const char *text)
{
    //if (p_text != nullptr)
    //delete[] p_text;
    memset(drawText, 0, sizeof(drawText));
    strncpy(drawText, text, sizeof(drawText));
    isChangeText = true;
}

void TextObj::SetText(const char *text, uint32_t newColor)
{
    textColor = newColor;
    SetText(text);
}

void TextObj::SetText(const char *text, uint32_t newColor, uint8_t newSize)
{
    textSize = newSize;
    SetText(text, newColor);
}

void TextObj::SetColor(uint32_t newColor, uint32_t newBGColor)
{
    textColor = newColor;
    color = newBGColor;
    isChangeText = true;
}

void TextObj::Draw(TFT_eSprite *canvas)
{
    if (isChangeText)
    {
        sprite->fillSprite(color);
        sprite->setTextColor(textColor, color);
        Efont::printEfontM5(sprite, drawText, 0, 0, textSize);
        isChangeText = false;
    }

    PivotObj::Draw(canvas);
}