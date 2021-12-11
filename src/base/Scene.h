#ifndef SCENE_H_INCLUDE
#define SCENE_H_INCLUDE

#include <vector>
#include "object/Object.h"

class Scene
{
public:
    friend class SceneManager; //SceneManagerには公開

    Scene(const char *name);
    virtual ~Scene();

    void AddObject(Object *addObj)
    {
        addObj->m_priority = ++m_maxPriority;
        addObjList.push_back(addObj);
    }
    void AddRemoveObject(Object *remObj){removeObjList.push_back(remObj);}

    String sceneName;

protected:
    virtual void Draw();
    virtual void Start();
    virtual void Update(float dt);

    void AddObjects();
    void RemoveObjects();
    void SortHielarchey();

    std::vector<Object *> objList;
    std::vector<Object *> addObjList;
    std::vector<Object *> removeObjList;
    bool enable;

    uint32_t bgColor = TFT_BLACK;

    uint16_t m_maxPriority = 0;
    bool m_requestSort = false;

private:
};

#endif
