#ifndef __ZU_MALLOCNODE_H__
#define __ZU_MALLOCNODE_H__

#include <cdk/ast/basic_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing the indexation ('[]') operator
   */
  class malloc_node: public cdk::basic_node {
    private:
			int _size;
			std::string* _name;
		  	bool _local;
	public:
    /**
     * @param lineno source code line number for this node
     * @param arg operand
     */
    inline malloc_node(int lineno, std::string *name, int size,bool local) :
        cdk::basic_node(lineno),_size(size),_name(name),_local(local) {
    }

	std::string* getName(){ return _name; }
	int getSize(){ return _size; }
	bool getLocal(){ return _local; }


    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_malloc_node(this, level);
    }

  };

} // zu

#endif
