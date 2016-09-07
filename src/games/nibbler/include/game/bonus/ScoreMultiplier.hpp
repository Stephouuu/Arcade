//
// ScoreMultiplier.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Mon Mar 21 10:27:36 2016 stephane galibert
// Last update Mon Mar 21 10:29:19 2016 stephane galibert
//

#ifndef _SCOREMULTIPLIER_HPP_
# define _SCOREMULTIPLIER_HPP_

# include "IBonus.hpp"
# include "Player.hpp"

namespace arcade
{
  class ScoreMultiplier : public IBonus
  {
  public:
    ScoreMultiplier(Player &player);
    virtual ~ScoreMultiplier(void);
    virtual void update(float const delta);
    virtual bool isFinish(void) const;
    virtual Drawable const& getCurrentDrawable(void) const;
  private:
    size_t const _duration;
    Vector2u _pos;
    Player &_player;
    float _delta;
    float _delta_text;
    Drawable _text;
  };
}

#endif /* !_SCOREMULTIPLIER_HPP_ */
