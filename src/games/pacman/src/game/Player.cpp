//
// Player.cpp for arcade in /home/galibe_s/rendu/cpp_arcadeold/src/games/pacman/src/game
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 24 12:56:57 2016 stephane galibert
// Last update Fri Apr  1 14:24:57 2016 stephane galibert
//

#include "Player.hpp"

arcade::Player::Player(void)
{
  _move[Direction::Top] = std::bind(&arcade::Player::up, this, std::placeholders::_1);
  _move[Direction::Bottom] = std::bind(&arcade::Player::down, this, std::placeholders::_1);
  _move[Direction::Backward] = std::bind(&arcade::Player::left, this, std::placeholders::_1);
  _move[Direction::Forward] = std::bind(&arcade::Player::right, this, std::placeholders::_1);

  _dirCurrent = Direction::Forward;
  _dirWanted = Direction::Forward;
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Up, InputT::None),
				    std::bind(&arcade::Player::dir_top, this)));
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Down, InputT::None),
				    std::bind(&arcade::Player::dir_bot, this)));
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Left, InputT::None),
				    std::bind(&arcade::Player::dir_backw, this)));
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Right, InputT::None),
				    std::bind(&arcade::Player::dir_forw, this)));
  _blocked = false;
  _delta = 0;
  _alive = false;
  _win = false;
  _score = 0;
  _scoreCoef = 1;
  _speed = REFRESH_DELAY_MS;

  _currentFrame = 1;
  _rotation = 0;
  _previous = TileType::EMPTY;
  _mode = Mode::NORMAL;
}

arcade::Player::~Player(void)
{
  for (auto &it : _textures)
    delete (it);
  for (auto &it : _bonus)
    delete (it);
}

bool arcade::Player::input(arcade::InputT const input)
{
  if (_directions.find(input) != _directions.end())
    {
      _directions[input]();
      return (true);
    }
  return (false);
}

bool arcade::Player::refresh(arcade::Map &map, float const delta)
{
  _delta += delta;
  if (_delta >= _speed)
    {
      if (!_blocked)
	{
	  ++_currentFrame;
	  if (_currentFrame >= _textures.size())
	    _currentFrame = 0;
	}
      else
	_currentFrame = 1;
      if (_alive && !_win && _move.find(_dirCurrent) != _move.end())
	_move[_dirCurrent](map);
      _delta = (size_t)_delta % _speed;
      return (true);
    }

  _drawables.erase(_drawables.begin(), _drawables.end());
  for (std::vector<IBonus *>::iterator it = _bonus.begin() ;
       it != _bonus.end() ;)
    {
      if ((*it)->isFinish())
	{
	  delete (*it);
	  it = _bonus.erase(it);
	}
      else
	{
	  (*it)->update(delta);
	  _drawables.push_back((*it)->getCurrentDrawable());
	  ++it;
	}
    }

  return (false);
}

std::list<arcade::Vector2u> const& arcade::Player::getPositions(void) const
{
  return (_pos);
}

arcade::Vector2u arcade::Player::getRealPosition(void) const
{
  Vector2u pos = *_pos.cbegin();
  pos.x *= 30;
  pos.y *= 30;
  return (pos);
}

arcade::Direction arcade::Player::getDirection(void) const
{
  return (_dirCurrent);
}

void arcade::Player::setPosition(arcade::Vector2u const& pos)
{
  *_pos.begin() = pos;
}

std::string arcade::Player::getName(void) const
{
  return (_name);
}

arcade::Player::Mode arcade::Player::getMode(void) const
{
  return (_mode);
}

void arcade::Player::setMode(Mode const mode)
{
  _mode = mode;
}

void arcade::Player::setName(std::string const& name)
{
  _name = name;
}

bool arcade::Player::isAlive(void) const
{
  return (_alive);
}

void arcade::Player::setAlive(bool const value)
{
  _alive = value;
}

bool arcade::Player::hasWin(void) const
{
  return (_win);
}

void arcade::Player::setWin(bool const value)
{
  _win = value;
}

void arcade::Player::setSpeed(size_t const speed)
{
  _speed = speed;
}

size_t arcade::Player::getSpeed(void) const
{
  return (_speed);
}

void arcade::Player::resetSpeed(void)
{
  _speed += 30;
}

size_t arcade::Player::addScore(size_t const value)
{
  _score = _score + (value * _scoreCoef);
  return (_scoreCoef);
}

size_t arcade::Player::getScore(void) const
{
  return (_score);
}

void arcade::Player::setScoreCoef(size_t const coef)
{
  _scoreCoef = coef;
}

size_t arcade::Player::getScoreCoef(void) const
{
  return (_scoreCoef);
}

