import Course

class Students:


    # constructor
    def __init__(self, name, dob, email, idnumber):
        # intialize person' (instance variables) to parameter values passed in
        self._name = name
        self._dob = dob
        self.__email = email #class private attribute, cannot be overwritten in subclass
        # by default information is public
        self._is_public = True 
        self._idnumber = idnumber
        self._enrolled_courses = set()
        self._credits = 0
    

    # getter and setters 
    def getName(self):
        return self._name
    

    def setName(self, new_name):
        self._name = new_name
    

    def getIsPublic(self):
        return self._is_public 
    

    def setIsPublic(self, is_public):
        ''' The is_public attribute can only be updated to a boolen value '''
        if type(is_public)==bool:
            self._is_public = is_public
        else:
            print("is_public must be True or False")


    def getDob(self):
        return self._dob
    

    def setDob(self, dob_str):
        self._dob = dob_str
    

    def getEmail(self):
        if self._is_public:
            return self.__email
        else:
            return "Email not available"
    

    def setEmail(self, email):
        self.__email = email
        

    def __str__(self):
        if self._is_public:
            return "Name: " +self._name+ " DOB: " +self._dob+ " Email: " +self.__email+ " Student ID #: " + str(self._idnumber)
        else: 
            return "No results returned."


    def __eq__(self,other_stud):
        if self._idnumber == other_stud._idnumber:
            return True
        return False

    def can_enroll(self,course_to_check):
        for course in self._enrolled_courses:
            if course.overlaps(course_to_check):
                return False
        return True

    def enroll(self,course):
        if self._credits < 18 and (self._credits + course.num_credits) <= 18:
            if course not in self._enrolled_courses and self.can_enroll(course):
                self._enrolled_courses.add(course)
                self._credits += course._num_credits
                return True
            else:
                return False
        else:
            return False

    
    def course_list(self):
        print("Student Schedule:")
        print("Credit count: " + str(self._credits))
        print("_________________________")
        for course in self._enrolled_courses:
            print(course)
            print("________________________")
