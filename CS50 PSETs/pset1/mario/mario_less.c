#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int line;
    int n;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 1||n>8);

        for (line = 1; line <=n; line++)
        {
         int column;
         int dots=n-line;

          for (column = dots; column >0; column=column-1)
        {
            printf(" ");
        }

           for (column = 0; column < line; column++)
        {
            printf("#");
        }

            printf("\n");

        }

}
