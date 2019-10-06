#pragma once
#include <string>
#include <memory>
#include "Operations.h"
#include "CalculationEngine.h"


class InputInterpreter {
public:
	CalculationEngine engine;
	int value;
	std::string input;
	std::shared_ptr<Operation> operation;

public:
	void setInput(const std::string& input) {
		this->input = input;
		if(auto firstChar = getChar(this->input))
			parseNextToken(firstChar);
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

	bool is_part_of_number(char x) {
		return isdigit(x) || x == '.';
	}

	void parseNextToken(char x) {
		std::string parsed;

		while (is_part_of_number(x)) {
			parsed += x;
			x = getChar(this->input);
			if (!x) break; // end of inputStr
		}
		if (!parsed.empty()) {
			engine.setOperand(to_Int(parsed));
			parsed.clear();
		}
		switch (x) {
		case '/':
			engine.setOperation(std::make_shared<Division>());
			break;
		case '*':
			engine.setOperation(std::make_shared<Multiplication>());
			break;
		case '=':
			engine.setOperation(std::make_shared<EndOperation>());
			break;
		}
		if (auto x = getChar(this->input))
			parseNextToken(x);
	}


	int getValue() const {
		return value;
	}

	auto getOperation() const {
		return operation;
	}
};
