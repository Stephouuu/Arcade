//
// CMDWhereAmI.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 19:54:55 2016 stephane galibert
// Last update Thu Mar 17 22:15:46 2016 stephane galibert
//

#include "CMDWhereAmI.hpp"

arcade::CMDWhereAmI::CMDWhereAmI(void)
{
  
}

arcade::CMDWhereAmI::~CMDWhereAmI(void)
{

}

void arcade::CMDWhereAmI::compute(arcade::IGames& game)
{
  std::cerr << "where am i" << std::endl;
  WhereAmI *where;
  std::list<Vector2u> const& playerPos = game.getPlayerPosition();
  size_t posSize = playerPos.size() * sizeof(Position);
  where = (WhereAmI *)malloc(sizeof(WhereAmI) + posSize);
  where->type = CommandType::WHERE_AM_I;
  where->lenght = playerPos.size();
  size_t i = 0;
  for (auto &it : playerPos)
    {
      Position pos;
      pos.x = it.x;
      pos.y = it.y;
      where->position[i] = pos;
      i++;
    }
  write(1, where, sizeof(WhereAmI) + posSize);
}
