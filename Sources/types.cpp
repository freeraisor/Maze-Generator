#include <../Headers/types.h>

Cell::Cell() {
  x = 0;
  y = 0;
}

Cell::Cell(int X, int Y) {
  x = X;
  y = Y;
}

Cell::Cell(const Cell &buf) {
  x = buf.x;
  y = buf.y;
}

bool operator!=(const Cell &left, const Cell &right) {
  return ((left.x == right.x) && (left.y == right.y)) ? false : true;
}
