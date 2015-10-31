#include <stdio.h>
#include "board.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
int main() {
	Board *b = new Board();
	
	while(true) {
		b->printBoard();

		int choice;
		printf ("Menu:\n 1 - Move Piece\n 2 - Set black(o) \n 3 - Set red(x) \n 4 - Random Test \n");
		cin >> choice;
		if(choice == 1) {
			string input;

			printf ("Move \"x,y\" 0-7... \n");
			cin >> input;
			int x=-1,y=-1;
			sscanf(input.c_str(),"%d,%d",&x,&y);
			Board::Square *sq = b->squareAt(x,y);
			if(sq->getChecker() != NULL && sq->getChecker()->isBlack) printf("Black \n");
			if(sq->getChecker() != NULL && !(sq->getChecker()->isBlack)) printf("Red \n");				
			if(sq->getChecker() == NULL) {
				printf("Nothing there...\n");
				goto exit;
			}  			

			printf("to \"x,y\" 0-7... \n");
			cin >> input;
			int x2=-1,y2=-1;
			sscanf(input.c_str(),"%d,%d",&x2,&y2);
			Board::Square *sq2 = b->squareAt(x2,y2);			
			if(sq2->getChecker() != NULL) { 
				printf("Square Not Available\n");
				goto exit;
			}
			
			sq2->setChecker(sq->getChecker());
			sq->setChecker(NULL);
		} else if (choice == 2 || choice == 3) {
			string input;
			Board::Checker *checker = new Board::Checker;
			if (choice == 2) checker->isBlack = true;

			printf ("Place black \"x,y\" 0-7... \n");
			cin >> input;
			int x=-1,y=-1;
			sscanf(input.c_str(),"%d,%d",&x,&y);
			Board::Square *sq = b->squareAt(x,y);
			if(sq->getChecker() != NULL) {
				printf("Square Not Available\n");
                                goto exit;
                        }
			sq->setChecker(checker);
		} else if (choice == 4) {
			b = new Board();
			srand(time(NULL));
			int q = 0;
			while (q < 40) {
				int rx = rand() % 8;
				int ry = rand() % 8;
				Board::Square *sq = b->squareAt(rx,ry);	
				if(sq->getChecker() == NULL) {
					Board::Checker *checker = new Board::Checker;
					int rc = rand() % 2;
					if(rc==1) checker->isBlack = true;
					sq->setChecker(checker);
					q++;
				}
			}
		}	
		
		

exit:
		cout << "";
	}

	return 0;
}
