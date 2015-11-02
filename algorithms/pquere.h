#ifndef PQUERE_H
#define PQUERE_H

class PQueue {
public:
    PQueue(int);
    ~PQueue();
    void insert(const int);
    int delMax();
    bool less(const int& a, const int& b);
    void exch(int i, int j);

    int max() const { return maxsize_ - 1; }
    int currsize() const { return currsize_; }
    bool isEmpty() const { return currsize_ <= 0; }
    void show() const;
    void delMin();
private:
   void swim(int pos);
   void sink(int pos);
   int *a_;
   int maxsize_;
   int currsize_;
};

int testPQueue(int argc, char *argv[]);
#endif // PQUERE_H
