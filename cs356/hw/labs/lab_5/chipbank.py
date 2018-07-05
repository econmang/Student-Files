'''
Evan Conley & Kyle Calvert
Lab 4
Chipbank class representing a set of chips and money associated with them in a game of blackjack.
'''

class ChipBank:

    def __init__(self,amount):
        '''
        Constructor of a ChipBank class object.
        '''
        try:
            if amount > 0:
                self._balance = amount
                self._chip_amounts = {"black":0,"green":0,"red":0,"blue":0}
                self._chip_values = (("black",100), ("green",25), ("red", 5), ("blue", 1))
                self._should_log = True
            else:
                raise ValueError
        except ValueError:
            print("ChipBank Balance amount must be greater than 0.")

    def no_log(self):
        '''Sets a chipbank to not log transactions.'''
        self._should_log = False

    def log(self):
        '''Sets a chipbank to log transactions.'''
        self._should_log = True

    def withdraw(self,amount):
        '''
        Withdraws the specified amount from the chipbank balance and logs the difference, if the bank is set to log transactions
        '''
        try:
            if self._balance - amount >= 0:
                self.set_balance(self._balance - amount)
                return amount
            else:
                raise ValueError
        except ValueError:
            return self._balance

    def deposit(self,amount):
        '''
        Deposits the specified amount into the chipbank balance and logs the change, if the bank is set to log transactions.
        '''
        self.set_balance(self._balance + amount)
        return amount

    def get_balance(self):
        '''
        Returns the current balance of the chipbank
        '''
        return self._balance

    def _init_chip_amounts(self):
        '''Helper function to reset chip amounts'''
        chip_amounts = {}
        for chips in self._chip_values:
            chip_amounts[chips[0]] = 0
        return chip_amounts

    def count_chips(self, amount):
        """
        count chips for current balance
        :param amount: int
        :return: chip_amounts: dict
        """
        chip_amounts = self._init_chip_amounts()
        for i in range(0, len(self._chip_values)):
            chip_amounts[self._chip_values[i][0]] = amount // self._chip_values[i][1]
            amount %= self._chip_values[i][1]

        return chip_amounts

    def set_balance(self,amount):
        '''
        Setter that updates the chipbank's balance to amount
        '''
        self._balance = amount

    def __str__(self):
        '''
        Summarizes the chipbank in terms of its balance, and the chips required to make up this balance.
        '''
        output = ""
        chip_amounts = self.count_chips(self.get_balance())
        for chip in chip_amounts:
            output += "%d %ss, " % (chip_amounts[chip], chip)
        output = output[:-2]
        output = output + (" totaling: $%d" % (self.get_balance()))
        return output
