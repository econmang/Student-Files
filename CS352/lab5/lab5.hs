{-|
	Evan Conley
	Professor Nordquist
	CS 352
	Lab 5
-}

days = ["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"]
weekday x = 	if x > 0 && x < 8
				then
				days !! (x-1)
				else show x ++ " is not a legal day"

maxOfTwoLists x y =  max (maximum x) (maximum y)

weekday' x = if x > 0 && x < 8
				then weekday x
				else if x <= 0
						then weekday' (x+7)
						else if x > 7
								then weekday' (x-7)
								else "not a valid input"

tl = [((0,'~'), (9)),((0,'~'),(1)),((1,'~'),(2)),((1,'~'),(6)),((6,'c'),(7)),((7,'~'),(8)),((2,'a'),(3)),((3,'~'),(4)),((4,'b'),(5)),((5,'~'),(8)),((8,'~'),(9)),((8,'~'),(0))]

transitionsFor s l = [ a | a <- l, fst (fst a) == s]