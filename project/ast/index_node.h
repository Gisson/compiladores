// $Id: index_node.h,v 1.9 2016/04/11 19:01:36 ist179042 Exp $
#ifndef __ZU_INDEX_NODE_H__
#define __ZU_INDEX_NODE_H__

#include <cdk/ast/expression_node.h>
#include "lvalue_node.h"
#include <string>

namespace zu {

  /**
   * Class for index nodes
   */
  class index_node: public lvalue_node {
	cdk::expression_node *_index,*_pointer;
  public:
    inline index_node(int lineno,cdk::expression_node *index,cdk::expression_node *pointer) :
    lvalue_node(lineno),_index(index),_pointer(pointer) {}
	
	inline cdk::expression_node* getIndex(){ return _index; }

	inline cdk::expression_node* getPointer(){ return _pointer; }                                             
	/**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }

  };

} // zu

#endif
