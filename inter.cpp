#include <bits/stdc++.h>
#include "lexer.h"

int tmain(){
  char s[512];
  //gets(s);
  freopen("pas.pas","r",stdin);
  while(gets_s(s)){
  words.clear();
  parsermessage.clear();
  words2.clear();
    parse(s);
    classify();
    
    
  }
  printf("\n-------\n");
  for(auto i:words) std::cout<<i<<std::endl;
  printf("\n-------\n");
  for(auto i:parsermessage) std::cout<<i<<std::endl;
  for(auto i:words2) std::cout<<i.first<<","<<i.second<<std::endl;
  return 0;
}
