//
// FileCache.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Wed Mar  9 19:21:41 2016 stephane galibert
// Last update Wed Mar  9 19:22:13 2016 stephane galibert
//

#ifndef _FILECACHE_HPP_
# define _FILECACHE_HPP_

# include <iostream>
# include <fstream>

# include "Exception.hpp"

namespace arcade
{
  struct FileCache
  {
    FileCache(void);
    FileCache(std::string const& filename);
    ~FileCache(void);
    char *data;
    std::size_t size;
    std::string filename;
  };
  
}

#endif /* !_FILECACHE_HPP_ */
