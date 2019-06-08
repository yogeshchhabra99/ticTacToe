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

int getMove(int state){
	int max=0;
	int maxindex=0;
	Data d=getData(state);
	while(d.wins[maxindex]==-1)
			maxindex++;
	if(maxindex>=9){
		cout<<"debug"<<endl;
		return -1;
	}
	for(int i=maxindex;i<9;i++){
		if(d.wins[i]>max){
			max=d.wins[i];
			maxindex=i;
		}	
	}
	//cout<<maxindex<<" "<<d.wins[maxindex]<<" "<<d.draws[maxindex]<<endl;
	//cout<<maxindex<<" "<<d.wins[7]<<" "<<d.draws[7]<<endl;
	for(int i=0;i<9;i++){
		if(d.draws[i]>max){
			max=d.draws[i];
			maxindex=i;
		}	
	}
	//cout<<maxindex<<" "<<d.wins[maxindex]<<" "<<d.draws[maxindex]<<endl;
	return maxindex;
}

//I can also train while playing!! cool; need to implement it

int main(){
	init();
	int res=calc();
	displayRules();
	display();
	while(res==0){
		cout<<"Your turn"<<endl;
		int x,y;
		cin>>x>>y;
		int out = nextMove(x,y);
		if(out==-1){
			cout<<"Invalid move"<<endl;
			continue;		
		}
		display();
		if(out==4){
			cout<<"Its a tie"<<endl;
			return 0;		
		}
		if(out==1){
			cout<<"You win"<<endl;
			return 0;		
		}
		cout<<"Coms Move"<<endl;
		while(1){
			int move=getMove(getState(2));
			if(move==-1){
				cout<<"Com has no moves"<<endl;
				return -1;		
			}
			out = nextMove(move/3+1,move%3+1);
			if(out==-1){
				cout<<"Invalid move by computer; training myself"<<endl;
				Data d = getData(getState(2));
				d.state=getState(2);
				d.wins[move]=-1;
				d.total++;
				saveData(d);
				continue;		
			}
			break;		
		}
		display();
		cout<<"out"<<out<<endl;
		if(out==4){
			cout<<"Its a tie"<<endl;
			return 0;		
		}
		if(out==1){
			cout<<"Computer win"<<endl;
			return 0;		
		}
	}
}
