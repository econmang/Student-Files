{-|
	Evan Conley
	Professor Nordquist
	CS 352
	2/27/16
-}
import Data.List

cartProd :: [String] -> [String] -> [String]
cartProd a b = [first ++ " " ++ second | first <- a, second <-b]

findID :: String -> [(String,Integer)] -> [Integer]
findID x y = snd (unzip(filter ((==x).fst) y))

findID' :: String -> [(String,Integer)] -> [Integer]
findID' idLookup names = [snd(u) | u <- names, idLookup == fst(u)]

tl :: [((Integer,Char),Integer)]
tl = [((0,'~'),0),((0,'~'),1),((0,'~'),9),((1,'~'),1),((1,'~'),2),((1,'~'),6),((2,'~'),2),((2,'a'),3),((3,'~'),3),((3,'~'),4),((4,'~'),4),((4,'b'),5),((5,'~'),5),((5,'~'),8),((6,'~'),6),((6,'c'),7),((7,'~'),7),((7,'~'),8),((8,'~'),8),((8,'~'),1),((8,'~'),9),((9,'~'),9)]

eClose :: [((Integer, Char), Integer)] -> [[Integer]]
eClose tl = eClose' (getStateList tl)

getStateList :: [((Integer, Char), Integer)] -> [Integer]
getStateList xs = nub ([fst (fst u) | u <- xs])

eClose' :: [Integer] -> [[Integer]]
eClose' xs = [ec (u : []) | u <- xs]

ec :: [Integer] -> [Integer]
ec [] = []
ec (s:xs) = [s] ++ ec (eTransTargets s (eTransOutOf s)) ++ (ec xs)

eTransOutOf :: Integer -> [((Integer, Char), Integer)]
eTransOutOf state = [u | u <- tl, fst (fst u) == state && snd (fst u) == '~']

eTransTargets :: Integer -> [((Integer, Char), Integer)] -> [Integer]
eTransTargets _ [] = []
eTransTargets s (x:xs) = [snd u | u <- (x:xs), fst (fst u) == s && snd (fst u) == '~' && snd u /= s]