#pragma once
#include <string>


enum class ElementType {number, operation, precedence_qualifier};
enum class NumericalType {INT, DOUBLE};
enum class OperationType {multiplication, division, addition, substraction, factorial};
enum class ParenthesisType {opening, closing};

class Element {
protected:
	ElementType type;
public:
	Element(ElementType type) : type(type) {}

	virtual std::string print() = 0;
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
public:
	Operation(OperationType t)
		: Element(ElementType::operation) {
		op_type = t;
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

	std::string print() override {
		if (p_type == ParenthesisType::opening)
			return "(";
		else
			return ")";
	}
};
