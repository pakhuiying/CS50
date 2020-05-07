import csv
import cs50
import sys

#open(f"students.db","w")
db = cs50.SQL("sqlite:///students.db")
#db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT)")


if len(sys.argv) != 2:
    print("python import.py characters.csv")
    sys.exit(1)

with open(sys.argv[1], "r") as file:
    characters = csv.DictReader(file)
    name_split = {}
    for row in characters:
        name = row["name"]
        names = name.split(" ")
        if name.count(" ") == 2:
            name_split['first'] = names[0]
            name_split['middle'] = names[1]
            name_split['last'] = names[2]
        elif name.count(" ") == 1:
            name_split['first'] = names[0]
            name_split['middle'] = None
            name_split['last'] = names[1]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",name_split["first"], name_split["middle"], name_split["last"],row["house"],row["birth"])





