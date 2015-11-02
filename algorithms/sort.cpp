#include <iostream>
#include <iomanip>
#include <map>
#include "sort.h"
#include "tools.h"

bool Sort::less(const int &a, const int &b) {
    return a < b;
}

void Sort::show(int *array, int length) {
    for (int i = 0; i < length; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

void Sort::exch(int *array, int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

bool Sort::isSorted(int *array, int length) {
    for (int i = 1; i < length; ++i) {
        if (array[i - 1] != array[i] && !less(array[i-1], array[i]))
            return false;
    }
    return true;
}

void Sort::merge(int *array, int lo, int mid, int hi, int *aux) {
    int i = lo;
    int j = mid + 1;

    // copying array to aux
    for (int k = lo; k <= hi; k++)
       aux[k]  = array[k];

    // copying array from aux
    for (int k = lo; k <= hi; k++) {
        if (i > mid)
            array[k] = aux[j++];// copy from right part
        else
            if (j > hi)
                array[k] = aux[i++];// copy from left part
            else
                if (less(aux[j], aux[i]))
                    array[k] = aux[j++];// copy from right part
                else
                    array[k] = aux[i++];// copy from left part
    }
}


int Sort::partition(int *array, int lo, int hi) {
    int i = lo;
    int j = hi + 1;
    int v = array[lo];
    while (true) {
        while (less(array[++i], v))
            if (i == hi)
                break;
        while (less(v, array[--j]))
            if (j == lo)
                break;
        if (i >= j)
            break;
        exch(array, i, j);
    }
    exch(array, lo, j);
    return j;
}


int Sort::partitionM(int *array, int lo, int hi) {
    int i = lo;
    int j = hi + 1;
    int ind = lo;

    if (hi - lo >= 3) {
        bool a_less_b = less(array[lo], array[lo+1]);
        bool b_less_c = less(array[lo+1], array[lo+2]);
        bool c_less_a = less(array[lo+2], array[lo]);

        if (c_less_a && a_less_b)
            ind = lo;
        else
            if (a_less_b && b_less_c)
                ind = lo+1;
            else
                if (b_less_c && c_less_a)
                    ind = lo+2;
    }

    if (ind != lo)
        exch(array, lo, ind);

    int v = array[lo];

    while (true) {
        while (less(array[++i], v))
            if (i == hi)
                break;
        while (less(v, array[--j]))
            if (j == lo)
                break;
        if (i >= j)
            break;
        exch(array, i, j);
    }
    exch(array, lo, j);
    return j;
}


void Sort::sink(int *array, int pos, int length) {
//    std::cout << std::endl << "a[" << pos << "] = " << array[pos] << std::endl;
    ++pos;
    while (2 * pos <= length) {
        int j = 2 * pos;
//        if(j < length && less(array[j], array[j + 1]))
        if(j < length && less(array[j - 1], array[j]))
            j++;
//        if(less(array[j], array[pos]))
        if(less(array[j - 1], array[pos - 1]))
            break;
        exch(array, j - 1, pos - 1);
//        std::cout << "exch: " << pos - 1 << " and " << j - 1 << std::endl;
        pos = j;
    }
}


// Dummy sort
template < typename Alg >
void Sort::sort(int *array, int length) {
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        for (int i = 0; i < length - 1; i++) {
            if (array[i] != array[i + 1] && !less(array[i], array[i + 1])) {
                exch(array, i, i + 1);
                isSorted = false;
            }
        }
    }
}

// Buble sort
template <>
void Sort::sort< SortBuble >(int *array, int length) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length - i - 1; ++j) {
            if (array[j] != array[j + 1] && !less(array[j], array[j + 1]))
                exch(array, j, j + 1);
        }
    }
}


// Shake sort
template <>
void Sort::sort< SortShake >(int *array, int length) {
    for (int left = 0, right = length - 1; left < right;) {

        for (int j = left; j < right; ++j) {
            if (array[j] != array[j + 1] && less(array[j + 1], array[j]))
                exch(array, j, j + 1);
        }
        right--;

        for (int j = right; j > left; --j) {
            if (array[j] != array[j - 1] && less(array[j], array[j - 1]))
                exch(array, j - 1, j);
        }
        left++;
    }
}


// Comb sort
template <>
void Sort::sort< SortComb >(int *array, int length) {
    int h = length;
    bool swapped = true;
    while (h > 1 || swapped) {
        if (h > 1)
            h /= 1.24733;

        swapped = false;
        for (int i = 0; i + h < length; i++) {
            if (less(array[i + h], array[i])) {
                exch(array, i, i + h);
                swapped = true;
            }
        }
    }
}


