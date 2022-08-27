import random
import math


problem = input("input the word sum: ").split(" ")

words = "".join(problem)

firstLetter = []


def assignment(letters): #function to assign random number values to each letter
    letter_assignments = {}

    for i in letters:
        randomNumber = math.floor(random.random()*10) #generates random number

        while(randomNumber in letter_assignments.values() or i in firstLetter and randomNumber == 0): #if number already assigned to another letter OR if letter is first letter and equal to 0, regenerate
            randomNumber = math.floor(random.random()*10)
            
        letter_assignments[i] = randomNumber #assign number in dictionary
        
    return letter_assignments
        

def check_equation(assignments): #function to check if the equation is true
    leftTotal = 0
    rightTotal = ""
    
    for i in problem[0:-1]: #left side of the equation
        number = ""
    
        for letters in i: #takes each number representation of each letter and concatonates them
            number += str(assignments.get(letters))

        leftTotal += int(number) #adds numbers representing each word, then adds to the running total of left side words

    for letter in problem[len(problem)-1]: #calculating numerical value of the right side of the equation
        rightTotal += str(assignments.get(letter))

    if(leftTotal == int(rightTotal)):    #checks if the equation is true 
       return True
    else:
       return False


def idkHandlerLol(): #deals with the results of both two functions above
    attempts = 0
    letter_amount = [] #this section creates array of all letters (no duplicates)

    for i in words:
        if(i not in letter_amount):
            letter_amount.append(i)
            
    for lol in problem: firstLetter.append(lol[0]) 
    
    assignments = assignment(letter_amount)

    while(not check_equation(assignments)): #checks if assignments give a true equation, if not, reroll numbers
        assignments = assignment(letter_amount)
        attempts += 1

    print(assignments, attempts) #absolutely no formatting for output yet, sorry lol
    
idkHandlerLol()    
