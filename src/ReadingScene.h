#ifndef _READINGSCENE_H_INCLUDED_
#define _READINGSCENE_H_INCLUDED_

#include "base/Scene.h"
#include "base/object/Box.h"
#include "TextButton.h"
#include "Book.h"
#include "ButtonSelector.h"

class ReadingScene : public Scene
{
    using Scene::Scene;

private:
    /* data */
    TextObj *m_mainTextObj;
    Box *m_progressBar;
    ButtonSelector m_bookSelector;
    TextButton *m_settingButton;

    ReadingSetting m_readSetting;

    float m_readTimer = 0;
    bool m_isPlay = false;

protected:
    void Start() override;
    void Update(float dt) override;

    void ReturnSeletScene();
    void OpenSetting();

public:
    static bool s_subMenu;
};

#endif