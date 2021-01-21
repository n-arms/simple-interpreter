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

  union VarValue;

  enum CallType {gotoCall, tagCall, returnCall, forCall, ifCall, writeCall, readCall} ;
  enum VarType {intVar, realVar, charVar, intArr, realArr, charArr} ;
  enum LineType {lineCall, definitionCall, declarationCall} ;

  class Line{
  public:
    virtual void print() const = 0;
    virtual const LineType& lineType() const = 0;
  } ;

  class Declaration : public Line{
  protected:
    std::string name_;
    VarType type_;
    unsigned long long length_;
  public:
    Declaration(VarType var, std::string name, unsigned long long length = 1);
    ~Declaration();
    const LineType& lineType() const override;
    void print() const override;
    const std::string& name() const;
    const VarType& type() const;
    const unsigned long long& length() const;

  } ;

  class Definition : public Line{
  protected:
    std::vector<Expression> value_;
    std::string name_;
  public:
    Definition(std::vector<Expression> value, std::string name);
    ~Definition();
    const LineType& lineType() const override;
    void print() const override;
    const std::string& name() const;
    const std::vector<Expression>& value() const;
    const unsigned long long length() const;
  } ;

  class Call : public Line{
  protected:
    CallType type_;
    std::vector<Expression> arguments_;
  public:
    Call(CallType type, std::vector<Expression> arguments);
    ~Call();
    const LineType& lineType() const override;
    void print() const override;
    const CallType& type() const;
    const std::vector<Expression>& arguments() const;
  } ;

  class Expression{
  public:
    virtual void print() const = 0;
    virtual Literal eval() const = 0;
  } ;

  class BinaryOperator : public Expression{
  protected:
    Expression* left_;
    Expression* right_;
    std::string op_;
  public:
    BinaryOperator(Expression* left, Expression* right, std::string op);
    void print() const override;
    Literal eval() const override;
  } ;

  class Literal : public Expression{
  protected:
    VarValue* value_;
    unsigned long long size_;
    VarType type_;
  public:
    Literal(std::vector<VarValue> value, VarType type);
    void print() const override;
    Literal eval() const override;
    Literal applyOp(std::string op, Literal other) const;
    std::vector<double> realValue() const;
    std::vector<long> intValue() const;
    std::vector<char> charValue() const;
  } ;

  class Variable : public Expression{
  protected:
    std::string varName_;
  public:
    Variable(std::string varName);
    void print() const override;
    Literal eval() const override;
    std::string name() const;
  } ;

  std::vector<Line> parse(std::deque<Token*> tokens);
}

#endif
