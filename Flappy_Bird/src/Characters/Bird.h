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
#define DELAY_JUMP 200
#define GRAVITY 0.2f
#define VEL_X 3

class Animation;

class Bird : public Character
{
    public:
        Bird(Properties* props);
        ~Bird();

        virtual void Draw();
        virtual void Update();
        virtual void Clean();
        void HandleEvent();
        inline bool PlayerDead(){ return m_IsDead; }
        inline int GetPoint(){ return m_CountPoint; }

    private:
        void AnimationState();
        void CountPoint();

        bool m_IsStart;
        bool m_IsDead;

        int m_CountPoint;
        int m_delayJump;

        Collider* m_Collider;
        Animation* m_Animation;
        Vector2D m_LastSafePosition;
        SDL_RendererFlip m_Flip;
};
#endif // BIRD_H
