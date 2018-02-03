#include "variable.h"
#include <string>
#include <sstream>

int Variable::unnamed = 1;

Variable::Variable(std::string name/**<[in] name of variable*/, VarType type/**<[in] type of Variable*/) : name(name), type(type) {

	if(name.length() == 0){
		std::ostringstream ss;
		ss << "tempVar" << unnamed++;
		this->name = ss.str();
	}
};

std::string Variable::getTypeString() const{
	/**Gets type of Variable*/
	switch(type){
	case number:
		return "Number";
		break;
	case matrix:
		return "Matrix";
		break;
	case complex:
		return "Complex";
		break;
	default:
		return "Unknown type string";
	}
	///\return Prints Variable::VarType of the Variable
}

std::ostream& operator<<(std::ostream& out, Variable const& variable){
	/**Variable::getString()*/
	out << variable.getString();
	return out;///\return prints Variable Value
