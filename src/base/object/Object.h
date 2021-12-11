#ifndef OBJ_H_INCLUDE
#define OBJ_H_INCLUDE

#include <M5StickCPlus.h>
#include <VectorXf.h>
#include "../Transform.h"

#define UNIT_PER_DOT 10 //pos1あたりのドット
#define DOT_PER_UNIT 0.1 //逆数

union DispVec2{
    int16_t data[2];
    struct {
        /// \brief Stores the `x` component of the vector.
        int16_t x;

        /// \brief Stores the `y` component of the vector.
        int16_t y;
    };
    DispVec2(int16_t x, int16_t y):data{x,y} {};
    DispVec2():DispVec2(0,0){};
    DispVec2 operator + (DispVec2 rh) const{
        return DispVec2(this->x + rh.x,this->y + rh.y);
    }
    DispVec2 operator - (DispVec2 rh) const{
        return DispVec2(this->x - rh.x,this->y - rh.y);
    }
    DispVec2 operator * (float rh) const{
        return DispVec2(this->x * rh,this->y * rh);
    }
    DispVec2 operator * (int16_t rh) const{
        return DispVec2(this->x * rh,this->y * rh);
    }
    DispVec2 operator / (int16_t rh) const{
        return DispVec2(this->x / rh,this->y / rh);
    }
};

/// 2DObject
class Object{

    public:
    friend class Scene;
    Object();
    Object(Transform initTr);

    virtual ~Object();

    virtual DispVec2 GetDisplayPos() const;
    const Transform* GetTransform() {return &transform;}
    const uint16_t GetPriority() {return m_priority;}

    void SetParent(Object* parent);
    void Destroy();
    
    protected:
    virtual void Start(){};
    virtual void Update(float dt);
    //描画はそれぞれで実装
    virtual void Draw(TFT_eSprite* canvas){};

    //変数
    public:
    const char* name = "object";
    Transform transform;
    Vec2f velocity;
    float angularVelocity;

    float velocityDump;
    float angularDump;
    float limitSpeed;

    uint32_t color = TFT_WHITE;

    protected:
    Object* m_pParentObj = nullptr;
    uint16_t m_priority = 0;

};

#endif