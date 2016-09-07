//
// CMDGoDown.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:43:01 2016 stephane galibert
// Last update Thu Mar 17 22:14:34 2016 stephane galibert
//

#include "CMDGoDown.hpp"

arcade::CMDGoDown::CMDGoDown(void)
{
  
}

arcade::CMDGoDown::~CMDGoDown(void)
{

}

void arcade::CMDGoDown::compute(arcade::IGames& game)
{
  std::cerr << "go down" << std::endl;
  game.goDown();
}
