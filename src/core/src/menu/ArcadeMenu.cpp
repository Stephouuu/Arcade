//
// ArcadeMenu.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Mar 14 20:29:46 2016 stephane galibert
// Last update Wed Mar 30 13:56:12 2016 stephane galibert
//

#include "ArcadeMenu.hpp"

arcade::ArcadeMenu::ArcadeMenu(arcade::Vector2u const& dim)
{
  _dim = dim;
  _started = false;
  _box.push_back(new TextBox("Start", Vector2u(325, 750),
			     Vector2u(15, 25),
			     Vector2u(250, 70),
			     RGBA(255, 40, 40, 180), LAYOUT_MIDDLE));

  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Up, InputT::None),
			       std::bind(&arcade::ArcadeMenu::up, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Down, InputT::None),
			       std::bind(&arcade::ArcadeMenu::down, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Left, InputT::None),
			       std::bind(&arcade::ArcadeMenu::left, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Right, InputT::None),
			       std::bind(&arcade::ArcadeMenu::right, this)));
  _input.insert(std::make_pair(InputT(InputT::KeyPressed, Input::Enter, InputT::None),
			       std::bind(&arcade::ArcadeMenu::enter, this)));

  _background = NULL;
  _indexRight = NULL;
  _indexLeft = NULL;

  _user = "Player";
  _username = new TextBox(_user, Vector2u(325, 660),
			  Vector2u(15, 23),
			  Vector2u(250, 70),
			  RGBA(60, 60, 60, 120), LAYOUT_MIDDLE);
  _current = _box.cend();
  _delta_cursor = 0;
}

arcade::ArcadeMenu::~ArcadeMenu(void)
{
  if (_background)
    delete (_background);
  if (_indexRight)
    delete (_indexRight);
  if (_indexLeft)
    delete (_indexLeft);
  if (_username)
    delete (_username);
  for (size_t i = 0 ; i < _title.size() ; i++)
    delete (_title[i]);
  for (size_t i = 0 ; i < _score.size() ; i++)
    delete (_score[i]);
  for (size_t i = 0 ; i < _box.size() ; i++)
    delete (_box[i]);
}

void arcade::ArcadeMenu::setCurrentGraph(std::string const& lib)
{
  size_t pos0 = lib.find_last_of("_");
  size_t pos1 = lib.find_last_of(".");
  if (pos0 != std::string::npos && pos1 != std::string::npos)
    _currentGraph = lib.substr(pos0 + 1, pos1 - pos0 - 1);
}

std::string arcade::ArcadeMenu::getGraph(void) const
{
  if (_graph.find(_currentGraph) != _graph.end())
    return (_graph.at(_currentGraph));
  return ("");
}

std::string arcade::ArcadeMenu::getGames(void) const
{
  if (_games.find(_currentGames) != _games.end())
    return (_games.at(_currentGames));
  return ("");
}

std::string arcade::ArcadeMenu::getUsername(void) const
{
  std::string username = _username->getText();
  if (username.back() == '|')
    username.pop_back();
  return (username);
}

void arcade::ArcadeMenu::init(void)
{
  try {
    _background = new FileCache("rsrc/texture/newmenu.jpg");
    _indexRight = new FileCache("rsrc/texture/index_right.png");
    _indexLeft = new FileCache("rsrc/texture/index_left.png");
  } catch (ArcadeError const& e) {
    throw (e);
  }
  _current = _box.cbegin();
}

bool arcade::ArcadeMenu::input(arcade::InputT const in)
{
  if (_input.find(in) != _input.end())
    {
      _input[in]();
      return (true);
    }
  else if (in.type == InputT::TextEntered
	   && (isprint(in.unicode) || in.unicode == 8)
	   && in.unicode != '|')
    {
      std::string username = _username->getText();
      if (!username.empty() && username.back() == '|')
	username.pop_back();
      if (!username.empty() && in.unicode == 8)
	username.pop_back();
      else if (username.size() < 12)
	username.push_back(in.unicode);
      _username->setText(username);
    }
  return (false);
}

void arcade::ArcadeMenu::update(float const delta)
{
  _delta_cursor += delta;
  if (_delta_cursor > 500)
    {
      if (_username)
	{
	  std::string username = _username->getText();
	  if (!username.empty() && username.back() == '|')
	    username.pop_back();
	  else
	    username.push_back('|');
	  _username->setText(username);
	}
      _delta_cursor = 0;
    }
}

void arcade::ArcadeMenu::display(arcade::IGraphic *&graphic)
{
  Drawable dTexture;

  dTexture.type = DrawableType::DRAWABLE_TEXTURE;
  dTexture.pos = Vector2u(0, 0);
  dTexture.size = Vector2u(_dim.x * _dim.x, _dim.y * _dim.y);
  dTexture.texture = _background;
  graphic->draw(dTexture);
  for (size_t i = 0 ; i < _title.size() ; ++i)
    _title[i]->draw(graphic, false);
  for (size_t i = 0 ; i < _score.size() ; ++i)
    _score[i]->draw(graphic, false);
  for (size_t i = 0 ; i < _box.size() ; ++i)
    {
      if (*_current == _box[i])
	_box[i]->draw(graphic, true);
      else if (_box[i]->getText() == _currentGames)
	_box[i]->draw(graphic, true);
      else if(_box[i]->getText() == _currentGraph)
	_box[i]->draw(graphic, true);
      else
	_box[i]->draw(graphic, false);
    }
  _username->draw(graphic, false);
  drawCursor(graphic);
}

bool arcade::ArcadeMenu::hasStarted(void) const
{
  return (_started);
}

void arcade::ArcadeMenu::setStarted(bool const value)
{
  _started = value;
}

