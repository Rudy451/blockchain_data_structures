#include <iostream>
#include <vector>
#include <string>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

// SETUP STUFF

using std::cin; using std::cout; using std::endl; using std::string; using std::copy; using std::begin; using std::end; using std::vector; using std::find; using std::max; using std::max_element; using std::min; using std::vector; using std::runtime_error;

int graph[5][5] = {{1, 0, 1, 1, 1},
                   {1, 1, 1, 1, 1},
                   {0, 1, 0, 1, 1},
                   {0, 1, 0, 1, 0},
                   {0, 1, 0, 1, 0}};

vector<vector<int>> goal{{4, 1}, {4, 3}};

vector<vector<int>> path;

int row_start = -1;

int bfs(int i = 0, int j = 0){

        if(((i == goal[0][0] && j == goal[0][1]) || (i == goal[1][0] && j == goal[1][1])) && (graph[i-1][j] != 0 || graph[i][j-1] != 0)){
             
		cout << "Solution Found: " << i << ", " << j << endl;
                return 0;
	
	} else if((i == (sizeof(graph[i]) / (sizeof(int) - 1))) && (j == (sizeof(graph[i]) / (sizeof(int) - 1)))){

		cout << "No Solution" << endl;
                return 0;

        } else if((graph[i][j] == 1) && ((i == 0 && j == 0) || (graph[i - 1][j] == 1) || ((j > 0) && (graph[i][j - 1] == 1)))){

		cout << i << ", " << j << endl;
		path.push_back({i, j});

		if((graph[i + 1][j] == 1) && (row_start == -1)){

			row_start = j;

		}
 
	}

	if(j < (sizeof(graph[i]) / sizeof(int))){
			
		bfs(i, j + 1);

	} else if(row_start != -1){
				
		j = row_start;
		row_start = 0;
		bfs(i + 1, j);

        }
}

int main(){

	bfs();

}
