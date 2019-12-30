#include<bits/stdc++.h>
#define pb push_back
const std::set<std::string>delimiter{":=","=","+","-","*","/",";","<>"};
const std::set<char>otherchar{',',' ','=','+','-','*','/','<','>',':','(',')',';'};
std::vector<std::string>originalwords;
std::vector<std::string>words;
bool legalchar(char c){ return isalpha(c)||otherchar.count(c)||isdigit(c); }
bool legalinnumber(char c){ return isdigit(c)||c=='.'; }
bool legalinid(char c){ return isalpha(c)||c=='_'||isdigit(c); }
bool classify(){
	for(auto s:originalwords){
		if(s==" ") continue;
		if(legalinnumber(s[0])){//number
			bool dot=0;
			bool number=0;
			bool cut=0;
			for(int i=0;i<s.length();++i){
				if(s[i]=='.'&&dot){
					s=s.substr(0,i);
					break;
				}
				if(s[i]=='.') dot=1;
			}
			if(s==".") {
				//printf("%s:num expected but . found",s.c_str());
				words.pb("err");
				return 1;
			}
			if(s[0]=='.') s="0"+s;
			if(s[s.length()-1]=='.') s=s+"0";

		}//end anlz num
		words.pb(s);
	}//end for
	return 0;
}
void parse(char* s){
	for(int i=0;i<strlen(s);){
		char c=s[i];
		if(legalinnumber(c)){
			std::string ts="";
			for(;i<strlen(s)&&legalinnumber(s[i]);++i){
				c=s[i];
				ts=ts+c;
			}
			//printf("%s\n",ts.c_str());
			originalwords.pb(ts);
		} else if(legalinid(c)){
			std::string ts="";
			for(;i<strlen(s)&&legalinid(s[i]);++i){
				c=s[i];
				ts=ts+c;
			}
			//printf("%s\n",ts.c_str());
			originalwords.pb(ts);
		} else if(!legalchar(c)){
			printf("ILLEGAL CHARACTER: %c\n",c);
			++i;
		} else{// symbols
			std::string ts="";
			if(s[i+1]){
				ts=ts+s[i]+s[i+1];
				if(delimiter.count(ts)){ //analyze token length=2
					//printf("%s\n",ts.c_str());
					originalwords.pb(ts);
					i=i+2;
					continue;
				}
			}
			char cc=s[i];
			ts="";
			ts=ts+cc;
			//printf("%s\n",ts.c_str());
			originalwords.pb(ts);
			i=i+1;
		}
	}

}
