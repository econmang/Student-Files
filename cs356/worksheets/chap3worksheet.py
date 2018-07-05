"""
Implementation of Chapter 3 Worksheet
Try to write out questions about outputs as you go along
"""

#Problem 1
a = 27
b = 23
x = a - b
print("Expected result: 4")
print("Actual result",x)

#Problem 2
a = 27
b = 23

b = a
x = a - b
print("Expected result: 0")
print("Actual result",x)

#Problem 3
a = 2**8
b = 2
x = a * b
print("Expected result: 512")
print("Actual result",x)

#Problem 4
a = 2*8
b = 8**2
x = a-b
print("Expected result: -48")
print("Actual result",x)

#Problem 5
a = 13
b = 10

x = a % b
print("Expected result: 3")
print("Actual result",x)

#Problem 6
mike = 11
bob = 10
x = mike % bob
print("Expected result: 1")
print("Actual result",x)

#Problem 7
a = 5
b = 8
x = (a >= b)
print("Expected result: False")
print("Actual result",x)

#Problem 8
a = 5
b = 5
x = (a == b)
print("Expected result: True")
print("Actual result",x)

#Problem 9
x = 12
y = 2

x = x // y
print("Expected result: 6")
print("Actual result", x)

#Problem 10
x = 3
y = 3
x = (x != y)
print("Expected result: False")
print("Actual result",x)

#Problem 11
name = "Peter Parker"
x = name[0:5]
print("Expected result: Peter")
print("Actual result", x)

#Problem 12
name = "Norman Osborn"
x = name[0:5] + name[5:]
print("Expected result: Norman Osborn")
print("Actual result", x)

#Problem 13.
greeting = "Hello there!"
greeting * 3
x = greeting
print("Expected result: Hello there!")
print("Actual result", x)

#Problem 14.
a = "Hey"
yelling = a.upper()
x = yelling
print("Expected result: HEY")
print("Actual result", x)

#Problem 15.
a = "Hey"
x = a.capitalize()
print("Expected result: Hey")
print("Actual result", x)

#Problem 16.
a = "    Hello there.    "
a.strip()
x = a
print("Expected output:    Hello there.     ")
print("Actual output", x)

#Problem 17.
y = 13
x = y < 22
print("Expected output: True")
print("Actual output", x)

#Problem 18.
y = 13
x = y < 22 and y > 10
print("Expected output: True")
print("Actual result", x)

#Problem 19.
x = "race"
x = "car" + x
print("Expected output: carrace")
print("Actual result", x)

#Problem 20.
x = True and False
print("Expected output: False")
print("Actual result", x)


