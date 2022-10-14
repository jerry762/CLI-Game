#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

void printTable(char table[3][3]);

int main()
{
    char table[3][3], OX[3] = "XO";
    bool pos[3][3] = {false};
    int time = 0, input;

    memset(table, ' ', sizeof(table));

    printf("A player (X)\nB player (O)\n\n");
    printTable(table);

    while (time < 9)
    {
        printf("%c player input position (%c):", (time % 2) ? 'B' : 'A', OX[time % 2]);
        input = getch() - '0';

        if (input > 9 || input < 1 || pos[(input - 1) / 3][(input - 1) % 3] == true)
        {
            printf("input again !\n");
            continue;
        }

        pos[(input - 1) / 3][(input - 1) % 3] = true;
        table[(input - 1) / 3][(input - 1) % 3] = OX[time % 2];

        system("cls");
        printTable(table);

        if ((table[0][0] == OX[time % 2] &&
             table[1][1] == OX[time % 2] &&
             table[2][2] == OX[time % 2]) ||

            (table[2][0] == OX[time % 2] &&
             table[1][1] == OX[time % 2] &&
             table[0][2] == OX[time % 2]))
        {
            printf("%c player win !\n", (time % 2) ? 'B' : 'A');
            system("pause");
            return 0;
        }

        for (int i = 0; i < 3; i++)
        {
            int row = 0, column = 0;

            for (int j = 0; j < 3; j++)
            {
                if (table[i][j] == OX[time % 2])
                    row++;
                if (table[j][i] == OX[time % 2])
                    column++;
            }
            if (row == 3 || column == 3)
            {
                printf("%c player win !\n", (time % 2) ? 'B' : 'A');
                system("pause");
                return 0;
            }
        }
        time++;
    }
    printf("no winner !\n");
    system("pause");
    return 0;
}

void printTable(char table[3][3])
{
    printf("\t*-*-*-*\n");
    printf("\t|%c|%c|%c|\n", table[2][0], table[2][1], table[2][2]);
    printf("\t*-*-*-*\n");
    printf("\t|%c|%c|%c|\n", table[1][0], table[1][1], table[1][2]);
    printf("\t*-*-*-*\n");
    printf("\t|%c|%c|%c|\n", table[0][0], table[0][1], table[0][2]);
    printf("\t*-*-*-*\n\n");
}