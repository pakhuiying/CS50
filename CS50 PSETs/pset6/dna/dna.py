import csv
import re
from cs50 import get_string
import sys

# Check for correct number of args
if len(sys.argv) != 3:
    print("Usage: python",sys.argv[0],"data.csv sequence.txt")
    sys.exit(1)

database = sys.argv[1]
txt = sys.argv[2]

# Open CSV file
database = open(database, mode='r')
database = csv.DictReader(database)
#The first line of the CSV file is assumed to contain the keys to use to build the dictionary.

sequences = open(txt, mode="r")
if sequences.mode == 'r':
    sequences = sequences.read()
    #print(sequences)
fieldnames = database.fieldnames #get fieldnames

dna_sequence = fieldnames[1:] #remove the first field

def count_seq(dna_seq):
    count_list=[]
    for i in range(1,len(sequences)): #start a for loop at 1 instead of 0
        n = sequences.count(dna_seq*i)
        if n != 0:
            count_list.append(i) #last i will give u the longest consecutive number
        else:
            count_list.append(0)
    longest_seq = max(count_list)
    return longest_seq

count_sequences = [count_seq(i) for i in dna_sequence] #remove the first field
#sequences.count doesnt count consecutive repeats
#print(fieldnames,count_sequences,dna_sequence)


for row in database:
        #print(row) #maps the information in each row to a dict
        slice_row = {fieldnames:row[fieldnames] for fieldnames in dna_sequence if fieldnames in row} #dict
        identity = row.get('name')
        slice_row = list(slice_row.values())
        slice_row = [int(i) for i in slice_row]
        #print(slice_row)
        if count_sequences == slice_row:
            person = identity
            break
        else:
            person = "No match"
print(person)

