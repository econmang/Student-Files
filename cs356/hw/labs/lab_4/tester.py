from card import Card
from chipbank import ChipBank


# If you edit or change the test code below, you must justify your change by # providing a reason via comments.

import random

if __name__ == "__main__":
    # Lets make a deck of cards
    deck = []
    for i in range(52):
        my_card = Card(i)
        deck.append(my_card)
        # flip over each card
        my_card.face_up()
        # print each card as we add them
        print(my_card)  

    # print a random card from the deck
    print(random.choice(deck)) 

    # In my implementation, card number 37 is the queen of clubs. 
    # Yours may be different.
    card = Card(37)
    print(card)
    # Queen of Clubs
    print(card.get_value())
    # 10
    print(card.get_suit())
    # Clubs
    print(card.get_rank())
    # Queen
    card.face_down()
    print(card)
    # <facedown>
    card.face_up()
    print(card)
    # Queen of Clubs
    cs = ChipBank(149)
    print(cs)
    # 1 blacks, 1 greens, 4 reds, 4 blues - totaling $149
    cs.deposit(7)
    print(cs.get_balance())
    # 156
    print(cs)
    # 1 blacks, 2 greens, 1 reds, 1 blues - totaling $156
    print(cs.withdraw(84))
    # 84
    print(cs)
    # 0 blacks, 2 greens, 4 reds, 2 blues - totaling $72
    cs.deposit(120)
    print(cs)
    # 1 blacks, 3 greens, 3 reds, 2 blues - totaling $192
    print(cs.withdraw(300))
    # 192

    #Addition Testing:
    #Testing control of banklog
    cs.no_log()
    cs.withdraw(2)
    cs.deposit(14)
    cs.log()
    cs.withdraw(14)
    cs.deposit(2)
