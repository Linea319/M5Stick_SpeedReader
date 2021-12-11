#include "ImageObj.h"

ImageObj::ImageObj(Transform initTr,DispVec2 imgSize, const uint16_t* data):
PivotObj::PivotObj(initTr,imgSize),
p_img(data),
drawInv(false)
{
    uint16_t* p_invImgTmp = new uint16_t[size.x*size.y];
    for(int y = 0; y< size.y; y++)
    {
        int lineStart = y*size.x;
        for(int x = 0; x<size.x; x++)
        {
            int invX = size.x - (x+1);
            p_invImgTmp[lineStart + x] = p_img[lineStart + invX];
        }
    }
    p_invImg = p_invImgTmp;
    sprite->pushImage(0,0,size.x,size.y,p_img);
}

void ImageObj::Draw(TFT_eSprite* canvas)
{
    if(drawInv != isInv)
    {
        const uint16_t* p_drawImg = isInv ? p_invImg:p_img; 
        sprite->pushImage(0,0,size.x,size.y,p_drawImg);
    }
    drawInv = isInv;
    PivotObj::Draw(canvas);
}

ImageInfo ImageObj::GetImageInfo() const
{
    ImageInfo info;
    info.imgSIze = size;
    info.p_img = p_img;
    return info;
}