#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class Variable{
public:
	enum VarType{matrix, number, complex};
	std::string getName() const {return name;}
	void setName(std::string name) {this->name = name;}
	VarType getType() const {return type;}
	std::string getTypeString() const;
	virtual ~Variable() {}
	virtual std::string getString() const = 0;
	friend std::ostream& operator<<(std::ostream& out, Variable const& variable);
protected:
	std::string name;
	VarType type;
	Variable(std::string name, VarType type);
	//disable copying Variable objects
	Variable(Variable const& other) = delete;
	Variable& operator=(Variable const& rhs) = delete;
	static int unnamed;
};


#endif //VARIABLE_H
