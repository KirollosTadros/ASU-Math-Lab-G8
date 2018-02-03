#ifndef NUMBER_H
#define NUMBER_H

#include "variable.h"

class Number : public Variable{
public:
	double value/**Value of Number*/;
	Number(double const value /**<[in] value of Number*/, std::string name = ""/**<[in] name of Number*/) :
		Variable(name, Variable::number), value(value) {}
	operator double() {return value;}
	std::string getString() const;
	friend std::ostream& operator<<(std::ostream& out, Number const& number);
};

#endif //NUMBER_H
