//
// Speed.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Mar 20 08:26:05 2016 stephane galibert
// Last update Sat Apr  2 22:34:42 2016 stephane galibert
//

#ifndef _SPEED_HPP_
# define _SPEED_HPP_

# include <vector>

# include "IItems.hpp"
# include "BSpeed.hpp"

namespace arcade
{
  class Speed : public IItems
  {
  public:
    Speed(Vector2u const& pos);
    virtual ~Speed(void);
    virtual void affectPlayer(Player &player, Map &map);
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

#endif /* !_SPEED_HPP_ */
