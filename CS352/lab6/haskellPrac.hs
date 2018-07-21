-- Evan Conley
-- CS Practice
import Data.List

lst = [("hello",201), ("running",423),("eating",908),("running",888)]

findID :: String -> [(String,Integer)] -> [Integer]
findID x y = snd (unzip(filter ((==x).fst) y))

tl = [((0,'~'),0),((0,'~'),1),((0,'~'),9),((1,'~'),1),((1,'~'),2),((1,'~'),6),((2,'~'),2),((2,'a'),3),((3,'~'),3),((3,'~'),4),((4,'~'),4),((4,'b'),5),((5,'~'),5),((5,'~'),8),((6,'~'),6),((6,'c'),7),((7,'~'),7),((7,'~'),8),((8,'~'),8),((8,'~'),1),((8,'~'),9),((9,'~'),9)]

-- in the following comments, assume the following has been defined
t = '~'

eClose :: [((Integer, Char), Integer)] -> [[Integer]]
eClose lst = eClose' (getStateList lst)
-- *Main> eClose tl
-- [[0,1,2,6,9],[1,2,6],[2],[3,4],[4],[5,8,1,2,6,9],[6],[7,8,1,2,6,9],[8,1,2,6,9],[9]]

-- getStateList -- return all state numbers in the NFA
-- assumes there is a transition of the form((s,t),s) for every state in the NFA
getStateList :: [((Integer, Char), Integer)] -> [Integer]
getStateList lst =  nub ([fst (fst u) | u <- lst])
-- *Main> getStateList tl
-- [0,1,2,3,4,5,6,7,8,9]

-- call ec for each state in the input list
eClose' :: [Integer] -> [[Integer]]
eClose' states = [ec u | u <- states]
-- I used a list comprehension
-- *Main> eClose' [0 .. 9]
-- [[0,1,2,6,9],[1,2,6],[2],[3,4],[4],[5,8,1,2,6,9],[6],[7,8,1,2,6,9],[8,1,2,6,9],[9]]

-- get epsilon transitions for each state in the list by calling eTransFor
-- returns one epsilon closure -- The example call above produces the e-closure for state 0:
-- ec :: Integer -> [Integer]
ec stateNum =  (ecTargs(concat [(eTransFor (snd u)) | u <- (eTransFor stateNum)]))
-- *Main> ec 0
--[0,1,2,6,9]

-- Walks the list produced by the call to peelTargetStates
-- makes a mutually recursive call back to ec
-------------------------------------------callEC :: [Integer] -> [Integer]
-- *Main> callEC [1,9]
-- [1,2,6,9]

-- get all target states from a list
peelTargetStates :: Integer -> [((Integer, Char), Integer)] -> [Integer]
peelTargetStates state lst = [snd u | u <- lst, snd u /= state && fst (fst u) == state]
-- *Main> peelTargetStates 0 [((0,'~'),0),((0,'~'),1),((0,'~'),9)]
-- [1,9]

ecTargs :: [((Integer,Char),Integer)] -> [Integer]
ecTargs lst = nub [snd u | u <- lst]

-- all epsilon transitions out of s
eTransFor :: Integer -> [((Integer, Char), Integer)]
eTransFor state = [u | u <- tl, fst (fst u) == state && snd (fst u) == t]
-- *Main> eTransFor 0
-- [((0,'~'),0),((0,'~'),1),((0,'~'),9)]
