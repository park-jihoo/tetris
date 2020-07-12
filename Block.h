#ifndef POINT_H
#define POINT_H
#include <string>
#include <iostream>

enum Color {
	TRANS, //0
	RED, //Z
	GREEN, //S
	YELLOW,  //O
	BLUE,  //J
	MAGENTA, //T
	CYAN, //I
	WHITE, //L
};

using namespace std;

class Block {
	private:
		int x;
		int y;
		string msg;
		Color color;

	public :
		Block();
		Block(int, int, Color);
		Block(int, int, Color, string);
		int getX() const {return x;}
		int getY() const {return y;}
		string getMsg() const {return msg;}
		Color getColor() const {return color;}
		void setX(int x_) {x = x_;}
		void setY(int y_) {y = y_;}
		void setMsg(string msg_) {msg = msg_;}
		void setColor(Color color_) {color = color_;}
		Block operator=(const Block &pt);
		Block operator+(const Block &pt);
		void display();
		~Block() {};
};

class Tetrimino{
	private :
		Block* blocks;
		Block* shadow;
	public :
		Tetrimino(int x, int y, Color color){
			blocks=new Block[4];
			shadow=new Block[4];
			blocks->setX(x);
			blocks->setY(y);
			for(int i=0;i<4;i++){
				(blocks+i)->setColor(color);
				(shadow+i)->setColor(color);
				(shadow+i)->setMsg(" ");
			}
		}
		void setshape(int shape[]);
		void display();
		void move(char ch, int blockcolor[]);
		void goBottom(int blockcolor[]);
		bool atBottom(int blockcolor[]);
		virtual void onerotate(char ch)=0;
		void rotate(char ch, int blockcolor[]);
		void setshadow(int blockcolor[]);
		void showshadow();
		void deleteshadow();
		void setdisplay(string msg);
		int getmaxX();
		int getminX();
		~Tetrimino(){
			delete[] blocks;
		};
};

class Tetrimino_I : public Tetrimino{
	int shape[4][8]= {{0, 2, 1, 2, 2, 2, 3, 2},
		{2,0,2,1,2,2,2,3}, {0, 2, 1, 2, 2, 2, 3, 2},
		{2,0,2,1,2,2,2,3}};
	int shapenum;
	public:
	Tetrimino_I(int x, int y):Tetrimino(x, y, CYAN){
		setshape(shape[0]);
		shapenum=0;
	}
	Tetrimino_I(int x, int y, int blockcolor[]):Tetrimino(x, y, CYAN){
		setshape(shape[0]);
		shapenum=0;
		setshadow(blockcolor);
	}
	void onerotate(char ch);
};

class Tetrimino_O : public Tetrimino{
	int shape[4][8]= {{0,0,0,1,1,0,1,1}, {0,0,0,1,1,0,1,1}, {0,0,0,1,1,0,1,1}, {0,0,0,1,1,0,1,1}}
	;
	int shapenum;
	public:
	Tetrimino_O(int x, int y):Tetrimino(x, y, YELLOW){
		setshape(shape[0]);
		shapenum=0;
	}
	Tetrimino_O(int x, int y, int blockcolor[]):Tetrimino(x, y, YELLOW){
		setshape(shape[0]);
		shapenum=0;
		setshadow(blockcolor);
	}
	void onerotate(char ch);
};

class Tetrimino_T : public Tetrimino{
	int shape[4][8]= {{0,0,0,1,1,1,0,2},{0,0,1,0,2,0,1,1},{1,0,0,1,1,1,1,2},{1,0,0,1,1,1,2,1}};
	int shapenum;
	public:
	Tetrimino_T(int x, int y):Tetrimino(x, y, MAGENTA){
		setshape(shape[0]);
		shapenum=0;
	}
	Tetrimino_T(int x, int y, int blockcolor[]):Tetrimino(x, y, MAGENTA){
		setshape(shape[3]);
		shapenum=0;
		setshadow(blockcolor);
	}
	void onerotate(char ch);
};

class Tetrimino_L : public Tetrimino{
	int shape[4][8]= {{2,1,0,2,1,2,2,2},{1,1,1,2,1,3,2,3},{0,2,1,2,2,2,0,3},{0,1,1,1,1,2,1,3}};
	int shapenum;
	public:
	Tetrimino_L(int x, int y):Tetrimino(x, y,  WHITE){
		setshape(shape[0]);
		shapenum=0;
	}
	Tetrimino_L(int x, int y, int blockcolor[]):Tetrimino(x, y, WHITE){
		setshape(shape[0]);
		shapenum=0;
		setshadow(blockcolor);
	}
	void onerotate(char ch);
};

class Tetrimino_J : public Tetrimino{
	int shape[4][8]= {{1,0,1,1,0,2,1,2},{0,0,0,1,1,1,2,1},{1,0,2,0,1,1,1,2},{0,1,1,1,2,1,2,2}};
	int shapenum;
	public:
	Tetrimino_J(int x, int y):Tetrimino(x, y, BLUE){
		setshape(shape[0]);
		shapenum=0;
	}
	Tetrimino_J(int x, int y, int blockcolor[]):Tetrimino(x, y, BLUE){
		setshape(shape[0]);
		shapenum=0;
		setshadow(blockcolor);
	}
	void onerotate(char ch);
};

class Tetrimino_S : public Tetrimino{
	int shape[4][8]= {{1,1,2,1,0,2,1,2},{0,1,0,2,1,2,1,3},{1,1,2,1,0,2,1,2},{0,1,0,2,1,2,1,3}};
	int shapenum;
	public:
	Tetrimino_S(int x, int y):Tetrimino(x, y,  GREEN){
		setshape(shape[0]);
		shapenum=0;
	}
	Tetrimino_S(int x, int y, int blockcolor[]):Tetrimino(x, y, GREEN){
		setshape(shape[0]);
		shapenum=0;
		setshadow(blockcolor);
	}
	void onerotate(char ch);
};

class Tetrimino_Z : public Tetrimino{
	int shape[4][8]= {{0,1,1,1,1,2,2,2},{2,1,1,2,2,2,1,3},{0,1,1,1,1,2,2,2},{2,1,1,2,2,2,1,3}};
	int shapenum;
	public:
	Tetrimino_Z(int x, int y):Tetrimino(x, y, RED){
		setshape(shape[0]);
		shapenum=0;
	}
	Tetrimino_Z(int x, int y, int blockcolor[]):Tetrimino(x, y, RED){
		setshape(shape[0]);
		shapenum=0;
		setshadow(blockcolor);
	}
	void onerotate(char ch);
};

#endif
