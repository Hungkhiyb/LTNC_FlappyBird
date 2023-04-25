#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "TextureManager.h"
#include "Input.h"

using TextureIdList = std::vector<std::string>;

enum ButtonStates {NORMAL = 0, HOVER = 1, PRESSED = 2};

class Button : public GameObject
{
    public:
        Button(int x, int y, void (*callback)(), TextureIdList textureIDs);
        virtual ~Button();

        virtual void Clean() override;
        virtual void Update() override;
        virtual void Draw();

    private:
        SDL_Rect m_Shape;
        bool m_IsReleased;
        void (*m_Callback)();
        TextureIdList m_TextureIDs;


};

#endif // BUTTON_H
