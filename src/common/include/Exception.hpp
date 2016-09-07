//
// Exception.hpp for nibbler in /home/galibe_s/github/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Jun 25 14:34:51 2015 stephane galibert
// Last update Fri Apr  1 14:54:01 2016 stephane galibert
//

#ifndef _EXCEPTION_HPP_
# define _EXCEPTION_HPP_

# include <iostream>
# include <string>
# include <exception>

namespace arcade
{
  class ArcadeError : public std::exception
  {
  public:
    ArcadeError(std::string const& message) throw();
    virtual ~ArcadeError(void) throw();

    virtual const char *what(void) const throw();
  private:
    std::string _message;
  };

  class LDError : public ArcadeError
  {
  public:
    LDError(std::string const& msg) throw();
    virtual ~LDError(void) throw();
  };

  class BadSym : public LDError
  {
  public:
    BadSym(std::string const& name) throw();
    virtual ~BadSym(void) throw();
  };

  class UnLoaded : public LDError
  {
  public:
    UnLoaded(std::string const& name) throw();
    virtual ~UnLoaded(void) throw();
  };

  class GameError : public ArcadeError
  {
  public:
    GameError(std::string const& msg) throw();
    virtual ~GameError(void) throw();
  };

  class FileError : public GameError
  {
  public:
    FileError(std::string const& name) throw();
    virtual ~FileError(void) throw();
  };

  class MapError : public GameError
  {
  public:
    MapError(std::string const& msg) throw();
    virtual ~MapError(void) throw();
  };

  class ElemNotFound : public GameError
  {
  public:
    ElemNotFound(std::string const& msg) throw();
    virtual ~ElemNotFound(void) throw();
  };
}

#endif /* !_EXCEPTION_HPP_ */
