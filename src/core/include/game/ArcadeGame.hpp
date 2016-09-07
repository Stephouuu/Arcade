//
// ArcadeGame.hpp for arcae in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Mar 18 03:00:49 2016 stephane galibert
// Last update Fri Mar 25 12:55:09 2016 stephane galibert
//

#ifndef _ARCADEGAME_HPP_
# define _ARCADEGAME_HPP_

# include <iostream>
# include <string>
# include <map>
# include <functional>
# include <fstream>

# include "Drawable.hpp"
# include "IGames.hpp"
# include "Exception.hpp"
# include "IGraphic.hpp"
# include "FileCache.hpp"
# include "Utility.hpp"
# include "Input.hpp"

namespace arcade
{
  class ArcadeGame
  {
  public:
    static const int DELAY_GAMEINTRO = 2000;
    static const int DELAY_GAMEOVER = 2000;
    static const int DELAY_GAMEWIN = 2000;
  public:
    ArcadeGame(Vector2u const& dim, IGames *game);
    ArcadeGame(void);
    ~ArcadeGame(void);

    void setLibGames(IGames *games);
    void init(void);
    bool input(InputT const in);
    void update(float const delta);
    void restart(void);
    void display(IGraphic *&graphic);
    bool isInGame(void) const;
    void setPlayerName(std::string const& name);
    std::string getPlayerName(void) const;
    std::string getGameName(void) const;
    Vector2u getGameDimension(void) const;
    Vector2u getGameScale(void) const;
    size_t getScore(void) const;
    void saveScore(void);
  private:
    void display_intro(IGraphic *&graphic);
    void display_game(IGraphic *&graphic);
    void display_pause(IGraphic *&graphic);
    void display_gameover(IGraphic *&graphic);
    void display_gamewin(IGraphic *&graphic);

    std::map<InputT, std::function<void(void)> > _input;
    void pause(void);

    Vector2u _dim;
    IGames *_game;
    int _delta_death;
    int _delta_start;
    int _delta_win;
    std::string _death_message;
    std::string _start_message;
    std::string _win_message;
    bool _pause;
  };
}

#endif /* !_ARCADEGAME_HPP_ */
