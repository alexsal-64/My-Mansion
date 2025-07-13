#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

typedef enum {
    SCENE_TRANSITION,
    SCENE_MENU,
    SCENE_SETTINGS,
    SCENE_SELECT,
    // Agrega aquí más escenas en el futuro
} SceneID;

void SceneManager_Init(void);
void SceneManager_Update(void);
void SceneManager_Draw(void);
void SceneManager_Unload(void);
void SceneManager_Change(SceneID newScene);
SceneID SceneManager_GetCurrent(void);

#endif // SCENE_MANAGER_H
