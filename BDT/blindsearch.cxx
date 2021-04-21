#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
#include "bininfo.h"

std::pair<int, int> blindpair(long ts= 1618557840){

  std::fstream input;
  input.open("BDT_description.log");
  std::map<int, std::string> dictmap;
  std::string stringbuf;
  while (input.peek() != EOF){
    std::getline(input, stringbuf);
    int inputts = stoi(stringbuf.substr(0,10));
    dictmap[inputts] = stringbuf.substr(12);
  }
  if(strcmp(dictmap[ts].substr(0,5).c_str(),"BLIND")==0){
    int nttrain = std::stoi(dictmap[ts].substr(6,1));
    int nttest = std::stoi(dictmap[ts].substr(8,1));
    return std::pair<int, int> (nttrain, nttest);
  }
  else{ std::cout << "This timestamp is not for BLIND train" << std::endl; return std::pair<int, int>(0,0);}
  input.close();
}
