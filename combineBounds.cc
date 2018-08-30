#include <iostream>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include "mpreal.h"

struct maxValue {
  mpfr::mpreal mValue;
  long long prime;
};

int main(int argc, char* argv[]) {
  DIR *dir;
  struct dirent *ent;

  std::vector<maxValue> maxValues;
  maxValues.resize(6);
  int pos;
  mpfr::mpreal tempM = 0.0;
  long long tempPrime = 0;
  std::string dummy;

  std::ifstream myFile;
  std::string str;
  std::string fileName;
  std::string path;
  std::string filePath;

  mpfr::mpreal::set_default_prec(192);
  std::cout << std::setprecision(58) << std::scientific;

  if(argc >= 2) {
    filePath = argv[1];
  } else{
    std::cout<<"Enter the file path: ";
    std::cin>>filePath;
  }
  if ((dir = opendir (filePath.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      fileName = ent->d_name;
      path = filePath + '/' + fileName;
      myFile.open(static_cast<std::string>(path));
      while(getline(myFile, str)) {
        std::stringstream myStream(str);
        if(str[0] == 'M') {
          myStream>>dummy>>dummy>>tempM>>dummy>>dummy>>dummy>>tempPrime;
          pos = str[1] - 48;
          if(tempM > maxValues[pos].mValue) {
            maxValues[pos].mValue = tempM;
            maxValues[pos].prime = tempPrime;
          }

        }
        if(myFile.eof())
          break;
      }
      myFile.close();
    }
    closedir (dir);

    for(int i = 0; i < maxValues.size(); ++i) {
      std::cout<<"M"<<i<<" = "<<maxValues[i].mValue<<" with P = "<<maxValues[i].prime<<std::endl;
    }
  } else {
  /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }
}
