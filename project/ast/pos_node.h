#ifndef __CDK_POSNODE_H__
#define __CDK_POSNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace zu {

  /**
   * Class for describing the address return ('?') operator
   */
  class pos_node: public cdk::unary_expression_node {
  public:
    /**
     * @param lineno source code line number for this node
     * @param arg operand
     */
    inline pos_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_pos_node(this, level);
    }

  };

} // zu

#endif
