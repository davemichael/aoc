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

  class Cube {
   public:
    Cube() : cube_() {}  // default-initialize
    Cube(const Cube& src) = default;
    Cube& operator+=(const Cube& src) {
      ForEach([this, &src](int& val, size_t i, size_t j, size_t k) {
        cube_[i][j][k] += src.cube_[i][j][k];
      });
      return *this;
    }

    void Set(size_t x, size_t y, size_t z) {
      cube_[x][y][z] = 1;
    }

    void FloodFill(int x, int y, int z) {
      if (x < 0 || y < 0 || z < 0 ||
          x == dim || y == dim || z == dim) return;
      if (cube_[x][y][z] == 1) return;
      cube_[x][y][z] = 1;
      FloodFill(x+1, y, z);
      FloodFill(x-1, y, z);
      FloodFill(x, y+1, z);
      FloodFill(x, y-1, z);
      FloodFill(x, y, z+1);
      FloodFill(x, y, z-1);
    }

    void Invert() {
      ForEach([](int& val, size_t, size_t, size_t) {
        val = val ? 0 : 1;
      });
    }
  
    int SurfaceArea() {
      int surface_area = 0;
      ForEach([this, &surface_area](int&, size_t i, size_t j, size_t k) {
        surface_area += exposed_sides(cube_, i, j, k);
      });
      return surface_area;
    }

   private:
    int cube_[dim][dim][dim];

    void ForEach(std::function<void(int&, size_t i, size_t j, size_t k)> fn) {
      for (size_t i = 0; i < dim; ++i) {
        for (size_t j = 0; j < dim; ++j) {
          for (size_t k = 0; k < dim; ++k) {
            fn(cube_[i][j][k], i, j, k);
          }
        }
      }
    }

  };

}  // namespace

int main() {
  Cube cube;

  int x,y,z;
  while (std::cin >> x >> y >> z) {
    cube.Set(x, y, z);
  }

  std::cout << cube.SurfaceArea() << std::endl;

  Cube interior(cube);
  interior.FloodFill(0, 0, 0);
  interior.Invert();
  cube += interior;
  std::cout << cube.SurfaceArea() << std::endl;
}
