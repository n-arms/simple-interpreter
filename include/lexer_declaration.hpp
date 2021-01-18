#ifndef LEXER_DEC_H
#define LEXER_DEC_H

#include <deque>
#include <string>
#include <vector>

namespace simple{
  enum tokenType {op, number, name, key, colon, quote, index, none};
  class Token{
  private:
    tokenType* type_;
    std::vector<char> value_;
    static std::string lowercase_;
    static std::string digit_;
    static std::string capital_;
    static char colon_;
    static char quote_;
    static std::string bracket_;
    static std::string operator_;

  public:
    Token();
    void operator<<(char c);
    static tokenType getType(const char& c);
    bool matchType(const char& c) const;
    void print() const;
    const tokenType type() const;
    const std::string value() const;
  } ;

  std::deque<Token*> lexer(const std::string& toTokens);
}

#endif
