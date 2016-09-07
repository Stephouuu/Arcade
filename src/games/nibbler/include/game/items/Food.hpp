//
// Food.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 18 18:19:24 2016 stephane galibert
// Last update Sat Apr  2 22:34:05 2016 stephane galibert
//

#ifndef _FOOD_HPP_
# define _FOOD_HPP_

# include <vector>

# include "Drawable.hpp"
# include "IItems.hpp"
# include "AddScore.hpp"

namespace arcade
{
  class Food : public IItems
  {
  public:
    Food(Vector2u const& pos, Drawable const * texture);
    virtual ~Food(void);
    virtual void affectPlayer(Player &player, Map &map);
    virtual void update(float const delta);
    virtual void addFrame(Drawable const * frame);
    virtual Vector2u const& getPos(void) const;
    virtual Drawable const * getCurrentFrame(void) const;
  private:
    Drawable const * _textureDest;
    std::vector<Drawable const *> _frames;
    size_t _currentFrame;
    Vector2u _pos;
    float _delta;
  };
}

#endif /* !_FOOD_HPP_ */
