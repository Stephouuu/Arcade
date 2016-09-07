//
// CMDGoLeft.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:35:22 2016 stephane galibert
// Last update Thu Mar 17 22:11:35 2016 stephane galibert
//

#ifndef _CMDGOLEFT_HPP_
# define _CMDGOLEFT_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDGoLeft : public ICommand
  {
  public:
    CMDGoLeft(void);
    virtual ~CMDGoLeft(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDGOLEFT_HPP_ */
