//double player pic tac toe

#include<bits/stdc++.h>

using namespace std;
char ** mat;
int turn=0;
int powers[9];

int calc(){
	//returns -1 if mat is full
	//returns 0 if nothing
	//returns 1 if player 1 wins( who writes x)
	//returns 2 if player 2 wins( who writes 0)
//	cout<<"debug 0"<<endl;
	for(int i=0;i<3;i++){
		int x=0; int o=0;
		for(int j=0;j<3;j++){
			if(mat[i][j]=='X')
				x++;
			else if(mat[i][j]=='0')
				o++;
		}
		if(x==3) return 1;
		if(o==3) return 2; 
	}
//	cout<<"debug 1"<<endl;
	for(int i=0;i<3;i++){
		int x=0; int o=0;
		for(int j=0;j<3;j++){
			if(mat[j][i]=='X')
				x++;
			else if(mat[i][j]=='0')
				o++;
		}
		if(x==3) return 1;
		if(o==3) return 2; 
	}

//	cout<<"debug 2"<<endl;
	int x=0; int o=0;
	for(int i=0;i<3;i++){
 		if(mat[i][i]=='X')
			x++;
		else if(mat[i][i]=='0')
			o++;
	}
	if(x==3) return 1;
	if(o==3) return 2;

//	cout<<"debug 3"<<endl;
	x=0;o=0;
	for(int i=0;i<3;i++){
 		if(mat[2-i][2-i]=='X')
			x++;
		else if(mat[2-i][2-i]=='0')
			o++;
	}
	if(x==3) return 1;
	if(o==3) return 2;
//	cout<<"debug 4"<<endl;
	int l=0;
	for(int i=0;i<3;i++){
		
		for(int j=0;j<3;j++){
			if(mat[i][j]==' ')
				l++;
		}
		
	}
	if(l==0) return -1;
	return 0;

}

void display(){
	cout<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<mat[2-i][j];
			if(j!=2)
				cout<<" , ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int getState(int p){
	int index=0;
	
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			int l=3*i+j;
			if(mat[i][j]=='X'){
				if(p==1)
					index+=1*powers[l];
				if(p==2)
					index+=2*powers[l];			
			}
			else if(mat[i][j]=='0'){
				if(p==2)
					index+=1*powers[l];
				if(p==1)
					index+=2*powers[l];			
			}				
		}	
	}
	return index;
}

void init(){
	mat = new char*[3];
	for(int i=0;i<3;i++){
		mat[i]=new char[3];
		for(int j=0;j<3;j++){
			mat[i][j]=' ';
		}
	}
	turn=1; //player 1's turn
	powers[0]=1;
	for(int i=1;i<9;i++){
		powers[i]=powers[i-1]*3;
	}
}

void displayRules(){
	cout<<"Player 1 writes X"<<endl;
	cout<<"Player 2 writes 0"<<endl;
	cout<<"Enter coordinates as horizontal<space>vertical e.g. 3 1 is bottom right corner"<<endl<<endl;
}

int nextMove(int x,int y){
	//return -1 invalid
	//return 1 if the player who just player won 
	//return 4 if tie
	//return 0 if nothing
	if(x>3 || y>3 || x<1 || y<1)
		return -1;
	if( mat[y-1][x-1] !=' ' )
		return -1;

	mat[y-1][x-1]=(turn==1)?'X':'0';

	turn=(turn==1)?2:1;
	if(calc()==1){
		//cout<<"Player 1 wins (writes X)"<<endl;
		return 1;		
	}
	if(calc()==-1){
		//cout<<"its a tie"<<endl;
		return 4;	
	}
	return 0;
}


