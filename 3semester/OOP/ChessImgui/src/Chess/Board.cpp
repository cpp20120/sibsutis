#include "Board.h"

#include <sstream>

#include "Game.h"
#include "PseudoLegal.h"
#include "Utility/StringParser.h"

static constexpr std::array<Piece, 64> s_StartBoard = {
    WhiteRook,   WhiteKnight, WhiteBishop, WhiteQueen,  WhiteKing,
    WhiteBishop, WhiteKnight, WhiteRook,   WhitePawn,   WhitePawn,
    WhitePawn,   WhitePawn,   WhitePawn,   WhitePawn,   WhitePawn,
    WhitePawn,   None,        None,        None,        None,
    None,        None,        None,        None,        None,
    None,        None,        None,        None,        None,
    None,        None,        None,        None,        None,
    None,        None,        None,        None,        None,
    None,        None,        None,        None,        None,
    None,        None,        None,        BlackPawn,   BlackPawn,
    BlackPawn,   BlackPawn,   BlackPawn,   BlackPawn,   BlackPawn,
    BlackPawn,   BlackRook,   BlackKnight, BlackBishop, BlackQueen,
    BlackKing,   BlackBishop, BlackKnight, BlackRook};

static constexpr std::array<BitBoard, PieceTypeCount> s_PieceBitBoards = {
    0b0000000011111111000000000000000000000000000000001111111100000000,
    0b0100001000000000000000000000000000000000000000000000000001000010,
    0b0010010000000000000000000000000000000000000000000000000000100100,
    0b1000000100000000000000000000000000000000000000000000000010000001,
    0b0000100000000000000000000000000000000000000000000000000000001000,
    0b0001000000000000000000000000000000000000000000000000000000010000};

static constexpr std::array<BitBoard, ColourCount> s_ColourBitBoards = {
    0b0000000000000000000000000000000000000000000000001111111111111111,
    0b1111111111111111000000000000000000000000000000000000000000000000};

static constexpr std::array<BitBoard, 4> s_CastlingPaths = {0x70, 0x70ull << 56,
                                                            0xE, 0xEull << 56};

void Board::Reset() {
  m_Board = s_StartBoard;
  m_PieceBitBoards = s_PieceBitBoards;
  m_ColourBitBoards = s_ColourBitBoards;

  m_PlayerTurn = White;
  m_CastlingPath = s_CastlingPaths;
  m_EnPassantSquare = 0;

  m_HalfMoves = 0;
  m_FullMoves = 1;
}

void Board::FromFEN(const std::string& fen) {
  m_Board.fill(Piece::None);
  m_PieceBitBoards.fill(0);
  m_ColourBitBoards.fill(0);
  m_CastlingPath.fill(CastleSide::NO_CASTLE);

  StringParser fenParser(fen);

  std::string_view board = fenParser.Next<std::string_view>().value_or("");

  Square square = 56;
  for (const char c : board) {
    if (std::isalpha(c)) {
      Piece p;

      switch (c) {
        case 'P':
          p = WhitePawn;
          break;
        case 'N':
          p = WhiteKnight;
          break;
        case 'B':
          p = WhiteBishop;
          break;
        case 'R':
          p = WhiteRook;
          break;
        case 'Q':
          p = WhiteQueen;
          break;
        case 'K':
          p = WhiteKing;
          break;
        case 'p':
          p = BlackPawn;
          break;
        case 'n':
          p = BlackKnight;
          break;
        case 'b':
          p = BlackBishop;
          break;
        case 'r':
          p = BlackRook;
          break;
        case 'q':
          p = BlackQueen;
          break;
        case 'k':
          p = BlackKing;
          break;

        default:
          throw InvalidFenException("Unexpected character in FEN string!");
      }

      PlacePiece(p, square);
      square++;
    } else if (std::isdigit(c)) {
      square += c - '0';
    } else if (c == '/') {
      square -= 16;
    }
  }

  auto playerTurn = fenParser.Next<std::string_view>().value_or("w");
  m_PlayerTurn = playerTurn == "w" ? White : Black;

  auto castlingRights = fenParser.Next<std::string_view>().value_or("-");
  for (char c : castlingRights) {
    if (c == '-') break;
    if (c == 'K')
      m_CastlingPath[White | KingSide] = s_CastlingPaths[White | KingSide];
    if (c == 'Q')
      m_CastlingPath[White | QueenSide] = s_CastlingPaths[White | QueenSide];
    if (c == 'k')
      m_CastlingPath[Black | KingSide] = s_CastlingPaths[Black | KingSide];
    if (c == 'q')
      m_CastlingPath[Black | QueenSide] = s_CastlingPaths[Black | QueenSide];
  }

  auto enPassantSquare = fenParser.Next<std::string_view>().value_or("-");
  if (enPassantSquare != "-")
    m_EnPassantSquare = ToSquare(enPassantSquare[0], enPassantSquare[1]);

  m_HalfMoves = fenParser.Next<int32_t>().value_or(1);
  m_FullMoves = fenParser.Next<int32_t>().value_or(0);
}

