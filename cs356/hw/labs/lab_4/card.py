'''
Evan Conley & Kyle Calvert
Lab 4
Card Class representing a card object in a game of blackjack.
'''

class Card:

    deck_vals = [("2",2),("3",3),("4",4),("5",5),("6",6),("7",7),("8",8),("9",9),("Jack",10),("Queen",10),("King",10),("Ace",11)]

    def __init__(self,card_number):
        '''
        Constructor for Card class. Uses a unique identifying number to create a card in a 52 card deck.
        '''
        try:
            if card_number < 0:
                raise ValueError
            elif card_number < 12:
                self._card_suit = "Hearts"
                self._card_rank = Card.deck_vals[card_number][0]
                self._card_value = Card.deck_vals[card_number][1]
                self._is_face_up = True
            elif card_number < 25:
                self._card_suit = "Diamonds"
                self._card_rank = Card.deck_vals[card_number % 12][0]
                self._card_value = Card.deck_vals[card_number % 12][1]
                self._is_face_up = True
            elif card_number < 38:
                self._card_suit = "Clubs"
                self._card_rank = Card.deck_vals[card_number % 12][0]
                self._card_value = Card.deck_vals[card_number % 12][1]
                self._is_face_up = True
            elif card_number < 52:
                self._card_suit = "Spades"
                self._card_rank = Card.deck_vals[card_number % 12][0]
                self._card_value = Card.deck_vals[card_number % 12][1]
                self._is_face_up = True
            else:
                raise ValueError
        except ValueError:
            print("Card value must must be within range 1-52")
    
    def face_up(self):
        '''
        This is a setter to set the card to be facing up.
        '''
        self._is_face_up = True

    def face_down(self):
        '''
        This is a setter to set the card to be face down.
        '''
        self._is_face_up = False

    def get_suit(self):
        '''
        Returns value of the card suit.
        '''
        return self._card_suit

    def get_rank(self):
        '''
        Returns value of the card rank.
        '''
        return self._card_rank

    def get_value(self):
        '''
        Returns the value of the card value.
        '''
        return self._card_value

    def __str__(self):
        '''
        Returns string that summarizes the suit, rank and value of a card object.
        '''
        if self._is_face_up:
            return ("Card: %s of %s, Value: %d" % (self.get_rank(), self.get_suit(), self.get_value()))
        else:
            return "<facedown>"
