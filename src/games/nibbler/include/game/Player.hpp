//
// Player.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 10 16:19:49 2016 stephane galibert
// Last update Sun Mar 27 12:55:00 2016 stephane galibert
//

#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include <iostream>
# include <string>
# include <list>
# include <map>
# include <vector>
# include <functional>

# include "IBonus.hpp"
# include "Drawable.hpp"
# include "Input.hpp"
# include "Utility.hpp"
# include "Map.hpp"
# include "FileCache.hpp"

namespace arcade
{
  class Player
  {
  public:
    static const int REFRESH_DELAY_MS = 150;
    Player(void);
    ~Player(void);
    bool input(InputT const input);
    bool refresh(Map &map, float const delta);
    void addBody(Map &map, Drawable const * drawable);
    std::list<Vector2u> const& getPositions(void) const;
    Vector2u getHeadPosition(void) const;
    std::string getName(void) const;
    void setName(std::string const& name);
    bool isAlive(void) const;
    bool hasWin(void) const;
    void setWin(bool const value);
    void setSpeed(size_t const value);
    size_t getSpeed(void) const;
    void resetSpeed(void);
    size_t addScore(size_t const value);
    size_t getScore(void) const;
    void setScoreCoef(size_t const coef);
    size_t getScoreCoef(void) const;
    void init(Vector2u const& start);
    Drawable const *getTexture(Vector2u const& pos) const;
    std::vector<Drawable> const& getDrawable(void) const;
    void addBuff(IBonus *bonus);
  private:
    bool isPlayerBody(Vector2u const& pos) const;
    bool isHeadCollide(void) const;
    std::map<Direction, std::function<void(Map &)> > _move;
    void up(Map &map);
    void down(Map &map);
    void left(Map &map);
    void right(Map &map);
    std::vector<std::string> _texturesPath;
    std::map<std::string, Drawable const *> _textures;
    std::map<InputT, std::function<void(void)> > _directions;
    void dir_top(void);
    void dir_bot(void);
    void dir_forw(void);
    void dir_backw(void);
    Direction _dir;
    bool _dirOk;
    std::vector<IBonus *> _bonus;
    std::vector<Drawable> _drawables;
    float _delta;
    bool _alive;
    bool _win;
    std::list<Vector2u> _body;
    size_t _score;
    size_t _scoreCoef;
    std::string _name;
    size_t _speed;
  };
}

#endif /* !_PLAYER_HPP_ */
