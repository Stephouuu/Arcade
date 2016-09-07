//
// CMDIllegal.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:57:26 2016 stephane galibert
// Last update Thu Mar 17 22:15:22 2016 stephane galibert
//

#include "CMDIllegal.hpp"

arcade::CMDIllegal::CMDIllegal(void)
{
  
}

arcade::CMDIllegal::~CMDIllegal(void)
{

}

void arcade::CMDIllegal::compute(arcade::IGames& game)
{
  std::cerr << "illegal" << std::endl;
  (void)game;
}
