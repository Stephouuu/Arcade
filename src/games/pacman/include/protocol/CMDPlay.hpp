//
// CMDPlay.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:54:58 2016 stephane galibert
// Last update Thu Mar 17 22:13:21 2016 stephane galibert
//

#ifndef _CMDPLAY_HPP_
# define _CMDPLAY_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDPlay : public ICommand
  {
  public:
    CMDPlay(void);
    virtual ~CMDPlay(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDPLAY_HPP_ */
