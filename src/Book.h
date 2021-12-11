#ifndef _BOOK_H_INCLUDED_
#define _BOOK_H_INCLUDED_

#include <Arduino.h>

struct BookInfo
{
    /* data */
    char title[32];
    char author[32];
    char path[64];
    int size = 0;
    int progress = 0;

    bool operator == (const BookInfo &a)
    {
        //タイトルとパスで一致
        return strcmp(a.path,path) == 0;
    }

    const char *GetSaveStr()
    {
        return strndup(title, 8);
    }

    const int GetProgressPercentage()
    {
        return progress/(float)size*100U;
    }
};

struct ReadingSetting
{
    float readingSpeed = 5.0f;
    int textSize = 2;
};

#endif