//
// Ghost.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 26 10:12:22 2016 stephane galibert
// Last update Mon Mar 28 20:52:27 2016 stephane galibert
//

#ifndef _GHOST_HPP_
# define _GHOST_HPP_

# include <iostream>
# include <string>
# include <functional>
# include <map>
# include <vector>

# include "Drawable.hpp"
# include "Utility.hpp"
# include "Map.hpp"
# include "FileCache.hpp"
# include "Player.hpp"
# include "Generator.hpp"

namespace arcade
{
  class Ghost
  {
  public:
    static const int REFRESH_SLOW = 300;
    static const int REFRESH_DELAY_MS = 150;
    Ghost(void);
    virtual ~Ghost(void);
    virtual void init(Vector2u const& start) = 0;
    virtual bool refresh(Map &map, float const delta, Player &player) = 0;
    virtual Drawable const* getTexture(Vector2u const& pos) const = 0;
    virtual Vector2u const& getPositions(void) const = 0;
    void setAfraid(bool const value);
    bool isAfraid(void) const;
    bool isAlive(void) const;
    void setAlive(bool const value);
    bool hasStarted(void) const;
    void setStart(bool const value);
  protected:
    std::vector<Drawable *> _textures;
    Drawable *_textureGhost;
    Drawable *_textureAfraid;
    Direction _dirCurrent;
    float _delta;
    bool _alive;
    bool _afraid;
    size_t _speed;
    Vector2u _spawn;
    Vector2u _pos;
    TileType _previous;
    bool _hasReachedRandom;
    Vector2u _random;
    Generator _generator;
    float _delta_afraid;
    bool _start;
  };
}

#endif /* !_GHOST_HPP_ */
