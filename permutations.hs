import System.Environment

getel :: Integer -> [a] -> a
getel 0 (x:xs) = x
getel n (x:xs) = getel (n-1) xs


long_length :: [a] -> Integer
long_length lst = long_length_tr 0 lst
long_length_tr :: Integer -> [a] -> Integer
long_length_tr a [] = a
long_length_tr a (x:xs) = long_length_tr (a+1) xs



delete :: Integer -> [Integer] -> [Integer]
delete _ [] = []
delete x (y:ys)
    | x==y = ys
    | otherwise = y:delete x ys

-- calculates factorial of n
factorial :: Integer -> Integer
factorial n
    | n >= 0 = factorial_tr 1 n
    | otherwise = 0
factorial_tr :: Integer -> Integer -> Integer
factorial_tr a 0 = a
factorial_tr a n = factorial_tr (a*n) (n-1)

-- factoriad of n using alphabet ns is [digits]
factoriad :: Integer -> [Integer] -> [Integer]
factoriad n ns
    | n > (factorial ((long_length ns)-1))*((long_length ns))-1= []
    | n < 0 = []
    | otherwise  = reverse (factoriad_tr ns [] n)
--              lst      acc      n      res
factoriad_tr :: [Integer] -> [Integer] -> Integer -> [Integer]
factoriad_tr [] r _ = r -- when out of alphabet
factoriad_tr (x:xs) r 0 = factoriad_tr xs (x:r) 0
factoriad_tr lst r n =
    let l = long_length lst -- how big a factorial do we need?
        f = (factorial (l-1)) -- what is it?
        el = getel (n `div` f) lst -- get the selected element
    in factoriad_tr (delete el lst) (el:r) (n `mod` f)

main = do
    args <- getArgs
    case args of
        [] -> error "usage: permutations <length> <n>"
        [nl,ml] -> do
            print (factoriad (read ml) [1..(read nl)])
        [arg] -> error "usage: permutations <length> <n>"
        _ -> error "usage: permutations <length> <n>"
