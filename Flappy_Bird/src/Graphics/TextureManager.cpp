#include "TextureManager.h"


TextureManager* TextureManager::s_Instance = nullptr;
float TextureManager::s_bgPos;

TextureManager::TextureManager()
{
    s_bgPos = 0;
}

TextureManager::~TextureManager()
{
    delete s_Instance;
}

bool TextureManager::LoadMedia(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        std::cerr << "Failed to load texture: " << filename.c_str() << ' ' << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr)
    {
        std::cerr << "Failed to load texture from surface: " << SDL_GetError() << std::endl;
        return false;
    }

    m_TextureMap[id] = texture;
    return true;
}

bool TextureManager::ParseTexture(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cerr << "Failed to load: "<< source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
        if(e->Value() == std::string("texture")){
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            LoadMedia(id, src);
        }
    }

    std::cout << "ParseTexture load success!" << std::endl;
    return true;
}

void TextureManager::QueryTexture(std::string id, int* out_w, int* out_h)
{
    SDL_QueryTexture(m_TextureMap[id], NULL, NULL, out_w, out_h);
}


void TextureManager::Draw(std::string id, int x, int y, float scrollRatio, float scale, SDL_RendererFlip flip)
{
    int width, height;
    QueryTexture(id, &width, &height);

    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition() * scrollRatio;

    SDL_Rect desRect = {x - cam.X, y - cam.Y, width * scale, height * scale};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::DrawCenter(std::string id, float scale, SDL_RendererFlip flip)
{
    int width, height;
    QueryTexture(id, &width, &height);

    SDL_Rect srcRect = {0, 0, width, height};

    int x, y;
    x = (SCREEN_WIDTH - width * scale) / 2;
    y = (SCREEN_HEIGHT - height * scale) / 2;
    SDL_Rect desRect = {x, y, width * scale, height * scale};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::DrawCenterX(std::string id, int y, float scale, SDL_RendererFlip flip)
{
    int width, height;
    QueryTexture(id, &width, &height);

    SDL_Rect srcRect = {0, 0, width, height};

    int x;
    x = (SCREEN_WIDTH - width * scale) / 2;
    SDL_Rect desRect = {x, y, width * scale, height * scale};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::DrawCenterY(std::string id, int x, float scale, SDL_RendererFlip flip)
{
    int width, height;
    QueryTexture(id, &width, &height);

    SDL_Rect srcRect = {0, 0, width, height};

    int y;
    y = (SCREEN_HEIGHT - height * scale) / 2;
    SDL_Rect desRect = {x, y, width * scale, height * scale};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, 0, nullptr, flip);
}


void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {tileSize*frame, tileSize*(row), tileSize, tileSize};
    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect desRect = {x - cam.X, y - cam.Y, tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &desRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, double angle, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*(row - 1), width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect desRect = {x - cam.X, y - cam.Y, width * 2, height * 2};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect, angle, nullptr, flip);
}

void TextureManager::DrawBackground(std::string id, int x, int y, float scale, SDL_RendererFlip flip)
{
    int width, height;
    QueryTexture(id, &width, &height);

    SDL_Rect srcRect = {0, 0, width, height};

    SDL_Rect desRect1 = {s_bgPos, 0, width * scale, height * scale};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect1, 0, nullptr, flip);

    SDL_Rect desRect2 = {s_bgPos + width, 0, width * scale, height * scale};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &desRect2, 0, nullptr, flip);

    s_bgPos -= 0.2;
    if(s_bgPos <= -SCREEN_WIDTH)
        s_bgPos = 0;
}


void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();

    std::cerr << "Texture map cleaned!";
}

