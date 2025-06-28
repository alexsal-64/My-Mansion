#include "scene_manager.h"
#include "transition_circle.h"
#include "scene_menu.h"
#include "scene_settings.h"

static SceneID currentScene;

void SceneManager_Init(void) {
    currentScene = SCENE_TRANSITION;
    TransitionCircle_Init();
}

void SceneManager_Update(void) {
    switch (currentScene) {
        case SCENE_TRANSITION:
            TransitionCircle_Update();
            if (TransitionCircle_IsDone()) {
                SceneManager_Change(SCENE_MENU);
            }
            break;
        case SCENE_MENU:
            SceneMenu_Update();
            break;
        case SCENE_SETTINGS:
            SceneSettings_Update();
            break;
    }
}

void SceneManager_Draw(void) {
    switch (currentScene) {
        case SCENE_TRANSITION:
            TransitionCircle_Draw();
            break;
        case SCENE_MENU:
            SceneMenu_Draw();
            break;
        case SCENE_SETTINGS:
            SceneSettings_Draw();
            break;
    }
}

void SceneManager_Unload(void) {
    // Placeholder para liberar recursos si es necesario
}

void SceneManager_Change(SceneID newScene) {
    currentScene = newScene;
    switch (newScene) {
        case SCENE_TRANSITION: TransitionCircle_Init(); break;
        case SCENE_MENU: SceneMenu_Init(); break;
        case SCENE_SETTINGS: SceneSettings_Init(); break;
    }
}

SceneID SceneManager_GetCurrent(void) {
    return currentScene;
}
