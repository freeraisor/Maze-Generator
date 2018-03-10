#include "types.h"
#include <vector>
#include <stack>
#include <ctime>
#include <random>

class Generator {

public:

  Generator();
  Generator(int &weigth, int &heigth);
  Generator(const Generator &data);

  // Главный алгоритм. Создание лабиринта.
  bool generateLabirint();

  // Главный алгоритм. Ищет путь, случайным переходом.
  int findWay();

  // Ищет путь по правилу правой руки.
  int findWayRightHand();

  Cell* getFirstPoint();
  int setFirstPoint(Cell* first);

  Cell* getEndPoint();
  int setEndPoint(Cell* end);

  int setBothPoint(Cell* first, Cell* end);


  // Возвращает матрицу лабиринта
  std::vector<std::vector<int> > getLabirintMatrix();
  std::vector<std::vector<int> > getWayMatrix();

  // Возвращает все типы данных лабиринта в специальной структуре
  DataMaze getDataMaze();


private:

  // Набор данных для лабиринта
  DataMaze maze_matrix;
  DataMaze way_matrix;

  // Число непосещенных вершин для генератора
  int unvisited_count;

  // Стек для вершин
  std::stack<Cell> stack_cell;

  // Инициализация матрицы стенками на четных позициях и ячейками на нечетных.
  void initMazeMatrix(const int &weigth, const int &heigth);

  // Устанавливает значения в ячейку
  void setValueInCell(Cell &cell, int key_word);

  // Получение массива ячеек непосещенных соседей
  std::vector<Cell> getNeighbours(const Cell &current, int rangeNeighbh = 2, int type_visited_1 = VISITED, int type_visited_2 = VISITED);
  // Получение массива ячеек непосещеных ячеек по всему лабиринту
  std::vector<Cell> getUnvisited(int type_visited_1 = VISITED, int type_visited_2 = VISITED);
  // Получение количества непосещеных вершин
  int getUnvisitedCount(int type_visited_1 = VISITED, int type_visited_2 = VISITED);

  // Очистить стенку и создать переход
  void createWay(const Cell &first, const Cell &last);

  // Проверка за выход за диапозоны лабиринта
  bool isInsight(const unsigned int &x, const unsigned int &y);
  bool isInsight(const Cell cell);

  // Функция возвращает максимальное значение
  int max(const int &a, const int &b);

  // Функция выбора рандомного числа
  int random(const int &min, const int &max);

  // Функция выбора соседа по правилу правой руки
  Cell rightway(Cell current);

};