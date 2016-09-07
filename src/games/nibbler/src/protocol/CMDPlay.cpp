//
 // CMDPlay.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:58:13 2016 stephane galibert
// Last update Thu Mar 17 22:23:07 2016 stephane galibert
//

#include "CMDPlay.hpp"

arcade::CMDPlay::CMDPlay(void)
{
  
}

arcade::CMDPlay::~CMDPlay(void)
{

}

void arcade::CMDPlay::compute(arcade::IGames& game)
{
  std::cerr << "play" << std::endl;
  game.play();
}
