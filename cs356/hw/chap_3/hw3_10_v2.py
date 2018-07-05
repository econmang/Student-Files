quit = 0

print("Welcome, enter the hours, minutes, and seconds from midnight")
while not quit:
    try:
        hours = int(input("\nEnter hours: "))
        if (hours < 0):
            while (hours < 0):
                print("ERROR: Hours must be greater than 0.")
                hours = int(input("Enter hours: "))
        if (hours >= 24):
            print("Hours above or equal to 24. Applying modular arithmetic...")
            hours = hours % 24
            print("New hours value:", hours)
        minutes = int(input("\nEnter minutes: "))
        if (minutes < 0):
            while (minutes < 0):
                print("ERROR: Minutes must be greater than 0.")
                minutes = int(input("Enter minutes:"))
        if (minutes >= 60):
            print("Minutes above or equal to 60. Adding to hours and applying modular arithmetic...")
            hour_shift = minutes // 60
            minutes = minutes % 60
            hours = (hours + hour_shift) % 24
            print("New hours value:", hours)
            print("New minutes value:", minutes)
        seconds = int(input("\nEnter seconds: "))
        if (seconds < 0):
            while (seconds < 0):
                print("ERROR: Seconds must be greater than 0.")
                seconds = int(input("Enter seconds: "))
        if (seconds >= 60):
            print("Seconds above or equal to 60. Adding to minutes and applying modular arithmetic...")
            minute_shift = seconds // 60
            seconds = seconds % 60
            minutes += minute_shift
            if(minutes >= 60):
                print("Minutes now above specified range. Adding to hours and applying modular arithmetic...")
                hour_shift = minutes // 60
                minutes = minutes % 60
                hours += hour_shift
                if (hours >= 24):
                    print("Hours now above specified range. Applying modular arithmetic...")
                    hours = hours % 24
                print("New hours value:", hours)
                print("New minutes value:", minutes)
                print("New seconds value:", seconds)
            else:
                print("New minutes value:", minutes)
                print("New seconds value:", seconds)
            

        hours_secs = hours * 60 * 60
        minutes_secs = minutes * 60
        secs = seconds

        total_secs = hours_secs + minutes_secs + secs
        print("\nTotal seconds from midnight:")
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
