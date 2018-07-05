def get_last_digit(num):
    if num < 0:
        num = -1 * num
    if num > 9:
        num = int(repr(num)[-1])
        return num
    else:
        return num

def same_last_digit(a,b,c):
    new_a = get_last_digit(a)
    new_b = get_last_digit(b)
    new_c = get_last_digit(c)

    if new_a == new_b == new_c:
        return True
    else:
        return False

print(same_last_digit(2,142,262))
print("Should be True")

print(same_last_digit(333,36,262))
print("Should be False")

print(same_last_digit(41,1,21))
print("Should be True")