// Selection sort
template <>
void Sort::sort< SortSelection >(int *array, int length) {
    for (int i = 0; i < length; i++) {
        int min = i;
        for (int j = i; j < length - 1; ++j) {
            if (array[min] != array[j + 1] && !less(array[min], array[j + 1]))
                min = j + 1;
        }
        exch(array, min, i);
    }
}

// Insertion sort
template <>
void Sort::sort< SortInsertion >(int *array, int length) {
    for (int i = 1; i < length; i++) {
        int key = array[i];
        int j = i - 1;

        while(j > 0 && array[j] > key) {
            array[j + 1] = array[j];
            --j;
        }
        array[j] = key;
    }
}

// Gnome sort
template <>
void Sort::sort< SortGnome >(int *array, int length) {
    for (int i = 1; i < length; i++) {
        for (int j = i; j > 0 && less(array[j], array[j - 1]); j--) {
            exch(array, j, j - 1);
        }
    }
}

// Insertion binary sort
template <>
void Sort::sort< SortInsertionB >(int *array, int length) {
    for (int i = 1; i < length; i++) {
        for (int j = i; j > 0 && less(array[j], array[j - 1]); j--) {
            exch(array, j, j - 1);
        }
    }
}

// Shell sort
template <>
void Sort::sort< SortShell >(int *array, int length) {
    int h = 1;
    while (h < length / 3)
        h = 3*h + 1;

    while (h >= 1) {
        for (int i = h; i < length; i++) {
            for (int j = i; j >= h && less(array[j], array[j - h]); j -= h) {
                exch(array, j, j - h);
            }
        }
        h /= 3;
    }
}

// Merge sort
template <>
void Sort::sort< SortMerge >(int *array, int lo, int hi, int *aux) {

    if (hi <= lo)
        return;

    int mid = lo + (hi - lo) / 2;

    sort< SortMerge >(array, lo, mid, aux);
    sort< SortMerge >(array, mid+1, hi, aux);
    merge(array, lo, mid, hi, aux);
}


// Merge with insertion sort
template <>
void Sort::sort< SortMergeIns >(int *array, int lo, int hi, int *aux) {

    if (hi - lo <= 15) {
        sort< SortInsertion >(&array[lo], hi - lo + 1);
        return;
    }

    int mid = lo + (hi - lo) / 2;

    sort< SortMergeIns >(array, lo, mid, aux);
    sort< SortMergeIns >(array, mid+1, hi, aux);
    merge(array, lo, mid, hi, aux);
}

// Merge upward sort
template <>
void Sort::sort< SortMergeUp >(int *array, int length, int *aux) {
    for (int sz = 1; sz < length; sz += sz)
        for (int lo = 0; lo < length - sz; lo += sz+sz)
            merge(array, lo, lo+sz-1, (lo + sz + sz - 1) < (length - 1) ? lo + sz + sz - 1 : length - 1, aux);
}


// Quick sort
template <>
void Sort::sort< SortQuick >(int *array, int lo, int hi) {
    if (hi <= lo)
        return;
    int j = partition(array, lo, hi);
    sort< SortQuick >(array, lo, j - 1);
    sort< SortQuick >(array, j + 1, hi);
}

// Quick with insertion sort
template <>
void Sort::sort< SortQuickIns >(int *array, int lo, int hi) {
    if (hi - lo <= 15) {
        sort< SortInsertion >(&array[lo], hi - lo + 1);
        return;
    }

    int j = partition(array, lo, hi);
    sort< SortQuickIns >(array, lo, j - 1);
    sort< SortQuickIns >(array, j + 1, hi);
}

// Quick sort (mediana)
template <>
void Sort::sort< SortQuickMed >(int *array, int lo, int hi) {
    if (hi <= lo)
        return;
    int j = partitionM(array, lo, hi);
    sort< SortQuickMed >(array, lo, j - 1);
    sort< SortQuickMed >(array, j + 1, hi);
}

// Quick sort (3parts)
template <>
void Sort::sort< SortQuick3 >(int *array, int lo, int hi) {
    if (hi <= lo)
        return;

    int lt = lo;
    int i = lo + 1;
    int gt = hi;
    int v = array[lo];

    while(i <= gt) {
        if (array[i] == v)
            i++;
        else if (less(array[i], v)) {
            exch(array, lt++, i++);
        }
        else
            exch(array, i, gt--);
    }
    sort< SortQuick3 >(array, lo, lt - 1);
    sort< SortQuick3 >(array, gt + 1, hi);
}

