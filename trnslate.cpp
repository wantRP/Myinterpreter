
#include<iostream> 
#include<string> 
using namespace std;
const int MAX=100;
char cost[8][8]={
' ','+','*','!','i','(',')','#',
'+','>','<','<','<','<','>','>',
'*','>','>','<','<','<','>','>',
'!','>','>','<','<','<','>','>',
'i','>','>','>',' ',' ','>','>',
'(','<','<','<','<','<','=',' ',
')','>','>','>',' ',' ','>','>',
'#','<','<','<','<','<',' ','='};//the priority realiton graph 
int Digital[MAX]; //store the letter swap to digital 
int Dp=0;//the pointer of the digital 
char Sign[MAX];//strore the sign of the string 
int Sp=0;//the pointer of the sign 
int Temp[MAX]; // 
int Tp;  //  
int Fp=0;//point to the four equation space 
void printprioritytable();
int SearchCost(int i,int j);
int Entry(char ch);
int NewTemp(int t[3]);
int CharToDigital(char ch);
void DispItem(int i);
void DispIndirect(int i);
int Merge(int* ch,int ll);
void ToDigital(int digital[],char str[],int& d_len);
typedef class four_item{
	char op;
	int s1,s2,s3;
public:
	four_item(){}
	four_item(int op,int  s1,int  s2){
		this->op=cost[0][op];
		this->s1=s1;
		this->s2=s2;
		this->s3=Fp+300;//metion +100 ,+200,+300 
	} 
	void DispSample(){
		cout<<"(";
		if(op=='!')
			cout<<"**";
		else
			cout<<op;
		cout<<","; DispIndirect(s1);
		cout<<",";
		DispIndirect(s2);
		cout<<",";
		DispIndirect(s3);
		cout<<")"<<endl;
	}
	void DispFour()
	{
		cout<<"Pruduce:"<<Fp;
		cout<<" (";
		if(op=='!')
			cout<<"**";
		else
			cout<<op;
		cout<<",";
		DispIndirect(s1);
		cout<<",";
		DispIndirect(s2);
		cout<<",";
		DispIndirect(s3);
		cout<<")";
	}
}*Four;
Four four[MAX]; //to store the four equation 
class stack{
	int top;
	int array[MAX];
public:

	stack(){ top=0; }

	int  GetTop(){ return array[top-1]; }
	int Getsize(){ return top; }
	void PushStack(int  c)
	{
		if(top<MAX)
			array[top++]=c;
		else
			cout<<"over flow!"<<endl;
	}
	int PopStack(int temp[],int length){
		if(top>=length){
			for(int i=0;i<length;i++){
				temp[i]=array[top-length+i];
			}
			top=top-length;

			return length;
		} else{
			cout<<"Error!"<<endl;
			exit(0);
		}
	}
	int GetChar(int pos){
		if((pos>=0)&&(pos<MAX))
			return array[pos];
		else
			return 0;
	}
	void DispStack(){
		for(int i=0;i<top;i++){
			DispItem(array[i]);
		}
		if(this->top>5) cout<<'\t';
		else cout<<'\t'<<'\t';
	}
};
stack s;
void printprioritytable(){//only print
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(cost[i][j]=='!')
				cout<<"**"<<'\t';
			else
				cout<<cost[i][j]<<'\t';
		}
		cout<<endl;
	}
}
int SearchCost(int i,int j)//set the realiton according to the cost 
{                                  //0==equal, 1==above, -1==low, 2==NULL
	if(i/100==1)
		i=4;
	if(j/100==1)
		j=4;
	switch(cost[i][j]){
	case '>':return 1;break;
	case '<':return -1;break;
	case '=':return 0;break;
	default:return 2;break;
	}
}
int Entry(char ch)
{
//	for(int i=1;i<Sign[0];i++)//find the no of variable,or add it to tail
//		if(Sign[i]==ch)
//			return i+100;
	Sign[++Sp]=ch;
	return Sp+100;
}
int NewTemp(int t[3])
{
	Fp++;
	four[Fp]=new four_item(t[1],t[0],t[2]);
	four[Fp]->DispFour();
	cout<<endl;
	return Fp+300;
}
int CharToDigital(char ch)//get number in table
{
	int j;
	for(j=0;j<8;j++)
		if(ch==cost[0][j])
			return j;//found
	if(isalnum(ch)){//not exist
		return Entry(ch);
	} else
		return 0;
}
void DispItem(int i)
{
	if(i<0||i>400){
		cout<<"Error!"<<endl;
		return;
	}
	if(i<100){
		if(i==3)
			cout<<"**";
		else
			cout<<cost[0][i];
		return;
	} else if(i<200){
		cout<<Sign[i-100];
		return;
	} else if(i<300){
		cout<<"E"<<i-200;
	} else
		cout<<"T"<<i-300;
}
void DispIndirect(int i)
{
	if(i<0||i>=400){
		cout<<"Error!"<<endl;
		return;
	}
	if(i<100){
		if(i==3)
			cout<<"**";
		else
			cout<<cost[0][i];
	} else if(i<200){
		cout<<Sign[i-100];
	} else if(i<300){
		DispIndirect(Temp[i-200]);
	} else
		cout<<"T"<<i-300;
}
int Merge(int* ch,int ll)
{
	s.PopStack(ch,ll);
	if(ll==1)//the length is 1
	{
		Temp[++Tp]=ch[0];
		cout<<"Merge:";
		DispItem(ch[0]);
		cout<<"==>";
		DispItem(Tp+200);
		cout<<endl;
		return Tp+200;
	}

	else if(ch[0]==5&&ch[2]==6)//When to '()'
	{
		Temp[++Tp]=ch[1];
		cout<<"Merge(";
		DispItem(ch[1]);
		cout<<")==>";
		DispItem(Tp+200);
		cout<<endl;
		return Tp+200;
	} else if(ch[0]>100&&ch[2]>100&&ch[1]<100)//(np£¬op£¬np)
	{
		cout<<"Merge£º";
		DispItem(ch[0]);
		DispItem(ch[1]);
		DispItem(ch[2]);
		cout<<"==>";
		DispItem(Fp+301);
		cout<<'\t';
		return NewTemp(ch);
	} else{
		cout<<"Merge fail!"<<endl;
		exit(0);
	}
}
void ToDigital(int digital[],char str[],int& d_len)//convert char to number in table
{
	int len=strlen(str);
	for(int i=0;i<len;i++){
		digital[d_len]=CharToDigital(str[i]);//if illigal character, throw
		if(digital[d_len]==0){
			cout<<"Wrong occur!"<<i+1<<"can not be recognise!\""<<str[i]<<"\"Please check"<<endl;
			exit(0);
		}
		if(digital[d_len]==2&&digital[d_len-1]==2)//**
			digital[d_len-1]=3;
		else
			d_len++;
	}
}

