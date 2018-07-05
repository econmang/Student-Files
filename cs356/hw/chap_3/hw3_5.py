quit = 0

print("Welcome, enter a number and I'll tell you your grade, or enter \'q\' to quit.")
while not quit:
    user_in = input("User input: ")
    if user_in == "q":
        print("Thank you for trying the grade calculator!")
        quit = 1
    else:
        try:
            num_grade = float(user_in)
            if(num_grade < 0):
                print("ERROR: Number must be 0 or greater")
            elif (num_grade >= 0 and num_grade < 60):
                print("A",num_grade,"gives you an F. :(")
            elif (num_grade >= 0 and num_grade < 70):
                print("A", num_grade,"gives you a D.")
            elif (num_grade >= 70 and num_grade <80):
                print("A", num_grade,"gives you a C.")
            elif (num_grade >= 80 and num_grade <90):
                print("A", num_grade, "gives you a B.")
            elif (num_grade >= 90 and num_grade <=100):
                print("A", num_grade, "gives you an A.")
            elif(num_grade > 100):
                print("Oh, did you get extra credit? You A++ student, you. :)")
        except ValueError:
            print("ERROR: Enter a valid input of a number or \'q\'.")
