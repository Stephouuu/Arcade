//
// Map.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Wed Mar  9 17:24:05 2016 stephane galibert
// Last update Sat Mar 26 18:21:53 2016 stephane galibert
//

#ifndef _MAP_HPP_
# define _MAP_HPP_

# include "Protocol.hpp"

namespace arcade
{
  struct Map
  {
    Map(void)
    {
      map = NULL;
      width = 0;
      height = 0;
    }
    TileType **map;
    size_t width;
    size_t height;
    size_t h;
  };
}

#endif /* !_MAP_HPP_ */
