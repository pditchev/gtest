#pragma once
#include <string>
#include <map>


enum class ElementType {number, operation, precedence_qualifier};
enum class NumericalType {INT, DOUBLE};
enum class OperationType {multiplication, division, addition, substraction, factorial};
enum class ParenthesisType {opening, closing};

const std::map < OperationType, int> precedenceMap {
	{OperationType::multiplication,	10},
	{OperationType::division,		10},
	{OperationType::addition,		 5},
	{OperationType::substraction,	 5},
	{OperationType::factorial,		15}
};

class Element {
protected:
	ElementType type;
public:
	Element(ElementType type) : type(type) {}

	virtual std::string print() = 0;

	ElementType getType() {
		return type;
	}
};

class Numerical : public Element {
	std::string value;
	NumericalType num_type;
public:
	Numerical( NumericalType t, std::string val) 
				:  Element(ElementType::number) {
		num_type = t;
		value = val;
	}

	std::string print() override {
		return value;
	}

	std::string getType() {
		if (type == ElementType::number)
			return "number";
		else
			return "other";
	}
};

class Operation : public Element {
	OperationType op_type;
//	int precedence;
public:
	Operation(OperationType t)
		: Element(ElementType::operation) {
		op_type = t;
	}

	OperationType getOperation() {
		return op_type;
	}


	std::string print() override {
		switch (op_type) {
		case OperationType::addition :
			return "+";
		case OperationType::substraction :
			return "-";
		case OperationType::multiplication :
			return "*";
		case OperationType::division :
			return "/";
		case OperationType::factorial :
			return "!";
		}
	}
};

class Addition : public Operation {

};



class Parenthesis : public Element {
	ParenthesisType p_type;
public:
	Parenthesis(ParenthesisType t)
		: Element(ElementType::precedence_qualifier) {
		p_type = t;
	}

	ParenthesisType getType() {
		return p_type;
	}

	std::string print() override {
		if (p_type == ParenthesisType::opening)
			return "(";
		else
			return ")";
	}
};
