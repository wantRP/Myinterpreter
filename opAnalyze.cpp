#include<bits/stdc++.h>
#define mp make_pair
typedef enum proty{pundefined='E',plow='<',phigh='>',pequal='='}priority;
std::map<std::pair<char,char>,priority>table;
std::set<char>vt;
std::vector<std::pair<char,std::string>>rules;
std::map<char,std::set<char>>firstvt,lastvt;
std::stack<std::pair<char,char> >sfirstvt,slastvt;
bool isvt(char c){ return (!isupper(c));}
void init(){
	char c;
	std::string s;
	freopen("syn.txt","r",stdin);
	while(std::cin>>c>>s) rules.push_back(make_pair(c,s));
	fclose(stdin);
	

}
void mark(std::pair<char,char>pair,std::stack<std::pair<char,char> >&v,std::map<char,std::set<char> >&m){
	char p=pair.first;
	char a=pair.second;
	//printf("%c %c$\n",p,a);
	if(!m[p].count(a)){
		m[p].insert(a);
		v.push(pair);
	}
}
void getfirstvt(){
	//P->a and P->Qa
	for(auto r:rules)
		if(!isupper(r.second[0])) mark(std::mp(r.first,r.second[0]),sfirstvt,firstvt);
			else if(r.second[1]&&!islower(r.second[1])) mark(std::mp(r.first,r.second[1]),sfirstvt,firstvt);
	while(!sfirstvt.empty()){
		std::pair<char,char>priority;
		priority=sfirstvt.top();//(Q,a)
		sfirstvt.pop();
		for(auto i:rules) if(i.second[0]==priority.first) mark(std::make_pair(i.first,priority.second),sfirstvt,firstvt);
	}
}
void getlastvt(){//OK
	for(auto r:rules){
		auto p=r.first;
		auto a=r.second;
		int l=a.length();
		if(!isupper(a[l-1])) mark(std::mp(p,a[l-1]),slastvt,lastvt);
			else if((l>1) && (!isupper(a[l-2]))) mark(std::mp(p,a[l-2]),slastvt,lastvt);
	}
	while(!slastvt.empty()){
		std::pair<char,char>priority;
		priority=slastvt.top();
		slastvt.pop();
		for(auto i:rules) if(i.second.back()==priority.first) mark(std::mp(i.first,priority.second),slastvt,lastvt);
	}
}
void maketable(){//OK
	for(auto r:rules){
		auto s=r.second;
		for(int i=0;i<s.length()-1;++i){
			if( (!isupper(s[i])) && (!isupper(s[i+1])) ) table[std::make_pair(s[i],s[i+1])]=pequal;
			if(!isupper(s[i])&&s[i+2]&&!isupper(s[i+2])&&isupper(s[i+1])) table[std::make_pair(s[i],s[i+2])]=pequal;
			if(!isupper(s[i])&&isupper(s[i+1])) for(auto j:firstvt[s[i+1]]) table[std::make_pair(s[i],j)]=plow;
			if(isupper(s[i])&&!isupper(s[i+1])) for(auto j:lastvt[s[i]]) table[std::make_pair(j,s[i+1])]=phigh;
		}
	}
}
void getvt(){
	for(auto r:rules)
		for(int j=0;j<r.second.size();++j) if(!isupper(r.second[j])) vt.insert(r.second[j]);
}
void opanalyze(std::string str){
	char s[122];
	std::vector<char>queue;
	std::vector<char>stack;
	strcpy(s, str.c_str());
	for(int i=0;i<strlen(s);++i) queue.push_back(s[i]);
	queue.push_back('#');
	stack.push_back('#');
	char a='#';
	int j;
	do{
		j=stack.size()-1;
		//printf("loop\n");
		for(auto i:stack) printf("%c",i);
		printf("\t");
		for(auto i:queue) printf("%c",i);
		printf("\n");
		a=queue[0];
		if(isvt(stack[j]));else j=j-1;
		while(table[std::make_pair(stack[j],a)]==phigh){
			//printf("replace\n");
			char q;
			do{
				q=stack[j];
				isvt(stack[j-1])?j=j-1:j=j-2;
				if(table[std::make_pair(stack[j],q)]==plow) break;
			}while(1);
			//printf("appear j=%d s[j]=%c q=%c\n",j,stack[j],q);
			std::string sr="";
			for(int k=j+1;k<stack.size();++k) sr=sr+stack[k];
			//std::cout<<"find "<<sr<<std::endl;
			char cl;
			for(auto k:rules) if(k.second==sr){
				//printf("use rule %c->%s\n",k.first,k.second.c_str());
				cl=k.first;
				break;
			}
			int l=sr.size();
			stack.erase(stack.begin()+j+1,stack.begin()+j+1+l);
			stack.push_back(cl);
			for(auto i:stack) printf("%c",i);
		printf("\t");
		for(auto i:queue) printf("%c",i);
		printf("\n");
		}
		if(table[std::mp(stack[j],a)]==plow||table[std::mp(stack[j],a)]==pequal){
			
			stack.push_back(a);
			queue.erase(queue.begin());
		}else{printf("ERRRRR");return;}
	}while(a!='#');
	
}
int main(){
	char s[233];
	std::cin>>s;
	init();
	for(auto i:rules) std::cout<<i.first<<" "<<i.second<<std::endl;
	getvt();
	for(auto i:vt)
		for(auto j:vt) table[std::make_pair(i,j)]=pundefined;
	getfirstvt();
	getlastvt();
	maketable();
	/*
	printf("---firstvt---\n");
	for(auto i:firstvt){
		std::cout<<i.first<<" ";
		for(auto j:i.second) std::cout<<j;
		printf("\n");
	}
	printf("---lastvt----\n");
	for(auto i:lastvt){
		std::cout<<i.first<<" ";
		for(auto j:i.second) std::cout<<j;
		printf("\n");
	}
	*/
	printf("----table----\n ");
	for(auto i:vt) printf("%c",i);
	printf("\n");
	for(auto i:vt){
		printf("%c",i);
		for(auto j:vt) printf("%c",table[std::make_pair(i,j)]);
		printf("\n");
	}
	freopen("CON","r",stdin);
	
	opanalyze(s);
}
