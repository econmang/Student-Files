from Student import *
from Course import *

cs210 = Course("CS210",4,{"T","Th"},"11:30","12:20")
cs122 = Course("CS122",4,{"M","W"}, "8:00","8:40")
cs122L = Course("CS122L",1,{"T"}, "12:00", "14:00")
mth341 = Course("MTH341",5,{"M","W","F"}, "8:30","9:20")
mth441 = Course("MTH441",4,{"M","W"}, "12:30","14:00")
mth490 = Course("MTH490",5,{"F"},"15:00","16:50")
cs360 = Course("CS360",3,{"T,Th"}, "16:30", "18:00")

evan = Student("Evan Conley","9/7/95","conleye@sou.edu","940433420")
dave = Student("Dave Smith", "8/24/97","smithd2@sou.edu","940422430")

print(evan.enroll(cs210)) #True - credit count: 4
print("Expected: TRUE")

print(evan.enroll(mth341)) #True - credit count: 9
print("Expected: TRUE")

print(evan.enroll(mth341)) #False - cannot enroll in duplicate course
print("Expected: FALSE")

print(evan.enroll(cs122)) #False - overlap with mth341
print("Expected: FALSE")

print(evan.enroll(mth441)) #True - credit count: 13
print("Expected: TRUE")

print(evan.enroll(mth490)) #True - credit count: 18
print("Expected: TRUE")

print(evan.enroll(cs360)) #False - credit count over limit
print("Expected: FALSE")


dave.enroll(mth490)
dave.enroll(cs360)
dave.enroll(cs210)

print("\n\n")
print(evan)
evan.course_list()

print("\n\n")
print(dave)
dave.course_list()
