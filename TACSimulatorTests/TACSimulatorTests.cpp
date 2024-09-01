#include "pch.h"
#include "CppUnitTest.h"

#include "../TACSimulator/include/Simulator/Simulator.h"
#include "../TACSimulator/include/Assembler/Assembler.h"

using std::string;
using Microsoft::VisualStudio::CppUnitTestFramework::Assert;

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
		}
	};
}
