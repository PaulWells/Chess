# Chess
Redoing chess using C++

# Todo
Change Moves from a vector to a set
ChessBoard should always be passed by reference
Only one of each type of MoveFinder should be used.
Remove double jump property of chess piece

Add MoveApplicator
 - Applies / Undoes Moves
 - Updates EnPassantTracker
   - EnPassantTracker is cleared after every move
   - Own EnPassantTracker is set after a doubleJump move
 - Filters moves that put own King in check
