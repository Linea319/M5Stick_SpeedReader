#ifndef _TEXTBUTTON_H_INCLUDED_
#define _TEXTBUTTON_H_INCLUDED_

#include "base/object/TextObj.h"
#include "base/comp/Button.h"

class TextButton : public TextObj, public Component::Button
{
private:
    /* data */
    void SwapColor() { SetColor(color, textColor); }

public:
    TextButton(Transform initTr, DispVec2 initSize, const char *initTxt, std::function<void()> func)
        : TextObj(initTr, initSize, initTxt),
          Component::Button(func)
    {
        name = initTxt;
    }

    void Select() override
    {   
        if(!mIsSelect)
            SwapColor();
        Component::Button::Select();
    };
    void Release() override
    {
        if(mIsSelect)
            SwapColor();
        Component::Button::Release();
    };
};

#endif