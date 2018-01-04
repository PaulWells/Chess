#include "GameState.hpp"
#include "../types/ChessBoard.hpp"
#include "../types/ChessPiece.hpp"

const int WHITE_START_ROW = 0;
const int BLACK_START_ROW = BOARD_WIDTH - 1;

GameState::GameState()
{
    InitializeChessBoard();
    m_whiteKingSquare = { WHITE_START_ROW, 3 };
    m_blackKingSquare = { BLACK_START_ROW, 4 };
    m_enPassantSquare = { -1, -1 };
}

static void AddKings(ChessBoard& board)
{
    ChessPiece whiteKing = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::King, false, false, false);
    ChessPiece blackKing = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::King, true, false, false);

    board[WHITE_START_ROW][3] = whiteKing;
    board[BLACK_START_ROW][4] = blackKing;
}

static void AddQueens(ChessBoard& board)
{
    ChessPiece whiteQueen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, false, false, false);
    ChessPiece blackQueen = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Queen, true, false, false);

    board[WHITE_START_ROW][4] = whiteQueen;
    board[BLACK_START_ROW][3] = blackQueen;
}

static void AddBishops(ChessBoard& board)
{
    ChessPiece whiteBishop = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Bishop, false, false, false);
    ChessPiece blackBishop = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Bishop, true, false, false);

    board[WHITE_START_ROW][2] = whiteBishop;
    board[WHITE_START_ROW][5] = whiteBishop;
    board[BLACK_START_ROW][2] = blackBishop;
    board[BLACK_START_ROW][5] = blackBishop;
}

static void AddKnights(ChessBoard& board)
{
    ChessPiece whiteKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, false, false, false);
    ChessPiece blackKnight = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Knight, true, false, false);

    board[WHITE_START_ROW][1] = whiteKnight;
    board[WHITE_START_ROW][6] = whiteKnight;
    board[BLACK_START_ROW][1] = blackKnight;
    board[BLACK_START_ROW][6] = blackKnight;
}

static void AddCastles(ChessBoard& board)
{
    ChessPiece whiteCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, false, false, false);
    ChessPiece blackCastle = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Castle, true, false, false);

    board[WHITE_START_ROW][0] = whiteCastle;
    board[WHITE_START_ROW][7] = whiteCastle;
    board[BLACK_START_ROW][0] = blackCastle;
    board[BLACK_START_ROW][7] = blackCastle;
}

static void AddPawns(ChessBoard& board)
{
    ChessPiece whitePawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, false, false, false);
    ChessPiece blackPawn = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::Pawn, true, false, false);

    for (int column = 0; column < BOARD_WIDTH; column++)
    {
        board[WHITE_START_ROW + 1][column] = whitePawn;
        board[BLACK_START_ROW - 1][column] = blackPawn;
    }
}

static void ClearMemory(ChessBoard& board)
{
    for (int row = 0; row < BOARD_WIDTH; row++)
    {
        for (int column = 0; column < BOARD_WIDTH; column++)
        {
            board[row][column] = ChessPieceHelpers::MakeChessPiece(ChessPieceTypes::EmptySquare, false, false, false);
        }
    }
}

void GameState::InitializeChessBoard()
{
    ClearMemory(m_board);
    AddKings(m_board);
    AddQueens(m_board);
    AddBishops(m_board);
    AddKnights(m_board);
    AddCastles(m_board);
    AddPawns(m_board);
}
