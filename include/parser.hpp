#ifndef PARSER_H
#define PARSER_H

#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include "parser_declaration.hpp"
#include <cassert>

namespace simple{
  simple::Expression::~Expression(){}


  /*##################################################################################
  Binary Operator
  #####################################################################################
  */
  simple::BinaryOperator::BinaryOperator(simple::Expression* left, simple::Expression* right, simple::OperationType op)
  {
    left_ = left;
    right_ = right;
    op_ = op;
  }

  simple::BinaryOperator::~BinaryOperator(){
    if (left_ != NULL)
    delete left_;

    if (right_ != NULL)
    delete right_;
  }

  void simple::BinaryOperator::print() const{
    std::cout << '(';
    if (left_ != NULL)
    left_->print();
    switch(op_){
      case add:
      std::cout << " + ";
      break;
      case sub:
      std::cout << " - ";
      break;
      case pow:
      std::cout << " ^ ";
      break;
      case div:
      std::cout << " / ";
      break;
      case acc:
      std::cout << " [] ";
      break;
      case mul:
      std::cout << " * ";
      break;

    }
    if (right_ != NULL)
    right_->print();
    std::cout << ')';
  }

  simple::Expression* simple::BinaryOperator::eval(){
    left_ = left_->eval();
    right_ = right_->eval();
    if (left_->exprType()==literalExpr && right_->exprType()==literalExpr){
      left_ = static_cast<Literal*>(left_)->applyOp(static_cast<Literal*>(right_), op_);
      return left_;
    }
    return this;
  }

  simple::ExpressionType simple::BinaryOperator::exprType() const{
    return simple::ExpressionType::binOpExpr;
  }

  std::vector<std::string> simple::BinaryOperator::undefined() const{
    std::vector<std::string> a = left_->undefined();
    std::vector<std::string> b = right_->undefined();
    a.insert(a.end(), b.begin(), b.end());
    return a;
  }

  Expression* simple::BinaryOperator::define(std::vector<std::pair<std::string, simple::Literal*>> values){
    left_ = left_->define(values);
    right_ = right_->define(values);
    return this;
  }

  Literal* simple::BinaryOperator::forceEval(){
    Expression* temp = this->eval();
    if (temp->exprType()==literalExpr){
      return dynamic_cast<Literal*>(temp);
    }else{
      throw 0;
    }
  }

/*##################################################################################
Literal
#####################################################################################
*/

  simple::Literal::Literal(std::vector<VarValue> value, VarType type){
    type_ = type;
    size_ = value.size();
    value_ = new VarValue[size_];
    switch (type){
      case intVar:
      for (int i = 0; i<size_; i++)
      value_[i].integerValue = value[i].integerValue;
      case realVar:
      for (int i = 0; i<size_; i++)
      value_[i].realValue = value[i].realValue;
      case charVar:
      for (int i = 0; i<size_; i++)
      value_[i].charValue = value[i].charValue;
    }
  }

  simple::Literal::~Literal(){
    delete value_;
  }

  void simple::Literal::print() const{
    if (size_ > 1)
    std::cout << '(';
    switch (type_){
      case intVar:
      for (int i = 0; i<size_; i++)
      std::cout << value_[i].integerValue<<" ";
      break;
      case charVar:
      for (int i = 0; i<size_; i++)
      std::cout << value_[i].charValue<<" ";
      break;
      case realVar:
      for (int i = 0; i<size_; i++)
      std::cout << value_[i].realValue<<" ";
      break;
    }
    if (size_ > 1)
    std::cout << ')';
  }

  simple::Expression* simple::Literal::eval(){
    return this;
  }

