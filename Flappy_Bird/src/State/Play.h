#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Camera.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Tranform.h"
#include "MapParser.h"
#include "GameMap.h"
#include "Bird.h"
#include "Menu.h"
#include "GameState.h"
#include "Button.h"

class Play : public GameState
{
    public:
        virtual void Init();
        virtual void Exit();
        virtual void Render();
        virtual void Update();
        virtual void HandleEvents();

        virtual void Pause();
        virtual void Resume();
        void Menu();

        static Play* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Play(); }
        inline GameMap* GetMap1(){ return m_LevelMap1; }
        inline GameMap* GetMap2(){ return m_LevelMap2; }

    protected:
        Play() {
            m_Menu = false;
        }
        virtual ~Play() {
            delete s_Instance;
        }

    private:
        static void PPause();
        static void RResume();
        static void Home();
        static void Restart();

        static int s_MapPos;
        static int s_CollisionPos;

        bool m_Menu;
        bool m_GameOver;

        GameMap* m_LevelMap1;
        GameMap* m_LevelMap2;

        std::vector <GameObject*> m_GuiObjects;
        std::vector <GameObject*> m_GameObjects;

        static Play* s_Instance;
};

#endif // PLAY_H
