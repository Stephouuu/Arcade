//
// CMDGoForward.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:56:00 2016 stephane galibert
// Last update Thu Mar 17 22:14:44 2016 stephane galibert
//

#include "CMDGoForward.hpp"

arcade::CMDGoForward::CMDGoForward(void)
{
  
}

arcade::CMDGoForward::~CMDGoForward(void)
{

}

void arcade::CMDGoForward::compute(arcade::IGames& game)
{
  std::cerr << "go forward" << std::endl;
  game.goForward();
}
