#ifndef _BookLoader_H_INCLUDED_
#define _BookLoader_H_INCLUDED_

#include <Arduino.h>
#include <Preferences.h>
#include "FS.h"
#include "base/Singleton.h"
#include "Book.h"

#define FORMAT_SPIFFS_IF_FAILED true

class BookLoader : public Singleton<BookLoader>
{
private:
    /* data */
    bool m_isEnable = false;
    std::vector<BookInfo> m_bookList;
    File m_loadingFile;
    BookInfo m_loadingBook;
    Preferences m_preferences;

public:
    BookLoader(/* args */){};
    ~BookLoader();

    void Begin();
    bool OpenBook(int index);
    bool OpenBook(const BookInfo &loadBook);
    bool ReadBookLine(char *outBuff, size_t len);
    void CloseBook();
    void SaveProgress();
    void LoadProgress(BookInfo &loadBook);

    std::vector<BookInfo> GetBookList() { return m_bookList; }
    BookInfo GetLoadingBook() { return m_loadingBook; }
};

#endif