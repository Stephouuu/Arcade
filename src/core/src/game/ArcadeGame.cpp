//
// ArcadeGame.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 18 03:16:25 2016 stephane galibert
// Last update Thu Mar 31 22:11:01 2016 stephane galibert
//

#include "ArcadeGame.hpp"

arcade::ArcadeGame::ArcadeGame(arcade::Vector2u const& dim, arcade::IGames *game)
{
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::P, InputT::None),
			       std::bind(&arcade::ArcadeGame::pause, this)));
  _dim = dim;
  _game = game;
  _delta_death = 0;
  _delta_start = DELAY_GAMEINTRO;
  _delta_win = 0;
  _death_message = "Game Over";
  _start_message = game->getGamesName() + ": Let's go ";
  _win_message = "Game Win";
  _pause = false;
}

arcade::ArcadeGame::~ArcadeGame(void)
{
  if (_game)
    delete (_game);
}

void arcade::ArcadeGame::setLibGames(IGames *game)
{
  if (_game)
    delete (_game);
  _game = game;
}

void arcade::ArcadeGame::init(void)
{
  if (_game)
    _game->loadTexture();
}

bool arcade::ArcadeGame::input(arcade::InputT const in)
{
  if (_input.find(in) != _input.end())
    {
      _input[in]();
      return (true);
    }
  if (_game && !_pause && _delta_start < 0)
    return (_game->input(in));
  return (false);
}

void arcade::ArcadeGame::update(float const delta)
{
  if (_game && !_pause)
    {
      if (_delta_start < 0)
	_game->updateGame(delta);
      if (_delta_start > -1)
	_delta_start -= delta;
      if (!_game->isPlayerAlive() && _delta_death < DELAY_GAMEOVER)
	_delta_death += delta;
      if (_game->isPlayerWin() && _delta_win < DELAY_GAMEWIN)
	_delta_win += delta;
    }
}

void arcade::ArcadeGame::restart(void)
{
  _delta_start = DELAY_GAMEINTRO;
  _delta_death = 0;
  _delta_win = 0;
  if (_game)
    _game->restart();
}

void arcade::ArcadeGame::display(arcade::IGraphic *&graphic)
{
  if (isInGame())
    {
      if (_pause)
	display_pause(graphic);
      else
	display_game(graphic);
    }
}

bool arcade::ArcadeGame::isInGame(void) const
{
  return (_game && ((_game->isPlayerAlive() || (!_game->isPlayerAlive() && _delta_death < DELAY_GAMEOVER))
		    && (!_game->isPlayerWin() || (_game->isPlayerWin() && _delta_win < DELAY_GAMEWIN))));
}

void arcade::ArcadeGame::setPlayerName(std::string const& name)
{
  if (_game)
    _game->setPlayerName(name);
}

std::string arcade::ArcadeGame::getPlayerName(void) const
{
  if (_game)
    return (_game->getPlayerName());
  return ("");
}

std::string arcade::ArcadeGame::getGameName(void) const
{
  if (_game)
    return (_game->getGamesName());
  return ("");
}

arcade::Vector2u arcade::ArcadeGame::getGameDimension(void) const
{
  if (_game)
    return (_game->getDimension());
  return (Vector2u(0, 0));
}

arcade::Vector2u arcade::ArcadeGame::getGameScale(void) const
{
  if (_game)
    return (_game->getScale());
  return (Vector2u(0, 0));
}

size_t arcade::ArcadeGame::getScore(void) const
{
  if (_game)
    return (_game->getScore());
  return (0);
}

void arcade::ArcadeGame::saveScore(void)
{
  if (_game)
    {
      std::ofstream ofs("score.txt", std::ofstream::out | std::ofstream::app);
      if (ofs)
	{
	  ofs << _game->getPlayerName() << "=" << _game->getScore() << std::endl;
	  ofs.close();
	}
      else
	std::cerr << "Warning: cannot create score.txt" << std::endl;
    }
}

