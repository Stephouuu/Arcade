//
// Pacman.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Mar 21 16:14:02 2016 stephane galibert
// Last update Fri Apr  1 14:22:23 2016 stephane galibert
//

#include "Pacman.hpp"

arcade::Pacman::Pacman(void)
{
  _dim = Vector2u(28, 31);
  _scale = Vector2u(30, 30);
  _begin.x = 14;
  _begin.y = 23;
  _player = NULL;
  _powerup = NULL;
  _backgroundTexture = NULL;
  _map.width = _dim.x;
  _map.height = _dim.y;
  _map.map = new TileType*[_map.height];
  for (size_t i = 0 ; i < _map.height ; ++i)
    _map.map[i] = new TileType[_map.width];
  _delta_ghost = 0;
}

arcade::Pacman::~Pacman(void)
{
  if (_player)
    delete (_player);
  if (_powerup)
    delete (_powerup);
  if (_backgroundTexture)
    delete (_backgroundTexture);
  for (auto &it : _textures)
    {
      delete (it->texture);
      delete (it);
    }
  for (size_t i = 0 ; i < _map.height ; ++i)
    delete[] _map.map[i];
  delete[] _map.map;
}

std::string arcade::Pacman::getGamesName(void) const
{
  return ("Pacman");
}

arcade::Drawable const& arcade::Pacman::getBackgroundTexture(void) const
{
  return (_background);
}

bool arcade::Pacman::input(InputT const input)
{
  return (_player && _player->input(input));
}

void arcade::Pacman::restart(void)
{
  try {
    if (_player)
      delete (_player);
    if (_powerup)
      delete (_powerup);
    for (auto &it : _ghosts)
    delete (it);
    _ghosts.erase(_ghosts.begin(), _ghosts.end());
    _player = new Player;
    _powerup = new PowerUp;
    initMap();
    _player->init(_mapData.getPosStart(MapData::PLAYER));
    _powerup->loadTexture();
    {
      Blinky *ghost = new Blinky;
      ghost->init(_mapData.getPosStart(MapData::BLINKY));
      _ghosts.push_back(ghost);
    }
    {
      Pinky *ghost = new Pinky;
      ghost->init(_mapData.getPosStart(MapData::PINKY));
      _ghosts.push_back(ghost);
    }
    {
      Inky *ghost = new Inky;
      ghost->init(_mapData.getPosStart(MapData::INKY));
      _ghosts.push_back(ghost);
    }
    {
      Clyde *ghost = new Clyde;
      ghost->init(_mapData.getPosStart(MapData::CLYDE));
      _ghosts.push_back(ghost);
    }
    _delta_ghost = 0;
    initPlayer();
    initGhost();
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

arcade::Map const& arcade::Pacman::getMap(void) const
{
  return (_map);
}

std::list<arcade::Vector2u> const& arcade::Pacman::getPlayerPosition(void) const
{
  return (_player->getPositions());
}

bool arcade::Pacman::isPlayerAlive(void) const
{
  return (_player && _player->isAlive());
}

bool arcade::Pacman::isPlayerWin(void) const
{
  return (_player && _player->hasWin());
}

void arcade::Pacman::setPlayerName(std::string const& name)
{
  if (_player)
    _player->setName(name);
}

std::string arcade::Pacman::getPlayerName(void) const
{
  if (_player)
    return (_player->getName());
  return ("");
}

size_t arcade::Pacman::getScore(void) const
{
  return (_player->getScore());
}

arcade::Vector2u arcade::Pacman::getDimension(void) const
{
  return (_dim);
}

arcade::Vector2u arcade::Pacman::getScale(void) const
{
  return (_scale);
}

void arcade::Pacman::updateGame(float const delta)
{
  if (_player && _player->isAlive())
    {
      if (_player->refresh(_map, delta) && _powerup)
	_powerup->checkCollisions(*_player, _ghosts, _map);
      std::list<Vector2u> const& pos = _player->getPositions();
      if (_mapData.isLink(*pos.cbegin()) && _player->isBlocked())
	{
	  _player->setBlocked(false);
	  _map.map[pos.cbegin()->y][pos.cbegin()->x] = TileType::EMPTY;
	  _player->setPosition(_mapData.getLink(*pos.cbegin()));
	  _map.map[pos.cbegin()->y][pos.cbegin()->x] = TileType::OTHER;
	}
      if (_delta_ghost <= 10000)
	_delta_ghost += delta;
      if (!_player->hasWin())
	for (auto &it : _ghosts)
	  {
	    if (_delta_ghost > 10000)
	      it->setStart(true);
	    it->refresh(_map, delta, *_player);
	  }
    }
  if (_powerup)
    _powerup->refresh(delta, _map);
}

void arcade::Pacman::loadTexture(void)
{
  try {
    {
      Drawable *food = new Drawable;
      food->type = DrawableType::DRAWABLE_TEXTURE;
      food->texture = new FileCache("rsrc/pacman/texture/pacgum.png");
      _textures.push_back(food);
    }
    {
      Drawable *sfood = new Drawable;
      sfood->type = DrawableType::DRAWABLE_TEXTURE;
      sfood->texture = new FileCache("rsrc/pacman/texture/spacgum.png");
      _textures.push_back(sfood);
    }
    {
      Drawable *sfood = new Drawable;
      sfood->type = DrawableType::DRAWABLE_TEXTURE;
      sfood->texture = new FileCache("rsrc/pacman/texture/spacgum1.png");
      _textures.push_back(sfood);
    }
    {
      Drawable *sfood = new Drawable;
      sfood->type = DrawableType::DRAWABLE_TEXTURE;
      sfood->texture = new FileCache("rsrc/pacman/texture/spacgum2.png");
      _textures.push_back(sfood);
    }
  } catch (ArcadeError const& e) {
    throw (e);
  }
  _background.type = DrawableType::DRAWABLE_TEXTURE;
  _background.pos = Vector2u(0, 0);
  _background.size = Vector2u(_map.width * _scale.x, _map.height * _scale.y);
}

arcade::Drawable const * arcade::Pacman::getTexture(Vector2u const& pos) const
{
  Drawable *texture = NULL;

  if (_player && (texture = const_cast<Drawable *>(_player->getTexture(pos))))
    {
      texture->origin = Vector2u(_scale.x / 2, _scale.y / 2);
      texture->pos = Vector2u((pos.x * _scale.x) + texture->origin.x,
			      (pos.y * _scale.y) + texture->origin.y);
      texture->rpos = pos;
      texture->size = _scale;
      return (texture);
    }
  for (auto &it : _ghosts)
    {
      if (it && (texture = const_cast<Drawable *>(it->getTexture(pos))))
	{
	  texture->pos = Vector2u(pos.x * _scale.x,
				  pos.y * _scale.y);
	  texture->rpos = pos;
	  texture->size = _scale;
	  return (texture);
	}
    }
  if (_powerup && (texture = const_cast<Drawable *>(_powerup->getTexture(pos))))
    {
      texture->pos = Vector2u(pos.x * _scale.x,
			      pos.y * _scale.y);
      texture->rpos = pos;
      texture->size = _scale;
      return (texture);
    }
  return (NULL);
}

std::vector<arcade::Drawable> const& arcade::Pacman::getDrawableEvent(void) const
{
  return (_player->getDrawable());
}

void arcade::Pacman::goUp(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Up, Input::None));
}

