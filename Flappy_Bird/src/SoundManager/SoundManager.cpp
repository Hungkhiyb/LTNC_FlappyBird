#include "SoundManager.h"

SoundManager* SoundManager::s_Instance = nullptr;

SoundManager::SoundManager()
{
    if(Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE) < 0)
        std::cerr << Mix_GetError() << std::endl;
}

SoundManager::~SoundManager()
{
    delete s_Instance;
}

bool SoundManager::ParseSound(std::string source)
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()){
        if(e->Value() == std::string("effect")){
            LoadEffect(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
        if(e->Value() == std::string("music")){
            LoadMusic(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
    }

    std::cout << source << " Parse!" << std::endl;
    return true;
}

void SoundManager::PlayMusic(std::string id)
{
    if(Mix_PlayMusic(m_MusicMap[id], -1) == -1)
        std::cerr << Mix_GetError() << ": " << id << std::endl;
}

void SoundManager::PauseMusic()
{
    Mix_PauseMusic();
}

void SoundManager::LoadMusic(std::string id, std::string source)
{
    Mix_Music* music = Mix_LoadMUS(source.c_str());
    if(music != nullptr)
        m_MusicMap[id] = music;
    else
        std::cerr << Mix_GetError() << ": " << source << std::endl;
}

void SoundManager::PlayEffect(std::string id)
{
    if(Mix_PlayChannel(-1, m_EffectMap[id], 0) == -1)
        std::cerr << Mix_GetError() << ": " << id << std::endl;
}

void SoundManager::LoadEffect(std::string id, std::string source)
{
    Mix_Chunk* effect = Mix_LoadWAV(source.c_str());
    if(effect != nullptr)
        m_EffectMap[id] = effect;

    else
        std::cerr << Mix_GetError() << ": " << source << std::endl;
}

void SoundManager::Clean()
{
    for(auto music : m_MusicMap)
        Mix_FreeMusic(music.second);
    for(auto effect : m_EffectMap)
        Mix_FreeChunk(effect.second);

    m_MusicMap.clear();
    m_EffectMap.clear();
    std::cout << "Sound system cleaned!" << std::endl;
}
