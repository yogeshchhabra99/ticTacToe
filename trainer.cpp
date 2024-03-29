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
extern void del();

bool debug=false;

class Data{
	public:
		int state;
		int total;
		int last;
		int wins[9];
		int draws[9];
		Data(){
			state=-1;
			total=0;
			last=8;
			for(int i=0;i<9;i++){
				wins[i]=0;
				draws[i]=0;
			}
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
	for(int i=0;i<9;i++){
		fscanf(fptr,"%d",&data.draws[i]);	
	}
	fclose(fptr);
	return data;
}

int saveData(Data data){
	string i;
	stringstream ss;
	ss << data.state;
	i = ss.str();
	string name="data/state-";
	name.append(i);
	name.append(".txt");
	//cout<<name<<endl;
	FILE *fptr= fopen(name.c_str(),"w");
	if(fptr==NULL){
		return -1;	
	}
	fprintf(fptr,"%d %d %d",(data.state),(data.total),(data.last));
	for(int i=0;i<9;i++){
		fprintf(fptr," %d",data.wins[i]);	
	}
	for(int i=0;i<9;i++){
		fprintf(fptr," %d",data.draws[i]);	
	}
	
	fprintf(fptr,"\n");
	fclose(fptr);
	return 0;
}
int test(){
	init();
	nextMove(2,2);
	display();
}

int train(){
	//getData(1);
	init();
	stack<Data> stacks[2];
	bool tie=false;
	while(calc()!=1 && calc()!=2){
		if(debug) cout<<"debug2"<<turn<<endl;
		int state = getState(turn);
		Data data = getData(state);
		if(data.state==-1){
			data.state=state;		
		}
		data.last=(data.last+1)%9;
		int res = nextMove(data.last/3 + 1 , data.last%3 + 1 );
		
		while(res==-1){
				
			data.wins[data.last]=-1;	//optimise this
			data.draws[data.last]=-1;
			data.last=(data.last+1)%9;
			res = nextMove(data.last/3 + 1 , data.last%3 + 1 );
		}
		data.total++;
		//turn changes auto
		if(debug) cout<<"turn:"<<turn<<endl;
		stacks[turn-1].push(data);
		if(debug) cout<<"debug3"<<endl;
		if(res==1)
			break;
		if(res==4){
			tie=true;
			break;		
		}	
	}
	
	
	while(!stacks[turn-1].empty()){
		Data d=stacks[turn-1].top();
		if(!tie) d.wins[d.last]++;
		else d.draws[d.last]++;
		int res = saveData(d);
		if(res==-1){
			cout<<"error"<<endl;		
		}
		stacks[turn-1].pop();
	}
	
	int t=(turn==1)?2:1;
	while(!stacks[t-1].empty()){
		Data d=stacks[t-1].top();
	//	d.wins[d.last]++;
		if(tie)
			d.draws[d.last]++;
		int res = saveData(d);
		if(res==-1){
			cout<<"error"<<endl;		
		}
		stacks[t-1].pop();
	}
	if(tie){
		//tie
		return -1;	
	}
	del();
	return 0;
}

int main(){
	for(int i=0;i<100000;i++){
		if(debug) cout<<"debug1"<<endl;
		cout<<"Iteration:"<<i;
		if(train()==0)
			cout<<"succesful"<<endl;
		else
			cout<<"unsuccesful"<<endl;
	}	
}





