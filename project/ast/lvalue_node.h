// $Id: lvalue_node.h,v 1.2 2016/04/04 23:09:39 ist179042 Exp $
#ifndef __ZU_NODE_EXPRESSION_LEFTVALUE_H__
#define __ZU_NODE_EXPRESSION_LEFTVALUE_H__

#include "lvalue_abstract_node.h"
#include <cdk/ast/simple_value_node.h>
#include <string>


namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class lvalue_node: public lvalue_abstract_node{
  public:
    inline lvalue_node(int lineno, const char *s) :
        lvalue_abstract_node(lineno, s) {
    }
    inline lvalue_node(int lineno, const std::string &s) :
        lvalue_abstract_node(lineno, s) {
    }
    inline lvalue_node(int lineno, const std::string *s) :
        lvalue_abstract_node(lineno, *s) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_lvalue_node(this, level);
    }

  };

} // zu

#endif
