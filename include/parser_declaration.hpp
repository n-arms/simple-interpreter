#ifndef PARSER_DEC_H
#define PARSER_DEC_H

#include <deque>
#include <vector>
#include <iostream>
#include <string>

namespace simple{
  class Line;
  class Call;
  class Declaration;
  class Definition;

  class Expression;
  class Literal;
  class BinOp;
  class Variable;

  union Value;

  enum CallType {gotoCall, tagCall, returnCall, forCall, ifCall, writeCall, readCall} ;
  enum VarType {intVar, realVar, charVar, intArr, realArr, charArr} ;

  std::vector<Line> parse(std::deque<Token*> tokens);

}

#endif
