#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include <Windows.h>

#define BOX_NUMBER 6
#define HEIGHT 11
#define WIDTH 23

typedef struct location
{
    int x;
    int y;
} Location;

void info();
void init();
void game();
void printMap();

char map[HEIGHT][WIDTH] = {
    "    #####             ",
    "    #   #             ",
    "    #B  #             ",
    "  ###  B###           ",
    "  #  B  B #           ",
    "### # ### #     ######",
    "#   # ### #######  @@#",
    "# B  B             @@#",
    "##### #### #P####  @@#",
    "    #      ###  ######",
    "    ########          ",
};

Location player;
Location box[BOX_NUMBER];
Location target[BOX_NUMBER];

int onTargetNum = BOX_NUMBER;

HANDLE stdHandle;
COORD coord;

int main()
{
    info();
    game();

    return 0;
}

void info()
{
    system("cls");
    printf(" ____        _         _\n");
    printf("/ ___|  ___ | | _____ | |__   __ _ _ __\n");
    printf("\\___ \\ / _ \\| |/ / _ \\| '_ \\ / _` | '_ \\\n");
    printf(" ___) | (_) |   < (_) | |_) | (_| | | | |\n");
    printf("|____/ \\___/|_|\\_\\___/|_.__/ \\__,_|_| |_|\n\n\n");
    printf("Welcome to my game sokoban !\n\n");
    printf("Symbol meaning\n");
    printf("----------------------------------------------\n");
    printf("# --> Wall\n");
    printf("@ --> location\n");
    printf("B --> Box (not on the location !)\n");
    printf("b --> Box (on the location !)\n\n");
    printf("Rule\n");
    printf("----------------------------------------------\n");
    printf("You can use (W,S,A,D) to move P.\n");
    printf("Move P to push all boxes to specific location.\n");
    printf("When all of boxes on their specific location, you win the game.\n\n");
    printf("Press any key to start ...");
    getch();
    system("cls");
}

void init()
{
    CONSOLE_CURSOR_INFO ci;
    int count1 = 0;
    int count2 = 0;

    stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = false;
    SetConsoleCursorInfo(stdHandle, &ci);

    coord.X = 0;
    coord.Y = 0;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (map[i][j] == 'P')
            {
                player.y = i;
                player.x = j;
            }
            if (map[i][j] == 'B')
            {
                box[count1].y = i;
                box[count1].x = j;
                count1++;
            }
            if (map[i][j] == '@')
            {
                target[count2].y = i;
                target[count2].x = j;
                count2++;
            }
            if (map[i][j] == 'b')
            {
                box[count1].y = i;
                box[count1].x = j;
                target[count2].y = i;
                target[count2].x = j;
                count1++;
                count2++;
                onTargetNum--;
            }
        }
    }
}