void tmain()
{
	char string[MAX];                    //for the sentence to be ananlyse
	int* ch=new int[MAX];                        //the mergeing string                     
	int a;                              //store the letter need to be judge
	int strp;                            //point to the letter of the string
	int statop;                           //point to the top of the stack
	int statopvt;                         //point to the top VT
	int fp=0;
	cout<<"*****The priority realiton graph is as following:********"<<endl;
	printprioritytable();
	cout<<"*********************************************************"<<endl;
	cout<<"input the string:";
	cin.getline(string,MAX);
	int l=strlen(string);
	string[l]='#';
	string[l+1]='\0';
	ToDigital(Digital,string,Dp); //convert char to number of vt in table save in Digital
	cout<<"**********************************************************"<<endl;
	cout<<"The stack:"<<'\t'<<"The action:"<<'\t'<<'\t'<<"Produce or not:"<<endl;
	s.PushStack(7);//push '#'
	strp=0;
	statop=s.Getsize()-1;
	statopvt=statop;
	a=Digital[0];
	while(a!=7)                        //The analysing progress is as following:
	{                                    //iftheletter's priority is litter thanthe top  start merge                                  
		a=Digital[strp];                     // get the letter
		if(s.GetChar(statop)<200)
			statopvt=statop;
		else
			statopvt=statop-1;
		//> is 1, < is -1, = is 0,un=2
		while(a<200&&(SearchCost(s.GetChar(statopvt),a)==1))//the topvt is greater than the letter the can not push then merge
		{
			s.DispStack();                            //show the stack before merging
			int highpos=statopvt,lowpos=highpos-1;    //calculate the length of the mergeing string
			if(s.GetChar(lowpos)>200)
				lowpos--;
			while(SearchCost(s.GetChar(lowpos),s.GetChar(highpos))!=-1){
				highpos=lowpos;

				lowpos--;
				if(s.GetChar(lowpos)>200)
					lowpos--;
			}
			int start=s.Getsize();
			lowpos++;
			int length=start-lowpos;//merge
			s.PushStack(Merge(ch,length));

			statopvt=s.Getsize()-1;
			if(s.GetChar(statopvt)>200)
				statopvt--;
		}
		if((a<200)&&(SearchCost(s.GetChar(statopvt),a)==2)){
			cout<<"Error!"<<endl;
			cout<<"The "<<strp+1<<" letter is wrong!"<<endl;
			DispItem(a);
			exit(0);
		} else{
			s.DispStack();
			cout<<"push:";
			DispItem(a);
			cout<<endl;
			s.PushStack(a);
			strp++;
			statop=s.Getsize()-1;
		}
	}
	s.DispStack();
	int t[MAX];
	s.PopStack(t,3);
	if(s.Getsize()==0)
		cout<<"Sucess!"<<endl;
	else
		cout<<"Fail!"<<endl;
	cout<<"******************************************************"<<endl;
	cout<<"*****The final four items are as following:****"<<endl;
	for(int l=1;l<=Fp;l++){
		cout<<l<<":";
		four[l]->DispSample();
	}
	cout<<"***********************************************"<<endl;
}