void arcade::ArcadeGame::display_intro(arcade::IGraphic *&graphic)
{
  Vector2u pos;
  std::string message = _start_message + _game->getPlayerName() + " !";
  Drawable dTexture;
  Drawable dRgba;
  Drawable dText;

  dTexture = _game->getBackgroundTexture();

  dRgba.type = DrawableType::DRAWABLE_RGBA;
  dRgba.pos = Vector2u(0, 0);
  dRgba.size = _game->getDimension() * _game->getScale();
  dRgba.rgba = RGBA(0, 0, 0, (float)(_delta_start / 2000.f) * 255.f);

  pos.x = ((_game->getDimension().x * _game->getScale().x) / 2) - ((message.size() / 2) * 20);
  pos.y = ((_game->getDimension().y * _game->getScale().y) / 2) - 20;
  dText.type = DrawableType::DRAWABLE_TEXT;
  dText.pos = pos;
  dText.csize = 40;
  dText.text = message;
  dText.rgba = RGBA(255, 255, 255, 255);

  graphic->draw(dTexture);

  for (size_t i = 0 ; i < _game->getMap().height ; ++i)
    for (size_t j = 0 ; j < _game->getMap().width ; ++j)
      if (_game->getMap().map[i][j] != TileType::EMPTY)
	{
	  Drawable const* dTexture = _game->getTexture(Vector2u(j, i));
	  if (dTexture)
	    graphic->draw(*dTexture);
	}

  graphic->draw(dRgba);
  graphic->draw(dText);
}

void arcade::ArcadeGame::display_game(arcade::IGraphic *&graphic)
{
  std::string score;
  Drawable dTexture;
  Drawable dTextName;
  Drawable dTextScore;

  dTexture.type = DrawableType::DRAWABLE_TEXTURE;
  if (_delta_start > -1)
    display_intro(graphic);
  else if (!_game->isPlayerAlive() && _delta_death < DELAY_GAMEOVER)
    display_gameover(graphic);
  else if (_game->isPlayerWin() && _delta_win < DELAY_GAMEWIN)
    display_gamewin(graphic);
  else
    {
      dTexture = _game->getBackgroundTexture();
      graphic->draw(dTexture);
      score = std::to_string(_game->getScore());
      for (size_t i = 0 ; i < _game->getMap().height ; ++i)
	for (size_t j = 0 ; j < _game->getMap().width ; ++j)
	  if (_game->getMap().map[i][j] != TileType::EMPTY)
	    {
	      Drawable const* dTexture = _game->getTexture(Vector2u(j, i));
	      if (dTexture)
		graphic->draw(*dTexture);
	    }
      if (_game->isPlayerAlive())
	{
	  std::vector<Drawable> const& event = _game->getDrawableEvent();
	  for (auto &it : event)
	    graphic->draw(it);
	}
      dTextName.type = DrawableType::DRAWABLE_TEXT;
      dTextName.csize = 20;
      dTextName.pos = Vector2u(20, 870);
      dTextName.text = _game->getPlayerName();
      dTextName.rgba = RGBA(255, 255, 255, 255);
      dTextName.pos = Vector2u(40, _game->getDimension().y * _game->getScale().y);
      dTextName.pos.y -= dTextName.csize;

      dTextScore.type = DrawableType::DRAWABLE_TEXT;
      dTextScore.csize = 20;
      dTextScore.text = "Score: " + score;
      dTextScore.rgba = RGBA(255, 255, 255, 255);
      dTextScore.pos = _game->getDimension() * _game->getScale();
      dTextScore.pos.x -= (dTextScore.text.size() * (dTextScore.csize)) - 40;
      dTextScore.pos.y -= dTextScore.csize;

      graphic->draw(dTextScore);
      graphic->draw(dTextName);
    }
}

