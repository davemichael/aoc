#include <iostream>
#include <vector>

namespace {
  const size_t dim = 23;

  int exposed_sides(const int cube[dim][dim][dim],
                    size_t x, size_t y, size_t z) {
    if (cube[x][y][z] == 0) return 0;
    return 6 -
           cube[x-1][y][z] -
           cube[x+1][y][z] -
           cube[x][y-1][z] -
           cube[x][y+1][z] -
           cube[x][y][z-1] -
           cube[x][y][z+1];
  }

  void flood_fill(int cube[dim][dim][dim],
                  int x, int y, int z) {
    if (cube[x][y][z] == 1) return;
    if (x < 0 || y < 0 || z < 0 ||
        x == dim || y == dim || z == dim) return;
    cube[x][y][z] = 1;
    flood_fill(cube, x+1, y, z);
    flood_fill(cube, x-1, y, z);
    flood_fill(cube, x, y+1, z);
    flood_fill(cube, x, y-1, z);
    flood_fill(cube, x, y, z+1);
    flood_fill(cube, x, y, z-1);
  }

  void print(int cube[dim][dim][dim]) {
    for (size_t i = 0; i < dim; ++i) {
      for (size_t j = 0; j < dim; ++j) {
        for (size_t k = 0; k < dim; ++k) {
          if (cube[i][j][k]) {
            std::cout << i << " " << j << " " << k << std::endl;
          }
        }
      }
    }
  }

  void copy(int src[dim][dim][dim], int dest[dim][dim][dim]) {
    for (size_t i = 0; i < dim; ++i) {
      for (size_t j = 0; j < dim; ++j) {
        for (size_t k = 0; k < dim; ++k) {
          dest[i][j][k] = src[i][j][k];
        }
      }
    }
  }

  void invert(int cube[dim][dim][dim]) {
    for (size_t i = 0; i < dim; ++i) {
      for (size_t j = 0; j < dim; ++j) {
        for (size_t k = 0; k < dim; ++k) {
          cube[i][j][k] = cube[i][j][k] ? 0 : 1;
        }
      }
    }
  }

  void addto(int src[dim][dim][dim], int dest[dim][dim][dim]) {
    for (size_t i = 0; i < dim; ++i) {
      for (size_t j = 0; j < dim; ++j) {
        for (size_t k = 0; k < dim; ++k) {
          if (dest[i][j][k] == 0 && src[i][j][k] == 1) {
            // std::cout << "copying: " << i << " " << j << " " << k << std::endl;
            dest[i][j][k] += src[i][j][k];
          }
        }
      }
    }
  }

  int surface_area(int cube[dim][dim][dim]) {
    int surface_area = 0;
    for (size_t i = 0; i < dim; ++i) {
      for (size_t j = 0; j < dim; ++j) {
        for (size_t k = 0; k < dim; ++k) {
          surface_area += exposed_sides(cube, i, j, k);
        }
      }
    }
    return surface_area;
  }
}

int main() {

  int cube[dim][dim][dim];
  for (size_t i = 0; i < dim; ++i) {
    for (size_t j = 0; j < dim; ++j) {
      for (size_t k = 0; k < dim; ++k) {
        cube[i][j][k] = 0;
      }
    }
  }

  int x,y,z;
  //int mx = 0;
  while (std::cin >> x >> y >> z) {
    //mx = std::max(x, std::max(y, std::max(z, mx)));

    cube[x][y][z] = 1;
  }

  std::cout << surface_area(cube) << std::endl;

  int interior[dim][dim][dim];
  copy(cube, interior);
  flood_fill(interior, 0, 0, 0);
  invert(interior);
  addto(interior, cube);
  std::cout << surface_area(cube) << std::endl;
}
