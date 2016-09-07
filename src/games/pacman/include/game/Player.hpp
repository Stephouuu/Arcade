//
// Player.hpp for arcade in /home/galibe_s/rendu/cpp_arcadeold/src/games/pacman/include/game
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 24 12:55:53 2016 stephane galibert
// Last update Mon Mar 28 20:24:47 2016 stephane galibert
//

#ifndef _PLAYER_HPP_
# define _PLAYER_HPP_

# include <iostream>
# include <string>
# include <list>
# include <map>
# include <vector>
# include <functional>
# include "Drawable.hpp"
# include "Input.hpp"
# include "Utility.hpp"
# include "Map.hpp"
# include "FileCache.hpp"
# include "IBonus.hpp"

namespace arcade
{
  class Player
  {
  public:
    static const int REFRESH_DELAY_MS = 150;
    enum Mode
      {
	NORMAL = 0,
	EAT
      };
    Player(void);
    ~Player(void);
    bool input(InputT const input);
    bool refresh(Map &map, float const delta);
    std::list<Vector2u> const& getPositions(void) const;
    Vector2u getRealPosition(void) const;
    void setPosition(Vector2u const& pos);
    Direction getDirection(void) const;
    std::string getName(void) const;
    Mode getMode(void) const;
    void setMode(Mode const mode);
    void setName(std::string const& name);
    bool isAlive(void) const;
    void setAlive(bool const value);
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
    bool isBlocked(void) const;
    void setBlocked(bool const value);
    Drawable const* getTexture(Vector2u const& pos) const;
    std::vector<Drawable> const& getDrawable(void) const;
    void addBuff(IBonus *bonus);
  private:
    std::map<Direction, std::function<bool(Map &)> > _move;
    bool up(Map &map);
    bool down(Map &map);
    bool left(Map &map);
    bool right(Map &map);
    std::vector<Drawable *> _textures;
    size_t _currentFrame;
    int _rotation;
    std::map<InputT, std::function<void(void)> > _directions;
    void dir_top(void);
    void dir_bot(void);
    void dir_forw(void);
    void dir_backw(void);
    Direction _dirCurrent;
    Direction _dirWanted;
    bool _blocked;
    std::vector<Drawable> _drawables;
    float _delta;
    bool _alive;
    bool _win;
    std::list<Vector2u> _pos;
    size_t _score;
    size_t _scoreCoef;
    std::string _name;
    size_t _speed;
    TileType _previous;
    Mode _mode;
    std::vector<IBonus *> _bonus;
  };
}

#endif /* !_PLAYER_HPP_ */