void arcade::ArcadeGame::display_pause(arcade::IGraphic *&graphic)
{
  std::string score = std::to_string(_game->getScore());
  Drawable dTexture;
  Drawable dTextPause;
  Drawable dTextScore;

  dTexture = _game->getBackgroundTexture();

  dTextPause.type = DrawableType::DRAWABLE_TEXT;
  dTextPause.pos = Vector2u(370, 430);
  dTextPause.csize = 50;
  dTextPause.text = "Pause";
  dTextPause.rgba = RGBA(255, 255, 255, 255);

  dTextScore.type = DrawableType::DRAWABLE_TEXT;
  dTextScore.pos = Vector2u(387, 490);
  dTextScore.csize = 20;
  dTextScore.text = "Score: " + score;
  dTextScore.rgba = RGBA(255, 255, 255, 255);

  graphic->draw(dTexture);

  for (size_t i = 0 ; i < _game->getMap().height ; ++i)
    for (size_t j = 0 ; j < _game->getMap().width ; ++j)
      if (_game->getMap().map[i][j] != TileType::EMPTY)
	{
	  Drawable const* dTexture = _game->getTexture(Vector2u(j, i));
	  if (dTexture)
	    graphic->draw(*dTexture);
	}

  graphic->draw(dTextPause);
  graphic->draw(dTextScore);
}

void arcade::ArcadeGame::display_gameover(arcade::IGraphic *&graphic)
{
  Drawable dTexture;
  Drawable dRgba;
  Drawable dText;

  dTexture = _game->getBackgroundTexture();

  dRgba.type = DrawableType::DRAWABLE_RGBA;
  dRgba.pos = Vector2u(0, 0);
  dRgba.size = _game->getDimension() * _game->getScale();
  if (_delta_death < 1500)
    dRgba.rgba = RGBA(0, 0, 0, (float)(_delta_death / 1500.f) * 255.f);
  else
    dRgba.rgba = RGBA(0, 0, 0, 255);

  dText.type = DrawableType::DRAWABLE_TEXT;
  dText.pos = Vector2u(300, 430);
  dText.csize = 50;
  dText.text = _death_message;
  dText.rgba = RGBA(255, 255, 255, 255);

  graphic->draw(dTexture);
  graphic->draw(dRgba);

  for (size_t i = 0 ; i < _game->getMap().height ; ++i)
    for (size_t j = 0 ; j < _game->getMap().width ; ++j)
      if (_game->getMap().map[i][j] != TileType::EMPTY)
	{
	  Drawable const * dTexture = _game->getTexture(Vector2u(j, i));
	  if (dTexture)
	    graphic->draw(*dTexture);
	}

  graphic->draw(dText);
}

void arcade::ArcadeGame::display_gamewin(arcade::IGraphic *&graphic)
{
  Drawable dTexture;
  Drawable dRgba;
  Drawable dText;

  dTexture = _game->getBackgroundTexture();

  dRgba.type = DrawableType::DRAWABLE_RGBA;
  dRgba.pos = Vector2u(0, 0);
  dRgba.size = _game->getDimension() * _game->getScale();
  if (_delta_win < 1500)
    dRgba.rgba = RGBA(0, 0, 0, (float)(_delta_win / 1500.f) * 255.f);
  else
    dRgba.rgba = RGBA(0, 0, 0, 255);

  dText.type = DrawableType::DRAWABLE_TEXT;
  dText.pos = Vector2u(300, 430);
  dText.csize = 50;
  dText.text = _win_message;
  dText.rgba = RGBA(255, 255, 255, 255);

  graphic->draw(dTexture);
  graphic->draw(dRgba);

  for (size_t i = 0 ; i < _game->getMap().height ; ++i)
    for (size_t j = 0 ; j < _game->getMap().width ; ++j)
      if (_game->getMap().map[i][j] != TileType::EMPTY)
	{
	  Drawable const * dTexture = _game->getTexture(Vector2u(j, i));
	  if (dTexture)
	    graphic->draw(*dTexture);
	}

  graphic->draw(dText);
}

void arcade::ArcadeGame::pause(void)
{
  _pause = !_pause;
}
