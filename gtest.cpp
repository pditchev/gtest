#include "pch.h"
#include "InputInterpreter.h"
#include "ShuntingYard.h"
#include "Evaluator.h"


class ShuntingYardTests : public testing::Test {
public:
	InputInterpreter interpreter;
	ShuntingYard shyard;
	Evaluator evaluator;
};

TEST_F(ShuntingYardTests, FinalResultAdvanced) {
	std::string input = "3 +4*(5-2)	/2";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	shyard.convert();

	auto rpn_queue = shyard.exposeRPNqueue();

	int check = evaluator.evaluate(rpn_queue);

	ASSERT_THAT(check, testing::Eq(9));
}

TEST_F(ShuntingYardTests, FinalResultSimple) {
	std::string input = "3 +4";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	shyard.convert();

	auto rpn_queue = shyard.exposeRPNqueue();

	int check = evaluator.evaluate(rpn_queue);

	ASSERT_THAT(check, testing::Eq(7));
}

TEST_F(ShuntingYardTests, CheckOutputWithParenthesisMoreAdv) {
	std::string input = "3 +4*	2/ (1-5)";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	shyard.convert();

	std::string check = shyard.showOutput();

	ASSERT_THAT(check, testing::Eq("342*15-/+"));
}

TEST_F(ShuntingYardTests, CheckOutputWithParenthesis) {
	std::string input = "2*(3+4)";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	shyard.convert();

	std::string check = shyard.showOutput();

	ASSERT_THAT(check, testing::Eq("234+*"));
}

TEST_F(ShuntingYardTests, CheckOutputWithPriorityOperands) {
	std::string input = "2*3+4";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	shyard.convert();

	std::string check = shyard.showOutput();

	ASSERT_THAT(check, testing::Eq("23*4+"));
}

TEST_F(ShuntingYardTests, CheckOutputNotSoSimple) {
	std::string input = "2+3*4";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	shyard.convert();

	std::string check = shyard.showOutput();

	ASSERT_THAT(check, testing::Eq("234*+"));
}

TEST_F(ShuntingYardTests, CheckOutputSimple) {
	std::string input = "2+3";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	shyard.convert();

	std::string check = shyard.showOutput();

	ASSERT_THAT(check, testing::Eq("23+"));
}

TEST_F(ShuntingYardTests, CheckInputSuccess) {
	std::string input = "(	* 36/)";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();
	shyard.init(elements);
	std::string check = shyard.showInput();

	ASSERT_THAT(check, testing::Eq("(*36/)"));
}

class InputInterpreterTests : public testing::Test {
public:
	InputInterpreter interpreter;
};

TEST_F(InputInterpreterTests, GetParenthesisFromVectorOfParsedElements) {
	std::string input = "(	* 36yahoo";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();

	ASSERT_THAT(elements[0]->print(), testing::Eq("("));
	ASSERT_THAT(elements[1]->print(), testing::Eq("*"));
	ASSERT_THAT(elements[2]->print(), testing::Eq("36"));
	ASSERT_THAT(interpreter.inputStr, testing::Eq("yahoo"));
}


TEST_F(InputInterpreterTests, GetAnotherTWoElementsFromVectorOfParsedElements) {
	std::string input = "*36yahoo";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();

	ASSERT_THAT(elements[0]->print(), testing::Eq("*"));
	ASSERT_THAT(elements[1]->print(), testing::Eq("36"));

	ASSERT_THAT(interpreter.inputStr, testing::Eq("yahoo"));

}

TEST_F(InputInterpreterTests, GetTWoElementsFromVectorOfParsedElements) {
	std::string input = "25+yahoo";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();

	ASSERT_THAT(elements[0]->print(), testing::Eq("25"));
	ASSERT_THAT(elements[1]->print(), testing::Eq("+"));

	ASSERT_THAT(interpreter.inputStr, testing::Eq("yahoo"));

}

TEST_F(InputInterpreterTests, GetFirstElementFromVectorOfParsedElements) {
	std::string input = "25yahoo";
	interpreter.init(input);
	auto elements = interpreter.getParsedElements();

	ASSERT_THAT(elements[0]->print(), testing::Eq("25"));
	ASSERT_THAT(interpreter.inputStr, testing::Eq("yahoo"));

}

//TEST_F(InputInterpreterTests, GetDoubleValueFromInput) {
//	std::string input = "21.5yahoo";
//	interpreter.init(input);
//	auto operand = interpreter.parseNumber(input);
//
//// to_string of a double returns 6 digits after the decimal-point character
//	ASSERT_THAT(operand->print(), testing::Eq("21.500000")); 
//	ASSERT_THAT(input, testing::Eq("yahoo"));
//
//}


TEST_F(InputInterpreterTests, GetIntValueFromInput) {
	std::string input = "21yahoo";
	interpreter.init(input);
	auto operand = interpreter.parseNumber(input);

	ASSERT_THAT(operand->print(), testing::Eq("21"));
	ASSERT_THAT(input, testing::Eq("yahoo"));

}

//TEST_F(InputInterpreterTests, GetResultOfMultiplication) {
//	std::string input = "4 *2=";
//	interpreter.setInput(input);
//	auto operand = interpreter.engine.getResult();
//	ASSERT_THAT(operand, testing::Eq(8));
//}
//
//TEST_F(InputInterpreterTests, GetResultOfEqualSign) {
//	std::string input = "42=";
//	interpreter.setInput(input);
//	auto operand = interpreter.engine.getResult();
//	ASSERT_THAT(operand, testing::Eq(42));
//}
//TEST_F(InputInterpreterTests, GetOperationFromInput) {
//	std::string input = "21*";
//	interpreter.setInput(input);
//	auto operation = std::dynamic_pointer_cast<Multiplication>
//		(interpreter.engine.getOperation());
//	ASSERT_TRUE(operation);
//}
//

//TEST_F(InputInterpreterTests, GetValueFromInput) {
//	std::string input = "21";
//	interpreter.setInput(input);
//	auto operand = interpreter.engine.getOperand();
//	ASSERT_THAT(operand, testing::Eq(21));
//}


//TEST_F(InputInterpreterTests, GetSuccessiveTokens) {
//
//
//	std::string input = "21";
//	//interpreter.setInput(input);
//
//	auto operand = interpreter.getChar(input);
//	ASSERT_EQ(operand, '2');
//	operand = interpreter.getChar(input);
//	ASSERT_EQ(operand, '1');
//}

int main(int argc, char* argv[]) {

	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}