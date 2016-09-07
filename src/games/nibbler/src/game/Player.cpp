//
// Player.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 10 16:19:45 2016 stephane galibert
// Last update Mon Mar 28 20:20:37 2016 stephane galibert
//

#include "Player.hpp"

arcade::Player::Player(void)
{
  _move[Direction::Top] = std::bind(&arcade::Player::up, this, std::placeholders::_1);
  _move[Direction::Bottom] = std::bind(&arcade::Player::down, this, std::placeholders::_1);
  _move[Direction::Backward] = std::bind(&arcade::Player::left, this, std::placeholders::_1);
  _move[Direction::Forward] = std::bind(&arcade::Player::right, this, std::placeholders::_1);

  _dir = Direction::Top;
  _dirOk = true;
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Up, InputT::None),
				    std::bind(&arcade::Player::dir_top, this)));
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Down, InputT::None),
				    std::bind(&arcade::Player::dir_bot, this)));
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Left, InputT::None),
				    std::bind(&arcade::Player::dir_backw, this)));
  _directions.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Right, InputT::None),
				    std::bind(&arcade::Player::dir_forw, this)));
  _delta = 0;
  _alive = false;
  _win = false;
  _score = 0;
  _scoreCoef = 1;
  _speed = REFRESH_DELAY_MS;
}

arcade::Player::~Player(void)
{
  for (auto &it : _bonus)
    delete (it);
  for (auto &it : _textures)
    {
      delete it.second->texture;
      delete it.second;
    }
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
      if (_move.find(_dir) != _move.end())
	_move[_dir](map);
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
  return (_body);
}

arcade::Vector2u arcade::Player::getHeadPosition(void) const
{
  Vector2u pos;
  pos.x = _body.cbegin()->x * 30;
  pos.y = _body.cbegin()->y * 30;
  return (pos);
}

std::string arcade::Player::getName(void) const
{
  return (_name);
}
void arcade::Player::setName(std::string const& name)
{
  _name = name;
}

