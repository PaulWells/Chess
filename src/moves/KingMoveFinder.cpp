#include <memory>
#include <vector>
#include "../types/ChessBoard.hpp"
#include "../types/Move.hpp"
#include "KingMoveFinder.hpp"
#include "MoveFinderHelpers.hpp"

static const unsigned int s_numberOfCastlesPerPlayer = 2;

static const Square s_blackCastleStartingSquares[s_numberOfCastlesPerPlayer] = {
    { 0, 0 },
    { 0, BOARD_WIDTH - 1 }
};

// The square that the king would end on during a castling
// move.  Each item corresponds with the item at the same
// index in s_blackCastleStartingSquares.
static const Square s_blackCastlingKingEndSquares[s_numberOfCastlesPerPlayer] = {
    { 0, 0 + 1 },
    { 0, (BOARD_WIDTH - 1) -1 }
};

static const Square s_whiteCastleStartingSquares[s_numberOfCastlesPerPlayer] = {
    { BOARD_WIDTH - 1, 0 },
    { BOARD_WIDTH - 1, BOARD_WIDTH - 1 }
};

// The square that the king would end on during a castling
// move.  Each item corresponds with the item at the same
// index in s_whiteCastleStartingSquares.
static const Square s_whiteCastlingKingEndSquares[s_numberOfCastlesPerPlayer] = {
    { BOARD_WIDTH - 1, 0 + 1 },
    { BOARD_WIDTH - 1, BOARD_WIDTH - 1 }
};

// The direction that the king would move during a
// castling move.  These are the same for both
// black and white pieces.
static const Vector s_castlingDirections[s_numberOfCastlesPerPlayer] = {
    { 0, -1 },
    { 0,  1 }
};

KingMoveFinder::KingMoveFinder()
{
    m_straightSlideMoveFinder = std::unique_ptr<IMoveFinder>(
        SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Straight, 1 /*rangeLimit*/));

    m_diagonalSlideMoveFinder = std::unique_ptr<IMoveFinder>(
        SlideMoveFinder::CreateSlideMoveFinder(SlideMoveType::Diagonal, 1 /*rangeLimit*/));

    m_squareUnderAttackDeterminer = std::unique_ptr<SquareUnderAttackDeterminer>();
}

static void AddCastlingMove(
    Square kingStartSquare,
    Square kingEndSquare,
    ChessPiece king,
    ChessPiece castle,
    Square castleStartingSquare,
    std::vector<Move>* moves)
{
    Move castlingMove = { 0 };
    castlingMove.start = kingStartSquare;
    castlingMove.end = kingEndSquare;
    castlingMove.startState = king;
    castlingMove.endState = ChessPieceHelpers::MarkChessPieceAsMoved(king);

    // When determining the next move to choose, the search space will
    // consist of a tree of Moves.  The speed in which we can create
    // and traverse this tree will be the performance bottleneck.  Therefore
    // we want to keep the Move struct as small as possible.  Instead of adding
    // more fields to the Move struct, the MoveApplicator will recognize that a
    // king has moved two spaces and therefore will know that the castle must be
    // moved instead of removed.
    castlingMove.removedPiece = castle;
    castlingMove.removedPieceSquare = castleStartingSquare;
    moves->push_back(castlingMove);
}

static void GetSquaresBetweenKingAndCastle(
    ChessBoard board,
    Square kingSquare,
    Square castleSquare,
    Vector direction,
    std::vector<Square>& squares)
{
    unsigned int totalDistance = std::abs(kingSquare.column - castleSquare.column);
    for (unsigned int distance = 0; distance < totalDistance; distance++)
    {
        Vector moveVector = direction * distance;
        Square square = kingSquare + moveVector;
        squares.push_back(square);
    }
}

static bool NoPiecesBetweenKingAndCastle(ChessBoard board, std::vector<Square>& squaresBetweenKingAndCastle)
{
    for (int i = 0; i < squaresBetweenKingAndCastle.size(); i++)
    {
        Square square = squaresBetweenKingAndCastle.at(i);
        ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
        if (ChessPieceHelpers::GetPieceType(piece) != ChessPieceTypes::EmptySquare)
        {
            return false;
        }
    }
    return true;
}

bool KingMoveFinder::NoSquareBetweenKingAndCastleIsUnderAttack(ChessBoard board, std::vector<Square>& squaresBetweenKingAndCastle, bool isOpponentBlack)
{
    for (int i = 0; i < squaresBetweenKingAndCastle.size(); i++)
    {
        Square square = squaresBetweenKingAndCastle.at(i);
        ChessPiece piece = ChessBoardHelpers::PieceAt(board, square);
        if (m_squareUnderAttackDeterminer->IsSquareUnderAttack(board, square, isOpponentBlack))
        {
            return false;
        }
    }
    return true;
}

void KingMoveFinder::FindCastlingMoves(ChessBoard board, Square kingSquare, std::vector<Move>* moves)
{
    ChessPiece king = ChessBoardHelpers::PieceAt(board, kingSquare);
    if (!ChessPieceHelpers::HasMoved(king))
    {
        bool isKingBlack = ChessPieceHelpers::IsBlack(king);
        const Square (*startingCastleSquares)[s_numberOfCastlesPerPlayer] =
        (isKingBlack ? &s_blackCastleStartingSquares : &s_whiteCastleStartingSquares);

        const Square (*kingEndSquares)[s_numberOfCastlesPerPlayer] =
        (isKingBlack ? &s_blackCastlingKingEndSquares : &s_whiteCastlingKingEndSquares);

        for (unsigned int i = 0; i < s_numberOfCastlesPerPlayer; i++)
        {
            Square castleStartingSquare = (*startingCastleSquares)[i];
            std::vector<Square> squaresBetweenKingAndCastle;
            GetSquaresBetweenKingAndCastle(
                board,
                kingSquare,
                castleStartingSquare,
                s_castlingDirections[i],
                squaresBetweenKingAndCastle);

            ChessPiece castle = ChessBoardHelpers::PieceAt(board, castleStartingSquare);
            bool isOpponentBlack = !isKingBlack;
            if (!ChessPieceHelpers::HasMoved(castle) &&
                 NoPiecesBetweenKingAndCastle(board, squaresBetweenKingAndCastle) &&
                 NoSquareBetweenKingAndCastleIsUnderAttack(board, squaresBetweenKingAndCastle, isOpponentBlack))
            {
                AddCastlingMove(kingSquare, (*kingEndSquares)[i], king, castle, castleStartingSquare, moves);
                // There can only be one valid castling move.
                continue;
            }
        }
    }
}

std::unique_ptr<std::vector<Move>> KingMoveFinder::FindMoves(ChessBoard board, Square square)
{
    std::unique_ptr<std::vector<Move>> moves = m_straightSlideMoveFinder->FindMoves(board, square);
    std::unique_ptr<std::vector<Move>> diagonalMoves = m_diagonalSlideMoveFinder->FindMoves(board, square);
    moves->insert(moves->end(), diagonalMoves->begin(), diagonalMoves->end());

    FindCastlingMoves(board, square, moves.get());
    return std::move(moves);
}

ChessPieceType KingMoveFinder::GetPieceType()
{
    return ChessPieceTypes::King;
}
