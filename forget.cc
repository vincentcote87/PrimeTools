#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

int main() {
   for (long long i = 10; i <= 1000000000000; i *= 10) {
      system(("forget.sh comparison " + to_string(i)).c_str());
   }
   return 0;
}
