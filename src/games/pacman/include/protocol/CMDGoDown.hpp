//
// CMDGoDown.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:33:08 2016 stephane galibert
// Last update Thu Mar 17 22:11:15 2016 stephane galibert
//

#ifndef _CMDGODOWN_HPP_
# define _CMDGODOWN_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDGoDown : public ICommand
  {
  public:
    CMDGoDown(void);
    virtual ~CMDGoDown(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDGODOWN_HPP_ */
