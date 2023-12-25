/***********************************************************************
 * File: main.cpp
 * Author:	陳仕興 B11115011
 *			王家宏 B11130038
 * Create Date: 2023-05-19
 * Editor:	陳仕興 B11115011
 *			王家宏 B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program do a dungeon game
***********************************************************************/

#include "main.h"
#include "Ghost.h"
#include "Zombie.h"
#include "Trigger.h"
#include "Sword.h"
#include "HealthPotion.h"
#include"Cartridge.h"

//to calculate the offset in the direction array
#define offset(dirName, number) (dirName + number) % 4

Hero gHero(2, 2);

bool isLose = false;
bool isWin = false;

float creatureDensity = 0.02;

// Constent value
const char GWALL = 'O';
const char GNOTHING = ' ';

int GWIDTH = -1;
int GHEIGHT = -1;
const int MIN_SIZE = 10;
const double gTimeLog = 0.033;

// Distance
const int gDistance = 4;

// 用來儲存版面資料
char** gBoard;

//set the direction
const int direction[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

// record the map is meet
bool** used;

// set total charactors
const int totalCharactor = 4;

int gameLevel = 1;

int maxLevel;

// 定義六種輸入指令與對應陣列index
enum ValidInput
{
	EW = 0,
	ES = 1,
	EA = 2,
	ED = 3,
	ESPACE = 4,
	EESC = 5,
	ESave = 6,
	ELoad = 7,
	INVALID,
};

// Vectore to store the creatures in the game
std::vector<Creature*> gCreatures;

// FUNCTION DECLARATION
// ===============================================================================================================
// Intent: To do a correct task when the user gave the input.
// Pre: 'key[]' parameter represents an array used to manage the state of keyboard input.
// Post: Do a task according to the user input.
void keyUpdate(bool key[]);

// Intent: To setup the board.
// Pre: The 'rowN' parameter represents the row size of the board, 
//		the 'colN' parameter represents the col size of the board.
// Post: Setup the board.
void setUpBoard(int rowN, int colN);

// Intent: To generate the map by dfs.
// Pre: The variable x, y, dir must have a value.
// Post: The function returns nothing.
void generateMap(int x, int y, int dir);

// Intent: Draw the board.
// Pre: All the creatures, trigers, hero have a valid position on the board.
// Post: The bord is drawn.
void draw(void);

// Intent: Output information.
// Pre: All hero, triggers, creatures' variables are valid and not NULL.
// Post: Print all the information.
void drawInfo(void);

// Intent: Update the board state.
// Pre: 'key[]' parameter represents an array used to manage the state of keyboard input.
// Post: The board state is updated.
void update(bool key[]);

// Intent: Set up for the next level.
// Pre: All the creatures in the current level are dead.
// Post: Move to the next level.
void nextLevel();

// Intent: Shot the bullet.
// Pre: Hero is valid and not NULL.
// Post: The hero shot the bullet.
void shot();

bool shotCreature(int x, int y);

// Intent: Save the map status.
// Pre: All the related class and variables are not NULL.
// Post: The current game condition is saved into a file.
void saveMap();

// Intent: Load the map status.
// Pre: None.
// Post: Update the map status according to the given save file.
void loadMap();

// Intent: To print the tutorial of the game before the game start
// Pre: None
// Post: Print the tutorial
void printTutorial();
// ===============================================================================================================

std::vector<Item*> gItems;

int main(int argc, char** argv)
{
	srand(time(NULL));

	// 用來管理鍵盤輸入狀態的陣列
	bool gKeyState[ValidInput::INVALID];
	for (int i = 0; i < ValidInput::INVALID; i++)
	{
		gKeyState[i] = false;
	}

	printTutorial();	// To print the tutorial

	// Take the user input about the size of the map until the user give the valid input
	while (true)
	{
		std::cout << "Enter Max Level: ";
		std::cin >> maxLevel;
		std::cout << "Enter Width: ";
		std::cin >> GWIDTH;
		std::cout << "Enter Height: ";
		std::cin >> GHEIGHT;
		system("CLS");
		if (GHEIGHT < MIN_SIZE || GWIDTH < MIN_SIZE)
		{
			std::cout << "Illegal, both has to be larger than " << MIN_SIZE << std::endl;
		}
		else if (maxLevel <= 0)
		{
			std::cout << "Illegal, maxLevel has to be larger than 0" << std::endl;
		}
		else
		{
			break;
		}
	}

	// Setup a clear dungeon
	setUpBoard(GHEIGHT, GWIDTH);

	// Draw the bord and information
	draw();
	drawInfo();

	// Variable for game loop
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	// Run the game loop
	while (!gKeyState[ValidInput::EESC])
	{
		// Compute the time lap
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;

		// Execute the game loop
		if (timeFrame >= gTimeLog)
		{
			update(gKeyState);
			startT = clock();
		}

		// Update the key
		keyUpdate(gKeyState);
		
		endT = clock();
		if (gKeyState[ValidInput::ESave])
		{
			saveMap();
		}
		else if (gKeyState[ValidInput::ELoad])
		{
			loadMap();
		}

		if (isLose)
		{
			break;
		}
		if (isWin)
		{
			break;
		}
	}

	//system("pause");

	return 0;
}

// Intent: To print the tutorial of the game before the game start
// Pre: None
// Post: Print the tutorial
void printTutorial()
{
	cout << "WELCOME TO THE GROUP 33 DUNGEON GAME\n\n";
	cout << "To win this game you must kill all the creatures and move on to the next level.\n";
	cout << "When the game starts, your character will have the base stats (hp = 50, attack = 5, 5 bullets).\n";
	cout << "You can hit the cratures by making your character position the same with the creature position,\n";
	cout << "Or you can use your gun, by clicking space. Note that if you do not have any bullet, \nyour gun will not work.\n";
	cout << "Your character can be upgraded throughout the game to increase its stats.\n";
	cout << "When you move to the next level, the creatures damage and density will be increased.\n\n";
	cout << "============================================CREATURES===============================================\n";
	cout << "There are two types of creatures in the game which are, Zombie and Ghost.\n";
	cout << "Zombie (Z) can chase your character and drain your blood.\n";
	cout << "Ghost (G) can do teleportation in 5% chance on each move.\n";
	cout << "====================================================================================================\n\n";
	cout << "================================================ITEMS===============================================\n";
	cout << "There will be 4 items spreads accross the map, which are, Triggers, Sword, Health Potion, and Bullet\n";
	cout << "Triggers (T) the triggers can give you exp to upgrade your level, when your level is upgraded,\n";
	cout << "you can increase your max HP.\n";
	cout << "Sword (S) can increase your damage.\n";
	cout << "Health Potion (P) can increase your health, note that it will not exceed your max HP.\n";
	cout << "Bullet (B) is the ammo for your gun.\n\n";
	cout << "PS: These items are not infintely generated.\n";
	cout << "====================================================================================================\n\n";
}

// Intent: To do a correct task when the user gave the input
// Pre: 'key[]' parameter represents an array used to manage the state of keyboard input.
// Post: Do a task according to the user input.
void keyUpdate(bool key[])
{
	// Set the 'key' to false
	for (int i = 0; i < ValidInput::INVALID; i++)
	{
		key[i] = false;
	}
	char input = _getch();
	switch (input)
	{
	case 'w':    // If the input is 'w' set 'EW'-th element to true
	case 'W':
		key[ValidInput::EW] = true;
		break;
	case 's':    // If the input is 's' set 'ES'-th element to true
	case 'S':
		key[ValidInput::ES] = true;
		break;
	case 'a':    // If the input is 'a' set 'EA'-th element to true
	case 'A':
		key[ValidInput::EA] = true;
		break;
	case 'd':    // If the input is 'd' set 'ED'-th element to true
	case 'D':
		key[ValidInput::ED] = true;
		break;
	case ' ':    // If the input is ' ' set 'ESPACE'-th element to true
		key[ValidInput::ESPACE] = true;
		break;
	case 27:    // If the input is escape set 'EESC'-th element to true
		key[ValidInput::EESC] = true;
		break;
	case '1':    // If the input is '1' set 'ESave'-th element to true
		key[ValidInput::ESave] = true;
		break;
	case '2':    // If the input is '1' set 'ELoad'-th element to true
		key[ValidInput::ELoad] = true;
		break;
	default:
		break;
	}

	if (input == 0 || input == -32) {  // 檢查是否是特殊按鍵
		char arrowKey = _getch();
		switch (arrowKey) {
		case 72:
			key[ValidInput::EW] = true;
			break;
		case 80:
			key[ValidInput::ES] = true;
			break;
		case 75:
			key[ValidInput::EA] = true;
			break;
		case 77:
			key[ValidInput::ED] = true;
			break;
		default:
			break;
		}
	}
}

// Intent: Check whether the location is a valid one i.e. not a wall
// Pre: 'loc' parameter represents the given position to check
// Position: If 'loc' is a valid position return true, vice versa
bool isPositionValid(Position& pos)
{
	if (pos.x >= GWIDTH || pos.y >= GHEIGHT)
		return false;

	// Check whether it is an empty space
	if (gBoard[pos.y][pos.x] != GNOTHING)
		return false;

	return true;
}

// Intent: clip algroithm
// Pre: The given float are not NULL
// Post: Return the biggest float between minimum and min(maximum, n)
float clip(float n, float minimun, float maximum)
{
	return max(minimun, std::min(n, maximum));
}

// Intent: Check whether two position is close enough，利用 call-by-referce 將計算得到的方向回傳
// Pre: 'cPos' represent the creature position, 'hPos' represent the hero position, 'dir' represents the direction
// Post: If the creature can see the hero, return true, vice versa
bool canSee(Position cPos, Position hPos, Position& dir)
{
	dir.x = (int)clip((float)(hPos.x - cPos.x), -1.f, 1.f);
	dir.y = (int)clip((float)(hPos.y - cPos.y), -1.f, 1.f);
	Position currentPos = cPos;

	while (currentPos != hPos)
	{
		// Add the position with the direction
		currentPos += dir;

		// Check if the current position is out of bounds
		if (currentPos.x < 0 || currentPos.y < 0)
			return false;

		// Get the character at the current position in the map
		char currentChar = gBoard[currentPos.y][currentPos.x];

		// Check if the current position is a wall
		if (currentChar == 'O')
			return false;
	}

	// If the creature can see the hero, return true
	return true;
}

// Intent: To get the board size for the other classes such as creatures classes and it derived classes
// Pre: None
// Post: Return the board size in a Position type
Position getBoardSize()
{
	return Position(GWIDTH, GHEIGHT);
}

// Intent: To know whether the zombie is adjacent to the hero or not
// Pre: None
// Post: If the creature is adjacent to the hero return true, vice versa
bool isAdjacent(Position cPos, Position hPos)
{
	// Check if the Hero is adjacent to the Zombie
	int dx = abs(cPos.x - hPos.x);
	int dy = abs(cPos.y - hPos.y);
	return (dx <= 1 && dy <= 1);
}

// Intent: To setup the board
// Pre: The 'rowN' parameter represents the row size of the board, the 'colN' parameter represents the col size of the board
// Post: Setup the board
void setUpBoard(int rowN, int colN)
{
	// Delete original data
	delete[] gBoard;

	for (int i = 0; i < gItems.size(); i++) 
	{
		delete gItems[i];
	}
	for (int i = 0; i < gCreatures.size(); i++) 
	{
		delete gCreatures[i];
	}

	gItems.clear();
	gCreatures.clear();

	// Allocate & init game board using 2d dynamic array
	gBoard = new char* [rowN];
	for (int i = 0; i < rowN; i++)
	{
		gBoard[i] = new char[colN];
		for (int j = 0; j < colN; j++)
		{
			gBoard[i][j] = GWALL;
		}
	}
	/*Please implement your code here*/
	int nothingCount;

	//create a 2d dynamic array to record the map is meet and innitialize the value is false
	used = new bool* [rowN];
	for (int i = 0; i < rowN; i++)
	{
		used[i] = new bool[colN];

		//innitialize the value is false
		for (int j = 0; j < colN; j++)
		{
			used[i][j] = false;
		}
	}

	//if all the characters can put in the map, break the loop, or continue
	while (1)
	{
		//set the exit position as nothing
		gBoard[rowN - 2][colN - 2] = gBoard[rowN - 3][colN - 2] = gBoard[rowN - 2][colN - 3] = GNOTHING;

		//generate the map by dfs
		generateMap(1, 1, 0);

		//fixed the wall 
		gBoard[1][0] = GWALL;

		//innitialize the variable to count the nothing
		nothingCount = 0;

		//innitialize used and count nothing
		for (int i = 0; i < rowN; i++)
		{
			for (int j = 0; j < colN; j++)
			{
				//innitialize used
				used[i][j] = false;

				//if the position is nothing, nothing count add 1
				if (gBoard[i][j] == GNOTHING) nothingCount += 1;
			}
		}

		//if nothing count is above all charactors(1 creature, 1 hero, 2 triggers), break the loop
		if (nothingCount >= totalCharactor) break;

		//if the blank is under 4, innitialize the map and generate the another in the next loop
		for (int i = 0; i < rowN; i++)
		{
			for (int j = 0; j < colN; j++)
			{
				gBoard[i][j] = GWALL;
			}
		}
	}

	//delete the used when the map has been generated
	delete[] used;

	// Setup for (random) position of all elements and implementation of game board using 2d dynamic array
	// Elements has to be randomly generated within canvas

	std::vector<std::vector<bool>> validFlags(GHEIGHT);
	// Iterates through the board
	for (int i = 0; i < GHEIGHT; i++)
	{
		validFlags[i].resize(GWIDTH);
		for (int j = 0; j < GWIDTH; j++)
		{
			// If the current board position is not a wall set the current element of vector to true
			validFlags[i][j] = gBoard[i][j] == GWALL ? false : true;
		}
	}

	// Generate valid random position
	auto getRandomPos = [&rowN, &colN]()
	{
		return Position((int)(rand() % colN), (int)(rand() % rowN));
	};

	auto getValidRandomPos = [&validFlags, &getRandomPos]()
	{
		while (true)
		{
			Position pos = getRandomPos();
			// If the generated position return the position,
			// but if it isn't valid, regenerate random position
			if (validFlags[pos.y][pos.x])
			{
				return pos;
			}
		}
	};

	// Set the generated random position to hero, and set the validFlags of the position to false
	Position hPos = getValidRandomPos();
	validFlags[hPos.y][hPos.x] = false;
	gHero.setPos(hPos);

	int area = GWIDTH * GHEIGHT;
	int cAmount = area * creatureDensity;
	//cout << "Next Level Creature Amount = " << cAmount << endl;

	// Set the generated random position to ghost, and set the validFlags of the position to false
	for (int i = 0; i < cAmount / 2; i++)
	{
		Position cPos = getValidRandomPos();
		validFlags[cPos.y][cPos.x] = false;
		Ghost* ghost = new Ghost('G', 10 * gameLevel, 10 * gameLevel, cPos);
		gCreatures.push_back(ghost);
	}

	// Set the generated random position to zombie, and set the validFlags of the position to false
	for (int i = 0; i < cAmount / 2; i++)
	{
		Position cPos = getValidRandomPos();
		validFlags[cPos.y][cPos.x] = false;
		Zombie* zombie = new Zombie('Z', 20 * gameLevel, 5 * gameLevel, cPos);
		gCreatures.push_back(zombie);
	}

	// Set the generated random position to triggers, and set the validFlags of the position to false
	for (int i = 0; i < cAmount; i++)
	{
		Position tPos = getValidRandomPos();
		Trigger* trigger = new Trigger(tPos);
		validFlags[tPos.y][tPos.x] = false;
		gItems.push_back(trigger);
	}

	// Set the generated random position to sword, and set the validFlags of the position to false
	Position sPos = getValidRandomPos();
	Sword* sword = new Sword(sPos);
	validFlags[sPos.y][sPos.x] = false;
	gItems.push_back(sword);

	Position pPos = getValidRandomPos();
	HealthPotion* healthPotion = new HealthPotion(pPos);
	validFlags[pPos.y][pPos.x] = false;
	gItems.push_back(healthPotion);

	// Set the generated random position to sword, and set the validFlags of the position to false
	Position bPos = getValidRandomPos();
	Cartridge* cartridge = new Cartridge(bPos);
	validFlags[bPos.y][bPos.x] = false;
	gItems.push_back(cartridge);
}

// Intent: To generate the map by dfs.
// Pre: The variable x, y, dir must have a value.
// Post: The function returns nothing.
void generateMap(int x, int y, int dir)
{
	//if the position is out of bounds or already used, return immediately
	if (x <= 0 || y <= 0 || x >= GHEIGHT - 1 || y >= GWIDTH - 1 || used[x][y]) return;

	//set the current position as empty and mark the position direction as used
	gBoard[x][y] = GNOTHING;
	used[x][y] = true;

	//if the opposite direction is valid and not used, set the position in the opposite direction as empty and mark the position direction as used 
	if (x >= 0 && y >= 0 && x <= GHEIGHT - 1 && y <= GWIDTH - 1)
	{
		gBoard[x + direction[offset(dir, 2)][0]][y + direction[offset(dir, 2)][1]] = GNOTHING;
		used[x + direction[offset(dir, 2)][0]][y + direction[offset(dir, 2)][1]] = true;
	}

	//randomly choose a starting direction for the next recursive calls
	int nextDir = rand() % 4;

	//recursively call generateMap on the positions in the next direction +0, +1, +2 and +3
	generateMap(x + direction[offset(nextDir, 0)][0] * 2, y + direction[offset(nextDir, 0)][1] * 2, offset(nextDir, 0));
	generateMap(x + direction[offset(nextDir, 1)][0] * 2, y + direction[offset(nextDir, 1)][1] * 2, offset(nextDir, 1));
	generateMap(x + direction[offset(nextDir, 2)][0] * 2, y + direction[offset(nextDir, 2)][1] * 2, offset(nextDir, 2));
	generateMap(x + direction[offset(nextDir, 3)][0] * 2, y + direction[offset(nextDir, 3)][1] * 2, offset(nextDir, 3));
}

// Intent: Draw the board
// Pre: All the creatures, trigers, hero have a valid position on the board
// Post: The bord is drawn
void draw()
{
	// Add the hero into the board
	// Setup and implementation of drawing board using 2d vector

	cout << "Level (" << gameLevel << " / " << maxLevel << ")\n";

	std::vector<std::vector<char>> drawBoard(GHEIGHT);

	for (int i = 0; i < GHEIGHT; i++)
	{
		drawBoard[i].resize(GWIDTH);
		for (int j = 0; j < GWIDTH; j++)
		{
			drawBoard[i][j] = gBoard[i][j];
		}
	}

	// Draw two triggers using for loop on drawBoard
	for (int i = 0; i < gItems.size(); i++)
	{
		Position t = gItems[i]->getPos();
		drawBoard[t.y][t.x] = gItems[i]->getIcon();
	}

	for (int i = 0; i < gCreatures.size(); i++)
	{
		Position c = gCreatures[i]->getPos();
		drawBoard[c.y][c.x] = gCreatures[i]->getIcon();
	}


	// Update the hero information
	Position h = gHero.getPos();
	drawBoard[h.y][h.x] = gHero.getIcon();

	// Draw the board
	for (int i = 0; i < GHEIGHT; i++)
	{
		for (int j = 0; j < GWIDTH; j++)
		{
			if (drawBoard[i][j] == GWALL)
			{
				std::cout << "\x1B[1;37m\u2588";
			}
			else
			{
				if (drawBoard[i][j] == 'G' || drawBoard[i][j] == 'Z' || drawBoard[i][j] == '!')std::cout << "\x1B[1;31m";
				else if (drawBoard[i][j] == 'H') std::cout << "\x1B[1;34m";
				else std::cout << "\x1B[1;32m";
				std::cout << drawBoard[i][j];
			}
		}
		std::cout << "\x1B[0m\n";
	}
}

//******************************************************************
// Intent: Output information
// Pre: All hero, triggers, creatures' variables are valid and not NULL
// Post: Print all the information
//==================================================================
void drawInfo(void)
//==================================================================
{
	std::cout << "The hero is level " << gHero.getLevel() << "(" << gHero.getExp() << "/" << gHero.getMaxExp() << " to level up)" << std::endl;
	std::cout << "The hero has " << gHero.getHP() << " hp" << std::endl;
	std::cout << "The hero has " << gHero.getPower() << " power" << std::endl;
	std::cout << "The hero has " << gHero.getBullet() << " bullet" << std::endl;
	std::cout << "Use wsad key to move Hero " << gHero.getIcon() << std::endl;
	std::cout << "Use space key to shot creature " << std::endl;
	std::cout << "Every time you step on a trigger T, the hero gets 10 exp." << std::endl;
	for (int i = 0; i < gCreatures.size(); i++)
	{
		Position dir;
		if (canSee(gCreatures[i]->getPos(), gHero.getPos(), dir))
		{
			std::cout << gCreatures[i]->getName() << " has spotted the Hero in the (" << dir.x << ", " << dir.y << ") direction\n";
			std::cout << gCreatures[i]->getName() << " health is " << gCreatures[i]->getHP() << "\n";
		}
	}
	std::cout << "(ESC) Exit (1) Save (2) Load" << std::endl;
}

//******************************************************************
// Intent: Update the board state
// Pre: 'key[]' parameter represents an array used to manage the state of keyboard input.
// Post: The board state is updated
//==================================================================
void update(bool key[])
//==================================================================
{
	if (gameLevel == maxLevel)
	{
		for (int i = 0; i < gCreatures.size(); i++)
		{
			if (gCreatures[i]->getIcon() != 'O')
			{
				break;
			}

			else if (gCreatures.size() == 0 || (i == gCreatures.size() - 1))
			{
				isWin = true;
				break;
			}
		}
	}

	if (isWin)
	{
		cout << "YOU WIN\n";
		return;
	}

	if (gHero.getHP() == 0)
	{
		cout << "YOU LOSE !\n";
		isLose = true;
		return;
	}

	bool nextLevelFlag = false;

	// If all the creatures on the current level is killed, upgrade to the next level
	for (int i = 0; i < gCreatures.size(); i++)
	{
		if (gCreatures[i]->getIcon() != 'O')
		{
			break;
		}
		else if ((i == gCreatures.size() - 1 && gameLevel <= maxLevel) || gCreatures.size() == 0)
		{
			nextLevel();
			nextLevelFlag = true;
			break;
		}
	}

	if (nextLevelFlag)
	{
		return;
	}

	// 清除版面
	system("CLS");

	Position delta;

	// 是否有input
	bool hasInput = false;
	if (key[ValidInput::EW]) // If the input is 'w', update the delta to go up and set hasInput to true
	{
		delta -= Position(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::ES])	// If the input is 's', update the delta to go down and set hasInput to true 
	{
		delta += Position(0, 1);
		hasInput = true;
	}
	else if (key[ValidInput::EA])	// If the input is 'a', update the delta to go left and set hasInput to true
	{
		delta = delta - Position(1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ED])	// If the input is 'd', update the delta to go right and set hasInput to true
	{
		delta = delta + Position(1, 0);
		hasInput = true;
	}
	else if (key[ValidInput::ESPACE])	// If the input is 'd', update the delta to go right and set hasInput to true
	{
		shot();
	}
	else if (key[ValidInput::ESave])	// If the input is '1', update the delta to go right and set hasInput to true
	{
		draw();	// Draw the board
		drawInfo();	// Draw the information
		return;
	}
	else if (key[ValidInput::ELoad])	// If the input is '2', update the delta to go right and set hasInput to true
	{
		draw();	// Draw the board
		drawInfo();	// Draw the information
		return;
	}
	else	// Check if none of those conditions are met
	{
		bool allInvalid = true;	// Set allInvalid to true (flag variable)
		// Iterates through keys
		for (int i = 0; i < ValidInput::INVALID; i++)
		{
			if (key[i]) // If i-th key element is true, set allInvalid to false and break
			{
				allInvalid = false;
				break;
			}
		}
		if (allInvalid)	// If the input is invalid, print "invalid input"
			std::cout << "Invalid Input\n";
	}

	// If the input is a move input, update the hero position by calling move methods with delta as the parameter of the new position
	if (hasInput) 
	{
		gHero.move(delta);
	}

	// Manipulate update of the items using for loop
	for (int i = 0; i < gItems.size(); i++)
	{
		// Check whether the item is not trigger, and the appearance is less or equal to the game level + 1 
		// and has the same position with the hero
		if (gItems[i]->update(gHero) && gItems[i]->getAppearance() <= gameLevel + 1)
		{
			gItems[i]->setAppearance(gItems[i]->getAppearance() + 1);

			// If the item appearance in the current level is bigger than the game level + 1, remove the item
			if (gItems[i]->getAppearance() > gameLevel + 1)
			{
				gItems[i]->remove();
			}
			else if(gItems[i]->getIcon() != 'T')
			{
				// Generate new valid position and update the appearance
				while (true)
				{
					Position newPos;
					newPos.x = rand() % (GWIDTH - 1);
					newPos.y = rand() & (GHEIGHT - 1);

					if (isPositionValid(newPos))
					{
						gItems[i]->setPos(newPos);
						break;
					}
				}
			}
		}
	}

	// Manipulate update of two creatures using while loop
	for (int i = 0; i < gCreatures.size(); i++)
	{
		if (gCreatures[i]->getHP() > 0)
		{
			gCreatures[i]->update(gHero);
		}
	}

	draw();	// Draw the board
	drawInfo();	// Draw the information
}

// Intent: Set up for the next level.
// Pre: All the creatures in the current level are dead.
// Post: Move to the next level.
void nextLevel()
{
	// Set the new height and width by adding the height and width with height and width divided by 2
	GHEIGHT = (GHEIGHT / 2) + GHEIGHT;
	GWIDTH = (GWIDTH / 2) + GWIDTH;

	// Increment the level, and increment the creature densitiy by 0.01
	gameLevel++;
	creatureDensity += 0.01;
	
	// Set up the board with the new height and width
	setUpBoard(GHEIGHT, GWIDTH);
}

// Intent: Shot the bullet.
// Pre: Hero is valid and not NULL.
// Post: The hero shot the bullet.
void shot()
{
	// If the Hero's bullet is zero, return
	if (gHero.getBullet() == 0) 
		return;

	// Get the hero position
	Position hPosition = gHero.getPos();
	int i, x, y;

	x = hPosition.x;
	y = hPosition.y;

	gHero.setBullet(gHero.getBullet() - 1);

	for (i = hPosition.x + 1; i < GWIDTH; i++) 
	{
		if (gBoard[y][x] == GWALL)
			break;
		else if (shotCreature(i, y)) 
			break;
	}
	for (i = hPosition.x - 1; 0 <= i; i--) 
	{
		if (gBoard[y][x] == GWALL) 
			break;
		else if (shotCreature(i, y)) 
			break;
	}
	for (i = hPosition.y + 1; i < GHEIGHT; i++) 
	{
		if (gBoard[y][x] == GWALL) 
			break;
		else if (shotCreature(x, i)) 
			break;
	}
	for (i = hPosition.y - 1; 0 <= i; i--) 
	{
		if (gBoard[y][x] == GWALL) 
			break;
		else if (shotCreature(x, i)) 
			break;
	}
}

bool shotCreature(int x, int y) {
	Position position(x, y);
	for (int i = 0; i < gCreatures.size(); i++) {
		if (gCreatures[i]->getPos() == position) {
			gCreatures[i]->setHP(gCreatures[i]->getHP() - gHero.getPower());
			if (gCreatures[i] ->getHP() <= 0)
			{
				gCreatures[i]->remove();
			}
			return true;
		}
	}
	return false;
}

//******************************************************************
// Intent: Save the map status
// Pre: All the related class and variables are not NULL
// Post: The current game condition is saved into a file
//==================================================================
void saveMap()
{
	// Take the user input about the save file name
	system("CLS");
	std::cout << "Input file name for saving or Exit to leave saving." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)	// If the user input is "Exit" then cancel 
		return;

	std::ofstream oStream(input + ".txt");	// Create the file
	oStream << GWIDTH << " " << GHEIGHT << std::endl;	// Output the width and height to the file

	// Print the board to the file
	for (int i = 0; i < GHEIGHT; i++)
	{
		for (int j = 0; j < GWIDTH; j++)
		{
			oStream << gBoard[i][j];
		}
		oStream << std::endl;
	}
	oStream << std::endl;

	// Print all the Hero, Creatures, Triggers, and Items data to the file
	oStream << gHero.getPos() << " " << gHero.getHP() << " " << gHero.getLevel() << " " << gHero.getExp() << " "
		<< gHero.getMaxExp() << " " << gHero.getPower() << " " << gHero.getBullet() << std::endl;

	oStream << gCreatures.size() << std::endl;
	for (int i = 0; i < gCreatures.size(); i++)
	{
		if (gCreatures[i]->getIcon() != '!')oStream << gCreatures[i]->getIcon() << " " << gCreatures[i]->getPos() << " " << gCreatures[i]->getHP() << " " << gCreatures[i]->getPower() << std::endl;
		else
		{
			char tmpIcon = ' ';
			if (typeid(*gCreatures[i]) == typeid(Ghost)) tmpIcon = 'G';
			else if (typeid(*gCreatures[i]) == typeid(Zombie))tmpIcon = 'Z';
			oStream << tmpIcon << " " << gCreatures[i]->getPos() << " " << gCreatures[i]->getHP() << " " << gCreatures[i]->getPower() << std::endl;
		}
	}

	oStream << gItems.size() << std::endl;
	for (int i = 0; i < gItems.size(); i++)
	{
		oStream << gItems[i]->getIcon() << " " << gItems[i]->getPos() << std::endl;
	}

	oStream << gameLevel << endl;
	oStream << maxLevel << endl;
	oStream.close();	// Close the file
}

