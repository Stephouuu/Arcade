//
// Parser.hpp for  in /home/avelin_j/Work/cpp_parser
//
// Made by avelin_j
// Login   <avelin_j@epitech.net>
//
// Started on  Sun Mar 13 11:55:55 2016 avelin_j
// Last update Thu Mar 17 21:58:51 2016 stephane galibert
//

#ifndef _PARSER_HPP_
# define _PARSER_HPP_

# include <fstream>
# include <string>
# include <iostream>
# include <vector>

# include "Exception.hpp"

namespace arcade
{
  typedef std::pair<std::string, std::string> Data;
  class Parser
  {
  public:
    Parser(std::string const& filename);
    Parser(Parser const& other);
    ~Parser(void);
    
    Parser& operator=(Parser const& other);
    void dumpData(void) const;
    void parseFile(void);
    
    std::string getFileName(void) const;
    std::vector<Data> const& getValues(void) const;
  private:
    std::string _filename;
    std::vector<Data> _values;
  };
}

std::ostream& operator<<(std::ostream& os, arcade::Parser const& data);

#endif /* _PARSER_HPP_ */
