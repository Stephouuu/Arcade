//
// IGames.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/games/nibbler
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Tue Mar  8 19:41:33 2016 stephane galibert
// Last update Mon Mar 28 20:07:23 2016 stephane galibert
//

#ifndef _IGAMES_HPP_
# define _IGAMES_HPP_

# include <string>
# include <list>
# include <vector>

# include "Drawable.hpp"
# include "Utility.hpp"
# include "Map.hpp"
# include "FileCache.hpp"
# include "Input.hpp"

namespace arcade
{
  class IGames
  {
  public:
    virtual ~IGames(void) {}
    // Misc
    virtual std::string getGamesName(void) const = 0;
    virtual Drawable const& getBackgroundTexture(void) const = 0;
    // Games Management
    virtual bool input(InputT const input) = 0;
    virtual void restart(void) = 0;
    // Player information
    virtual std::list<Vector2u> const& getPlayerPosition(void) const = 0;
    virtual bool isPlayerAlive(void) const = 0;
    virtual bool isPlayerWin(void) const = 0;
    virtual void setPlayerName(std::string const& name) = 0;
    virtual std::string getPlayerName(void) const = 0;
    virtual size_t getScore(void) const = 0;
    virtual Vector2u getDimension(void) const = 0;
    virtual Vector2u getScale(void) const = 0;
    // Updater
    virtual void updateGame(float const delta) = 0;
    // Initialization
    virtual Map const& getMap(void) const = 0;
    // Texture management
    virtual void loadTexture(void) = 0;
    virtual Drawable const* getTexture(Vector2u const& pos) const = 0;
    virtual std::vector<Drawable> const& getDrawableEvent(void) const = 0;
    // Protocol
    virtual void goUp(void) = 0;
    virtual void goDown(void) = 0;
    virtual void goLeft(void) = 0;
    virtual void goRight(void) = 0;
    virtual void goForward(void) = 0;
    virtual void shoot(void) = 0;
    virtual void play(void) = 0;
  };
}

#endif /* !_IGAMES_HPP_ */
