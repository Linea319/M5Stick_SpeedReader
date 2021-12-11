#include "Scene.h"
#include <M5StickCPlus.h>

// 画面ダブルバッファ用スプライト
TFT_eSprite sceneCanvas = TFT_eSprite(&M5.Lcd);

Scene::Scene(const char *name) : sceneName(name),
                                 enable(false)
{
    //古いものを削除
    sceneCanvas.deleteSprite();
    // 画面ダブルバッファ用スプライト作成
    sceneCanvas.createSprite(M5.Lcd.width(), M5.Lcd.height());
    sceneCanvas.setSwapBytes(false);
}

Scene::~Scene()
{
    //登録されているオブジェクトも破棄
    enable = false;
    for (auto obj : objList)
    {
        delete (obj);
    }
}

void Scene::AddObjects()
{
    for (auto addObj : addObjList)
    {   
        auto findItr = std::find(objList.begin(), objList.end(), addObj);
        size_t dist = std::distance(objList.begin(), findItr);
        if (dist < objList.size())
            return;
        objList.push_back(addObj);
        //起動済みシーンだったら初期処理実行
        if (enable)
            addObj->Start();
    }
    addObjList.clear();
}

void Scene::RemoveObjects()
{
    for (auto removeObj : removeObjList)
    {    
        Serial.println("remove");
        //同じプライオリティを削除
        uint16_t removePriority = removeObj->GetPriority();
        for (auto itr = objList.begin(); itr != objList.end();)
        {
            auto obj = (*itr);
            if(removePriority == obj->GetPriority())
            {
                delete(obj);
                itr = objList.erase(itr);
                continue;
            }
            ++itr;
        }
    }

    removeObjList.clear();
}

void Scene::SortHielarchey()
{
    std::sort(objList.begin(),objList.end(),
    [](Object* a, Object* b) -> bool {
        return a->m_priority + (int)(a->m_pParentObj != nullptr)*0.5f  < b->m_priority +(int)(a->m_pParentObj != nullptr)*0.5f;
    });
    m_requestSort = false;

    /*
    for (auto obj : objList)
    {
        Serial.printf("%s prioty=%d\n",obj->name,obj->m_priority);
    }
    */
}

void Scene::Start()
{
    AddObjects();
    enable = true;
    //ソートで実行順を設定
    SortHielarchey();
    //登録済みのオブジェクトを初期処理
    for (auto obj : objList)
    {
        obj->Start();
    }
}

void Scene::Update(float dt)
{
    if (!enable)
        return;
    //削除
    RemoveObjects();
    //追加
    AddObjects();
    //リクエストが来ていたらソート
    if(m_requestSort)
        SortHielarchey();
    //登録済みのオブジェクトを処理
    for (auto obj : objList)
    {
        if(obj != nullptr)
            obj->Update(dt);
    }
}

void Scene::Draw()
{
    if (!enable)
        return;

    // まずは前フレームを描画してから次フレームを作る
    sceneCanvas.pushSprite(0, 0);

    sceneCanvas.startWrite();
    // 塗りつぶし
    sceneCanvas.fillSprite(bgColor);

    //登録済みのオブジェクトを描画
    for (auto obj : objList)
    {
        if(obj != nullptr)
            obj->Draw(&sceneCanvas);
    }

    sceneCanvas.endWrite();
}
