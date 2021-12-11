#include <M5StickCPlus.h>
#include "base/Base.h"
#include "BookLoadre.h"
#include "BookSelectScene.h"

void setup()
{
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setCursor(16, 16);
  delay(500);

  Serial.println("setup book");
  BookLoader::Create();
  BookLoader *bookLoader = BookLoader::GetInstance();
  bookLoader->Begin();

  delay(100);

  SceneManager::Create();
  BookSelectScene *bookSelectScene = new BookSelectScene("BookSelectScene");
  SceneManager::GetInstance()->ChangeScene(bookSelectScene);
  
}

void loop()
{
  /*
  M5.update();
  if (M5.BtnA.isPressed())
  {
    m5.Lcd.fillScreen(TFT_BLACK);
    delay(200);
    char line[32] = "";
    BookLoader::GetInstance()->readBookLine(line, 32);
    printEfont(line, 16, 48, 2);
    Serial.println(line);
    delay(300);
  }

  if (M5.BtnB.wasPressed())
  {
    BookLoader::GetInstance()->saveProgress();
  }
  */

  delay(100);
}