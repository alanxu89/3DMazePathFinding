/*  The Prince of Persia has been thrown onto the top level of Jaffar's underground labyrinth. The labyrinth consists of h levels strictly
on top of each other. Each level is split into m by n areas. Some areas have columns that support ceiling, some areas are free. The Prince
can move only to free areas. To move to the level below the Prince can break the floor underneath him and jump down if there is no column 
underneath. Every move takes the Prince 5 seconds. A Princess is waiting for the Prince at the lowest level. Write a program that will help
the Prince to save the Princess as fast as possible by finding the shortest path between them and outputting time it took the Prince to 
find the Princess. The structure of the labyrinth is given bellow. The Prince’s location is marked with '1', the Princess’s location is 
marked with '2'. ‘.’ - marks a free spot and ‘o’ marks a column.
*/

/*Given a grid, return a solution object.
 *
 * A solution object is a struct that connntains the following.
 * = amountOfTime == an int stating how much time it took to complete the maze.
 * = directions == an array of Directions that dictates the path through the maze.
 * = isPossible == a boolean that says *if* there is a path through the maze.
 *
 * A Direction is an enum with six states {EAST, WEST, SOUTH,
 * NORTH, UP, DOWN} you can access this via Problem5::Direction::NORTH etc.
 *
 * A ThreeDimCharArray is a std::vector<std::vector<std::vector>>>.
 */
 
 
#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

enum Direction { EAST, WEST, SOUTH, NORTH, UP, DOWN };


struct solution{
    int amountOfTime;
    bool isPossible;
    vector<Direction> directions;
};


