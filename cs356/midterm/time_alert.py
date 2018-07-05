'''
Evan Conley
Prof. Vanderberg
CS 356
5/7/18

Part I: Specifying Requirements

    Problem Statement: Create a program that will identify a time to set an alert for a user given the time of an event and how many minutes prior
                       the user wishes to be alerted.

    Requirements: 
                    - The program shall take a time formatted as a String as input.
                    - The program shall take the number of minutes prior to an event as input.
                    - The program shall return the time that an alert should be set to inform a user a certain number of minutes prior to a specified event time.

    Assumptions:
                    - The program will take input of the form HH:MM AM/PM.
                    - The program will return the time of to set the alert in the form HH:MM AM/PM for readability
                    - The program will assume that minutes before is a positive integer number between 0 and 60.
                    - The program expects zeroes in tens place if number less than 10. Example 6:45 should be enter 06:45

    Constraints:
                    - The program does not take user input (uses only hardcoded values)
                    - The program does not have means to set an alert

Part II: Planning/Designing

    After consideration, decided to create a helper function that will be called by the alert finder function. This will help to autoformat each input type
    into military time, as that is easier to work with. Also, it will make the alert finder function a little cleaner as well.

    Funcion Specifications:
                    - time_formatter(time_string)
                        * time_string: String representing the time to be formatted to military time.
                        * Should return the time_string formatted in military time

                    - alert_finder(time, minutes_before):
                        * time: String of the time to be formatted and then utilized to find the necessary alert time.
                        * minutes_before: Integer representing how many minutes before the user wishes to reminded of the event."
                        * Should return time to set an alert for specified minutes before an event.

Part III: Implementation and Testing
'''
import datetime
import sys

def time_formatter(time_string):
    '''Returns the military time equivalent of the time_string String value entered as input.'''
    time_string = time_string.strip()
    try:
        AM_or_PM = time_string[-2:]
        time = time_string[:-2].strip()
        hour = int(time[0:2])
        if (hour == 12):
            hour = 0
        if (AM_or_PM == "PM"):
            hour += 12
        hour_string = str(hour)
        military_time = hour_string + time[2:]
        return military_time
    except:
        print("Incorrectly formatted time string")
        sys.exit()


def alert_finder(time, minutes_before):
    '''Returns the time to set an alarm based on the time of a event and the desired minutes before the event to be alerted.'''
    new_time = time_formatter(time)
    hour_min = new_time.split(":")
    try:
        int(minutes_before)
        if minutes_before < 0 or minutes_before > 60:
            raise ValueError
        if (int(hour_min[1]) - minutes_before) < 0:
            hour_min[0] = str(int(hour_min[0]) - 1)
            hour_min[1] = str(60 - minutes_before)
        else:
            hour_min[1] = str(int(hour_min[1]) - minutes_before)
        if int(hour_min[1]) < 10:
            hour_min[1] = "0" + hour_min[1]
        if int(hour_min[0]) > 12:
            hour_min[0] = str(int(hour_min[0]) - 12)
            ending = "PM"
            alert_time = hour_min[0] + ":" + hour_min[1] + " " + ending
            return alert_time
        else:
            ending = "AM"
            alert_time = hour_min[0] + ":" + hour_min[1] + " " + ending
            return alert_time
    except:
        print("Unexpected Formatting Error")


def main():
    print(time_formatter("12:45 AM")) #Expected output 0:45
    print(alert_finder("06:45 PM", 56)) #Expected ouptut 5:45 PM


if __name__ == '__main__':
    main()


'''
Reflection and Refactoring:
    Apologies, cutting close on time. I think this went alright; I got to learn a bit about formatting time strings and using the datetime and sys modules.
    As to refactoring ideas, though, I believe user input would be a good addition to this and would make it more useful. Also, I think I could have handled specific exceptions to
    catch. This would make errors more informative to the user. Also, I'm sure there is a more elegant means of constructing the output time other than the if/else block of mess I
    created. A final thought is that I restricted the minutes_before time pretty heavily. I could see extending this time so that users are
    not expected to only input time between 0 and 60 minutes before an event. That being said, it did pass the test cases, and I'm relatively happy with the solution.

Impromtu Extra Credit:
    Normally I utilize Stack Overflow and python.org and did so today as well.

    Thanks for the midterm, hope you have a good day!
'''
