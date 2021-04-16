#include <iostream>
#include <fstream>
#include <map>
#include <cstring>

int main(){
  int ts= 1618557840;
  std::cout << "timestamp :";
  std::string _ts;
  std::cin >> _ts;
  std::fstream input;
  input.open("BDT_description.log");
  std::map<int, std::string> dictmap;
  std::string stringbuf;
  while (input.peek() != EOF){
    std::getline(input, stringbuf);
    int inputts = stoi(stringbuf.substr(0,10));
    dictmap[inputts] = stringbuf.substr(12);
  }
  try{stoi(_ts);
    if (stoi(_ts) !=0) ts= stoi(_ts);
    if (stoi(_ts) == 0) return 0;
    std::cout <<"Description: " <<  dictmap[ts] << std::endl;
  }
  catch(...){
    if( strcmp(_ts.c_str(),"exit")==0) return 0;
    else std::cout << "input 10 digit POSIX timestamp" << std::endl;
  }
  input.close();
  main();

  return 0;
  
}


