#ifndef TRANSFORM_H_INCLUDE
#define TRANSFORM_H_INCLUDE

#include <VectorXf.h>

//Transform
class Transform{
    friend class Object; //Objectには公開

    public:
    Transform(): pos(Vec2f()), angle(0) {};
    Transform(Vec2f initPos, float initAngle = 0): pos(initPos), angle(initAngle) {};

    //getter
    Vec2f GetPos() const 
    {
        return m_pParent != nullptr ? m_pParent->GetPos() + pos : pos;
    }
    float GetAngle() const 
    {
        return m_pParent != nullptr ? m_pParent->GetAngle() + angle : angle;
    }
    Vec2f GetFwd() const {return Vec2f(cosf(GetAngle()*DEG_TO_RAD),sinf(GetAngle()*DEG_TO_RAD));}
    Vec2f GetUp() const {return Vec2f(sinf(GetAngle()*DEG_TO_RAD),cosf(GetAngle()*DEG_TO_RAD));}
    const Transform* GetParent() {return m_pParent;}

    //setter
    void SetPos(Vec2f setPos) {pos = setPos;}
    void AddPos(Vec2f addPos) {pos += addPos;}
    void SetAngle(float setAngle) {angle = setAngle;}
    void AddAngle(float addAngle) {angle += addAngle;}

    protected:
    void Start();
    void Update();
    void Draw();

    //変数
    protected:
    Vec2f pos;
    float angle;

    const Transform* m_pParent = nullptr;

};

#endif