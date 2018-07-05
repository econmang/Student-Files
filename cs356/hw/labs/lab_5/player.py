'''
Evan Conley
Lab 5
Player class will represent a general player of the game of blackjack
'''

import sys

class Player:

    player_options = {
    'q' : 'quit',
    'h' : 'hit',
    's' : 'stay',
    'c' : 'check dealer cards',
    'd' : 'look down at your cards'
    }

    def __init__(self,chipBank):
        self._chips = chipBank
        self._hand = []
        self._hit_flag = False
        self._stay_flag = False
        self._check_flag = False

    def signal(self,action):
        if action == 'q':
            self.quit()
            return True
        elif action == 'h':
            self.set_hit()
            return True
        elif action == 's':
            self.set_stay()
            return True
        elif action == 'l':
            self.options()
            return True
        elif action == 'c':
            self.set_check()
            return True
        elif action == 'd':
            print("Your Hand:")
            self.look_down()
            return True
        else:
            print("Invalid action")
            return False

    def quit(self):
        print("Thanks for trying out the game!\nGoodbye!")
        sys.exit()

    def get_hit(self):
        return self._hit_flag

    def set_hit(self):
        print("Hitting...")
        self._hit_flag = True

    def get_stay(self):
        return self._stay_flag

    def set_stay(self):
        print("Staying...")
        self._stay_flag = True

    def get_check(self):
        return self._check_flag

    def set_check(self):
        print("Dealer's Hand:")
        self._check_flag = True

    def options(self):
        for option in Player.player_options:
            print("%s  :  %s" % (option, Player.player_options[option]))

    def get_chips(self):
        return self._chips

    def take_card(self,card):
        self._hand.append(card)

    def look_down(self):
        for card_pulled in self._hand:
            print(card_pulled)
        print("Totaling:")
        print(self.add_up())
    
    def add_up(self):
        total = 0
        for card_pulled in self._hand:
            if card_pulled._is_face_up:
                total += card_pulled.get_value()
        return total

    def instant_win_check(self):
        if self.add_up() == 21:
            return True

    def bust(self):
        if self.add_up() > 21:
            return True

    def get_winnings(self, amount):
        print("Adding $%d to you chip bank!" % (amount))
        self.get_chips().deposit(amount)

    def reset(self):
        self._hand = []

    def show_chips(self):
        print("Current chip balance:")
        print(self.get_chips())
