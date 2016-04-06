/* TO DELETE */

#ifndef __ZU_PRIORITYNODE_H__
#define __ZU_PRIORITYNODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace zu {

  /**
   * Class for describing the priority ('()') operator
   */
  class priority_node: public cdk::unary_expression_node {
  public:
    /**
     * @param lineno source code line number for this node
     * @param arg operand
     */
    inline priority_node(int lineno, expression_node *arg) :
        unary_expression_node(lineno, arg) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_priority_node(this, level);
    }

  };

} // zu

#endif
