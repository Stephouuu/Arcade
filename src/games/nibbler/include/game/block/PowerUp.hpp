//
// PowerUp.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 11 16:27:25 2016 stephane galibert
// Last update Sat Apr  2 22:33:30 2016 stephane galibert
//

#ifndef _POWERUP_HPP_
# define _POWERUP_HPP_

# include <string>
# include <iostream>
# include <list>
# include <vector>

# include "Drawable.hpp"
# include "Block.hpp"
# include "Player.hpp"
# include "Utility.hpp"
# include "Map.hpp"
# include "Generator.hpp"
# include "Protocol.hpp"
# include "FileCache.hpp"
# include "IItems.hpp"
# include "Food.hpp"
# include "SuperFood.hpp"
# include "Random.hpp"
# include "Speed.hpp"
# include "Score.hpp"

namespace arcade
{
  class PowerUp : public Block
  {
  public:
    PowerUp(void);
    virtual ~PowerUp(void);
    virtual void refresh(float const delta, Map &map);
    virtual void loadTexture(void);
    virtual Drawable const* getTexture(Vector2u const& pos) const;
    virtual void checkCollisions(Player& player, Map &map);
  private:
    bool isEmptyFood(Map &map);

    void generateFood(Map &map);
    void generateBonus(Map &map);

    void generateNormal(Map &map);
    void generateSuper(Map &map);
    void generateRandom(Map &map);

    void generateSpeedBonus(Map &map);
    void generateScoreBonus(Map &map);

    Generator _generator;
    std::list<IItems *> _items;
    std::vector<Drawable *> _texture;

    std::list<IItems *> _bonus;
    float _delta_bonus;
  };
}

#endif /* !_POWERUP_HPP_ */
