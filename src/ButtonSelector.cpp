#include "ButtonSelector.h"

void ButtonSelector::RegisterButton(PButton button)
{
    buttons.push_back(button);
    //選択位置を初期化
    ResetSelect();
}


void ButtonSelector::UnregisterButton()
{
    buttons.erase(buttonItr);
    //選択位置を初期
    ResetSelect();
}

void ButtonSelector::UnregisterButton(PButton button)
{
    auto itr = std::find(buttons.begin(),buttons.end(),button);
    buttons.erase(itr);
    //選択位置を初期
    ResetSelect();
}

void ButtonSelector::Move(uint8_t movingDir)
{   
    (*buttonItr)->Release();
    buttonItr += movingDir;
    if(buttonItr >= buttons.end())
        buttonItr = buttons.begin();
    if(buttonItr < buttons.begin())
        buttonItr = buttons.end() - 1;
    (*buttonItr)->Select();
}

void ButtonSelector::Select(uint8_t selectNum)
{
    (*buttonItr)->Release();
    buttonItr = buttons.begin() + selectNum;
    (*buttonItr)->Select();
}

void ButtonSelector::ResetSelect()
{
    for (auto button : buttons)
    {
        button->Release();
    }
    buttonItr = buttons.begin();
    (*buttonItr)->Select();
}