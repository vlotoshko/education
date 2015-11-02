#ifndef SORT_H
#define SORT_H

#include <string>

class SortDummy{};
class SortBuble{};
class SortShake{};
class SortComb{};
class SortSelection{};
class SortInsertion{};
class SortGnome{};
class SortShell{};
class SortMerge{};
class SortMergeIns{};
class SortMergeUp{};
class SortInsertionB{};
class SortQuick{};
class SortQuickIns{};
class SortQuickMed{};
class SortQuick3{};
class SortHeap{};


// Int sort
class Sort {
public:
    // overloaded sort template functions
    template < typename Alg = SortDummy >
    void sort(int *array, int length);

    template < typename Alg>
    void sort(int *array, int lo, int hi, int *aux);

    template < typename Alg>
    void sort(int *array, int length, int *aux);

    template < typename Alg>
    void sort(int *array, int lo, int hi);

    void show(int *array, int length);
    bool less(const int& a, const int& b);
    void exch(int *array, int i, int j);
    bool isSorted(int *array, int length);
private:
    void merge(int *array, int lo, int mid, int hi, int *aux);
    int partition(int *array, int lo, int hi);
    int partitionM(int *array, int lo, int hi);
    void sink(int *array, int pos, int length);
};

int testSort(int argc, char *argv[]);
std::string getRandomAlg();

#endif // SORT_H