// Heap sort
template <>
void Sort::sort< SortHeap >(int *array, int length) {
//    --length;
    for (int i = length / 2; i >= 0; i--) {
        sink(array, i, length);
//        show(array, length);
    }

//    std::cout << std::endl;
//    show(array, length);

    while(length > 1) {
        exch(array, 0, --length);
        sink(array, 0, length);
//        std::cout << "a" << std::endl;
    }
}

int testSort(int argc, char *argv[]) {

    double oldtime = 1;

    if (argc > 2) {

        int beginCount = atoi(argv[2]);
        int times = atoi(argv[3]) + 1;

        for (int i = 0; i < times; ++i) {

//            cout  << "generating array... " << flush;
            int array[beginCount];

            fillArray(array, beginCount, 0, beginCount - 1);
//            cout  << "Ok! ";

            Sort s;
            Timer t;

            switch (atoi(argv[1])) {

            // ----------- Changing sort -----------
            case 11:
                std::cout << "Dummy sort: ";
                s.sort(array, beginCount);
                break;
            case 12:
                std::cout << "Buble sort: ";
                s.sort< SortBuble >(array, beginCount);
                break;
            case 13:
                std::cout << "Shake sort: ";
                s.sort< SortShake >(array, beginCount);
                break;
            case 14:
                std::cout << "Comb sort: ";
                s.sort< SortComb >(array, beginCount);
                break;
            case 15:
                std::cout << "Quick sort: ";
                s.sort< SortQuick >(array, 0, beginCount-1);
                break;
            case 16:
                std::cout << "QuickIns sort: ";
                s.sort< SortQuickIns >(array, 0, beginCount-1);
                break;
            case 17:
                std::cout << "QuickMed sort: ";
                s.sort< SortQuickMed >(array, 0, beginCount-1);
                break;
            case 18:
                std::cout << "Quick 3-parts sort: ";
                s.sort< SortQuick3 >(array, 0, beginCount-1);
                break;


            // ----------- Selection sort -----------
            case 21:
                std::cout << "Selection sort: ";
                s.sort< SortSelection >(array, beginCount);
                break;

            // ----------- Insertion sort -----------
            case 31:
                std::cout << "Insertion sort: ";
                s.sort< SortInsertion >(array, beginCount);
                break;

            case 32:
                std::cout << "Shell sort: ";
                s.sort< SortShell >(array, beginCount);
                break;

            // ----------- Merging sort -----------
            case 41:
                std::cout << "Merge sort: ";
            {
                int aux[beginCount];
                s.sort< SortMerge >(array, 0, beginCount-1, aux);
            }
                break;
            case 42:
                std::cout << "Merge-upward sort: ";
            {
                int aux[beginCount];
                s.sort< SortMergeUp >(array, beginCount, aux);
            }
                break;

            // ----------- Hybrid sort -----------
            case 51:
                std::cout << "Gnome sort: ";
                s.sort< SortGnome >(array, beginCount);
                break;
            case 52:
                std::cout << "Insertion binary sort: stub";
//                s.sort< SortInsertionB >(array, beginCount);
                break;
            case 53:
                std::cout << "Timsort: ";
            {
                int aux[beginCount];
                s.sort< SortMergeIns >(array, 0, beginCount-1, aux);
            }
                break;

            // ----------- Other sort algorithms-----------
            case 91:
                std::cout << "Heap sort: ";
                s.sort< SortHeap >(array, beginCount);
                break;

             default:
                break;
            }

            double time = t.eplacedTime();
            std::cout << std::left << (s.isSorted(array, beginCount) ? "" : "NOT ") << std::setw(10) << "sorted" ;
            std::cout  << "count: " << std::setw(10) << beginCount << "time eplaced: " << std::setw(10)
                       << time << "ratio: " << time/oldtime << std::endl;
//            s.show(array, beginCount);
            beginCount += beginCount;
            if (time != 0)
                oldtime = time;
            else
                oldtime = 1;
        }
    }
    std::cout << std::endl;
    return 0;
}



std::string getRandomAlg() {
    std::map< int, std::string > algs;
    algs.insert(std::pair<int, std::string>(1, "Dummy"));
    algs.insert(std::pair<int, std::string>(2, "Buble"));
    algs.insert(std::pair<int, std::string>(3, "Shake"));
    algs.insert(std::pair<int, std::string>(4, "Comb"));
    algs.insert(std::pair<int, std::string>(5, "Quick"));
    algs.insert(std::pair<int, std::string>(6, "Selection"));
    algs.insert(std::pair<int, std::string>(7, "Insertion"));
    algs.insert(std::pair<int, std::string>(8, "Shell"));
    algs.insert(std::pair<int, std::string>(9, "Merge"));
    algs.insert(std::pair<int, std::string>(10, "Heap"));

    return algs[ random<int>(1, 10)];
}
