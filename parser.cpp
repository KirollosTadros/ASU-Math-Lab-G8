#include "parser.h"
#include <vector>
#include <string>
#include <cstddef>
#include <iostream>
#include "number.h"
#include "matrix.h"

Parser::~Parser(){
	if(!varList.empty()){
		for(auto it=varList.begin(); it!=varList.end(); ++it){
			delete *it;
		}
	}
}

void Parser::addVar(Variable* var){
	varList.push_back(var);
}

Variable* Parser::findVar(std::string varName) const{
	if(varList.empty()){
		return nullptr;
	}
	for(std::vector<Variable*>::const_iterator it=varList.begin(); it!=varList.end(); ++it){
		Variable* var = *it;
		if(var->getName() == varName){
			return var;
		}
	}
	return nullptr;
}

void Parser::printVars() const{
	for(auto it=varList.begin(); it!=varList.end(); ++it){
		Variable* var = *it;
		switch(var->getType()){
		case Variable::number:
			std::cout << *(Number*) var << std::endl;
			break;
		case Variable::matrix:
			std::cout << *(Matrix*) var << std::endl;
			break;
		}
	}
}

void Parser::parse(std::string){
	//todo implement or remove from class
}

void Parser::evaluate(){
	//todo implement or remove from class
}
