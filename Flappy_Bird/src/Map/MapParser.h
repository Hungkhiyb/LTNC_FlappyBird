#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>

#include "GameMap.h"
#include "TileLayer.h"
#include "tinyxml.h"

struct Tileset;
class TileLayer;

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class MapParser
{
    public:
        bool ParseFileMap(std::string source);
        void Clean();

        inline GameMap* GetMap(std::string id) { return m_MapDict[id];}
        GameMap* GetRandomMap();
        inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

    private:
        MapParser(){}
        ~MapParser(){ delete s_Instance; }
        static MapParser* s_Instance;
        std::map<std::string, GameMap*> m_MapDict;

    private:
        bool Load(std::string id, std::string source);
        bool Parse(std::string id, std::string source);

        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

};

#endif // MAPPARSER_H
