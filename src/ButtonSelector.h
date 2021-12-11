#ifndef _BUTTONSELECTOR_H_INCLUDED_
#define _BUTTONSELECTOR_H_INCLUDED_

#include "base/comp/Button.h"

typedef Component::Button* PButton;

class ButtonSelector
{
private:
    /* data */
    std::vector<PButton> buttons;
    std::vector<PButton>::iterator buttonItr;

public:
    ButtonSelector() {
        buttons.clear();
    }
    ~ButtonSelector() {
        buttons.clear();
    }

    void RegisterButton(PButton button);
    void UnregisterButton();
    void UnregisterButton(PButton button);
    void Move(uint8_t movingDir);
    void Select(uint8_t selectNum);
    void ResetSelect();

    PButton GetCurrentButton(){return  *buttonItr;}
    int8_t GetCurrentIndex(){return  std::distance(buttons.begin(),buttonItr);}
    
};

#endif