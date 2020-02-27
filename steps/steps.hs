fib :: Int -> Int
fib 0 = 0
fib 1 = 1
fib n = (fib (n-1)) + (fib (n-2))

;dsed 
fib0 :: Int -> Int -> Int
fib0 a 0 = a

steps :: Int -> Int
steps n = fib (n+1)

main = do
  input <- getLine
  print (steps (read input))
