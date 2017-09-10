#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
// #include "mzegen.h"

using namespace std;

const int size = 25;
struct zone {
	int ix, iy;
	int jx, jy;
};

class maze{
private:
	bool maze[size][size];
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
		cout << "solid > " << solid<< endl;
		// Wall Passages
		int passage;
		if(solid != 0){
			passage = divx;
			while(passage % 2 == 0){
				passage = rand() % (divy - startzone.iy) + startzone.iy;
				cout <<"wall > "<< "1"<< endl;
			}
			maze[divx][passage] = 0;
		}
		if(solid != 1){
			passage = divy;
			while(passage % 2 == 0){
				passage = rand() % (startzone.jx-1 - divx+1) + divx+1;
				cout <<"wall > "<< "2"<< endl;
			}
			maze[passage][divy] = 0;
		}
		if(solid != 2){
			passage = divx;
			while(passage % 2 == 0){
				passage = rand() % (startzone.jy-1 - divy+1) + divy+1;
				cout <<"wall > "<< "3"<< endl;				
			}
			maze[divx][passage] = 0;
		}
		if(solid != 3){
			passage = divy;
			while(passage % 2 == 0){
				passage = rand() % (divx - startzone.ix) + startzone.ix;
				cout <<"wall > "<< "4"<< endl;				
			}
			maze[passage][divy] = 0;
		}
		cout << endl;
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
				cout << xdiv << ' ' << endl;
			}	
		}
		if(startzone.jy - startzone.iy > 2){
			while(ydiv % 2 == 1){
				ydiv = rand() % (startzone.jy-startzone.iy-1)+(startzone.iy+1);
				cout << ydiv << ' ' << endl;				
			}
		}
		cout << "YDIV : " << ydiv<<endl;
		cout << "XDIV : " << xdiv << endl;
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
		print();
		// cin.get();
		Sleep(300);

		// Split Zone
		divzone(zone1);
		divzone(zone2);
		divzone(zone3);
		divzone(zone4);
		
		return false;
	}

  public:
	void init(){
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
		system("cls");
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if (maze[j][i] == 0){
					cout << ' ' << ' ';
				}
				else{
					cout << 'X' << ' ';
				}
				// cout << maze[j][i]<< ' ';
			}
			cout << endl;
		}
	}
	int gen(){
		// Check Maze Dimensions
		if(size % 2 == 0){
			system("cls");
			cerr << "Maze Size Error" << endl;
			return 1;
		}

		zone startzone;
		startzone.ix = 1;
		startzone.iy = 1;
		startzone.jx = size-2;
		startzone.jy = size-2;

		divzone(startzone);
		cout << "FINISHED" << endl;
	}
	void save(){

	}
};

int main(void){
	maze maze;

	srand(time(NULL));
	maze.init();
	maze.gen();
	maze.print();
	
	cin.get();
	return 0;
}