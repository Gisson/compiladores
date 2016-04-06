// $Id: function_call_node.h,v 1.2 2016/03/18 12:05:32 ist177459 Exp $ -*- c++ -*-
#ifndef __ZU_FUNCTION_CALL_NODE_H__
#define __ZU_FUNCTION_CALL_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing function nodes.
   */
  class function_call_node: public cdk::expression_node {
	
	private:
		  std::string *_functionName;
		  cdk::sequence_node *_args;

  public:
    inline function_call_node(int lineno,std::string *name, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _functionName(name),_args(args) {
    }

  public:
    inline std::string* getFunctionName() {
      return _functionName;
    }

	inline cdk::sequence_node* getArgs() {
  		return _args;
	}
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_call_node(this, level);
    }

  };

} // zu

#endif