int main() {
    std::vector<std::vector<std::vector<char>>> simple_grid=
            {
                {
                    { '1', '.', 'o','o', '.', '.' },
                    { 'o', '.', '.','.', 'o', '.' },
                    { '.', 'o', '.','o', '.', 'o' },
                    { 'o', '.', 'o','o', '.', '.' },
                    { 'o', '.', '.','.', 'o', '.' },
                    { '.', 'o', '.','o', '.', 'o' }

                },
                {
                    { 'o', 'o', '.','o', 'o', '.' },
                    { '.', 'o', '.','.', '.', '.' },
                    { 'o', '.', '.','.', 'o', 'o' },
                    { '.', 'o', '.','.', '.', '.' },
                    { 'o', 'o', 'o','.', 'o', 'o' },
                    { '.', '.', 'o','.', '.', 'o' }

                },
                {
                    { 'o', 'o', '.','o', 'o', 'o' },
                    { '.', '.', 'o','.', '.', 'o' },
                    { 'o', 'o', 'o','.', '.', 'o' },
                    { 'o', '.', 'o','o', '.', '.' },
                    { '.', 'o', '.','.', '.', '.' },
                    { '.', '.', '.','o', 'o', '.' }

                },
                {
                    { 'o', '.', 'o','o', '.', '.' },
                    { 'o', 'o', '.','.', 'o', '.' },
                    { 'o', '.', 'o','.', '.', '.' },
                    { '.', 'o', '.','o', '.', 'o' },
                    { '.', '.', 'o','o', '.', '.' },
                    { 'o', 'o', 'o','.', 'o', '.' }

                },
                {
                    { 'o', 'o', 'o','.', 'o', '.' },
                    { 'o', 'o', '.','.', '.', 'o' },
                    { '.', '.', '.','o', '.', '.' },
                    { 'o', 'o', 'o','.', 'o', '.' },
                    { '.', '.', '.','.', '.', 'o' },
                    { '.', 'o', '.','o', 'o', 'o' }
                },
                {
                    { 'o', '.', '.','.', 'o', 'o' },
                    { '.', 'o', 'o','o', '.', '.' },
                    { '.', '.', '.','o', 'o', 'o' },
                    { '.', 'o', 'o','.', 'o', 'o' },
                    { 'o', 'o', 'o','.', '.', 'o' },
                    { 'o', 'o', 'o','o', '.', '.' }
                },
                {
                    { 'o', '.', 'o','.', 'o', '.' },
                    { 'o', 'o', '.','o', 'o', 'o' },
                    { '.', '.', '.','o', '.', 'o' },
                    { '.', 'o', 'o','.', 'o', '.' },
                    { 'o', '.', '.','.', 'o', 'o' },
                    { 'o', '.', 'o','o', '.', 'o' }
                },
                {
                    { '.', 'o', '.','.', 'o', 'o' },
                    { '.', 'o', 'o','.', '.', 'o' },
                    { 'o', '.', 'o','o', 'o', '.' },
                    { '.', 'o', '.','o', '.', 'o' },
                    { '.', '.', '.','.', '.', '.' },
                    { 'o', '.', 'o','o', '.', '.' }
                },
                {
                    { 'o', '.', 'o','o', 'o', '.' },
                    { 'o', 'o', '.','o', 'o', 'o' },
                    { 'o', 'o', '.','.', '.', '.' },
                    { '.', 'o', 'o','.', '.', 'o' },
                    { '.', '.', 'o','o', 'o', '.' },
                    { 'o', 'o', 'o','.', 'o', 'o' },
                    
                },
                {
                    { 'o', 'o', '.','o', 'o', 'o' },
                    { '.', '.', '.','o', '.', 'o' },
                    { 'o', '.', 'o','.', 'o', 'o' },
                    { '.', '.', 'o','o', '.', '.' },
                    { 'o', 'o', '.','.', '.', 'o' },
                    { '.', 'o', 'o','o', '.', '2' },
                    
                },

            };
    
    const int h= (int) simple_grid.size();
    const int m= (int) simple_grid[0].size();
    const int n= (int) simple_grid[0][0].size();
    const int V=m*n*h;
    
    solution solLabyrinth;
    std::vector<std::list<int>> adjList(V);
    
    for (int i=0; i<h; i++) {
        for (int j=0; j<m; j++) {
            for (int k=0; k<n; k++) {
                if (simple_grid[i][j][k]!= 'o'){
                    
                    if (i>0 && simple_grid[i-1][j][k]!= 'o')
                        adjList[i*m*n+j*n+k].push_back((i-1)*m*n+j*n+k);
                    
                    if (j>0 && simple_grid[i][j-1][k]!= 'o')
                        adjList[i*m*n+j*n+k].push_back(i*m*n+(j-1)*n+k);
                    
                    if (k>0 && simple_grid[i][j][k-1]!= 'o')
                        adjList[i*m*n+j*n+k].push_back(i*m*n+j*n+(k-1));
                    
                    if (k<n-1 && simple_grid[i][j][k+1]!= 'o')
                        adjList[i*m*n+j*n+k].push_back(i*m*n+j*n+(k+1));
                    
                    if (j<m-1 && simple_grid[i][j+1][k]!= 'o')
                        adjList[i*m*n+j*n+k].push_back(i*m*n+(j+1)*n+k);
                    
                    if (i<h-1 && simple_grid[i+1][j][k]!= 'o')
                        adjList[i*m*n+j*n+k].push_back((i+1)*m*n+j*n+k);
                }
                    
            }
        }
    }
    
    
    queue<int> q;
    int distance[V];
    int path[V];
    for (int i=0; i<V; i++) {
        distance[i] = -1;
        path[i] = -1;
    }
    
    int s=0;
    distance[s]=0;
    q.push(s);
    
    while(!q.empty()){
        int v=q.front();
        q.pop();
        
        std::list<int> neighborList = adjList[v];
        for(auto it=neighborList.begin(); it != neighborList.end() ; ++it ){
            int w=*it;
            if( distance[w] == -1) {
                distance[w]=distance[v]+1;
                path[w]=v;
                q.push(w);
            }
        }
    }
    
    for (int i=0; i<V; i++) {
        cout<<i<<" "<<path[i]<<endl;
    }
    
    
    std::vector<Direction> shortestPath;
    std::vector<int> pathIndex;
    int endIndex = V-1;
    
    if (path[endIndex]!=-1){

        solLabyrinth.isPossible = true;
        
        cout<<"There is a path through exists the maze: "<<endl;
        
        int shortestDistance = 0;
        while (path[endIndex]!=-1){
            pathIndex.push_back(endIndex);
            int diff=endIndex-path[endIndex];
            if (diff == m*n)
                shortestPath.push_back(DOWN);
            else if (diff == -(m*n))
                shortestPath.push_back(UP);
            else if (diff == n)
                shortestPath.push_back(SOUTH);
            else if (diff == -n)
                shortestPath.push_back(NORTH);
            else if (diff == 1)
                shortestPath.push_back(EAST);
            else
                shortestPath.push_back(WEST);
            endIndex=path[endIndex];
            ++shortestDistance;
        }
        
        solLabyrinth.amountOfTime = 5*shortestDistance;
        for (auto it3=shortestPath.rbegin(); it3 !=shortestPath.rend(); it3++) {
            (solLabyrinth.directions).push_back(*it3);
        }
    
        cout<<"Shortest path:"<<endl;
        for (auto it3=shortestPath.rbegin(); it3 !=shortestPath.rend(); it3++) {
            cout<<*it3<<endl;
        }
    
        cout<<"The shortest path from 1 to 2 takes: "<<solLabyrinth.amountOfTime<<" seconds"<<endl;
    }
    else {
        solLabyrinth.isPossible = false;
        solLabyrinth.amountOfTime = 0;
        solLabyrinth.directions = {};
        }

    
    return 0;
}
