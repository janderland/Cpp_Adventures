#include <vector>
#include <utility>

namespace jander {

  std::vector<std::vector<unsigned int>> prettyprint(unsigned int A) {
    const unsigned int size = (2*A)-1;
    std::vector<std::vector<unsigned int>> array(size);
    for (auto& row : array) row.resize(size);

    for (unsigned int i=0; i<A; i++)
      for (unsigned int x=i; x<size-i; x++)
        for (unsigned int y=i; y<size-i; y++)
          array[x][y] = A-i;

    return array;
  }

}
