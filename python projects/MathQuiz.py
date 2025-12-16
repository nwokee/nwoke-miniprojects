import time
def run_quiz(questions):
    score = 0
    for question in questions:
        print(question["prompt"])
        answer = input("Enter your answer : ")
        if answer == question["answer"]:
            print("Correct!\n")
            score += 1
        else:
            print("Wrong! The correct answer was", question["answer"], "\n")
    return score

# List of quiz questions. Each question is a dictionary.
q1 = [
    {
        "prompt": "What is 45 + 30",
        "answer": "75"
    },
    {
        "prompt": "When counting by tens, what comes just after 37?",
        "answer": "47"
    },
    {
        "prompt": "What is the smallest number out of (9,12,7,15)?",
        "answer": "7"
    },
    {
        "prompt": "What is the greatest number out of (55,58,52,49)?",
        "answer": "58"
    },
    {
        "prompt": "Type the missing number in this pattern (1,3,5,7,  ,11,13)",
        "answer": "9"
    },
    {
        "prompt": "What sign goes here [39 () 12]? \n            (<,>, or =)",
        "answer": ">"
    }
]
q2 = [
    {
        "prompt": "Write this number in standard form (500 + 20 + 7)",
        "answer": "527"
    },
    {
        "prompt": "What number makes the following equation true? \n    [__ + 4 = 46 - 7]",
        "answer": "35"
    },
    {
        "prompt": "What is 808 rounded to the nearest ten?",
        "answer": "810"
    },
    {
        "prompt": "If Ava has a quarter and 2 dimes, what is the value of what she has in cents?",
        "answer": "45"
    },
    {
        "prompt": "How many sides does a stop sign have?",
        "answer": "8"
    },
    {
        "prompt": "What is the missing number in the following equation? \n  () () ()\n+  1  1  1\n----------\n   2  7  9",
        "answer": "168"
    }
]
q3 = [
    {
        "prompt": "What is 2 x 7?",
        "answer": "14"
    },
    {
        "prompt": "What is 9 x 100?",
        "answer": "900"
    },
    {
        "prompt": "What is the missing number in the following equation? \n     5  2  9\n+    7  7  6\n------------\n () () () ()",
        "answer": "1305"
    },
    {
        "prompt": "Find the mean of these numbers (9,5,7,4,3,8)",
        "answer": "6"
    },
    {
        "prompt": "Find the median of these numbers (17,15,13,18,11,19)",
        "answer": "16"
    },
    {
        "prompt": "What is the remainder of 33 ÷ 14?",
        "answer": "5"
    }
]
q4 = [
    {
        "prompt": "What is the greatest common factor of 8, 12, and 20?",
        "answer": "4"
    },
    {
        "prompt": "What is the least common multiple of 6, 8, and 12?",
        "answer": "24"
    },
    {
        "prompt": "What is 3.6 - 1.3",
        "answer": "2.3"
    },
    {
        "prompt": "Convert 3 2/3 to an improper fraction",
        "answer": "11/3"
    },
    {
        "prompt": "Solve this equation: (62 ÷ 2 - 3) x 3 + 6 =",
        "answer": "90"
    },
    {
        "prompt": "What sign goes here [5/3 () 7/6]? \n            (<,>, or =)",
        "answer": ">"
    }
]
q5 = [
    {
        "prompt": "How many minutes is 7 hours and 24 minutes?",
        "answer": "444"
    },
    {
        "prompt": "What is the volume of a rectangular prism with sid lengths of 7, 3, and 4?",
        "answer": "48"
    },
    {
        "prompt": "Wishy Washy Car Wash washes 92 cars per day, and they make $15 per car washed."
                  "\nHow much money(in dollars) will they have made in 4 days?",
        "answer": "5520"
    },
    {
        "prompt": "A jug has 2.6kg of laundry detergent, and Jason uses 65g of detergent for each wash."
                  "\nHow many washes can Jason do before he uses all the detergent?",
        "answer": "40"
    },
    {
        "prompt": "A stack of 40 boxes is 8ft tall. How tall is the stack(in ft) if we take 5 boxes off the top?",
        "answer": "7"
    },
    {
        "prompt": "A hot dog costs $1.35. How much change should Amy get if she pays with a $5 bill?",
        "answer": "3.65"
    }
]
q6 = [
    {
        "prompt": "What is 8^3?",
        "answer": "512"
    },
    {
        "prompt": "What percentage is 7/10?",
        "answer": "70"
    },
    {
        "prompt": "What is 400% of 40?",
        "answer": "160"
    },
    {
        "prompt": "What is 14 feet in inches?",
        "answer": "528"
    },
    {
        "prompt": "What is 4896 cm in meters?",
        "answer": "48.96"
    },
    {
        "prompt": "What is 6.233 X 10^4?",
        "answer": "623300"
    }
]
q7 = [
    {
        "prompt": "If x = 11, what is x + 4?",
        "answer": "15"
    },
    {
        "prompt": "If x = 8 and y = 10, what is 3x + 2y?",
        "answer": "44"
    },
    {
        "prompt": "What is the value of |-10 - (|4| + 1)|?",
        "answer": "15"
    },
    {
        "prompt": "What is 6 + (-4)?",
        "answer": "2"
    },
    {
        "prompt": "If m = -8, what is 9 - m?",
        "answer": "17"
    },
    {
        "prompt": "A boat sails 40 miles south and then 30 miles east.\nHow many miles away is the boat from its start point?",
        "answer": "50"
    }
]

qset = [q1,q2,q3,q4,q5,q6,q7]

# Run the quiz
playing = True
while playing:
    print("           Are you smarter than a 7th Grader?")
    print("               -----------RULES-----------")
    print("You will get 6 math questions from every grade level from 1-7")
    print("In order to reach the next level, you must score 5/6 or better")
    if input("\n \nAre you ready? (y/n): ").upper() == "Y":
        isAlive = True
        level = 1
        total = 0
        while isAlive and level < 8:
            print(f"\n\n               -----------LEVEL {level}-----------\n")
            score = run_quiz(qset[level - 1])
            total += score
            if score > 4:
                print(f"You passed with {score} correct answers")
                level += 1
            else:
                print(f"You failed with {score} correct answers")
                isAlive = False

        if level == 8:
            print(f"Congratulations, you completed the whole challenge!")
            print(f"Overall Score: {total}/42 ({(total/42)*100}%)")
        else:
            print(f"Nice try, you made it to Grade {level}")
            qa = level * 6
            print(f"Overall Score: {total}/{qa} ({(total/qa)*100}%)")

        playing = input("Would you like to play again? (y/n): ").upper() == "Y"

    else:
        playing = False