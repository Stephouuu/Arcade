//
// ICommand.hpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 19:21:26 2016 stephane galibert
// Last update Thu Mar 17 22:11:01 2016 stephane galibert
//

#ifndef _ICOMMAND_HPP_
# define _ICOMMAND_HPP_

# include "IGames.hpp"

namespace arcade
{
  class ICommand
  {
  public:
    virtual ~ICommand(void) {}
    virtual void compute(IGames& game) = 0;
  };
}

#endif /* !_ICOMMAND_HPP_ */
