//
// Pacman.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/games
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Mar 21 16:01:10 2016 stephane galibert
// Last update Sun Apr  3 14:15:54 2016 stephane galibert
//

#ifndef _PACMAN_HPP_
# define _PACMAN_HPP_

# include <iostream>
# include <string>
# include <map>
# include <vector>
# include <functional>

# include "Generator.hpp"
# include "IGames.hpp"
# include "Player.hpp"
# include "Ghost.hpp"
# include "Blinky.hpp"
# include "Pinky.hpp"
# include "Inky.hpp"
# include "Clyde.hpp"

# include "MapData.hpp"
# include "PowerUp.hpp"
# include "PacGum.hpp"
# include "SPacGum.hpp"

# include "ICommand.hpp"
# include "CMDBuilder.hpp"

namespace arcade
{
  class Pacman : public IGames
  {
  public:
    Pacman(void);
    virtual ~Pacman(void);
    // Misc
    virtual std::string getGamesName(void) const;
    virtual Drawable const& getBackgroundTexture(void) const;
    // Game Management
    virtual bool input(InputT const input);
    virtual void restart(void);
    virtual Map const& getMap(void) const;
    // Player information
    virtual std::list<Vector2u> const& getPlayerPosition(void) const;
    virtual bool isPlayerAlive(void) const;
    virtual bool isPlayerWin(void) const;
    virtual void setPlayerName(std::string const& name);
    virtual std::string getPlayerName(void) const;
    virtual size_t getScore(void) const;
    virtual Vector2u getDimension(void) const;
    virtual Vector2u getScale(void) const;
    // Updater
    virtual void updateGame(float const delta);
    // Texture management
    virtual void loadTexture(void);
    virtual Drawable const *getTexture(Vector2u const& pos) const;
    virtual std::vector<Drawable> const& getDrawableEvent(void) const;
    // Protocol
    virtual void goUp(void);
    virtual void goDown(void);
    virtual void goLeft(void);
    virtual void goRight(void);
    virtual void goForward(void);
    virtual void shoot(void);
    virtual void play(void);
  private:
    void initMap(void);
    bool parseMap(void);
    void initPlayer(void);
    void initGhost(void);

    std::vector<Drawable *> _textures;
    std::vector<Drawable> _drawable;
    FileCache *_backgroundTexture;
    Drawable _background;
    Player *_player;
    std::vector<Ghost *> _ghosts;
    PowerUp *_powerup;

    Vector2u _begin;
    Vector2u _dim;
    Vector2u _scale;

    Generator _generator;
    float _delta_ghost;

    Map _map;
    MapData _mapData;
  };
}

extern "C"
{
  arcade::IGames *Entry(void)
  {
    return (new arcade::Pacman);
  }

  void Play(void)
  {
    arcade::Pacman pacman;
    arcade::CMDBuilder builder;
    arcade::ICommand *current = NULL;
    arcade::CommandType cmd = arcade::CommandType::ILLEGAL;
    pacman.restart();
    while (std::cin.read((char *)&cmd, sizeof(arcade::CommandType)) > 0)
      if ((current = builder.create(cmd)))
	{
	  current->compute(pacman);
	  delete (current);
	}
  }
};

#endif /* !_PACMAN_HPP_ */
