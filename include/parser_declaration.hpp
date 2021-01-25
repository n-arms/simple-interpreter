#ifndef PARSER_DEC_H
#define PARSER_DEC_H

#include <deque>
#include <vector>
#include <iostream>
#include <string>

namespace simple{
  class Line;//declared
  class Call;//declared
  class Declaration;//declared
  class Definition;//declared

  class Expression;//declared
  class Literal;//declared
  class BinOp;//declared
  class Variable;//declared

  union VarValue;//declared

  enum CallType {gotoCall, tagCall, returnCall, forCall, ifCall, writeCall, readCall} ;
  enum VarType {intVar, realVar, charVar, intArr, realArr, charArr} ;
  enum LineType {lineCall, definitionCall, declarationCall} ;
  enum ExpressionType {literalExpr, binOpExpr, varExpr} ;
  enum OperationType {add, sub, mul, div, pow, acc} ;

  class Line{
  public:
    virtual void print() const = 0;
    virtual const simple::LineType& lineType() const = 0;
  } ;

  class Declaration : public Line{
  protected:
    std::string name_;
    simple::VarType type_;
    unsigned long long length_;
  public:
    Declaration(simple::VarType var, std::string name, unsigned long long length = 1);
    ~Declaration();
    const simple::LineType& lineType() const override;
    void print() const override;
    const std::string& name() const;
    const simple::VarType& type() const;
    const unsigned long long& length() const;

  } ;

  class Definition : public Line{
  protected:
    std::vector<simple::Expression> value_;
    std::string name_;
  public:
    Definition(std::vector<simple::Expression> value, std::string name);
    ~Definition();
    const simple::LineType& lineType() const override;
    void print() const override;
    const std::string& name() const;
    const std::vector<simple::Expression>& value() const;
    const unsigned long long length() const;
  } ;

  class Call : public Line{
  protected:
    simple::CallType type_;
    std::vector<Expression> arguments_;
  public:
    Call(simple::CallType type, std::vector<simple::Expression> arguments);
    ~Call();
    const simple::LineType& lineType() const override;
    void print() const override;
    const simple::CallType& type() const;
    const std::vector<simple::Expression>& arguments() const;
  } ;

  class Expression{
  public:
    virtual void print() const = 0;
    virtual simple::Literal* eval() = 0;
    virtual simple::ExpressionType exprType() const = 0;
  } ;

  class BinaryOperator : public Expression{
  protected:
    simple::Expression* left_ = NULL;
    simple::Expression* right_ = NULL;
    simple::OperationType op_;
  public:
    BinaryOperator(simple::Expression* left, simple::Expression* right, simple::OperationType op);
    void print() const override;
    simple::Literal* eval() override;
    simple::ExpressionType exprType() const override;
  } ;

  class Literal : public Expression{
  protected:
    simple::VarValue* value_;
    unsigned long long size_;
    simple::VarType type_;
  public:
    Literal(std::vector<VarValue> value, VarType type);
    void print() const override;
    simple::Literal* eval() override;
    simple::Literal applyOp(std::string op, simple::Literal other) const;
    std::vector<double> realValue() const;
    std::vector<long> intValue() const;
    std::vector<char> charValue() const;
    simple::ExpressionType exprType() const override;
  } ;

  class Variable : public Expression{
  protected:
    std::string varName_;
  public:
    Variable(std::string varName);
    void print() const override;
    simple::Literal* eval() override;
    std::string name() const;
    simple::ExpressionType exprType() const override;
  } ;

  union VarValue{
    int* integerValue;
    double* realValue;
    char* charValue;
  } ;

  std::vector<simple::Line> parse(std::deque<simple::Token*> tokens);
}

#endif
