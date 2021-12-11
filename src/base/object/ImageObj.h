#ifndef IMGOBJ_H_INCLUDE
#define IMGOBJ_H_INCLUDE

#include "PivotObject.h"

struct ImageInfo
{
    DispVec2 imgSIze;
    const uint16_t* p_img;
};

class ImageObj : public PivotObj
{
    public:
    ImageObj(Transform initTr,DispVec2 imgSize, const uint16_t* data);
    ~ImageObj(){delete[] p_invImg;};

    ImageInfo GetImageInfo() const;

    protected:
    virtual void Draw(TFT_eSprite* canvas) override;

    const uint16_t* p_img;
    const uint16_t* p_invImg;

    bool drawInv;

};
#endif