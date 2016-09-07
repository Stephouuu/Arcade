//
// AddScore.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/games/nibbler/bonus
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Mon Mar 21 02:16:54 2016 stephane galibert
// Last update Mon Mar 21 02:30:24 2016 stephane galibert
//

#ifndef _ADDSCORE_HPP_
# define _ADDSCORE_HPP_

# include "IBonus.hpp"
# include "Utility.hpp"

namespace arcade
{
  class AddScore : public IBonus
  {
  public:
    AddScore(Vector2u const& pos, size_t const score);
    virtual ~AddScore(void);
    virtual void update(float const delta);
    virtual bool isFinish(void) const;
    virtual Drawable const& getCurrentDrawable(void) const;
  private:
    size_t const _duration;
    float _delta_text;
    Drawable _text;
    Vector2u _pos;
  };
}

#endif /* !_ADDSCORE_HPP_ */
