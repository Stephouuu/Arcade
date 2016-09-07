//
// CMDIllegal.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 20:53:58 2016 stephane galibert
// Last update Thu Mar 17 22:12:10 2016 stephane galibert
//

#ifndef _CMDILLEGAL_HPP_
# define _CMDILLEGAL_HPP_

# include <iostream>
# include <string>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDIllegal : public ICommand
  {
  public:
    CMDIllegal(void);
    virtual ~CMDIllegal(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDILLEGAL_HPP_ */
