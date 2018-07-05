'''Takes in number from 0-99 and returns'''
def roman(num):
    if num < 0:
        return "Incorrect input"
    elif num > 99:
        return "Incorrect input"
    elif num == 0:
        return "nulla"
    elif num >= 50:
        if num == 50:
            return "L"
        else:
            return "L" + roman(num-50)
    elif num >=10:
        if num == 10:
            return "X"
        else:
            return "X" + roman(num-10)
    elif num >= 5:
        if num == 5:
            return "V"
        else:
            return "V" + roman(num-5)
    elif num >= 1:
        if num == 1:
            return "I"
        else:
            return "I" + roman(num-1)

print(roman(4))
print(roman(7))
print(roman(17))
print(roman(77))
