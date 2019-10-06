#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Element.h"
#include "Operations.h"
#include "CalculationEngine.h"

const std::string operations{ "+-*/!" };


class InputInterpreter {
	std::vector<std::shared_ptr<Element>> parsedExpression;
	bool consistent = false;
public:
	CalculationEngine engine;
	int value;
	std::string input;

public:
	std::vector<std::shared_ptr<Element>> getParsedElements() {
		return parsedExpression;
	}

	void init(const std::string& input) {
		this->input = input;
		parseInput();
		consistent = checkConsistency();
	}

	bool checkConsistency() {
		if (!input.empty())
			return false;

		int parentheses = 0;
		for (auto e : parsedExpression) {
			if (e->print() == "(")
				++parentheses;
			if (e->print() == ")")
				--parentheses;
			if (parentheses < 0)
				return false;
		}
		if (!parentheses)
			return false;



	}

	bool is_operation(char x) {
		return operations.find(x) != std::string::npos;
	}

	bool is_parenthesis(char x) {
		return x == '(' || x == ')';
	}

	void parseInput() {
		while (!input.empty()) {
			if (is_part_of_number(input[0])) {
				parsedExpression.emplace_back(parseNumber(input));
			}
			else if (is_operation(input[0])) {
				parsedExpression.emplace_back(parseOperation(input));
			}
			else if (is_parenthesis(input[0])) {
				parsedExpression.emplace_back(parseParenthesis(input));
			}
			else break;
		}
	}

	std::shared_ptr<Parenthesis> parseParenthesis(std::string& str) {
		char a = str[0];
		str.erase(str.begin());
		if (a == '(')
			return std::make_shared<Parenthesis>(ParenthesisType::opening);
		else
			return std::make_shared<Parenthesis>(ParenthesisType::closing);
	}


	std::shared_ptr<Operation> parseOperation(std::string& str) {
		std::shared_ptr<Operation> p;
		switch (str[0]) {
		case '+':
			 p = std::make_shared<Operation>(OperationType::addition);
			break;
		case '-':
			 p = std::make_shared<Operation>(OperationType::substraction);
			break;
		
		case '*':
			p = std::make_shared<Operation>(OperationType::multiplication);
			break;
		case '/':
			p = std::make_shared<Operation>(OperationType::division);
			break;
		case '!':
			p = std::make_shared<Operation>(OperationType::factorial);
			break;
		}

		str.erase(str.begin());
		return p;
	
	}



	std::shared_ptr<Numerical> parseNumber(std::string& str) {
		char* out_strI;
		char* out_strD;

		int parsedInt = strtol(str.c_str(), &out_strI, 10);
		double parsedDouble = strtod(str.c_str(), &out_strD);
		if (parsedInt == parsedDouble) {
			str = std::string(out_strI);

			return std::make_shared<Numerical>
					(NumericalType::INT, std::to_string(parsedInt));
		}
		else {
			str = std::string(out_strD);
			return std::make_shared<Numerical>
					(NumericalType::DOUBLE, std::to_string(parsedDouble));
		}
	}

	bool is_part_of_number(char x) {
		return isdigit(x) || x == '.';
	}

	char getChar(std::string& inputStr) {
		if (inputStr.size() == 0)
			return 0;
		char x = inputStr[0];
		inputStr.erase(inputStr.begin());
		return x;
	}

	int to_Int(const std::string& str) const {
		return strtol(str.c_str(), nullptr, 10);
	}



	//void parseNextToken(char x) {
	//	std::string parsed;

	//	while (is_part_of_number(x)) {
	//		parsed += x;
	//		x = getChar(this->input);
	//		if (!x) break; // end of inputStr
	//	}
	//	if (!parsed.empty()) {
	//		engine.setOperand(to_Int(parsed));
	//		parsed.clear();
	//	}
	//	switch (x) {
	//	case '/':
	//		engine.setOperation(std::make_shared<Division>());
	//		break;
	//	case '*':
	//		engine.setOperation(std::make_shared<Multiplication>());
	//		break;
	//	case '=':
	//		engine.setOperation(std::make_shared<EndOperation>());
	//		break;
	//	}
	//	if (auto x = getChar(this->input))
	//		parseNextToken(x);
	//}


	int getValue() const {
		return value;
	}

	//auto getOperation() const {
	//	return operation;
	//}
};
