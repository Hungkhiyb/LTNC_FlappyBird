#include "Engine.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        std::cerr << "Failed to initialize SDL: %s" << SDL_GetError();
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    m_Window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
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

    TextureManager::GetInstance()->ParseTexture("assets/Textures.xml");
    MapParser::GetInstance()->ParseFileMap("assets/Maps/Map.xml");

    PushState(Menu::GetInstance());

    std::cerr << "Game Initialize Success!" << std::endl;
    return m_IsRunning = true;
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
    m_State.back()->HandleEvents();
    //std::cout << "Done!" << std::endl;
}

void Engine::Update()
{
    m_State.back()->Update();
}

void Engine::Render()
{
    m_State.back()->Render();
}


bool Engine::Clean()
{
    while(!m_State.empty()) {
        m_State.back()->Exit();
        m_State.pop_back();
    }

    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::PopState()
{
	if (!m_State.empty()) {
		m_State.back()->Exit();
		m_State.pop_back();
	}

	if (!m_State.empty()) {
		m_State.back()->Resume();
	}
}

void Engine::PushState(GameState* current)
{
	if (!m_State.empty()) {
		m_State.back()->Pause();
	}

	m_State.push_back(current);
	m_State.back()->Init();
}

void Engine::ChangeState(GameState* target)
{
	if (!m_State.empty()) {
		m_State.back()->Exit();
		m_State.pop_back();
	}

	m_State.push_back(target);
	m_State.back()->Init();

}

