#ifndef _EFONTSETTING_H_INCLUDED_
#define _EFONTSETTING_H_INCLUDED_

#include <M5StickCPlus.h>

namespace Efont
{

    //prototype
    //char *efontUFT8toUTF16(uint16_t *pUTF16, char *pUTF8);
    //void getefontData(uint8_t *font, uint16_t fontUTF16);

    void printEfontM5(char *str);
    void printEfontM5(char *str, int x, int y);
    void printEfontM5(char *str, int x, int y, int textsize);

    void printEfontM5(TFT_eSprite *sprite, char *str);
    void printEfontM5(TFT_eSprite *sprite, char *str, int x, int y);
    void printEfontM5(TFT_eSprite *sprite, char *str, int x, int y, int textsize);

}
#endif