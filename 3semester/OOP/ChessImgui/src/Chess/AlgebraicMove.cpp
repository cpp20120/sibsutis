#include "Move.h"

static char s_Promotions[] = " NBRQEEE";
std::string LongAlgebraicMove::ToString() noexcept {
  char result[5];
  char* ptr = result;

  *(ptr++) = (char)('a' + FileOf(SourceSquare));
  *(ptr++) = (char)('1' + RankOf(SourceSquare));
  *(ptr++) = (char)('a' + FileOf(DestinationSquare));
  *(ptr++) = (char)('1' + RankOf(DestinationSquare));

  if (Promotion != Pawn && Promotion != King)
    *(ptr++) = s_Promotions[Promotion];

  return {result, ptr};
}

AlgebraicMove::AlgebraicMove(std::string_view str) {
  bool error = false;

  char* fromFront = (char*)&str.front();
  char* fromBack = (char*)&str.back();

  if (*fromBack == '#') {
    Flags |= MoveFlag::Checkmate;
    fromBack--;
  } else if (*fromBack == '+') {
    Flags |= MoveFlag::Check;
    fromBack--;
  }

  const std::string_view castle(fromFront, fromBack - fromFront + 1);

  if (castle == "O-O-O") {
    Flags |= MoveFlag::CastleQueenSide;
    return;
  }

  if (castle == "O-O") {
    Flags |= MoveFlag::CastleKingSide;
    return;
  }

  if (std::islower(str[0])) {
    if (str[1] == 'x') {
      char file = str[0];
      Specifier = ToSquare(file, '1');
      Specifier |= SpecifyFile;

      Flags |= MoveFlag::Capture;

      Destination = ToSquare(str[2], str[3]);
      fromFront += 4;
    } else {
      Destination = ToSquare(str[0], str[1]);
      fromFront += 2;
    }

    if (*fromFront == '=') {
      char promotion = *(++fromFront);

      switch (promotion) {
        case 'N':
          Flags |= MoveFlag::PromoteKnight;
          break;
        case 'B':
          Flags |= MoveFlag::PromoteBishop;
          break;
        case 'R':
          Flags |= MoveFlag::PromoteRook;
          break;
        case 'Q':
          Flags |= MoveFlag::PromoteQueen;
          break;
        default:
          error = true;
      }
    }
  } else {
    MovingPiece = CharToPieceType(str[0]);

    ++fromFront;

    char rank = *(fromBack--);
    char file = *(fromBack--);
    Destination = ToSquare(file, rank);

    if (*fromBack == 'x') fromBack--;

    const uint64_t length = fromBack - fromFront + 1;
    if (length == 1) {
      if (std::isalpha(*fromFront)) {
        Specifier = ToSquare(*fromFront, '1');
        Specifier |= SpecifyFile;
      } else if (std::isdigit(*fromFront)) {
        Specifier = ToSquare('a', *fromFront);
        Specifier |= SpecifyRank;
      } else {
        error = true;
      }
    } else if (length == 2) {
      file = *(fromFront);
      rank = *(++fromFront);
      Specifier = ToSquare(file, rank);
      Specifier |= SpecifyFile | SpecifyRank;
    } else if (length != 0) {
      error = true;
    }
  }

  if (error) throw InvalidAlgebraicMoveException(str);
}

std::string AlgebraicMove::ToString() noexcept {
  if (Flags & MoveFlag::CastleKingSide) {
    if (Flags & MoveFlag::Check) return "O-O+";
    if (Flags & MoveFlag::Checkmate) return "O-O#";
    return "O-O";
  }

  if (Flags & MoveFlag::CastleQueenSide) {
    if (Flags & MoveFlag::Check) return "O-O-O+";
    if (Flags & MoveFlag::Checkmate) return "O-O-O#";
    return "O-O-O";
  }

  char result[7];
  char* ptr = result;

  if (MovingPiece != Pawn) {
    *(ptr++) = PieceTypeToChar(MovingPiece);

    if (Specifier & SpecifyFile)
      *(ptr++) = (char)('a' + FileOf(Specifier & RemoveSpecifierFlag));

    if (Specifier & SpecifyRank)
      *(ptr++) = (char)('1' + RankOf(Specifier & RemoveSpecifierFlag));
  }

  if (Flags & MoveFlag::Capture) {
    if (MovingPiece == Pawn)
      *(ptr++) = (char)('a' + FileOf(Specifier & RemoveSpecifierFlag));

    *(ptr++) = 'x';
  }

  *(ptr++) = (char)('a' + FileOf(Destination));
  *(ptr++) = (char)('1' + RankOf(Destination));

  if (Flags & MoveFlag::PromotionFlags) {
    *(ptr++) = '=';

    *(ptr++) = s_Promotions[(Flags & 0b111)];
  }

  if (Flags & MoveFlag::Checkmate)
    *(ptr++) = '#';
  else if (Flags & MoveFlag::Check)
    *(ptr++) = '+';

  return {result, ptr};
}