void arcade::ArcadeMenu::resetWindowSize(arcade::IGraphic *&graphic)
{
  graphic->setWindowSize(Vector2u(900, 900));
}

void arcade::ArcadeMenu::createGames(std::vector<std::string> const& games)
{
  _title.push_back(new TextBox("Jeux:", Vector2u(50, 100),
			       Vector2u(5, 4),
			       Vector2u(250, 40),
			       RGBA(160, 160, 160, 180), LAYOUT_MIDDLE));
  for (size_t i = 0 ; i < games.size() ; ++i)
    {
      size_t pos0 = games[i].find_last_of("_");
      size_t pos1 = games[i].find_last_of(".");
      if (pos0 != std::string::npos && pos1 != std::string::npos)
	{
	  std::string name = games[i].substr(pos0 + 1, pos1 - pos0 - 1);
	  _games[name] = games[i];
	  _box.push_back(new TextBox(name, Vector2u(50, 140 + (40 * i)),
				     Vector2u(5, 5 + (i * 1)),
				     Vector2u(250, 40),
				     RGBA(120, 120, 120, 180), LAYOUT_MIDDLE));
	  if (_currentGames.empty())
	    _currentGames = name;
	}
    }
}

void arcade::ArcadeMenu::createGraph(std::vector<std::string> const& graph)
{
  _title.push_back(new TextBox("Graphiques:", Vector2u(50, 450),
			       Vector2u(5, 14),
			       Vector2u(250, 40),
			       RGBA(160, 160, 160, 180), LAYOUT_MIDDLE));
  for (size_t i = 0 ; i < graph.size() ; ++i)
    {
      size_t pos0 = graph[i].find_last_of("_");
      size_t pos1 = graph[i].find_last_of(".");
      if (pos0 != std::string::npos && pos1 != std::string::npos)
	{
	  std::string name = graph[i].substr(pos0 + 1, pos1 - pos0 - 1);
	  _graph[name] = graph[i];
	  _box.push_back(new TextBox(name, Vector2u(50, 490 + (40 * i)),
				     Vector2u(5, 15 + (i * 1)),
				     Vector2u(250, 40),
				     RGBA(120, 120, 120, 180), LAYOUT_MIDDLE));
	  if (_currentGraph.empty())
	    _currentGraph = name;
	}
    }
}

void arcade::ArcadeMenu::createScore(std::vector<std::string> const& score)
{
  (void)score;
  _title.push_back(new TextBox("Score:", Vector2u(600, 100),
			       Vector2u(25, 4),
			       Vector2u(250, 40),
			       RGBA(160, 160, 160, 180), LAYOUT_MIDDLE));
}

void arcade::ArcadeMenu::refreshScore(std::vector<std::string> const& score)
{
  for (size_t i = 0 ; i < _score.size() ; ++i)
    delete (_score[i]);
  _score.erase(_score.begin(), _score.end());
  for (size_t i = 0 ; i < score.size() && i < 15 ; ++i)
    _score.push_back(new TextBox(score[i], Vector2u(600, 140 + (40 * i)),
				 Vector2u(25, 5 + (i * 1)),
				 Vector2u(250, 40),
				 RGBA(120, 120, 120, 180), LAYOUT_NONE));
}

void arcade::ArcadeMenu::drawCursor(arcade::IGraphic *&graphic)
{
  Vector2u pos;
  Drawable dTextureLeft;
  Drawable dTextureRight;

  pos.x = (*_current)->getPosition().x - 40 - 5;
  pos.y = (*_current)->getPosition().y + ((*_current)->getSize().y / 2) - 20;
  if (_current == _box.begin())
    pos.x -= 15;
  dTextureLeft.type = DrawableType::DRAWABLE_TEXTURE;
  dTextureLeft.pos = pos;
  dTextureLeft.rpos = (*_current)->getRPosition();
  dTextureLeft.rpos.x -= 1;
  dTextureLeft.size = Vector2u(40, 40);
  dTextureLeft.texture = _indexLeft;

  pos.x = (*_current)->getPosition().x + (*_current)->getSize().x + 5;
  pos.y = (*_current)->getPosition().y + ((*_current)->getSize().y / 2) - 20;
  if (_current == _box.begin())
    pos.x += 15;
  dTextureRight.type = DrawableType::DRAWABLE_TEXTURE;
  dTextureRight.pos = pos;
  dTextureRight.size = Vector2u(40, 40);
  dTextureRight.texture = _indexRight;

  graphic->draw(dTextureLeft);
  graphic->draw(dTextureRight);
}

void arcade::ArcadeMenu::up(void)
{
  if (_current != _box.cbegin()
      && _current != _box.cbegin() + 1)
    _current--;
  else
    _current = _box.cend() - 1;
}

void arcade::ArcadeMenu::down(void)
{
  if (_current != _box.cend() - 1)
    _current++;
  else
    _current = _box.cbegin() + 1;
}

void arcade::ArcadeMenu::left(void)
{
  if (_current != _box.cbegin())
    _current = _box.cbegin();
  else
    _current = _box.cbegin() + 1;
}

void arcade::ArcadeMenu::right(void)
{
  if (_current != _box.cbegin())
    _current = _box.cbegin();
  else
    _current = _box.cbegin() + 1;
}

void arcade::ArcadeMenu::enter(void)
{
  if (_current == _box.cbegin())
    {
      if (_graph.find(_currentGraph) != _graph.end()
	  && _games.find(_currentGames) != _games.end())
	_started = true;
    }
  else
    {
      if (_graph.find((*_current)->getText()) != _graph.end())
	_currentGraph = (*_current)->getText();
      else if (_games.find((*_current)->getText()) != _games.end())
	_currentGames = (*_current)->getText();
    }
}
