//
// CMDGetMap.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 19:32:16 2016 stephane galibert
// Last update Thu Mar 17 22:12:26 2016 stephane galibert
//

#ifndef _CMDGETMAP_HPP_
# define _CMDGETMAP_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"
# include "Map.hpp"

namespace arcade
{
  class CMDGetMap : public ICommand
  {
  public:
    CMDGetMap(void);
    virtual ~CMDGetMap(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDGETMAP_HPP_ */
