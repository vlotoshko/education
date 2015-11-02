#include "pquere.h"
#include "tools.h"
#include "iostream"

PQueue::PQueue(int size) : a_(new int[size + 1]), maxsize_(size + 2), currsize_(0) {
    for (int i = 0; i < max(); ++i) {
        a_[i] = -1;
    }
}

PQueue::~PQueue() {
    delete[] a_;
}

bool PQueue::less(const int &i, const int &j) {
    return a_[i] < a_[j];
}

void PQueue::show() const {
    for (int i = 1; i <= currsize(); ++i) {
        std::cout << a_[i] << ' ';
    }
    std::cout << std::endl;
}

void PQueue::exch(int i, int j) {
    int temp = a_[i];
    a_[i] = a_[j];
    a_[j] = temp;
}


void PQueue::insert(const int item) {
    a_[++currsize_] = item;
    swim(currsize_);

    if(currsize_ == max()) {
        delMin();
    }
}

void PQueue::delMin() {
    int idx_min = currsize() / 2 - 1;

    for(int i = idx_min + 1; i <= currsize(); ++i) {
        if (less(i, idx_min))
            idx_min = i;
    }

    a_[idx_min] = a_[currsize_];
    a_[currsize_--] = -1;
    sink(idx_min);
}

int PQueue::delMax() {
    if(!isEmpty()) {
        int result = a_[1];
        a_[1] = a_[currsize_];
        a_[currsize_--] = -1;
        sink(1);
        return result;
    }
    else
        return -1;
}

void PQueue::swim(int pos) {
    while(pos > 1 && less(pos/2, pos)) {
        exch(pos/2, pos);
        pos /= 2;
    }
}

void PQueue::sink(int pos) {
    while (2 * pos <= currsize()) {
        int j = 2 * pos;
        if(j < currsize() && less(j, j + 1))
            j++;
        if(less(j, pos))
            break;
        exch(j, pos);
        pos = j;
    }
}



int testPQueue(int argc, char *argv[]) {

    if (argc > 2) {
        int count = atoi(argv[2]);
        int size = atoi(argv[3]);

        PQueue pq(size);

        for(int i = 0; i < count; ++i) {
            pq.insert(random<int>(0, count));
        }

        std::cout << std::endl;
        pq.show();

        while(!pq.isEmpty())
            std::cout << pq.delMax() << ' ';
    }
    std::cout << std::endl;
    return 0;
}
