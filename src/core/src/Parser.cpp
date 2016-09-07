//
// Parser.cpp for  in /home/avelin_j/Work/cpp_parser
//
// Made by avelin_j
// Login   <avelin_j@epitech.net>
//
// Started on  Sun Mar 13 11:52:53 2016 avelin_j
// Last update Thu Mar 17 21:59:13 2016 stephane galibert
//

#include "Parser.hpp"

arcade::Parser::Parser(Parser const& other)
  : _filename("")
{
  *this = other;
}

arcade::Parser::Parser(std::string const& filename)
  : _filename(filename)
{
  
}

arcade::Parser::~Parser(void)
{

}

arcade::Parser& arcade::Parser::operator=(Parser const& other)
{
  if (&other != this)
    {
      this->_filename = other.getFileName();
      this->_values = other.getValues();
    }
  return *this;
}

void	arcade::Parser::parseFile(void)
{
  std::string line;
  std::ifstream file(_filename.c_str());

  if (file.is_open())
    {
      while (getline(file, line))
	{
	  size_t pos = line.find_first_of("=");
	  if (pos != std::string::npos)
	    _values.push_back(std::make_pair(line.substr(0, pos), line.substr(pos + 1)));
	}
      file.close();
    }
  else
    throw FileError("Unable to open " + _filename);
}

void arcade::Parser::dumpData(void) const
{
  for (size_t i = 0 ; i < _values.size() ; ++i)
    std::cout << "k: " << _values[i].first
	      << " v: " << _values[i].second << std::endl;
}

std::string arcade::Parser::getFileName(void) const
{
  return (this->_filename);
}

std::vector<arcade::Data> const& arcade::Parser::getValues(void) const
{
  return (_values);
}

std::ostream& operator<<(std::ostream& os, arcade::Parser const& data)
{
  data.dumpData();
  return os;
}
