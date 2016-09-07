//
// CMDGoRight.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:44:46 2016 stephane galibert
// Last update Thu Mar 17 22:15:02 2016 stephane galibert
//

#include "CMDGoRight.hpp"

arcade::CMDGoRight::CMDGoRight(void)
{
  
}

arcade::CMDGoRight::~CMDGoRight(void)
{

}

void arcade::CMDGoRight::compute(arcade::IGames& game)
{
  std::cerr << "go left" << std::endl;
  game.goRight();
}
