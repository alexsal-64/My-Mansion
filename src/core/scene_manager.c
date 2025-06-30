#include "scene_manager.h"
#include "transition_circle.h"
#include "scene_menu.h"
#include "scene_settings.h"
#include <raylib.h>

static SceneID currentScene;

// Nuevo: Para saber a qué escena vamos a transicionar
static SceneID nextScene = SCENE_MENU;

void SceneManager_Init(void) {
    currentScene = SCENE_TRANSITION;
    nextScene = SCENE_MENU;
    TransitionCircle_Init();
}

void SceneManager_Update(void) {
    switch (currentScene) {
        case SCENE_TRANSITION:
            TransitionCircle_Update();
            if (TransitionCircle_IsDone()) {
                SceneManager_Change(nextScene);
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
            // Dibuja la escena a la que se está transicionando (menú, por ahora)
            if (nextScene == SCENE_MENU) {
                SceneMenu_Draw();
            } else if (nextScene == SCENE_SETTINGS) {
                SceneSettings_Draw();
            }
            // Encima dibuja la transición circular
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
