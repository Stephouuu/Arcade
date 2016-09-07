//
// PowerUp.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 11 16:27:25 2016 stephane galibert
// Last update Thu Mar 31 22:24:04 2016 stephane galibert
//

#ifndef _POWERUP_HPP_
# define _POWERUP_HPP_

# include <string>
# include <iostream>
# include <list>
# include <vector>

# include "Block.hpp"
# include "Player.hpp"
# include "Utility.hpp"
# include "Map.hpp"
# include "Protocol.hpp"
# include "FileCache.hpp"
# include "IItems.hpp"
# include "PacGum.hpp"

namespace arcade
{
  class PowerUp : public Block
  {
  public:
    PowerUp(void);
    virtual ~PowerUp(void);
    virtual void refresh(float const delta, Map &map);
    virtual void loadTexture(void);
    virtual Drawable const* getTexture(Vector2u const& pos) const;
    virtual void checkCollisions(Player& player, std::vector<Ghost *> &ghosts,
				 Map &map);
    virtual bool add(IItems *item);
  private:
    std::list<IItems *> _items;
    std::vector<Drawable *> _texture;
  };
}

#endif /* !_POWERUP_HPP_ */
