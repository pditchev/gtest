#include "pch.h"
#include "InputInterpreter.h"


class InputInterpreterTests : public testing::Test {
public:
	InputInterpreter interpreter;
};

TEST_F(InputInterpreterTests, GetResultOfMultiplication) {
	std::string input = "4 *2=";
	interpreter.setInput(input);
	auto operand = interpreter.engine.getResult();
	ASSERT_THAT(operand, testing::Eq(8));
}

TEST_F(InputInterpreterTests, GetResultOfEqualSign) {
	std::string input = "42=";
	interpreter.setInput(input);
	auto operand = interpreter.engine.getResult();
	ASSERT_THAT(operand, testing::Eq(42));
}
TEST_F(InputInterpreterTests, GetOperationFromInput) {
	std::string input = "21*";
	interpreter.setInput(input);
	auto operation = std::dynamic_pointer_cast<Multiplication>
		(interpreter.engine.getOperation());
	ASSERT_TRUE(operation);
}


TEST_F(InputInterpreterTests, GetValueFromInput) {
	std::string input = "21";
	interpreter.setInput(input);
	auto operand = interpreter.engine.getOperand();
	ASSERT_THAT(operand, testing::Eq(21));
}


TEST_F(InputInterpreterTests, GetSuccessiveTokens) {


	std::string input = "21";
	//interpreter.setInput(input);

	auto operand = interpreter.getChar(input);
	ASSERT_EQ(operand, '2');
	operand = interpreter.getChar(input);
	ASSERT_EQ(operand, '1');
}

int main(int argc, char* argv[]) {

	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}