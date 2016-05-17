#ifndef __ZU_VARIABLE_NODE_H__
#define __ZU_VARIABLE_NODE_H__

#include <cdk/ast/expression_node.h>
#include "lvalue_node.h"
#include <string>

namespace zu {

  /**
   * Class for variable declaration nodes
   */
  class variable_node: public lvalue_node {
	std::string *_varName;
  public:

    inline variable_node(int lineno, std::string *varName) :
    lvalue_node(lineno), _varName(varName) {}

    inline variable_node(int lineno, std::string &varName) :
    lvalue_node(lineno), _varName(&varName) {}

    inline variable_node(int lineno, std::string varName) :
    lvalue_node(lineno), _varName(&varName) {}	

	inline basic_type* getType(){ return _type; }

	inline std::string* getVarName(){ return _varName; }
	/**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

  };

} // zu

#endif
