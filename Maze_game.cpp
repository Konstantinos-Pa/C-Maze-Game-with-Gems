#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <new>
#include <conio.h>
#include <time.h>

using namespace std;

int points=0;
int rows=0;
int coll=0;
int size=1;
int gems=10;
int c=0;
int esc=0;
int flag=0;
int ate=0;
int win=0;
int z=1;

class Maze{
	private:
		char *Map;
		int g1;
		int g2;
		int p;
	public:
		Maze();
		~Maze();
		void menu();
		void setMap(char *);
		char *getMap();
		void checkEaten();
		void checkWin();
		void addPlayer();
		void sortFile(string);
		int checkEsc();
		void addGhosts();
		void addGem();
		void moveGhosts();
		void movePlayer();
		void scroll();
		void display();
		void addScore(string);
		void showScoreboard(string);
		void initialRun();
		void run();
};

Maze::Maze(){
	this->Map=new char [size];
}

Maze::~Maze(){
	delete [] this->Map;
}

void Maze::setMap(char *Map){
	delete [] this->Map;
	this->Map=new char [size];
	for (int i=0;i<size;i++){
		this->Map[i]=Map[i];
	}
}

char *Maze::getMap(){
	return this->Map;
}

void Maze::menu(){
	cout << flush;
	system("CLS");
	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << '\t' << '\t'  << '\t'  << '\t' << "Wellcome to a bad pacman copy" << endl;
	cout << '\t' << '\t'  << '\t'  << '\t' <<  '\t' << "You are the (&)" << endl;
	cout << '\t' << '\t'  << '\t' <<  ' ' <<  ' ' <<  ' ' <<  ' ' <<  ' ' <<  ' ' << "Take all the gems (^) and after that" << endl;
	cout << '\t' << '\t'  << '\t'  << '\t' <<  ' ' <<  ' ' <<  ' ' <<  ' ' << "the scroll (%) to win" << endl;
	cout << '\t' << '\t'  << '\t' <<  ' ' <<  ' ' <<  ' ' <<  ' ' <<  ' ' << "But carefull of the Monsters (# and @)" << endl;
	cout << endl << endl << endl << endl << endl << endl << endl;
	system("PAUSE");
}

void Maze::addPlayer(){
	int RandIndex = rand() % size;
	while(this->Map[RandIndex]!=' '){
		RandIndex = rand() % size;
	}
	this->p=RandIndex;
	this->Map[p]='&';
}

void Maze::addGhosts(){
	int amount=2;
	int f=1;
	while (amount>0){
		int RandIndex = rand() % size;
		while (RandIndex<coll+1 || RandIndex>(size-coll-1) || this->Map[RandIndex]=='*' || this->Map[RandIndex]=='\n' || this->Map[RandIndex]=='@' || this->Map[RandIndex]=='&' || this->Map[RandIndex+1]=='&' || this->Map[RandIndex-1]=='&' || this->Map[RandIndex+coll]=='&' || this->Map[RandIndex-coll]=='&'){
			RandIndex = rand() % size;
		}
		if (f==1){
			this->g1=RandIndex;
			this->Map[g1]='@';
			f=0;
		}else{
			this->g2=RandIndex;
			this->Map[g2]='#';
		}
		amount-=1;
	}
}

void Maze::addGem(){
	int amount=10;
	while(amount>0){
		int RandIndex = rand() % size;
		while (RandIndex<coll+1 || RandIndex>(size-coll-1) || this->Map[RandIndex]=='*' || this->Map[RandIndex]=='#' || this->Map[RandIndex]=='@' || this->Map[RandIndex]=='\n' || this->Map[RandIndex]=='^' || this->Map[RandIndex]=='%' || this->Map[RandIndex]=='&' || this->Map[RandIndex]=='#' || this->Map[RandIndex+1]=='&' || this->Map[RandIndex-1]=='&' || this->Map[RandIndex+coll]=='&' || this->Map[RandIndex-coll]=='&'){
			RandIndex = rand() % size;
		}
		this->Map[RandIndex]='^';
		amount-=1;
	}
}

