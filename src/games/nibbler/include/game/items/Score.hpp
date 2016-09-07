//
// Score.hpp for arcadde in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Mar 21 11:11:30 2016 stephane galibert
// Last update Sat Apr  2 22:34:32 2016 stephane galibert
//

#ifndef _SCORE_HPP_
# define _SCORE_HPP_

# include <vector>

# include "IItems.hpp"
# include "ScoreMultiplier.hpp"

namespace arcade
{
  class Score : public IItems
  {
  public:
    Score(Vector2u const& pos);
    virtual ~Score(void);
    virtual void affectPlayer(Player &player, Map &map);
    virtual void update(float const delta);
    virtual void addFrame(Drawable const *frame);
    virtual Vector2u const& getPos(void) const;
    virtual Drawable const * getCurrentFrame(void) const;
  private:
    std::vector<Drawable const *> _frames;
    size_t _currentFrame;
    Vector2u _pos;
    float _delta;
  };
}

#endif /* !_SCORE_HPP_ */
