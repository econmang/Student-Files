class Course():
    
    
    ''' A course is defined by its name, number of credits, and when
        its offered '''
    def __init__(self, name, num_credits, days, start_time, end_time):
        self._name = name
        self._num_credits = num_credits
        self._days = days  # needed to determine if times overlap
        self._start_time = start_time
        self._end_time = end_time


    @property
    def name(self):
        return self._name
    @name.setter
    def name(self, updated_name):
        self._name = updated_name


    @property
    def num_credits(self):
        return self._num_credits
    @num_credits.setter
    def num_credits(self,num):
        self._num_credits = num


    @property
    def days(self):
        return self._days
    @days.setter
    def days(self,times):
        self._days = times


    @property
    def start_time(self):
        return self._start_time
    @start_time.setter
    def start_time(self,start):
        self._start_time = start


    @property
    def end_time(self):
        return self._end_time
    @end_time.setter
    def end_time(self,new_end):
        self._end_time = new_end


    # should also have getters and setters for other instance variables

    # public overlaps function
    # uses two helper functions to determine if course times overlap
    # courseA.overlaps(courseB)
    def overlaps(self, other):
        ''' checks if days overlap, if so its checks times'''
        # if days overlap, check times
        if self._daysOverlap(other):
            return self._timesOverlap(other)
        else:
            return False


    # returns True if days overlap
    def _daysOverlap(self, other):
        ''' Assumes days are initialized to a set'''
        #if self._days.intersection(other._days):
        #    return True
        #else:
        #    return False
        return self._days.intersection(other._days)


    # return True is new course time (other) conflicts with 
    # exisiting course time (self)
    def _timesOverlap(self,other):
        ''' Compares start and end times of two Course objects
            to determin if the times overlap. Should only be called
            if the days overlap.'''
        # compare all times using minutes since midnight
        # self_start = self._getMinutes(self._start_time)
        self_start = self._getMinutes(self._start_time)
        self_end = self._getMinutes(self._end_time)
        other_start = other._getMinutes(other._start_time)
        other_end = other._getMinutes(other._end_time)
        
        # bad start time
        # if start of other falls between start and end of self
        if other_start >= self_start and other_start <= self_end:
        #if self.start <= other_start <=self_end:
            return True
         
        # bad end time
        # if end of other falls between start and end of self
        if other_end >= self_start and other_end <= self_end:
        # if self_start <= other_end <=self_end:
            return True
        
        # start and end look fine on thier own, but together cause problem
        # if other start time is less than self start time AND 
        # other end time is greater then self end
        if other_start <= self_start and other_end >= self_end:
            return True
        
        # no overlaps over times found
        return False

    
    def _getMinutes(self, time):
        ''' assumes timeString is given in 24 hour format HH:MM'''
        time_list = time.split(":")
        return int(time_list[0])*60 + int(time_list[1])


    def __str__(self):
        ''' prints course in a familiar format '''
        return self._name + " " + str(self._days) + " " + self._start_time +" " + self._end_time
