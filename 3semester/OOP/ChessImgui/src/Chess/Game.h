#pragma once

#include <filesystem>
#include <ostream>
#include <unordered_map>
#include <vector>

#include "Board.h"
#include "Utility/StringParser.h"

using GameMoveFlags = uint8_t;

namespace GameMoveFlag {
enum : uint8_t {
  PromoteKnight = 0b001,
  PromoteBishop = 0b010,
  PromoteRook = 0b011,
  PromoteQueen = 0b100,

  PromotionFlags = 0b111,

  CastleWhiteKingSide = 0b001000,
  CastleWhiteQueenSide = 0b010000,
  CastleBlackKingSide = 0b101000,
  CastleBlackQueenSide = 0b110000,

  CastlingFlags = 0b111000,

  CanCastleOtherSide = 1 << 6,

  EnPassant = 1 << 7,
};
}

struct GameMove {
  Square Start;
  Square Destination;
  Piece MovingPiece;
  Piece DestinationPiece;
  GameMoveFlags Flags = 0;

  std::string Comment;

  bool operator==(const GameMove& m) const {
    return Start == m.Start && Destination == m.Destination &&
           MovingPiece == m.MovingPiece &&
           DestinationPiece == m.DestinationPiece && Flags == m.Flags;
  }
};

struct Branch {
  Branch* Parent;

  uint32_t StartingPly;

  std::vector<GameMove> Moves;

  std::vector<Branch*> Variations;

  Branch(Branch* parent, uint32_t startingPly)
      : Parent(parent), StartingPly(startingPly) {}

  ~Branch() {
    for (Branch* b : Variations) delete b;
  }

  Branch(const Branch&) = delete;
  Branch(Branch&&) = delete;

  Branch& operator=(const Branch&) = delete;
  Branch& operator=(Branch&&) = delete;
};

class Game {
  friend std::ostream& operator<<(std::ostream&, const Game&);

 public:
  Game();
  Game(const std::string& pgn);
  ~Game();

  std::string ToPGN() const;

  const Board& GetPosition() const { return m_Position; }
  uint32_t CurrentPly() const { return m_Ply; }
  Branch* CurrentVariation() const { return m_Variation; }

  LongAlgebraicMove Move(AlgebraicMove move);
  AlgebraicMove Move(LongAlgebraicMove move);

  bool Back();
  bool Forward();
  void ToBeginning();
  void ToEnd();
  void Seek(uint32_t ply);
  void Seek(uint32_t ply, Branch* variation);
  void Delete(uint32_t ply, Branch* variation);
  void SetComment(const std::string& comment);
  void SetComment(std::string&& comment);

 private:
  void Move(GameMove move);

  void FromPGN(const std::string& pgn);
  void ParseVariation(StringParser& sp);

  std::unordered_map<std::string, std::string> m_Header;

  Branch* m_Branches;

  uint32_t m_Ply = 0;
  Branch* m_Variation;
  Board m_Position;
};

std::ostream& operator<<(std::ostream& os, const Game& game);
