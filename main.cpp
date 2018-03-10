///////////////////////////////////////////////////
// Ларюшкин Илья. 2018 год.                      //
// Генератор лабиринта                          //
///////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include "render.h"

// Код генерации лабиринта и прозождения двумя способами.
// Вход: ширина и длина лабиринта в ячейках
// Выход: 3 изображения. 
//  1 изображение - вид лабиринта. 
//  2 изображение - путь в лабиринте, пройденный случайным образом
//  3 изображение - путь в лабиринте, пройденный по правилу правой руки

int main() {

  int heigth, width;
  std::cout << "Enter dimensions of labirint" << std::endl;
  std::cin >> heigth >> width;
  // Из-за особенности алгоритма генерации, размеры лабиринта должны быть нечетными
  // так как в случае четности будет дублироваться внешняя стенка
  // Это условие позволяет по любым входным данным генерировать лабиринт
  if (!(heigth % 2)) {
    heigth++;
  }
  if (!(width % 2)) {
    width++;
  }
  std::cout << "Your dimension is " << heigth << "x" << width << std::endl;

  // Инициализация рандома.
  srand(std::time(0));
  // Создание объекта лабиринта.
  Generator labirint = Generator(width, heigth);
  // Инициализация начальных ячеек.
  Cell* first = new Cell(1, 1);
  Cell* end = new Cell(width-2, heigth-2);

  
  std::string choose = "No";
  std::cout << "Do you want use standart Start(Upper left corner) and End(Bottom right corner) point or chose by yourself?(Y/N)" << std::endl;
  std::cin >> choose;
  if (choose == "N" || choose == "No" || choose == "n" || choose == "no") {
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0, result = 0;
    do {
      std::cout << "Enter x and y coordinats for start point" << std::endl;
      std::cin >> x1 >> y1;
      std::cout << "Enter x and y coordinats for end point" << std::endl;
      std::cin >> x2 >> y2;
      Cell* bfirst = new Cell(x1, y1); 
      Cell* bend = new Cell(x2, y2);
      result = labirint.setBothPoint(first, end);
      if (result == 1) std::cout << "First point can not be set" << std::endl;
      if (result == 2) std::cout << "Second point can not be set" << std::endl;
      first = bfirst, end = bend;
      delete bfirst, bend; 
    } while (!result);
  }
  labirint.setBothPoint(first, end);
  // Генерация лабиринта
  int gen = labirint.generateLabirint();
  labirint.setBothPoint(first, end);
  if (gen) {
    std::vector<std::vector<int>> result = labirint.getLabirintMatrix();
    std::cout << "Labirint was generated" << std::endl;
    RenderToPNG(width, heigth, result, LABIRINT);
    std::cout << "Labirint was rendered" << std::endl;
    std::cout << "Count of real step - " << gen << std::endl;
  }
  else {
    std::cout << "Labirint was not generated" << std::endl;
  }
  
  
  std::cout << std::endl;
  
  // Прохождение лабиринта
  int find = labirint.findWay();
  labirint.setBothPoint(first, end);
  if (find) {
    std::cout << "Labirint was solved" << std::endl;
    std::vector<std::vector<int>> result = labirint.getWayMatrix();
    RenderToPNG(width, heigth, result, SOLVE);
    std::cout << "Solved labirint was rendered" << std::endl;
    std::cout << "Count of real step - " << find << std::endl;
  }
  else {
    std::cout << "Solve do not exist" << std::endl;
  }

  return 0;
}