void Maze::moveGhosts(){
	int RandIndex1 = rand() % 100;
	if (RandIndex1<=25){
		if(Map[this->g1+1]!='*' && Map[this->g1+1]!='&' && Map[this->g1+1]!='#' && Map[this->g1+1]!='^' && Map[this->g1+1]!='%'){
			this->Map[this->g1]=' ';
			this->Map[this->g1+1]='@';
			this->g1+=1;
		}
		else if(Map[this->g1+1]=='^' || Map[this->g1+1]=='%'){
			this->Map[this->g1]=this->Map[this->g1+1];
			this->Map[this->g1+1]='@';
			this->g1+=1;
		}
		else if(Map[this->g1+1]=='&'){
			this->Map[this->g1+1]='@';
			this->Map[this->g1]=' ';
			ate=1;
		}
	}
	else if(RandIndex1>25 and RandIndex1<=50){
		if(Map[this->g1-1]!='*' && Map[this->g1-1]!='&' && Map[this->g1-1]!='#' && Map[this->g1-1]!='^' && Map[this->g1-1]!='%'){
			this->Map[this->g1]=' ';
			this->Map[this->g1-1]='@';
			this->g1-=1;
		}
		else if(Map[this->g1-1]=='^' || Map[this->g1-1]=='%'){
			this->Map[this->g1]=this->Map[this->g1-1];
			this->Map[this->g1-1]='@';
			this->g1-=1;
		}
		else if(Map[this->g1-1]=='&'){
			this->Map[this->g1-1]='@';
			this->Map[this->g1]=' ';
			ate=1;
		}
	}
	else if(RandIndex1>50 and RandIndex1<=75){
		if(Map[this->g1+coll]!='*' && Map[this->g1+coll]!='&' && Map[this->g1+coll]!='#' && Map[this->g1+coll]!='^' && Map[this->g1+coll]!='%'){
			this->Map[this->g1]=' ';
			this->Map[this->g1+coll]='@';
			this->g1=this->g1+coll;
		}
		else if(Map[this->g1+coll]=='^' || Map[this->g1+coll]=='%'){
			this->Map[this->g1]=this->Map[this->g1+coll];
			this->Map[this->g1+coll]='@';
			this->g1=this->g1+coll;
		}
		else if(Map[this->g1+coll]=='&'){
			this->Map[this->g1+coll]='@';
			this->Map[this->g1]=' ';
			ate=1;
		}
	}
	else if(RandIndex1>75){
		if(Map[this->g1-coll]!='*' && Map[this->g1-coll]!='&' && Map[this->g1-coll]!='#' && Map[this->g1-coll]!='^' && Map[this->g1-coll]!='%'){
			this->Map[this->g1]=' ';
			this->Map[this->g1-coll]='@';
			this->g1=this->g1-coll;
		}
		else if(Map[this->g1-coll]=='^' || Map[this->g1-coll]=='%'){
			this->Map[this->g1]=this->Map[this->g1-coll];
			this->Map[this->g1-coll]='@';
			this->g1=this->g1-coll;
		}
		else if(Map[this->g1-coll]=='&'){
			this->Map[this->g1-coll]='@';
			this->Map[this->g1]=' ';
			ate=1;
		}
	}
	int RandIndex = rand() % 100;
	if (RandIndex<=25){
		if(Map[this->g2+1]!='*' && Map[this->g2+1]!='&' && Map[this->g2+1]!='@' && Map[this->g2+1]!='^' && Map[this->g2+1]!='%'){
			this->Map[this->g2]=' ';
			this->Map[this->g2+1]='#';
			this->g2+=1;
		}
		else if(Map[this->g2+1]=='^' || Map[this->g2+1]=='%'){
			this->Map[this->g2]=this->Map[this->g2+1];
			this->Map[this->g2+1]='#';
			this->g2+=1;
		}
		else if(Map[this->g2+1]=='&'){
			this->Map[this->g2+1]='#';
			this->Map[this->g2]=' ';
			ate=1;
		}
	}
	else if(RandIndex>25 and RandIndex<=50){
		if(Map[this->g2-1]!='*' && Map[this->g2-1]!='&' && Map[this->g2-1]!='@' && Map[this->g2-1]!='^' && Map[this->g2-1]!='%'){
			this->Map[this->g2]=' ';
			this->Map[this->g2-1]='#';
			this->g2-=1;
		}
		else if(Map[this->g2-1]=='^' || Map[this->g2-1]=='%'){
			this->Map[this->g2]=this->Map[this->g2-1];
			this->Map[this->g2-1]='#';
			this->g2-=1;
		}
		else if(Map[this->g2-1]=='&'){
			this->Map[this->g2-1]='#';
			this->Map[this->g2]=' ';
			ate=1;
		}
	}
	else if(RandIndex>50 and RandIndex<=75){
		if(Map[this->g2+coll]!='*' && Map[this->g2+coll]!='&' && Map[this->g2+coll]!='@' && Map[this->g2+coll]!='^' && Map[this->g2+coll]!='%'){
			this->Map[this->g2]=' ';
			this->Map[this->g2+coll]='#';
			this->g2=this->g2+coll;
		}
		else if(Map[this->g2+coll] =='^' || Map[this->g2+coll] =='%'){
			this->Map[this->g2]=this->Map[this->g2+coll];
			this->Map[this->g2+coll]='#';
			this->g2=this->g2+coll;
		}
		else if(Map[this->g2+coll]=='&'){
			this->Map[this->g2+coll]='#';
			this->Map[this->g2]=' ';
			ate=1;
		}
	}
	else if(RandIndex>75){
		if(Map[this->g2-coll]!='*' && Map[this->g2-coll]!='&' && Map[this->g2-coll]!='@' && Map[this->g2-coll]!='^' && Map[this->g2-coll]!='%'){
			this->Map[this->g2]=' ';
			this->Map[this->g2-coll]='#';
			this->g2=this->g2-coll;
		}
		else if(Map[this->g2-coll]=='^' || Map[this->g2-coll]=='%'){
			this->Map[this->g2]=this->Map[this->g2-coll];
			this->Map[this->g2-coll]='#';
			this->g2=this->g2-coll;
		}
		else if(Map[this->g2-coll]=='&'){
			this->Map[this->g2-coll]='#';
			this->Map[this->g2]=' ';
			ate=1;
		}
	}
}

