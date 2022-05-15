#pragma once
// Credit to Dietmar Kuhl
// https://stackoverflow.com/a/12827213

#include <streambuf>
#include <ostream>
#include <functional>
#include <string>
#include <memory>

// Parameters are (message, message_level), where 0 = cout, 1 = clog, 2 = cerr
using function_type = std::function<void(std::string, int)>;

class functionbuf : public std::streambuf
{
public:
  functionbuf(function_type const& function, int level)
    : d_function(function),
    d_level(level)
  {
    this->setp(this->d_buffer, this->d_buffer + sizeof(this->d_buffer) - 1);
  }

private:
  using traits_type = std::streambuf::traits_type;
  function_type d_function;
  int d_level;
  char d_buffer[1024];
  
  int overflow(int c)
  {
    if (!traits_type::eq_int_type(c, traits_type::eof()))
    {
      *this->pptr() = traits_type::to_char_type(c);
      this->pbump(1);
    }
    return this->sync() ? traits_type::not_eof(c) : traits_type::eof();
  }

  int sync()
  {
    if (this->pbase() != this->pptr())
    {
      // Execute attached function whenever buffer syncs
      this->d_function(std::string(this->pbase(), this->pptr()), d_level);
      this->setp(this->pbase(), this->epptr());
    }
    return 0;
  }
};

class ofunctionstream : private virtual functionbuf, public std::ostream
{
public:
  ofunctionstream(function_type const& function, int level)
    : functionbuf(function, level),
    std::ostream(static_cast<std::streambuf*>(this))
  {
    this->flags(std::ios_base::unitbuf);
  }
};