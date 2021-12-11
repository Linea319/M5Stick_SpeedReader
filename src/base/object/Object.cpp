#include "Object.h"
#include <base/SceneManager.h>

Object::Object(Transform initTr):
transform(initTr),
velocity(),
angularVelocity(0),
velocityDump(0),
angularDump(0),
limitSpeed(-1.f)
{
    //追加はここで
    SceneManager::GetInstance()->AddObject(this);
}

Object::Object():
Object(Transform())
{
}

Object::~Object()
{
    
}

void Object::Destroy()
{
    SceneManager::GetInstance()->RemoveObject(this);
}

DispVec2 Object::GetDisplayPos() const
{
    Vec2f dotPos = transform.GetPos() * UNIT_PER_DOT;
    DispVec2 ret = DispVec2((int16_t)dotPos.x,(int16_t)dotPos.y);

    return ret;
}

void Object::Update(float dt)
{
    if(limitSpeed > 0)
        velocity.limit(limitSpeed);

    velocity -= velocity*velocityDump;
    angularVelocity -= angularVelocity*angularDump;

    transform.AddPos(velocity*dt);
    transform.AddAngle(angularVelocity*dt);
}

void Object::SetParent(Object* parent = nullptr)
{
    m_pParentObj = parent;
    if(parent != nullptr)
    {
        transform.m_pParent =  parent->GetTransform();
        m_priority = parent->GetPriority();
        Serial.printf("set prent priority = %d\n",parent->GetPriority());
    }
    else
    {
        transform.m_pParent =  nullptr;
    }
    //シーンの順序ソートをリクエスト
    SceneManager::GetInstance()->SortHielarchey();

}