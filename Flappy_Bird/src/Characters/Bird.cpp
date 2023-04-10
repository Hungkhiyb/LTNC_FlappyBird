#include "Bird.h"

const float Time = 0.8;

Bird::Bird(Properties* props) : Character(props)
{
    m_Flip = SDL_FLIP_NONE;

    m_IsStart = false;
    m_IsDead = false;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-20, -20, 40, 40);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 3, 150);
}

Bird::~Bird()
{
    delete m_Collider;
    delete m_Animation;
}
void Bird::Draw()
{
    double angle = atan(m_Transform->VelY / VEL_X) * 360 / 2 / 3.14;
    std::cout << angle << std::endl;
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, angle);

    //Test box collision
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);

}

void Bird::HandleEvent(SDL_Event& event)
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_SPACE:
                m_IsStart = true;
                m_Transform->VelY = -VEL_JUMP;
                break;
        }
    }
}


void Bird::Update(float dt)
{
    if(m_IsStart){
        //Move on x axis
        m_LastSafePosition.X = m_Transform->X;
        m_Transform->VelX = VEL_X;
        m_Transform->X += m_Transform->VelX;
        m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get())){
            m_Transform->X = m_LastSafePosition.X;
            m_IsDead = true;
        }

        //Move on y axis
        m_LastSafePosition.Y = m_Transform->Y;
        m_Transform->TranslateVelY(GRAVITY);
        if(m_Transform->VelY > 10)
            m_Transform->VelY = 10;
        m_Transform->Y += m_Transform->VelY;
        m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

        if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        {
            m_Transform->Y = m_LastSafePosition.Y;
            m_IsDead = true;
        }
    }

    m_Origin->X = m_Transform->X + m_Width / 2;
    m_Origin->Y = m_Transform->Y + m_Height / 2;

    AnimationState();
    m_Animation->Update();
}

void Bird::AnimationState()
{

}

void Bird::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
