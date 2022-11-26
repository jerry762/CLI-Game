#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define HEIGHT 20
#define WIDTH 31

typedef struct location
{
    int x;
    int y;
} Location;

void info();
int init(Location *player, Location *dest);
void game();
void printMap();

char maze_map[HEIGHT][WIDTH] = {
    "##############################",
    "#P         #   ##   # ### ####",
    "# ###### # # #    # # ### ####",
    "# #   ## #   # #### # ###   ##",
    "#   # ##  ###    #  #  ## ####",
    "##### #     # ##### ##    ####",
    "#   # ##### #   #   # # #    #",
    "# # #    ## # #### ## # # ####",
    "# # # ##      ##      # # ####",
    "# # # ####### ## ###### #   ##",
    "# #   ##   # ## ###### ###   #",
    "# ###### # #####  #        # #",
    "#        # #     ##### ### # o",
    "# ######## ##### # ### ### # #",
    "#     # ## ##### ###       ###",
    "##### # ## #      ######## # #",
    "#     # ## ## ###        #   #",
    "# # ###       ###### ####### #",
    "# #    ### ##      #         #",
    "##############################",
};

int main()
{
    info();
    game();

    return 0;
}

void info()
{
    system("cls");
    printf(" __  __\n");
    printf("|  \\/  | __ _ _______\n");
    printf("| |\\/| |/ _` |_  / _ \\\n");
    printf("| |  | | (_| |/ /  __/\n");
    printf("|_|  |_|\\__,_/___\\___|\n\n\n");
    printf("Welcome to my game maze !\n\n");
    printf("\'P\' is your start point\n");
    printf("Use w, s, a, d to move\n");
    printf("Destination is \'o\'\n\n");
    printf("Press any key to start ...");
    getch();
    system("cls");
}

int init(Location *player, Location *dest)
{
    int count = 0;

    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            if (maze_map[i][j] == 'P')
            {
                player->x = j;
                player->y = i;
                count++;
            }
            else if (maze_map[i][j] == 'o')
            {
                dest->x = j;
                dest->y = i;
                count++;
            }
        }
        if (count == 2)
            break;
    }

    return count;
}

void game()
{
    char input = 0;

    Location player = {.x = 0, .y = 0};
    Location dest = {.x = 0, .y = 0};

    if (init(&player, &dest) != 2)
    {
        printf("Init Failure !");
        exit(EXIT_FAILURE);
    }

    while (player.x != dest.x || player.y != dest.y)
    {

        printMap();

        input = getch();

        switch (input)
        {
        case 'W':
        case 'w':
            if (maze_map[player.y - 1][player.x] == ' ' ||
                maze_map[player.y - 1][player.x] == 'o')
            {
                maze_map[player.y - 1][player.x] = 'P';
                maze_map[player.y][player.x] = ' ';
                player.y--;
            }
            break;
        case 'S':
        case 's':
            if (maze_map[player.y + 1][player.x] == ' ' ||
                maze_map[player.y + 1][player.x] == 'o')
            {
                maze_map[player.y + 1][player.x] = 'P';
                maze_map[player.y][player.x] = ' ';
                player.y++;
            }
            break;
        case 'A':
        case 'a':
            if (maze_map[player.y][player.x - 1] == ' ' ||
                maze_map[player.y][player.x - 1] == 'o')
            {
                maze_map[player.y][player.x - 1] = 'P';
                maze_map[player.y][player.x] = ' ';
                player.x--;
            }
            break;
        case 'D':
        case 'd':
            if (maze_map[player.y][player.x + 1] == ' ' ||
                maze_map[player.y][player.x + 1] == 'o')
            {
                maze_map[player.y][player.x + 1] = 'P';
                maze_map[player.y][player.x] = ' ';
                player.x++;
            }
            break;
        }
        system("cls");
    }

    printf("Congratulations !\n");
    printf("You won the game !\n\n");
    printf("Press any key to exit ...");
    getch();
}

void printMap()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        puts(maze_map[i]);
    }
}
