#include "variable.h"
#include <string>
#include <sstream>

int Variable::unnamed = 1;

Variable::Variable(std::string name, VarType type) : name(name), type(type) {
	if(name.length() == 0){
		std::ostringstream ss;
		ss << "tempVar" << unnamed++;
		this->name = ss.str();
	}
};

std::string Variable::getTypeString() const{
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
}

std::ostream& operator<<(std::ostream& out, Variable const& variable){
	out << variable.getString();
	return out;
}
