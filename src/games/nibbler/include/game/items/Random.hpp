//
// Random.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 19 23:24:39 2016 stephane galibert
// Last update Sat Apr  2 22:34:23 2016 stephane galibert
//

#ifndef _RANDOM_HPP_
# define _RANDOM_HPP_

# include <vector>

# include "Drawable.hpp"
# include "IItems.hpp"
# include "Generator.hpp"
# include "AddScore.hpp"

namespace arcade
{
  class Random : public IItems
  {
  public:
    Random(Vector2u const& pos, Drawable const * dest);
    virtual ~Random(void);
    virtual void affectPlayer(Player &player, Map &map);
    virtual void update(float const delta);
    virtual void addFrame(Drawable const *frame);
    virtual Vector2u const& getPos(void) const;
    virtual Drawable const * getCurrentFrame(void) const;
  private:
    Drawable const * _textureDest;
    std::vector<Drawable const *> _frames;
    size_t _currentFrame;
    Vector2u _pos;
    Generator _generator;
    float _delta;
  };
}

#endif /* !_SUPERFOOD_HPP_ */
