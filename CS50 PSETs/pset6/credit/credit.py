from cs50 import get_int, get_string

while True:
    card = get_string("What's your card number?:")
    if card.isnumeric()==True:
        break

def more_than_10(i):
    if i >= 10:
        r = i%10
        sum = 1 + r
        return sum
    else:
        return i


if len(card) < 13 or len(card) > 16:
    print("INVALID")
else:
    reverse = card[::-1] #reverse card number
    list1 = reverse[1::2] #take alternate numbers starting from 2nd
    list1 = list(list1) #convert each character in string into elements in list
    list2 = [int(i) * 2 for i in list1] #convert string to integer then *2
    list2 = [more_than_10(i) for i in list2]
    sum1 = sum(list2)
    #list3 = list(card[1::2])
    list3 = reverse[0::2]
    list3 = [int(i) for i in list3]
    total = sum1 + sum(list3)
    last_digit = int(str(total)[-1])
    
    if last_digit == 0 and int(card[0]) == 4:
        print("VISA")
    elif last_digit == 0 and (int(card[0:2]) >= 51 and int(card[0:2]) <= 55):
        print("MASTERCARD")
    elif last_digit == 0 and (int(card[0:2]) == 34 or int(card[0:2]) == 37):
        print("AMEX")
    else:
        print("INVALID")






