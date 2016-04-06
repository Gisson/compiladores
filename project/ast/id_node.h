/* Falar com o professor */

#ifndef __ZU_IDNODE_H__
#define __ZU_IDNODE_H__

#include <cdk/ast/binary_expression_node.h>

namespace zu {

  /**
   * Class for describing the identity ('+') operator
   */
  class id_node: public cdk::unary_expression_node {
  public:
    /**
     * @param lineno source code line number for this node
     * @param arg operand
     */
    inline id_node(int lineno, expression_node *arg) :
        unary_expression_node(lineno, arg) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_id_node(this, level);
    }

  };

} // zu

#endif
