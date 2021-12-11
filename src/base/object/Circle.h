#ifndef CIRCLE_H_INCLUDE
#define CIRCLE_H_INCLUDE

#include "Object.h"

class Circle : public Object
{
    using Object::Object;

    public:

    float radius = 1.0f;

    protected:
    void Draw(TFT_eSprite* canvas) override;

};
#endif