void arcade::Pacman::goDown(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Down, Input::None));
}

void arcade::Pacman::goLeft(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Left, Input::None));
}

void arcade::Pacman::goRight(void)
{
  if (_player)
    _player->input(InputT(InputT::KeyPressed, Input::Right, Input::None));
}

void arcade::Pacman::goForward(void)
{
  play();
}

void arcade::Pacman::shoot(void)
{
  // do nothing
}

void arcade::Pacman::play(void)
{
  updateGame(Player::REFRESH_DELAY_MS);
}

void arcade::Pacman::initMap(void)
{
  for (size_t i = 0 ; i < _map.height ; ++i)
    for (size_t j = 0 ; j < _map.width ; ++j)
      _map.map[i][j] = TileType::EMPTY;

  try {
    _mapData.parseMapData("rsrc/pacman/map/pacman", _map);
    _backgroundTexture = new FileCache(_mapData.getBackground());
    _background.texture = _backgroundTexture;
    for (auto &it : _mapData.getSPacGum())
      {
	SPacGum *spg = new SPacGum(it);
	if (_textures.size() > 1)
	  spg->addFrame(_textures[1]);
	if (_textures.size() > 2)
	  spg->addFrame(_textures[2]);
	if (_textures.size() > 3)
	  spg->addFrame(_textures[3]);
	_powerup->add(spg);
      }
    for (auto &it : _mapData.getPacGum())
      {
	PacGum *pg = new PacGum(it);
	if (_textures.size() > 0)
	  pg->addFrame(_textures[0]);
	if (!_powerup->add(pg))
	  delete (pg);
      }
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

void arcade::Pacman::initPlayer(void)
{
  if (_player)
    {
      std::list<Vector2u> const& player = _player->getPositions();
      _map.map[player.cbegin()->y][player.cbegin()->x] = TileType::OTHER;
    }
}

void arcade::Pacman::initGhost(void)
{
  for (auto &it : _ghosts)
    {
      Vector2u const& pos = it->getPositions();
      _map.map[pos.y][pos.x] = TileType::EVIL_DUDE;
    }
}
