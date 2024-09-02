#include "pch.h"
#include "CppUnitTest.h"

#include "../TACSimulator/include/Simulator/Simulator.h"
#include "../TACSimulator/include/Assembler/Assembler.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TACSimulatorTests
{
	TEST_CLASS(TACSimulatorTests) {
private:
	Simulator runProgram(const string& inputPath, const string& outputPath) {
		Assembler assembler;
		assembler.assembleFile(inputPath, outputPath);

		// The simulator can hold quite a bit of simulated memory.
		// So, we're using the heap.
		Simulator simulator;
		simulator.loadProgramIntoRAM(outputPath);
		simulator.executeProgram();

		return simulator;
	}
	


	public:
		TEST_METHOD(TestRegInsn) {

			string fileName = "regInsn";
			string input = "../../TACSimulator/assemblyFiles/" + fileName + ".asm";
			string output = "../../TACSimulator/assemblyFiles/output/" + fileName + ".out";

			Simulator simulator = runProgram(input, output);
			std::array<int32_t, 32> registers = simulator.dumpRegisters();
			
			Assert::IsTrue(registers[1] == 3);
			Assert::IsTrue(registers[2] == -1000);
			Assert::IsTrue(registers[3] == -1000);
			Assert::IsTrue(registers[4] == 1000);
			Assert::IsTrue(registers[5] == -3);
			Assert::IsTrue(registers[6] == 16);
			Assert::IsTrue(registers[7] == -516);
			Assert::IsTrue(registers[8] == -532);
			Assert::IsTrue(registers[9] == 515);
			Assert::IsTrue(registers[10] == 1);
			Assert::IsTrue(registers[11] == 80);
		}

		TEST_METHOD(TestMemInst) {
			string fileName = "memInst";
			string input = "../../TACSimulator/assemblyFiles/" + fileName + ".asm";
			string output = "../../TACSimulator/assemblyFiles/output/" + fileName + ".out";

			Simulator simulator = runProgram(input, output);
			std::array<int32_t, 32> registers = simulator.dumpRegisters();

			Assert::IsTrue(registers[1] == -1000);
			Assert::IsTrue(registers[2] == 200);
			Assert::IsTrue(registers[3] == 300);
			Assert::IsTrue(registers[4] == 400);

			Assert::IsTrue(registers[5] == -1000);
			Assert::IsTrue(registers[6] == -1000);
			Assert::IsTrue(registers[7] == -1000);
			Assert::IsTrue(registers[8] == 800);
			Assert::IsTrue(registers[9] == 900);
			Assert::IsTrue(registers[10] == 1000);

			Assert::IsTrue(registers[11] == 255);
			Assert::IsTrue(registers[12] == 255);
			Assert::IsTrue(registers[13] == 255);
			Assert::IsTrue(registers[14] == 255);

			Assert::IsTrue(simulator.loadWord(200) == -1000);
			Assert::IsTrue(simulator.loadWord(290) == -1000);
			Assert::IsTrue(simulator.loadWord(410) == -1000);

			Assert::IsTrue(simulator.loadByte(800) == 255);
			Assert::IsTrue(simulator.loadByte(890) == 255);
			Assert::IsTrue(simulator.loadByte(1010) == 255);
		}
	};
}
