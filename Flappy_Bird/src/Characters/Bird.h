#ifndef BIRD_H
#define BIRD_H

#include <math.h>

#include "Character.h"
#include "Animation.h"
#include "Collider.h"
#include "Vector2D.h"
#include "Camera.h"
#include "CollisionHandler.h"

#define VEL_JUMP 5
#define DELAY_JUMP 50
#define GRAVITY 0.2f
#define VEL_X 3

class Animation;

class Bird : public Character
{
    public:
        Bird(Properties* props);
        ~Bird();

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();
        void HandleEvent(SDL_Event& event);
        inline bool PlayerDead(){ return m_IsDead; }

    private:
        void AnimationState();

        bool m_IsStart;
        bool m_IsDead;

        Collider* m_Collider;
        Animation* m_Animation;
        Vector2D m_LastSafePosition;
        SDL_RendererFlip m_Flip;
};
#endif // BIRD_H
