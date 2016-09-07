//
// Core.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Mar  9 15:13:54 2016 stephane galibert
// Last update Wed Mar 30 14:30:19 2016 stephane galibert
//

#ifndef _CORE_HPP_
# define _CORE_HPP_

# include <iostream>
# include <string>
# include <map>
# include <functional>
# include <signal.h>

# include "SoLoader.hpp"
# include "IGraphic.hpp"
# include "Utility.hpp"
# include "Chrono.hpp"
# include "GameState.hpp"
# include "Protocol.hpp"
# include "Map.hpp"
# include "FileCache.hpp"
# include "LibConfigFile.hpp"
# include "ArcadeMenu.hpp"
# include "ArcadeGame.hpp"

namespace arcade
{
  class Core
  {
  public:
    static const std::string GamesConfig;
    static const std::string GraphConfig;
  public:
    Core(Vector2u const& gamedim);
    ~Core(void);

    void init(std::string const& lib, std::string const& conf);
    void setLibGraphic(std::string const& lib);
    void setLibGames(std::string const& lib);
    bool play(void);
  private:
    std::map<GameState, std::function<void(float const, InputT const)> > _update;
    void up_menu(float const delta, InputT const in);
    void up_game(float const delta, InputT const in);

    std::map<InputT, std::function<void(void)> > _input;
    void closeWindow(void);
    void prevLibGraph(void);
    void nextLibGraph(void);
    void prevLibGame(void);
    void nextLibGame(void);
    void restartGame(void);
    void goToMenu(void);

    void loadScore(void);

    Chronometer _clock;
    GameState _state;
    Vector2u _gamedim;

    SoLoader _loader[2];
    IGraphic *_graphic;

    std::string _currentGames;
    std::string _currentGraph;
    std::vector<std::string> _gamesPath;
    std::vector<std::string> _graphPath;
    std::vector<std::string> _scoreData;

    ArcadeMenu *_menu;
    ArcadeGame *_game;
  };
}

void exit_arcade(int n);

#endif /* !_CORE_HPP_ */
