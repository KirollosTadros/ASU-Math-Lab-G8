#include "number.h"
#include <string>
#include <sstream>


std::string Number::getString() const{
	std::ostringstream ss;
	ss << name << " = ";
	ss << value; 	//can also be written: ss << *this
					//thanks to overloading (operator double)
	return ss.str();
}

std::ostream& operator<<(std::ostream& out, Number const& number){
	out << number.getString();
	return out;
}
