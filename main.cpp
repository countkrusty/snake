//
//  main.cpp
//  SnakeC++
//
//  Created by Tristan Wießalla on 10.06.19.
//  Copyright © 2019 Tristan Wießalla. All rights reserved.
//

#include <iostream>
#include <ncurses.h> //I/O library, not supported for Windows, alternative: conio 
#include <unistd.h> //for sleep functions
#include <cstdlib> //for rand function
using namespace std;

bool gameOver;

const int width = 40; // Specify map dimensions
const int heigth = 20;
int x, y, fruitx, fruity, score; // head & fruit positions, score
int tailx[1000], taily[1000];
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;


void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = heigth / 2;
    srand(time(NULL));
    fruitx = (rand() % (width-1))+1;
    fruity =(rand() % (heigth-1))+1;
    score = 0;
}

void Draw()
{
    initscr();
    curs_set(0);
    
    for (int i = 0; i <= heigth+1; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            if (i == 0 || i == heigth+1)
                mvaddstr(i, j, "#"); //Horizontal walls
            if (i < heigth+1 && (j == 0 || j == width))
                mvaddstr(i, j, "#"); //Vertical walls    for (int i = 0; i < width + 1; i++)
        }
    }
    mvaddstr(fruity, fruitx, "*");
    mvaddstr(y, x, "O");    
    for(int i = 0; i < nTail; i++)
	{
            mvaddstr(taily[i], tailx[i], "o");
    
	}
    mvprintw(0, width+5, "score: %i", score);
}

void Input()
{
    nodelay(stdscr, TRUE); //program doesn't block until key is pressed but loops continuously 
        switch(getch())
        {
            case  ' ':
                break;
            case  'a':
                dir = LEFT;
                break;
            case  'd':
                dir = RIGHT;
                break;
            case  'w':
                dir = UP;
                break;
            case  's':
                dir = DOWN;
                break;
            case  'x':
                gameOver = true;
                break;
            default:
                break;
       }
}

void Logic()
{
    for(int i = nTail ; i > 0; i--)
	{
            tailx[0] = x; //0th tail element = head
            taily[0] = y;
            taily[i] = taily[i-1];
            tailx[i] = tailx[i-1];
    	}
    switch(int(dir))
    {
        case 1:
            dir = LEFT;
            x--; //'When go left, decrease x-dim value (x) by one
	    break;
        case 2:
            dir = RIGHT;
            x++;
            break;
        case 3:
            dir = UP;
            y--;
            break;
        case 4:
            dir = DOWN;
            y++;
            break;
        default:
            break;
    }
    if(x >= width || x <= 0 || y >heigth || y <= 0) 
	gameOver = true; 
    for(int i = nTail; i > 0; i--)
        {
            if(x == tailx[i] && y == taily[i])
                gameOver = true;
        }    
    if(x == fruitx && y == fruity){
        fruitx = (rand() % (width-1))+1;
        fruity =(rand() % (heigth-1))+1;
        score += 5;
        nTail++;
    }
}

int main()
{
    Setup();
    do // Loop all program elements unless gameOver has become true.
    {
        initscr();
        erase();
        noecho();
        Draw();
        Input();
        Logic();
        usleep(300000);
        refresh();
    }while (!gameOver);
    endwin();
    return 0;
    
}


