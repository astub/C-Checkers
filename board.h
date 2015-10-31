#include <string>
class Board {
public:
	struct Checker {
		bool isBlack;
	};

	class Square {
	private:
		Board *board;
		Checker *checker;
	public:
		int x;
		int y;
		
		void checkSides();
		void checkSide(int,int&,std::string&);
		
		Checker* getChecker();
		void setChecker(Checker*);	
			
		Square();
		Square(Board*);
	};

	void printBoard();
	Square* squareAt(int,int);	
	
	Board();
	~Board();
private:
	Square squares[8][8];	
};

