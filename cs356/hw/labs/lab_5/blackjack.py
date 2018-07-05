'''
Evan Conley
Lab 5
Game of blackjack to test out the full functionality of all classes created
'''

import chipbank
import card
import player
import dealer
import os
import time

print("Hello, Player! Welcome to text-based BlackJack!")

got_amount = False

while not got_amount:
    try:
        money_to_table = chipbank.ChipBank(int(input("Enter the amount of dollars you're bringing to the table: ")))
        if hasattr(money_to_table,"_balance"):
            you = player.Player(money_to_table)
            got_amount = True
    except ValueError:
        print("Must enter a number! Try again!")

dealer = dealer.Dealer()

print("\nLet's get playing!")

playing = True
reset = True
while playing:
    try:
        if you.get_chips().get_balance() == 0:
            print("Zero Dollars!?")
            print("Come back when you get some money, buddy!")
            playing == False
            break
        wager_request = input("\nWager this hand, or quit with 'q': ")
        if wager_request == 'q':
            print("Taking the money and running, huh?")
            playing = False
            break
        wager = int(wager_request)
        if wager < 0 or wager > you.get_chips().get_balance():
            raise ValueError
        you.get_chips().withdraw(wager)
        print("\nInitial Deal:")
        dealer.first_deal(you)
        you.signal('d')
    
        if you.instant_win_check():
            dealer._hand[1].face_up()
            if you.add_up() == dealer.add_up():
                print("Dealer also had 21.")
                print("Tie. You get half of your wager back.")
                you.get_winnings(wager // 2)
                you.show_chips()
            else:
                print("Dealer did not have 21!")
                print("Winner!")
                you.get_winnings(wager * 2)
                you.show_chips()
        else:
            print("\nActions:")
            you.signal('l')
            while not dealer.react(you):
                while not you.signal(input("What would you like to do? ")):
                    you.signal('l')
            
            if you.instant_win_check():
                dealer._hand[1].face_up()
                if you.add_up() == dealer.add_up():
                    print("Dealer also had 21.")
                    print("Tie. You get half of your wager back.")
                    get_winnings(wager // 2)
                else:
                    print("Dealer did not have 21!")
                    print("Winner!")
                    you.get_winnings(wager * 2)
                    you.show_chips()
            elif you.bust():
                print("Bust!\nYou lost your wager!")
                you.show_chips()
            else:
                print("\n\nDEALER'S TURN")
                dealer._hand[1].face_up()
                
                while dealer.add_up() <= 16:
                    time.sleep(1)
                    you.signal('c')
                    dealer.react(you)
                    dealer.signal('h')
                    if dealer.react(dealer):
                        time.sleep(1)
                        if dealer.add_up() > 21:
                            you.signal('c')
                            dealer.react(you)
                            print("")
                            print("Winner!")
                            you.get_winnings(wager * 2)
                            you.show_chips()
                        else:
                            you.signal('c')
                            dealer.react(you)
                            print("")
                            print("Lost!\nYou lose your wager!")
                            you.show_chips()
                time.sleep(1)
                if you.add_up() > dealer.add_up():
                    you.signal('c')
                    dealer.react(you)
                    print("")
                    print("Winner!")
                    you.get_winnings(wager * 2)
                    you.show_chips()
                elif you.add_up() == dealer.add_up():
                    you.signal('c')
                    dealer.react(you)
                    print("")
                    print("Tie: You get half you wager back.")
                    you.get_winnings(wager // 2)
                    you.show_chips()
                elif dealer.add_up() < 21 and you.add_up() < dealer.add_up():
                    you.signal('c')
                    dealer.react(you)
                    print("")
                    print("Lost!\nYou lose your wager!")
                    you.show_chips()
        you.reset()
        dealer.reset()
        try:
            play_again = input("Wanna play again (y/n)?  ")
            if play_again == 'y':
                clear_time = 3
                while clear_time:
                    mins = 0
                    secs = clear_time
                    timeformat = 'Clearing screen in {:02d}:{:02d}'.format(mins, secs)
                    print(timeformat, end='\r')
                    time.sleep(1)
                    clear_time -= 1
                os.system('cls' if os.name == 'nt' else 'clear')
                print("Next hand!\n")
            elif play_again == 'n':
                playing = False
                print("Thanks for playing!\nSee you soon!")
            else:
                raise RuntimeError
        except RuntimeError:
            print("That's not a 'y' or a 'n'.. I'm gonna assume you don't wanna play :(")
            playing = False
    except ValueError:
        print("\nMust be a positive valued integer, smaller than or equal to the amount of money you have.")
        print("Try again.\n")
