#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
// #include "mzegen.h"
#include "fileIO.h"

using namespace std;

int steps = 0;
const int size = 31;	
struct zone {
	int ix, iy;
	int jx, jy;
};

class maze{
private:
  int mazeSize = size;
  bool maze[size][size];
  int nodes[size][size];  
  // Cursor
  int xpos = 6;
  int ypos = 6;

  struct position
  {
	  int x, y;
	  int direction;
	};

	position start;
	position finish;
	position cursor;

	void setStart(){
		start.y = 0;
		start.x = 0;
		while(maze[start.x][start.y] != 0){
			start.x = rand() % mazeSize;
			start.y = rand() % mazeSize;
		}
		cursor.x = start.x;
		cursor.y = start.y;
	}
	void setFinish(){
		finish.x = 0;
		finish.y = 0;
		// int axis = rand() % 1;
		int axis = 0;
		if (axis == 0){
			while(maze[finish.x][1] == 1){
				finish.x = rand() % mazeSize;
			}
		}
		else{
			while(maze[1][finish.y] == 1){
				finish.y = rand() % mazeSize;
			}
		}
	}
	bool moveUP(){
		if(maze[cursor.x][cursor.y-1] == 0){
			cursor.y--;
			return 0;
		}else{
			return 1;
		}
	}
	bool moveDOWN(){
		if(maze[cursor.x][cursor.y+1] == 0){
			cursor.y = cursor.y + 1;
			return 0;
		}else{
			return 1;
		}
	}
	bool moveLEFT(){
		if(maze[cursor.x-1][cursor.y] == 0){
			cursor.x--;
			return 0;
		}else{
			return 1;
		}
	}
	bool moveRIGHT(){
		if(maze[cursor.x+1][cursor.y] == 0){
			cursor.x++;
			return 0;
		}else{
			return 1;
		}
	}

	void wall(zone &startzone, int divx, int divy){
		// Generate Horizontal and Vertical Walls
		for(int i = startzone.ix;i <  startzone.jx+1; i++){
			maze[i][divy] = 1;
		}
		for(int j = startzone.iy; j < startzone.jy+1; j++){
			maze[divx][j] = 1;
		}

		// Generate Passthrough
		int ypass, xpass;
		
		// Wall Selector
		int solid= rand() % 3 + 0;
		// Wall Passages
		int passage;
		if(solid != 0){
			passage = divx;
			while(passage % 2 == 0){
				passage = rand() % (divy - startzone.iy) + startzone.iy;
			}
			maze[divx][passage] = 0;
		}
		if(solid != 1){
			passage = divy;
			while(passage % 2 == 0){
				passage = rand() % (startzone.jx-1 - divx+1) + divx+1;
			}
			maze[passage][divy] = 0;
		}
		if(solid != 2){
			passage = divx;
			while(passage % 2 == 0){
				passage = rand() % (startzone.jy-1 - divy+1) + divy+1;
			}
			maze[divx][passage] = 0;
		}
		if(solid != 3){
			passage = divy;
			while(passage % 2 == 0){
				passage = rand() % (divx - startzone.ix) + startzone.ix;
			}
			maze[passage][divy] = 0;
		}
	}

	void scanMaze(){
		for (int y = 0; y < mazeSize; y++) {
			for (int x = 0; x < mazeSize; x++) {
				if(maze[x][y] == 0){
					int paths = 0;
					if(maze[x+1][y] == 0){
						paths++;
					}
					if(maze[x-1][y] == 0){
						paths++;
					}
					if(maze[x][y+1] == 0){
						paths++;
					}
					if(maze[x][y-1] == 0){
						paths++;
					}
					nodes[x][y] = paths;
				}
			}
		}

	}
	bool divzone(zone &startzone){
		// Check Zone Size
		if(startzone.jx - startzone.ix < 3 || startzone.jy - startzone.iy < 3){
			return true;
		}

		int xdiv = 1;
		int ydiv = 1;
		// Split
		if(startzone.jx - startzone.ix > 2){
			while(xdiv % 2 == 1){
				xdiv = rand() % (startzone.jx-startzone.ix-1)+(startzone.ix+1);
			}	
		}
		if(startzone.jy - startzone.iy > 2){
			while(ydiv % 2 == 1){
				ydiv = rand() % (startzone.jy-startzone.iy-1)+(startzone.iy+1);
			}
		}
		wall(startzone, xdiv, ydiv);

		// Assign Zones
		zone zone1, zone2, zone3, zone4;
		//Zone 1
		zone1.iy = startzone.iy;
		zone1.ix = startzone.ix;
		zone1.jy = ydiv;
		zone1.jx = xdiv;
		// Zone 2
		zone2.iy = startzone.iy;
		zone2.ix = xdiv;
		zone2.jy = ydiv;
		zone2.jx = startzone.jx;
		// Zone 3
		zone3.iy = ydiv;
		zone3.ix = startzone.ix;
		zone3.jy = startzone.jy;
		zone3.jx = xdiv;
		// Zone 4
		zone4.iy = ydiv;
		zone4.ix = xdiv;
		zone4.jy = startzone.jy;
		zone4.jx = startzone.jx;

		// Split Zone
		divzone(zone1);
		divzone(zone2);
		divzone(zone3);
		divzone(zone4);
		
		return false;
	}

