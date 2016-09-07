//
// main.cpp for testlib in /home/galibe_s/lib/sfml
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Sat Mar  5 18:19:36 2016 stephane galibert
// Last update Mon Mar 21 16:45:27 2016 stephane galibert
//

#include <iostream>
#include <string>

#include "Core.hpp"
#include "Utility.hpp"

int main(int ac, char **av)
{
  if (ac != 2)
    return (0);
  arcade::Core core(arcade::Vector2u(30, 30));
  try {
    core.init(av[1], "./lib.conf");
    core.play();
  } catch (arcade::ArcadeError const& e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
