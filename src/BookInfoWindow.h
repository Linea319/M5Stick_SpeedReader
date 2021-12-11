#pragma once

#include <base/object/PivotObject.h>
#include "ButtonSelector.h"
#include "TextButton.h"
#include "Book.h"

class MenuWindowBase:public PivotObj
{

protected:
    /* data */
    ButtonSelector m_menuSelect;

public:
    MenuWindowBase(Transform initTr,DispVec2 initSize);
    virtual ~MenuWindowBase(){};

    virtual void Update(float dt) override;
};

class BookInfoWindow:public MenuWindowBase
{
private:
    /* data */
    BookInfo m_bookInfo;
public:
    BookInfoWindow(Transform initTr,DispVec2 initSize, BookInfo &bookInfo);
    ~BookInfoWindow();

protected:
    void OpenBook(bool isContinue);
};

class ReadSettingWindow:public MenuWindowBase
{
private:
    /* data */
    ReadingSetting &m_setting;

    TextButton *m_speedBtn;
public:
    ReadSettingWindow(Transform initTr,DispVec2 initSize, ReadingSetting &setting);
    ~ReadSettingWindow();

protected:
    void ChangeSpeed();
};