#include <iostream>
#include "unionfind.h"
using namespace std;


int threeSum(int arr[], int size) {
  int cnt = 0;
  for (int i = 0; i < size; i++)
      for (int j = i + 1; j < size; j++)
          for (int k = j + 1; k < size; k++)
              if(arr[i] + arr[j] + arr[k] == 0) {
//                  cout << arr[i] << '\t'<< arr[j] << '\t'<< arr[k] << endl;
                  cnt++;
              }
  return cnt;
}

double timeTrial(int size) {
    int arr[size];
    int MAX = 1000000;
    fillArray(arr, size, -MAX, MAX);

    Timer t;
    cout << threeSum(arr, size) << endl;
    return t.eplacedTime();
}

void testTriple(int count) {
    int size = 250;
    double prev = timeTrial(size/2);
    double time;
    for( int i = 0; i < count; ++i) {
        time = timeTrial(size);

        cout << "size: " << size << ";\ttime eplaced: " << time << ";\tratio: " << time/prev << endl;
        size += size;
        prev = time;
    }
}

std::ostream& operator << (std::ostream &out, const UF& uf) {
    for (int i = 0; i < uf.count(); ++i)
        out << uf.id(i) << ' ';
    return out;
}

UF::UF(int count) : count_(count), components_(count), finds_(0), unions_(0) {
    id_ = new int[count];
    for (int i = 0; i < count_; ++i)
        id_[i] = i;
    sz_ = new int[count];
    for (int i = 0; i < count_; ++i)
        sz_[i] = 1;
}

UF::~UF() {
    delete[] id_;
    delete[] sz_;
}

template< class T >
int UF::find(int p) const {
    return id(p);
}

template< class T >
void UF::union_(const int p, const int q) {
    unions_++;
    int pID = find(p);
    int qID = find(q);

//    cout << pID << '-' << qID << endl;
    if (pID == qID)
        return;

    for (int i= 0; i < count_; ++i)  {
        if (id(i) == pID)
            id_[i] = qID;
    }
    --components_;
}


// explicit specialization TQuickUnion
template<>
int UF::find< TQuickUnion >(int p) const {
    while(p != id(p))
        p = id(p);
    return p;
}

template<>
void UF::union_< TQuickUnion >(const int p, const int q) {
    unions_++;
    int pRoot = find<TQuickUnion>(p);
    int qRoot = find<TQuickUnion>(q);

//    cout << p << '-' << q << "; " << pRoot << '-' << qRoot << endl;
    if (pRoot == qRoot)
        return;

    id_[pRoot] = qRoot;
    --components_;
}

// explicit specialization TWeightedQuickUnion
template<>
void UF::union_< TWeightedQuickUnion >(const int p, const int q) {
    unions_++;
    int pRoot = find<TQuickUnion>(p);
    int qRoot = find<TQuickUnion>(q);

//    cout << p << '-' << q << "; " << pRoot << '-' << qRoot << endl;
    if (pRoot == qRoot)
        return;

    if(sz_[pRoot] < sz_[qRoot])
    {
        id_[pRoot] = qRoot;
        sz_[qRoot] += sz_[pRoot];
    } else {

        id_[qRoot] = pRoot;
        sz_[pRoot] += sz_[qRoot];
    }
    --components_;
}

template< class Alg = TQuickSearch, typename P >
void testUF(RandomPair<P> *pairs, int count) {

    UF uf(count);
//    cout << endl << uf << endl;
//    cout << "components: " << uf.components() << endl;

    for (int i = 0; i < count; ++i) {
        uf.union_<Alg>(pairs[i].a(), pairs[i].b());
//        cout << uf << endl;
    }
//    cout << "components: " << uf.components() << endl;
    cout << endl << "finds: " << uf.finds() << " unions: " << uf.unions() << " components: " << uf.components() << endl;
//    return uf.components();
}

int testUnionFind(int argc, char *argv[]) {
    int beginCount = 1000;
    double oldtime = 1;

    if (argc > 2) {

        int times = atoi(argv[2]);

        for (int i = 0; i < times; ++i) {

            cout  << endl << "genetarting pairs... " << flush;
            RandomPair<int> pairs[beginCount];
            for (int j = 0; j < beginCount; ++j) {
                pairs[j].generate(0, beginCount-1);
            }

            cout  << "Ok!" << endl;

            Timer t;

            switch (atoi(argv[1])) {
            case 1:
                cout  << "Triple: ";
                testTriple(beginCount);
                break;
            case 2:
                cout  << "TQuickSearch: ";
                testUF<TQuickSearch, int>(pairs, beginCount);
                break;
            case 3:
                cout  << "TQuickUnion: ";
                testUF<TQuickUnion, int>(pairs, beginCount);
                break;
            case 4:
                cout  << "TWeightedQuickUnion: ";
                testUF<TWeightedQuickUnion, int>(pairs, beginCount);
                break;
            default:
                break;
            }

            double time = t.eplacedTime();
            cout  << "count: " << beginCount << " time eplaced: " << time << "; ratio = " << time/oldtime << endl;
            beginCount += beginCount;
            if (time != 0)
                oldtime = time;
            else
                oldtime = 1;
        }
    }
    return 0;
}
