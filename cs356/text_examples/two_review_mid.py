def list_printer(alist):
    return ((alist[0]),(alist[len(alist)-1]),(alist[(len(alist)//2)]))

list_test_one = [1,2,3,4,5,6]
list_test_two = [1,2,3,4,5]

print(list_printer(list_test_one))
print(list_printer(list_test_two))
