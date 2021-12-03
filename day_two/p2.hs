{-# LANGUAGE RecordWildCards #-}

import Control.Monad.State

data Move = Forward | Down | Up
data Step = Step Move Int

data Position =
  Position { horPos :: Int
           , depth  :: Int
           , aim    :: Int
           }

mkPos :: Int -> Int -> Int -> Position
mkPos h d a = Position { horPos = h, depth = d, aim = a }

doit :: Position -> Int
doit Position {..} = horPos * depth

stringToMove :: String -> Move
stringToMove "forward" = Forward
stringToMove "down"    = Down
stringToMove "up"      = Up
stringToMove m = error $ "dont recognize this move: " ++ m

doStep :: Step -> State Position ()
doStep (Step t i) = state $ \Position {..} ->
  case t of
    Forward -> ((), mkPos (horPos + i) (depth + aim * i) aim)
    Down    -> ((), mkPos horPos depth (aim + i))
    Up      -> ((), mkPos horPos depth (aim - i))

main :: IO ()
main = interact
  ((\i -> show i ++ "\n") . doit . snd . flip runState initialPos . mapM (doStep . parse . words) . lines)
  where parse [mv, amt] = Step (stringToMove mv) (read amt :: Int)
        parse _ = undefined
        initialPos = mkPos 0 0 0
