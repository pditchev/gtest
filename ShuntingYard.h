#pragma once

#include <stack>
#include <queue>
#include <memory>
#include <string>
#include "Element.h"


class ShuntingYard {
	std::stack<std::shared_ptr<Element>> workingStack;
	std::queue<std::shared_ptr<Element>> output;
	std::queue<std::shared_ptr<Element>> input;

public:
	void init(const std::vector<std::shared_ptr<Element>>& tokens) {
		for (auto& t : tokens)
			input.push(t);
	}

	void convert() {
		while (!input.empty()) {
			auto token = input.front();

			if (auto t = std::dynamic_pointer_cast<Numerical>(token))
				output.push(token);

			else if (auto op = std::dynamic_pointer_cast<Operation>(token)) {

				while ( !workingStack.empty() ) { 

					if (auto w = std::dynamic_pointer_cast<Operation>(workingStack.top());
						w &&
						precedenceMap.at(op->getOperation())
						<=
						precedenceMap.at(w->getOperation())
						)
					{
						output.push(workingStack.top());
						workingStack.pop();
					}
					else break;
				}
						  
				workingStack.push(op);
			}
			else if (auto paren = std::dynamic_pointer_cast<Parenthesis>(token)) {
				if (paren->getType() == ParenthesisType::opening) {
					workingStack.push(paren);
				}
				else {
					while(!std::dynamic_pointer_cast<Parenthesis>(workingStack.top()))
					{
						output.push(workingStack.top());
						workingStack.pop();
					}
					workingStack.pop();
				}
			}
			input.pop();
		}
		while (!workingStack.empty()) {
			output.push(workingStack.top());
			workingStack.pop();
		}
	}
	
	std::string showInput() {
		std::queue<std::shared_ptr<Element>> temp{ input };
		std::string result;
		while (!temp.empty()) {
			result += temp.front()->print();
			temp.pop();
		}
		return result;
	}

	std::string showOutput() {
		std::queue<std::shared_ptr<Element>> temp{ output };
		std::string result;
		while (!temp.empty()) {
			result += temp.front()->print();
			temp.pop();
		}
		return result;
	}

};
