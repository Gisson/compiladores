#ifndef __ZU_VARIABLE_NODE_H__
#define __ZU_VARIABLE_NODE_H__

#include <cdk/ast/nil_node.h>

#include <cdk/ast/basic_node.h>
#include <string>

namespace zu {

  /**
   * Class for variable declaration nodes
   */
  class variable_node: public cdk::basic_node {
	basic_type *_type;
	std::string *_varName;
	cdk::basic_node *_value; // In case it doesn't get any value it receives a nil_node
  public:
    inline variable_node(int lineno, basic_type *type, std::string *varName) :
    cdk::basic_node(lineno),_type(type),_varName(varName) {_value=new cdk::nil_node(lineno);}

    inline variable_node(int lineno, basic_type *type, std::string *varName,cdk::basic_node *value) :
    cdk::basic_node(lineno),_type(type),_varName(varName),_value(value) {/*might be buggy */}

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