//******************************************************************
// Intent: Load the map status
// Pre: None
// Post: Update the map status according to the given save file
//==================================================================
void loadMap()
{
	// Load from file and reset the dungeon
	system("CLS");
	std::cout << "Input file name for loading or Exit to leave loading." << std::endl;
	std::cout << "Input: ";
	std::string input;
	std::cin >> input;
	if (input.compare("Exit") == 0)	// If the user input is "Exit", cancel
		return;

	// Open the file
	std::ifstream iStream(input + ".txt");
	if (!iStream.is_open())
		return;	// If the file is not opened, return

	// Reset the dungeon
	for (int i = 0; i < GHEIGHT; i++)
	{
		delete[] gBoard[i];
	}
	delete[] gBoard;

	// Delete all creatures and triggers
	for (int i = 0; i < gCreatures.size(); i++)
	{
		delete gCreatures[i];
	}
	gCreatures.clear();

	for (int i = 0; i < gItems.size(); i++)
	{
		delete gItems[i];
	}
	gItems.clear();

	iStream >> GWIDTH >> GHEIGHT;	// Take the size of the board

	char _c;
	iStream.get(_c);

	// Update the board according to the file
	gBoard = new char* [GHEIGHT];
	for (int i = 0; i < GHEIGHT; i++)
	{
		gBoard[i] = new char[GWIDTH];
		for (int j = 0; j < GWIDTH; j++)
		{
			iStream.get(gBoard[i][j]);
		}
		iStream.get(_c);
	}

	// Take the hero's stat and update it
	int posX, posY;
	int hp, level, exp, maxExp, power, bullet;
	iStream >> posX >> posY >> hp >> level >> exp >> maxExp >> power >> bullet;

	gHero.setPos(posX, posY);
	gHero.setHP(hp);
	gHero.setLevel(level);
	gHero.setExp(exp);
	gHero.setMaxExp(maxExp);
	gHero.setPower(power);
	gHero.setBullet(bullet);

	// Take the Creatures' stats and update it
	int creatureN;
	iStream >> creatureN;
	for (int i = 0; i < creatureN; i++)
	{
		char icon;
		Position cPos;
		iStream >> icon >> cPos >> hp >> power;
		if (icon == 'G')
		{
			Ghost* ghost = new Ghost(icon, hp, power, cPos);
			gCreatures.push_back(ghost);
		}
		else if (icon == 'Z')
		{
			Zombie* zombie = new Zombie(icon, hp, power, cPos);
			gCreatures.push_back(zombie);
		}
	}

	// Take the items' position, and update it to the board
	int itemN;
	iStream >> itemN;
	for (int i = 0; i < itemN; i++)
	{
		char icon;
		Position iPos;
		iStream >> icon >> iPos;
		// If the icon is 'T' it means the item is a trigger, so appends new trigger with the given position to the vector
		if (icon == 'T')
		{
			Trigger* trigger = new Trigger(iPos);
			gItems.push_back(trigger);
		}
		// If the icon is 'S' it means the item is a sword, so appends new sword with the given position to the vector
		else if (icon == 'S')
		{
			Sword* sword = new Sword(iPos);
			gItems.push_back(sword);
		}
		// If the icon is 'P' it means the item is a HealthPotion, so appends new HealthPotion with the given position to the vector
		else if (icon == 'P')
		{
			HealthPotion* healthPotion = new HealthPotion(iPos);
			gItems.push_back(healthPotion);
		}
		// If the icon is 'B' it means the item is a Cartridge, so appends new Cartridge with the given position to the vector
		else if (icon == 'B')
		{
			Cartridge* cartridge = new Cartridge(iPos);
			gItems.push_back(cartridge);
		}
	}

	iStream >> gameLevel;

	iStream >> maxLevel;

	iStream.close();
}

