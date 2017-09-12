#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
// #include "mzegen.h"
#include "fileIO.h"

using namespace std;

const int size = 35;	
struct zone {
	int ix, iy;
	int jx, jy;
};

class maze{
private:
	int mazeSize = size;	
	bool maze[size][size];
	// Cursor
	int xpos = 6;
	int ypos = 6;

	struct position{
		int x, y;
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
	}

	void moveUP(){
		if(cursor.x-1 == 0){
			cursor.x - 1;
		}
	}
	void moveDOWN(){
		if(cursor.x+1 == 0){
			cursor.x + 1;
		}
	}
	void moveLEFT(){
		if(cursor.y-1 == 0){
			cursor.y - 1;
		}
	}
	void moveRIGHT(){
		if(cursor.y+1 == 0){
			cursor.y + 1;
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
				if(j == start.x && i == start.y){
					cout << 'O' << " ";
				} else{ // Print Walls
						if (maze[j][i] == 0){
							cout << ' ' << ' ';						
					}
					else{
						cout << 'X' << ' ';
					}
				}
			}
			cout << endl;
		}
	}
	void solve(){
		// Init Path Array
		bool path[size][size];
		for (int i = 0; i <= size; i++) {
			for (int j = 0; j <= size; j++) {
				path[i][j] = 0;
			}
		}

		
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
	maze.print();
	// maze.save();
	// maze.savetxt();
	maze.solve();

	cin.get();
	return 0;
}