#ifndef NUMBER_H
#define NUMBER_H

#include "variable.h"

class Number : public Variable{
public:
	double value;
	Number(double const value, std::string name = "") :
		Variable(name, Variable::number), value(value) {}
	operator double() {return value;}
	std::string getString() const;
	friend std::ostream& operator<<(std::ostream& out, Number const& number);
};

#endif //NUMBER_H
