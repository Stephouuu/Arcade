//
// CacheManager.hpp for arcade in /home/galibe_s/rendu/cpp_arcade/src/graphics/sfml
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Fri Apr  1 14:45:12 2016 stephane galibert
// Last update Fri Apr  1 14:56:45 2016 stephane galibert
//

#ifndef _CACHEMANAGER_HPP_
# define _CACHEMANAGER_HPP_

# include <iostream>
# include <string>
# include <utility>
# include <map>

# include "Exception.hpp"

namespace arcade
{
  template<typename Key, typename Cache>
  class CacheManager
  {
  public:
    CacheManager(void) {}
    ~CacheManager(void) {}

    Cache &operator[](Key const& key)
    {
      if (_cache.find(key) != _cache.end())
	return (_cache[key]);
      throw (ElemNotFound("CacheManager: key not found"));
    }

    Cache const& operator[](Key const& key) const
    {
      if (_cache.find(key) != _cache.end())
	return (_cache.at(key));
      throw (ElemNotFound("CacheManager: key not found"));
    }

    void insert(Key const& key, Cache const& cache)
    {
      _cache.insert(std::make_pair(key, cache));
    }

    bool find(Key const& key)
    {
      return (_cache.find(key) != _cache.end());
    }
  private:
    std::map<Key, Cache> _cache;
  };
}

#endif /* !_CACHEMANAGER_HPP_ */