std::string Board::ToFEN() const {
  std::ostringstream fen;

  uint32_t emptySquares = 0;

  for (Square rank = 7; rank < 8; rank--) {
    for (Square file = 0; file < 8; file++) {
      Piece p = m_Board[rank * 8 + file];
      if (p == Piece::None) {
        emptySquares++;
      } else {
        if (emptySquares > 0) {
          fen << emptySquares;
          emptySquares = 0;
        }

        fen << PieceToChar(p);
      }
    }

    if (emptySquares > 0) fen << emptySquares;

    if (rank > 0) fen << "/";

    emptySquares = 0;
  }

  fen << " " << (m_PlayerTurn == White ? "w " : "b ");

  uint32_t castlingCount = 0;
  if (m_CastlingPath[White | KingSide] != NO_CASTLE) {
    fen << "K";
    castlingCount++;
  }
  if (m_CastlingPath[White | QueenSide] != NO_CASTLE) {
    fen << "Q";
    castlingCount++;
  }
  if (m_CastlingPath[Black | KingSide] != NO_CASTLE) {
    fen << "k";
    castlingCount++;
  }
  if (m_CastlingPath[Black | QueenSide] != NO_CASTLE) {
    fen << "q";
    castlingCount++;
  }
  if (castlingCount == 0) fen << "-";

  if (m_EnPassantSquare != 0)
    fen << " " << (char)('a' + FileOf(m_EnPassantSquare))
        << (char)('1' + RankOf(m_EnPassantSquare));
  else
    fen << " -";

  fen << " " << m_HalfMoves << " " << m_FullMoves;

  return fen.str();
}

