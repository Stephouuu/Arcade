//
// nibbler.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Mar  8 11:09:56 2016 stephane galibert
// Last update Tue Mar 29 23:06:53 2016 stephane galibert
//

#include "Nibbler.hpp"

arcade::Nibbler::Nibbler(void)
{
  _scale = Vector2u(30, 30);
  _dim = Vector2u(30, 30);
  _begin.x = _dim.x / 2;
  _begin.y = _dim.y / 2;
  _player = NULL;
  _powerup = NULL;
  _backgroundTexture = NULL;
  _map.width = _dim.x;
  _map.height = _dim.y;
  _map.map = new TileType*[_map.height];
  for (size_t i = 0 ; i < _map.height ; ++i)
    _map.map[i] = new TileType[_map.width];
}

arcade::Nibbler::~Nibbler(void)
{
  for (auto &it : _texture)
    delete (it.second);
  if (_player)
    delete (_player);
  if (_powerup)
    delete (_powerup);
  if (_backgroundTexture)
    delete (_backgroundTexture);
  for (size_t i = 0 ; i < _map.height ; ++i)
    delete[] _map.map[i];
  delete[] _map.map;
}

std::string arcade::Nibbler::getGamesName(void) const
{
  return ("Nibbler");
}

arcade::Drawable const& arcade::Nibbler::getBackgroundTexture(void) const
{
  return (_background);
}

bool arcade::Nibbler::input(InputT const input)
{
  return (_player && _player->input(input));
}

void arcade::Nibbler::restart(void)
{
  if (_player)
    delete (_player);
  if (_powerup)
    delete (_powerup);
  _player = new Player;
  _powerup = new PowerUp;
  _player->init(Vector2u(_begin.x, _begin.y));
  _powerup->loadTexture();
  initMap();
  initPlayer();
}

arcade::Map const& arcade::Nibbler::getMap(void) const
{
  return (_map);
}

std::list<arcade::Vector2u> const& arcade::Nibbler::getPlayerPosition(void) const
{
  return (_player->getPositions());
}

bool arcade::Nibbler::isPlayerAlive(void) const
{
  return (_player && _player->isAlive());
}

bool arcade::Nibbler::isPlayerWin(void) const
{
  return (_player && _player->hasWin());
}

void arcade::Nibbler::setPlayerName(std::string const& name)
{
  if (_player)
    _player->setName(name);
}

std::string arcade::Nibbler::getPlayerName(void) const
{
  if (_player)
    return (_player->getName());
  return ("");
}

size_t arcade::Nibbler::getScore(void) const
{
  return (_player->getScore());
}

arcade::Vector2u arcade::Nibbler::getDimension(void) const
{
  return (_dim);
}

arcade::Vector2u arcade::Nibbler::getScale(void) const
{
  return (_scale);
}

void arcade::Nibbler::updateGame(float const delta)
{
  if (_player && _player->isAlive())
    {
      if (_player->refresh(_map, delta) && _powerup)
	_powerup->checkCollisions(*_player, _map);
    }
  if (_powerup)
    _powerup->refresh(delta, _map);
}

void arcade::Nibbler::loadTexture(void)
{
  try {
    if (!_backgroundTexture)
      _backgroundTexture = new FileCache("rsrc/nibbler/texture/herbe.jpg");
  } catch (ArcadeError const& e) {
    throw (e);
  }
  _background.type = DrawableType::DRAWABLE_TEXTURE;
  _background.pos = Vector2u(0, 0);
  _background.size = Vector2u(_map.width * _map.width, _map.height * _map.height);
  _background.texture = _backgroundTexture;
}

arcade::Drawable const * arcade::Nibbler::getTexture(arcade::Vector2u const& pos) const
{
  Drawable *drawable = NULL;
  if (_player && (drawable = const_cast<Drawable *>(_player->getTexture(pos))))
    {
      drawable->pos = Vector2u(pos.x * _scale.x,
			      pos.y * _scale.y);
      drawable->rpos = pos;
      drawable->size = _scale;
      return (drawable);
    }
  if (_powerup && (drawable = const_cast<Drawable *>(_powerup->getTexture(pos))))
    {
      drawable->pos = Vector2u(pos.x * _scale.x,
			      pos.y * _scale.y);
      drawable->size = _scale;
      drawable->rpos = pos;
      return (drawable);
    }
  return (NULL);
}

std::vector<arcade::Drawable> const& arcade::Nibbler::getDrawableEvent(void) const
{
  return (_player->getDrawable());
}

void arcade::Nibbler::goUp(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Up, Input::None));
}

void arcade::Nibbler::goDown(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Down, Input::None));
}

void arcade::Nibbler::goLeft(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Left, Input::None));
}

void arcade::Nibbler::goRight(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Right, Input::None));
}

void arcade::Nibbler::goForward(void)
{
  play();
}

void arcade::Nibbler::shoot(void)
{
  // do nothing
}

void arcade::Nibbler::play(void)
{
  updateGame(Player::REFRESH_DELAY_MS);
}

void arcade::Nibbler::initMap(void)
{
  for (size_t i = 0 ; i < _map.height ; ++i)
    for (size_t j = 0 ; j < _map.width ; ++j)
      _map.map[i][j] = TileType::EMPTY;
}

void arcade::Nibbler::initPlayer(void)
{
  if (_player)
    {
      std::list<Vector2u> const& player = _player->getPositions();
      for (auto &it : player)
	_map.map[it.y][it.x] = TileType::OTHER;
    }
}
