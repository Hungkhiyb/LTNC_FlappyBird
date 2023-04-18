#include "Button.h"

Button::Button(int x, int y, void(* callback)(), TextureIdList textureIDs)
: GameObject(new Properties())
{
    m_Transform->X = x;
    m_Transform->Y = y;
    m_Callback = callback;
    m_TextureIDs = textureIDs;
    m_TextureID = m_TextureIDs[NORMAL];
    TextureManager::GetInstance()->QueryTexture(m_TextureID, &m_Width, &m_Height);
    m_Shape = {m_Transform->X, m_Transform->Y, m_Width, m_Height};
    m_IsReleased = false;
}

Button::~Button()
{
    m_TextureIDs.clear();
    //m_TextureIDs.shrink_to_fit();
}

void Button::Clean()
{
    m_TextureIDs.clear();
    //m_TextureIDs.shrink_to_fit();
}

void Button::Update(float dt)
{
    Vector2D MouseMotion = Input::GetInstance()->GetMouseMotion();
    SDL_Point point = {MouseMotion.X, MouseMotion.Y};

    //std::cout << MouseMotion.X << " : " << MouseMotion.Y << std::endl;

    if(SDL_PointInRect(&point, &m_Shape)){
        if(Input::GetInstance()->GetMouseButtonDown(LEFT) && !m_IsReleased) {
            m_Callback();
            m_TextureID = m_TextureIDs[PRESSED];
            m_IsReleased = true;
        }
        else if(!Input::GetInstance()->GetMouseButtonDown(LEFT)){
            m_TextureID = m_TextureIDs[HOVER];
            m_IsReleased = false;
        }
    }
    else{
        m_TextureID = m_TextureIDs[NORMAL];
    }
}

void Button::Draw()
{
    TextureManager::GetInstance()->Draw(m_TextureID, m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

