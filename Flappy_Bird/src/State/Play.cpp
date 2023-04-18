#include "Play.h"

Play* Play::s_Instance = nullptr;
int Play::s_MapPos = 0;
int Play::s_CollisionPos = 0;
Bird* player = nullptr;
Button* pause = nullptr;

void Play::Init()
{
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    m_LevelMap1 = MapParser::GetInstance()->GetMap("level0");
    m_LevelMap2 = MapParser::GetInstance()->GetRandomMap();

    player = new Bird(new Properties("bird", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 64 * 2, 32, 32));
    m_GameObjects.push_back(player);
    Camera::GetInstance()->setTarget(player->GetOrigin());

    pause = new Button(SCREEN_WIDTH - 70, 18, PPause, {"pause_n", "pause_h", "pause_p"});
    m_GuiObjects.push_back(pause);

    std::cerr << "Play Initialized!" << std::endl;
}

void Play::Exit()
{
    for(auto object : m_GameObjects){
        object->Clean();
        delete object;
        object = nullptr;
    }
    for(auto object : m_GuiObjects){
        object->Clean();
        delete object;
        object = nullptr;
    }

    m_GameObjects.clear();
    //m_GameObjects.shrink_to_fit();
    m_GuiObjects.clear();
    //m_GuiObjects.shrink_to_fit();
    std::cerr << "Exit Play!" << std::endl;
}

void Play::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 0, 255, 255, 255);
    SDL_RenderClear(m_Ctxt);

    TextureManager::GetInstance()->DrawBackground("bg1", 960, 640, 0.2);
    TextureManager::GetInstance()->Draw("tutorial", 100, (SCREEN_HEIGHT - 128) / 2 - 150, 300, 300, 1);

    m_LevelMap1->Render(s_MapPos);
    m_LevelMap2->Render(s_MapPos + SCREEN_WIDTH);

    for(int i = 0; i < m_GameObjects.size(); i++)
        m_GameObjects[i]->Draw();

    for(int i = 0; i < m_GuiObjects.size(); i++)
        m_GuiObjects[i]->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Play::Update()
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
    for(int i = 0; i < m_GuiObjects.size(); i++)
        m_GuiObjects[i]->Update(0);

    Camera::GetInstance()->Update(0);
    if(player->PlayerDead())
        Engine::GetInstance()->ChangeState(Menu::GetInstance());
}

void Play::HandleEvents()
{
    player->HandleEvent();
}

void Play::Pause()
{
    std::cout << "Play Pause!" << std::endl;
}

void Play::Resume()
{
    std::cout << "Play Resume!" << std::endl;
}

void Play::PPause()
{
    std::cout << "Play Pause!" << std::endl;
}

