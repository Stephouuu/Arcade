//
// PowerUp.cpp for arcade in /home/galibe_s/rendu/cpp_arcadeold/src/games/pacman
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Thu Mar 24 12:57:46 2016 stephane galibert
// Last update Thu Mar 31 22:25:38 2016 stephane galibert
//

#include "PowerUp.hpp"

arcade::PowerUp::PowerUp(void)
{

}

arcade::PowerUp::~PowerUp(void)
{
  for (auto &it : _items)
    delete (it);
}

void arcade::PowerUp::refresh(float const delta, arcade::Map &map)
{
  (void)map;
  for (auto &it : _items)
    it->update(delta);
}

void arcade::PowerUp::loadTexture(void)
{
  try {
    {
      Drawable *speed1 = new Drawable;
      speed1->type = DrawableType::DRAWABLE_TEXTURE;
      speed1->texture = new FileCache("rsrc/nibbler/texture/potion_speed1.png");
      _texture.push_back(speed1);
    }
    {
      Drawable *speed2 = new Drawable;
      speed2->type = DrawableType::DRAWABLE_TEXTURE;
      speed2->texture = new FileCache("rsrc/nibbler/texture/potion_speed2.png");
      _texture.push_back(speed2);
    }
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

arcade::Drawable const * arcade::PowerUp::getTexture(arcade::Vector2u const& pos) const
{
  for (auto &it : _items)
    if (pos.x == it->getPos().x && pos.y == it->getPos().y)
      return (it->getCurrentFrame());
  return (NULL);
}

void arcade::PowerUp::checkCollisions(arcade::Player& player,
				      std::vector<Ghost *> &ghosts,
				      arcade::Map &map)
{
  std::list<Vector2u> const& playerPos = player.getPositions();
  for (std::list<IItems *>::iterator it = _items.begin() ;
       it != _items.end() ;
       ++it)
    if ((*it)->getPos().x == playerPos.cbegin()->x
	&& (*it)->getPos().y == playerPos.cbegin()->y)
      {
	(*it)->affectPlayer(player, ghosts, map);
	delete (*it);
	it = _items.erase(it);
      }
  if (_items.size() == 0)
    player.setWin(true);
}

bool arcade::PowerUp::add(arcade::IItems *item)
{
  for (auto &it : _items)
    if (item->getPos() == it->getPos())
      return (false);
  _items.push_back(item);
  return (true);
}
