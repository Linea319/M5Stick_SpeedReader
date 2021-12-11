#ifndef SCENEMANAGER_H_INCLUDE
#define SCENEMANAGER_H_INCLUDE

#include "Singleton.h"
#include "Scene.h"

class SceneManager : public Singleton<SceneManager>
{
    public:
    friend class Singleton<SceneManager>;

    //シーン変更
    void ChangeScene(Scene* newScene);

    //カレントシーン取得
    Scene* GetCurrentScene() {return p_currentScene;}

    //現在のシーン更新
    void Update(float dt);
    void Draw();

    //現在のシーンにオブジェクトを追加
    void AddObject(Object* addObj);
    //現在のシーンからオブジェクトを削除
    void RemoveObject(Object *removeObj);
    // 現在のシーンの順序をソートし直し
    void SortHielarchey();

    protected:
    SceneManager(); //コンストラクタは封印
    ~SceneManager();

    //シーン変更の実体
    void ChangeSceneImpl();

    Scene* p_currentScene;
    Scene* p_requestScene;

    private:
    
};

#endif