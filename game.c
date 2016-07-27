#include "game.h"
#include "myLib.h"
#include "finish.h"

#include <stdlib.h>
#include <stdio.h>


int enemies1Row = ENEMY_1_ROW;
int en1del = EN_1_DEL;

int lives = LIVES;


PLAYER p1 = {START_ROW, START_COL, START_ROW, START_COL, RDEL, CDEL};

ENEMY enemy1_1 = {ENEMY_1_ROW, 50, EN_1_DEL, EN_1_DEL};
ENEMY enemy1_2 = {ENEMY_1_ROW, 110, EN_1_DEL, EN_1_DEL};
ENEMY enemy1_3 = {ENEMY_1_ROW, 170, EN_1_DEL, EN_1_DEL};

ENEMY enemy2_1 = {EN2_ROW, EN2_COL, EN2_DEL, EN2_DEL};
ENEMY enemy2_2 = {EN2_ROW+30-SIZE, EN2_COL+30, EN2_DEL, EN2_DEL};

ENEMY enemy3_1 = {EN3_ROW, EN3_COL, EN3_DEL, EN3_DEL};
ENEMY enemy3_2 = {EN3_ROW, EN3_COL+95, EN3_DEL, EN3_DEL};



////////////****DRAW BOARD******////////////////

//SET UP BOARD
void drawLevel1Board() {
	drawRect(20, 10, 40, 220, BLACK);
	drawRect(60, 200, 50, 30, BLACK);
	drawRect(70, 10, 40, 190, BLACK);
	drawRect(110, 10, 40, 30, BLACK);
	drawRect(120, 40, 30, 160, BLACK);
	drawImage3(120, 200, FINISH_WIDTH, FINISH_HEIGHT, finish);

	printHeader();
}
void resetBoard()
{
	p1.oldRow = p1.row;
	p1.oldCol = p1.col;
	clearOld();

	p1.row = START_ROW;
	p1.col = START_COL;
	enemies1Row = ENEMY_1_ROW;
	drawCurr();

	printLives();
}
void printHeader() {
	sprintf(buffer, "Good Luck!");
	drawString(5,10,buffer,BLACK);
}


//clear old element positions
void clearOld() {
	drawRect(p1.oldRow, p1.oldCol, SIZE, SIZE, BLACK);
	clearEnemies1();
	clearEnemies2();
	clearEnemies3();
}
//DRAW NEW ELEMENT POSITIONS
void drawCurr()
{
	drawRect(p1.row, p1.col, SIZE, SIZE, RED);
	drawEnemies1();
	drawEnemies2();
	drawEnemies3();
	printLives();
}



/////////******LIVES******//////////////////////////

void refillLives() {
	lives = LIVES;
}
int currLives() {
	return lives;
}
void printLives() {
	//clear old num lives
	drawRect(5, 180, 8, 48, GRAY);

	//draw new num lives
	sprintf(buffer, "Lives: %d", lives);
	if (lives == 1) {
		drawString(5,180,buffer,RED);
	} else {
		drawString(5,180,buffer,BLACK);
	}
}




////////////******COLLISION TEST******///////////////////

//TEST FOR ANY COLLISIONS
int isCollide() {
	if (checkEnemies1() == 1 || checkEnemies2() == 1 || checkEnemies3() == 1) {
		lives--;
		return 1;
	}
	return 0;
}
//check if two squares have collided, return 1 if true
int checkSquareCollide(int r1, int c1, int size1, int r2, int c2, int size2)
{
	if ((r1 >= r2 && r1 <= (r2+size2)) || ((r1+size1) >= r2 && (r1+size1) <= (r2+size2)) || (r2 >= r1 && r2 <= (r1+size1)) || ((r2+size2) >= r1 && (r2+size2) <= (r1+size1))) {
		if ((c1 >= c2 && c1 <= (c2+size2)) || ((c1+size1) >= c2 && (c1+size1) <= (c2+size2)) || (c2 >= c1 && c2 <= (c1+size1)) || ((c2+size2) >= c1 && (c2+size2) <= (c1+size1))) {
			return 1;
		}
	}
	return 0;
}
int isWin() {
	return checkSquareCollide(p1.row, p1.col, SIZE, 120, 200, 30);
}






///////////*****MOVE PLAYER*****//////////////////
//move functions include boundary test

void moveRight() {
	if ((p1.row > 110-SIZE && p1.row < 120 && p1.col >= 40-SIZE) //second to third row transition boundary
		|| p1.col >= 230-SIZE) //right boundary
		return;
	p1.oldCol = p1.col;
	p1.oldRow = p1.row;
	p1.col = p1.col + CDEL;
}
void moveLeft() {
	if (p1.col <= 10 //left boundary
		|| (p1.row > 60-SIZE && p1.row < 70 && p1.col <= 200)) //first to second row transition boundary
		return;
	p1.oldCol = p1.col;
	p1.oldRow = p1.row;
	p1.col = p1.col - CDEL;
}
void moveUp() {
	if (p1.row <= 20 //upper boundary
		|| (p1.row <= 70 && p1.row > 60 && p1.col < 200) //second row boundary
		|| (p1.row <= 120 && p1.row > 110 && p1.col > 40-SIZE)) //third row boundary
		return;
	p1.oldRow = p1.row;
	p1.oldCol = p1.col;
	p1.row = p1.row - RDEL;
}
void moveDown() {
	if ((p1.row >= 60-SIZE && p1.row < 70 && p1.col < 200) //first row boundary
		|| (p1.row >= 110-SIZE && p1.row < 120 && p1.col > 40-SIZE) //second row boundary
		|| p1.row >= 150-SIZE) //lower boundary
		return;
	p1.oldRow = p1.row;
	p1.oldCol = p1.col;
	p1.row = p1.row + RDEL;
}





