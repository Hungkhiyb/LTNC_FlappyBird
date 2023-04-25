#include "Play.h"

Play* Play::s_Instance = nullptr;
Bird* player = nullptr;

void Play::Init()
{
    Camera::GetInstance()->Init();
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    m_LevelMap1 = MapParser::GetInstance()->GetMap("level0");
    m_LevelMap2 = MapParser::GetInstance()->GetRandomMap();

    player = new Bird(new Properties("bird", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 64 * 2, 32, 32));
    m_GameObjects.push_back(player);
    Camera::GetInstance()->setTarget(player->GetOrigin());

    Button* pause = new Button(SCREEN_WIDTH - 70, 18, PPause, {"pause_n", "pause_h", "pause_p"});
    Button* resume = new Button(480, 350, RResume, {"resume_n", "resume_h", "resume_p"});
    Button* home = new Button(550, 350, Home, {"home_n", "home_h", "home_p"});
    Button* restart = new Button(620, 350, Restart, {"restart_n", "restart_h", "restart_p"});
    m_GuiObjects.push_back(pause);
    m_GuiObjects.push_back(resume);
    m_GuiObjects.push_back(home);
    m_GuiObjects.push_back(restart);

    CollisionHandler::GetInstance()->Init();
    SoundManager::GetInstance()->PlayMusic("themeMusic");

    s_MapPos = 0;
    s_CollisionPos = 0;
    m_Pause = false;
    m_Menu = false;
    m_GameOver = false;
    tmpPoint = 0;

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
    m_GameObjects.shrink_to_fit();
    m_GuiObjects.clear();
    m_GuiObjects.shrink_to_fit();

    std::cerr << "Exit Play!" << std::endl;
}

std::string Play::GetPoint(int point)
{
    int tmp = point;
    std::string str_point = "";
    if(tmp == 0)
        str_point = "0";
    while(tmp != 0){
        str_point = char(tmp % 10 + '0') + str_point;
        tmp /= 10;
    }
    return str_point;
}

void Play::Render()
{
    SDL_SetRenderDrawColor(m_Ctxt, 0, 255, 255, 255);
    SDL_RenderClear(m_Ctxt);

    TextureManager::GetInstance()->DrawBackground("bg1");
    TextureManager::GetInstance()->Draw("tutorial", 100, (SCREEN_HEIGHT - 128) / 2 - 150, 1);

    m_LevelMap1->Render(s_MapPos);
    m_LevelMap2->Render(s_MapPos + SCREEN_WIDTH);

    for(int i = 0; i < m_GameObjects.size(); i++)
        m_GameObjects[i]->Draw();

    SDL_Color textColor = {255, 255, 255};

    if(!m_Pause){
        TextureManager::GetInstance()->DrawTextCenter("assets/Fonts/FontPoint.ttf", GetPoint(player->GetPoint()), 70, textColor, SCREEN_WIDTH / 2, 30);
    }

    for(int i = 0; i < 1; i++)
        m_GuiObjects[i]->Draw();

    if(player->PlayerDead()){
        TextureManager::GetInstance()->DrawCenterX("gameover_tile", 100, 4);
        TextureManager::GetInstance()->DrawCenter("gameover", 4);
        for(int i = 2; i < 4; i++)
            m_GuiObjects[i]->Draw();
        if(tmpPoint > player->GetPoint())
            tmpPoint = player->GetPoint();
        TextureManager::GetInstance()->DrawTextCenter("assets/Fonts/FontPoint.ttf", GetPoint(tmpPoint), 70, textColor, 620, 280);
        if(player->GetPoint() >= 10 && tmpPoint == player->GetPoint())
            TextureManager::GetInstance()->Draw("coper", 310, 290, 0, 4);
        if(player->GetPoint() >= 20 && tmpPoint == player->GetPoint())
            TextureManager::GetInstance()->Draw("silver", 310, 290, 0, 4);
        if(player->GetPoint() >= 30 && tmpPoint == player->GetPoint())
            TextureManager::GetInstance()->Draw("gold", 310, 290, 0, 4);
        if(player->GetPoint() >= 40 && tmpPoint == player->GetPoint())
            TextureManager::GetInstance()->Draw("platinum", 310, 290, 0, 4);
        SDL_Delay(20);
        tmpPoint++;
    }
    else if(m_Pause){
        TextureManager::GetInstance()->DrawCenter("pause");
        for(int i = 1; i < 4; i++)
            m_GuiObjects[i]->Draw();
        TextureManager::GetInstance()->DrawTextCenter("assets/Fonts/FontPoint.ttf", GetPoint(player->GetPoint()), 70, textColor, 370, 280);
    }

    SDL_RenderPresent(m_Ctxt);
}

void Play::Update()
{
    if(player->PlayerDead()){
        for(int i = 2; i < 4; i++)
            m_GuiObjects[i]->Update();
        if(m_Menu)
            Engine::GetInstance()->ChangeState(Menu::GetInstance());
    }
    else if(m_Pause){
        for(int i = 1; i < 4; i++)
            m_GuiObjects[i]->Update();
        if(m_Menu)
            Engine::GetInstance()->ChangeState(Menu::GetInstance());
    }
    else if(!m_Pause){
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
            m_GameObjects[i]->Update();
        for(int i = 0; i < 1; i++)
            m_GuiObjects[i]->Update();

        Camera::GetInstance()->Update();
        if(player->PlayerDead()){
            s_Instance->Pause();
            SoundManager::GetInstance()->PauseMusic();
            SoundManager::GetInstance()->PlayEffect("end");
            SoundManager::GetInstance()->PlayEffect("dead");
        }
    }
}

void Play::HandleEvents()
{
    if(!m_Pause)
        player->HandleEvent();
}

void Play::Pause()
{
    m_Pause = true;

    std::cout << "Play Pause!" << std::endl;
}

void Play::Resume()
{
    m_Pause = false;

    std::cout << "Play Resume!" << std::endl;
}

void Play::Menu()
{
    m_Menu = true;

    std::cout << "Menu Open!" << std::endl;
}

void Play::PPause()
{
    s_Instance->Pause();
}

void Play::RResume()
{
    s_Instance->Resume();
}

void Play::Home()
{
    s_Instance->Menu();
}

void Play::Restart()
{
    Engine::GetInstance()->ChangeState(Play::GetInstance());

    std::cout << "Restart Game!" << std::endl;
}


