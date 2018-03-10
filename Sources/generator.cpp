#include "../Headers/generator.h"
#include <iostream>

Generator::Generator() {

  maze_matrix.weigth = 0;
  maze_matrix.heigth = 0;
  unvisited_count = 0;

  maze_matrix.end_point = nullptr;
  maze_matrix.start_point = nullptr;

  maze_matrix.maze = {{}};
}

Generator::Generator(int &weigth, int &heigth) {

  maze_matrix.weigth = weigth;
  maze_matrix.heigth = heigth;
  unvisited_count = 0;

  maze_matrix.end_point = nullptr;
  maze_matrix.start_point = nullptr;

  initMazeMatrix(weigth, heigth);
}

Generator::Generator(const Generator &data) {

}

Cell* Generator::getFirstPoint() {
  return maze_matrix.start_point;
}

int Generator::setFirstPoint(Cell* first) {
  if (maze_matrix.maze[first->x][first->y] != WALL) {
    maze_matrix.start_point = first;
    return 0;
  }
  else {
    return 1;
  }
}

Cell* Generator::getEndPoint() {
  return maze_matrix.end_point;
}

int Generator::setEndPoint(Cell* end) {
  if (maze_matrix.maze[end->x][end->y] != WALL) {
    maze_matrix.end_point = end;
    return 0;
  }
  else {
    return 1;
  }
}

int Generator::setBothPoint(Cell* first, Cell* end) {

  if (!setFirstPoint(first)) {
    setValueInCell(*first, START);
  }
  else {
    return 1;
  }

  if (!setEndPoint(end)) {
    setValueInCell(*end, END);
  }
  else {
    return 2;
  }

}

std::vector<std::vector<int>> Generator::getLabirintMatrix() {
  return maze_matrix.maze;
}

std::vector<std::vector<int>> Generator::getWayMatrix() {
  return way_matrix.maze;
}

DataMaze Generator::getDataMaze() {
  return maze_matrix;
}

void Generator::setValueInCell(Cell &cell, int key_word) {
  maze_matrix.maze[cell.x][cell.y] = key_word;
}

void Generator::initMazeMatrix(const int &weigth, const int &heigth) {

  for (int i = 0; i < heigth; i++) {
    std::vector<int> bufer;
    maze_matrix.maze.push_back(bufer);
    for (int j = 0; j < weigth; j++) {
      if ((i % 2 != 0 && j % 2 != 0) && (i < heigth - 1 && j < weigth - 1)) {
        maze_matrix.maze[i].push_back(CELL);
      }
      else {
        maze_matrix.maze[i].push_back(WALL);
      }
    }
  }
}

std::vector<Cell> Generator::getNeighbours(const Cell &current, int rangeNeighbh, int type_visited_1, int type_visited_2) {

  unsigned int newx = 0, newy = 0;
  std::vector<Cell> result;

  // Правый сосед
  newx = current.x + rangeNeighbh;
  newy = current.y;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != type_visited_1 && maze_matrix.maze[newx][newy] != type_visited_2)) {
      Cell cell = Cell(newx, newy);
      result.push_back(cell);
    }
  }


  // Верхний сосед
  newx = current.x;
  newy = current.y - rangeNeighbh;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != type_visited_1 && maze_matrix.maze[newx][newy] != type_visited_2)) {
      Cell cell = Cell(newx, newy);
      result.push_back(cell);
    }
  }


  // Левый сосед
  newx = current.x - rangeNeighbh;
  newy = current.y;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != type_visited_1 && maze_matrix.maze[newx][newy] != type_visited_2)) {
      Cell cell = Cell(newx, newy);
      result.push_back(cell);
    }
  }


  // Нижний сосед
  newx = current.x;
  newy = current.y + rangeNeighbh;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != type_visited_1 && maze_matrix.maze[newx][newy] != type_visited_2)) {
      Cell cell = Cell(newx, newy);
      result.push_back(cell);
    }
  }

  return result;
}

std::vector<Cell> Generator::getUnvisited(int type_visited_1, int type_visited_2) {

  std::vector<Cell> result;
  for (unsigned int i = 0; i < maze_matrix.heigth; i++) {
    for (unsigned int j = 0; j < maze_matrix.weigth; j++) {
      if (maze_matrix.maze[i][j] != WALL && maze_matrix.maze[i][j] != type_visited_1 && maze_matrix.maze[i][j] != type_visited_2) {
        Cell cell = Cell(i, j);
        result.push_back(cell);
      }
    }
  }

  return result;
}

int Generator::getUnvisitedCount(int type_visited_1, int type_visited_2) {

  int count = 0;
  for (unsigned int i = 0; i < maze_matrix.heigth; i++) {
    for (unsigned int j = 0; j < maze_matrix.weigth; j++) {
      if (maze_matrix.maze[i][j] !=  WALL&& maze_matrix.maze[i][j] != type_visited_1 && maze_matrix.maze[i][j] != type_visited_2) {
        count++;
      }
    }
  }

  return count;
}

