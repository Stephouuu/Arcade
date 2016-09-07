//
// LibConfigFile.cpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/core
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Mon Mar 14 19:04:39 2016 stephane galibert
// Last update Mon Mar 14 19:15:59 2016 stephane galibert
//

#include "LibConfigFile.hpp"

arcade::LibConfigFile::LibConfigFile(std::string const& path)
{
  _filename = path;
  _parser = new Parser(path);
}

arcade::LibConfigFile::~LibConfigFile(void)
{
  if (_parser)
    delete (_parser);
}

void arcade::LibConfigFile::updateConfig(void)
{
  try {
    _parser->parseFile();
    _data = _parser->getValues();
  } catch (ArcadeError const& e) {
    throw (e);
  }
}

std::vector<std::string> arcade::LibConfigFile::getLibsPath(std::string const& type) const
{
  std::vector<std::string> graphs;
  for (auto &it : _data)
    if (it.first == type)
      graphs.push_back(it.second);
  return (graphs);
}

std::vector<arcade::Data> arcade::LibConfigFile::getData(void) const
{
  return (_data);
}

std::ostream &operator<<(std::ostream &flux, arcade::LibConfigFile const& config)
{
  std::vector<arcade::Data> data = config.getData();
  for (auto &it : data)
    std::cout << it.first << ": " << it.second << std::endl;
  return (flux);
}