AlgebraicMove Board::Move(LongAlgebraicMove m) {
  Piece piece = m_Board[m.SourceSquare];
  Colour colour = GetColour(piece);
  PieceType pieceType = GetPieceType(piece);

  if (!IsMoveLegal(m)) throw IllegalMoveException(m.ToString());

  bool pawnMove = false;
  bool capture = m_Board[m.DestinationSquare] != Piece::None;
  Square newEnPassantSquare = 0;
  MoveFlags moveFlags = 0;

  if (pieceType == King) {
    int direction = m.DestinationSquare - m.SourceSquare;
    if (abs(direction) == 2) {
      Square rookSquare, newRookSquare;

      if (direction < 0) {
        rookSquare = m.SourceSquare - 4;
        newRookSquare = m.DestinationSquare + 1;
        moveFlags |= MoveFlag::CastleQueenSide;
      } else {
        rookSquare = m.SourceSquare + 3;
        newRookSquare = m.DestinationSquare - 1;
        moveFlags |= MoveFlag::CastleKingSide;
      }

      RemovePiece(rookSquare);
      PlacePiece(PieceTypeAndColour(Rook, colour), newRookSquare);
    }

    m_CastlingPath[colour | KingSide] = NO_CASTLE;
    m_CastlingPath[colour | QueenSide] = NO_CASTLE;
  } else if (pieceType == Pawn) {
    pawnMove = true;
    if (m.SourceSquare - m.DestinationSquare == 16) {
      newEnPassantSquare = m.DestinationSquare + 8;
    } else if (m.DestinationSquare - m.SourceSquare == 16) {
      newEnPassantSquare = m.DestinationSquare - 8;
    } else if (m.DestinationSquare == m_EnPassantSquare) {
      if (colour == White)
        RemovePiece(m.DestinationSquare - 8);
      else
        RemovePiece(m.DestinationSquare + 8);

      capture = true;
    } else if ((1ull << m.DestinationSquare) & 0xFF000000000000FF) {
      if (m.Promotion == Pawn || m.Promotion == King)
        throw IllegalMoveException(m.ToString(),
                                   "Pawn must promote to another piece!");

      piece = PieceTypeAndColour(m.Promotion, colour);
    }
  }

  m_EnPassantSquare = newEnPassantSquare;

  if (m.SourceSquare == A1 || m.DestinationSquare == A1)
    m_CastlingPath[White | QueenSide] = NO_CASTLE;
  else if (m.SourceSquare == H1 || m.DestinationSquare == H1)
    m_CastlingPath[White | KingSide] = NO_CASTLE;
  else if (m.SourceSquare == A8 || m.DestinationSquare == A8)
    m_CastlingPath[Black | QueenSide] = NO_CASTLE;
  else if (m.SourceSquare == H8 || m.DestinationSquare == H8)
    m_CastlingPath[Black | KingSide] = NO_CASTLE;

  m_HalfMoves = (m_HalfMoves + 1) * !(pawnMove || capture);
  m_FullMoves += m_PlayerTurn == Black;

  Square specifier = m.SourceSquare;

  if (pieceType == Pawn) {
    specifier |= SpecifyFile * capture;
  } else if (pieceType != King) {
    BitBoard possiblePieces =
        m_ColourBitBoards[colour] & m_PieceBitBoards[pieceType];
    const BitBoard allPieces =
        m_ColourBitBoards[White] | m_ColourBitBoards[Black];
    switch (pieceType) {
      case Knight:
        possiblePieces &= PseudoLegal::KnightAttack(m.DestinationSquare);
        break;
      case Bishop:
        possiblePieces &=
            PseudoLegal::BishopAttack(m.DestinationSquare, allPieces);
        break;
      case Rook:
        possiblePieces &=
            PseudoLegal::RookAttack(m.DestinationSquare, allPieces);
        break;
      case Queen:
        possiblePieces &=
            PseudoLegal::QueenAttack(m.DestinationSquare, allPieces);
        break;
      default:
        possiblePieces = 0;
    }

    for (BitBoard b = possiblePieces; b != 0; b &= b - 1) {
      if (!GetPieceLegalMoves(GetSquare(b)))
        possiblePieces &= ~(1ull << GetSquare(b));
    }

    if (SquareCount((possiblePieces * 0x0101010101010101) >> 56) > 1)
      specifier |= SpecifyFile;

    if (BitBoardFile(m.SourceSquare) & possiblePieces &
        ~(1ull << m.SourceSquare))
      specifier |= SpecifyRank;
  }

  m_PlayerTurn = OppositeColour(m_PlayerTurn);

  RemovePiece(m.SourceSquare);
  RemovePiece(m.DestinationSquare);
  PlacePiece(piece, m.DestinationSquare);

  bool isCheck = m_PieceBitBoards[King] & m_ColourBitBoards[m_PlayerTurn] &
                 ControlledSquares(colour);
  bool isMate = !HasLegalMoves(m_PlayerTurn) && isCheck;

  moveFlags |= m.Promotion;
  moveFlags |= MoveFlag::Check * isCheck;
  moveFlags |= MoveFlag::Checkmate * isMate;
  moveFlags |= MoveFlag::Capture * capture;

  return {pieceType, m.DestinationSquare, specifier, moveFlags};
}