void game()
{
    init();

    char input;

    while (onTargetNum)
    {
        printf("%d left...\n\n", onTargetNum);
        printMap();

        input = getch();

        switch (input)
        {
        case 'W':
        case 'w':
            //* handle move
            if (map[player.y - 1][player.x] == ' ' ||
                map[player.y - 1][player.x] == '@')
            {
                map[player.y - 1][player.x] = 'P';
                map[player.y][player.x] = ' ';
                player.y--;
                //* check leave @
                for (int i = 0; i < BOX_NUMBER; i++)
                {
                    if (player.x == target[i].x && player.y + 1 == target[i].y)
                    {
                        map[player.y + 1][player.x] = '@';
                        break;
                    }
                }
            }
            //* handle push
            else if (map[player.y - 1][player.x] == 'B' ||
                     map[player.y - 1][player.x] == 'b')
            {
                if (map[player.y - 2][player.x] != '#' &&
                    map[player.y - 2][player.x] != 'B' &&
                    map[player.y - 2][player.x] != 'b')
                {
                    if (map[player.y - 2][player.x] == ' ')
                    {
                        map[player.y - 2][player.x] = 'B';
                    }
                    if (map[player.y - 2][player.x] == '@')
                    {
                        map[player.y - 2][player.x] = 'b';
                        onTargetNum--;
                    }
                    if (map[player.y - 1][player.x] == 'b')
                        onTargetNum++;
                    map[player.y - 1][player.x] = 'P';
                    map[player.y][player.x] = ' ';
                    player.y--;
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x == box[i].x && player.y == box[i].y)
                        {
                            box[i].y--;
                            break;
                        }
                    }
                    //* check leave @
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x == target[i].x && player.y + 1 == target[i].y)
                        {
                            map[player.y + 1][player.x] = '@';
                            break;
                        }
                    }
                }
            }
            break;
        case 'S':
        case 's':
            //* handle move
            if (map[player.y + 1][player.x] == ' ' ||
                map[player.y + 1][player.x] == '@')
            {
                map[player.y + 1][player.x] = 'P';
                map[player.y][player.x] = ' ';
                player.y++;
                //* check leave @
                for (int i = 0; i < BOX_NUMBER; i++)
                {
                    if (player.x == target[i].x && player.y - 1 == target[i].y)
                    {
                        map[player.y - 1][player.x] = '@';
                        break;
                    }
                }
            }
            //* handle push
            else if (map[player.y + 1][player.x] == 'B' ||
                     map[player.y + 1][player.x] == 'b')
            {
                if (map[player.y + 2][player.x] != '#' &&
                    map[player.y + 2][player.x] != 'B' &&
                    map[player.y + 2][player.x] != 'b')
                {
                    if (map[player.y + 2][player.x] == ' ')
                    {
                        map[player.y + 2][player.x] = 'B';
                    }
                    if (map[player.y + 2][player.x] == '@')
                    {
                        map[player.y + 2][player.x] = 'b';
                        onTargetNum--;
                    }
                    if (map[player.y + 1][player.x] == 'b')
                        onTargetNum++;
                    map[player.y + 1][player.x] = 'P';
                    map[player.y][player.x] = ' ';
                    player.y++;
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x == box[i].x && player.y == box[i].y)
                        {
                            box[i].y++;
                            break;
                        }
                    }
                    //* check leave @
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x == target[i].x && player.y - 1 == target[i].y)
                        {
                            map[player.y - 1][player.x] = '@';
                            break;
                        }
                    }
                }
            }
            break;
        case 'A':
        case 'a':
            //* handle move
            if (map[player.y][player.x - 1] == ' ' ||
                map[player.y][player.x - 1] == '@')
            {
                map[player.y][player.x - 1] = 'P';
                map[player.y][player.x] = ' ';
                player.x--;
                //* check leave @
                for (int i = 0; i < BOX_NUMBER; i++)
                {
                    if (player.x + 1 == target[i].x && player.y == target[i].y)
                    {
                        map[player.y][player.x + 1] = '@';
                        break;
                    }
                }
            }
            //* handle push
            else if (map[player.y][player.x - 1] == 'B' ||
                     map[player.y][player.x - 1] == 'b')
            {
                if (map[player.y][player.x - 2] != '#' &&
                    map[player.y][player.x - 2] != 'B' &&
                    map[player.y][player.x - 2] != 'b')
                {
                    if (map[player.y][player.x - 2] == ' ')
                    {
                        map[player.y][player.x - 2] = 'B';
                    }
                    if (map[player.y][player.x - 2] == '@')
                    {
                        map[player.y][player.x - 2] = 'b';
                        onTargetNum--;
                    }
                    if (map[player.y][player.x - 1] == 'b')
                        onTargetNum++;
                    map[player.y][player.x - 1] = 'P';
                    map[player.y][player.x] = ' ';
                    player.x--;
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x == box[i].x && player.y == box[i].y)
                        {
                            box[i].x--;
                            break;
                        }
                    }
                    //* check leave @
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x + 1 == target[i].x && player.y == target[i].y)
                        {
                            map[player.y][player.x + 1] = '@';
                            break;
                        }
                    }
                }
            }
            break;
        case 'D':
        case 'd':
            //* handle move
            if (map[player.y][player.x + 1] == ' ' ||
                map[player.y][player.x + 1] == '@')
            {
                map[player.y][player.x + 1] = 'P';
                map[player.y][player.x] = ' ';
                player.x++;
                //* check leave @
                for (int i = 0; i < BOX_NUMBER; i++)
                {
                    if (player.x - 1 == target[i].x && player.y == target[i].y)
                    {
                        map[player.y][player.x - 1] = '@';
                        break;
                    }
                }
            }
            //* handle push
            else if (map[player.y][player.x + 1] == 'B' ||
                     map[player.y][player.x + 1] == 'b')
            {
                if (map[player.y][player.x + 2] != '#' &&
                    map[player.y][player.x + 2] != 'B' &&
                    map[player.y][player.x + 2] != 'b')
                {
                    if (map[player.y][player.x + 2] == ' ')
                    {
                        map[player.y][player.x + 2] = 'B';
                    }
                    if (map[player.y][player.x + 2] == '@')
                    {
                        map[player.y][player.x + 2] = 'b';
                        onTargetNum--;
                    }
                    if (map[player.y][player.x + 1] == 'b')
                        onTargetNum++;
                    map[player.y][player.x + 1] = 'P';
                    map[player.y][player.x] = ' ';
                    player.x++;
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x == box[i].x && player.y == box[i].y)
                        {
                            box[i].x++;
                            break;
                        }
                    }
                    //* check leave @
                    for (int i = 0; i < BOX_NUMBER; i++)
                    {
                        if (player.x - 1 == target[i].x && player.y == target[i].y)
                        {
                            map[player.y][player.x - 1] = '@';
                            break;
                        }
                    }
                }
            }
            break;
        }
        SetConsoleCursorPosition(stdHandle, coord);
    }

    system("cls");
    printf("Congratulations !\n");
    printf("You won the game !\n\n");
    printf("Press any key to exit ...");
    getch();
}

void printMap()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        puts(map[i]);
    }
}