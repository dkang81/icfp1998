#ifndef POUSSE_H
#define POUSSE_H

#include <vector>
#include <string>
#include <cstdlib>
#include <memory>

enum Direction { TOP, BOTTOM, LEFT, RIGHT };
enum SquareState { EMPTY, OCCUPIED_X, OCCUPIED_O };
enum GameState { IN_PROGRESS, X_WINS, O_WINS };

int calcRawIndex(int dimension, int x, int y);

class PousseMove {
public:
  Direction direction;
  int rank;
  PousseMove(std::string move);
  PousseMove(Direction d, int r): direction(d), rank(r) {};
  std::string toString() const;
  bool operator== (const PousseMove& other) const {
    return direction == other.direction && rank == other.rank;
  }
};

class PousseBoard {
private:
  int straightCount(std::vector<bool> board) const;
public:
  int dimension;
  bool turn; // true is X's turn; false is O's turn
  std::vector<bool> boardX;
  std::vector<bool> boardO;
  PousseBoard (int d, bool t, std::vector<bool> bX, std::vector<bool> bO):
  dimension(d), turn(t), boardX(bX), boardO(bO) {};
  PousseBoard (int d);
  PousseBoard makeMove(PousseMove m) const;
  std::unique_ptr<std::vector<PousseMove> > moves() const;
  SquareState at(int x, int y) const;
  int rawIndex(int x, int y) const;
  int calcX(int x, int offset, Direction d) const;
  int calcY(int y, int offset, Direction d) const;
  int straightCountX() const;
  int straightCountO() const;
  bool operator== (const PousseBoard& other) const {
    return turn == other.turn && boardX == other.boardX && boardO == other.boardO;
  }
};

class PousseGame {
public:
  int dimension;
  PousseGame(int d) : dimension(d), history(std::vector<PousseBoard>(1, PousseBoard(d))) { };
  std::vector<PousseBoard> history;
  void makeMove(PousseMove m);
  void undo();
  GameState result() const;
  std::vector<bool> board(bool x) const;
  bool turn() const;
};

#endif
