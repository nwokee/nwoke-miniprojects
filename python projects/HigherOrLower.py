import random


max = int(input("Enter max value: "))

if max <= 0:
    target = random.randrange(max,1)
else:
    target = random.randrange(0,max+1)
gcount = 0
tfound = False
guess = int(input("Guess the random number between 0 and %s(-1 to give up): "%(max)))


while (guess != -1) and (not tfound):
    gcount += 1
    if guess == target:
        tfound = True
        if gcount == 1:
            print("Wow! You got the number(%s) in only 1 guess!" %(target))
        else:
            print("Congratulations! You guessed the number(%s) after %s tries!" %(target, gcount))
    elif guess < target:
        guess = int(input("HIGHER: "))
    else:
        guess = int(input("LOWER: "))


if not tfound:
    print("You gave up?? The number was", target)