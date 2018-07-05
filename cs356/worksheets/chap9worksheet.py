class Mutant:
    
    def __init__(self):
        self._identity = ""
        self._powers = []

    @property
    def identity(self):
        return self._identity

    @identity.setter
    def identity(self,x):
        self._identity = x

    @property
    def powers(self):
        return self._powers

    @powers.setter
    def powers(self, x):
        self._powers = x

wolverine = Mutant()
wolverine.identity = "James Howlett"
wolverine.powers = ["Healing Factor", "Retractable Bone Claws", "Enhanced Senses"]

cyclops = Mutant()
cyclops.identity = "Scott Summers"
cyclops.powers = ["Project concussive force from his eyes"]

gambit = Mutant()
gambit.identity = "Remy LeBeau"
gambit.powers = ["Explosive Kinetic Energy","Enhanced Agility","Hypnotic Charm"]

x = cyclops.identity 
print(x) #Expected output: Scott Summers
 
wolverine.powers[1] = "Adamantium Claws"
x = wolverine.powers
print(x) #Expected output: ["Healing Factor","Adamantium Claws","Enhanced Senses"]

cyclops.powers = "Laser Eyes"
x = cyclops.powers[0]
print(x) #Expect output "L" (indexing string Laser Eyes like a list)

professorX = Mutant()
professorX.identity = "Charlex Francis Xavier"
x = professorX.powers
print(x) #Expected output: []

x = cyclops.powers
del(cyclops)
print(x) #Expected output: "Laser Eyes"

gambit.powers[0] = gambit.powers[1]
gambit.powers[2] = gambit.powers[0]
x = gambit.powers
print(x) #Expected Output ["Enhanced Agility","Enhanced Agility","Enhanced Agility"]

x = gambit.powers.sort()
print(x) # Expected output: (should be same as problem above)
# Ah, I was incorrect. It gets the return of sort(), which returns nothing.
# So, x gets a value of None

#storm = Mutant()
#storm.identity = "Ororo Monroe"
#storm.powers("Weather manipulation")
#EXPECTED TYPERROR AT THIS LINE
#Ha, I was correct!
#x = storm.powers[0]

x = gambit.identity
print(x) #Expected Output: Remy LeBeau

wolverine.identity = "Hugh Jackman"
x = wolverine.identity
print(x)
#Expected Output: Hugh Jackman

x = isinstance(wolverine,Mutant)
print(x) #Expected out: True

x = gambit is wolverine
print(x) #Expected out: False

try:
    x = gambit.powers[3]
except IndexError:
    print("Index out of range.")
#Expected output: Index out of range

#try:
#    x = cyclops.identity
#except AttributeError:
#    print("Attribute undefined")
#EXPECTED ERROR AT THIS LINE
#Cyclops was deleted from scope


class MutantTracker:
    count = 0
    def __init__(self):
        MutantTracker.count += 1

    @classmethod
    def reset_count(cls):
        cls.count = 0

t1 = MutantTracker()
t2 = MutantTracker()
x = t1.count
print(x) #Expected output: 2

t1 = MutantTracker()
t1.reset_count
t2 = MutantTracker()
x = t2.count
print(x) #Expected output: 4

class Automobile:

    def is_mobile(self):
        return True

class SportsCar(Automobile):
    def __init__(self,top_speed):
        self.top_speed = top_speed

    def is_sports_car(self):
        if self.top_speed > 176:
            return True
        else:
            return "Not Quite"

class Porsche(SportsCar):
    pass

cayman = Porsche(175)
x = cayman.is_sports_car()
print(x) #Expected output "Not Quite"


gt3 = Porsche(195)
x = gt3.is_sports_car()
print(x) #Expected output True

malibu = Automobile()
x = malibu.is_mobile()
print(x) #Expected: True

#malibu = Automobile()
#x = malibu.is_sports_car()
#EXPECTED ERROR HERE
#parent class has not is_sports_car method
