//
// CMDGoLeft.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:44:05 2016 stephane galibert
// Last update Thu Mar 17 22:14:53 2016 stephane galibert
//

#include "CMDGoLeft.hpp"

arcade::CMDGoLeft::CMDGoLeft(void)
{
  
}

arcade::CMDGoLeft::~CMDGoLeft(void)
{

}

void arcade::CMDGoLeft::compute(arcade::IGames& game)
{
  std::cerr << "go left" << std::endl;
  game.goLeft();
}
