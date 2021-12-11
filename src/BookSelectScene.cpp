#include "BookSelectScene.h"
#include <M5StickCPlus.h>
#include "base/SceneManager.h"
#include "ReadingScene.h"
#include "BookLoadre.h"
#include "TextButton.h"
#include "BookInfoWindow.h"

bool BookSelectScene::s_subMenu = false;

void BookSelectScene::Start()
{
    BookLoader *bookLoader = BookLoader::GetInstance();
    auto bookInfoList = bookLoader->GetBookList();

    DispVec2 infoDispSize(M5.Lcd.width() - 32, 20);
    for (int i = 0; i < bookInfoList.size(); i++)
    {
        char bookText[64];
        sprintf(bookText, "%s:%s", bookInfoList[i].title, bookInfoList[i].author);
        Serial.println(bookText);
        TextButton *obj = new TextButton(Transform(Vec2f(16, 20 * (i + 1)) * DOT_PER_UNIT), infoDispSize, bookText,
                                      std::bind(&BookSelectScene::PressSelect, this));
        obj->SetColor(TFT_WHITE, TFT_BLACK);
        bookSelector.RegisterButton(obj);
    }

    s_subMenu = false;
    Scene::Start();
}

void BookSelectScene::Update(float dt)
{
    M5.update();

    if(!s_subMenu)
    {
        if (M5.BtnA.wasPressed())
        {
            bookSelector.GetCurrentButton()->Press();
            return;
        }

        if (M5.BtnB.wasPressed())
        {
            bookSelector.Move(1);
        }
    }

    Scene::Update(dt);
}

void BookSelectScene::PressSelect()
{
    /*
    BookLoader::GetInstance()->openBook(bookSelector.GetCurrentIndex());
    ReadingScene *readingScene = new ReadingScene("ReadingScene");
    SceneManager::GetInstance()->ChangeScene(readingScene);
    */
    BookInfo selectBook = BookLoader::GetInstance()->GetBookList()[bookSelector.GetCurrentIndex()];
    Serial.printf("select %s\n",selectBook.title);

   DispVec2 infoDispSize(80, 64);
   Vec2f menuPos(M5.lcd.width() - 80,4);
   new BookInfoWindow(menuPos * DOT_PER_UNIT,infoDispSize
        ,selectBook);
    s_subMenu = true;
}

void BookSelectScene::SetSubMenuMode(bool sw)
{
    s_subMenu = sw;
}