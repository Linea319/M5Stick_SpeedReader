#ifndef _BOOKSELECTSCENE_H_INCLUDED_
#define _BOOKSELECTSCENE_H_INCLUDED_

#include "base/Scene.h"
#include "base/object/Box.h"
#include "ButtonSelector.h"

class BookSelectScene : public Scene
{
    using Scene::Scene;
private:
    /* data */
    ButtonSelector bookSelector;
    static bool s_subMenu;

protected:
    void Start() override;
    void Update(float dt) override;

    void SelectNext();
    void PressSelect();

public:
    static void SetSubMenuMode(bool sw);
};

#endif