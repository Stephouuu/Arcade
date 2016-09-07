//
// Block.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 11 16:30:01 2016 stephane galibert
// Last update Sat Apr  2 22:33:22 2016 stephane galibert
//

#ifndef _BLOCK_HPP_
# define _BLOCK_HPP_

# include "Drawable.hpp"
# include "Player.hpp"
# include "FileCache.hpp"
# include "Map.hpp"
# include "Utility.hpp"

namespace arcade
{
  class Block
  {
  public:
    virtual ~Block(void) {}
    virtual void refresh(float const delta, Map &map) = 0;
    virtual void loadTexture(void) = 0;
    virtual Drawable const* getTexture(Vector2u const& pos) const = 0;
    virtual void checkCollisions(Player& player, Map &map) = 0;
  };
}

#endif /* !_BLOCK_HPP_ */
