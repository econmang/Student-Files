'''
Evan Conley
Lab 5
Dealer Class will represent the actions of the dealer in blackjack.
Inherits from the player class
'''

import player
import random
from card import Card

class Dealer(player.Player):

    def __init__(self):
        self._hand = []

    def first_deal(self,player):
        player.take_card(Card(random.randint(0,51)))
        player.take_card(Card(random.randint(0,51)))

        self.take_card(Card(random.randint(0,51)))
        self.take_card(Card(random.randint(0,51)))

        self._hand[1].face_down()

    def react(self,player):
        if player.get_hit():
            new_card = Card(random.randint(0,51))
            if new_card.get_rank() == "Ace" and player.add_up() + 11 > 21:
                new_card.set_value(1)
            player.take_card(new_card)
            player._hit_flag = False
            if player.instant_win_check():
                return True
            elif player.bust():
                return True
            return False
        elif player.get_stay():
            player._stay_flag = False
            return True
        elif player.get_check():
            self.look_down()
            player._check_flag = False
            return False
        else:
            return False
