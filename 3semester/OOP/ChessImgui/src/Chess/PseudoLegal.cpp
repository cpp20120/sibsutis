#include "PseudoLegal.h"

#include <array>

   
namespace {

constexpr BitBoard A_FILE = 0x0101010101010101;
constexpr BitBoard B_FILE = 0x0202020202020202;
constexpr BitBoard RANK_1 = 0x00000000000000FF;
constexpr BitBoard RANK_1_TO_A_FILE = 0x8040201008040201;   constexpr BitBoard VERTICAL_BITBOARD_KEY =
    0x0080402010080400;   
 
constexpr std::array<BitBoard, 64> pawns = []() -> auto {
  std::array<BitBoard, 64> result = {0};

  for (Square s = 8; s < 56; s++) {
              if (RankOf(s + 8) == RankOf(s + 9) && (s + 9) < 64)
      result[s] |= 1ull << (s + 9);
    if (RankOf(s + 8) == RankOf(s + 7) && (s + 7) < 64)
      result[s] |= 1ull << (s + 7);
         if (s + 8 < 64) result[s] |= 1ull << (s + 8);
         if ((1ull << s) & 0x000000000000FF00) result[s] |= 1ull << (s + 16);

              if (RankOf(s - 8) == RankOf(s - 9) && (s - 9) < 64)
      result[s] |= 1ull << (s - 9);
    if (RankOf(s - 8) == RankOf(s - 7) && (s - 7) < 64)
      result[s] |= 1ull << (s - 7);
         if (s - 8 < 64) result[s] |= 1ull << (s - 8);
         if ((1ull << s) & 0x00FF000000000000) result[s] |= 1ull << (s - 16);
  }

  return result;
}();

constexpr std::array<BitBoard, 64> knights = []() -> auto {
  std::array<BitBoard, 64> result = {0};

  constexpr int8_t s_KnightSquares[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

  constexpr int8_t s_Rows[8] = {-16, -16, -8, -8, 8, 8, 16, 16};

  for (Square s = 0; s < 64; s++) {
    for (size_t i = 0; i < 8; i++) {
      const Square knightSquare = s + s_KnightSquares[i];

      if (RankOf(knightSquare) == RankOf(s + s_Rows[i]) && knightSquare < 64)
        result[s] |= 1ull << knightSquare;
    }
  }

  return result;
}();

 constexpr std::array<BitBoard, 64> antiDiagonals = []() -> auto {
  std::array<BitBoard, 64> result = {0};

  for (Square s = 0; s < 64; s++) {
    const Square distanceTop = (FileOf(s) + 56 - s) / 8;
    const Square distanceBottom = (s - FileOf(s)) / 8;
    const Square distanceLeft = s - (RankOf(s) * 8);
    const Square distanceRight = (RankOf(s) * 8) + 7 - s;

    if ((1ull << s) & 0x0103070F1F3F7FFF)
      result[s] = 0x0102040810204080ull >> (8 * (distanceTop - distanceLeft));
    else
      result[s] = 0x0102040810204080ull
                  << (8 * (distanceBottom - distanceRight));

         result[s] ^= 1ull << s;
  }

  return result;
}();

 constexpr std::array<BitBoard, 64> diagonals = []() -> auto {
  std::array<BitBoard, 64> result = {0};

  for (Square s = 0; s < 64; s++) {
    const Square distanceTop = (FileOf(s) + 56 - s) / 8;
    const Square distanceBottom = (s - FileOf(s)) / 8;
    const Square distanceLeft = s - (RankOf(s) * 8);
    const Square distanceRight = (RankOf(s) * 8) + 7 - s;

    if ((1ull << s) & 0x80C0E0F0F8FCFEFF)
      result[s] = 0x8040201008040201ull >> (8 * (distanceTop - distanceRight));
    else
      result[s] = 0x8040201008040201ull
                  << (8 * (distanceBottom - distanceLeft));

         result[s] ^= 1ull << s;
  }

  return result;
}();

    constexpr std::array<std::array<BitBoard, 64>, 8> rankAttacks = []() -> auto {
  std::array<std::array<BitBoard, 64>, 8> result = {0};

     for (Square s = 0; s < 8; s++) {
         for (BitBoard b = 0; b < 128; b += 2) {
      BitBoard attacks = 0;

             BitBoard blockers = b & ~(1ull << s);

                    for (Square i = s; i < 8; i++) {
        attacks |= 1ull << i;
        if (blockers & (1ull << i)) break;
      }

      for (Square i = s; i < 8; i--) {
        attacks |= 1ull << i;
        if (blockers & (1ull << i)) break;
      }

             attacks ^= 1ull << s;

      result[s][b >> 1] = attacks * A_FILE;
    }
  }

  return result;
}();

constexpr std::array<std::array<BitBoard, 64>, 8> aFileAttacks = []() -> auto {
  std::array<std::array<BitBoard, 64>, 8> result = {0};

     for (Square s = 0; s < 8; s++) {
         for (BitBoard b = 0; b < 128; b += 2) {
                    Square mirroredSquare = 7 - s;

             BitBoard attacked = rankAttacks[mirroredSquare][b >> 1] & RANK_1;

                    result[s][b >> 1] = ((attacked * RANK_1_TO_A_FILE) >> 7) & A_FILE;
    }
  }

  return result;
}();

constexpr std::array<BitBoard, 64> kings = []() -> auto {
  std::array<BitBoard, 64> result = {0};

  constexpr int8_t s_KingSquares[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

  constexpr int8_t s_Rows[8] = {-8, -8, -8, 0, 0, 8, 8, 8};

  for (Square s = 0; s < 64; s++) {
    for (size_t i = 0; i < 8; i++) {
      const Square kingSquare = s + s_KingSquares[i];

      if (RankOf(kingSquare) == RankOf(s + s_Rows[i]) && kingSquare < 64)
        result[s] |= 1ull << kingSquare;
    }
  }

  return result;
}();

    
BitBoard HorizontalAttack(Square square, BitBoard blockers) {
  BitBoard relevantBits = BitBoardRank(square);
  size_t blockerIndex = ((blockers & relevantBits) * B_FILE) >> 58;

  return rankAttacks[FileOf(square)][blockerIndex] & relevantBits;
}

BitBoard VerticalAttack(Square square, BitBoard blockers) {
  size_t blockerIndex = (((blockers & BitBoardFile(square)) >> FileOf(square)) *
                         VERTICAL_BITBOARD_KEY) >>
                        58;

  return aFileAttacks[RankOf(square)][blockerIndex] << FileOf(square);
}

 BitBoard DiagonalAttack(Square square, BitBoard blockers) {
  BitBoard relevantBits = diagonals[square];
  size_t index = ((blockers & relevantBits) * B_FILE) >> 58;

  return rankAttacks[FileOf(square)][index] & relevantBits;
}

 BitBoard AntiDiagonalAttack(Square square, BitBoard blockers) {
  BitBoard relevantBits = antiDiagonals[square];
  size_t index = ((blockers & relevantBits) * B_FILE) >> 58;

  return rankAttacks[FileOf(square)][index] & relevantBits;
}

}   
namespace PseudoLegal {

BitBoard PawnMoves(Square square, Colour colour, BitBoard blockers,
                   Square enPassant) {
           BitBoard colourMask = (1ull << square) - 1;

  if (colour == White) {
    colourMask = ~colourMask;
    blockers |= (blockers << 8) & (1ull << (square + 16));
  } else {
    blockers |= (blockers >> 8) & (1ull << (square - 16));
  }

  BitBoard pawnMoves = pawns[square] & colourMask;

              blockers |= 1ull << enPassant;

  pawnMoves &= ~(blockers & BitBoardFile(square));
  pawnMoves &= ~(blockers ^ ~BitBoardFile(square));

  return pawnMoves;
}

BitBoard PawnAttack(Square square, Colour colour) {
           BitBoard colourMask = ~(colour * 0xFFFFFFFFFFFFFFFF) ^ ((1ull << square) - 1);
  BitBoard pawnMoves = pawns[square] & colourMask;
  return pawnMoves & ~BitBoardFile(square);
}

BitBoard KnightAttack(Square square) { return knights[square]; }

BitBoard BishopAttack(Square square, BitBoard blockers) {
  return DiagonalAttack(square, blockers) |
         AntiDiagonalAttack(square, blockers);
}

BitBoard RookAttack(Square square, BitBoard blockers) {
  return HorizontalAttack(square, blockers) | VerticalAttack(square, blockers);
}

BitBoard QueenAttack(Square square, BitBoard blockers) {
  return BishopAttack(square, blockers) | RookAttack(square, blockers);
}

BitBoard KingAttack(Square square) { return kings[square]; }

BitBoard Line(BitBoard square1, BitBoard square2) {
     square1 &= (~square1) + 1;
  square2 &= (~square2) + 1;

     if (square1 && square2 == 0) return 0;

  BitBoard inBetween =
      (square1 - 1) ^
      (square2 - 1);     inBetween |=
      (square1 |
       square2);   
     Square s1 = GetSquare(square1);
  Square s2 = GetSquare(square2);

  if (FileOf(s1) == FileOf(s2)) return inBetween & BitBoardFile(s1);
  if (RankOf(s1) == RankOf(s2)) return inBetween & BitBoardRank(s1);
  if (diagonals[s1] & square2) return inBetween & diagonals[s1];
  if (antiDiagonals[s1] & square2) return inBetween & antiDiagonals[s1];

  return 0;
}

}   