void Maze::movePlayer(){
	int ch;
	ch = getch ();
	if(ch=='\e'){
		esc=1;
	}
	else if (ch == 224){
		ch = getch();
		switch(ch){
			case 72:
				if (Map[p-coll]==' '){
					this->Map[p]=' ';
					this->Map[p-coll]='&';
					this->p=p-coll;
				}
				else if(Map[p-coll]=='^'){
					this->Map[p]=' ';
					this->Map[p-coll]='&';
					this->p=p-coll;
					gems-=1;
					points+=10;
				}
				else if(Map[p-coll]=='%'){
					this->Map[p]=' ';
					this->Map[p-coll]='&';
					win=1;
					points+=100;
				}
				else if(Map[p-coll]=='#' || Map[p-coll]=='@'){
					this->Map[p]=' ';
					ate=1;
				}
				break;
			case 80:
				if (Map[p+coll]==' '){
					this->Map[p]=' ';
					this->Map[p+coll]='&';
					this->p=p+coll;
				}
				else if(Map[p+coll]=='^'){
					this->Map[p]=' ';
					this->Map[p+coll]='&';
					this->p=p+coll;
					gems-=1;
					points+=10;
				}
				else if(Map[p+coll]=='%'){
					this->Map[p]=' ';
					this->Map[p+coll]='&';
					win=1;
					points+=100;
				}
				else if(Map[p+coll]=='#' || Map[p+coll]=='@'){
					this->Map[p]=' ';
					ate=1;
				}
				break;
			case 75:
				if (Map[p-1]==' '){
					this->Map[p]=' ';
					this->Map[p-1]='&';
					this->p=p-1;
				}
				else if(Map[p-1]=='^'){
					this->Map[p]=' ';
					this->Map[p-1]='&';
					this->p=p-1;
					gems-=1;
					points+=10;
				}
				else if(Map[p-1]=='%'){
					this->Map[p]=' ';
					this->Map[p-1]='&';
					win=1;
					points+=100;
				}
				else if(Map[p-1]=='#' || Map[p-1]=='@'){
					this->Map[p]=' ';
					ate=1;
				}
				break;
			case 77:
				if (Map[p+1]==' '){
					this->Map[p]=' ';
					this->Map[p+1]='&';
					this->p=p+1;
				}
				else if(Map[p+1]=='^'){
					this->Map[p]=' ';
					this->Map[p+1]='&';
					this->p=p+1;
					gems-=1;
					points+=10;
				}
				else if(Map[p+1]=='%'){
					this->Map[p]=' ';
					this->Map[p+1]='&';
					win=1;
					points+=100;
				}
				else if(Map[p+1]=='#' || Map[p+1]=='@'){
					this->Map[p]=' ';
					ate=1;
				}
				break;
		}
	}
}

