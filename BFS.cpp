// C++ program to find the shortest path between
// a given source cell to a destination cell.
#include <bits/stdc++.h>
#include "BFS.h"

using namespace std;
#define ROW 9
#define COL 10

//To store matrix cell cordinates
struct Point
{
    int x;
    int y;
};

// A Data Structure for queue used in BFS
struct queueNode
{
    Point pt; // The cordinates of a cell
    int dist; // cell's distance of from the source
    string direction;
    string weight;
};

// check whether given cell (row, col) is a valid
// cell or not.
bool BFS:: isValid(int row, int col)
{
    // return true if row number and column number
    // is in range
    return (row !=-1) && (row < ROW) &&
           (col != -1) && (col < COL);
}

// These arrays are used to get row and column
// numbers of 4 neighbours of a given cell
int rowNum[] = {0, 0, 0, 1};
int colNum[] = {0, 0, 1, 0};


string BFS:: classifyDirection(int i){
    if (i==0){return "up";}
    if (i==1){return "left";}
    if (i==2){return "right";}
    if (i==3){return "down";}
    return " ";
}

vector<string> BFS::split_sentence(string str,vector<string> splitedVec){

    if(str[0]==' '){
        str.erase(str.begin());
    }
    string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            splitedVec.push_back(word);
            word = "";
        }
        else
        {
            word = word + x;
        }
    }
    splitedVec.push_back(word);
    return splitedVec;
}

void BFS:: print_vectors(vector<string> splitedDirec, vector<string> splitedWeight){
    int i=0;
    while (i<splitedDirec.size() || i<splitedWeight.size()){
        cout<<splitedDirec[i]<<"(" <<splitedWeight[i]<< ") ,";
        i++;
    }
}

// function to find the shortest path between
// a given source cell to a destination cell.
int BFS::bfs(int mat[][COL], Point src, Point dest)
{
    queue<string>pathVec;
    // check source and destination cell
    // of the matrix have value 1
    if (!mat[src.x][src.y] || !mat[dest.x][dest.y])
        return -1;

    bool visited[ROW][COL];
    memset(visited, false, sizeof visited);

    // Mark the source cell as visited
    visited[src.x][src.y] = true;

    // Create a queue for BFS
    queue<queueNode> q;

    // Distance of source cell is 0
    queueNode s = {src, 0};
    q.push(s); // Enqueue source cell

    // Do a BFS starting from source cell
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;

        // If we have reached the destination cell,
        // we are done
        vector<string> splitedDirec;
        vector<string> splitedWeight;
        if (pt.x == dest.x && pt.y == dest.y) {
            cout<<curr.direction<<endl;
            cout<<curr.weight<<endl;
            splitedDirec=split_sentence(curr.direction,splitedDirec);
            splitedWeight=split_sentence(curr.weight,splitedWeight);
            print_vectors(splitedDirec, splitedWeight);
            return curr.dist;
        }

        // Otherwise dequeue the front cell in the queue
        // and enqueue its adjacent cells
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            // if adjacent cell is valid, has path and
            // not visited yet, enqueue it.
            if (isValid(row, col) && mat[row][col] &&
                !visited[row][col])
            {
                // mark cell as visited and enqueue it
                visited[row][col] = true;
                string direc= classifyDirection(i);
                string wgt=  to_string(mat[row][col]);
                queueNode Adjcell = { {row, col},
                                      curr.dist + 1, curr.direction+" "+direc, curr.weight+" "+ wgt};
                q.push(Adjcell);
                pathVec.push(Adjcell.direction);
            }

        }
    }

    // Return -1 if destination cannot be reached
    return -1;
}

// Driver program to test above function
int main()
{
    int mat[ROW][COL] =
            {
                    { 1, 3, 12, 8, 1, 1, -1, 1, 1, 1 },
                    { 5, 2, 17, 4, 1, 1, 1, 0, 1, 1 },
                    { -1, 9, -1, 6, 1, 1, 0, 1, 0, 1 },
                    { 7, 3, 1, 2, 200, 0, 0, 0, 0, 1 },
                    { 1, 1, 1, -1, 1, 1, 1, 0, 1, 0 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
                    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
                    { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
                    { 1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }
            };

    Point source = {0, 0};
    Point dest = {3, 4};

    int dist = bfs(mat, source, dest);

    if (dist = INT_MAX) {
        cout << "Shortest Path doesn't exist" << dist;
    }
    return 0;
}
