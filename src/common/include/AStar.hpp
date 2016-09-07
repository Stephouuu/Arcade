//
// AStar.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/common
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 26 18:56:47 2016 stephane galibert
// Last update Sun Mar 27 14:12:26 2016 stephane galibert
//

#ifndef _ASTAR_HPP_
# define _ASTAR_HPP_

# include <iostream>
# include <string>
# include <cmath>
# include <vector>
# include <utility>
# include <list>
# include <queue>
# include <stdexcept>

# include "Map.hpp"
# include "Utility.hpp"
# include "Protocol.hpp"

namespace arcade
{
  struct Node
  {
    Vector2u parent;
    Vector2u pos;
    float g;
    float h;
    float f;
    Node &operator=(Node const& other)
    {
      parent = other.parent;
      pos = other.pos;
      g = other.g;
      h = other.h;
      f = other.f;
      return *this;
    }
  };

  class AStar
  {
  public:
    AStar(void);
    ~AStar(void);
    Vector2u getNextPath(Map &map, Vector2u const& p1, Vector2u const& p2);
  private:
    void addAdjCase(arcade::Map &map, Node const& p, Vector2u const& obj);
    float getDistance(Vector2u const& p1, Vector2u const& p2) const;
    bool findInList(Node const& p, std::vector<Node> &list) const;
    void addInList(Node node, std::vector<Node> &list);
    void addInCloseList(Node const& p);
    Node &getNode(Vector2u const& p, std::vector<Node> &list) const;
    Node getBestNode(std::vector<Node> &list) const;
    void retrievePath(Vector2u const& begin);
    std::vector<Node> _listClose;
    std::vector<Node> _listOpen;
    Node _end;
    std::list<Vector2u> _path;
  };
}

#endif /* !_ASTAR_HPP_ */
