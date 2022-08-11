import random
import math


problem = input("input the word sum: ").split(" ")

words = "".join(problem)

def assignment(letters):
    letter_assignments = {}

    for i in letters:
        randomNumber = math.floor(random.random()*10)

        while(randomNumber in letter_assignments.values()):
            randomNumber = math.floor(random.random()*10)
            
        letter_assignments[i] = randomNumber
        
    return letter_assignments
        

def check_equation(assignments):
    leftTotal = 0
    rightTotal = ""
    
    for i in problem[0:-1]:
        number = ""
    
        for letters in i:
            number += str(assignments.get(letters))

        leftTotal += int(number)

    for letter in problem[len(problem)-1]:
        rightTotal += str(assignments.get(letter))

    if(leftTotal == int(rightTotal)):    
       return True
    else:
       return False


def idkHandlerLol():
    letter_amount = []

    for i in words:
        if(i not in letter_amount):
            letter_amount.append(i)
            
    assignments = assignment(letter_amount)

    while(not check_equation(assignments)):
        assignments = assignment(letter_amount)

    print(assignments)
    
idkHandlerLol()    
