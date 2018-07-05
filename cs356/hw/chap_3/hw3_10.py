quit = 0

print("Welcome, enter the hours, minutes, and seconds from midnight")
while not quit:
    try:
        hours = int(input("\nEnter hours: "))
        if (hours < 0 or hours >= 24):
            while (hours < 0 or hours >= 24):
                print("ERROR: Hours must be within [0-24) range.")
                hours = int(input("Enter hours: "))

        minutes = int(input("\nEnter minutes: "))
        if (minutes < 0 or minutes >= 60):
            while (minutes < 0 or minutes >= 60):
                print("ERROR: Minutes must be within [0-60) range.")
                minutes = int(input("Enter minutes:"))

        seconds = int(input("\nEnter seconds: "))
        if (seconds < 0 or seconds >= 60):
            while (seconds < 0 or seconds >= 60):
                print("ERROR: Seconds must be within [0,60) range.")
                seconds = int(input("Enter seconds: "))

        hours_secs = hours * 60 * 60
        minutes_secs = minutes * 60
        secs = seconds

        total_secs = hours_secs + minutes_secs + secs
        print("Total seconds from midnight:")
        print(total_secs)

        ans = 0
        while not ans:
            user_in = input("\nWould you like to try again? (y/n): ")
            if user_in == "y":
                print("\nAwesome, let's try again!")
                ans = 1
            elif user_in == "n":
                print("\nThanks for trying the seconds from midnight calculator!")
                ans = 1
                quit = 1
            else:
                print("\nPlease just enter a \'y\' or a \'n\'")

                
    except ValueError:
        print("ERROR: Enter a valid number for hours, minutes, and seconds.")
        ans = 0
        while not ans:
            user_in = input("\nWould you like to quit? (y/n): ")
            if user_in == "y":
                print("\nThanks for giving the seconds from midnight calculator a try!")
                ans = 1
                quit = 1
            elif user_in == "n":
                print("\nAwesome, let's try again")
                ans = 1
            else:
                print("\nPlease just enter a \'y\' or a \'n\'")
