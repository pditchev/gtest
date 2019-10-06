#pragma once
#include <memory>

struct Result {
	Result(int value) : value(value) {}
	int value;
};

class CalculationEngine {
	std::unique_ptr<Result> result;
	int operand;
//	std::shared_ptr<Operation> operation;

public:
	int getResult() {
		std::cout << result << '\n';
		return result->value;
	}


	//void setOperand(int value) {
	//	operand = value;
	//	if (this->operation) {
	//		result->value = operation->operate(operand);
	//		operation = nullptr;
	//	}
	//}

	//void setOperation(std::shared_ptr<Operation> operation) {
	//	this->operation = operation;
	//	result = std::make_unique<Result>(Result(this->operation->operate(operand)));//!!!!????

	//}

	//int getOperand() const {
	//	return operand;
	//}

	//auto getOperation()const {
	//	return operation;
	//}

};