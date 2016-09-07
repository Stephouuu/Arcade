//
// CMDBuilder.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/include/protocol
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Thu Mar 17 19:35:17 2016 stephane galibert
// Last update Thu Mar 17 21:03:02 2016 stephane galibert
//

#ifndef _CMDBUILDER_HPP_
# define _CMDBUILDER_HPP_

# include <string>
# include <iostream>
# include <map>
# include <functional>

# include "Protocol.hpp"
# include "ICommand.hpp"

# include "CMDGetMap.hpp"
# include "CMDWhereAmI.hpp"
# include "CMDGoUp.hpp"
# include "CMDGoDown.hpp"
# include "CMDGoLeft.hpp"
# include "CMDGoRight.hpp"
# include "CMDGoForward.hpp"
# include "CMDShoot.hpp"
# include "CMDIllegal.hpp"
# include "CMDPlay.hpp"

namespace arcade
{
  class CMDBuilder
  {
  public:
    CMDBuilder(void);
    ~CMDBuilder(void);
    
    ICommand *create(CommandType const type) const;
  private:
    std::map<CommandType, std::function<ICommand *(void)> > _builder;

    ICommand *create_GetMap(void) const;
    ICommand *create_WhereAmI(void) const;
    ICommand *create_GoUp(void) const;
    ICommand *create_GoDown(void) const;
    ICommand *create_GoLeft(void) const;
    ICommand *create_GoRight(void) const;
    ICommand *create_GoForward(void) const;
    ICommand *create_Shoot(void) const;
    ICommand *create_Illegal(void) const;
    ICommand *create_Play(void) const;
  };
}

#endif /* !_CMDBUILDER_HPP_ */
