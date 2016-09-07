//
// Core.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Mar  9 15:15:02 2016 stephane galibert
// Last update Wed Mar 30 14:32:52 2016 stephane galibert
//

#include "Core.hpp"

const std::string arcade::Core::GamesConfig = "libgames";
const std::string arcade::Core::GraphConfig = "libgraph";

arcade::Core::Core(Vector2u const& gamedim)
{
  _update[GameState::MenuStatus] = std::bind(&arcade::Core::up_menu, this,
					     std::placeholders::_1, std::placeholders::_2);
  _update[GameState::GameStatus] = std::bind(&arcade::Core::up_game, this,
					     std::placeholders::_1, std::placeholders::_2);
  _gamedim = gamedim;
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Escape, InputT::None),
			       std::bind(&arcade::Core::closeWindow, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::K2, InputT::None),
			       std::bind(&arcade::Core::prevLibGraph, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::K3, InputT::None),
			       std::bind(&arcade::Core::nextLibGraph, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::K4, InputT::None),
			       std::bind(&arcade::Core::prevLibGame, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::K5, InputT::None),
			       std::bind(&arcade::Core::nextLibGame, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::K8, InputT::None),
			       std::bind(&arcade::Core::restartGame, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::K9, InputT::None),
  			       std::bind(&arcade::Core::goToMenu, this)));
  _menu = new ArcadeMenu(gamedim);
  _game = NULL;
  _graphic = NULL;
  _state = GameState::MenuStatus;
}

arcade::Core::~Core(void)
{
  if (_graphic)
    delete (_graphic);
  if (_game)
    delete (_game);
  if (_menu)
    delete (_menu);
}

