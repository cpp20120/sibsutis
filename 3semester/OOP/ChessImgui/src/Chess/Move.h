#pragma once

#include <ostream>
#include <string_view>
#include <cstdint>
#include "math.h"

#include "ChessException.h"

enum Colour : uint8_t {
    White, Black,

    ColourCount = 2
};

enum PieceType : uint8_t {
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King,

    PieceTypeCount = 6
};

enum Piece : uint8_t {
    WhitePawn,
    WhiteKnight,
    WhiteBishop,
    WhiteRook,
    WhiteQueen,
    WhiteKing,
    BlackPawn = 8,
    BlackKnight,
    BlackBishop,
    BlackRook,
    BlackQueen,
    BlackKing,

    None,        };

 enum CastleSide : uint64_t {
    KingSide  = 0b00,
    QueenSide = 0b10,

    NO_CASTLE = 0xFFFFFFFFFFFFFFFF,
};

 constexpr inline PieceType GetPieceType(Piece p) { return (PieceType)(p & 0b0111); }

 constexpr inline Colour GetColour(Piece p) { return (Colour)((p & 0b1000) >> 3); }

 constexpr inline Colour OppositeColour(Colour c) { return (Colour)(1 - c); }

 constexpr inline Piece PieceTypeAndColour(PieceType t, Colour c) { return (Piece)(t | (c << 3)); }

inline char PieceToChar(Piece p) {
    constexpr static char s_PieceToChar[] = "PNBRQK  pnbrqk";

    return s_PieceToChar[p];
}

inline char PieceTypeToChar(PieceType t) {
    constexpr static char s_PieceTypeToChar[] = "PNBRQK";

    return s_PieceTypeToChar[t];
}

inline PieceType CharToPieceType(char piece) {
    switch ((char)std::tolower(piece)) {
        case 'p': return Pawn;
        case 'n': return Knight;
        case 'b': return Bishop;
        case 'r': return Rook;
        case 'q': return Queen;
        case 'k': return King;
        default: throw InvalidPieceTypeException();
    }
}

  using Square = uint8_t;

enum SquareValues : Square {
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    SQUARE_MAX = 64, INVALID_SQUARE = 64
};

inline constexpr Square ToSquare(char file, char rank) {
    Square x = file - 'a';       Square y = (rank - 1) - '0';       return y * 8 + x;
}

 inline constexpr Square RankOf(Square s) { return (s & 0b00111000) >> 3; }
 inline constexpr Square FileOf(Square s) { return s & 0b00000111; }

inline constexpr Square FlipPerspective(Square s, Colour c) { return s ^ (c * 0b00111000); }

struct LongAlgebraicMove {
    Square SourceSquare = 0;
    Square DestinationSquare = 0;
    PieceType Promotion = Pawn;

    LongAlgebraicMove() = default;

    LongAlgebraicMove(Square a, Square b, PieceType promotion = Pawn)
		: SourceSquare(a), DestinationSquare(b), Promotion(promotion) {}

    LongAlgebraicMove(std::string_view longAlgebraic) {
        if (longAlgebraic.size() == 4) {
            SourceSquare = ToSquare(longAlgebraic[0], longAlgebraic[1]);
            DestinationSquare = ToSquare(longAlgebraic[2], longAlgebraic[3]);
        } else if (longAlgebraic.size() == 5) {
            SourceSquare = ToSquare(longAlgebraic[0], longAlgebraic[1]);
            DestinationSquare = ToSquare(longAlgebraic[2], longAlgebraic[3]);
            Promotion = CharToPieceType(longAlgebraic[4]);
        } else {
            throw InvalidLongAlgebraicMoveException(std::string{ longAlgebraic });
        }
    }

    std::string ToString() noexcept;
};

inline std::ostream& operator<<(std::ostream& os, LongAlgebraicMove m) {
    os << m.ToString();
    return os;
}

using MoveFlags = uint8_t;

namespace MoveFlag {
    enum : uint8_t {
                 PromotionFlags = 0b111,

                 PromoteKnight  = 0b001,
        PromoteBishop  = 0b010,
        PromoteRook    = 0b011,
        PromoteQueen   = 0b100,

        CastlingFlags   = 0b11000,

        CastleKingSide  = 1 << 3,
        CastleQueenSide = 1 << 4,

        Capture   = 1 << 5,
        Check     = 1 << 6,
        Checkmate = 1 << 7,
    };
}

enum : uint8_t {
    SpecifyFile = 1 << 7,
    SpecifyRank = 1 << 6,
    SpecifyFileAndRank = 0b11 << 6,

    RemoveSpecifierFlag = 0b00111111,
};

struct AlgebraicMove {
    PieceType MovingPiece = Pawn;
    Square Destination = 0;
    
                        Square Specifier = 0;

         MoveFlags Flags = 0;

    AlgebraicMove(PieceType movingPiece, Square destination, Square specifier, MoveFlags flags)
	    : MovingPiece(movingPiece), Destination(destination), Specifier(specifier), Flags(flags) {}
    
    AlgebraicMove(std::string_view str);

    std::string ToString() noexcept;
};

inline std::ostream& operator<<(std::ostream& os, AlgebraicMove m) {
    os << m.ToString();
    return os;
}
