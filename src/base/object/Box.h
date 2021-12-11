#ifndef _BOX_H_INCLUDED_
#define _BOX_H_INCLUDED_

#include "Object.h"

class Box : public Object
{
private:
    /* data */
protected:
    void Draw(TFT_eSprite *canvas) override;

public:
    Box(Transform initTr, DispVec2 initSize):Object(initTr),size(initSize){};

    DispVec2 size;
};

#endif