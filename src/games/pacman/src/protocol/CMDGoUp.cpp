//
// CMDGoUp.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:42:06 2016 stephane galibert
// Last update Thu Mar 17 22:15:13 2016 stephane galibert
//

#include "CMDGoUp.hpp"

arcade::CMDGoUp::CMDGoUp(void)
{
  
}

arcade::CMDGoUp::~CMDGoUp(void)
{

}

void arcade::CMDGoUp::compute(arcade::IGames& game)
{
  std::cerr << "go up" << std::endl;
  game.goUp();
}
