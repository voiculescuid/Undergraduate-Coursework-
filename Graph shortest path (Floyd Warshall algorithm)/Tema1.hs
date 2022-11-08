module Tema1 (
        solveSimple,
        solveCosts
        ) where
import Data.Array

inf = 10^10

solveSimple :: (Int, [(Int, Int, Int)]) -> Maybe ([Int], Int)
solveSimple (_, []) = Nothing
solveSimple (2, (i,j,c):[]) = Just ([i,j], c)
solveSimple (towns, ways)  = if long >= inf 
                         then Nothing
                         else Just ([1] ++ range ++ [towns], long ) 
    where 
         graph = listArray ((0,0), (length ways,length ways)) [ (foo x y ways ) | x <- [0..length ways], y <- [0..length ways] ]
         mem   = listArray ((1,1,0), (length ways,length ways, length ways)) [ (shortest x y z) | x <- [1..length ways], y <- [1..length ways], z<-[0..length ways] ]
         shortest  i j 0  = graph!(i,j)
         shortest  i j k  = min (mem!(i,j,k-1)) (mem!(i,k,k-1) + mem!(k,j,k-1))
         long  = mem!(1,towns,length ways)
         range = path (1,towns,length ways) mem

path (i,j,0) _ = []
path (i,j,k) mem=  if direct < step 
                      then path(i,j,k-1) mem
                      else (path(i,k,k-1) mem) ++ [k] ++ (path(k,j,k-1) mem)
                   where direct =  mem!(i,j,k-1) 
                         step   =  mem!(i,k,k-1) + mem!(k,j,k-1)

foo i j ((a,b,c):xs) = if i==a && j==b then c else foo i j xs
foo _ _ [] = inf
