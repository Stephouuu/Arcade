//
// Chrono.cpp for nibbler in /home/galibe_s/github/nibbler/tmp
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Mon Jul 13 22:54:20 2015 stephane galibert
// Last update Wed Mar  9 16:54:40 2016 stephane galibert
//

#include <iostream>
#include "Chrono.hpp"

arcade::Chronometer::Chronometer(void)
{
  this->_running = false;
  this->_value = 0;
}

arcade::Chronometer::~Chronometer(void)
{

}

double arcade::Chronometer::restart(void)
{
  double elapsed = 0.;

  elapsed = getElapsedTime();
  this->_value = 0.;
  this->_running = false;
  start();
  return (elapsed);
}

void arcade::Chronometer::toggle(void)
{
  if (!this->_running)
    start();
  else
    pause();
}

void arcade::Chronometer::start(void)
{
  if (!this->_running)
    {
      this->_current = std::chrono::steady_clock::now();
      this->_running = true;
    }
}

void arcade::Chronometer::pause(void)
{
  if (this->_running)
    {
      this->_value += getElapsedTime();
      this->_running = false;
    }
}

double arcade::Chronometer::getElapsedTime(void)
{
  if (this->_running)
    {
      this->_begin = std::chrono::steady_clock::now();
      std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double> >(this->_begin - this->_current);
      return (time_span.count() + this->_value);
    }
  return (this->_value);
}
