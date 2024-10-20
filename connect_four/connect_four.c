#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 6
#define COLUMN 7
#define ROW_EXT ROW + 3 + 3
#define COLUMN_EXT COLUMN + 3 + 3

void Init(char table[ROW_EXT][COLUMN_EXT]);
void PrintMap(char table[ROW_EXT][COLUMN_EXT]);
bool CheckWin(char table[ROW_EXT][COLUMN_EXT], int posX, int posY, char player);

int main()
{
    int round = 1;
    char table[ROW_EXT][COLUMN_EXT];
    char input;

    Init(table);
    PrintMap(table);

    while (round)
    {
        input = getch();
        
        int posY;
        int posX;
        int columnNo = input - '0';

        for (size_t i = 0; i < ROW; i++)
        {
            if (table[ROW - 1 + 3 - i][columnNo + 3] == ' ')
            {
                table[ROW - 1 + 3 - i][columnNo + 3] = (round % 2) ? 'O' : 'X';
                posY = ROW - 1 + 3 - i;
                posX = columnNo + 3;
                break;
            }
        }

        PrintMap(table);

        if (CheckWin(table, posX, posY, (round % 2) ? 'O' : 'X'))
            break;

        round++;
    }

    return 0;
}

void Init(char table[ROW_EXT][COLUMN_EXT])
{
    for (size_t i = 0; i < ROW_EXT; i++)
    {
        for (size_t j = 0; j < COLUMN_EXT; j++)
        {
            table[i][j] = '=';
        }
    }

    for (size_t i = 0; i < ROW; i++)
    {
        for (size_t j = 0; j < COLUMN; j++)
        {
            table[i + 3][j + 3] = ' ';
        }
    }
}

bool CheckWin(char table[ROW_EXT][COLUMN_EXT], int posX, int posY, char player)
{
    if (table[posY][posX - 0] == player && table[posY][posX - 1] == player && table[posY][posX - 2] == player && table[posY][posX - 3] == player ||
        table[posY][posX + 0] == player && table[posY][posX + 1] == player && table[posY][posX + 2] == player && table[posY][posX + 3] == player ||
        table[posY - 0][posX] == player && table[posY - 1][posX] == player && table[posY - 2][posX] == player && table[posY - 3][posX] == player ||
        table[posY + 0][posX] == player && table[posY + 1][posX] == player && table[posY + 2][posX] == player && table[posY + 3][posX] == player ||
        table[posY - 0][posX - 0] == player && table[posY - 1][posX - 1] == player && table[posY - 2][posX - 2] == player && table[posY - 3][posX - 3] == player ||
        table[posY + 0][posX + 0] == player && table[posY + 1][posX + 1] == player && table[posY + 2][posX + 2] == player && table[posY + 3][posX + 3] == player ||
        table[posY - 0][posX + 0] == player && table[posY - 1][posX + 1] == player && table[posY - 2][posX + 2] == player && table[posY - 3][posX + 3] == player ||
        table[posY + 0][posX - 0] == player && table[posY + 1][posX - 1] == player && table[posY + 2][posX - 2] == player && table[posY + 3][posX - 3] == player)
    {
        printf("Player %c win !\n", player);
        return true;
    }

    return false;
}

void PrintMap(char table[ROW_EXT][COLUMN_EXT])
{
    system("cls");

    printf("%s%-2d%-2d%-2d%-2d%-2d%-2d%-2d\n", "    ", 0, 1, 2, 3, 4, 5, 6);
    printf("%s%s", "   ", "===============\n");
    for (size_t i = 0; i < ROW; i++)
    {
        printf(" %d |", i);
        for (size_t j = 0; j < COLUMN; j++)
        {
            printf("%c|", table[i + 3][j + 3]);
        }
        printf("\n");
    }
    printf("%s%s", "   ", "===============\n");
}