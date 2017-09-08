#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int size = 30;
struct zone {
	int ix, iy;
	int jx, jy;
};

class maze{
private:
	bool maze[size][size];
	bool check = false;

	void wall(zone &startzone, int divx, int divy){
		bool walls[4] = {1, 1, 1, 1};
=
		// Generate Horizontal and Vertical Walls

		for(int i = startzone.ix;i <  startzone.jx+1; i++){
			maze[i][divy] = 1;
		}
		for(int j = startzone.iy; j < startzone.jy+1; j++){
			maze[divx][j] = 1;
		}

		// Generate Passthrough
		int ypass, xpass;
		
		// X pass
		int iteration1= rand() % 2 + 1;		
		int iteration2= rand() % 2 + 1;
		for (int i = 0; i <= iteration1;i++){
			xpass = rand() % (startzone.jx - startzone.ix) + startzone.ix;
			if (xpass != divy){
			maze[xpass][divy] = 0;	
			}
		}

		// 
		for (int i = 0; i <= iteration2;i++){
			ypass = rand() % (startzone.jy - startzone.iy) + startzone.iy;	
			if (ypass != divx){				
				maze[divx][ypass] = 0;			
			}
		}
	}
	bool divzone(zone &startzone){
		if(startzone.jx - startzone.ix < 3 || startzone.jy - startzone.iy < 3){
			return true;
		}

		// Split
		int xdiv = rand() % (startzone.jx-startzone.ix-1)+(startzone.ix+1);
		int ydiv = rand() % (startzone.jy-startzone.iy-1)+(startzone.iy+1);

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
		cin.get();

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
	}
	void print(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				cout << maze[j][i]<< ' ';
			}
			cout << endl;
		}
	}
	void gen(){
		zone startzone;
		startzone.ix = 0;
		startzone.iy = 0;
		startzone.jx = size-1;
		startzone.jy = size-1;

		divzone(startzone);
		cout << "FINISHED" << endl;
	}
} maze;

int main(void){
	srand(time(NULL));
	maze.init();
	maze.gen();
	maze.print();
	
	cin.get();
	return 0;
}