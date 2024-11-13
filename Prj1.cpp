#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
using ELEM = vector<T>;
template <class T>
using VEC = vector<ELEM<T>>;
template <class T>
using action_t = T(*)(int);
template <class T>
using pred_t = bool (*)(T);
template <class T>
using map_t = T(*)(T, T);

template <class T>
void printElem(ELEM<T>& v) {
    if (v.size() > 1) {
        cout << "("; 
    }
    for (auto i : v) {
        cout << i << " ";

    }
     
    if (v.size() > 1) {
        cout << ")";
    }

    
}

template <class T>
void initVec(VEC<T> &v, ELEM<T> &&conn) {
    for (int i = 0; i < conn.size(); i++) {
        v.push_back(ELEM<T>({ conn[i] }));
    }
   
}

template <class T>
void printVec(VEC<T> &v) {
    cout << "[";
    for (auto &row : v) {
        printElem(row);
        cout << ",";
    }
    
    cout << "\b]\n"; 
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> result;
   
    for (int i = 0; i < N; i++) {
        result.push_back(ELEM<T>({ f(i) }));
    }
    
    return result;
}

template <class T>
VEC<T> zip(VEC<T> &v, VEC<T> &w) {
    VEC<T> result;
    int size = min(v.size(), w.size());
    for (int i = 0; i < size; i++) {
        
        ELEM<T> row;
        for (int j = 0; j < v[i].size(); j++) {
             row.push_back(v[i][j]);
            
        }
        for (int j = 0; j < w[i].size(); j++) {
            row.push_back(w[i][j]);
            
        }
        
        result.push_back(row);
    }
    return result;
}

template <class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) {
    VEC<T> result;
    for (auto& row : v) {
        ELEM<T> filteredRow;
        for (auto& elem : row) {
            if (f(elem)) {
                filteredRow.push_back(elem);
            }
        }
        if (!filteredRow.empty()) {
            result.push_back(filteredRow);
        }
    }
    return result;
}

template <class T>
VEC<T> map(VEC<T>& v, action_t<T> f) {
    VEC<T> result;
    for (auto& row : v) {
        ELEM<T> mappedRow;
        for (size_t i = 0; i < row.size(); i++) {
            mappedRow.push_back(f(row[i]));
        }
        result.push_back(mappedRow);
    }
    return result;
}

template <class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) {
    T result = ident[0];
    for (auto& row : v) {
        for (auto& elem : row) {
            result = f(result, elem);
        }
    }
    return ELEM<T>{result};
}

template <class T>
T k(T i, T j) {
    return i + j;
}

int f(int x) { return x * x; }
bool g(int x) { return x > 0; }
int h(int x) { return x > 0 ? 1 : 0; }

int main() {
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});
    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});
    printVec(v);
    cout << string(10, '*') << endl;
    printVec(w);
    cout << string(10, '*') << endl;
    VEC<int> z = zip(v, w);
    printVec(z);
    cout << string(10, '*') << endl;
    VEC<int> x = zip(z, z);
    printVec(x);

    cout << string(10, '*') << endl;
    VEC<int> a = generate(10, f); // f is a function that squares
    printVec(a);
    VEC<int> y = filter(w, g); // g is a bool function that returns true if arg > 0
    printVec(y);
    VEC<int> u = map(w, h); // h is like g but returns 1 or 0
    printVec(u);
    ELEM<int> e = reduce(u, k, ELEM<int>{0});
    printElem(e);

    cout << endl << string(10, '$') << endl;
    VEC<string> ws;
    initVec(ws, ELEM<string>{"hello", "there", "franco", "carlacci"});
    printVec(ws);
    ELEM<string> es = reduce(ws, k, ELEM<string>{""});
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});
    cout << endl << string(10, '$') << endl;
    printVec(wc);
    ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});
    cout << string(10, '$') << endl;
    printElem(ec);

    return 0;

}
