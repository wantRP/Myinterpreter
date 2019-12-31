#include <bits/stdc++.h>
#include "lexer.h"
int main(){
  char s[256];
  //gets(s);
  printf(".2. a:= 1+sdd+(1.34<> 192.168.1.1 - 13..)aaa.ccc... ;end.");
  parse((char*)".2. a:= 1+sdd+(1.34<> 192.168.1.1 - 13..)aaa.ccc... ;end");
  classify();
  
	printf("\n-------\n");
  for(auto i:words) std::cout<<i<<std::endl;
  printf("\n-------\n");
  for(auto i:parsermessage) std::cout<<i<<std::endl;
  for(auto i:words2) std::cout<<i.first<<","<<i.second<<std::endl;
}
