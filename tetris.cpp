#include "Block.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <random>
#include <Windows.h>
#include <string>

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define cRED "\x1b[31m"
#define cGREEN "\x1b[32m"
#define cYELLOW "\x1b[33m"
#define cBLUE "\x1b[34m"
#define cMAGENTA "\x1b[35m"
#define cCYAN "\x1b[36m"
#define cWHITE "\x1b[37m"
#define cRESET "\x1b[0m"

using namespace std;

void tiledisplay(int blockcolor[]){ 
	for(int i=0;i<20;i++){
		for(int j=0;j<10;j++){
			gotoxy(j+2, i+2);
			if (blockcolor[i*10+j] == RED) {cout<< cRED << "■" << cRESET<<endl;}
			else if (blockcolor[i*10+j] == GREEN) {cout<< cGREEN << "■" << cRESET<<endl;}
			else if (blockcolor[i*10+j] == YELLOW) {cout<< cYELLOW << "■"<< cRESET<<endl;}
			else if (blockcolor[i*10+j] == BLUE) {cout<< cBLUE << "■" << cRESET<<endl;}
			else if (blockcolor[i*10+j] == MAGENTA) {cout<< cMAGENTA << "■" << cRESET<<endl;}
			else if (blockcolor[i*10+j] == CYAN) {cout<< cCYAN << "■" << cRESET<<endl;}
			else if	(blockcolor[i*10+j] == WHITE) {cout<< cWHITE << "■" << cRESET<<endl;}
		}
	}
}//내려온 Block들을 각각 저장

void menudisplay(int blockcolor[]){
	gotoxy(0,0);
	cout<<"▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦▦"<<endl;
	for(int i=0;i<5;i++){
		gotoxy(0, i+2);
		cout<<"▦";
		gotoxy(12, i+2);
		cout<<"▦";
		gotoxy(20, i+2);
		cout<<"▦";
	}
	cout<<endl;
	cout<<"▦          ▦▦▦▦▦▦▦▦▦"<<endl;
	cout<<"▦          ▦Score  ▦"<<endl;
	cout<<"▦          ▦       ▦"<<endl;
	cout<<"▦          ▦▦▦▦▦▦▦▦▦"<<endl;
	for(int i=0;i<11;i++)
		cout<<"▦          ▦"<<endl;
	cout<<"▦▦▦▦▦▦▦▦▦▦▦▦"<<endl;
	tiledisplay(blockcolor);
}//초기 메뉴 디스플레이

void deleteline(int i, int blockcolor[]){
	for(int j=i;j>0;j--){
		for(int k=0;k<10;k++){
			blockcolor[j*10+k]=blockcolor[(j-1)*10+k];
		}
	}
	for(int j=0;j<10;j++){
		blockcolor[j]=0;
	}
}//한 줄이 다 색깔이 있다면 지우고 위에 걸 내리기


int hasline(int blockcolor[]){
	int cnt=0; //cnt = 줄 수
	for(int i=0;i<20;i++){ //한 줄이 다 색깔이 있다면 줄 지우기
		if((blockcolor[i*10]*blockcolor[i*10+1]*blockcolor[i*10+2]*blockcolor[i*10+3]*
					blockcolor[i*10+4]*blockcolor[i*10+5]*blockcolor[i*10+6]*blockcolor[i*10+7]*
					blockcolor[i*10+8]*blockcolor[i*10+9])!=0){
			cnt++;
			deleteline(i, blockcolor);
			i--;
		}
	}
	if(cnt==0)
		return 0; //0줄
	else if(cnt==1) //1줄
		return 100;
	else if(cnt==2) //2줄
		return 300;
	else if(cnt==3) //3줄
		return 500;
	else //4줄
		return 1000;	
}//줄 갖고 있으면 점수 추가하는 시스템

void scoredisplay(int score){
	gotoxy(13, 9);
	printf("%07d", score);
} //현재 점수를 디스플레이함
void randomarray(int blocklist[], int a){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0,6);
	int ans=-1;
	while(ans==-1){
		ans=dis(gen);
		for(int i=0;i<a;i++){
			if(blocklist[i]==ans){
				ans=-1;
				break;
			}
		}
	}
	blocklist[a]=ans;
} //다음에 나올 블록 중복 없이 생성, ans를 통해 중복 걸러냄