  simple::Literal* simple::Literal::applyOp(simple::Literal* other, simple::OperationType op){
    switch (op){
      case add:
      switch (type_){
        case intVar:
        for (int i = 0; i<size_; i++){
          value_[i].integerValue += other->intValue()[i];
        }
        break;
        case realVar:
        for (int i = 0; i<size_; i++){
          value_[i].realValue += other->realValue()[i];
        }
        break;
        case charVar:
        throw 0;
      }
      break;
      case sub:
      switch (type_){
        case intVar:
        for (int i = 0; i<size_; i++){
          value_[i].integerValue -= other->intValue()[i];
        }
        break;
        case realVar:
        for (int i = 0; i<size_; i++){
          value_[i].realValue -= other->realValue()[i];
        }
        break;
        case charVar:
        throw 0;
      }
      break;
      case mul:
      switch (type_){
        case intVar:
        for (int i = 0; i<size_; i++){
          value_[i].integerValue *= other->intValue()[i];
        }
        break;
        case realVar:
        for (int i = 0; i<size_; i++){
          value_[i].realValue *= other->realValue()[i];
        }
        break;
        case charVar:
        throw 0;
      }
      break;
      case div:
      switch (type_){
        case intVar:
        for (int i = 0; i<size_; i++){
          value_[i].integerValue /= other->intValue()[i];
        }
        break;
        case realVar:
        for (int i = 0; i<size_; i++){
          value_[i].realValue /= other->realValue()[i];
        }
        break;
        case charVar:
        throw 0;
      }
      break;
      case pow:
      switch (type_){
        case intVar:
        for (int i = 0; i<size_; i++){
          value_[i].integerValue = std::pow(value_[i].integerValue, other->intValue()[i]);
        }
        break;
        case realVar:
        for (int i = 0; i<size_; i++){
          value_[i].realValue = std::pow(value_[i].integerValue, other->realValue()[i]);
        }
        break;
        case charVar:
        throw 0;
      }
      break;
      case acc:
      switch (type_){
        case intVar:
        value_[0].integerValue = value_[other->intValue()[0]].integerValue;
        break;
        case realVar:
        value_[0].realValue = value_[other->intValue()[0]].realValue;
        break;
        case charVar:
        value_[0].charValue = value_[other->intValue()[0]].charValue;
        break;
      }
      break;
    }
    return this;
  }

  std::vector<double> simple::Literal::realValue() const{
    std::vector<double> output;
    for (int i = 0; i<size_; i++)
    output.push_back(value_[i].realValue);
    return output;
  }

  std::vector<int> simple::Literal::intValue() const{
    std::vector<int> output;
    for (int i = 0; i<size_; i++)
    output.push_back(value_[i].integerValue);
    return output;
  }

  std::vector<char> simple::Literal::charValue() const{
    std::vector<char> output;
    for (int i = 0; i<size_; i++)
    output.push_back(value_[i].charValue);
    return output;
  }

  simple::ExpressionType simple::Literal::exprType() const{
    return simple::ExpressionType::literalExpr;
  }

  unsigned long long simple::Literal::size() const{
    return size_;
  }

  std::vector<std::string> simple::Literal::undefined() const{
    return {};
  }

  Expression* simple::Literal::define(std::vector<std::pair<std::string, simple::Literal*>> values){
    return this;
  }

  Literal* simple::Literal::forceEval(){
    return this;
  }

  simple::VarType simple::Literal::varType() const{
    return type_;
  }

  /*##################################################################################
  Variable
  #####################################################################################
  */

  simple::Variable::Variable(std::string varName){
    varName_ = varName;
  }

  simple::Variable::~Variable(){}

  void simple::Variable::print() const{
    std::cout << varName_;
  }

  simple::Expression* simple::Variable::eval(){
    return this;
  }

  std::string simple::Variable::name() const{
    return varName_;
  }

  simple::ExpressionType simple::Variable::exprType() const{
    return simple::ExpressionType::varExpr;
  }

  std::vector<std::string> simple::Variable::undefined() const{
    return {varName_};
  }

  Expression* simple::Variable::define(std::vector<std::pair<std::string, simple::Literal*>> values){
    for (std::pair<std::string, simple::Literal*> p: values){
      if (std::get<0>(p)==varName_)
      return std::get<1>(p);
    }
    return this;
  }

  Literal* simple::Variable::forceEval(){
    throw 0;
  }

  //###################################################################################
  simple::Line::~Line(){}

  /*##################################################################################
  Declaration
  #####################################################################################
  */

  simple::Declaration::Declaration(simple::VarType var, std::string name, unsigned long long length){
    name_ = name;
    type_ = var;
    length_ = length;
  }

  void simple::Declaration::print() const{
    switch(type_){
      case intVar:
      std::cout << "INT::";
      break;
      case charVar:
      std::cout << "CHAR::";
      break;
      case realVar:
      std::cout << "REAL::";
      break;
    }
    if (length_ > 1)
    std::cout << length_<<"::";
    std::cout << name_<<"\n";
  }

  const std::string& simple::Declaration::name() const{
    return name_;
  }

  const simple::VarType& simple::Declaration::type() const{
    return type_;
  }

  const unsigned long long& simple::Declaration::length() const{
    return length_;
  }

  const simple::LineType simple::Declaration::lineType() const{
    return declarationCall;
  }

  /*##################################################################################
  Definition
  #####################################################################################
  */

  simple::Definition::Definition(std::vector<simple::Expression*> value, std::string name){
    value_ = value;
    name_ = name;
  }

  const simple::LineType simple::Definition::lineType() const{
    return definitionCall;
  }

  void simple::Definition::print() const{
    std::cout << name_ << " = ";
    for (Expression* e: value_){
      e->print();
      std::cout << " ";
    }
    std::cout << "\n";
  }

  const std::string& simple::Definition::name() const{
    return name_;
  }