LongAlgebraicMove Board::Move(AlgebraicMove m) {
  Square source;

  Colour opponentColour = OppositeColour(m_PlayerTurn);

  Square newEnPassantSquare = 0;

  if (m.Flags & MoveFlag::CastlingFlags) {
    Square kingStart = E1 ^ (m_PlayerTurn * 0b00111000);
    Square kingDestination, rookStart, rookDestination;
    CastleSide castleSide;

    if (m.Flags & MoveFlag::CastleKingSide) {
      kingDestination = G1 ^ (m_PlayerTurn * 0b00111000);
      rookStart = H1 ^ (m_PlayerTurn * 0b00111000);
      rookDestination = F1 ^ (m_PlayerTurn * 0b00111000);
      castleSide = KingSide;
    } else {
      kingDestination = C1 ^ (m_PlayerTurn * 0b00111000);
      rookStart = A1 ^ (m_PlayerTurn * 0b00111000);
      rookDestination = D1 ^ (m_PlayerTurn * 0b00111000);
      castleSide = QueenSide;
    }

    if (IsMoveLegal({kingStart, kingDestination})) {
      RemovePiece(kingStart);
      PlacePiece(PieceTypeAndColour(King, m_PlayerTurn), kingDestination);

      RemovePiece(rookStart);
      PlacePiece(PieceTypeAndColour(Rook, m_PlayerTurn), rookDestination);

      m_CastlingPath[m_PlayerTurn | castleSide] = NO_CASTLE;

      m_PlayerTurn = opponentColour;
      return {kingStart, kingDestination};
    }

    throw IllegalMoveException(m.ToString());
  } else if (m.MovingPiece == Pawn) {
    int8_t direction = m_PlayerTurn == White ? 8 : -8;
    if (m.Flags & MoveFlag::Capture) {
      BitBoard possiblePieces =
          PseudoLegal::PawnAttack(m.Destination, opponentColour);
      Square file = FileOf(m.Specifier);
      source = GetSquare(possiblePieces & BitBoardFile(file));

      if (m.Destination == m_EnPassantSquare)
        RemovePiece(m.Destination - direction);
    } else {
      source = m.Destination - direction;

      const bool middle = RankOf(m.Destination) == (3 + m_PlayerTurn);
      if (middle && GetPieceType(m_Board[source]) != Pawn) {
        newEnPassantSquare = source;
        source -= direction;
      }

      if ((1ull << m.Destination) & 0xFF000000000000FFull) {
        PieceType type = (PieceType)(m.Flags & MoveFlag::PromotionFlags);

        if (!type)
          throw IllegalMoveException(m.ToString(), "Must promote pawn");

        if (!IsMoveLegal({source, m.Destination}))
          throw IllegalMoveException(m.ToString());

        RemovePiece(source);
        RemovePiece(m.Destination);
        PlacePiece(PieceTypeAndColour(type, m_PlayerTurn), m.Destination);

        m_PlayerTurn = opponentColour;

        return {source, m.Destination, type};
      }
    }
  } else {
    BitBoard possiblePieces =
        m_PieceBitBoards[m.MovingPiece] & m_ColourBitBoards[m_PlayerTurn];

    const BitBoard allPieces =
        m_ColourBitBoards[White] | m_ColourBitBoards[Black];
    switch (m.MovingPiece) {
      case Knight:
        possiblePieces &= PseudoLegal::KnightAttack(m.Destination);
        break;
      case Bishop:
        possiblePieces &= PseudoLegal::BishopAttack(m.Destination, allPieces);
        break;
      case Rook:
        possiblePieces &= PseudoLegal::RookAttack(m.Destination, allPieces);
        break;
      case Queen:
        possiblePieces &= PseudoLegal::QueenAttack(m.Destination, allPieces);
        break;
      case King:
        possiblePieces &= PseudoLegal::KingAttack(m.Destination);
        break;
      default:
        possiblePieces = 0;
    }

    if (m.Specifier & SpecifyFile) possiblePieces &= BitBoardFile(m.Specifier);

    if (m.Specifier & SpecifyRank) possiblePieces &= BitBoardRank(m.Specifier);

    for (BitBoard b = possiblePieces; b != 0; b &= b - 1) {
      if (!GetPieceLegalMoves(GetSquare(b)))
        possiblePieces &= ~(1ull << GetSquare(b));
    }

    if (SquareCount(possiblePieces) != 1) {
      if (SquareCount(possiblePieces) == 0)
        throw IllegalMoveException(m.ToString(),
                                   "No piece can more to specified square!");
      else
        throw IllegalMoveException(
            m.ToString(), "More than one piece can move to the same square!");
    }

    source = GetSquare(possiblePieces);
  }

  if (source == A1 || m.Destination == A1)
    m_CastlingPath[White | QueenSide] = NO_CASTLE;
  else if (source == H1 || m.Destination == H1)
    m_CastlingPath[White | KingSide] = NO_CASTLE;
  else if (source == A8 || m.Destination == A8)
    m_CastlingPath[Black | QueenSide] = NO_CASTLE;
  else if (source == H8 || m.Destination == H8)
    m_CastlingPath[Black | KingSide] = NO_CASTLE;

  if (!IsMoveLegal({source, m.Destination}))
    throw IllegalMoveException(m.ToString());

  m_EnPassantSquare = newEnPassantSquare;

  Piece piece = m_Board[source];
  RemovePiece(source);
  RemovePiece(m.Destination);
  PlacePiece(piece, m.Destination);

  m_PlayerTurn = opponentColour;

  return {source, m.Destination};
}

