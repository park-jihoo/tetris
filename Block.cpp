//Honor Code
//나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다.
//I completed this programming task without the improper help of others
#include <iostream>
#include "Block.h"

using namespace std;

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define cRED "\x1b[31m"
#define cGREEN "\x1b[32m"
#define cYELLOW "\x1b[33m"
#define cBLUE "\x1b[34m"
#define cMAGENTA "\x1b[35m"
#define cCYAN "\x1b[36m"
#define cWHITE "\x1b[37m"
#define cRESET "\x1b[0m"

Block::Block()
{
	x=0;
	y=0;
	color=CYAN;
	msg="■";
}

Block::Block(int x_, int y_, Color color_)
{
	x = x_;
	y = y_;
	color = color_;
	msg ="■";
}
Block::Block(int x_, int y_, Color color_, string msg_)
{
	x = x_;
	y = y_;
	color = color_;
	msg = msg_;
}

Block Block::operator=(const Block &pt){
	return Block(pt.x, pt.y, pt.color, pt.msg);
}

Block Block::operator+(const Block &pt)
{
	return Block(x + pt.x, y + pt.y, color, msg);
}	

void Block::display()
{
	gotoxy(this->x, this->y);
	if (color == RED) {cout<< cRED << msg << cRESET<<endl;}
	else if (color == GREEN) {cout<< cGREEN << msg << cRESET<<endl;}
	else if (color == YELLOW) {cout<< cYELLOW << msg << cRESET<<endl;}
	else if (color == BLUE) {cout<< cBLUE << msg << cRESET<<endl;}
	else if (color == MAGENTA) {cout<< cMAGENTA << msg << cRESET<<endl;}
	else if (color == CYAN) {cout<< cCYAN << msg << cRESET<<endl;}
	else {cout<< cWHITE << msg << cRESET<<endl;}
}

void Tetrimino::display(){
	for(int i=0;i<4;i++){
		blocks[i].display();
	}
}//해당하는 블록 4개 디스플레이

void Tetrimino::setshape(int shape[]){
	int x=blocks[0].getX();
	int y=blocks[0].getY();
	for(int i=0;i<4;i++){
		blocks[i].setX(x+shape[i*2]-shape[0]);
		blocks[i].setY(y+shape[i*2+1]-shape[1]);
	}
}//모양 설정

int Tetrimino::getmaxX(){
	int max=0;
	for(int i=0;i<4;i++){
		if(blocks[i].getX()>max)
			max=blocks[i].getX();
	}
	return max;
}//가장 큰 X값 찾기
int Tetrimino::getminX(){
	int min=20;
	for(int i=0;i<4;i++){
		if(blocks[i].getX()<min)
			min=blocks[i].getX();
	}
	return min;
}//가장 작은 X값 찾기

void Tetrimino::move(char ch, int blockcolor[]){
	this->setdisplay(" ");
	if(ch=='d'){
		for(int i=0;i<4;i++){
			int a=blocks[i].getX()-2, b=blocks[i].getY()-2;
			if(blockcolor[b*10+a+1]!=0){ //옆에가 비어 있지 않으면 못 움직임
				this->setdisplay("■");
				return;
			}
		}
		if(this->getmaxX()<11){
			for(int i=0;i<4;i++){ //끝이 아니어야 움직임
				int k=blocks[i].getX();
				blocks[i].setX(++k);
				shadow[i].setX(k);
			}
		}
	}
	else if(ch=='a'){
		for(int i=0;i<4;i++){
			int a=blocks[i].getX()-2, b=blocks[i].getY()-2;
			if(blockcolor[b*10+a-1]!=0){
				this->setdisplay("■");
				return;
			}
		}
		if(this->getminX()>2){
			for(int i=0;i<4;i++){
				int k=blocks[i].getX();
				(blocks+i)->setX(--k);
				(shadow+i)->setX(k);
			}
		}
	}
	else if(ch=='s'){
		for(int i=0;i<4;i++){
			int a=blocks[i].getX()-2, b=blocks[i].getY()-2;
			if(blockcolor[(b+1)*10+a]!=0){ //밑에 블록이 있으면 못 내림
				this->setdisplay("■");
				return;
			}
		}
		for(int i=0;i<4;i++){
			int k=(blocks+i)->getY();
			(blocks+i)->setY(++k);
		}
	}
	this->setdisplay("■");
}

void Tetrimino::goBottom(int blockcolor[]){
	this->setdisplay(" ");
	while(1){
		for(int i=0;i<4;i++){
			int a=blocks[i].getX()-2, b=blocks[i].getY()-2;
			if(b==19){
				this->setdisplay("■");
				return; //아래에 도달했을 때 return;
			}
			if(blockcolor[(b+1)*10+a]!=0){
				this->setdisplay("■");
				return; //아래에 도달했을 때 return;
			}
		}
		for(int i=0;i<4;i++){
			int k=blocks[i].getY();
			blocks[i].setY(++k); //아래에 도달할 때까지 계속 내리기
		}
	}
}

