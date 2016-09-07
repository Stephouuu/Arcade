//
// LibConfigFile.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/core
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Mon Mar 14 19:04:06 2016 stephane galibert
// Last update Mon Mar 14 19:14:31 2016 stephane galibert
//

#ifndef _LIBCONFIGFILE_HPP_
# define _LIBCONFIGFILE_HPP_

# include <iostream>
# include <string>

# include "Exception.hpp"
# include "Parser.hpp"

namespace arcade
{
  class LibConfigFile
  {
  public:
    LibConfigFile(std::string const& path);
    ~LibConfigFile(void);
    void updateConfig(void);
    std::vector<std::string> getLibsPath(std::string const& type) const;
    std::vector<Data> getData(void) const;
  private:
    std::string _filename;
    std::vector<Data> _data;
    Parser *_parser;
  };
}

std::ostream &operator<<(std::ostream &flux, arcade::LibConfigFile const& config);

#endif /* !_LIBCONFIGFILE_HPP_ */
