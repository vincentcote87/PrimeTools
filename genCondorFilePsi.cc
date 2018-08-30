#include <iostream>
#include <fstream>
#include <primesieve.hpp>
#include <sstream>
#include "mpreal.h"

using namespace std;

int main() {
   string exeName;
   string folderName;
   ofstream condorFile;
   ifstream psiTable;
   uint64_t start = 0;
   uint64_t stop = 10;
   uint64_t range = 25000000;
   uint64_t temp = 0;

   std::vector<mpfr::mpreal> psiList;
   mpfr::mpreal psi;
   std::string str;
  //  mpfr::mpreal::set_default_prec(256);
  //  psiTable.open("psi_1e13_5e13");
   //
  //  while(getline(psiTable, str)) {
  //    std::stringstream myStream(str);
  //    myStream >> psi;
  //    psiList.push_back(psi);
  //  }

   cout<<"Enter the name of the executable program: ";
   cin>>exeName;
   cout<<"Enter the starting value: ";
   cin>>start;
   cout<<"Enter the end value: ";
   cin>>stop;
   cout<<"Enter range value: ";
   cin>>range;
   cout<<"Enter the output folder name: ";
   cin>>folderName;

   folderName = "Output = /moose/cotev4/" + folderName + "/o.";

   cout<<"Your job will run "<<exeName<<" from "<<start<<" to "<<stop<<" with intervals of "<<range<<endl;

   condorFile.open("run.condor");
   condorFile << "Executable = " <<exeName<<endl<<endl;
   for(uint64_t i = start; i < stop; i += range) {
      temp = i;
      condorFile<<"Arguments = "<<i<<endl;
      condorFile<<"Log = ct.log"<<endl;
      condorFile<<"request_memory=7000"<<endl;
      condorFile<<"+xcount = 1"<<endl;
      condorFile<<folderName;
      while(temp < stop) {
	       if(temp == 0)
	        temp = 1;
	        condorFile<<0;
	        temp *= 10;
      }
      condorFile<<i<<endl;
      condorFile<<"Queue"<<endl<<endl;
   }
}
