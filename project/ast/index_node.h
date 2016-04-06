// $Id: index_node.h,v 1.7 2016/04/04 23:09:39 ist179042 Exp $
#ifndef __ZU_INDEX_NODE_H__
#define __ZU_INDEX_NODE_H__

#include <cdk/ast/expression_node.h>
#include <string>

namespace zu {

  /**
   * Class for index nodes
   */
  class index_node: public lvalue_abstract_node {
	cdk::expression_node *_index,*_pointer;
  public:
    inline index_node(int lineno, const char *s,cdk::expression_node *index,cdk::expression_node *pointer) :
    lvalue_abstract_node(lineno, s),_index(index),_pointer(pointer) {}

	inline index_node(int lineno, const std::string &s,cdk::expression_node *index,cdk::expression_node *pointer) :
	lvalue_abstract_node(lineno, s),_index(index),_pointer(pointer) {}

	inline index_node(int lineno, const std::string *s,cdk::expression_node *index,cdk::expression_node *pointer) :
	lvalue_abstract_node(lineno, *s) {}

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
