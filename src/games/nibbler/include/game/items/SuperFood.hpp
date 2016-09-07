//
// SuperFood.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/games/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 18 20:49:32 2016 stephane galibert
// Last update Sat Apr  2 22:34:52 2016 stephane galibert
//

#ifndef _SUPERFOOD_HPP_
# define _SUPERFOOD_HPP_

# include <vector>

# include "Drawable.hpp"
# include "IItems.hpp"
# include "AddScore.hpp"

namespace arcade
{
  class SuperFood : public IItems
  {
  public:
    SuperFood(Vector2u const& pos, Drawable const * texture);
    virtual ~SuperFood(void);
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

#endif /* !_SUPERFOOD_HPP_ */
