//
// CMDShoot.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:56:40 2016 stephane galibert
// Last update Thu Mar 17 22:15:39 2016 stephane galibert
//

#include "CMDShoot.hpp"

arcade::CMDShoot::CMDShoot(void)
{
  
}

arcade::CMDShoot::~CMDShoot(void)
{

}

void arcade::CMDShoot::compute(arcade::IGames& game)
{
  std::cerr << "shoot" << std::endl;
  game.shoot();
}
