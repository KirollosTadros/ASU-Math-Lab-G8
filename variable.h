#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

class Variable{
public:
	enum VarType{matrix/**<Matrix type Variable*/, number/**<Number type Variable*/, complex/**<complex type Variable*/};
	std::string getName() const {return name;}
	void setName(std::string name) {this->name = name;}
	VarType getType() const {/**gets type of Variable*/return type;/**\return Type of the Variable*/}
	std::string getTypeString() const;
	virtual ~Variable() {}
	virtual std::string getString() const = 0;
	friend std::ostream& operator<<(std::ostream& out, Variable const& variable);
protected:
	std::string name /**name of Variable*/;
	VarType type/**type of Variable*/;
	Variable(std::string name, VarType type);
	//disable copying Variable objects
	Variable(Variable const& other) = delete;
	Variable& operator=(Variable const& rhs) = delete;
	static int unnamed;
};


#endif //VARIABLE_H
