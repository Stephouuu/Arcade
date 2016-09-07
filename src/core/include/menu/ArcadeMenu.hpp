//
// ArcadeMenu.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Mar 14 20:30:51 2016 stephane galibert
// Last update Fri Mar 25 13:44:19 2016 stephane galibert
//

#ifndef _ARCADEMENU_HPP_
# define _ARCADEMENU_HPP_

# include <string>
# include <iostream>
# include <vector>
# include <map>
# include <functional>

# include "Drawable.hpp"
# include "Exception.hpp"
# include "IGraphic.hpp"
# include "FileCache.hpp"
# include "Utility.hpp"
# include "Input.hpp"

# include "IBox.hpp"
# include "TextBox.hpp"

namespace arcade
{
  class ArcadeMenu
  {
  public:
    ArcadeMenu(Vector2u const& dim);
    ~ArcadeMenu(void);

    void setCurrentGraph(std::string const& lib);
    std::string getGraph(void) const;
    std::string getGames(void) const;
    std::string getUsername(void) const;

    void init(void);
    bool input(InputT const in);
    void update(float const delta);
    void display(IGraphic *&graphic);
    bool hasStarted(void) const;
    void setStarted(bool const value);
    void resetWindowSize(IGraphic *&graphic);

    void createGames(std::vector<std::string> const& games);
    void createGraph(std::vector<std::string> const& graph);
    void refreshScore(std::vector<std::string> const& score);
    void createScore(std::vector<std::string> const& score);
  private:
    void drawCursor(IGraphic *&graphic);

    std::map<InputT, std::function<void(void)> > _input;
    void up(void);
    void down(void);
    void left(void);
    void right(void);
    void enter(void);

    Vector2u _dim;
    FileCache *_indexRight;
    FileCache *_indexLeft;
    FileCache *_background;
    bool _started;

    std::string _user;
    std::string _currentGraph;
    std::string _currentGames;
    IBox *_username;
    std::vector<IBox *> _title;
    std::vector<IBox *> _score;
    std::vector<IBox *> _box;
    std::vector<IBox *>::const_iterator _current;

    std::map<std::string, std::string> _games;
    std::map<std::string, std::string> _graph;

    float _delta_cursor;
  };
}

#endif /* !_ARCADEMENU_HPP_ */
