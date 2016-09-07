//
// Nibbler.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/games
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Mar  8 19:47:53 2016 stephane galibert
// Last update Sun Apr  3 14:15:57 2016 stephane galibert
//

#ifndef _NIBBLER_HPP_
# define _NIBBLER_HPP_

# include <iostream>
# include <string>
# include <map>
# include <functional>

# include "IGames.hpp"
# include "PowerUp.hpp"
# include "Player.hpp"

# include "ICommand.hpp"
# include "CMDBuilder.hpp"

namespace arcade
{
  class Nibbler : public IGames
  {
  public:
    Nibbler(void);
    virtual ~Nibbler(void);
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
    virtual Drawable const* getTexture(Vector2u const& pos) const;
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
    void initPlayer(void);
    FileCache *_backgroundTexture;
    Drawable _background;
    std::map<TileType, FileCache *> _texture;
    Player *_player;
    PowerUp *_powerup;
    Vector2u _begin;
    Map _map;
    Vector2u _dim;
    Vector2u _scale;
  };
}

extern "C"
{
  arcade::IGames *Entry(void)
  {
    return (new arcade::Nibbler);
  }

  void Play(void)
  {
    arcade::Nibbler nibbler;
    arcade::CMDBuilder builder;
    arcade::ICommand *current = NULL;
    arcade::CommandType cmd = arcade::CommandType::ILLEGAL;
    nibbler.restart();
    while (std::cin.read((char *)&cmd, sizeof(arcade::CommandType)) > 0)
      if ((current = builder.create(cmd)))
	{
	  current->compute(nibbler);
	  delete (current);
	}
  }
};

#endif /* !_NIBBLER_HPP_ */
