//
// BSPacGum.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman/include/game/bonus
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Mar 27 18:17:27 2016 stephane galibert
// Last update Mon Mar 28 20:44:51 2016 stephane galibert
//

#ifndef _BSPACGUM_HPP_
# define _BSPACGUM_HPP_

# include <vector>

# include "IBonus.hpp"
# include "Player.hpp"
# include "Ghost.hpp"

namespace arcade
{
  class BSPacGum : public IBonus
  {
  public:
    BSPacGum(Player &player, std::vector<Ghost *> &ghosts);
    virtual ~BSPacGum(void);
    virtual void update(float const delta);
    virtual bool isFinish(void) const;
    virtual Drawable const& getCurrentDrawable(void) const;
  private:
    size_t const _duration;
    size_t const _duration_text;
    Vector2u _pos;
    Player &_player;
    std::vector<Ghost *> &_ghosts;
    float _delta;
    float _delta_text;
    Drawable _text;
    size_t _scoreCoef;
  };
}

#endif /* !_BSPEED_HPP_ */
