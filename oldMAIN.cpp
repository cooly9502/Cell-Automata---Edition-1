// goal is to have a grid of X's and O's that ever half a second or so update with a life-like algorithem
#include <iostream>
#include <Windows.h> //for sleep
#include <stdlib.h> //for random decision algorithms
#include <time.h> //for random seed

#define DELAY 500 //500ms for each frame update
#define WIDTH 10 
#define HEIGHT 10

using namespace std;

int space[WIDTH][HEIGHT];
int iteration();
void test( int a, int x, int y );
bool render();
void generate();

int main()
{
    srand( time(NULL) );
    SetConsoleOutputCP(CP_UTF8); //allows fun characters
    generate();
    while (true)
    {
        render();
        iteration();
        Sleep(1000);
    }
    return 0;
}

int iteration()
{
    for ( int x = 0; x < WIDTH; x++ )
    {
        for ( int y = 0; y < HEIGHT; y++ )
        {
            int r = rand() % 8;
            test( r, x, y);
        }
    }
}

void generate()
{
    //generate for teams. BLANK = 0 | TEAM_A = 1 | TEAM_B = 2  an initialize function
    for ( int y = 0; y < HEIGHT; y++ )
    {
        for ( int x = 0; x < WIDTH; x++ )
        {
            //half of the board is TEAM_A
            if ( y < HEIGHT / 2 )
            {
                space[x][y] = 1;
            }else{
                space[x][y] = 2;
            }
        }
    }
}
bool render()
{
    for ( int i = 0; i < WIDTH; i ++){cout << "~";}
    cout << '\n';
    for ( int x = 0; x < HEIGHT; x++ )
    {
        for ( int y = 0; y < WIDTH; y++ )
        {
            cout << ( space[x][y] == 1 ? "█" : space[x][y] == 2 ? "▒" : " ");
        }
        cout << '\n';
    }
    return 1;
}

//testfor coords a is the random number 0 - 7
void test( int a, int x, int y)
{
    //value of area cell is trying to move to
    int move[3];
    switch( a ) 
        {
            case 0 : move[0] = (x + 1); move[1] = (y + 1); break; //top right
            case 1 : move[0] = (x + 1); move[1] = (y + 0); break;//right
            case 2 : move[0] = (x + 1); move[1] = (y - 1); break;//bottom right
            case 3 : move[0] = (x + 0); move[1] = (y - 1); break;//bottom
            case 4 : move[0] = (x - 1); move[1] = (y - 1); break;//bottom left
            case 5 : move[0] = (x - 1); move[1] = (y - 0); break;//left
            case 6 : move[0] = (x - 1); move[1] = (y + 1); break;//top left
            case 7 : move[0] = (x - 0); move[1] = (y + 1); break;//top 
        }
    //value of the new move's location
    int value;
    if ( move[0] > 0 && move[0] < WIDTH-1 )
    {
        if ( move[1] > 0 && move[1] < HEIGHT-1 )
        {
            value = space[move[0]][move[1]];
        }
    } else{
        //if outofbounds
        value = 4;
    }

    if ( value == 4 ){ /*do nothing*/ }
    else if ( value == 0)
    {
        //clear... move there
        space[ move[0] ][ move[1] ] = space[x][y];
        space[x][y] = 0;
    }else if ( value != space[x][y] )
    {
        //cell is not same team, enemy, 50 - 50 chance of winning battle 
        int randVal = rand() % 2; //50% random int
        if ( randVal == 1){
            space[move[0]][move[1]] = space[x][y]; //win
            space[x][y] = 0;
        }  else{
            space[x][y] = 0; //if die, set zero. if win, still set zero
        }
        
    }else
    {
        //cell is same team. do nothing
    }
}