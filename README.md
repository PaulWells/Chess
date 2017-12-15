# Chess
Redoing chess using C++

# Todo
Change Moves from a vector to a set
ChessBoard should always be passed by reference
Only one of each type of MoveFinder should be used.

Add MoveApplicator
 - Applies / Undoes Moves
 - Updates EnPassantTracker
   - EnPassantTracker is cleared after every move
   - Own EnPassantTracker is set after a doubleJump move
 - Filters moves that put own King in check

Add EnPassantTracker
 - Holds square of pawn that just double jumped

Add GameState
 - holds board and EnPassantTracker

 Add class for determining if a square is in check or not
