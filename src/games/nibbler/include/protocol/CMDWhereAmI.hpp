//
// CMDWhereAmI.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 19:52:44 2016 stephane galibert
// Last update Thu Mar 17 22:12:19 2016 stephane galibert
//

#ifndef _CMDWHEREAMI_HPP_
# define _CMDWHEREAMI_HPP_

# include <string>
# include <iostream>
# include <list>
# include <unistd.h>

# include "Protocol.hpp"
# include "ICommand.hpp"

namespace arcade
{
  class CMDWhereAmI : public ICommand
  {
  public:
    CMDWhereAmI(void);
    virtual ~CMDWhereAmI(void);
    virtual void compute(IGames& game);
  };
}

#endif /* !_CMDWHEREAMI_HPP_ */