void Maze::scroll(){
	if(gems==0 && flag == 0){
		int RandIndex = rand() % size;
		while (RandIndex<coll+1 || RandIndex>(size-coll-1) || this->Map[RandIndex]=='*' || this->Map[RandIndex]=='\n' || this->Map[RandIndex]=='^' || this->Map[RandIndex]=='%' || this->Map[RandIndex]=='&' || this->Map[RandIndex]=='#' || this->Map[RandIndex+1]=='&' || this->Map[RandIndex-1]=='&' || this->Map[RandIndex+coll]=='&' || this->Map[RandIndex-coll]=='&'){
			RandIndex = rand() % size;
		}
		this->Map[RandIndex]='%';
		flag=1;
	}
}

void Maze::checkWin(){
	if(win==1){
		cout << flush;
		system("CLS");
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "WOW you actually did it too bad you won't be joining us\n";
		z=0;
		system("PAUSE");
		cout << flush;
		system("CLS");
	}
}

void Maze::display(){
	cout << flush;
	system("CLS");
	for(int i=0;i<size;i++){
		cout << this->Map[i];
	}
	cout << '\n';
}


void Maze::checkEaten(){
	if(ate==1){
		cout << flush;
		system("CLS");
		cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl ;
		cout << "Welcome to the club you lost and have to do it again next semester\n";
		z=0;
		system("PAUSE");
		cout << flush;
		system("CLS");
	}
}

int Maze::checkEsc(){
	if(esc==1){
		printf("Hope we won't see you next semester\n");
		system("PAUSE");
		return 0;
	}
	else{
		return 1;
	}
}

void Maze::addScore(string scoreName){
	string username;
	cout << "Enter your Name (10 characters max):";
	cin >> username;
	while (username.length()>10 && username.length()<1){
		cout <<"invalid Name \n";
		cout << "Enter name :";
		cin >> username;
	}
	ofstream sb (scoreName.c_str(),ios_base::app);
	sb << username << points << endl ;
	sb.close();
}

void Maze::showScoreboard(string scoreName){
	char c;
	string file[5],line;
	int j=0,q;
	cout << flush;
	system("CLS");
	ifstream sb (scoreName.c_str());
	if (sb.is_open()){
		cout << "High score Board" << endl << endl;
		while(!(sb.eof() || j==5)){
			q=0;
			j++;
			while(c != '\n' || p==1){
				p=0;
				sb.get(c);
				if(c-48>=0 && c-48<=9){
					if(q==0){
						cout << '\t' << '\t' ;
						q=1;
					}
					cout << c;
				}
				else{
					cout << c;
				}
			}
			p=1;
		}
		system("PAUSE");
		sb.close();
	}
}

