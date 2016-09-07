//
// IItems.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 18 18:06:49 2016 stephane galibert
// Last update Mon Mar 28 22:27:38 2016 stephane galibert
//

#ifndef _IITEMS_HPP_
# define _IITEMS_HPP_

# include <list>

# include "FileCache.hpp"
# include "Utility.hpp"
# include "Player.hpp"
# include "Map.hpp"
# include "Drawable.hpp"
# include "Ghost.hpp"

namespace arcade
{
  class IItems
  {
  public:
    static const size_t DELAY_ANIMATION = 100;
  public:
    virtual ~IItems(void) {}
    virtual void affectPlayer(Player &player, std::vector<arcade::Ghost *> &ghosts,
			      Map &map) = 0;
    virtual void update(float const delta) = 0;
    virtual void addFrame(Drawable const *frame) = 0;
    virtual Vector2u const& getPos(void) const = 0;
    virtual Drawable const * getCurrentFrame(void) const = 0;
  };
}

#endif /* !_IITEMS_HPP_ */
