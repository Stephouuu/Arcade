//
// Utility.hpp for nibbler in /home/galibe_s/github/nibbler/src/core
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Jun 26 20:33:56 2015 stephane galibert
// Last update Fri Apr  1 00:29:14 2016 stephane galibert
//

#ifndef _UTILITY_HPP_
# define _UTILITY_HPP_

namespace arcade
{
  typedef unsigned int const t_usi_c;
  typedef unsigned int t_usi;

  template<typename T>
  struct Vector2
  {
    Vector2(void);
    Vector2(Vector2<T> const& other);
    Vector2(T const& _x, T const& _y);
    Vector2<T> &operator=(Vector2<T> const& other);
    T x;
    T y;
  };

  template<typename T>
  Vector2<T>::Vector2(void)
  {
    x = 0;
    y = 0;
  }

  template<typename T>
  Vector2<T>::Vector2(Vector2<T> const& other)
  {
    x = other.x;
    y = other.y;
  }

  template<typename T>
  Vector2<T>::Vector2(T const& _x, T const& _y)
  {
    x = _x;
    y = _y;
  }

  template<typename T>
  Vector2<T> &Vector2<T>::operator=(Vector2<T> const& other)
  {
    x = other.x;
    y = other.y;
    return (*this);
  }

  template<typename T>
  Vector2<T> operator*(Vector2<T> const& lhs, Vector2<T> const& rhs)
  {
    return (Vector2<T>(lhs.x * rhs.x, lhs.y * rhs.y));
  }

  template<typename T>
  bool operator==(Vector2<T> const& lhs, Vector2<T> const& rhs)
  {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
  }

  template<typename T>
  bool operator!=(Vector2<T> const& lhs, Vector2<T> const& rhs)
  {
    return (lhs.x != rhs.x || lhs.y != rhs.y);
  }

  typedef Vector2<int> Vector2i;
  typedef Vector2<float> Vector2f;
  typedef Vector2<unsigned int> Vector2u;

  enum Input
    {
      None = 0,
      Up,
      Down,
      Right,
      Left,
      P,
      Escape,
      Enter,
      K2,
      K3,
      K4,
      K5,
      K8,
      K9
    };

  enum GameStatus
    {
      Menu = 0,
      Game,
      Pause
    };

  enum Direction
    {
      Dir_None = 0,
      Top,
      Bottom,
      Forward,
      Backward
    };
}

namespace std
{
  template<>
  class less<arcade::Vector2u>
  {
  public:
    bool operator()(arcade::Vector2u const& lhs, arcade::Vector2u const& rhs) const
      {
	if (lhs.x != rhs.x)
	  return (lhs.x < rhs.x);
	return (lhs.y < rhs.y);
      }
  };
}

#endif /* !_UTILITY_HPP_ */
