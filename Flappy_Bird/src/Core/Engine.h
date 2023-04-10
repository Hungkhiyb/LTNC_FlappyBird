#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

#include "Camera.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Tranform.h"
#include "MapParser.h"
#include "GameMap.h"
#include "Bird.h"

class Engine {

    public:
        Engine();
        ~Engine();

        static Engine* GetInstance(){ return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine(); }
        inline GameMap* GetMap1(){ return m_LevelMap1; }
        inline GameMap* GetMap2(){ return m_LevelMap2; }

        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        inline bool IsRunning(){ return m_IsRunning; }
        inline SDL_Renderer* GetRenderer(){ return m_Renderer; }

    private:
        bool m_IsRunning;
        static int s_MapPos;
        static int s_CollisionPos;

        GameMap* m_LevelMap1;
        GameMap* m_LevelMap2;

        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;

        std::vector<GameObject*> m_GameObjects;
};

#endif // ENGINE_H
