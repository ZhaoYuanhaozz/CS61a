# Object Oriented Programming

class Fib():
    """A Fibonacci number.

    >>> start = Fib()
    >>> start
    0
    >>> start.next()
    1
    >>> start.next().next()
    1
    >>> start.next().next().next()
    2
    >>> start.next().next().next().next()
    3
    >>> start.next().next().next().next().next()
    5
    >>> start.next().next().next().next().next().next()
    8
    >>> start.next().next().next().next().next().next() # Ensure start isn't changed
    8
    """

    def __init__(self, value=0):
        self.value = value

    def next(self):
        "*** YOUR CODE HERE ***"
        if self.value == 0:
            result = Fib(1)
        else:
            result = Fib(self.value + self.previous)
        result.previous = self.value
        return result
    def __repr__(self):
        return str(self.value)

 
class VendingMachine:
    
    def __init__(self,goods, price):

        self.goods = goods
        self.price = price
        self.store_num = 0
        self.balance = 0

    def vend(self):
        if self.store_num == 0 :
            return 'Machine is out of stock'
        else:
            difference = self.balance - self.price
            if difference < 0 :
                return 'You must deposit ${0} more.'.format(-difference)
            if difference > 0:
                self.store_num = self.store_num - 1
                self.balance = 0

                return 'Here is your {0} and ${1} change'.format(self.goods,difference)
                
            if difference == 0:
                self.store_num = self.store_num - 1
                self.balance = 0
                return 'Here is your {0}.'.format(self.goods)
               
    
    def deposit(self,input_money):
        self.balance = input_money + self.balance
        if self.store_num == 0 :
            self.balance = 0
            return 'Machine is out of stock. Here is your ${0}'.format(input_money)
        else:
            return 'Current balance: ${0}'.format(self.balance)
        
    def restock(self, restock_num):
        self.store_num = restock_num + self.store_num
        return 'Current {0} stock: {1}'.format(self.goods, self.store_num)
    



   

