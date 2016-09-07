//
// MapData.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 31 23:14:29 2016 stephane galibert
// Last update Fri Apr  1 00:29:30 2016 stephane galibert
//

#include "MapData.hpp"

const std::string arcade::MapData::PLAYER = "PLAYER";
const std::string arcade::MapData::BLINKY = "BLINKY";
const std::string arcade::MapData::PINKY = "PINKY";
const std::string arcade::MapData::INKY = "INKY";
const std::string arcade::MapData::CLYDE = "CLYDE";

arcade::MapData::MapData(void)
{
  _parser["LINK"] = std::bind(&arcade::MapData::parseLink, this,
			      std::placeholders::_1);
  _parser["PSTART"] = std::bind(&arcade::MapData::setPlayerStart, this,
				std::placeholders::_1);
  _parser["BLINKY_START"] = std::bind(&arcade::MapData::setBlinkyStart, this,
				      std::placeholders::_1);
  _parser["PINKY_START"] = std::bind(&arcade::MapData::setPinkyStart, this,
				      std::placeholders::_1);
  _parser["INKY_START"] = std::bind(&arcade::MapData::setInkyStart, this,
				    std::placeholders::_1);
  _parser["CLYDE_START"] = std::bind(&arcade::MapData::setClydeStart, this,
				     std::placeholders::_1);
  _parser["SP"] = std::bind(&arcade::MapData::setSPacGum, this,
			    std::placeholders::_1);
  _parser["TEXTURE"] = std::bind(&arcade::MapData::setBackgroundTexture, this,
				 std::placeholders::_1);
}

arcade::MapData::~MapData(void)
{

}

void arcade::MapData::parseMapData(std::string const& filename, arcade::Map &map)
{
  std::ifstream ifs(filename.data());
  std::string line;
  if (ifs)
    {
      while (std::getline(ifs, line))
	{
	  size_t pos = line.find_first_of(" \t");
	  if (pos != std::string::npos)
	    {
	      if (_parser.find(line.substr(0, pos)) != _parser.end())
		_parser[line.substr(0, pos)](line);
	    }
	  else if (line == "MAP_BEGIN")
	    parseMap(ifs, map);
	}
      ifs.close();
      for (size_t y = 0 ; y < map.height ; ++y)
	for (size_t x = 0 ; x < map.width ; ++x)
	  if (map.map[y][x] == TileType::POWERUP)
	    _pacgum.push_back(Vector2u(x, y));
    }
  else
    throw (MapError(filename + " file not found"));
}

bool arcade::MapData::isLink(Vector2u const& pos) const
{
  return (_link.find(pos) != _link.end());
}

arcade::Vector2u const& arcade::MapData::getLink(arcade::Vector2u const& link) const
{
  if (_link.find(link) != _link.end())
    return _link.at(link);
  throw (MapError("key link not found"));
}

arcade::Vector2u const& arcade::MapData::getPosStart(std::string const& key) const
{
  if (_positions.find(key) != _positions.end())
    return (_positions.at(key));
  throw (MapError("key pos not found"));
}

std::string const& arcade::MapData::getBackground(void) const
{
  return (_background);
}

std::vector<arcade::Vector2u> const& arcade::MapData::getSPacGum(void) const
{
  return (_spacgum);
}

std::vector<arcade::Vector2u> const& arcade::MapData::getPacGum(void) const
{
  return (_pacgum);
}

void arcade::MapData::parseMap(std::ifstream &ifs, arcade::Map &map)
{
  std::string line = "";
  size_t pos = 0;
  size_t x = 0;
  size_t y = 0;

  while (std::getline(ifs, line) && line != "MAP_END")
    {
      x = 0;
      pos = line.find_first_not_of(" \t");
      while (pos != std::string::npos && y < map.height && x < map.width)
	{
	  map.map[y][x] = static_cast<TileType>(line[pos] - 48);
	  pos = line.find_first_not_of(" \t", pos + 1);
	  x++;
	}
      y++;
    }
}

