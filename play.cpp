#include<bits/stdc++.h>
#include<string>
#include<stack>
using namespace std;

extern int getState(int i);
extern int display();
extern int nextMove(int x, int y);
extern void init();
extern int turn;
extern int calc();
extern void displayRules();

class Data{
	public:
		int state;
		int total;
		int last;
		int wins[9];
		Data(){
			state=-1;
			total=0;
			last=8;
			for(int i=0;i<9;i++)
				wins[i]=0;	
		}
};

Data getData(int state){
	string i;
	stringstream ss;
	ss << state;
	 i = ss.str();
	string name="data/state-";
	name.append(i);
	name.append(".txt");
	//cout<<name<<endl;
	FILE *fptr= fopen(name.c_str(),"r");
	if(fptr==NULL){
		return Data();	
	}
	Data data;
	fscanf(fptr,"%d %d %d",&(data.state),&(data.total),&(data.last));
	for(int i=0;i<9;i++){
		fscanf(fptr,"%d",&data.wins[i]);	
	}
	fclose(fptr);
	return data;
}

int getMove(int state){
	int max=0;
	int maxindex=0;
	Data d=getData(state);
	for(int i=0;i<9;i++){
		if(d.wins[i]>max){
			max=d.wins[i];
			maxindex=i	
		}	
	}
}

int main(){
	init();
	int res=calc();
	displayRules();
	display();
	while(res==0){
		cout<<"Your turn"<<endl;
		
	}
}
