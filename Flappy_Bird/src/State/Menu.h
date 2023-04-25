#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <iostream>
#include "GameState.h"
#include "Engine.h"
#include "Button.h"

class Menu : public GameState
{
    public:
        virtual void Init();
        virtual void Exit();
        virtual void Update();
        virtual void Render();
        virtual void HandleEvents();

        virtual void Pause();
        virtual void Resume();

        static Menu* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu(); }

    protected:
        Menu(){}
        virtual ~Menu(){
            delete s_Instance;
        }

    private:
        static void StartGame();
        static void Settings();
        static void Quit();

        GameMap* m_LevelMap;
        std::vector <GameObject*> m_GuiObjects;

        static int s_MapPos;
        static Menu* s_Instance;
};

#endif // MENU_H
