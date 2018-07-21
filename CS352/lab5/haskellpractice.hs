doubleMe x = x + x
doubleUs x y = doubleMe x + doubleMe y
doubleSmallNumber x = if x > 100
					then x
					else x*2

conanO'Brien = "It's a-me, Conan O' Brien!"

list_prac = [((1,2),(3,4)),((5,6),(6,7))]

taco x = [ a | a <- list_prac, fst (fst a) == x]