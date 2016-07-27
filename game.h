

#define START_ROW 35
#define START_COL 20
#define SIZE 8
#define LIVES 3

#define RDEL 1
#define CDEL 1

#define ENEMY_SIZE 3

#define ENEMY_1_ROW 33
#define EN_1_DEL 1

#define EN2_ROW 75
#define EN2_COL 15
#define EN2_DEL 2

#define EN3_ROW 122
#define EN3_COL 15
#define EN3_DEL 1

char buffer[41];

typedef struct
{
	int row, col, rdel, cdel;
} ENEMY;

typedef struct
{
	int row, col, oldRow, oldCol, rdel, cdel;
} PLAYER;


void drawLevel1Board();
void printHeader();
void resetBoard();
void drawCurr();
void clearOld();

void refillLives();
int currLives();
void printLives();

void moveRight();
void moveLeft();
void moveUp();
void moveDown();

void drawEnemies1();
void clearEnemies1();

void drawEnemies2();
void clearEnemies2();

void drawEnemies3();
void clearEnemies3();

int isCollide();
int checkSquareCollide(int r1, int c1, int size1, int r2, int c2, int size2);
int checkEnemies1();
int checkEnemies2();
int checkEnemies3();

int isWin();
