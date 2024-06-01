#include "Board.h"
#include "Stepper.h"

//#include <limits.h>

#include "gtest/gtest.h"

#define MOTOR_PIN_COUNT 4
namespace {

  class TestBoard : public Board {

    private: 
      const int stepperPinCount = MOTOR_PIN_COUNT;
      int stepperPins[MOTOR_PIN_COUNT];

    public:
      TestBoard() {
        for (int i=0;i<stepperPinCount;i++)
          stepperPins[i]=0;
      }

      void writeMotor(int pinValues[]) {
        for (int i=0;i<stepperPinCount;i++)
          stepperPins[i]=pinValues[i];
      };

      int* getMotor() {
        return stepperPins;
      }
  };


TEST(TestStepper, Initialize) {
  TestBoard board;

  Stepper stepper(4,&board);

  for(int i=0; i<4; i++)
    EXPECT_EQ(0,board.getMotor()[i]);
}

void printMotor(TestBoard* boardPtr){
  printf("%Motor values:{");
  for(int i=0;i<4;i++) printf("%d",boardPtr->getMotor()[i]);
  printf("}");
}

void compareMotor(int compareValues[], TestBoard* boardPtr) {
  for(int i=0; i<4; i++)
    EXPECT_EQ(compareValues[i],boardPtr->getMotor()[i]);
}

TEST(TestStepper, FirstStep) {
  TestBoard board;
  Stepper stepper(4,&board);
  stepper.step();

  int compareValues[] = {1,0,0,0};
  compareMotor(compareValues,&board);
}


TEST(TestStepper, ForwardSteps) {
  TestBoard board;
  Stepper stepper(4,&board);

  int compareValues[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; i++) {
    stepper.step();
    compareMotor(compareValues[i],&board);
  }
}

TEST(TestStepper, BackwardSteps) {
  TestBoard board;
  Stepper stepper(4,&board);

  int compareValues[4][4] = {{0,0,1,0},{0,1,0,0},{1,0,0,0},{0,0,0,1}};
  for (int i=0; i<4; i++) {
    stepper.step(false);
    compareMotor(compareValues[i],&board);
  }
}

}  // namespace

// Step 3. Call RUN_ALL_TESTS() in main().
//
// We do this by linking in src/gtest_main.cc file, which consists of
// a main() function which calls RUN_ALL_TESTS() for us.
//
// This runs all the tests you've defined, prints the result, and
// returns 0 if successful, or 1 otherwise.
//
// Did you notice that we didn't register the tests?  The
// RUN_ALL_TESTS() macro magically knows about all the tests we
// defined.  Isn't this convenient?
int main(int argc, char **argv)
{
    printf("Running main() from %s\n", __FILE__);

    ::testing::InitGoogleTest(&argc, argv);
	if (RUN_ALL_TESTS())
	;
	// Always return zero-code and allow PlatformIO to parse results
	return 0;
}