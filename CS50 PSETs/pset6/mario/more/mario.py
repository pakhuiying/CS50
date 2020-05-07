from cs50 import get_int

while (True):
    h = get_int("What's the height?\n")
    if h >=1 and h<=8:
        break

count = 1

for i in range(h):
    print(" "*(h-count), end="")
    print("#"*count, end="  ")
    print("#"*count)
    count+=1

