#include <iostream>
#include <chrono>
#include "Primetools.h"
#include "int_double.h"
#include "PsiTools.h"
#include "N.h"
#include "InterpretClock.h"
#include <exception>

using std::cout;
using std::endl;

mpfr::mpreal B = 0.2614972128476427837554268386086958590516;

mpfr::mpreal A(uint64_t, mpfr::mpreal);
// Should keep interval size < 10^9
vector<vector<uint64_t>> getInterval(uint64_t, uint64_t);
mpfr::mpreal getRunningSum(uint64_t);
mpfr::mpreal getMax(mpfr::mpreal, mpfr::mpreal);

int main() {
  uint64_t lb = 0;
  uint64_t ub = 0;
  cout<<"Enter the lower bound ( > 0): ";
  cin>>lb;
  cout<<"Enter the upper bound (Keep interval size <= 10^9): ";
  cin>>ub;

  mpfr::mpreal::set_default_prec(1024);
  std::cout << std::setprecision(12) << std::scientific;
  vector<mpfr::mpreal> max;
  max.resize(100);
  mpfr::mpreal sum;
  mpfr::mpreal one = 1.0;
  mpfr::mpreal tmp1;
  mpfr::mpreal tmp2;

  uint64_t bottom;
  uint64_t top = 0;
  uint64_t index = 0;

  max[index] = 0;

  vector<vector<uint64_t>> interval = getInterval(lb, ub);
  sum = getRunningSum(lb);
  for (int z = 0; z < interval[0].size(); ++z) {
    tmp1 = A(interval[0][z], sum);
    tmp2 = A(interval[1][z], sum);
    sum += one/interval[1][z];
    if (getMax(tmp1, tmp2) > max[index])
        max[index] = getMax(tmp1, tmp2);
    }
      cout<<"Interval ("<<lb<<","<<ub<<") has a max of "<<max[index]<<endl;

  // for (uint64_t i = 1; i <= 9; ++i) {
  //   for (uint64_t j = 1; j <= 9; ++j) {
  //     bottom = top;
  //     top = j * pow(10, i);
  //     max[index] = 0;
  //     vector<vector<uint64_t>> interval = getInterval(bottom, top);
  //     sum = getRunningSum(bottom);
  //     for (int z = 0; z < interval[0].size(); ++z) {
  //       tmp1 = A(interval[0][z], sum);
  //       tmp2 = A(interval[1][z], sum);
  //       sum += one/interval[1][z];
  //       if (getMax(tmp1, tmp2) > max[index])
  //         max[index] = getMax(tmp1, tmp2);
  //     }
  //     cout<<"Interval ("<<bottom<<","<<top<<") has a max of "<<max[index]<<endl;
  //     index++;
  //   }
  // }
return 0;
}

mpfr::mpreal A(uint64_t y, mpfr::mpreal p) {
  mpfr::mpreal ans = p - mpfr::log(mpfr::log(y)) - B;
  return ans < 0 ? ans * -1 : ans;
}

vector<vector<uint64_t>> getInterval(uint64_t bottom, uint64_t top) {
  primesieve::iterator it;
  uint64_t temp;
  vector<uint64_t> low;
  vector<uint64_t> high;

  it.skipto(bottom);
  temp = it.prev_prime();
  low.push_back(bottom);
  high.push_back(temp = it.next_prime());
  while (temp < top) {
    low.push_back(temp);
    temp = it.next_prime();
    if (temp < top)
      high.push_back(temp);
  }
  high.push_back(top);
  vector<vector<uint64_t>> newInterval = {low, high};
  return newInterval;
}

mpfr::mpreal getRunningSum(uint64_t upTo) {
  if (upTo == 0)
    return 0;
  primesieve::iterator it;
  it.skipto(0);
  uint64_t prime = it.next_prime();
  mpfr::mpreal sum;
  mpfr::mpreal one = 1.0;
  for (; prime <= upTo; prime = it.next_prime()) {
    // force it to use mpreal division
      sum += one/prime;
    // cout<<prime<<endl;
  }
  return sum;
}

mpfr::mpreal getMax(mpfr::mpreal x, mpfr::mpreal y) {
  return x > y ? x : y;
}