void Board::UndoMove(const GameMove& move) {
  m_PlayerTurn = OppositeColour(m_PlayerTurn);

  if (GameMoveFlags castling = move.Flags & GameMoveFlag::CastlingFlags) {
    bool otherSide = move.Flags & GameMoveFlag::CanCastleOtherSide;

    switch (castling) {
      case GameMoveFlag::CastleWhiteKingSide: {
        RemovePiece(G1);
        RemovePiece(F1);
        PlacePiece(WhiteRook, H1);
        PlacePiece(WhiteKing, E1);
        m_CastlingPath[White | KingSide] = s_CastlingPaths[White | KingSide];
        m_CastlingPath[White | QueenSide] =
            otherSide * s_CastlingPaths[White | QueenSide];
        return;
      }
      case GameMoveFlag::CastleWhiteQueenSide: {
        RemovePiece(C1);
        RemovePiece(D1);
        PlacePiece(WhiteRook, A1);
        PlacePiece(WhiteKing, E1);
        m_CastlingPath[White | KingSide] =
            otherSide * s_CastlingPaths[White | KingSide];
        m_CastlingPath[White | QueenSide] = s_CastlingPaths[White | QueenSide];
        return;
      }
      case GameMoveFlag::CastleBlackKingSide: {
        RemovePiece(G8);
        RemovePiece(F8);
        PlacePiece(BlackRook, H8);
        PlacePiece(BlackKing, E8);
        m_CastlingPath[Black | KingSide] = s_CastlingPaths[Black | KingSide];
        m_CastlingPath[Black | QueenSide] =
            otherSide * s_CastlingPaths[Black | QueenSide];
        return;
      }
      case GameMoveFlag::CastleBlackQueenSide: {
        RemovePiece(C8);
        RemovePiece(D8);
        PlacePiece(BlackRook, A8);
        PlacePiece(BlackKing, E8);
        m_CastlingPath[Black | KingSide] =
            otherSide * s_CastlingPaths[Black | KingSide];
        m_CastlingPath[Black | QueenSide] = s_CastlingPaths[Black | QueenSide];
        return;
      }
    }
  }

  RemovePiece(move.Destination);
  PlacePiece(move.MovingPiece, move.Start);

  if (move.Flags & GameMoveFlag::EnPassant) {
    if (GetColour(move.MovingPiece) == White)
      PlacePiece(BlackPawn, move.Destination - 8);
    else
      PlacePiece(WhitePawn, move.Destination + 8);
    m_EnPassantSquare = move.Destination;
  }

  if (move.DestinationPiece != None)
    PlacePiece(move.DestinationPiece, move.Destination);
}

