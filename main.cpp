#include <iostream>
#include <climits>
#include <queue>
using namespace std;
//ifstream cin("sudoku.in");
//ofstream cout("sudoku.out");
#define len 9
int limit;
int sdk[20][20];
pair <int,int> poz[150];

bool validateRowCol(int xk, int yk, int value)
{
    for(int x = 1; x <= len; x++)
    {
        if(sdk[x][yk] == value)
            return false;
    }
    
    for(int y = 1; y <= len; y++)
    {
        if(sdk[xk][y] == value)
            return false;
    }
    
    return true;
}

bool validateCheckBox(int xk, int yk, int value)
{
    int coordX = xk/3;
    int coordY = yk/3;
    
    if(xk%3 == 0)
        coordX--; /// bigger frame from 1 to 3 on X axis

    if(yk%3 == 0)
        coordY--; /// bigger frame from 1 to 3 on Y axis
    
    int startx = coordX*3 + 1;
    int endx = (coordX+1) * 3;
    
    int starty = coordY*3 + 1;
    int endy = (coordY+1) * 3;
    for(int x = startx; x <= endx; x++)
    {
        for(int y = starty; y <= endy; y++)
        {
            if(value == sdk[x][y])
                return false;
        }
    }
    
    return true;
}

bool verify(int xk, int yk, int value)
{
    return validateRowCol(xk,yk,value) && validateCheckBox(xk,yk,value);
}

bool complete()
{
    for(int x = 1; x <= len; x++)
    {
        for(int y = 1; y <= len; y++)
        {
            if(!sdk[x][y])
            return false;
        }
    }
    return true;
}

void printSudoku()
{
    cout << '\n';
    cout << "Here is the solved sudoku puzzle!" << '\n';
    for(int x = 1; x <= len; x++)
    {
        for(int y = 1; y <= len; y++)
        {
            cout << sdk[x][y] << " ";
        }
        cout << '\n';
    }
}

void solveSudoku(int k)
{
    int xk = poz[k].first;
    int yk = poz[k].second;
    for(int i = 1; i <= len; i++)
    {
        if(verify(xk,yk,i))
        {
            sdk[xk][yk] = i;
            
            if(complete() && k == limit)
            {
                printSudoku();
                return ;
            }

            solveSudoku(k+1);
            
            sdk[xk][yk] = 0;
        }
    }
}

int main()
{
    cout << "Insert the unsolved sudoku matrix: " << '\n';
    for(int x = 1; x <= len; x++)
    {
        for(int y = 1; y <= len; y++)
        {
            cin >> sdk[x][y];
            if(sdk[x][y] == 0)
            {
                limit ++;
                poz[limit] = {x,y};
            }
        }
    }
    solveSudoku(1);

    system("pause");
    return 0;
}

/*
0 0 7 0 0 0 0 0 0
0 0 0 8 6 0 4 0 0
2 0 0 0 0 1 6 0 3
0 0 9 0 0 0 1 0 0
1 0 2 0 0 7 0 9 0
0 0 0 0 0 0 0 6 0
0 0 5 0 0 9 0 0 1
0 0 0 0 0 0 3 4 0
0 0 0 3 0 0 2 0 0
*/