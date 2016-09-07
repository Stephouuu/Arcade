//
// Bonus.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Sun Mar 20 23:26:57 2016 stephane galibert
// Last update Sun Mar 20 23:39:42 2016 stephane galibert
//

#ifndef _IBONUS_HPP_
# define _IBONUS_HPP_

# include "Drawable.hpp"

namespace arcade
{
  class IBonus
  {
  public:
    virtual ~IBonus(void) {}
    virtual void update(float const delta) = 0;
    virtual bool isFinish(void) const = 0;
    virtual Drawable const& getCurrentDrawable(void) const = 0;
  };
}

#endif /* !_BONUS_HPP_ */
