//
// AStar.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/common
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sat Mar 26 18:58:04 2016 stephane galibert
// Last update Sun Mar 27 14:04:46 2016 stephane galibert
//

#include "AStar.hpp"

arcade::AStar::AStar(void)
{

}

arcade::AStar::~AStar(void)
{

}

arcade::Vector2u arcade::AStar::getNextPath(arcade::Map &map,
					    arcade::Vector2u const& p1,
					    arcade::Vector2u const& p2)
{
  Node begin;
  begin.pos = p1;
  begin.f = 0;
  begin.h = 0;
  begin.g = 0;
  if (p1 == p2)
    return (p2);
  addInList(begin, _listOpen);
  while (!_listOpen.empty())
    {
      Node u = getBestNode(_listOpen);
      if (u.pos == p2)
	{
	  _end = u;
	  addInCloseList(u);
	  retrievePath(begin.pos);
	  return (*(_path.cbegin()));
	}
      addAdjCase(map, u, p2);
      addInCloseList(u);
    }
  return (p1);
}

void arcade::AStar::addAdjCase(arcade::Map &map, arcade::Node const& u,
			       arcade::Vector2u const& objectif)
{
  Vector2u current;
  for (size_t i = u.pos.x - 1 ; i <= u.pos.x + 1 ; ++i)
    for (size_t j = u.pos.y - 1 ; j <= u.pos.y + 1 ; ++j)
      {
	Node v;
	v.pos = Vector2u(i, j);
	if (j < map.height && i < map.width
	    && map.map[j][i] != TileType::BLOCK
	    && map.map[j][i] != TileType::EVIL_DUDE
	    && u.pos != v.pos
	    && (i == u.pos.x || j == u.pos.y))
	  {
	    if (!findInList(v, _listClose) && !findInList(v, _listOpen))
	      {
		v.parent = u.pos;
		v.g = u.g + 10;
		v.h = getDistance(v.pos, objectif);
		v.f = v.g + v.h;
		addInList(v, _listOpen);
	      }
	  }
      }
}

float arcade::AStar::getDistance(arcade::Vector2u const& p1,
				 arcade::Vector2u const& p2) const
{
  return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

bool arcade::AStar::findInList(Node const& p,
			       std::vector<arcade::Node> &list) const
{
  for (auto &it : list)
    if (it.pos == p.pos)
      return (true);
  return (false);
}

void arcade::AStar::addInList(arcade::Node node, std::vector<arcade::Node> &list)
{
  list.push_back(node);
}

void arcade::AStar::addInCloseList(arcade::Node const& p)
{
  addInList(p, _listClose);
  std::vector<Node>::iterator it = _listOpen.begin();
  while (it != _listOpen.end())
    {
      if (it->pos == p.pos)
	it = _listOpen.erase(it);
      else
	++it;
    }
}

arcade::Node &arcade::AStar::getNode(arcade::Vector2u const& p,
				     std::vector<arcade::Node> &list) const
{
  for (auto &it : list)
    if (it.pos == p)
      return it;
  throw std::runtime_error("node not found");
}

arcade::Node arcade::AStar::getBestNode(std::vector<Node> &list) const
{
  float min = list.cbegin()->f;
  Node pos = *list.cbegin();
  for (auto &it : list)
    if (it.f < min)
      {
	min = it.f;
	pos = it;
      }
  return (pos);
}

void arcade::AStar::retrievePath(arcade::Vector2u const& begin)
{
  Node &node = getNode(_end.pos, _listClose);
  Vector2u prev = node.parent;
  Vector2u pos = node.pos;
  _path.push_front(pos);
  while (prev != begin)
    {
      pos = prev;
      _path.push_front(prev);
      node = getNode(node.parent, _listClose);
      prev = node.parent;
    }
}
