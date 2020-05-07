from cs50 import get_float
import math

while True:
    cash = get_float("Change owed:")
    if cash>=0:
        break

cash = cash*100

quarters = 0
dimes = 0
nickels = 0
pennies = 0

while cash>0:
    if cash >= 25:
        quarters = math.floor(cash/25)
        cash = cash%25
    elif cash >= 10 and cash < 25:
        dimes = math.floor(cash/10)
        cash = cash%10
    elif cash >= 5 and cash < 10:
        nickels = math.floor(cash/5)
        cash = cash%5
    else:
         pennies = math.floor(cash/1)
         cash = cash%1
        
    
total = quarters + dimes + nickels + pennies

print(total)
        