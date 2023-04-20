#include "Animation.h"

Animation::Animation()
{
    //ctor
}

Animation::~Animation()
{
    //dtor
}

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}

void Animation::Draw(int x, int y, int spriteWidth, int spriteHeight, double angle)
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, angle, m_Flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
}