  public:
	void printNodes(){
		for (int y = 0; y < mazeSize; y++) {
			for (int x = 0; x < mazeSize; x++) {
				cout << nodes[x][y] << ' ';
			}
			cout << endl;
		}
	}
	void init(int mazeSize){
		for(int i = 0; i <= size; i++){
			for(int j = 0; j <= size; j++){
				maze[i][j] = 0;
			}
		}

		// Wall Vertical and Horizontal
		for (int i = 0; i <= size; i++){
			// Vertical
			maze[0][i] = 1;
			maze[size - 1][i] = 1;
			// Horizontal
			maze[i][0] = 1;
			maze[i][size -1] = 1;
		}
	}
	void print(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				// Cursor Location
				if(j == cursor.x && i == cursor.y){
					cout << 'O' << " ";
				}
				else {
					if(j == finish.x && i == finish.y){
						cout << '%' << ' ';
					} else{ // Print Walls
						if (maze[j][i] == 0){
							cout << ' ' << ' ';						
						}
						else{
							cout << 'X' << ' ';
						}
					}
				}
			}
			cout << endl;
		}
	}

	void movePRight(){
		if (cursor.direction == 0){
			cursor.direction = 1;
			moveRIGHT();
		}
		else if(cursor.direction == 1){
			cursor.direction = 2;
			moveDOWN();
		}
		else if(cursor.direction == 2){
			cursor.direction = 3;
			moveLEFT();
		}
		else if(cursor.direction == 3){
			cursor.direction = 0;
			moveUP();
		}
	}
	

	bool moveFWD(){
		if (cursor.direction == 0){
			if(moveUP() == 1){
				return 1;
			}else{
				return 0;
			}
		}
		else if(cursor.direction == 1){
			if(moveRIGHT() == 1){
				return 1;
			}else{
				return 0;
			}
		}
		else if(cursor.direction == 2){
			if(moveDOWN() == 1){
				return 1;
			}else{
				return 0;
			}
		}
		else if(cursor.direction == 3){
			if(moveLEFT() == 1){
				return 1;
			}else{
				return 0;
			}
		}
		return 0;
	}
	void turnLEFT(){
		cursor.direction--;
		if(cursor.direction < 0){
			cursor.direction = 3;
		}
	}
	bool navigate(){
		steps++;
		// Winning Condition
		if(cursor.x == finish.x && cursor.y == finish.y ){
			return 0;
		}
		if(cursor.x == finish.x-1 && cursor.y == finish.y ){
			return 0;
		}
		if(cursor.x == finish.x+1 && cursor.y == finish.y ){
			return 0;
		}
		if(cursor.x == finish.x && cursor.y == finish.y+1 ){
			return 0;
		}
		if(cursor.x == finish.x && cursor.y == finish.y-1 ){
			return 0;
		}
		// Draw Maze
		// print();

		// Sleep(200);
		// cout << "cursor.direction = " << cursor.direction << endl;
		// cin.get();
		// Sleep(20);
		system("cls");
		// START
		bool leftCheck = 1;

		if (cursor.direction == 0){
			if(moveLEFT() == 0){
				leftCheck = 0;
				turnLEFT();
			}
		}
		else if(cursor.direction == 1){
			if(moveUP() == 0){
				leftCheck = 0;		
				turnLEFT();						
			}
		}
		else if(cursor.direction == 2){
			if(moveRIGHT() == 0){
				leftCheck = 0;		
				turnLEFT();						
			}
		} // TURN LEFT
		else if(cursor.direction == 3){
			if(moveDOWN() == 0){
				leftCheck = 0;		
				turnLEFT();								
			}
		}
		// TURN RIGHT
		if (leftCheck == 1 && moveFWD() != 0){
			movePRight();
		}
		navigate();
	}

	void smartSolve(){
		// Init Node Array
		for (int y = 0; y < mazeSize; y++) {
			for (int x = 0; x < mazeSize; x++) {
				nodes[x][y] = 0;
			}
		}
		// 
		scanMaze();
	}

	void solve(){
		// Init Path Array
		bool path[mazeSize][mazeSize];
		for (int i = 0; i <= size; i++) {
			for (int j = 0; j <= size; j++) {
				path[i][j] = 0;
			}
		}
		cursor.direction = 0;
		navigate();
	}
	int gen(){
		// Random Seed
		srand(time(NULL));
		// Check Maze Dimensions
		if(size % 2 == 0){
			system("cls");
			cerr << "Maze Size Error" << endl;
			cerr << "Size +1" << endl;

		}

		zone startzone;
		startzone.ix = 1;
		startzone.iy = 1;
		startzone.jx = size-2;
		startzone.jy = size-2;

		divzone(startzone);
		setStart();
		setFinish();
	}
	void savetxt(){
		ofstream file("maze.txt");
		for (int index = 0; index < size; index++) {
			for (int Y = 0; Y < size; Y++) {
				file << maze[index][Y]<< ' ';
			}
			file << endl;
		}
	}
};

int main(void){
	// New Maze Class
	maze maze;
	// Set Window Size


	maze.init(31);
	maze.gen();
	// maze.print();
	// maze.save();
	// maze.savetxt();
	maze.smartSolve();
	maze.print();
	maze.printNodes();
	cout << "Steps: " << steps<< endl;
	
	cin.get();
	return 0;
}