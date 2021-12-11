#include <efontEnableJa.h>
#include <efont.h>
#include <efontM5StickCPlus.h>

namespace Efont
{
    //char *efontUFT8toUTF16(uint16_t *pUTF16, char *pUTF8)
    //void getefontData(uint8_t *font, uint16_t fontUTF16);

    void printEfontM5(char *str)
    {
        printEfont(str);
    }
    void printEfontM5(char *str, int x, int y)
    {
        printEfont(str, x, y);
    }
    void printEfontM5(char *str, int x, int y, int textsize)
    {
        printEfont(str, x, y, textsize);
    }

    void printEfontM5(TFT_eSprite *sprite, char *str)
    {
        printEfont(sprite, str);
    }
    void printEfontM5(TFT_eSprite *sprite, char *str, int x, int y)
    {
        printEfont(sprite, str, x, y);
    }
    void printEfontM5(TFT_eSprite *sprite, char *str, int x, int y, int textsize)
    {
        printEfont(sprite, str, x, y, textsize);
    }
}