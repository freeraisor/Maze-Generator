#ifndef TYPES_H
#define TYPES_H
#include <vector>


// Структура стандартной ячейки
struct Cell {

  Cell();
  Cell(int X, int Y);
  Cell(const Cell &buf);

  int x;
  int y;

};

bool operator!=(const Cell &left, const Cell &right);

enum TypesOfCell {

  // Типы ячеек для этапа генерации
  // Пустая ячейка
  CELL = 0,
  // Стена
  WALL,
  // Ячейка старта(для обхода)
  START,
  // Ячейка выхода(для обхода)
  END,
  // Посещеная ячейка
  VISITED,

  WAY,

  WAS

};

// Описание данных лабиринта
struct DataMaze {

  unsigned int weigth;            // Высота
  unsigned int heigth;            // Ширина

  Cell* start_point;               // Точка старта
  Cell* end_point;                 // Точка выхода

  std::vector<std::vector<int> > maze;

};


























#endif // TYPES_H
