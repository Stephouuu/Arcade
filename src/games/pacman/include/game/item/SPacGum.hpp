//
// SPacGum.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman/include/game/item
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 24 15:27:47 2016 stephane galibert
// Last update Sun Mar 27 21:15:09 2016 stephane galibert
//

#ifndef _SPACGUM_HPP_
# define _SPACGUM_HPP_

# include <vector>

# include "IItems.hpp"
# include "BSPacGum.hpp"
# include "Ghost.hpp"

namespace arcade
{
  class SPacGum : public IItems
  {
  public:
    SPacGum(Vector2u const& pos);
    virtual ~SPacGum(void);
    virtual void affectPlayer(Player &player, std::vector<arcade::Ghost *> &ghosts,
			      Map &map);
    virtual void update(float const delta);
    virtual void addFrame(Drawable const *frame);
    virtual Vector2u const& getPos(void) const;
    virtual Drawable const * getCurrentFrame(void) const;
  private:
    std::vector<Drawable const *> _frames;
    size_t _currentFrame;
    Vector2u _pos;
    float _delta;
  };
}

#endif /* !_SPACGUM_HPP_ */
