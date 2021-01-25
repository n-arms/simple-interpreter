#ifndef PARSER_H
#define PARSER_H

#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include "parser_declaration.hpp"

namespace simple{
  simple::BinaryOperator::BinaryOperator(simple::Expression* left, simple::Expression* right, simple::OperationType op)
  {
    left_ = left;
    right_ = right;
    op_ = op;
  }

  void simple::BinaryOperator::print() const{
    std::cout << '(';
    if (left_ != NULL)
    left_->print();
    std::cout << ' '<<op_<<' ';
    if (right_ != NULL)
    right_->print();
    std::cout << ')';
  }

  simple::Literal* simple::BinaryOperator::eval(){
    left_ = left_->eval();
    right_ = right_->eval();
    if (left_->exprType()==literalExpr && right_->exprType()==literalExpr){
      switch (op_){
        case acc:
        break;
        case add:
        break;
        case sub:
        break;
        case div:
        break;
        case pow:
        break;
        case mul:
        break;
        default:
        throw 0;
      }

    }
    return NULL;
  }

  simple::ExpressionType simple::BinaryOperator::exprType() const{
    return simple::ExpressionType::binOpExpr;
  }


}

#endif