void arcade::Core::init(std::string const& lib, std::string const& conf)
{
  LibConfigFile libConfig(conf);
  try {
    signal(SIGINT, exit_arcade);
    libConfig.updateConfig();
    _gamesPath = libConfig.getLibsPath(GamesConfig);
    _graphPath = libConfig.getLibsPath(GraphConfig);
    _menu->setCurrentGraph(lib);
    _menu->createGames(_gamesPath);
    _menu->createGraph(_graphPath);
    _menu->createScore(_scoreData);
    _menu->init();
    _currentGraph = lib;
    setLibGraphic(lib);
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

void arcade::Core::setLibGraphic(std::string const& lib)
{
  void *entry = NULL;

  _loader[0].setLibName(lib);
  try {
    _loader[0].load();
    entry = _loader[0].sym("Entry");
    _graphic = ((arcade::IGraphic *(*)(void))(entry))();
    _graphic->setWindowSize(_gamedim * _gamedim);
    if (_game)
      {
	_graphic->setTitleWindow(_game->getGameName());
	_graphic->setWindowSize(_game->getGameDimension() * _game->getGameScale());
      }
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

void arcade::Core::setLibGames(std::string const& lib)
{
  void *entry = NULL;

  _loader[1].setLibName(lib);
  try {
    _loader[1].load();
    entry = _loader[1].sym("Entry");
    _game = new ArcadeGame(_gamedim, ((arcade::IGames *(*)(void))(entry))());
    _game->init();
    _game->restart();
    if (_graphic)
      {
	_graphic->setWindowSize(_game->getGameDimension() * _game->getGameScale());
	_graphic->setTitleWindow(_game->getGameName());
      }
    if (_menu)
      _game->setPlayerName(_menu->getUsername());
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

bool arcade::Core::play(void)
{
  InputT in;
  float elapsed = 0;

  if (!_graphic)
    return (false);
  goToMenu();
  while (_graphic->isOpen())
    {
      elapsed = _clock.restart() * 1000;
      in = _graphic->checkInput();
      if (_input.find(in) != _input.end())
	_input[in]();
      try {
	if (_update.find(_state) != _update.end())
	  _update[_state](elapsed, in);
      } catch (ArcadeError const& e) {
	throw (e);
      }
    }
  return (true);
}

void arcade::Core::up_menu(float const delta, arcade::InputT const in)
{
  _menu->input(in);
  _menu->update(delta);
  _graphic->clearScreen();
  _menu->display(_graphic);
  _graphic->display();
  if (_menu->hasStarted())
    {
      _state = GameState::GameStatus;
      if (_game)
	{
	  delete (_game);
	  _game = NULL;
	}
      if (_graphic)
	{
	  delete (_graphic);
	  _graphic = NULL;
	}
      try {
	_currentGraph = _menu->getGraph();
	_currentGames = _menu->getGames();
	setLibGraphic(_currentGraph);
	setLibGames(_currentGames);
      } catch (ArcadeError const& e) {
	throw (e);
      }
    }
}

void arcade::Core::up_game(float const delta, arcade::InputT const in)
{
  _game->input(in);
  _game->update(delta);
  _graphic->clearScreen();
  _game->display(_graphic);
  _graphic->display();
  if (!_game->isInGame())
    {
      _game->saveScore();
      goToMenu();
    }
}

void arcade::Core::closeWindow(void)
{
  if (_graphic)
    _graphic->close();
}

void arcade::Core::prevLibGraph(void)
{
  std::vector<std::string>::const_iterator it = _graphPath.cbegin();
  while (it != _graphPath.cend() && *it != _currentGraph)
    ++it;
  if (it != _graphPath.cend())
    {
      if (it == _graphPath.cbegin())
	it = --_graphPath.cend();
      else
	--it;
    }
  else
    it = _graphPath.cbegin();
  _currentGraph = *it;
  if (_graphic)
    delete (_graphic);
  setLibGraphic(_currentGraph);
}

void arcade::Core::nextLibGraph(void)
{
  std::vector<std::string>::const_iterator it = _graphPath.cbegin();
  while (it != _graphPath.cend() && *it != _currentGraph)
    ++it;
  if (it != _graphPath.cend())
    {
      ++it;
      if (it == _graphPath.cend())
	it = _graphPath.cbegin();
    }
  else
    it = _graphPath.cbegin();
  if (_graphic)
    delete (_graphic);
  _currentGraph = *it;
  setLibGraphic(_currentGraph);
}

void arcade::Core::prevLibGame(void)
{
  if (_game && _state == GameState::GameStatus)
    {
      std::vector<std::string>::const_iterator it = _gamesPath.cbegin();
      while (it != _gamesPath.cend() && *it != _currentGames)
	++it;
      if (it != _gamesPath.cend())
	{
	  if (it == _gamesPath.cbegin())
	    it = --_gamesPath.cend();
	  else
	    --it;
	}
      else
	it = _gamesPath.cbegin();
      _currentGames = *it;
      if (_game)
	delete (_game);
      setLibGames(_currentGames);
    }
}

void arcade::Core::nextLibGame(void)
{
  if (_game && _state == GameState::GameStatus)
    {
      std::vector<std::string>::const_iterator it = _gamesPath.cbegin();
      while (it != _gamesPath.cend() && *it != _currentGames)
	++it;
      if (it != _gamesPath.cend())
	{
	  ++it;
	  if (it == _gamesPath.cend())
	    it = _gamesPath.cbegin();
	}
      else
	it = _gamesPath.cbegin();
      _currentGames = *it;
      if (_game)
	delete (_game);
      setLibGames(_currentGames);
    }
}

void arcade::Core::restartGame(void)
{
  if (_game && _state == GameState::GameStatus)
    {
      _game->restart();
      if (_menu)
	_game->setPlayerName(_menu->getUsername());
    }
}

void arcade::Core::goToMenu(void)
{
  if (_state == GameState::GameStatus || !_game)
    {
      loadScore();
      _state = GameState::MenuStatus;
      _menu->setStarted(false);
      _menu->refreshScore(_scoreData);
      _menu->resetWindowSize(_graphic);
    }
}

void arcade::Core::loadScore(void)
{
  std::ifstream ifs("score.txt");
  std::string line;
  if (ifs)
    {
      _scoreData.erase(_scoreData.begin(), _scoreData.end());
      while (std::getline(ifs, line))
	_scoreData.push_back(line);
      ifs.close();
    }
}

void exit_arcade(int n)
{
  (void)n;
  std::cout << std::endl << "receiving signal SIGINT" << std::endl;
  std::cout << "exit" << std::endl;
  exit(1);
}
