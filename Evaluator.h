#pragma once
#include <queue>
#include <stack>
#include <memory>
#include "Element.h"


class Evaluator {
public:

	int evaluate(std::queue<std::shared_ptr<Element>>& rpn_queue) {
		std::stack<std::shared_ptr<Numerical>> operands;

		while (!rpn_queue.empty()) {
			if (auto n = std::dynamic_pointer_cast<Numerical>(rpn_queue.front()))
			{
				operands.push(n);
				rpn_queue.pop();
			}
			else
			{
				auto oper = std::static_pointer_cast<Operation>(rpn_queue.front());
				oper->operate(operands);
				rpn_queue.pop();
			}
		}

		return operands.top()->getValue();
	}



};