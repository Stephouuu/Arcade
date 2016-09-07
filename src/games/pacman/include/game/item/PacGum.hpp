//
// PacGum.hpp for arcade in /home/galibe_s/rendu/cpp_arcadeold/include/games/pacman/item
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 24 10:12:55 2016 stephane galibert
// Last update Sun Mar 27 21:16:29 2016 stephane galibert
//

#ifndef _PACGUM_HPP_
# define _PACGUM_HPP_

# include <vector>

# include "IItems.hpp"
# include "Ghost.hpp"

namespace arcade
{
  class PacGum : public IItems
  {
  public:
    PacGum(Vector2u const& pos);
    virtual ~PacGum(void);
    virtual void affectPlayer(Player &player, std::vector<Ghost *> &ghosts,
			      Map &map);
    virtual void update(float const delta);
    virtual void addFrame(Drawable const * frame);
    virtual Vector2u const& getPos(void) const;
    virtual Drawable const * getCurrentFrame(void) const;
  private:
    std::vector<Drawable const *> _frames;
    size_t _currentFrame;
    Vector2u _pos;
    float _delta;
  };
}

#endif /* !_PACGUM_HPP_ */
