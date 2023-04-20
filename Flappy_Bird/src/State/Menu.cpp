#include "Menu.h"

Menu* Menu::s_Instance = nullptr;
int Menu::s_MapPos;

void Menu::Init()
{
    Camera::GetInstance()->Init();
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    Button* start = new Button(SCREEN_WIDTH / 2 - 90, 350, StartGame, {"start_n", "start_h", "start_p"});
    Button* settings = new Button(SCREEN_WIDTH / 2 - 90, 420, Settings, {"settings_n", "settings_h", "settings_p"});
    Button* quit = new Button(SCREEN_WIDTH / 2 - 90, 490, Quit, {"quit_n", "quit_h", "quit_p"});

    m_LevelMap = MapParser::GetInstance()->GetMap("level0");

    m_GuiObjects.push_back(start);
    m_GuiObjects.push_back(settings);
    m_GuiObjects.push_back(quit);

    s_MapPos = 0;
    std::cout << "Menu Initialized!" << std::endl;
}

void Menu::Exit()
{
    for(auto object : m_GuiObjects){
        object->Clean();
        delete object;
        object = nullptr;
    }

    m_GuiObjects.clear();
    m_GuiObjects.shrink_to_fit();
    std::cout << "exit menu!" << std::endl;
}

void Menu::Update()
{
    m_LevelMap->Update();

    for(int i = 0; i < m_GuiObjects.size(); i++)
        m_GuiObjects[i]->Update(0);
}

void Menu::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 0, 255, 255, 255);
    SDL_RenderClear(m_Ctxt);

    TextureManager::GetInstance()->DrawBackground("bg1");
    TextureManager::GetInstance()->DrawCenterX("tile", 100, 1.2);

    if(s_MapPos <= -SCREEN_WIDTH)
        s_MapPos = 0;
    s_MapPos--;
    m_LevelMap->Render(s_MapPos);
    m_LevelMap->Render(s_MapPos + SCREEN_WIDTH);

    for(int i = 0; i < m_GuiObjects.size(); i++)
        m_GuiObjects[i]->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Menu::HandleEvents()
{

}


void Menu::Pause()
{
    std::cout << "Menu Pause!" << std::endl;
}

void Menu::Resume()
{
    std::cout << "Menu Resume!" << std::endl;
}


void Menu::StartGame()
{
    Engine::GetInstance()->ChangeState(Play::GetInstance());

    std::cout << "Start Game!" << std::endl;
}

void Menu::Settings()
{
    std::cout << "Option Mode!" << std::endl;
}

void Menu::Quit()
{
    Engine::GetInstance()->Quit();

    std::cout << "Quit Game!" << std::endl;
}
