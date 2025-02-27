import os
import sys
import getpass

user = (getpass.getuser())



def getKiraGradebook():
    date = input("Please enter the date of a file you would like to import in the form of YYYY-MM-DD: ")
    file = open(f"C:\\Users\\{user}\\Downloads\\Introduction to CS in Python (High School)_1st Period_7th Period_3rd Period_4th Period_5th period_6th Period_{date}.csv", "r", encoding="utf-8-sig")
    nameIndex = 0
    lessonIndex = 0
    grades = {}
    if file:
        while True:
            line = file.readline()
            if '"Name"' in line and '"Email"' in line:
                cols = line.replace('"', '').split(',')
                for i in range(len(cols)):
                    if cols[i] == 'Name' or cols[i].count('.', 0) >= 1:
                        if cols[i] == 'Name':
                            nameIndex = i
                        elif ' - ' in cols[i]:
                            lessonIndex = i
                            break
                    if cols[i] == '\n':
                        cols[i] = ''
            elif line != '' and 'Name' not in line:
                line = line.replace('"', '')
                line = line.replace('\n', '')
                line = line.split(',')
                if len(line[lessonIndex]) != 0 and lessonIndex != 0:
                    grades[line[nameIndex]] = int(line[lessonIndex])
                else:
                    grades[line[nameIndex]] = ""
            else:
                break
    file.close()
    os.remove(f"C:\\Users\\{user}\\Downloads\\Introduction to CS in Python (High School)_1st Period_7th Period_3rd Period_4th Period_5th period_6th Period_{date}.csv")
    return grades
    
    
def getUserIds():
    file = open("userids.csv", "r", encoding="utf-8-sig")
    ids = {}
    if file:
        while True:
            line = file.readline()
            if line != '':
               line = line.replace('\n', '')
               line = line.split(',')
               name = line[1] + ' ' + line[2]
               ids.update({line[0]: name})
            else:
                break
    file.close()
    return ids

def getFinalCSV(k, u): 
    new = {}
    name = input("What would you like to name the assignment?: ")
    for key, value in k.items():
        for key2, value2 in u.items():
            if(key2 == "Unique User ID"):
                new.update({key2: name})
            elif key == value2 or ('ALTGILBERS' in key and 'ALTGILBERS' in value2):
                new.update({key2: value})
    return new

def main():
    period = input("What class period is this import for?: ")
    final = getFinalCSV(getKiraGradebook(), getUserIds())

    file = open(f"C:\\Users\\{user}\\OneDrive - Cheatham County School District\\Documents\\Class files\\Computer Science\\Kira Gradebook Imports\\" +period + " " + next(iter(final.values())) + ".csv", "w")
    for key, value in final.items():
        file.write(key + ',' + str(value) + '\n')
    file.close()
    

main()



