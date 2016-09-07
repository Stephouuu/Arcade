//
// FileCache.cpp for arcade in /home/galibe_s/rendu/cpp_arcade
// 
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
// 
// Started on  Wed Mar  9 19:21:48 2016 stephane galibert
// Last update Wed Mar  9 19:22:56 2016 stephane galibert
//

#include "FileCache.hpp"

arcade::FileCache::FileCache(void)
{
  data = NULL;
  size = 0;
  filename = "";
}

arcade::FileCache::FileCache(std::string const& filename)
{
  this->filename = filename;
  std::ifstream ifs(filename, std::ios::binary);
 
  if (ifs)
    {
      ifs.seekg(0, ifs.end);
      size = static_cast<int>(ifs.tellg());
      ifs.seekg(0, ifs.beg);
      data = new char[size];
      ifs.read(data, size);
      ifs.close();
    }
  else
    throw FileError("Error: unable to open " + filename);
}

arcade::FileCache::~FileCache(void)
{
  if (data != NULL)
    {
      delete[] data;
      data = NULL;
    }
}
