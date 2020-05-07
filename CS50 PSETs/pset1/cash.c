// Math library
#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main (void)
{
float change=0;
int count=0;
 do
    {
           change = get_float("What's the change? ");

    }
    while (change<0);

int amount = round(change*100);

while(amount > 0)
{
  if (amount >= 25)
  {
      amount  =  amount - 25;
      count++;
  }

  else if (amount >= 10)
  {
      amount =  amount - 10;
      count++;
  }

  else if (amount >= 5)
  {
      amount = amount -5;
      count++;
  }

  else
  {
      amount = amount -1;
      count ++;
  }


  }
  printf("%i coins\n", count);

  }
