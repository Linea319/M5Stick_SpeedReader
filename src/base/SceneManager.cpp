#include "SceneManager.h"

#define UPDATE_TIMER 0
#define DRAW_TIMER 1

// タイマー
hw_timer_t *sceneTimer = NULL;
hw_timer_t *sceneDrawTimer = NULL;
// 画面描画タスクハンドル
TaskHandle_t sceneTaskHandle;
TaskHandle_t sceneDrawTaskHandle;

//ミューテックス
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// タイマー割り込み
void IRAM_ATTR OnUpdateTimer()
{
    xTaskNotifyFromISR(sceneTaskHandle, 0, eIncrement, NULL);
}
void IRAM_ATTR OnDrawTimer()
{
    xTaskNotifyFromISR(sceneDrawTaskHandle, 0, eIncrement, NULL);
}
//タイマーで呼ばれる更新コール
void UpdateTask(void *pvParameters)
{
    while (1)
    {
        // タイマーが発生するまで待つ
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        SceneManager::GetInstance()->Update(timerAlarmReadSeconds(sceneTimer));
    }
}
//タイマーで呼ばれる描画コール
void DrawTask(void *pvParameters)
{
    while (1)
    {
        // タイマーが発生するまで待つ
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        //割込み禁止
        portENTER_CRITICAL(&timerMux);
        SceneManager::GetInstance()->Draw();
        portEXIT_CRITICAL(&timerMux);
    }
}

SceneManager::SceneManager()
{
    //初期シーンはない
    p_currentScene = NULL;

    // 更新タイマー作成(16.666ms)
    sceneTimer = timerBegin(UPDATE_TIMER, 80, true);
    timerAttachInterrupt(sceneTimer, &OnUpdateTimer, true);
    timerAlarmWrite(sceneTimer, 33333, true);
    timerAlarmEnable(sceneTimer);

    // 更新用タスク作成
    xTaskCreateUniversal(
        UpdateTask,
        "UpdateTask",
        8192,
        NULL,
        1,
        &sceneTaskHandle,
        APP_CPU_NUM);

    //return;

    // 描画タイマー作成(33.333ms)
    sceneDrawTimer = timerBegin(DRAW_TIMER, 80, true);
    timerAttachInterrupt(sceneDrawTimer, &OnDrawTimer, true);
    timerAlarmWrite(sceneDrawTimer, 33333, true);
    timerAlarmEnable(sceneDrawTimer);

    // 描画用タスク作成
    xTaskCreateUniversal(
        DrawTask,
        "DrawTask",
        8192,
        NULL,
        1,
        &sceneDrawTaskHandle,
        APP_CPU_NUM);
}

SceneManager::~SceneManager()
{
    //タイマー割り込みを止める
    timerEnd(sceneTimer);
    timerEnd(sceneDrawTimer);
}

void SceneManager::ChangeScene(Scene *newScene)
{
    p_requestScene = newScene;
}

void SceneManager::ChangeSceneImpl()
{
    //変更シーンがリクエスト済みか
    if(p_requestScene == nullptr)
    {
        return;
    }

    //割込み禁止
    portENTER_CRITICAL(&timerMux);

    if (p_currentScene != nullptr)
    {
        delete (p_currentScene);
    }

    //割り込み解除
    portEXIT_CRITICAL(&timerMux);

    p_currentScene = p_requestScene;
    p_requestScene = nullptr;
    p_currentScene->Start();

    Serial.println(p_currentScene->sceneName);
    Serial.printf("===============================================================\n");
    Serial.printf("Mem Test\n");
    Serial.printf("===============================================================\n");
    Serial.printf("esp_get_free_heap_size()                              : %6d\n", esp_get_free_heap_size());
    Serial.printf("esp_get_minimum_free_heap_size()                      : %6d\n", esp_get_minimum_free_heap_size());
    //xPortGetFreeHeapSize()（データメモリ）ヒープの空きバイト数を返すFreeRTOS関数です。これはを呼び出すのと同じheap_caps_get_free_size(MALLOC_CAP_8BIT)です。
    Serial.printf("xPortGetFreeHeapSize()                                : %6d\n", xPortGetFreeHeapSize());
}

void SceneManager::AddObject(Object *addObj)
{
    if(p_currentScene != nullptr)
        p_currentScene->AddObject(addObj);
}

void SceneManager::RemoveObject(Object *removeObj)
{
    if(p_currentScene != nullptr)
        p_currentScene->AddRemoveObject(removeObj);
}

void SceneManager::SortHielarchey()
{
    //ソートリクエスト
    if(p_currentScene != nullptr)
        p_currentScene->m_requestSort = true;
}

void SceneManager::Update(float dt)
{
    //シーンリクエスト来てたら変更
    if(p_requestScene != nullptr)
    {
        ChangeSceneImpl();
        return;
    }
    
    if (p_currentScene != nullptr)
    {
        p_currentScene->Update(dt);
    }
}

void SceneManager::Draw()
{

    //Serial.printf("draw\n");

    if (p_currentScene != nullptr)
    {
        p_currentScene->Draw();
    }
}