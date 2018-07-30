#include <iostream>
#include <fstream>
#include <vector>
#include "PsiTools.h"
#include "Primetools.h"
#include "mobius.h"

using namespace std;

int main() {

  ifstream inFile;
  inFile.open("./mobius.txt");
  string str;
  std::vector<long long> v;
  v.push_back(-2);
  mobius_setup();

  while(inFile >> str) {
    if(str == "-1" || str == "1" || str == "0")
      v.push_back(stoi(str));
  }
  cout<<"size = "<<v.size()<<endl;
  for(long long i = 1; i < v.size(); ++i) {
    if(v[i] != mobius(i)) {
      cout<<"Mismatched mobius at "<<i<<" file = "<<v[i]<<" algorith = "<<mobius(i)<<endl;
    }
  }
  return 0;
}
