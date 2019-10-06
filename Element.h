#pragma once
#include <string>


enum class ElementType {number, operation, precedence_qualifier};
enum class NumericalType {integer, doubl};

class Element {
protected:
	ElementType type;
	std::string value;
public:
	Element(ElementType type, std::string value) : type(type), value(value) {}
	//virtual void evaluate() = 0;
};

class Numerical : public Element {
	NumericalType num_type;
public:
	Numerical( NumericalType t, std::string val) 
				:  Element(ElementType::number, val) {
		num_type = t;
	}


	std::string getValue() {
		return value;
	}


	std::string getType() {
		if (type == ElementType::number)
			return "number";
		else
			return "other";
	}
};
