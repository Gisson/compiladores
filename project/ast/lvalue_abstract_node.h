// $Id: lvalue_abstract_node.h,v 1.1 2016/04/04 23:09:39 ist179042 Exp $
#ifndef __ZU_NODE_EXPRESSION_LEFTVALUE_ABSTRACT_H__
#define __ZU_NODE_EXPRESSION_LEFTVALUE_ABSTRACT_H__

#include <cdk/ast/simple_value_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class lvalue_abstract_node: public cdk::simple_value_node<std::string> {
  public:
    inline lvalue_abstract_node(int lineno, const char *s) :
        cdk::simple_value_node<std::string>(lineno, s) {
    }
    inline lvalue_abstract_node(int lineno, const std::string &s) :
        cdk::simple_value_node<std::string>(lineno, s) {
    }
    inline lvalue_abstract_node(int lineno, const std::string *s) :
        cdk::simple_value_node<std::string>(lineno, *s) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level)=0;

  };

} // zu

#endif
