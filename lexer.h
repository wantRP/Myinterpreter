#include<bits/stdc++.h>
#define pb push_back
const std::set<std::string>delimiter{":=","=","+","-","*","/",";","<>"};
const std::set<std::string>keyword{"begin","end","integer","bool","read","write","for","while","do","if","and","then","or","not","var","true","false","else"};
const std::set<char>otherchar{',',' ','=','+','-','*','/','<','>',':','(',')',';'};
std::vector<std::string>originalwords;
std::vector<std::string>words;
std::vector<std::string>parsermessage;
bool legalchar(char c){ return isalpha(c)||otherchar.count(c)||isdigit(c); }
bool legalinnumber(char c){ return isdigit(c)||c=='.'; }
bool legalinid(char c){ return isalpha(c)||c=='_'||isdigit(c); }
int classify(){
	for(auto s:originalwords){
		if(s==" ") continue;//ignore space
		if(legalinnumber(s[0])){//number,auto cut the second dot
			bool point=0;
			bool number=0;
			bool cut=0;
			for(int i=0;i<s.length();++i){
				if(s[i]=='.'&&point){
					parsermessage.push_back("waring: too many points, converted \'"+s+"'\ to \'"+s.substr(0,i)+"\'.");
					s=s.substr(0,i);
					break;
				}
				if(s[i]=='.') point=1;
			}
			if(s==".") {
				parsermessage.push_back("error: unexcepted point");
				//printf("%s:num expected but . found",s.c_str());
				//words.pb("err");
				continue;
			}
			if(s[0]=='.') s="0"+s;
			if(s[s.length()-1]=='.') s=s+"0";
			
		}//end anlz num
		else if(legalinid(s[0])){
			if(keyword.count(s)) s=s+", keyword";else s=s+",user id";
		}
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
