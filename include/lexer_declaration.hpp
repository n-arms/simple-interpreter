#ifndef LEXER_DEC_H
#define LEXER_DEC_H

#include <deque>
#include <string>
#include <vector>

namespace simple{
  enum tokenType;
  class Token{
  private:
    tokenType type_;
    std::vector<char> value_;
  public:
    void opperator<<(char c);
    static tokenType getType(const char& c);
    bool matchType(const char& c) const;
    void print() const;
    const type_& type() const;
    const string value() const;
  } ;

  std::deque<Token> lexer(const std::string& toTokens);
}

#endif
