#include "../Headers/render.h"
#include <SFML/Graphics.hpp>

void RenderToPNG(const int &Width, const int &Heigth, std::vector<std::vector<int> > &result, int type_render) {

  sf::Image img;
  // Размер в пикселях одной ячейки
  int cell_demension = 5;
  int ImgHei = Heigth*cell_demension;
  int ImgWei = Width*cell_demension;
  int img_i = 0;
  int img_j = 0;
  img.create(ImgHei, ImgWei);
  for (int i = 0; i < result.size(); i++) {
    img_j = 0;
    for (int j = 0; j < result[i].size(); j++) {

      if(result[i][j] == VISITED) {
        // Алгоритм обхода области пикселей 5 на 5
        for (int c_i = 0; c_i < cell_demension; c_i++) {
          for (int c_j = 0; c_j < cell_demension; c_j++) {
            img.setPixel(img_j + c_j, img_i + c_i, sf::Color::White);
          }
        }

      }
      if(result[i][j] == WALL) {
        // Алгоритм обхода области пикселей 5 на 5
        for (int c_i = 0; c_i < cell_demension; c_i++) {
          for (int c_j = 0; c_j < cell_demension; c_j++) {
            img.setPixel(img_j + c_j, img_i + c_i, sf::Color::Black);
          }
        }
      }

      if(result[i][j] == START) {
        // Алгоритм обхода области пикселей 5 на 5
        for (int c_i = 0; c_i < cell_demension; c_i++) {
          for (int c_j = 0; c_j < cell_demension; c_j++) {
            img.setPixel(img_j + c_j, img_i + c_i, sf::Color::Green);
          }
        }
      }

      if(result[i][j] == END) {
        // Алгоритм обхода области пикселей 5 на 5
        for (int c_i = 0; c_i < cell_demension; c_i++) {
          for (int c_j = 0; c_j < cell_demension; c_j++) {
            img.setPixel(img_j + c_j, img_i + c_i, sf::Color::Green);
          }
        }
      }

      if (type_render == SOLVE || type_render == SOLVER) {

        if(result[i][j] == WAY) {
          // Алгоритм обхода области пикселей 5 на 5
          for (int c_i = 0; c_i < cell_demension; c_i++) {
            for (int c_j = 0; c_j < cell_demension; c_j++) {
              img.setPixel(img_j + c_j, img_i + c_i, sf::Color::Red);
            }
          }
        }

        if(result[i][j] == WAS) {
          // Алгоритм обхода области пикселей 5 на 5
          for (int c_i = 0; c_i < cell_demension; c_i++) {
            for (int c_j = 0; c_j < cell_demension; c_j++) {
              img.setPixel(img_j + c_j, img_i + c_i, sf::Color::Blue);
            }
          }
        }
      }
      img_j += cell_demension;
    }
    img_i += cell_demension;
  }

  switch (type_render) {

    case LABIRINT: {
      img.saveToFile("NoWayLabirint.png");
      break;
    }

    case SOLVER: {
      img.saveToFile("WayLabirintR.png");
      break;
    }

    case SOLVE: {
      img.saveToFile("WayLabirint.png");
    }

  }


}