///////////////*****ENEMY SPECIFIC FUNCTIONS******///////////////////////


//ENEMIES 1
void drawEnemies1() {
	for (int i = 0; i<3; i++) {
		drawRect(enemies1Row, enemy1_1.col + (i*10), ENEMY_SIZE, ENEMY_SIZE, BLUE);
		drawRect(enemies1Row, enemy1_2.col + (i*10), ENEMY_SIZE, ENEMY_SIZE, BLUE);
		drawRect(enemies1Row, enemy1_3.col + (i*10), ENEMY_SIZE, ENEMY_SIZE, BLUE);
	}
}
void clearEnemies1() {
	for (int i = 0; i<3; i++) {
		drawRect(enemies1Row, enemy1_1.col + (i*10), ENEMY_SIZE, ENEMY_SIZE, BLACK);
		drawRect(enemies1Row, enemy1_2.col + (i*10), ENEMY_SIZE, ENEMY_SIZE, BLACK);
		drawRect(enemies1Row, enemy1_3.col + (i*10), ENEMY_SIZE, ENEMY_SIZE, BLACK);
	}
	if (enemies1Row > 56 || enemies1Row < 23) {
		en1del = -en1del;
	}
	enemies1Row += en1del;
}
int checkEnemies1() {
	for (int i = 0; i < 3; i++) {
		if (checkSquareCollide(p1.row, p1.col, SIZE, enemies1Row, enemy1_1.col + (i*10), ENEMY_SIZE)
			|| checkSquareCollide(p1.row, p1.col, SIZE, enemies1Row, enemy1_2.col + (i*10), ENEMY_SIZE)
			|| checkSquareCollide(p1.row, p1.col, SIZE, enemies1Row, enemy1_3.col + (i*10), ENEMY_SIZE)) {
			return 1;
		}
	}
	return 0;
}



//ENEMIES 2
void drawEnemies2() {
	drawRect(enemy2_1.row, enemy2_1.col, ENEMY_SIZE, ENEMY_SIZE, BLUE);
	drawRect(enemy2_2.row, enemy2_2.col, ENEMY_SIZE, ENEMY_SIZE, BLUE);
}
void clearEnemies2() {
	drawRect(enemy2_1.row, enemy2_1.col, ENEMY_SIZE, ENEMY_SIZE, BLACK);
	if(enemy2_1.row < EN2_ROW || enemy2_1.row > EN2_ROW+30-SIZE) enemy2_1.rdel = -enemy2_1.rdel;
	if(enemy2_1.col < EN2_COL || enemy2_1.col > EN2_COL+210-SIZE) enemy2_1.cdel = -enemy2_1.cdel;
	enemy2_1.row += enemy2_1.rdel;
	enemy2_1.col += enemy2_1.cdel;

	drawRect(enemy2_2.row, enemy2_2.col, ENEMY_SIZE, ENEMY_SIZE, BLACK);
	if(enemy2_2.row < EN2_ROW || enemy2_2.row > EN2_ROW+30-SIZE) enemy2_2.rdel = -enemy2_2.rdel;
	if(enemy2_2.col < EN2_COL || enemy2_2.col > EN2_COL+210-SIZE) enemy2_2.cdel = -enemy2_2.cdel;
	enemy2_2.row += enemy2_2.rdel;
	enemy2_2.col += enemy2_2.cdel;
}
int checkEnemies2() {
	if (checkSquareCollide(p1.row, p1.col, SIZE, enemy2_1.row, enemy2_1.col, ENEMY_SIZE)
		|| checkSquareCollide(p1.row, p1.col, SIZE, enemy2_2.row, enemy2_2.col, ENEMY_SIZE)) {
		return 1;
	}
	return 0;
}



//ENEMIES 3
void drawEnemies3() {
	drawRect(enemy3_1.row, enemy3_1.col, ENEMY_SIZE, ENEMY_SIZE, BLUE);
	drawRect(enemy3_2.row, enemy3_2.col, ENEMY_SIZE, ENEMY_SIZE, BLUE);
}
void clearEnemies3() {
	drawRect(enemy3_1.row, enemy3_1.col, ENEMY_SIZE, ENEMY_SIZE, BLACK);
	if(enemy3_1.row < EN3_ROW || enemy3_1.row > EN3_ROW+30-SIZE) enemy3_1.rdel = -enemy3_1.rdel;
	if(enemy3_1.col < EN3_COL || enemy3_1.col > EN3_COL+90-SIZE) enemy3_1.cdel = -enemy3_1.cdel;
	enemy3_1.row += enemy3_1.rdel;
	enemy3_1.col += enemy3_1.cdel;

	drawRect(enemy3_2.row, enemy3_2.col, ENEMY_SIZE, ENEMY_SIZE, BLACK);
	if(enemy3_2.row < EN3_ROW || enemy3_2.row > EN3_ROW+30-SIZE) enemy3_2.rdel = -enemy3_2.rdel;
	if(enemy3_2.col < EN3_COL+90 || enemy3_2.col > EN3_COL+180-SIZE) enemy3_2.cdel = -enemy3_2.cdel;
	enemy3_2.row += enemy3_2.rdel;
	enemy3_2.col += enemy3_2.cdel;
}
int checkEnemies3() {
	if (checkSquareCollide(p1.row, p1.col, SIZE, enemy3_1.row, enemy3_1.col, ENEMY_SIZE)
		|| checkSquareCollide(p1.row, p1.col, SIZE, enemy3_2.row, enemy3_2.col, ENEMY_SIZE)) {
		return 1;
	}
	return 0;
}