bool blockdown(Tetrimino &my, float velo, int blockcolor[], bool shadow, int score){
	bool isfirst=TRUE;
	for(int i=0;i<200;i++){
		if(blockcolor[i]!=0){
			isfirst=FALSE;
			break;
		}
	} //첫 블록이면 mingw를 이용해 ./assn3.exe를 실행했을 때 assn3.exe에 해당하는 것들이 버퍼에 남아있기에 이를 사용함
	my.setshadow(blockcolor);
	if(shadow){
		my.showshadow();
	}
	my.display();
	Sleep(velo);
	while(1){
		if(my.atBottom(blockcolor)){
			break;
		}//밑으로 내려왔으면 break;
		my.move('s', blockcolor);
		for(int i=0;i<10;i++){
			if((GetAsyncKeyState(0x41)&0x8001)&&(!isfirst) || (GetAsyncKeyState(0x41)&0x8000)){
				menudisplay(blockcolor);
				scoredisplay(score);
				my.move('a', blockcolor);
				my.setshadow(blockcolor);
				if(shadow)
					my.showshadow();
				my.display();
			}
			if((GetAsyncKeyState(0x53)&0x8001)&&(!isfirst) || (GetAsyncKeyState(0x53)&0x8000)){
				menudisplay(blockcolor);
				scoredisplay(score);
				my.move('s', blockcolor);
				if(shadow)
					my.showshadow();
				my.display();
			}
			if((GetAsyncKeyState(0x44)&0x8001)&&(!isfirst) || (GetAsyncKeyState(0x44)&0x8000)){
				menudisplay(blockcolor);
				scoredisplay(score);
				my.move('d', blockcolor);
				my.setshadow(blockcolor);
				if(shadow)
					my.showshadow();
				my.display();
			}
			if((GetAsyncKeyState(0x57)&0x8001)&&(!isfirst) || (GetAsyncKeyState(0x57)&0x8000)){
				menudisplay(blockcolor);
				scoredisplay(score);
				my.rotate('w', blockcolor);
				if(shadow)
					my.showshadow();
				my.display();
			}
			if((GetAsyncKeyState(0x58)&0x8001)&&(!isfirst) || (GetAsyncKeyState(0x58)&0x8000)){
				menudisplay(blockcolor);
				scoredisplay(score);
				my.rotate('x', blockcolor);
				if(shadow)
					my.showshadow();
			}
			if((GetAsyncKeyState(0x4D)&0x8001)&&(!isfirst) || (GetAsyncKeyState(0x4D)&0x8000)){
				menudisplay(blockcolor);
				scoredisplay(score);
				shadow=!shadow;
				if(shadow){my.showshadow();}
				else{my.deleteshadow();}
			}
			if((GetAsyncKeyState(VK_SPACE)&0x8001)&&(!isfirst) || (GetAsyncKeyState(VK_SPACE)&0x8000)){
				menudisplay(blockcolor);
				scoredisplay(score);
				my.goBottom(blockcolor);
				break;
			}
			char ch;
			if((GetAsyncKeyState(ch)&0x8001)){
				menudisplay(blockcolor);
				scoredisplay(score);
				if(shadow){my.showshadow();}
			}
			Sleep(velo/10);
		}
	}
	gotoxy(0,0);
	return shadow;
} //Block 내려오게 함

void nextdisplay(int blocklist[], int cnt){
	if(blocklist[cnt]==0){//랜덤하게 정해진 것의 종류가 blocklist[cnt]이기에 이 종류에 따라 다음 걸 display
		Tetrimino_I my=Tetrimino_I(15,4);
		my.display();
	}
	else if(blocklist[cnt]==1){
		Tetrimino_L my=Tetrimino_L(15,4);
		my.display();
	}
	else if(blocklist[cnt]==2){
		Tetrimino_J my=Tetrimino_J(15,4);
		my.display();
	}
	else if(blocklist[cnt]==3){
		Tetrimino_O my=Tetrimino_O(15,4);
		my.display();
	}
	else if(blocklist[cnt]==4){
		Tetrimino_S my=Tetrimino_S(15,4);
		my.display();
	}
	else if(blocklist[cnt]==5){
		Tetrimino_T my=Tetrimino_T(15,4);
		my.display();
	}
	else{
		Tetrimino_Z my=Tetrimino_Z(14,3);
		my.display();
	}
}

