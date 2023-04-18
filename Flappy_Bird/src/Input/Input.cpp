#include "Input.h"

Input* Input::s_Instance = nullptr;

Input::Input()
{
    m_MouseButtonStates.push_back(false);
    m_MouseButtonStates.push_back(false);
    m_MouseButtonStates.push_back(false);
}

Input::~Input()
{
    delete s_Instance;
}
void Input::Listen()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                Engine::GetInstance()->Quit();
                break;
            case SDL_KEYUP:
                KeyUp();
                break;
            case SDL_KEYDOWN:
                KeyDown();
                break;
            case SDL_MOUSEBUTTONUP:
                ButtonUp(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                ButtonDown(event);
                break;
            case SDL_MOUSEMOTION:
                MouseMotion(event);
                break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key)
{
    if(m_KeyStates[key] == 1)
        return true;
    return false;
}

bool Input::GetKeyUp(SDL_Scancode key)
{
    if(m_KeyStates[key] == 0)
        return true;
    return false;
}

void Input::KeyUp()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown()
{
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::ButtonDown(SDL_Event event)
{
    if(SDL_BUTTON_LEFT == event.button.button)
        m_MouseButtonStates[LEFT] = true;

    if(SDL_BUTTON_MIDDLE == event.button.button)
        m_MouseButtonStates[MIDDLE] = true;

    if(SDL_BUTTON_RIGHT == event.button.button)
        m_MouseButtonStates[RIGHT] = true;
}

void Input::ButtonUp(SDL_Event event)
{
    if(SDL_BUTTON_LEFT == event.button.button)
        m_MouseButtonStates[LEFT] = false;

    if(SDL_BUTTON_MIDDLE == event.button.button)
        m_MouseButtonStates[MIDDLE] = false;

    if(SDL_BUTTON_RIGHT == event.button.button)
        m_MouseButtonStates[RIGHT] = false;
}

void Input::MouseMotion(SDL_Event event)
{
    m_MouseMotion.X = event.motion.x;
    m_MouseMotion.Y = event.motion.y;
}


