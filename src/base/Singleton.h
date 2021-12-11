#ifndef SINGLETON_H_INCLUDE
#define SINGLETON_H_INCLUDE

#include <cstddef>

template<class T>
class Singleton
{
public:
    static inline T* GetInstance()
    {
        return sp_instance;
    }

    static void Create()
    {
        if (sp_instance == nullptr)
        {
            sp_instance = new T();
        }
    }
    static void Destroy()
    {
        delete sp_instance;
        sp_instance = NULL;
    };

protected:
    Singleton() {} // 外部でのインスタンス作成は禁止
    virtual ~Singleton() {}

private:
    static T* sp_instance;

    void operator=(const Singleton& obj) {} // 代入演算子禁止
    Singleton(const Singleton &obj) {} // コピーコンストラクタ禁止
};

template< typename T > T* Singleton<T>::sp_instance = 0;

#endif
