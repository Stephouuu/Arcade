//
// Pinky.hpp for arca in /home/galibe_s/rendu/cpp_arcade/src/games/pacman/include/game/ghost
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 26 13:33:29 2016 stephane galibert
// Last update Mon Mar 28 21:07:05 2016 stephane galibert
//

#ifndef _PINKY_HPP_
# define _PINKY_HPP_

# include <string>
# include <iostream>
# include <functional>
# include <map>
# include <vector>

# include "Drawable.hpp"
# include "Utility.hpp"
# include "Map.hpp"
# include "FileCache.hpp"
# include "Generator.hpp"

# include "Ghost.hpp"
# include "AStar.hpp"

namespace arcade
{
  class Pinky : public Ghost
  {
  public:
    Pinky(void);
    virtual ~Pinky(void);
    virtual void init(Vector2u const& start);
    virtual bool refresh(Map &map, float const delta, Player &player);
    virtual Drawable const* getTexture(Vector2u const& pos) const;
    virtual Vector2u const& getPositions(void) const;
  private:
    void randomPath(Map &map);
    void computeDirection(Map &map, Player &dest);
    Vector2u findPath(Map &map, Vector2u const& dest) const;
    Direction deduceDirection(Vector2u const& path) const;
    void play_normal(Map &map, Player &player);
    void play_afraid(Map &map);
    void play_ghost(Map &map);
    Vector2u getDest(Map &map, Player const& player);
    std::map<Direction, std::function<bool(Map &)> > _move;
    bool up(Map &map);
    bool down(Map &map);
    bool left(Map &map);
    bool right(Map &map);
  };
}

#endif /* !_PINKY_HPP_ */
