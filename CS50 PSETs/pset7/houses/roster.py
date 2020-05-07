import csv
import cs50
import sys

if len(sys.argv) != 2:
    print("python import.py [name of house]")
    sys.exit(1)

db = cs50.SQL("sqlite:///students.db")

house = sys.argv[1]

selected_students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", house)

for rows in selected_students:
    if rows['middle']==None:
        #print(rows['first'],rows['last'],",born", rows['birth'])
        print(f"{rows['first']} {rows['last']}, born {rows['birth']}")
    else:
        print(f"{rows['first']} {rows['middle']} {rows['last']}, born {rows['birth']}")
        #print(rows['first'],rows['middle'] ,rows['last'],",born", rows['birth'])