bool arcade::Player::isAlive(void) const
{
  return (_alive);
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
    _body.push_back(Vector2u(start.x, start.y));
    _body.push_back(Vector2u(start.x, start.y + 1));
    _body.push_back(Vector2u(start.x, start.y + 2));
    _body.push_back(Vector2u(start.x, start.y + 3));
    _texturesPath.push_back("rsrc/nibbler/texture/chefdeguerre.png");
    _texturesPath.push_back("rsrc/nibbler/texture/bouloute.png");
    _texturesPath.push_back("rsrc/nibbler/texture/bouloute.png");
    _texturesPath.push_back("rsrc/nibbler/texture/bouloute.png");
    {
      Drawable *head = new Drawable;
      head->type = DrawableType::DRAWABLE_TEXTURE;
      head->texture = new FileCache(_texturesPath[0]);
      _textures[_texturesPath[0]] = head;
    }
    {
      Drawable *body1 = new Drawable;
      body1->type = DrawableType::DRAWABLE_TEXTURE;
      body1->texture = new FileCache(_texturesPath[1]);
      _textures[_texturesPath[1]] = body1;
    }
    {
      Drawable *body2 = new Drawable;
      body2->type = DrawableType::DRAWABLE_TEXTURE;
      body2->texture = new FileCache(_texturesPath[2]);
      _textures[_texturesPath[2]] = body2;
    }
    {
      Drawable *body3 = new Drawable;
      body3->type = DrawableType::DRAWABLE_TEXTURE;
      body3->texture = new FileCache(_texturesPath[3]);
      _textures[_texturesPath[3]] = body3;
    }
    _alive = true;
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

arcade::Drawable const *arcade::Player::getTexture(arcade::Vector2u const& pos) const
{
  if (isPlayerBody(pos))
    {
      size_t i = 0;
      for (auto &it : _body)
	{
	  if (it.x == pos.x && it.y == pos.y)
	    {
	      if (i < _texturesPath.size()
		  && _textures.find(_texturesPath[i]) != _textures.end())
		return (_textures.at(_texturesPath.at(i)));
	      return (NULL);
	    }
	  ++i;
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

bool arcade::Player::isPlayerBody(arcade::Vector2u const& pos) const
{
  for (auto &it : _body)
    if (it.x == pos.x && it.y == pos.y)
      return (true);
  return (false);
}

bool arcade::Player::isHeadCollide(void) const
{
  for (std::list<Vector2u>::const_iterator it = ++_body.cbegin() ;
       it != _body.cend() ;
       ++it)
    if (_body.cbegin()->x == it->x && _body.cbegin()->y == it->y)
      return (true);
  return (false);
}

void arcade::Player::up(arcade::Map &map)
{
  if (_body.cbegin()->y == 0)
    _alive = false;
  else
    {
      _dirOk = true;
      map.map[_body.crbegin()->y][_body.crbegin()->x] = TileType::EMPTY;
      _body.rbegin()->y = _body.cbegin()->y - 1;
      _body.rbegin()->x = _body.cbegin()->x;
      _body.insert(_body.begin(), *_body.rbegin());
      _body.erase(std::next(_body.rbegin()).base());
      if (isHeadCollide())
	_alive = false;
      map.map[_body.cbegin()->y][_body.cbegin()->x] = TileType::OTHER;
    }
}

void arcade::Player::down(arcade::Map &map)
{
  if (_body.cbegin()->y == map.height - 1)
    _alive = false;
  else
    {
      _dirOk = true;
      map.map[_body.crbegin()->y][_body.crbegin()->x] = TileType::EMPTY;
      _body.rbegin()->y = _body.cbegin()->y + 1;
      _body.rbegin()->x = _body.cbegin()->x;
      _body.insert(_body.begin(), *_body.rbegin());
      _body.erase(std::next(_body.rbegin()).base());
      if (isHeadCollide())
	_alive = false;
      map.map[_body.cbegin()->y][_body.cbegin()->x] = TileType::OTHER;
    }
}

void arcade::Player::left(arcade::Map &map)
{
  if (_body.cbegin()->x == 0)
    _alive = false;
  else
    {
      _dirOk = true;
      map.map[_body.crbegin()->y][_body.crbegin()->x] = TileType::EMPTY;
      _body.rbegin()->x = _body.cbegin()->x - 1;
      _body.rbegin()->y = _body.cbegin()->y;
      _body.insert(_body.begin(), *_body.rbegin());
      _body.erase(std::next(_body.rbegin()).base());
      if (isHeadCollide())
	_alive = false;
      map.map[_body.cbegin()->y][_body.cbegin()->x] = TileType::OTHER;
    }
}

void arcade::Player::right(arcade::Map &map)
{
  if (_body.cbegin()->x == map.width - 1)
    _alive = false;
  else
    {
      _dirOk = true;
      map.map[_body.crbegin()->y][_body.crbegin()->x] = TileType::EMPTY;
      _body.rbegin()->x = _body.cbegin()->x + 1;
      _body.rbegin()->y = _body.cbegin()->y;
      _body.insert(_body.begin(), *_body.rbegin());
      _body.erase(std::next(_body.rbegin()).base());
      _dir = Direction::Forward;
      if (isHeadCollide())
	_alive = false;
      map.map[_body.cbegin()->y][_body.cbegin()->x] = TileType::OTHER;
    }
}

void arcade::Player::addBody(arcade::Map &map, arcade::Drawable const * drawable)
{
  Vector2u newElement;

  if (drawable && drawable->texture)
    {
      _texturesPath.push_back(drawable->texture->filename);
	if (_textures.find(drawable->texture->filename) == _textures.end())
	  _textures[drawable->texture->filename] = drawable;
    }

  newElement.x = _body.crbegin()->x + (_body.crbegin()->x - (++_body.crbegin())->x);
  newElement.y = _body.crbegin()->y + (_body.crbegin()->y - (++_body.crbegin())->y);
  if (newElement.x < map.width && newElement.y < map.height
      && map.map[newElement.y][newElement.x] == TileType::EMPTY)
    {
      map.map[newElement.y][newElement.x] = TileType::OTHER;
      _body.push_back(newElement);
    }
  else
    {
      newElement.x = _body.crbegin()->x;
      newElement.y = _body.crbegin()->y;
      if (newElement.x + 1 < map.width && newElement.y < map.height
	  && map.map[newElement.y][newElement.x + 1] == TileType::EMPTY)
	{
	  map.map[newElement.y][newElement.x + 1] = TileType::OTHER;
	  _body.push_back(Vector2u(newElement.x + 1, newElement.y));
	}
      else if (newElement.x - 1 < map.width && newElement.y < map.height
	       && map.map[newElement.y][newElement.x - 1] == TileType::EMPTY)
	{
	  map.map[newElement.y][newElement.x - 1] = TileType::OTHER;
	  _body.push_back(Vector2u(newElement.x - 1, newElement.y));
	}
      else if (newElement.x < map.width && newElement.y + 1 < map.height
	       && map.map[newElement.y + 1][newElement.x] == TileType::EMPTY)
	{
	  map.map[newElement.y + 1][newElement.x] = TileType::OTHER;
	  _body.push_back(Vector2u(newElement.x, newElement.y + 1));
	}
      else if (newElement.x < map.width && newElement.y - 1 < map.height
	   && map.map[newElement.y - 1][newElement.x] == TileType::EMPTY)
	{
	  _body.push_back(Vector2u(newElement.x, newElement.y - 1));
	  map.map[newElement.y - 1][newElement.x] = TileType::OTHER;
	}
      else
	_alive = false;
    }
}

void arcade::Player::dir_top(void)
{
  if (_dirOk && _dir != Direction::Bottom)
    {
      _dir = Direction::Top;
      _dirOk = false;
    }
}

void arcade::Player::dir_bot(void)
{
  if (_dirOk && _dir != Direction::Top && _dir != Direction::Dir_None)
    {
      _dir = Direction::Bottom;
      _dirOk = false;
    }
}

void arcade::Player::dir_forw(void)
{
  if (_dirOk && _dir != Direction::Backward)
    {
      _dir = Direction::Forward;
      _dirOk = false;
    }
}

void arcade::Player::dir_backw(void)
{
  if (_dirOk && _dir != Direction::Forward)
    {
      _dir = Direction::Backward;
      _dirOk = false;
    }
}
