print("Problem 3-2")
print("Complementary Colors\n")

quit = False

while not quit:
    color = input("Enter a color:\n")
    color = color.strip().lower()
    if color == "red":
        print("The complementary color to red is: Green!")
    elif color == "green":
        print("The complementary color to green is: Red!")
    elif color == "yellow":
        print("The complementary color to yellow is: Violet!")
    elif color == "violet":
        print("The complementary color to violet is: Yellow!")
    elif color == "blue":
        print("The complementary color to blue is: Orange!")
    elif color == "orange":
        print("The complementary color to orange is: Blue!")
    else:
        print("ERROR: You did not enter a correct color.")

    answer = False
    response = input("Would you like to quit? (y/n)\n")
    while not answer:
        if response == "y":
            answer = True
            quit = True
            print("Thanks for trying!\n")
        elif response == "n":
            answer = True
            print("Let's go again!\n")
        else:
            print("ERROR: Invalid input; Would you like to quit?")
