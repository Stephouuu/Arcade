//
// MapData.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/games/pacman
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 31 23:06:48 2016 stephane galibert
// Last update Fri Apr  1 00:22:46 2016 stephane galibert
//

#ifndef _MAPDATA_HPP_
# define _MAPDATA_HPP_

# include <iostream>
# include <string>
# include <map>
# include <functional>
# include <vector>
# include <fstream>

# include "Exception.hpp"
# include "Utility.hpp"
# include "Map.hpp"

namespace arcade
{
  class MapData
  {
  public:
    static const std::string PLAYER;
    static const std::string BLINKY;
    static const std::string PINKY;
    static const std::string INKY;
    static const std::string CLYDE;
  public:
    MapData(void);
    ~MapData(void);
    void parseMapData(std::string const& filename, Map &map);
    bool isLink(Vector2u const& pos) const;
    Vector2u const& getLink(Vector2u const& link) const;
    Vector2u const& getPosStart(std::string const& key) const;
    std::string const& getBackground(void) const;
    std::vector<Vector2u> const& getSPacGum(void) const;
    std::vector<Vector2u> const& getPacGum(void) const;
  private:
    std::map<std::string, std::function<void(std::string const&)> > _parser;
    void parseMap(std::ifstream &ifs, Map &map);
    void parseLink(std::string const& data);
    void setPlayerStart(std::string const& start);
    void setBlinkyStart(std::string const& start);
    void setPinkyStart(std::string const& start);
    void setInkyStart(std::string const& start);
    void setClydeStart(std::string const& start);
    void setSPacGum(std::string const& start);
    void setBackgroundTexture(std::string const& path);

    std::string _background;
    std::map<Vector2u, Vector2u> _link;
    std::map<std::string, Vector2u> _positions;
    std::vector<Vector2u> _spacgum;
    std::vector<Vector2u> _pacgum;
  };
}

#endif /* !_MAPDATA_HPP_ */
