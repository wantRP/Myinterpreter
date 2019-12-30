#include <bits/stdc++.h>
#include "lexer.h"
int main(){
  char s[256];
  //gets(s);
  parse("a:= 1+sdd+(1.34<> 192.168.1.1)aaa.ccc... ;");
  classify();
  for(auto i:originalwords) std::cout<<"("<<i<<")";
	printf("\n-------\n");
  for(auto i:words) std::cout<<i<<std::endl;
}
