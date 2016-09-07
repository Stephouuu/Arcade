//
// CMDGetMap.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 19:36:40 2016 stephane galibert
// Last update Mon Mar 21 12:24:21 2016 stephane galibert
//

#include "CMDGetMap.hpp"

arcade::CMDGetMap::CMDGetMap(void)
{
  
}

arcade::CMDGetMap::~CMDGetMap(void)
{

}

void arcade::CMDGetMap::compute(arcade::IGames& game)
{
  std::cerr << "get map" << std::endl;
  GetMap *getmap;
  Map const& map = game.getMap();
  size_t mapSize = sizeof(TileType) * map.height * map.width;
  getmap = (GetMap *)malloc(sizeof(GetMap) + mapSize);
  getmap->type = CommandType::GET_MAP;
  getmap->width = map.width;
  getmap->height = map.height;
  for (size_t i = 0 ; i < map.height ; ++i)
    for (size_t j = 0 ; j < map.width ; ++j)
      getmap->tile[j * map.width + i] = map.map[i][j];
  write(1, getmap, sizeof(GetMap) + mapSize);
  free(getmap);
}
