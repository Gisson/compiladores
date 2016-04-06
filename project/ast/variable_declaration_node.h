#ifndef __ZU_VARIABLE_DECLARATION_NODE_H__
#define __ZU_VARIABLE_DECLARATION_NODE_H__

/* DEPRECATED */

#include <cdk/ast/basic_node.h>
#include <string>

namespace zu {

  /**
   * Class for variable declaration nodes
   */
  class variable_declaration_node: public cdk::basic_node {
	basic_type *_type;
	std::string *_varName;
  public:
    inline variable_declaration_node(int lineno, basic_type *type, std::string *varName) :
    cdk::basic_node(lineno),_type(type),_varName(varName) {}


	inline basic_type* getType(){ return _type; }

	inline std::string* getVarName(){ return _varName; }                                             
	/**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_declaration_node(this, level);
    }

  };

} // zu

#endif