bool Board::HasLegalMoves(Colour colour) {
  for (Square s = 0; s < m_Board.size(); s++)
    if (GetColour(m_Board[s]) == colour)
      if (GetPieceLegalMoves(s) != 0) return true;

  return false;
}

BitBoard Board::GetPieceLegalMoves(Square piece) {
  Colour playerColour = GetColour(m_Board[piece]);
  Colour enemyColour = OppositeColour(playerColour);

  if (enemyColour == m_PlayerTurn) return 0;

  BitBoard allPieces = m_ColourBitBoards[White] | m_ColourBitBoards[Black];
  BitBoard king = m_ColourBitBoards[playerColour] & m_PieceBitBoards[King];
  BitBoard enemyPieces = m_ColourBitBoards[enemyColour];

  if (GetPieceType(m_Board[piece]) == King) {
    BitBoard legalMoves = GetPseudoLegalMoves(piece);
    BitBoard controlledSquares = ControlledSquares(enemyColour);

    if (!((allPieces & ~king) & m_CastlingPath[playerColour | KingSide]) &&
        !(controlledSquares & m_CastlingPath[playerColour | KingSide]))
      legalMoves |= 0x40ull << (playerColour == White ? 0 : 56);
    if (!((allPieces & ~king) & m_CastlingPath[playerColour | QueenSide]) &&
        !(controlledSquares & m_CastlingPath[playerColour | QueenSide]))
      legalMoves |= 0x04ull << (playerColour == White ? 0 : 56);

    return legalMoves & ~controlledSquares;
  }

  Square kingSquare = GetSquare(king);

  BitBoard checkMask = 0;
  BitBoard checkers = 0;

  BitBoard bishopView = PseudoLegal::BishopAttack(kingSquare, allPieces);
  BitBoard bishopCheck = bishopView & enemyPieces &
                         (m_PieceBitBoards[Bishop] | m_PieceBitBoards[Queen]);
  checkers |= bishopCheck;
  checkMask |= PseudoLegal::Line(king, bishopCheck);

  BitBoard bishopXRay =
      PseudoLegal::BishopAttack(kingSquare, allPieces & ~bishopView) &
      enemyPieces & (m_PieceBitBoards[Bishop] | m_PieceBitBoards[Queen]);
  BitBoard bishopPin = 0;
  while (bishopXRay) {
    bishopPin |= PseudoLegal::Line(king, bishopXRay);
    bishopXRay &= bishopXRay - 1;
  }

  BitBoard rookView = PseudoLegal::RookAttack(kingSquare, allPieces);
  BitBoard rookCheck = rookView & enemyPieces &
                       (m_PieceBitBoards[Rook] | m_PieceBitBoards[Queen]);
  checkers |= rookCheck;
  checkMask |= PseudoLegal::Line(king, rookCheck);

  BitBoard rookXRay =
      PseudoLegal::RookAttack(kingSquare, allPieces & ~rookView) & enemyPieces &
      (m_PieceBitBoards[Rook] | m_PieceBitBoards[Queen]);
  BitBoard rookPin = 0;
  while (rookXRay) {
    rookPin |= PseudoLegal::Line(king, rookXRay);
    rookXRay &= rookXRay - 1;
  }

  BitBoard knightCheck = PseudoLegal::KnightAttack(kingSquare) & enemyPieces &
                         m_PieceBitBoards[Knight];
  checkers |= knightCheck;
  checkMask |= knightCheck;

  BitBoard pawnCheck = PseudoLegal::PawnAttack(kingSquare, playerColour) &
                       enemyPieces & m_PieceBitBoards[Pawn];
  checkers |= pawnCheck;
  checkMask |= pawnCheck;

  if (checkMask == 0) checkMask = 0xFFFFFFFFFFFFFFFF;

  checkMask *= SquareCount(checkers) < 2;

  BitBoard pseudoLegal = GetPseudoLegalMoves(piece);

  BitBoard pieceSquare = 1ull << piece;
  if (pieceSquare & rookPin)
    pseudoLegal &= rookPin & PseudoLegal::RookAttack(piece, allPieces);
  else if (pieceSquare & bishopPin)
    pseudoLegal &= bishopPin & PseudoLegal::BishopAttack(piece, allPieces);

  pseudoLegal &= checkMask;

  if (GetPieceType(m_Board[piece]) == Pawn && king & 0x000000FFFF000000 &&
      m_EnPassantSquare) {
    BitBoard twoPawns = ((1ull << (m_EnPassantSquare + 8)) |
                         (1ull << (m_EnPassantSquare - 8))) &
                        0x000000FFFF000000;
    twoPawns |= pieceSquare;

    rookView = PseudoLegal::RookAttack(kingSquare, allPieces & ~twoPawns);
    if (rookView & enemyPieces &
        (m_PieceBitBoards[Rook] | m_PieceBitBoards[Queen]))
      pseudoLegal &= ~(1ull << m_EnPassantSquare);
  }

  return pseudoLegal;
}

