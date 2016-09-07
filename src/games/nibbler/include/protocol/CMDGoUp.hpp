//
// CMDGoUp.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:31:11 2016 stephane galibert
// Last update Thu Mar 17 22:11:25 2016 stephane galibert
//

#ifndef _CMDGOUP_HPP_
# define _CMDGOUP_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDGoUp : public ICommand
  {
  public:
    CMDGoUp(void);
    virtual ~CMDGoUp(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDGOUP_HPP_ */
