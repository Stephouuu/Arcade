//
// CMDBuilder.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 19:36:04 2016 stephane galibert
// Last update Thu Mar 17 21:02:58 2016 stephane galibert
//

#include "CMDBuilder.hpp"

arcade::CMDBuilder::CMDBuilder(void)
{
  _builder[CommandType::GET_MAP] = std::bind(&arcade::CMDBuilder::create_GetMap, this);
  _builder[CommandType::WHERE_AM_I] = std::bind(&arcade::CMDBuilder::create_WhereAmI, this);
  _builder[CommandType::GO_UP] = std::bind(&arcade::CMDBuilder::create_GoUp, this);
  _builder[CommandType::GO_DOWN] = std::bind(&arcade::CMDBuilder::create_GoDown, this);
  _builder[CommandType::GO_LEFT] = std::bind(&arcade::CMDBuilder::create_GoLeft, this);
  _builder[CommandType::GO_RIGHT] = std::bind(&arcade::CMDBuilder::create_GoRight, this);
  _builder[CommandType::GO_FORWARD] = std::bind(&arcade::CMDBuilder::create_GoForward, this);
  _builder[CommandType::SHOOT] = std::bind(&arcade::CMDBuilder::create_Shoot, this);
  _builder[CommandType::ILLEGAL] = std::bind(&arcade::CMDBuilder::create_Illegal, this);
  _builder[CommandType::PLAY] = std::bind(&arcade::CMDBuilder::create_Play, this);
}

arcade::CMDBuilder::~CMDBuilder(void)
{
  
}

arcade::ICommand *arcade::CMDBuilder::create(arcade::CommandType const type) const
{
  if (_builder.find(type) != _builder.end())
    return (_builder.at(type)());
  return (NULL);
}

arcade::ICommand *arcade::CMDBuilder::create_GetMap(void) const
{
  return (new CMDGetMap);
}

arcade::ICommand *arcade::CMDBuilder::create_WhereAmI(void) const
{
  return (new CMDWhereAmI);
}

arcade::ICommand *arcade::CMDBuilder::create_GoUp(void) const
{
  return (new CMDGoUp);
}

arcade::ICommand *arcade::CMDBuilder::create_GoDown(void) const
{
  return (new CMDGoDown);
}

arcade::ICommand *arcade::CMDBuilder::create_GoLeft(void) const
{
  return (new CMDGoLeft);
}

arcade::ICommand *arcade::CMDBuilder::create_GoRight(void) const
{
  return (new CMDGoRight);
}

arcade::ICommand *arcade::CMDBuilder::create_GoForward(void) const
{
  return (new CMDGoForward);
}

arcade::ICommand *arcade::CMDBuilder::create_Shoot(void) const
{
  return (new CMDShoot);
}

arcade::ICommand *arcade::CMDBuilder::create_Illegal(void) const
{
  return (new CMDIllegal);
}

arcade::ICommand *arcade::CMDBuilder::create_Play(void) const
{
  return (new CMDPlay);
}