BitBoard Board::GetPseudoLegalMoves(Square piece) const {
  PieceType pt = GetPieceType(m_Board[piece]);
  Colour c = GetColour(m_Board[piece]);

  BitBoard blockers = m_ColourBitBoards[White] | m_ColourBitBoards[Black];

  switch (pt) {
    case Pawn:
      return PseudoLegal::PawnMoves(piece, c, blockers, m_EnPassantSquare) &
             ~m_ColourBitBoards[c];
    case Knight:
      return PseudoLegal::KnightAttack(piece) & ~m_ColourBitBoards[c];
    case Bishop:
      return PseudoLegal::BishopAttack(piece, blockers) & ~m_ColourBitBoards[c];
    case Rook:
      return PseudoLegal::RookAttack(piece, blockers) & ~m_ColourBitBoards[c];
    case Queen:
      return PseudoLegal::QueenAttack(piece, blockers) & ~m_ColourBitBoards[c];
    case King:
      return PseudoLegal::KingAttack(piece) & ~m_ColourBitBoards[c];

    default:
      return 0;
  }
}

BitBoard Board::ControlledSquares(Colour c) const {
  BitBoard king = m_ColourBitBoards[OppositeColour(c)] & m_PieceBitBoards[King];
  BitBoard blockers =
      (m_ColourBitBoards[White] | m_ColourBitBoards[Black]) ^ king;

  BitBoard controlledSquares = 0;
  for (Square s = 0; s < 64; s++) {
    if (m_Board[s] != Piece::None && GetColour(m_Board[s]) == c) {
      switch (GetPieceType(m_Board[s])) {
        case Pawn:
          controlledSquares |= PseudoLegal::PawnAttack(s, c);
          break;
        case Knight:
          controlledSquares |= PseudoLegal::KnightAttack(s);
          break;
        case Bishop:
          controlledSquares |= PseudoLegal::BishopAttack(s, blockers);
          break;
        case Rook:
          controlledSquares |= PseudoLegal::RookAttack(s, blockers);
          break;
        case Queen:
          controlledSquares |= PseudoLegal::QueenAttack(s, blockers);
          break;
        case King:
          controlledSquares |= PseudoLegal::KingAttack(s);
          break;

        default:
          return 0;
      }
    }
  }

  return controlledSquares;
}
