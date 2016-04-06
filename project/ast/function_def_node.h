// $Id: function_def_node.h,v 1.1 2016/03/18 02:49:54 ist179042 Exp $ -*- c++ -*-
#ifndef __ZU_FUNCTION_DEF_NODE_H__
#define __ZU_FUNCTION_DEF_NODE_H__

#include <cdk/ast/basic_node.h>
#include <cdk/ast/sequence_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing function nodes.
   */
  class function_def_node: public cdk::basic_node {

	private:
		  std::string *_functionName;
		  cdk::sequence_node *_args;
		  basic_type *_returnType;
		  cdk::basic_node *_block;
		  bool _local;
		  cdk::expression_node *_defaultReturn;

  public:

	inline function_def_node(int lineno, cdk::sequence_node* args): basic_node(lineno),_args(args){
		/*FIXME MIGHT NEED TO DELETE THIS CONTRUCTOR*/
	}


    inline function_def_node(int lineno, std::string* functionName,cdk::sequence_node* args, basic_type *returnVal,cdk::basic_node* block,bool local, cdk::expression_node* defaultReturn): 
			basic_node(lineno),_functionName(functionName), _args(args),_returnType(returnVal),_block(block),_local(local),_defaultReturn(defaultReturn){
    }


	std::string* getFunctionName(){ return _functionName; }
	cdk::sequence_node* getArgs(){ return _args; }
	basic_type* getReturnType(){ return _returnType; }
	bool getLocal(){ return _local; }
	cdk::expression_node* getDefaultReturn(){ return _defaultReturn; }
	cdk::basic_node* getBlock(){ return _block; }

	void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_def_node(this, level);
    }

  };

} // zu

#endif