void arcade::Player::init(arcade::Vector2u const& start)
{
  try {
    {
      Drawable *player0 = new Drawable;
      player0->type = DrawableType::DRAWABLE_TEXTURE;
      player0->texture = new FileCache("rsrc/pacman/texture/pacman_0.png");
      _textures.push_back(player0);
    }
    {
      Drawable *player1 = new Drawable;
      player1->type = DrawableType::DRAWABLE_TEXTURE;
      player1->texture = new FileCache("rsrc/pacman/texture/pacman_1.png");
      _textures.push_back(player1);
    }
    {
      Drawable *player2 = new Drawable;
      player2->type = DrawableType::DRAWABLE_TEXTURE;
      player2->texture = new FileCache("rsrc/pacman/texture/pacman_2.png");
      _textures.push_back(player2);
    }
    _alive = true;
    _pos.push_back(start);
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

bool arcade::Player::isBlocked(void) const
{
  return (_blocked);
}

void arcade::Player::setBlocked(bool const value)
{
  _blocked = value;
}

arcade::Drawable const * arcade::Player::getTexture(arcade::Vector2u const& pos) const
{
  if (pos == *_pos.cbegin())
    {
      if (_currentFrame < _textures.size())
	{
	  _textures[_currentFrame]->rotation = _rotation;
	  return (_textures[_currentFrame]);
	}
    }
  return (NULL);
}

std::vector<arcade::Drawable> const& arcade::Player::getDrawable(void) const
{
  return (_drawables);
}

void arcade::Player::addBuff(arcade::IBonus *bonus)
{
  _bonus.push_back(bonus);
}

bool arcade::Player::up(arcade::Map &map)
{
  if (_dirWanted != Direction::Top && _move[_dirWanted](map))
    {
      _dirCurrent = _dirWanted;
      return (true);
    }
  if (_pos.cbegin()->y > 0
      && map.map[_pos.cbegin()->y - 1][_pos.cbegin()->x] != TileType::BLOCK)
    {
      _rotation = -90;
      _blocked = false;
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = _previous;
      --_pos.begin()->y;
      _previous = map.map[_pos.cbegin()->y][_pos.cbegin()->x];
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = TileType::OTHER;
      return (true);
    }
  else
    _blocked = true;
  return (false);
}

bool arcade::Player::down(arcade::Map &map)
{
  if (_dirWanted != Direction::Bottom && _move[_dirWanted](map))
    {
      _dirCurrent = _dirWanted;
      return (true);
    }
  if (_pos.cbegin()->y != map.height - 1
      && map.map[_pos.cbegin()->y + 1][_pos.cbegin()->x] != TileType::BLOCK)
    {
      _rotation = 90;
      _blocked = false;
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = _previous;
      ++_pos.begin()->y;
      _previous = map.map[_pos.cbegin()->y][_pos.cbegin()->x];
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = TileType::OTHER;
      return (true);
    }
  else
    _blocked = true;
  return (false);
}

bool arcade::Player::left(arcade::Map &map)
{
  if (_dirWanted != Direction::Backward && _move[_dirWanted](map))
    {
      _dirCurrent = _dirWanted;
      return (true);
    }
  if (_pos.cbegin()->x > 0
      && map.map[_pos.cbegin()->y][_pos.cbegin()->x - 1] != TileType::BLOCK)
    {
      _rotation = 180;
      _blocked = false;
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = _previous;
      --_pos.begin()->x;
      _previous = map.map[_pos.cbegin()->y][_pos.cbegin()->x];
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = TileType::OTHER;
      return (true);
    }
  else
    _blocked = true;
  return (false);
}

bool arcade::Player::right(arcade::Map &map)
{
  if (_dirWanted != Direction::Forward && _move[_dirWanted](map))
    {
      _dirCurrent = _dirWanted;
      return (true);
    }
  if (_pos.cbegin()->x != map.width - 1
      && map.map[_pos.cbegin()->y][_pos.cbegin()->x + 1] != TileType::BLOCK)
    {
      _rotation = 0;
      _blocked = false;
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = _previous;
      ++_pos.begin()->x;
      _previous = map.map[_pos.cbegin()->y][_pos.cbegin()->x];
      map.map[_pos.cbegin()->y][_pos.cbegin()->x] = TileType::OTHER;
      return (true);
    }
  else
    _blocked = true;
  return (false);
}

void arcade::Player::dir_top(void)
{
  _dirWanted = Direction::Top;
  if (_dirCurrent == Direction::Dir_None)
    _dirCurrent = _dirWanted;
}

void arcade::Player::dir_bot(void)
{
  _dirWanted = Direction::Bottom;
  if (_dirCurrent == Direction::Dir_None)
    _dirCurrent = _dirWanted;
}

void arcade::Player::dir_forw(void)
{
  _dirWanted = Direction::Forward;
  if (_dirCurrent == Direction::Dir_None)
    _dirCurrent = _dirWanted;
}

void arcade::Player::dir_backw(void)
{
  _dirWanted = Direction::Backward;
  if (_dirCurrent == Direction::Dir_None)
    _dirCurrent = _dirWanted;
}
