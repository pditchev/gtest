#pragma once
#include <string>
#include <memory>
#include <vector>
#include "Element.h"
#include "Operations.h"
#include "CalculationEngine.h"


class InputInterpreter {
	std::vector<Element> parsedExpression;
public:
	CalculationEngine engine;
	int value;
	std::string input;
	//std::shared_ptr<Operation> operation;

public:
	void setInput(const std::string& input) {
		this->input = input;
		//if(auto firstChar = getChar(this->input))
		//	parseNextToken(firstChar);
	}

	void ParseInput() {
		if (is_part_of_number(input[0])) {
			auto parsedNumber = parseNumber(input);
		}
	}

	std::shared_ptr<Numerical> parseNumber(std::string& str) {
		char* out_strI;
		char* out_strD;

		int parsedInt = strtol(str.c_str(), &out_strI, 10);
		double parsedDouble = strtod(str.c_str(), &out_strD);
		if (parsedInt == parsedDouble) {
			str = std::string(out_strI);

			return std::make_shared<Numerical>
					(NumericalType::integer, std::to_string(parsedInt));
		}
		else {
			str = std::string(out_strD);
			return std::make_shared<Numerical>
					(NumericalType::doubl, std::to_string(parsedDouble));
		}
		
		//return parsedInt;
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

	//auto getOperation() const {
	//	return operation;
	//}
};