bool Generator::generateLabirint() {

  Cell *first = maze_matrix.start_point;
  setValueInCell(*first, VISITED);
  unvisited_count = getUnvisitedCount();
  Cell curent_cell = *first, choosen;

  // Генерация лабиринта методом бэк-трекинга

  do {

    std::vector<Cell> neighbours = getNeighbours(curent_cell);
    if (neighbours.size() != 0) {

      int random_cell_index = random(0, neighbours.size() - 1);
      choosen = neighbours[random_cell_index];
      stack_cell.push(curent_cell);
      createWay(curent_cell, choosen);

      curent_cell = choosen;
      setValueInCell(choosen, VISITED);
      unvisited_count--;
    }
    else if (!stack_cell.empty()) {
      curent_cell = stack_cell.top();
      stack_cell.pop();
    }
    else {
      std::vector<Cell> unvisited = getUnvisited();
      int random_cell_index = random(0, unvisited.size() - 1);
      curent_cell = unvisited[random_cell_index];
      setValueInCell(curent_cell, VISITED);
      unvisited_count--;
    }

  } while (unvisited_count != 0);

  return true;
}

void Generator::createWay(const Cell &first, const Cell &last) {

  int dx = abs(last.x - first.x), dy = abs(last.y - first.y);

  if (!dx == !dy) {
    return;
  }
  else if (!dy) {
    Cell cell = Cell(max(first.x, last.x) - 1, first.y);
    setValueInCell(cell, VISITED);
  }
  else if (!dx) {
    Cell cell = Cell(first.x, max(first.y, last.y) - 1);
    setValueInCell(cell, VISITED);
  }
}

int Generator::findWay() {

  Cell first = *maze_matrix.start_point;
  setValueInCell(first, WAY);
  way_matrix = maze_matrix;
  int count = 0;
  Cell curent_cell = first, choosen;

  // Прохождение лабиринта методом бэк-трекинга

  do {

    std::vector<Cell> neighbours = getNeighbours(curent_cell, 1, WAY, WAS);
    if (neighbours.size() != 0) {

      stack_cell.push(curent_cell);
      int random_cell_index = random(0, neighbours.size() - 1);
      choosen = neighbours[random_cell_index];
      curent_cell = choosen;
      setValueInCell(choosen, WAY);
      count++;
    }
    else if (!stack_cell.empty()) {
      setValueInCell(curent_cell, WAS);
      count--;
      curent_cell = stack_cell.top();
      stack_cell.pop();
    }
    else {
      return 0;
    }

  } while (curent_cell != *maze_matrix.end_point);

  std::vector<std::vector<int>> bufer = maze_matrix.maze;
  maze_matrix.maze = way_matrix.maze;
  way_matrix.maze = bufer;
  setBothPoint(maze_matrix.start_point, maze_matrix.end_point);
  return count;
}

// Доработать. 
Cell Generator::rightway(Cell current) {

  // Против часовой стрелки
  int newx, newy;
  // на 12 часов
  newx = current.x;
  newy = current.y - 1;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != WAY && maze_matrix.maze[newx][newy] != WAS)) {
      return Cell(newx, newy);
    }
  }

  // На 9 часов
  newx = current.x - 1;
  newy = current.y;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != WAY && maze_matrix.maze[newx][newy] != WAS)) {
      return Cell(newx, newy);
    }
  }

  // На 6 часов
  newx = current.x;
  newy = current.y + 1;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != WAY && maze_matrix.maze[newx][newy] != WAS)) {
      return Cell(newx, newy);
    }
  }

  // На 3 часа
  newx = current.x + 1;
  newy = current.y;
  if (isInsight(newx, newy)) {
    if (maze_matrix.maze[newx][newy] != WALL && (maze_matrix.maze[newx][newy] != WAY && maze_matrix.maze[newx][newy] != WAS)) {
      return Cell(newx, newy);
    }
  }

}

int Generator::findWayRightHand() {

  Cell first = Cell(1, 1);
  setValueInCell(first, WAY);
  way_matrix = maze_matrix;
  int count;

  Cell curent_cell = first, choosen;

  do {

    std::vector<Cell> neighbours = getNeighbours(curent_cell, 1, WAY, WAS);
    if (neighbours.size() != 0) {

      stack_cell.push(curent_cell);
      choosen = rightway(curent_cell);
      curent_cell = choosen;
      setValueInCell(choosen, WAY);
      count++;
    }
    else if (!stack_cell.empty()) {
      setValueInCell(curent_cell, WAS);
      count--;
      curent_cell = stack_cell.top();
      stack_cell.pop();
    }
    else {
      return 0;
    }

  } while (curent_cell != *maze_matrix.end_point);

  std::vector<std::vector<int>> bufer = maze_matrix.maze;
  maze_matrix.maze = way_matrix.maze;
  way_matrix.maze = bufer;

  return count;
}

bool Generator::isInsight(const unsigned int &x, const unsigned int &y) {
  return ((x < maze_matrix.heigth) && (y < maze_matrix.weigth)) ? true : false;
}

int Generator::random(const int &min, const int &max) {
  return rand() % (max - min + 1) + min;
}

int Generator::max(const int &a, const int &b) {
  return (a < b) ? b : a;
}
