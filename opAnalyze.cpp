#include<bits/stdc++.h>
#define mp make_pair
typedef enum{
	pundefined=0,
	plow,
	phigh,
	pequal
} pr;
/*typedef struct{
	enum {
		vt=0,vi
	} type=vt;
	std::string content;
	int num=0;
}symbols;
std::vector<symbols>rightpart;
std::pair<int,std::string>rules;
*/
std::map<std::pair<char,char>,pr>sheet;
//std::set<int> firstvt;
std::vector<std::pair<char,std::string>>rules;
std::map<char,std::set<char>>firstvt,lastvt;
std::stack<std::pair<char,char> >firstvts,lastvts;
void init(){
	char c;
	std::string s;
	freopen("syn.txt","r",stdin);
	while(std::cin>>c>>s) rules.push_back(make_pair(c,s));
	fclose(stdin);
}
void mark(std::pair<char,char>pair,std::stack<std::pair<char,char> >&v){
	char p=pair.first;
	char a=pair.second;
	printf("%c %c$\n",p,a);
	if(!firstvt[p].count(a)){
		firstvt[p].insert(a);
		v.push(pair);
	}
}
void getfirstvt(){
	//P->a and P->Qa
	for(auto r:rules){ 
		if(!isupper(r.second[0])) mark(std::mp(r.first,r.second[0]),firstvts);
		else if(r.second[1]&&!islower(r.second[1])) mark(std::mp(r.first,r.second[1]),firstvts);
	};
	while(!firstvts.empty()){
		std::pair<char,char>pr;
		pr=firstvts.top();//(Q,a)
		printf("%c %c\n",pr.first,pr.second);
		firstvts.pop();
		for(auto i:rules){
			if(i.second[0]==pr.first) mark(std::make_pair(i.first,pr.second),firstvts);
		}
	}
}
int main(){
	init();
	for(auto i:rules) std::cout<<i.first<<" "<<i.second<<std::endl;
	printf("--stack--\n");
	getfirstvt();
	printf("--------\n");
	for(auto i:firstvt){
		std::cout<<i.first<<" ";
		for(auto j:i.second) std::cout<<j;
		printf("\n");
	}
}