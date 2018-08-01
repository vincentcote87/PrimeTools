#include <iostream>
#include <cmath>

int main() {
   long double x, u;
   long long a;
   while (true) {
      std::cin >> a;
      x = a;
      u = std::cbrtl(static_cast<long double>(x)) * std::cbrtl(std::log(std::log(x))*std::log(std::log(x)));
      std::cout << u << std::endl;
   }
   return 0;
}
