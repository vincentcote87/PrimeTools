#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

int main(int N, char* arg[]) {
   if (N != 3) {
      std::cout << "usage: " << std::endl;
      std::cout << "       " << arg[0] << " start stop" << std::endl;
   }
   const long long start = std::atoll(arg[1]);
   const long long stop = std::atoll(arg[2]);
   for (long long i = start; i <= stop; i *= 10) {
      for (long long j = 1; i*j > 0 && i <= stop && j <= 9; ++j) {
	 system(("simultaneous.sh main " + to_string(i*j)).c_str());
      }
   }
   return 0;
}
