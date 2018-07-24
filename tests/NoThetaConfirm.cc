#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"

void interpretClk(const std::chrono::milliseconds& a) {
   long long count = a.count();
   const long long h = count / 3600000;
   count %= 3600000;
   const long long min = count / 60000;
   count %= 60000;
   const long long s = count / 1000;
   count %= 1000;
   const long long ms = count;
   std::cout << "Ran for: " << h << ':' << std::right << std::setfill('0') << std::setw(2) << min << ':' << s << ':' << ms << std::endl;
}

uint64_t toTheTen(const uint64_t target) {
	switch (target) {
		case 0:
			return 1;
		case 1:
			return 10;
		default:
			if (target % 2 == 0) {
				return toTheTen(target/2) * toTheTen(target/2);
			}
			return toTheTen(target/2) * toTheTen(target/2) * 10;
	}
}

int main() {
	setupEnvironment();
  	std::chrono::steady_clock clk;
  	uint64_t x;
	for (uint64_t power = 6; power <= 15; ++power) {
		for (uint64_t dig = 1; !( dig > 9 || (x = dig * toTheTen(power)) > 1000000000000000); ++dig) {
			std::cout << x << "\n";
			auto before = clk.now();
			std::cout << "Power Psi:           " << primetools::calculatePsiNoTheta(x) << std::endl;
			auto endTime = clk.now();
			interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - before));
			before = clk.now();
			std::cout << "Theta Psi:           " << primetools::calculatePsiLongDouble(x) << std::endl;
			endTime = clk.now();
			interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - before));
			before = clk.now();
			//std::cout << "Deleglise-Rivat Psi: " << psi(x) << std::endl;
			//endTime = clk.now();
			//interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - before));
			//before = clk.now();
		}
	}
	return 0;
}
