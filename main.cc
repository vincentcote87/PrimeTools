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

    // std::vector<int> low;
    // std::vector<int> high;

    // low.push_back(1);
    // low.push_back(3);
    // low.push_back(4);
    // high.push_back(0);
    // high.push_back(2);
    // high.push_back(6);

    // std::vector<std::vector<int>> twoD = {low, high};
    // std::cout<<twoD[1][0];

mpfr::mpreal B = 0.2614972128476427837554268386086958590516;

mpfr::mpreal A(uint64_t, mpfr::mpreal);
mpfr::mpreal Mn(uint64_t, mpfr::mpreal);
vector<uint64_t> getInterval(uint64_t, uint64_t);
mpfr::mpreal getRunningSum(uint64_t);

int main(int argc, char* argv[]) {

  mpfr::mpreal::set_default_prec(512);
  std::cout << std::setprecision(30) << std::scientific;

  mpfr::mpreal primeSum = 0;
  primesieve::iterator it;
  it.skipto(1);
  uint64_t prime = it.next_prime();
  uint64_t last = 10;
  vector<mpfr::mpreal> max;
  mpfr::mpreal runningSum;
  max.resize(80);
  vector<uint64_t> interval;
  interval = getInterval(0, 100);
  for (int i = 0; i < interval.size(); ++i) {
    if (i < interval.size() - 1) {
      cout<<"["<<interval[i]<<","<<interval[i+1]<<"] ";
    }
    // cout<<interval[i]<<" ";
  }
  cout<<endl;
  // cout<<"["<<interval[0]<<","<<interval[1]<<") and get intervals up to "<<interval[2]<<endl;

  uint64_t bottom;
  uint64_t top;
  uint64_t index = 0;

  for (uint64_t i = 1; i < 9; ++i) {
    for (uint64_t j = 1; j < 9; ++j) {
      bottom = j * pow(10, i);
      if (j + 1 < 10) {
        top = (j + 1) * pow(10, i);
      } else {
        top = pow(10, i + 1);
      }
      cout<<"interval is "<<bottom<<" to "<<top<<" ";
      interval = getInterval(bottom, top);
      runningSum = getRunningSum(interval[0]);
      cout<<"with first prime ="<<interval[0]<<" and last prime ="<<interval[1]<<" and last prime - 1 ="<<interval[2]<<endl;
      // cout<<"Running sum up to "<<interval[0]<<" is = "<<runningSum<<endl;
      it.skipto(interval[0]);
      uint64_t low = interval[0];
      while (low <= interval[2]) {
        mpfr::mpreal ans = Mn(low, runningSum);
        if (ans > max[index]) {
          max[index] =ans;
        }
        // cout<<Mn(low, runningSum)<<endl;
        low = it.next_prime();
        runningSum += 1.0/low;
      }
      // cout<<"["<<interval[0]<<","<<interval[1]<<"] has a max of "<<max[index]<<endl;
      index++;
      // cout<<"["<<interval[0]<<","<<interval[1]<<"] and get intervals up to "<<interval[2]<<endl;
    }
  }

  // for (; prime < last; prime = it.next_prime()) {
  //     primeSum += (1.0/prime);
  //     cout<<Mn(prime, primeSum)<<endl;
  // }

  return 0;
}

mpfr::mpreal A(uint64_t y, mpfr::mpreal p) {
  return p - mpfr::log(mpfr::log(y)) - B;
}

mpfr::mpreal Mn(uint64_t Pn, mpfr::mpreal runningSum) {
  // cout<<"In Mn with Pn = "<<Pn;
  primesieve::iterator i;
  it.skipto(Pn);
  uint64_t PnPlusOne = it.next_prime();
  // cout<<" and Pn+1 = "<<PnPlusOne<<endl;
  mpfr::mpreal x = runningSum - mpfr::log(mpfr::log(Pn)) - B;
  mpfr::mpreal y = runningSum - mpfr::log(mpfr::log(PnPlusOne)) - B;
  return x > y ?  x :  y;
}

vector<uint64_t> getInterval(uint64_t bottom, uint64_t top) {
  primesieve::iterator it;
  uint64_t temp;
  vector<uint64_t> newInterval;
  vector<uint64_t> low;
  vector<uint64_t> high;
  // it.skipto(bottom);
  // temp = it.prev_prime();
  // newInterval.push_back(temp < 2 ? 2 : temp);
  // it.skipto(top);
  // temp = it.prev_prime();
  // newInterval.push_back(temp < 2 ? 2 : temp);
  // temp = it.prev_prime();
  // newInterval.push_back(temp < 2 ? 2 : temp);
  // return newInterval;

  newInterval.push_back(bottom);
  // low.push_back(bottom);
  it.skipto(bottom);
  temp = it.prev_prime();
  while (temp < top) {
    temp = it.next_prime();
    if (temp < top)
      newInterval.push_back(temp);
  }
  newInterval.push_back(top);
  return newInterval;

}

mpfr::mpreal getRunningSum(uint64_t upTo) {
  primesieve::iterator it;
  it.skipto(0);
  uint64_t prime = it.next_prime();
  mpfr::mpreal sum;
  for (; prime <= upTo; prime = it.next_prime()) {
      sum += 1.0/prime;
    // cout<<prime<<endl;
  }
  return sum;
}

