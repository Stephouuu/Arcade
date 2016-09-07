//
// BSpeed.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/games/nibbler/bonus
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Sun Mar 20 23:41:29 2016 stephane galibert
// Last update Mon Mar 21 12:49:11 2016 stephane galibert
//

#ifndef _BSPEED_HPP_
# define _BSPEED_HPP_

# include "IBonus.hpp"
# include "Player.hpp"

namespace arcade
{
  class BSpeed : public IBonus
  {
  public:
    BSpeed(Player &player);
    virtual ~BSpeed(void);
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
    Drawable _progressBar;
    Drawable _progressText;
  };
}

#endif /* !_BSPEED_HPP_ */
