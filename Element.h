#pragma once
#include <string>
#include <map>
#include <stack>
#include <any>


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

struct Element {
	virtual std::string print() = 0;

};

class Numerical : public Element {
public:
	virtual int getValue() const = 0;
};

class Integer : public Numerical {
	int value;
public:
	explicit Integer(int v): value(v){}

	int getValue() const override {
		return value;
	}

	std::string print() override {
		return std::to_string(value);
	}
};

//class Double : public Numerical {
//	double value;
//public:
//	std::any getValue() const override {
//		return value;
//	}
//	std::string print() override {
//		return std::to_string(value);
//	}
//};

class Operation : public Element {
	OperationType op_type;
public:

	virtual int getPrecedence() const = 0;

	virtual void operate(std::stack<std::shared_ptr<Numerical>>& input) = 0;

	//Operation(OperationType t) : op_type(t) {}

	//OperationType getOperation() {
	//	return op_type;
	//}


	//std::string print() override {
	//	switch (op_type) {
	//	case OperationType::addition :
	//		return "+";
	//	case OperationType::substraction :
	//		return "-";
	//	case OperationType::multiplication :
	//		return "*";
	//	case OperationType::division :
	//		return "/";
	//	case OperationType::factorial :
	//		return "!";
	//	}
	//}
};

class Addition : public Operation {
	std::shared_ptr<Numerical> lhs, rhs;

public:
	virtual int getPrecedence() const override {
		return 5;
	}

	virtual std::string print() override {
		return "+";
	}

	virtual void operate(std::stack<std::shared_ptr<Numerical>>& input) override {
		lhs = input.top();
		input.pop();
		rhs = input.top();
		input.pop();

		auto result = lhs->getValue() + rhs->getValue();
		input.emplace(std::make_shared<Integer>(result));
	}
};

class Substraction : public Operation {
	std::shared_ptr<Numerical> lhs, rhs;

public:
	virtual int getPrecedence() const override {
		return 5;
	}

	virtual std::string print() override {
		return "-";
	}

	virtual void operate(std::stack<std::shared_ptr<Numerical>>& input) override {
		rhs = input.top();
		input.pop();
		lhs = input.top();
		input.pop();

		auto result = lhs->getValue() - rhs->getValue();
		input.emplace(std::make_shared<Integer>(result));
	}
};

class Multiplication : public Operation {
	std::shared_ptr<Numerical> lhs, rhs;

public:
	virtual int getPrecedence() const override {
		return 10;
	}

	virtual std::string print() override {
		return "*";
	}

	virtual void operate(std::stack<std::shared_ptr<Numerical>>& input) override {
		lhs = input.top();
		input.pop();
		rhs = input.top();
		input.pop();

		auto result = lhs->getValue() * rhs->getValue();
		input.emplace(std::make_shared<Integer>(result));
	}
};

class Division : public Operation {
	std::shared_ptr<Numerical> lhs, rhs;

public:
	virtual int getPrecedence() const override {
		return 10;
	}

	virtual std::string print() override {
		return "/";
	}

	virtual void operate(std::stack<std::shared_ptr<Numerical>>& input) override {
		rhs = input.top();
		input.pop();
		lhs = input.top();
		input.pop();

		auto result = lhs->getValue() / rhs->getValue();
		input.emplace(std::make_shared<Integer>(result));
	}
};

class Parenthesis : public Element {
	ParenthesisType p_type;
public:
	Parenthesis(ParenthesisType t) : p_type(t) {}

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
