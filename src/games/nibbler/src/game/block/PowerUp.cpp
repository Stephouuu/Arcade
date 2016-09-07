
//
// PowerUp.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 11 16:27:15 2016 stephane galibert
// Last update Fri Apr  1 16:42:19 2016 stephane galibert
//

#include "PowerUp.hpp"

arcade::PowerUp::PowerUp(void)
{
  _delta_bonus = 0;
}

arcade::PowerUp::~PowerUp(void)
{
  for (auto &it : _items)
    delete (it);
}

void arcade::PowerUp::refresh(float const delta, arcade::Map &map)
{
  if (isEmptyFood(map))
    generateFood(map);

  _delta_bonus += delta;
  if (_delta_bonus > 5000 && _bonus.size() < 3)
    {
      generateBonus(map);
      _delta_bonus = (size_t)_delta_bonus % 1000;
    }

  for (auto &it : _items)
    it->update(delta);
  for (auto &it : _bonus)
    it->update(delta);
}

void arcade::PowerUp::loadTexture(void)
{
  try {
    {
      Drawable *bouloute = new Drawable;
      bouloute->type = DrawableType::DRAWABLE_TEXTURE;
      bouloute->texture = new FileCache("rsrc/nibbler/texture/bouloute.png");
      _texture.push_back(bouloute);
    }
    {
      Drawable *bnoir = new Drawable;
      bnoir->type = DrawableType::DRAWABLE_TEXTURE;
      bnoir->texture = new FileCache("rsrc/nibbler/texture/bouftonnoir.png");
      _texture.push_back(bnoir);
    }
    {
      Drawable *boufette = new Drawable;
      boufette->type = DrawableType::DRAWABLE_TEXTURE;
      boufette->texture = new FileCache("rsrc/nibbler/texture/boufette.png");
      _texture.push_back(boufette);
    }
    {
      Drawable *pspeed1 = new Drawable;
      pspeed1->type = DrawableType::DRAWABLE_TEXTURE;
      pspeed1->texture = new FileCache("rsrc/nibbler/texture/potion_speed1.png");
      _texture.push_back(pspeed1);
    }
    {
      Drawable *pspeed2 = new Drawable;
      pspeed2->type = DrawableType::DRAWABLE_TEXTURE;
      pspeed2->texture = new FileCache("rsrc/nibbler/texture/potion_speed2.png");
      _texture.push_back(pspeed2);
    }
    {
      Drawable *pscore1 = new Drawable;
      pscore1->type = DrawableType::DRAWABLE_TEXTURE;
      pscore1->texture = new FileCache("rsrc/nibbler/texture/potion_score1.png");
      _texture.push_back(pscore1);
    }
    {
      Drawable *pscore2 = new Drawable;
      pscore2->type = DrawableType::DRAWABLE_TEXTURE;
      pscore2->texture = new FileCache("rsrc/nibbler/texture/potion_score2.png");
      _texture.push_back(pscore2);
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
  for (auto &it : _bonus)
    if (pos.x == it->getPos().x && pos.y == it->getPos().y)
      return (it->getCurrentFrame());
  return (NULL);
}

void arcade::PowerUp::checkCollisions(arcade::Player& player, arcade::Map &map)
{
  std::list<Vector2u> const& playerPos = player.getPositions();
  for (std::list<IItems *>::iterator it = _items.begin() ;
       it != _items.end() ;
       ++it)
    if ((*it)->getPos().x == playerPos.cbegin()->x
	&& (*it)->getPos().y == playerPos.cbegin()->y)
      {
	(*it)->affectPlayer(player, map);
	delete (*it);
	it = _items.erase(it);
      }
  for (std::list<IItems *>::iterator it = _bonus.begin() ;
       it != _bonus.end() ;
       ++it)
    if ((*it)->getPos().x == playerPos.cbegin()->x
	&& (*it)->getPos().y == playerPos.cbegin()->y)
      {
	(*it)->affectPlayer(player, map);
	delete (*it);
	it = _bonus.erase(it);
      }
}

bool arcade::PowerUp::isEmptyFood(Map &map)
{
  (void)map;
  return (_items.size() == 0);
}

void arcade::PowerUp::generateFood(arcade::Map &map)
{
  size_t type = 0;

  type = _generator(0, 100);
  if (type > 90)
    generateRandom(map);
  else if (type > 70)
    generateSuper(map);
  else
    generateNormal(map);
}

void arcade::PowerUp::generateBonus(arcade::Map &map)
{
  size_t random = 0;

  random = _generator(0, 100);
  if (random > 80)
    generateSpeedBonus(map);
  else if (random > 60)
    generateScoreBonus(map);
}

void arcade::PowerUp::generateNormal(arcade::Map &map)
{
  Vector2u random;
  do {
    random.x = _generator(0, map.width - 1);
    random.y = _generator(0, map.height - 1);
  } while (map.map[random.y][random.x] != TileType::EMPTY);
  map.map[random.y][random.x] = TileType::POWERUP;
  Food *food = new Food(random, _texture[0]);
  food->addFrame(_texture[0]);
  _items.push_back(food);
}

void arcade::PowerUp::generateSuper(arcade::Map &map)
{
  Vector2u random;
  do {
    random.x = _generator(0, map.width - 1);
    random.y = _generator(0, map.height - 1);
  } while (map.map[random.y][random.x] != TileType::EMPTY);
  map.map[random.y][random.x] = TileType::POWERUP;
  SuperFood *food = new SuperFood(random, _texture[1]);
  food->addFrame(_texture[1]);
  _items.push_back(food);
}

void arcade::PowerUp::generateRandom(arcade::Map &map)
{
  Vector2u random;
  do {
    random.x = _generator(0, map.width - 1);
    random.y = _generator(0, map.height - 1);
  } while (map.map[random.y][random.x] != TileType::EMPTY);
  map.map[random.y][random.x] = TileType::POWERUP;
  Random *ran = new Random(random, _texture[0]);
  ran->addFrame(_texture[2]);
  _items.push_back(ran);
}

void arcade::PowerUp::generateSpeedBonus(arcade::Map &map)
{
  Vector2u random;
  do {
    random.x = _generator(0, map.width - 1);
    random.y = _generator(0, map.height - 1);
  } while (map.map[random.y][random.x] != TileType::EMPTY);
  map.map[random.y][random.x] = TileType::OTHER;
  Speed *speed = new Speed(random);
  speed->addFrame(_texture[3]);
  speed->addFrame(_texture[4]);
  _bonus.push_back(speed);
}

void arcade::PowerUp::generateScoreBonus(arcade::Map &map)
{
  Vector2u random;
  do {
    random.x = _generator(0, map.width - 1);
    random.y = _generator(0, map.height - 1);
  } while (map.map[random.y][random.x] != TileType::EMPTY);
  map.map[random.y][random.x] = TileType::OTHER;
  Score *score = new Score(random);
  score->addFrame(_texture[5]);
  score->addFrame(_texture[6]);
  _bonus.push_back(score);
}
