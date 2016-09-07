//
// CMDGoForward.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:49:14 2016 stephane galibert
// Last update Thu Mar 17 22:11:45 2016 stephane galibert
//

#ifndef _CMDGOFORWARD_HPP_
# define _CMDGOFORWARD_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDGoForward : public ICommand
  {
  public:
    CMDGoForward(void);
    virtual ~CMDGoForward(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDGOFORWARD_HPP_ */
