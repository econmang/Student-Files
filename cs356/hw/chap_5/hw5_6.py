def second_highest(a,b,c):
    list_num = [a,b,c]
    list_num.remove(max(list_num))
    return max(list_num)

print(second_highest(900.5,1000,65))
print("Should be: 900.5")
print(second_highest(333,36,43))
print("Should be: 43")
print(second_highest(12,2,8))
print("Should be: 8")



#Better solution
#def second_highest(numone,numtwo,numthree):
    #return max(min(numone,numtwo), min(numtwo, numthree), min(numone, numthree))
