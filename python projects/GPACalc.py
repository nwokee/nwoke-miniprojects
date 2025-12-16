grades = ["A", "B", "C", "D", "F"]
gchour = [4, 3, 2, 1, 0]
gcount = [0] * 5
csum = 0
ccount = 0

x = float(input("Enter Grades (-1 to stop): "))

while (x != -1):
    gi = int(x / 10)
    gi = 9 - gi
    if gi > 3:
        gi = 4
    elif gi < 0:
        gi = 0

    gcount[gi] += 1
    csum += gchour[gi]
    ccount += 1

    if gi == 4 or gi == 0:
        print("The %s is an %s" % (x, grades[gi]))
    else:
        print("The %s is a %s" % (x, grades[gi]))

    x = float(input())

if ccount == 0:
    print("No Grades Entered")
else:
    for i in range(0, 5):
        if gcount[i] == 1:
            print("There was 1", grades[i])
        else:
            print("There were %s %ss" % (gcount[i], grades[i]))
    gpa = csum / ccount
    print("GPA =", round(gpa, 2))