void arcade::MapData::parseLink(std::string const& data)
{
  Vector2u lnk1;
  Vector2u lnk2;
  size_t pos = data.find_first_of(" \t");
  size_t pos1 = 0;
  if (pos != std::string::npos)
    {
      ++pos;
      pos1 = data.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	lnk1.x = std::atoi(data.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = data.find_first_of(" \t", pos);
      if (pos1 != std::string::npos)
	lnk1.y = std::atoi(data.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = data.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	lnk2.x = std::atoi(data.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = data.find_first_of("-", pos1);
      if (pos1 != std::string::npos)
	lnk2.y = std::atoi(data.substr(pos, pos1 - pos).data());
    }
  _link[lnk1] = lnk2;
}

void arcade::MapData::setPlayerStart(std::string const& start)
{
  Vector2u player;
  size_t pos = start.find_first_of(" \t");
  size_t pos1 = 0;
  if (pos != std::string::npos)
    {
      ++pos;
      pos1 = start.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	player.x = std::atoi(start.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = start.find_first_of(" \t", pos1);
      player.y = std::atoi(start.substr(pos, pos1 - pos).data());
      _positions[PLAYER] = player;
    }
}

void arcade::MapData::setBlinkyStart(std::string const& start)
{
  Vector2u blinky;
  size_t pos = start.find_first_of(" \t");
  size_t pos1 = 0;
  if (pos != std::string::npos)
    {
      ++pos;
      pos1 = start.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	blinky.x = std::atoi(start.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = start.find_first_of(" \t", pos1);
      blinky.y = std::atoi(start.substr(pos, pos1 - pos).data());
      _positions[BLINKY] = blinky;
    }
}

void arcade::MapData::setPinkyStart(std::string const& start)
{
  Vector2u pinky;
  size_t pos = start.find_first_of(" \t");
  size_t pos1 = 0;
  if (pos != std::string::npos)
    {
      ++pos;
      pos1 = start.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	pinky.x = std::atoi(start.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = start.find_first_of(" \t", pos1);
      pinky.y = std::atoi(start.substr(pos, pos1 - pos).data());
      _positions[PINKY] = pinky;
    }
}

void arcade::MapData::setInkyStart(std::string const& start)
{
  Vector2u inky;
  size_t pos = start.find_first_of(" \t");
  size_t pos1 = 0;
  if (pos != std::string::npos)
    {
      ++pos;
      pos1 = start.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	inky.x = std::atoi(start.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = start.find_first_of(" \t", pos1);
      inky.y = std::atoi(start.substr(pos, pos1 - pos).data());
      _positions[INKY] = inky;
    }
}

void arcade::MapData::setClydeStart(std::string const& start)
{
  Vector2u clyde;
  size_t pos = start.find_first_of(" \t");
  size_t pos1 = 0;
  if (pos != std::string::npos)
    {
      ++pos;
      pos1 = start.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	clyde.x = std::atoi(start.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = start.find_first_of(" \t", pos1);
      clyde.y = std::atoi(start.substr(pos, pos1 - pos).data());
      _positions[CLYDE] = clyde;
    }
}

void arcade::MapData::setSPacGum(std::string const& start)
{
  Vector2u spos;
  size_t pos = start.find_first_of(" \t");
  size_t pos1 = 0;
  if (pos != std::string::npos)
    {
      ++pos;
      pos1 = start.find_first_of("-", pos);
      if (pos1 != std::string::npos)
	spos.x = std::atoi(start.substr(pos, pos1 - pos).data());
      pos = pos1 + 1;
      pos1 = start.find_first_of(" \t", pos1);
      spos.y = std::atoi(start.substr(pos, pos1 - pos).data());
      _spacgum.push_back(spos);
    }
}

void arcade::MapData::setBackgroundTexture(std::string const& path)
{
  size_t pos = path.find_first_of(" \t");
  if (pos != std::string::npos)
    _background = path.substr(pos + 1);
}
