#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

int main (void)
{
long card;
card = get_long("What's your credit card number? ");    


int digits[8];  // declaring array that holds 8 digits. every odd number in 16 long digit
int sumOddDigits=0;
int sumEvenDigits=0;
int sum=0;
long cardOdd=card;
long cardEven=card;
cardOdd = card/10; // remove last digit  
long FirstTwo = card; //extract first 2 digits
//FirstTwo =  floor(card/pow(10,14));
  while (FirstTwo >= 100) 
    {
        FirstTwo /= 10;
    }
   // return FirstTwo;

printf("FirstTwo: %li\n",FirstTwo); 
for (int i = 0; i < 8; ++i)  // for each odd digit. 
{
    
    digits[i] = cardOdd %10; // extract the last digit. last digit is the remainder 
    cardOdd /= 100;   // remove last 2 digit at a time
    digits[i]*=2; //multiply digits by 2
    printf("%i\n",digits[i]); 
    if (digits[i]>=10){
        digits[i]=digits[i]%10; //get last digit
        digits[i]+=1; //digits>10 will always need to +1 becus 9 is the max number & sum will not exceed 20
    } 
    else
    {
        digits[i]=digits[i];
    }
    sumOddDigits+=digits[i];  
}
printf("SumOddDigits: %i\n",sumOddDigits);  

for (int i = 0; i < 8; ++i)  // for each odd digit. 
{   
    digits[i] = cardEven %10; // extract the last digit 
    cardEven /= 100;   // remove last 2 digit at a time
    printf("%i\n",digits[i]);  
    sumEvenDigits+=digits[i];    
}

printf("SumEvenDigits: %i\n",sumEvenDigits);  

sum=sumEvenDigits + sumOddDigits;
int lastDigit=0;
lastDigit = sum%10;

if (lastDigit==0 && floor(FirstTwo/10)==4 && ((card/pow(10,12)>=1 & card/pow(10,12)<10) || (card/pow(10,15)>=1 & card/pow(10,15)<10)))
{
   printf("VISA\n");
}

else if (lastDigit==0 && (FirstTwo>50 && FirstTwo<56) && (card/pow(10,15)>=1 || card/pow(10,15)<10))
{
   printf("MASTERCARD\n");
}

else if (lastDigit==0 && (FirstTwo==34 || FirstTwo==37) && (card/pow(10,14)>=1 || card/pow(10,14)<10))
{
   printf("AMEX\n");
}

//if (!(lastDigit==0) || card/pow(10,15)<1 || card/pow(10,15)>9) //make sure that only card length==16 is accepted
else
{
    printf("INVALID\n");
}
//printf("lastDigit: %i\n",lastDigit);  
    
}

