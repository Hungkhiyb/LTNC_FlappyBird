#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <SDL.h>

#include "TextureManager.h"

class Animation
{
    public:
        Animation();
        virtual ~Animation();

        void Update();
        void Draw(int x, int y, int spriteWidth, int spriteHeight, double angle = 0);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        int m_SpriteRow, m_SpriteFrame;
        int m_AnimSpeed, m_FrameCount;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif // ANIMATION_H
