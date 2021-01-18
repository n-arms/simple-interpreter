#ifndef LEXER_H
#define LEXER_H

#include "lexer_declaration.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <deque>

namespace simple{
  std::string Token::lowercase_ = "abcdefghijklmnopqrstuvwxyz_";
  std::string Token::capital_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char Token::colon_ = ':';
  char Token::quote_ = '"';
  std::string Token::bracket_ = "[]";
  std::string Token::digit_ = "1234567890.";
  std::string Token::operator_ = "+-*/%";

  Token::Token(){
    type_ = new tokenType(none);
  }

  void Token::operator<<(char c){
    if (c != ' ')
    value_.push_back(c);
    if (value_.size()==1)
    type_ = new tokenType(getType(c));
  }

  tokenType Token::getType(const char& c){
    for (char i: lowercase_){
      if (i==c)
      return name;
    }
    for (char i: capital_){
      if (i==c)
      return key;
    }
    for (char i: digit_){
      if (i==c)
      return number;
    }
    for (char i: bracket_){
      if (i==c)
      return index;
    }
    for (char i: operator_){
      if (i==c){
        return op;
      }
    }
    if (c==quote_)
    return quote;
    if (c==colon_)
    return colon;
    throw 0;
  }

  bool Token::matchType(const char& c) const{
    if (c==' ' || (*type_)==op || (*type_)==quote || (*type_)==index)
    return false;
    if ((*type_)==none)
    return true;
    return getType(c)==*type_;
  }

  void Token::print() const{
    std::string output = std::string(value_.begin(), value_.end());
    std::cout << '<'<<*type_<<", "<<output<<'>';
  }

  const tokenType Token::type() const{
    return *type_;
  }

  const std::string Token::value() const{
    return std::string(value_.begin(), value_.end());
  }

  std::deque<Token*> lexer(const std::string& toTokens){
    std::deque<Token*> tokens;
    tokens.push_back(new Token());
    for (int i = 0; i<toTokens.size(); i++){
      if (tokens.back()->matchType(toTokens[i])){
        (*tokens.back())<<toTokens[i];
      }else{
        tokens.push_back(new Token());
        (*tokens.back())<<toTokens[i];
      }
    }
    return tokens;
  }

}


#endif
