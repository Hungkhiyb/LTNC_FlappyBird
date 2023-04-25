#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "Vector2D.h"
#include "Engine.h"
#include "SDL.h"

class Camera
{
    public:
        Camera(){ m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; }
        virtual ~Camera(){ delete s_Instance; }

        void Init();
        void Update();

        inline SDL_Rect GetViewBox() { return m_ViewBox; }
        inline Vector2D GetPosition() { return m_Position; }
        inline void setTarget(Point* target) { m_Target = target; }
        inline static Camera* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera(); }

    private:
        Point* m_Target;
        Vector2D m_Position;

        SDL_Rect m_ViewBox;
        static Camera* s_Instance;
};

#endif // CAMERA_H