int main(void){
	fstream scoref;
	printf("\e[?25l");
	scoref.open("score.txt", ios_base::in);
	scoref.close();
	bool shadow=true;
	int *scores=new int[1000];
	int scoretime=0;
	while(1){
		system("clear");
		string ask;
		int score = 0;
		float velo;
		bool game=true;
		int blockcolor[200]={};
		menudisplay(blockcolor);
		scoredisplay(score);
		int cnt=0;
		int blocklist[7]={};
		randomarray(blocklist, cnt); //첫 블록 만들고
		int myblock=blocklist[cnt]; // temp에 지정해놓기
		cnt++;
		while(game){
			velo=1000/(1+0.1*((int)(score/1000)));
			randomarray(blocklist, cnt); //다음 블록 랜덤하게 생성
			nextdisplay(blocklist, cnt); //다음 블록 display
			if(myblock==0){ //내려오는 블록의 종류에 따라 블록을 내림
				Tetrimino_I my=Tetrimino_I(6,2, blockcolor);
				shadow=blockdown(my, velo, blockcolor, shadow, score);
			}
			else if(myblock==1){
				Tetrimino_L my=Tetrimino_L(6,2, blockcolor);
				shadow=blockdown(my, velo, blockcolor, shadow, score);
			}
			else if(myblock==2){
				Tetrimino_J my=Tetrimino_J(6,2, blockcolor);
				shadow=blockdown(my, velo, blockcolor, shadow,score);
			}
			else if(myblock==3){
				Tetrimino_O my=Tetrimino_O(6,2, blockcolor);
				shadow=blockdown(my, velo, blockcolor, shadow,score);
			}
			else if(myblock==4){
				Tetrimino_S my=Tetrimino_S(6,2, blockcolor);
				shadow=blockdown(my, velo, blockcolor, shadow,score);
			}
			else if(myblock==5){
				Tetrimino_T my=Tetrimino_T(6,2, blockcolor);
				shadow=blockdown(my, velo, blockcolor, shadow,score);
			}
			else{
				Tetrimino_Z my=Tetrimino_Z(6,2, blockcolor);
				shadow=blockdown(my, velo, blockcolor, shadow,score);
			}
			score+=hasline(blockcolor); //다 내렸을 때 점수가 있으면 점수 추가
			system("clear");
			menudisplay(blockcolor); 
			scoredisplay(score);//리셋
			for(int i=0;i<10;i++){
				if(blockcolor[i]!=0){
					game=false;
					break;
				}
			} //맨 위에 줄이 차 있으면 게임 끝
			myblock=blocklist[cnt]; //다음 블록을 내려갈 블록으로 지정
			if(cnt==6){ //7가지 다 만들어졌으면 다시 처음부터 랜덤으로 블록 생성
				cnt=-1;
				for(int i=0;i<7;i++){
					blocklist[i]=0;
				}
			}
			cnt++;
		}
		while(1){
			gotoxy(0, 23);
			printf("\e[?25h");
			cout<<"Do you want to save your score? (y/n) ";
			getline(cin, ask); //이때까지 테트리스 조정했던 것들이 다 입력된 상태이기에 string으로 받음
			if(ask[ask.size()-1]=='y'){
				scores[scoretime]=score;
				scoref.open("score.txt", ios_base::out);
				for(int i=0;i<=scoretime;i++){
					scoref<<scores[i]<<endl;
				}
				scoref.close();
				break;
			}
			else if(ask[ask.size()-1]=='n')
				break;
			else //예외처리
				cout<<"Not valid response"<<endl;
		}
		while(1){
			cout<<"Do you want to restart? (y/n) ";
			getline(cin, ask);
			if(ask[ask.size()-1]=='n'){
				return 0;
			}
			else if(ask[ask.size()-1]=='y'){
				system("clear");
				break;
			}
			else //예외처리
				cout<<"Not valid response"<<endl;
		}
	}
}
