#include "board.h"
#include <stdio.h>
Board::Board() {
	for(int y=0; y<8; y++){
		for(int x=0; x<8; x++){
			Square *s = new Square(this);
			s->x = x;
			s->y = y;
			squares[x][y] = *s;
		}
	}
}

Board::~Board() {

}

void Board::printBoard() {
	for(int y=7; y>=0; y--){
		std::string line = std::to_string(y)+"|";
		for(int x=0; x<8; x++){
			Square *s = squareAt(x,y);
			std::string sqLine;
			Board::Checker *c = s->getChecker(); 
			if(c != NULL && c->isBlack) sqLine = "o|";
			else if(c != NULL) sqLine="x|";
			else sqLine = " |";
			line.append(sqLine);
		}
		line.append("\n");
		printf("%s",line.c_str());
	}
	printf("  0 1 2 3 4 5 6 7 \n");	

	for(int y=0; y<8; y++){
		for(int x=0; x<8; x++){
			Square *s = squareAt(x,y);
			if(s->getChecker() != NULL) s->checkSides();
		}
	}

}

Board::Square* Board::squareAt(int x, int y) {
	Square *sq = &(squares[x][y]);
	return sq;
}


//Square Functions
Board::Square::Square() {
	x = -1;
	y = -1;
}

Board::Square::Square(Board *owner) {
	board = owner;
	checker = NULL;	
}

void Board::Square::checkSides() {
	//NW = 1, N = 2, NE = 3, E = 4
	for(int d=1;d<5;d++) {
		int direction = d;
		std::string apString = "{"+std::to_string(x)+","+std::to_string(y) + "}"+",";
		int count = 1;
		checkSide(direction,count,apString);
		if (count == 4) printf("ap: %s \n",apString.c_str());
	}


	//printf("count: %d \n", count);
	//printf("ap: %s \n",apString.c_str());
}

void Board::Square::checkSide(int dir, int &count, std::string &ap) {
	int cX; 
	int cY;
	if(dir==1) {
		cX = x - 1;
		cY = y + 1;
	} else if (dir == 2) {
		cX = x;
		cY = y + 1;
	} else if (dir == 3) {
		cX = x + 1;
		cY = y + 1;
	} else if (dir == 4) {
		cX = x + 1;
		cY = y;
	} else {
		return;
	}
	
	if (cX > 7 || cX < 0 || cY > 7 || cY < 0) return;
	Square *s= board->squareAt(cX,cY);
	
	if(s->getChecker() != NULL && s->getChecker()->isBlack == checker->isBlack) {
		ap.append("{"+std::to_string(cX)+","+std::to_string(cY) + "}"+",");		
		count++;
		if(count==4)return;
		else s->checkSide(dir,count,ap);
	}
}

Board::Checker* Board::Square::getChecker() {
	return checker;
}

void Board::Square::setChecker(Checker *c) {
	checker = c;
}

