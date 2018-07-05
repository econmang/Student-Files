"""
This is an implementation of chapter 4 worksheet
Try to find any strange outputs and ask questions
"""
#Problem 1
a = "Apricot"
x = len(a) *2
print("Expected Output: 14")
print("Actual Output:",x,"\n\n\n")

#Problem 2
a = "    arizona    "
x = a.strip().capitalize()
print("Expected Output: Arizona")
print("Actual Output:", x, "\n\n\n")

#Problem 3
a = True
b = False
x = b and a or a and b
print("Expected Output: False")
print("Actual Ouptut:",x,"\n\n\n")

#Problem 4
cats = 2
dogs = 13
cats += dogs
x = cats
print("Expected Output: 15")
print("Actual Output:",x,"\n\n\n")

#Problem 5
x = 16 - 4 * 3
print("Expected Output: 4")
print("Actual Output:",x,"\n\n\n")

#Problem 6
x = 10 + 2 * 5 + 3 / 2
print("Expected Output: 21.5")
print("Actual Output:",x,"\n\n\n")

#Problem 7
x = "here" or "there"
print("Expected Output: here")
print("Actual Output:", x, "\n\n\n")

#Probem 8
x =2
y = 8
x **=y
print("Expected Output: 256")
print("Actual Output:",x, "\n\n\n")

#Problem 9
x = 24 and 3600
print("Expected Output: 3600")
print("Actual Output:", x, "\n\n\n")

#Problem 10
fahrenheit = float(90)
celsius = (fahrenheit - 32.0) * 5.0 /9.0
print("Expected Output: 32.222222")
print("Actual Output:",celsius,"\n\n\n")

#Problem 11
a = True
b = False
x = a or b
print("Expected Output: True")
print("Actual Output:",x,"\n\n\n")

#Problem 12
x = "{2}{1}{0}".format(False, "s", 37)
print("Expected Output: 37sFalse")
print("Actual Output:",x,"\n\n\n")

#Problem 13
a = "hello THERE    "
x = a[0:5].upper()
x += a[5:].lower().strip()
print("Expected Output: HELLOthere")
print("Actual Output:",x,"\n\n\n")

#Problem 14 
a = 3.141567
x = round(a,2)
print("Expected Output: 3.14 3 3.14")
print("Actual Output:","%0.2f %i %g" % (a,a,x),"\n\n\n")

#Problem 15
y = [True, False, True, True]
x = y[1] and y [3]
print("Expected Output: False")
print("Actual Output:",x,"\n\n\n")

#Problem 16
x = len("snails" * 3)
print("Expected Output: 18")
print("Actual Output:",x,"\n\n\n")

#Problem 17
y = 8
if y % 2:
    x = "even"
else:
    x = "odd"
print("Expected Output: odd")
print("Actual Output:",x,"\n\n\n")

#Problem 18
x = "Disney Land" or 1776 and 34
print("Expected Output: Disney Land")
print("Actual Output:",x,"\n\n\n")

#Problem 19
x = 7
y = 2
x = x // y + 4
print("Expected Output: 7")
print("Actual Output:",x,"\n\n\n")

#Problem 20
y = 13
x = y % 2 + 5 // 2
print("Expected Output: 3")
print("Actual Output:",x,"\n\n\n")