void Maze::sortFile(string scoreName){
	string file[6];
	int file2[6]={0,0,0,0,0,0};
	string line,temp;
	int i=0,j,k,p,temp1;
		ifstream sb(scoreName.c_str());
	while (getline(sb,line) && i<6) {
		k=0;
		p=0;
	    file[i]=line+'\n';
	    while(!(file[i].at(k)-48>=0 &&file[i].at(k)-48<=9)){
	    	k++;
		}
		while(file[i].at(k+p)-48>=0 &&file[i].at(k+p)-48<=9){
	    	p++;
		}
		for(j=k;j<(k+p);j++){
			file2[i]+=(int)file[i].at(j)-48;
			if(j==p+k-1){
				break;
			}
			file2[i]*=10;
		}
	    i++;
	}
	sb.close();
	ofstream sb1(scoreName.c_str());
    for (i = 0; i < 5; i++){
	    for (j = 0; j < 5-i; j++){
	        if (file2[j] < file2[j+1] ){
	        	temp1=file2[j+1];
	        	file2[j+1]=file2[j];
	        	file2[j]=temp1;
	        	temp=file[j+1];
	        	file[j+1]=file[j];
	        	file[j]=temp;
			}
		}  
	}
	for(i=0;i<5;i++){
		sb1 << file[i];
	}
	sb1.close();
}

void Maze::initialRun(){
	this->addPlayer();
	this->addGhosts();
	this->addGem();
}
	
void Maze::run(){
	this->display();
	this->movePlayer();
	this->moveGhosts();
	this->scroll();
	this->checkEaten();
	this->checkWin();
}

int main(int argc, char *argv[]){
	string line;
	string fileName,scoreName;;
	srand(time(0));
	char c;
	char *fileMap;
	fileName = argv[1];
	fileName += ".txt";
	scoreName = argv[2];
	scoreName += ".txt";
	ifstream maze (fileName.c_str());
	if (maze.is_open()) {
		maze.get(c);
		while (!(maze.eof())) {
	    	if (c != '*' && c != ' ' && c != '\n'){
				cout << "Invalid character :" << c <<endl;
	    		cout << "maze must only has stars and spaces \n";
	    		cout << scoreName.c_str();
	    		system("PAUSE");
	    		exit(1);
			}
			maze.get(c);
	    }
	    maze.clear();
	    maze.seekg(0);
		maze.get(c);
	    while (c !='\n') {
	    	coll+=1;
			maze.get(c);
	    }
	    coll+=1;
		while (getline(maze,line)) {
	        rows+=1;
	    }
	    rows+=1;
	    
	    size=rows*coll-1;
	    maze.clear();
	    maze.seekg(0);
	    fileMap=new char[size];
	    for (int i=0;i<size;i++) {
			maze.get(c);
			fileMap[i]=c;
	    }
		maze.close();
		ifstream scorebo (scoreName.c_str());
		if (scorebo.is_open()) {
			Maze maze;
			while(maze.checkEsc()){
				maze.menu();
				maze.setMap(fileMap);
				maze.initialRun();
				z=1;
				ate=0;
				win=0;
				flag=0;
				gems=10;
				points=0;
				while(z && maze.checkEsc()){
					maze.run();
				}
		  		maze.addScore(scoreName);
		  		maze.sortFile(scoreName);
				maze.showScoreboard(scoreName);
			}
	  		scorebo.close();
		}
		else{
			Maze maze;
			maze.setMap(fileMap);
			printf("Error no score board found");
			while(maze.checkEsc()){
				maze.menu();
				maze.setMap(fileMap);
				maze.initialRun();
				z=1;
				ate=0;
				win=0;
				flag=0;
				gems=10;
				points=0;
				while(z && maze.checkEsc()){
					maze.run();
				}
			}
		}
		delete [] fileMap;
	}
	return 0;
}
