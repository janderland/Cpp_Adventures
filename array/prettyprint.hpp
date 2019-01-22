#include <vector>
#include <utility>

namespace jander {

  std::vector<std::vector<int>> prettyprint(int A) {
    int size = (2*A)-1;
    std::vector<std::vector<int>> array(size);
    for (auto& row : array) row.resize(size);

    for (int i=0; i<A; i++)
      for (int x=i; x<size-i; x++)
        for (int y=i; y<size-i; y++)
          array[x][y] = A-i;

    return array;
  }

}
