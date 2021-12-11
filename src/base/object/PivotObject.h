#ifndef PIVOTOBJ_H_INCLUDE
#define PIVOTOBJ_H_INCLUDE

#include "Object.h"

class PivotObj:public Object
{
    //using Object::Object;
    public:
    PivotObj(Transform initTr,DispVec2 initSize);
    virtual ~PivotObj();

    void SetInverse(bool inv);
    bool GetInverse() const { return isInv;}
    Vec2f GetPivotFwd() const { return isInv ? -transform.GetFwd() : transform.GetFwd();}

    Vec2f pivot = Vec2f(0.5,0.5);   //ピボット座標　(0~1)
    DispVec2 size;

    protected:
    DispVec2 GetPivotDisplayPos() const;
    virtual void Draw(TFT_eSprite* canvas) override;
    
    // 描画用スプライト
    TFT_eSprite *sprite = nullptr;

    bool isInv;

};

#endif