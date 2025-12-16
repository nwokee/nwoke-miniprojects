import random
import time
print("Blackjack\n\n")


    
playing = True
cards = [2,3,4,5,6,7,8,9,10,10,10,10,11]
names = ["Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"]
user = 0
comp = 0
userW = 0
compW = 0

while playing:
    if (userW + compW) == 0:
        print("-----------BLACKJACK RULES-----------")
        print("- Type 'hit' to get a new card")
        print("- The card will add to your total score")
        print("- Once happy with your score type 'stand'")
        print("- Get as close to 21 without going over")
        print("- The computer will go after you")
        print("- Winner is the player closest to 21")
        print("\n   (face cards are 10, aces are 1s or 11s)   \n\n")
    user = 0
    comp = 0
    
    hasAce = False
    usedAce = False
    canhit = True
    cch = True
    bust = False
    while canhit:
        if user == 0:
            choice = "hit"
        else:
            choice = input("hit or stand?: ")
        if choice != "hit" and choice != "stand":
            print("You didn't type either, try again, ", end = " ")
        elif choice == "hit":
            cidx = random.randint(0,12)
            print("Card you got:", names[cidx])
            if cidx == 12 and not hasAce:
                hasAce = True
                user += cards[cidx]
            elif cidx == 12 and hasAce:
                user += 1
                usedAce = True
            else:
                user += cards[cidx]
            if user == 21:
                print("BLACKJACK! Computer's turn now")
                canhit = False
            elif user > 21:
                if not hasAce or (hasAce and usedAce):
                    print("BUST! You Lose!")
                    canhit = False
                    bust = True
                elif hasAce:
                    user -= 10
                    usedAce = True
            print("Score:", user, "\n")
        else:
            print("STANDING at %s" %(user))
            canhit = False
    
    if not bust:
        print("Computer's Turn...")
        time.sleep(3)
        compCards = []
        hasAce = False
        usedAce = False
        while cch:
            if (comp < 17) and (comp < user):
                cidx = random.randint(0,12)
                compCards.append(names[cidx])
                if cidx == 12 and not hasAce:
                    hasAce = True
                    comp += cards[cidx]
                elif cidx == 12 and hasAce:
                    comp += 1
                    usedAce = True
                else:
                    comp += cards[cidx]
            elif comp < 22:
                cch = False
                print("Computer got a score of %s" %comp, compCards)
                if comp > user:
                    print("Computer Wins!")
                    compW += 1
                elif comp == user:
                    print("Tie")
                else:
                    print("You win!")
                    userW += 1
            else:
                print("Computer busted at %s!" %comp, compCards)
                cch = False
                print("You win!")
                userW += 1
    else:
        print("Computer Wins!")
        compW += 1
                    
    
    
    print("current score: (User)%s - %s(Computer)" %(userW, compW))
    rerun = False
    while not rerun:
        pagain = input("\nplay again? (y or n): ")
        if pagain != "y" and pagain != "n":
            print("You didn't type either, try again, ", end = " ")
        elif pagain == "n":
            playing = False
            rerun = True
        else:
            rerun = True




print("FINAL SCORE: (User)%s - %s(Computer)" %(userW, compW))
    
    
