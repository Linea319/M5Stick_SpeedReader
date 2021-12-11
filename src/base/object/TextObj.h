#ifndef _TEXTOBJ_H_INCLUDED_
#define _TEXTOBJ_H_INCLUDED_

#include "PivotObject.h"

class TextObj : public PivotObj
{
public:
    TextObj(Transform initTr, DispVec2 initSize, const char *initTxt);

    const char *GetText() { return &drawText[0]; }
    void SetText(const char *text);
    void SetText(const char *text, uint32_t newColor);
    void SetText(const char *text, uint32_t newColor, uint8_t newSize);
    void SetColor(uint32_t newColor, uint32_t newBGColor);

protected:
    virtual void Draw(TFT_eSprite *canvas) override;

    uint32_t textColor = TFT_WHITE;
    uint8_t textSize = 1;
    char drawText[64];

private:
    bool isChangeText = false;
};

#endif