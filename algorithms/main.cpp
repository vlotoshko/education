#include <iostream>
#include <iomanip>
#include <vector>

#include "tools.h"
#include "unionfind.h"
#include "sort.h"
#include "search.h"
#include "pquere.h"
#include "graph.h"
#include "digraph.h"


void exch(int *array, int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}


void xsort(int* a, int length) {
    int h = 1;

    while(h < length / 3)
        h = h * 3 + 1;

    while(h >= 1) {
        for(int i = h; i < length; ++i) {

            int key = a[i];
            int j = i;

            while(j - h >= 0 && a[j - h] > key) {
                a[j] = a[j -h];
                j -= h;
            }
            a[j] = key;
        }
        h /= 3;
    }
}


void testAlg() {
    int length = 1024000;
    int *a = new int[length];
    int *tmp = new int[length];

    fillArray(a, length, 0, length - 1);

    Timer t;
    Sort s;

//    st.put(1, 'a');
//    s.show(a, length);
    xsort(a, length);
    std::cout << "time eplaced: " << t.eplacedTime()
              << (s.isSorted(a, length) ? " " : " NOT ") << "sorted\n";
//    s.show(a, length);
    delete[] a;
    delete[] tmp;
}


int main(int argc, char *argv[])
{
  if (argc > 2) {
    int mode = atoi(argv[1]);

    if (mode >= 1 && mode <= 4)
      return testUnionFind(argc, argv);

    if (mode >= 5 && mode < 101)
      return testSort(argc, argv);

    if (mode >= 101 && mode < 200)
      return testPQueue(argc, argv);

    if(mode == 201)
      return testBst(argc, argv);

    if(mode == 301)
      return testGraph(argc, argv);

    if(mode == 401)
      return testSymbolGraph(argc, argv);

    if(mode == 501)
      return testDiGraph(argc, argv);
  }
    else
      if (argc > 1) {
        if(atoi(argv[1]) == 0)
            testAlg();
      }
      else
        std::cout << getRandomAlg() << std::endl;
  return 0;
}
