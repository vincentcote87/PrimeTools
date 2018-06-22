#include <iostream>
#include "N.hpp"

using namespace std;

int main() {
   while (true) {
      cout << "Enter x u l k\n";
      integer x, u, l, k;
      cin >> x >> u >> l >> k;
      integer result = N(x, u, l, k);
      std::cout << "N(" << x << ", " << u << ", " << l << ", " << k << ") = ";
      std::cout << result << "\n\n" << std::endl;
   }
   return 0;
}
