#include "Engine.h"

Engine* Engine::s_Instance = nullptr;
int Engine::s_MapPos;
int Engine::s_CollisionPos;
Bird* player = nullptr;

Engine::Engine()
{
    s_MapPos = 0;
    s_CollisionPos = 0;
}

Engine::~Engine()
{
    delete s_Instance;
    delete player;
}

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        std::cerr << "Failed to initialize SDL: %s" << SDL_GetError();
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if(m_Window == nullptr)
    {
        std::cerr << "Failed to create window SDL: %s" << SDL_GetError();
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr)
    {
        std::cerr << "Failed to create renderer SDL: %s" << SDL_GetError();
        return false;
    }

    if(!MapParser::GetInstance()->ParseFileMap("assets/Maps/Map.xml"))
    {
        std::cout << "Failed to load map file!" << std::endl;
    }

    m_LevelMap1 = MapParser::GetInstance()->GetMap("level0");
    m_LevelMap2 = MapParser::GetInstance()->GetRandomMap();

    TextureManager::GetInstance()->ParseTexture("assets/Textures.xml");

    player = new Bird(new Properties("bird", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 64 * 2, 32, 32));

    m_GameObjects.push_back(player);

    Camera::GetInstance()->setTarget(player->GetOrigin());

    return m_IsRunning = true;
}

void Engine::Events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        player->HandleEvent(event);
        if(event.type == SDL_QUIT)
            m_IsRunning = false;
    }
}

void Engine::Update()
{
    if(player->GetOrigin()->X >= s_MapPos + SCREEN_WIDTH + SCREEN_WIDTH / 2)
    {
        m_LevelMap1 = m_LevelMap2;
        m_LevelMap2 = MapParser::GetInstance()->GetRandomMap();
        s_MapPos += SCREEN_WIDTH;
    }

    m_LevelMap1->Update();
    m_LevelMap2->Update();

    if(player->GetOrigin()->X + 32 >= s_CollisionPos + SCREEN_WIDTH){
        s_CollisionPos += SCREEN_WIDTH;
        CollisionHandler::GetInstance()->Update(s_CollisionPos);
    }

    for(int i = 0; i < m_GameObjects.size(); i++)
        m_GameObjects[i]->Update(1);

    Camera::GetInstance()->Update(0);
    if(player->PlayerDead())
        m_IsRunning = false;
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 0, 255, 255, 255);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->DrawBackground("bg1", 960, 640, 0.2);

    m_LevelMap1->Render(s_MapPos);
    m_LevelMap2->Render(s_MapPos + SCREEN_WIDTH);

    for(int i = 0; i < m_GameObjects.size(); i++)
        m_GameObjects[i]->Draw();

    SDL_RenderPresent(m_Renderer);
}


bool Engine::Clean()
{
    for(int i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Clean();
        delete m_GameObjects[i];
    }

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}