  std::vector<simple::Expression*> simple::Definition::value() const{
    return value_;
  }

  const unsigned long long simple::Definition::length() const{
    return value_.size();
  }

  /*##################################################################################
  Call
  #####################################################################################
  */

  simple::Call::Call(simple::CallType type, std::vector<simple::Expression*> arguments){
    type_ = type;
    arguments_ = arguments;
  }

  const simple::LineType simple::Call::lineType() const{
    return lineCall;
  }

  void simple::Call::print() const{
    switch(type_){
      case gotoCall:
      std::cout << "GOTO ";
      break;
      case tagCall:
      std::cout << "TAG ";
      break;
      case returnCall:
      std::cout << "RETURN ";
      break;
      case forCall:
      std::cout << "FOR ";
      break;
      case ifCall:
      std::cout << "IF ";
      break;
      case writeCall:
      std::cout << "WRITE ";
      break;
      case readCall:
      std::cout << "READ ";
      break;
    }
    for (Expression* e: arguments_){
      e->print();
      std::cout << " ";
    }
    std::cout << "\n";
  }

  const simple::CallType& simple::Call::type() const{
    return type_;
  }

  const std::vector<simple::Expression*>& simple::Call::arguments() const{
    return arguments_;
  }

  /*##################################################################################
  Evaluator
  #####################################################################################
  */
  const unsigned long long simple::Evaluator::entryPoint_ = 0;

  simple::Evaluator::Evaluator(std::vector<simple::Line*> lines, std::ostream& io) : io_(io){
    indeces_.push_back(simple::Evaluator::entryPoint_);
    lines_ = lines;
  }

  simple::Evaluator::~Evaluator(){
    for (auto itr = variables_.begin(); itr != variables_.end(); itr++){
      delete itr->second;
    }
    for (simple::Line* l: lines_)
    delete l;
  }

  void simple::Evaluator::evaluateLine(){
    simple::Line* current = lines_[indeces_.back()];
    std::cout << "evaluating line ";
    current->print();
    std::cout << "\n";

    switch(current->lineType()){
      case lineCall:
      call(dynamic_cast<Call*>(current));
      throw "why are you implementing the hardest one first!!?!?!?!?!?!?!!?";
      break;
      case definitionCall:
      define(dynamic_cast<Definition*>(current));
      break;
      case declarationCall:
      declare(dynamic_cast<Declaration*>(current));
      break;
    }
    if(++indeces_.back() >= lines_.size()){
      indeces_.pop_back();
    }
  }

  void simple::Evaluator::define(simple::Definition* line){
    assert (line != NULL);
    std::vector<std::pair<std::string, Literal*>> toDefine;
    std::vector<std::string> undefinedVariables;
    std::vector<Expression*> expressions = line->value();
    for (Expression* e: expressions){
      undefinedVariables = e->undefined();
      for (std::string s: undefinedVariables){
        auto itr = variables_.find(s);
        toDefine.push_back(*itr);
      }
      e = e->define(toDefine);
      e = e->eval();
      toDefine.clear();

    }


    std::vector<VarValue> literalValueList;
    Literal* l;
    for (Expression* e: expressions){
      l = dynamic_cast<Literal*>(e);
      assert (l != NULL);
      switch (l->varType()){
        case intVar:
        for (auto i: l->intValue()){
          literalValueList.push_back(VarValue(i));
        }
        break;
        case charVar:
        for (auto c: l->charValue()){
          literalValueList.push_back(VarValue(c));
        }
        break;
        case realVar:

        for (auto r: l->realValue()){
          literalValueList.push_back(VarValue(r));
        }
        break;

      }
    }

    Literal* literalValue = new Literal(literalValueList, l->varType());

    auto itr = variables_.find(line->name());

    if (itr != variables_.end()){
      itr->second = literalValue;
    }else{
      variables_.insert(std::pair<std::string, Literal*>(line->name(), literalValue));
    }
  }

  void simple::Evaluator::declare(simple::Declaration* line){
    assert (line != NULL);
    variables_.insert(std::pair<std::string, Literal*>(line->name(), NULL));
  }

  void simple::Evaluator::call(simple::Call* line){
    assert (line != NULL);
    throw "sheesh be patient i havent implemented this yet";
  }

  void simple::Evaluator::printEnviroment(){
    for (std::map<std::string, Literal*>::iterator it = variables_.begin(); it != variables_.end(); it++){
      std::cout << it->first << ": ";
      if (it->second == NULL){
        std::cout << "NULL\n";
      }else{
        it->second->print();
        std::cout << "\n";
      }
    }
  }
}

void simple::Evaluator::eval(){
  while (indeces_.size() > 0){
    evaluateLine();
  }
}

#endif
