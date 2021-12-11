#ifndef _BUTTON_H_INCLUDED_
#define _BUTTON_H_INCLUDED_

#include <M5StickCPlus.h>

namespace Component
{
    class Button
    {
    private:
        /* data */
        std::function<void()> mPressFunc;

    protected:
        bool mIsSelect = false;

    public:
        Button(std::function<void()> func) { mPressFunc = func; };
        ~Button(){};

        void Press()
        {
            if (mIsSelect)
                mPressFunc();
        }
        virtual void Select() { mIsSelect = true; };
        virtual void Release() { mIsSelect = false; };
    };
}
#endif