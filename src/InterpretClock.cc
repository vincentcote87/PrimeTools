#include "InterpretClock.h"

void positionClkOutput(const int theWidth, const char fillingCharacter) {
	std::cout << std::right << std::setfill(fillingCharacter) << std::setw(theWidth);
}

void interpretClk(const std::chrono::milliseconds& a) {
   long long count = a.count();
   const long long h = count / 3600000;
   count %= 3600000;
   const long long min = count / 60000;
   count %= 60000;
   const long long s = count / 1000;
   count %= 1000;
   const long long ms = count;
   std::cout << "Ran for: ";
   std::cout << h;
   std::cout << ':';
   positionClkOutput(2);
   std::cout << min;
   std::cout << ':';
   positionClkOutput(2);
   std::cout << s;
   std::cout << '.';
   positionClkOutput(3);
   std::cout << ms;
   std::cout << std::endl;
}

void interpretClk(const std::chrono::steady_clock::duration dur) {
	interpretClk(std::chrono::duration_cast<std::chrono::milliseconds>(dur));
}
