#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <vector>

#include "SDL.h"
#include "TileLayer.h"
#include "GameMap.h"
#include "Engine.h"
#include "Play.h"

class TileLayer;
using TileMap = std::vector<std::vector<int>>;

class CollisionHandler
{
    public:
        CollisionHandler();
        ~CollisionHandler();

        void Update(int mapPos);
        bool CheckCollision(SDL_Rect a, SDL_Rect b);
        bool MapCollision(SDL_Rect a);
        bool Delete(){ delete s_Instance; }

        inline static CollisionHandler* GetInstance(){ return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler(); }

    private:
        int MapPos;

        TileMap m_CollisionTilemap;
        TileLayer* m_CollisionLayer;
        static CollisionHandler* s_Instance;
};

#endif // COLLISIONHANDLER_H
