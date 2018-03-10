#ifndef RENDER_H
#define RENDER_H
#include <vector>
#include "generator.h"

enum TRend {

  LABIRINT = 0,
  SOLVER,
  SOLVE

};

void RenderToPNG(const int &Width, const int &Heigth, std::vector<std::vector<int> > &result, int type_render = LABIRINT);

#endif // RENDER_H