void Tetrimino::rotate(char ch, int blockcolor[]){
	char ch2;
	if(ch=='w')ch2='x';
	else ch2='w';
	this->setdisplay(" ");
	this->onerotate(ch); //일단 돌려봄
	for(int i=0;i<4;i++){
		int a=(this->blocks[i].getX())-2, b=(this->blocks[i].getY())-2;
		if(a>9){ //돌렸는데 벗어나면
			this->onerotate(ch2); //원상태로 복구
			this->setdisplay("■");
			return;
		}
		if(a<0){
			this->onerotate(ch2);
			this->setdisplay("■");
			return;
		}
		if(blockcolor[10*b+a]!=0){ //돌렸는데 이미 블록이 있으면
			this->onerotate(ch2);
			this->setdisplay("■");
			return;
		}
	}
	this->setshadow(blockcolor);
	this->setdisplay("■");
}

bool Tetrimino::atBottom(int blockcolor[]){ //아래에 있는지 여부
	for(int i=0;i<4;i++){
		int a=blocks[i].getX()-2, b=blocks[i].getY()-2;
		if(b==19){
			for(int j=0;j<4;j++)
				blockcolor[(blocks[j].getY()-2)*10+blocks[j].getX()-2]=blocks[j].getColor(); //아래에 있으면 현재 블록들을 굳게 함
			return true;
		}
		if(blockcolor[(b+1)*10+a]!=0){
			for(int j=0;j<4;j++)
				blockcolor[(blocks[j].getY()-2)*10+blocks[j].getX()-2]=blocks[j].getColor(); //밑에 블록 있으면 현재 블록들을 굳게 함
			return true;
		}
	}
	return false;
}

void Tetrimino::setdisplay(string msg){
	for(int i=0;i<4;i++){
		(blocks+i)->setMsg(msg);
	}
	this->display(); //테트리미노 모양 설정
}

void Tetrimino::setshadow(int blockcolor[]){
	for(int i=0;i<4;i++){
		shadow[i].setX(blocks[i].getX());
		shadow[i].setY(blocks[i].getY());
	}
	while(1){
		for(int i=0;i<4;i++){
			int a=shadow[i].getX()-2, b=shadow[i].getY()-2;
			if(b==19){
				return;
			}
			if(blockcolor[(b+1)*10+a]!=0){
				return;
			}
		}
		for(int i=0;i<4;i++){
			int k=shadow[i].getY();
			shadow[i].setY(++k);
		}
	}
}//제일 아래로 그림자 설정

void Tetrimino::showshadow(){
	for(int i=0;i<4;i++){
		shadow[i].setMsg("□");
		shadow[i].display();
	}
}//그림자 보여주기
void Tetrimino::deleteshadow(){
	for(int i=0;i<4;i++){
		shadow[i].setMsg(" ");
		shadow[i].display();
	}
}//그림자 지우기

void Tetrimino_I::onerotate(char ch){//돌리기
	this->setdisplay(" ");
	if(ch=='w'){
		this->setshape(shape[(++shapenum)%4]);
	}
	else if(ch=='x'){
		shapenum+=3;
		this->setshape(shape[(shapenum)%4]);
	}

}
void Tetrimino_O::onerotate(char ch){
	if(ch=='w'){
		this->setshape(shape[(++shapenum)%4]);
	}
	else if(ch=='x'){
		shapenum+=3;
		this->setshape(shape[(shapenum)%4]);
	}
}
void Tetrimino_T::onerotate(char ch){
	if(ch=='w'){
		this->setshape(shape[(++shapenum)%4]);
	}
	else if(ch=='x'){
		shapenum+=3;
		this->setshape(shape[(shapenum)%4]);
	}
}
void Tetrimino_L::onerotate(char ch){
	if(ch=='w'){
		this->setshape(shape[(++shapenum)%4]);
	}
	else if(ch=='x'){
		shapenum+=3;
		this->setshape(shape[(shapenum)%4]);
	}
}
void Tetrimino_J::onerotate(char ch){
	if(ch=='w'){
		this->setshape(shape[(++shapenum)%4]);
	}
	else if(ch=='x'){
		shapenum+=3;
		this->setshape(shape[(shapenum)%4]);
	}
}
void Tetrimino_S::onerotate(char ch){
	if(ch=='w'){
		this->setshape(shape[(++shapenum)%4]);
	}
	else if(ch=='x'){
		shapenum+=3;
		this->setshape(shape[(shapenum)%4]);
	}
}
void Tetrimino_Z::onerotate(char ch){
	if(ch=='w'){
		this->setshape(shape[(++shapenum)%4]);
	}
	else if(ch=='x'){
		shapenum+=3;
		this->setshape(shape[(shapenum)%4]);
	}
}
