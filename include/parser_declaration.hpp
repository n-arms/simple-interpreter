#ifndef PARSER_DEC_H
#define PARSER_DEC_H

#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <map>

namespace simple{
  class Line;//declared
  class Call;//declared
  class Declaration;//declared
  class Definition;//declared

  class Expression;//declared
  class Literal;//declared
  class BinOp;//declared
  class Variable;//declared

  union VarValue{
    int integerValue;
    double realValue;
    char charValue;
    VarValue(){}
    VarValue(int val){
      integerValue = val;
    }
    VarValue(double val){
      realValue = val;
    }
    VarValue(char val){
      charValue = val;
    }
  } ;

  enum CallType {gotoCall, tagCall, returnCall, forCall, ifCall, writeCall, readCall} ;
  enum VarType {intVar, realVar, charVar} ;
  enum LineType {lineCall, definitionCall, declarationCall} ;
  enum ExpressionType {literalExpr, binOpExpr, varExpr} ;
  enum OperationType {add, sub, mul, div, pow, acc} ;

  class Line{
  public:
    virtual void print() const = 0;
    virtual const simple::LineType lineType() const = 0;
    virtual ~Line() = 0;
  } ;

  class Declaration : public Line{
  protected:
    std::string name_;
    simple::VarType type_;
    unsigned long long length_;
  public:
    Declaration(simple::VarType var, std::string name, unsigned long long length = 1);
    const simple::LineType lineType() const override;
    void print() const override;
    const std::string& name() const;
    const simple::VarType& type() const;
    const unsigned long long& length() const;

  } ;

  class Definition : public Line{
  protected:
    std::vector<simple::Expression*> value_;
    std::string name_;
  public:
    Definition(std::vector<simple::Expression*> value, std::string name);
    const simple::LineType lineType() const override;
    void print() const override;
    const std::string& name() const;
    const std::vector<simple::Expression*>& value() const;
    const unsigned long long length() const;
  } ;

  class Call : public Line{
  protected:
    simple::CallType type_;
    std::vector<Expression*> arguments_;
  public:
    Call(simple::CallType type, std::vector<simple::Expression*> arguments);
    const simple::LineType lineType() const override;
    void print() const override;
    const simple::CallType& type() const;
    const std::vector<simple::Expression*>& arguments() const;
  } ;

  class Expression{
  public:
    virtual void print() const = 0;
    virtual simple::Expression* eval() = 0;
    virtual simple::ExpressionType exprType() const = 0;
    virtual std::vector<std::string> undefined() const = 0;
    virtual Expression* define(std::vector<std::pair<std::string, simple::Literal*>> values) = 0;
    virtual ~Expression() = 0;
  } ;

  class BinaryOperator : public Expression{
  protected:
    simple::Expression* left_ = NULL;
    simple::Expression* right_ = NULL;
    simple::OperationType op_;
  public:
    BinaryOperator(simple::Expression* left, simple::Expression* right, simple::OperationType op);
    ~BinaryOperator() override;
    void print() const override;
    simple::Expression* eval() override;
    simple::ExpressionType exprType() const override;
    std::vector<std::string> undefined() const override;
    Expression* define(std::vector<std::pair<std::string, Literal*>> values) override;
  } ;

  class Literal : public Expression{
  protected:
    simple::VarValue* value_;
    unsigned long long size_;
    simple::VarType type_;
  public:
    Literal(std::vector<VarValue> value, VarType type);
    ~Literal() override;
    void print() const override;
    simple::Expression* eval() override;
    simple::Literal* applyOp(simple::Literal* other, simple::OperationType op);
    std::vector<double> realValue() const;
    std::vector<int> intValue() const;
    std::vector<char> charValue() const;
    simple::ExpressionType exprType() const override;
    unsigned long long size() const;
    std::vector<std::string> undefined() const override;
    Expression* define(std::vector<std::pair<std::string, Literal*>> values) override;
  } ;

  class Variable : public Expression{
  protected:
    std::string varName_;
  public:
    Variable(std::string varName);
    ~Variable() override;
    void print() const override;
    simple::Expression* eval() override;
    std::string name() const;
    simple::ExpressionType exprType() const override;
    std::vector<std::string> undefined() const override;
    Expression* define(std::vector<std::pair<std::string, Literal*>> values) override;
  } ;

  std::vector<simple::Line> parse(std::deque<simple::Token*> tokens);

  class Evaluator{
  protected:
    std::map<std::string, Expression*> variables_;
    std::deque<unsigned long long> indeces_; //program path, used as stack with pop/push back only
    std::ostream& io_;
    std::vector<simple::Line*> lines_;

    static const unsigned long long entryPoint_;

    void evaluateLine();
    void define(simple::Definition* line);
    void declare(simple::Declaration* line);
    void call(simple::Call* line);
  public:
    Evaluator(std::vector<simple::Line*> lines, std::ostream& io);
    ~Evaluator();
    void eval();
    void printEnviroment();
  } ;
}

#endif
