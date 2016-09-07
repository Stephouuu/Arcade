//
// Pinky.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman/src/game/ghost
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 26 13:34:48 2016 stephane galibert
// Last update Mon Mar 28 21:25:50 2016 stephane galibert
//

#include "Pinky.hpp"

arcade::Pinky::Pinky(void)
{
  _move[Top] = std::bind(&arcade::Pinky::up, this, std::placeholders::_1);
  _move[Bottom] = std::bind(&arcade::Pinky::down, this, std::placeholders::_1);
  _move[Backward] = std::bind(&arcade::Pinky::left, this, std::placeholders::_1);
  _move[Forward] = std::bind(&arcade::Pinky::right, this, std::placeholders::_1);
}

arcade::Pinky::~Pinky(void)
{

}

void arcade::Pinky::init(Vector2u const& start)
{
  try {
    {
      Drawable *ghost = new Drawable;
      ghost->type = DrawableType::DRAWABLE_TEXTURE;
      ghost->texture = new FileCache("rsrc/pacman/texture/pacghost_3.png");
      _textures.push_back(ghost);
    }
    {
      _textureGhost = new Drawable;
      _textureGhost->type = DrawableType::DRAWABLE_TEXTURE;
      _textureGhost->texture = new FileCache("rsrc/pacman/texture/pacghost.png");
    }
    {
      _textureAfraid = new Drawable;
      _textureAfraid->type = DrawableType::DRAWABLE_TEXTURE;
      _textureAfraid->texture = new FileCache("rsrc/pacman/texture/pacghost_afraid.png");
    }
  } catch (ArcadeError const& e) {
    throw (e);
  }
  _spawn = start;
  _pos = start;
  _alive = true;
}

bool arcade::Pinky::refresh(arcade::Map &map, float const delta,
			    arcade::Player &player)
{
  if (_start)
    {
      _delta += delta;
      if (_afraid)
	{
	  if (_delta_afraid >= 10000)
	    setAfraid(false);
	  else
	    _delta_afraid += delta;
	}
      if (_delta > _speed)
	{
	  computeDirection(map, player);
	  _delta = (size_t)_delta % _speed;
	  return (true);
	}
    }
  return (false);
}

arcade::Drawable const* arcade::Pinky::getTexture(Vector2u const& pos) const
{
  if (_pos == pos)
    {
      if (!_alive)
	return (_textureGhost);
      if (_afraid)
	return (_textureAfraid);
      if (_textures.size() > 0)
	return (_textures[0]);
    }
  return (NULL);
}

arcade::Vector2u const& arcade::Pinky::getPositions(void) const
{
  return (_pos);
}

void arcade::Pinky::randomPath(arcade::Map &map)
{
  do {
    _random.x = _generator(0, map.width - 1);
    _random.y = _generator(0, map.height - 1);
  } while (map.map[_random.y][_random.x] == TileType::BLOCK);
}

void arcade::Pinky::play_normal(arcade::Map &map, arcade::Player &player)
{
  std::list<Vector2u> const& ppos = player.getPositions();
  Direction dir;
  Vector2u dest;
  Vector2u path;

  dest = getDest(map, player);
  path = findPath(map, dest);
  dir = deduceDirection(path);

  if (_pos == *ppos.cbegin())
    player.setAlive(false);
  if (_move.find(dir) != _move.end())
    _move[dir](map);
  if (_pos == *ppos.cbegin())
    player.setAlive(false);
}

void arcade::Pinky::play_afraid(arcade::Map &map)
{
  Direction dir;
  Vector2u dest;
  Vector2u path;

  randomPath(map);
  dest = _random;
  path = findPath(map, dest);
  dir = deduceDirection(path);

  if (_move.find(dir) != _move.end())
    _move[dir](map);
}

void arcade::Pinky::play_ghost(arcade::Map &map)
{
  Direction dir;
  Vector2u dest;
  Vector2u path;

  dest = _spawn;
  path = findPath(map, dest);
  dir = deduceDirection(path);

  if (_move.find(dir) != _move.end())
    _move[dir](map);
  if (_pos == dest)
    _alive = true;
}

