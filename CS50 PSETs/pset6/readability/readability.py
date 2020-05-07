from cs50 import get_string

text = get_string("Text:")
words = 1
letters = 0
sentence = 0

for i in text:
    if i.isspace()==True:
        words+=1
    if i.isalpha()==True:
        letters+=1
    if i == "." or i == "!" or i == "?":
        sentence+=1
L = letters/words * 100
S = sentence/words * 100
index = round(0.0588*L - 0.296*S - 15.8)
if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade",index)
