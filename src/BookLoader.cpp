#include "BookLoadre.h"
#include "SPIFFS.h"

void BookLoader::Begin()
{
    m_isEnable = SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED);
    m_isEnable &= m_preferences.begin("Book");
    m_bookList.clear();

    if (!m_isEnable)
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }

    //create book list
    const char *dirname = "/book";
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = SPIFFS.open(dirname);
    if (!root)
    {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory())
    {
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file)
    {
        if (!file.isDirectory())
        {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());

            BookInfo bookInfo;
            sprintf(bookInfo.title, file.readStringUntil('\n').c_str());
            sprintf(bookInfo.author, file.readStringUntil('\n').c_str());
            sprintf(bookInfo.path, file.name());
            bookInfo.size = file.size();
            bookInfo.progress = m_preferences.getInt(bookInfo.GetSaveStr());
            m_bookList.push_back(bookInfo);

            Serial.print("  TITLE: ");
            Serial.println(bookInfo.title);
            Serial.print("AUTHOR: ");
            Serial.println(bookInfo.author);
            Serial.print("PATH: ");
            Serial.println(bookInfo.path);
            Serial.print("PROGRESS: ");
            Serial.print(bookInfo.progress);
            Serial.print("\tPROGRESS KEY: ");
            Serial.println(bookInfo.GetSaveStr());
        }
        file = root.openNextFile();
    }
    root.close();
}

BookLoader::~BookLoader()
{
    SPIFFS.end();
    m_preferences.end();
}

bool BookLoader::OpenBook(int index)
{
    if (!m_isEnable)
    {
        return false;
    }

    if (index >= m_bookList.size())
    {
        Serial.println("- index is bigger than book list");
        return false;
    }

    return OpenBook(m_bookList[index]);
}

bool BookLoader::OpenBook(const BookInfo &loadBook)
{
    if (!m_isEnable)
    {
        return false;
    }

    Serial.printf("Reading file: %s\r\n", loadBook.path);

    m_loadingFile = SPIFFS.open(loadBook.path);
    if (!m_loadingFile || m_loadingFile.isDirectory())
    {
        Serial.println("- failed to open file for reading");
        m_loadingFile.close();
        return false;
    }

    //load progress
    m_loadingFile.seek(loadBook.progress);

    m_loadingBook = loadBook;
    Serial.println("- read from file:");
    return true;
}

bool BookLoader::ReadBookLine(char *outBuff, size_t len)
{
    if (!m_isEnable || !m_loadingFile)
    {
        Serial.println("- not open book");
        return false;
    }

    if (!m_loadingFile.available())
    {
        return false;
    }

    int count = 0;
    char c;
    do
    {
        c = m_loadingFile.read();
        outBuff[0] = c;
        outBuff++;
        m_loadingBook.progress++;
        count++;
    } while (count < len && c != '\n' && c != '\r\n');

    return true;
}

void BookLoader::CloseBook()
{
    if (!m_isEnable || !m_loadingFile)
    {
        Serial.println("- not open book");
        return;
    }

    m_loadingFile.close();
}

void BookLoader::SaveProgress()
{
    if (!m_isEnable || !m_loadingFile)
        return;

    if (m_loadingFile.available())
    {
        BookInfo *currentBook = &m_loadingBook;
        m_preferences.putInt(currentBook->GetSaveStr(), currentBook->progress);
        Serial.print("SAVE PROGRESS: ");
        Serial.print(currentBook->progress);
        Serial.print("\tPROGRESS KEY: ");
        Serial.println(currentBook->GetSaveStr());
    }
}

void BookLoader::LoadProgress(BookInfo &loadBook)
{
    if (m_isEnable)
        loadBook.progress = m_preferences.getInt(loadBook.GetSaveStr());
}