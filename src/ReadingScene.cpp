#include "ReadingScene.h"
#include <M5StickCPlus.h>
#include "base/SceneManager.h"
#include "BookLoadre.h"
#include "TextButton.h"
#include "BookInfoWindow.h"
#include "BookSelectScene.h"

bool ReadingScene::s_subMenu = false;

void ReadingScene::Start()
{
    Transform textTr(Vec2f(8, 40) * DOT_PER_UNIT);
    DispVec2 textArea(M5.lcd.width() - 16, 80);
    m_mainTextObj = new TextObj(textTr, textArea, "START");

    BookInfo currentBook = BookLoader::GetInstance()->GetLoadingBook();
    char bookText[64];
    sprintf(bookText, " %s : %s", currentBook.title, currentBook.author);
    textArea = DispVec2(M5.lcd.width(), 20);
    TextObj *infoText = new TextObj(Transform(), textArea, bookText);
    infoText->SetColor(TFT_WHITE, TFT_BLUE);

    //buttons
    Transform buttonTr(Vec2f(0,M5.Lcd.height()-32) * DOT_PER_UNIT);
    //return
    TextButton *returnButton = new TextButton(buttonTr,DispVec2(m5.lcd.width()/3,16)
    ,"戻る", std::bind(&ReadingScene::ReturnSeletScene,this));
    m_bookSelector.RegisterButton(returnButton);
    buttonTr.SetPos(buttonTr.GetPos() + Vec2f(m5.lcd.width()/3,0)*DOT_PER_UNIT);
    //play
    TextButton *playButton = new TextButton(buttonTr,DispVec2(m5.lcd.width()/3,16)
    ,"再生/停止",[&](){m_isPlay = !m_isPlay;});
    m_bookSelector.RegisterButton(playButton);
    buttonTr.SetPos(buttonTr.GetPos() + Vec2f(m5.lcd.width()/3,0)*DOT_PER_UNIT);

    //setting 
    m_settingButton = new TextButton(buttonTr,DispVec2(m5.lcd.width()/3,16)
                                            ,"設定",std::bind(&ReadingScene::OpenSetting,this));
    m_bookSelector.RegisterButton(m_settingButton);

    //progress
    Transform progTr(Vec2f(0, M5.Lcd.height() - 16) * DOT_PER_UNIT);
    m_progressBar = new Box(progTr, DispVec2(m5.Lcd.width(), 16));
    m_progressBar->color = TFT_DARKCYAN;

    Scene::Start();
}

void ReadingScene::Update(float dt)
{
    M5.update();

    if (m_isPlay)
    {
        m_readTimer += dt * m_readSetting.readingSpeed;
        if (m_readTimer > 1.0f)
        {
            //更新
            char line[32] = "";
            BookLoader::GetInstance()->ReadBookLine(line, 32);
            m_mainTextObj->SetText(line, TFT_WHITE, m_readSetting.textSize);
            BookInfo bookInfo = BookLoader::GetInstance()->GetLoadingBook();
            float progRate = (float)bookInfo.progress / (float)bookInfo.size;
            m_progressBar->size.x = progRate * M5.lcd.width();
            //Serial.printf("progress rate %d%\n", (int)(progRate * 100));
            Serial.println(line);
            //タイマーリセット
            m_readTimer = 0;
        }
    }

    if(!s_subMenu)
    {
        if (M5.BtnA.wasPressed())
        {
            m_bookSelector.GetCurrentButton()->Press();
        }

        if (M5.BtnB.wasPressed())
        {
            m_bookSelector.Move(1);
        }
    }

    Scene::Update(dt);
}

void ReadingScene::ReturnSeletScene()
{
    BookLoader::GetInstance()->SaveProgress();
    BookLoader::GetInstance()->CloseBook();
    BookSelectScene *bookSelectScene = new BookSelectScene("BookSelectScene");
    SceneManager::GetInstance()->ChangeScene(bookSelectScene);
}

void ReadingScene::OpenSetting()
{
    DispVec2 infoDispSize = m_settingButton->size;
    infoDispSize.y = 64;
    Transform menuTr(*(m_settingButton->GetTransform()));
    menuTr.AddPos(Vec2f(0,-infoDispSize.y - 8)*DOT_PER_UNIT);
    new ReadSettingWindow(menuTr,infoDispSize,m_readSetting);
    s_subMenu = true; 
}