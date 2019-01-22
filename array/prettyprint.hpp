#include <vector>
#include <utility>
#include <iostream>

using std::max;
using std::vector;

namespace jander {

vector<vector<int>> prettyprint_simple(int A) {
  int size = (2*A)-1;
  vector<vector<int>> array(size, vector<int>(size));

  for(int i=0; i<A; i++)
    for(int x=i; x<size-i; x++)
      for(int y=i; y<size-i; y++)
        array[x][y] = A-i;

  return array;
}


vector<vector<int>> prettyprint_param(int A) {
  vector<vector<int>> array;

  auto set = [&](int i, int j) {
    array.back().push_back(max(A-i, A-j));
  };

  for(int i=0; i<=A-1; i++) {
    array.push_back({});
    for(int j=0; j<=A-1; j++) set(i, j);
    for(int j=A-2; j>=0; j--) set(i, j);
  }

  for(int i=A-2; i>=0; i--) {
    array.push_back({});
    for(int j=0; j<=A-1; j++) set(i, j);
    for(int j=A-2; j>=0; j--) set(i, j);
  }

  return array;
}

}
