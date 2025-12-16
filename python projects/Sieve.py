from array import array
import random


def createArray(n):
    arr = array('i')
    for i in range(0, n):
        arr.append(random.randrange(0, round(n / 2)))
    return arr


size = int(input("Enter array size: "))
pool = createArray(size)
print(" ")
done = False

while not done:
    target = int(input("Enter a number to look for (negative num to end): "))
    if target < 0:
        done = True
    else:
        fnd = 0
        for i in range(0, len(pool)):
            if pool[i] == target:
                if fnd == 0:
                    print("Indices %s has been found: %s" % (target, i), end=" ")
                else:
                    print(", %s" % (i), end=" ")
                fnd += 1
        if fnd == 0:
            print("%s was not in this array" % (target))
        elif fnd == 1:
            print(" ")
            print("%s was found %s time" % (target, fnd))
        else:
            print(" ")
            print("%s was found %s times" % (target, fnd))
        print(" ")