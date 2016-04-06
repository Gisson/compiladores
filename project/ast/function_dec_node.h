// $Id: function_dec_node.h,v 1.2 2016/03/18 03:15:50 ist179042 Exp $ -*- c++ -*-
#ifndef __ZU_FUNCTION_DEC_NODE_H__
#define __ZU_FUNCTION_DEC_NODE_H__

#include <cdk/ast/basic_node.h>
namespace zu {

  /**
   * Class for describing function nodes.
   */
  class function_dec_node: public cdk::basic_node {
		  std::string* _functionName;
		  cdk::sequence_node* _args;
		  basic_type* _returnType;  // FIXME: This can be null so need to overload contructor


  public:
    inline function_dec_node(int lineno, std::string* name,cdk::sequence_node* args, basic_type* returnType) :
        basic_node(lineno),_functionName(name),_args(args),_returnType(returnType) {
    }

	std::string* getFunctionName(){ return _functionName; }
	cdk::sequence_node* getArgs(){ return _args; }
	basic_type* getReturnType(){ return _returnType; }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_dec_node(this, level);
    }

  };

} // zu

#endif
