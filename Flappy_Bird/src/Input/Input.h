#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "Engine.h"
#include "Vector2D.h"

enum MouseButtons {LEFT = 0, MIDDLE = 1, RIGHT = 2};

class Input
{
    public:
        Input();
        ~Input();

        void Listen();
        void Delete(){ delete s_Instance; }
        bool GetKeyDown(SDL_Scancode key);
        bool GetKeyUp(SDL_Scancode key);

        inline bool GetMouseButtonDown(MouseButtons button) { return m_MouseButtonStates[button]; }
        inline Vector2D GetMouseMotion() { return m_MouseMotion; }
        inline static Input* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }

    private:
        void KeyUp();
        void KeyDown();
        void ButtonDown(SDL_Event event);
        void ButtonUp(SDL_Event event);
        void MouseMotion(SDL_Event event);

        Vector2D m_MouseMotion;
        const Uint8* m_KeyStates;
        static Input* s_Instance;
        std::vector<bool> m_MouseButtonStates;
};

#endif // INPUT_H
