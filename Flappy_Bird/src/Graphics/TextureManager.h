#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include "tinyxml.h"
#include "Engine.h"
#include "Camera.h"

class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();

        static TextureManager* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }

        bool LoadMedia(std::string id, std::string filename);
        bool LoadText(std::string text, SDL_Color textColor);
        bool ParseTexture(std::string source);
        void QueryTexture(std::string id, int* out_w, int* out_h);
        void Drop(std::string id);
        void Clean();

        void Draw(std::string id, int x, int y, float scrollRatio = 0, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawCenter(std::string id, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawCenterX(std::string id, int y, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawCenterY(std::string id, int x, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, double angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void DrawBackground(std::string id, int x = 0, int y = 0, float scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void DrawText(std::string source, std::string text, int size, SDL_Color textColor, int x, int y);
        void DrawTextCenter(std::string source, std::string text, int size, SDL_Color textColor, int x, int y);

    private:
        std::map<std::string, SDL_Texture*> m_TextureMap;
        TTF_Font* m_Font;
        SDL_Texture* m_Texture;

        static TextureManager* s_Instance;

        float m_bgPos;
};

#endif // TEXTUREMANAGER_H
