//
// Exception.cpp for nibbler in /home/galibe_s/github/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Jun 25 14:34:49 2015 stephane galibert
// Last update Fri Apr  1 14:54:18 2016 stephane galibert
//

#include "Exception.hpp"

arcade::ArcadeError::ArcadeError(std::string const& message) throw()
{
  this->_message = message;
}

arcade::ArcadeError::~ArcadeError(void) throw()
{

}

const char *arcade::ArcadeError::what(void) const throw()
{
  std::string message;

  message = this->_message;
  return (message.data());
}

arcade::LDError::LDError(std::string const& name) throw()
  : arcade::ArcadeError::ArcadeError(name)
{

}

arcade::LDError::~LDError(void) throw()
{

}

arcade::BadSym::BadSym(std::string const& name) throw()
  : arcade::LDError::LDError(name)
{

}

arcade::BadSym::~BadSym(void) throw()
{

}

arcade::UnLoaded::UnLoaded(std::string const& name) throw()
  : arcade::LDError::LDError(name)
{

}

arcade::UnLoaded::~UnLoaded(void) throw()
{

}

arcade::GameError::GameError(std::string const& name) throw()
  : arcade::ArcadeError::ArcadeError(name)
{

}

arcade::GameError::~GameError(void) throw()
{

}

arcade::FileError::FileError(std::string const& name) throw()
  : arcade::GameError::GameError(name)
{

}

arcade::FileError::~FileError(void) throw()
{

}

arcade::MapError::MapError(std::string const& msg) throw()
  : arcade::GameError::GameError(msg)
{

}

arcade::MapError::~MapError(void) throw()
{

}


arcade::ElemNotFound::ElemNotFound(std::string const& msg) throw()
  : arcade::GameError::GameError(msg)
{

}

arcade::ElemNotFound::~ElemNotFound(void) throw()
{

}
