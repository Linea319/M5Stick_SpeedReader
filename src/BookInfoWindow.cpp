#include "BookInfoWindow.h"
#include <M5StickCPlus.h>
#include <base/SceneManager.h>
#include "BookLoadre.h"
#include "ReadingScene.h"
#include "BookSelectScene.h"

MenuWindowBase::MenuWindowBase(Transform initTr,DispVec2 initSize):
PivotObj::PivotObj(initTr,initSize)
{
    pivot = Vec2f(0,0);

    color = TFT_WHITE;
    sprite->fillRect(0,0,initSize.x,initSize.y,TFT_BLACK);
    sprite->drawRect(0,0,initSize.x,initSize.y,color);
    name = "MenuWindowBase";
}

void MenuWindowBase::Update(float dt)
{
    if (M5.BtnA.wasPressed())
    {
        m_menuSelect.GetCurrentButton()->Press();
    }

    if (M5.BtnB.wasPressed())
    {
        m_menuSelect.Move(1);
    }

    PivotObj::Update(dt);
}

BookInfoWindow::BookInfoWindow(Transform initTr,DispVec2 initSize, BookInfo &bookInfo):
MenuWindowBase::MenuWindowBase(initTr,initSize),
m_bookInfo(bookInfo)
{
    DispVec2 infoDispSize(initSize.x-16, 18);
    Vec2f btnPos(8,8);
    TextButton *firstBtn = new TextButton(Transform(btnPos * DOT_PER_UNIT), infoDispSize, "最初から",
                                      std::bind(&BookInfoWindow::OpenBook, this,false));
    btnPos.y += 20;
    char continueTxt[32];
    sprintf(continueTxt,"続きから: %d%",bookInfo.GetProgressPercentage());
    TextButton *continueBtn = new TextButton(Transform(btnPos * DOT_PER_UNIT), infoDispSize, continueTxt,
                                      std::bind(&BookInfoWindow::OpenBook, this,true));
    btnPos.y += 20;
    TextButton *returnBtn = new TextButton(Transform(btnPos * DOT_PER_UNIT), infoDispSize, "戻る",
                                      std::bind(&BookInfoWindow::Destroy, this));
    //セレクタ登録
    m_menuSelect.RegisterButton(firstBtn);
    m_menuSelect.RegisterButton(continueBtn);
    m_menuSelect.RegisterButton(returnBtn);

    //parent
    firstBtn->SetParent(this);
    continueBtn->SetParent(this);
    returnBtn->SetParent(this);

    name = "BookInfoWindow";
}

BookInfoWindow::~BookInfoWindow()
{
    BookSelectScene::SetSubMenuMode(false);
}

void BookInfoWindow::OpenBook(bool isContinue)
{
    if(isContinue)
    {
        BookLoader::GetInstance()->LoadProgress(m_bookInfo);
    }
    else
    {
        m_bookInfo.progress = 0;
    }
    BookLoader::GetInstance()->OpenBook(m_bookInfo);
    ReadingScene *readingScene = new ReadingScene("ReadingScene");
    SceneManager::GetInstance()->ChangeScene(readingScene);
}

ReadSettingWindow::ReadSettingWindow(Transform initTr,DispVec2 initSize, ReadingSetting &setting):
MenuWindowBase::MenuWindowBase(initTr,initSize),
m_setting(setting)
{
    DispVec2 infoDispSize(initSize.x-16, 18);
    Vec2f btnPos(8,8);
    m_speedBtn = new TextButton(Transform(btnPos * DOT_PER_UNIT), infoDispSize, "速度",
                                std::bind(&ReadSettingWindow::ChangeSpeed,this));
    m_speedBtn->Select();
    btnPos.y += 20;
    TextButton *returnBtn = new TextButton(Transform(btnPos * DOT_PER_UNIT), infoDispSize, "戻る",
                                      std::bind(&ReadSettingWindow::Destroy, this));
    //セレクタ登録
    m_menuSelect.RegisterButton(m_speedBtn);
    m_menuSelect.RegisterButton(returnBtn);

    //parent
    m_speedBtn->SetParent(this);
    returnBtn->SetParent(this);

    name = "ReadingSettingWindow";
}

ReadSettingWindow::~ReadSettingWindow()
{
    ReadingScene::s_subMenu = false;
}

void ReadSettingWindow::ChangeSpeed()
{
    m_setting.readingSpeed *= 2;
    if(m_setting.readingSpeed > 50)
        m_setting.readingSpeed = 5;
    char speedBtnTxt[32];
    sprintf(speedBtnTxt,"速度:%d",(int)m_setting.readingSpeed);
    m_speedBtn->SetText(speedBtnTxt);
}