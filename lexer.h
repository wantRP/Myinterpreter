#include<bits/stdc++.h>
const std::set<std::string>delimiter{":=","=","+","-","*","/",";","<>"};
const std::set<char>otherchar{',',' ','=','+','-','*','/','<','>'};
bool legalchar(char c){ return isalpha(c)||otherchar.count(c)||isdigit(c); }
bool legalinnumber(char c){ return isdigit(c)||c=='.'; }
bool legalinid(char c){ return isalpha(c)||c=='_'||isdigit(c); }
void parse(char* s){
	for(int i=0;i<strlen(s);){
		char c=s[i];
		if(legalinnumber(c)){
			std::string ts="";
			for(;i<strlen(s)&&legalinnumber(s[i]);++i){
				c=s[i];
				ts=ts+c;
			}
			printf("%s\n",ts.c_str());
		} else if(legalinid(c)){
			std::string ts="";
			for(;i<strlen(s)&&legalinid(s[i]);++i){
				c=s[i];
				ts=ts+c;
			}
			printf("%s\n",ts.c_str());
		} else if(!legalchar(c)){
			printf("ILLEGAL CHARACTER: %c\n",c);
			++i;
		} else{

		}
	}

}