void arcade::Pinky::computeDirection(arcade::Map &map, arcade::Player &player)
{
  if (!_alive)
    play_ghost(map);
  else if (_afraid)
    play_afraid(map);
  else
    play_normal(map, player);
}

arcade::Vector2u arcade::Pinky::findPath(arcade::Map &map,
					  arcade::Vector2u const& dest) const
{
  AStar astar;
  return (astar.getNextPath(map, _pos, dest));
}

arcade::Direction arcade::Pinky::deduceDirection(arcade::Vector2u const& path) const
{
  Direction dir = Dir_None;
  if (path.x != _pos.x)
    {
      if (path.x > _pos.x)
	dir = Forward;
      else if (path.x < _pos.x)
	dir = Backward;
    }
  else if (path.y != _pos.y)
    {
      if (path.y > _pos.y)
	dir = Bottom;
      else if (path.y < _pos.y)
	dir = Top;
    }
  return (dir);
}

arcade::Vector2u arcade::Pinky::getDest(arcade::Map &map,
					arcade::Player const& player)
{
  Direction pdir = player.getDirection();
  Vector2u dest = *player.getPositions().cbegin();
  if (pdir == Direction::Backward)
    {
      if (dest.x - 1 < map.width)
	if (map.map[dest.y][dest.x - 1] != TileType::BLOCK)
	  --dest.x;
    }
  else if (pdir == Direction::Forward)
    {
      if (dest.x + 1 < map.width)
	if (map.map[dest.y][dest.x + 1] != TileType::BLOCK)
	  ++dest.x;
    }
  else if (pdir == Direction::Top)
    {
      if (dest.y - 1 < map.height)
	if (map.map[dest.y - 1][dest.x] != TileType::BLOCK)
	  --dest.y;
    }
  else if (pdir == Direction::Bottom)
    {
      if (dest.y + 1 < map.height)
	if (map.map[dest.y + 1][dest.x] != TileType::BLOCK)
	  ++dest.y;
    }
  return (dest);
}

bool arcade::Pinky::up(arcade::Map &map)
{
  if (_pos.y > 0 && map.map[_pos.y - 1][_pos.x] != TileType::BLOCK)
    {
      map.map[_pos.y][_pos.x] = _previous;
      --_pos.y;
      _previous = map.map[_pos.y][_pos.x];
      map.map[_pos.y][_pos.x] = TileType::EVIL_DUDE;
      return (true);
    }
  return (false);
}

bool arcade::Pinky::down(arcade::Map &map)
{
  if (_pos.y != map.height - 1 && map.map[_pos.y + 1][_pos.x] != TileType::BLOCK)
    {
      map.map[_pos.y][_pos.x] = _previous;
      ++_pos.y;
      _previous = map.map[_pos.y][_pos.x];
      map.map[_pos.y][_pos.x] = TileType::EVIL_DUDE;
      return (true);
    }
  return (false);
}

bool arcade::Pinky::left(arcade::Map &map)
{
  if (_pos.y > 0 && map.map[_pos.y][_pos.x - 1] != TileType::BLOCK)
    {
      map.map[_pos.y][_pos.x] = _previous;
      --_pos.x;
      _previous = map.map[_pos.y][_pos.x];
      map.map[_pos.y][_pos.x] = TileType::EVIL_DUDE;
      return (true);
    }
  return (false);
}

bool arcade::Pinky::right(arcade::Map &map)
{
  if (_pos.y != map.width - 1 && map.map[_pos.y][_pos.x + 1] != TileType::BLOCK)
    {
      map.map[_pos.y][_pos.x] = _previous;
      ++_pos.x;
      _previous = map.map[_pos.y][_pos.x];
      map.map[_pos.y][_pos.x] = TileType::EVIL_DUDE;
      return (true);
    }
  return (false);
}
