//
// CMDGoRight.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:36:16 2016 stephane galibert
// Last update Thu Mar 17 22:14:01 2016 stephane galibert
//

#ifndef _CMDGORIGHT_HPP_
# define _CMDGORIGHT_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDGoRight : public ICommand
  {
  public:
    CMDGoRight(void);
    virtual ~CMDGoRight(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDGORIGHT_HPP_ */
