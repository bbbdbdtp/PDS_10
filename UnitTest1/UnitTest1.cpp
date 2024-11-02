#include "pch.h"
#include "CppUnitTest.h"
#include "../PDS_10/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1 {
	TEST_CLASS(UnitTest1) {
	public:
        TEST_METHOD(TestReadGraphAndPrintWeightMatrix) {
            std::ofstream testInput("testInput.txt");
            testInput << "3 3\n";
            testInput << "1 2 5\n";
            testInput << "2 3 7\n";
            testInput << "3 1 9\n";
            testInput.close();

            int n, m;
            int** weightMatrix = nullptr;
            readGraph("testInput.txt", n, m, weightMatrix);

            Assert::AreEqual(3, n);
            Assert::AreEqual(3, m);

            Assert::AreEqual(INF, weightMatrix[0][0]);
            Assert::AreEqual(5, weightMatrix[0][1]);
            Assert::AreEqual(INF, weightMatrix[0][2]);
            Assert::AreEqual(INF, weightMatrix[1][0]);
            Assert::AreEqual(INF, weightMatrix[1][1]);
            Assert::AreEqual(7, weightMatrix[1][2]);
            Assert::AreEqual(9, weightMatrix[2][0]);
            Assert::AreEqual(INF, weightMatrix[2][1]);
            Assert::AreEqual(INF, weightMatrix[2][2]);

            printWeightMatrix(weightMatrix, n, "testOutput.txt");
            std::ifstream testOutput("testOutput.txt");
            std::string line;
            std::string expectedOutput[] = {
                "INF 5 INF ",
                "INF INF 7 ",
                "9 INF INF "
            };

            for (int i = 0; i < 3; ++i) {
                std::getline(testOutput, line);
                Assert::AreEqual(expectedOutput[i], line);
            }
            testOutput.close();
            deleteMatrix(weightMatrix, n);
            std::remove("testInput.txt");
            std::remove("testOutput.txt");
        }
	};
}
