#include <ncurses.h>
#include <string>

using namespace std;

int menu();

int main()
{
    menu();
    return(0);
}

int menu()
{
    initscr();
    noecho();
    

    int sizeY, sizeX;
    getmaxyx(stdscr, sizeY, sizeX);

    //create a menu window
    WINDOW *menuwin = newwin(6, 40,  sizeY/2, sizeX-50);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    string MENUOPTIONS [3] = {"PLAY", "OPTIONS", "QUIT"};
    int choice;
    int highlight = 0;

    while(1)
    {
        for(int i = 0; i < 3; i++)
        {
            if(i == highlight)
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 1, MENUOPTIONS[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 2; 
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 3)
                    highlight = 0;
                break;
            default:
                break;
        }
        if(choice == 10)
            return(highlight);
            break;
    }
    printw("You just selected %d", highlight);
    getch();
    endwin();

}

