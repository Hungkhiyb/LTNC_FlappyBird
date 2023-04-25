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
#include "GameState.h"
#include "Input.h"
#include "Play.h"
#include "Menu.h"
#include "SoundManager.h"


class Engine {

    public:
        bool Init();
        bool Clean();
        void Quit();

        void Update();
        void Render();
        void Events();

        void PopState();
        void PushState(GameState* current);
        void ChangeState(GameState* target);

        inline bool IsRunning(){ return m_IsRunning; }
        inline SDL_Renderer* GetRenderer(){ return m_Renderer; }
        inline SDL_Window* GetWindow() { return m_Window; }
        inline static Engine* GetInstance(){ return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine(); }

    private:
        Engine() {}
        virtual ~Engine() { delete s_Instance; }

        bool m_IsRunning;

        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;

        std::vector<GameState*> m_State;
};

#endif // ENGINE_H
