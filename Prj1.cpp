#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;



// Alias templates to simplify type declarations
template <class T>
using ELEM = vector<T>;         // Defines ELEM as a vector of elements of type T
template <class T>
using VEC = vector<ELEM<T>>;    // Defines VEC as a vector of ELEM vectors
template <class T>
using action_t = T(*)(int);     // Defines action_t as a pointer to a function that takes an int and returns T 
template <class T>
using pred_t = bool (*)(T);     // Defines pred_t as a pointer to a function that takes T and returns bool
template <class T>
using map_t = T(*)(T, T);       // Defines map_t as a pointer to a function that takes two T and returns T



// Function to print elements of a vector with optional parentheses
template <class T>
void printElem(ELEM<T>& v) {
    if (v.size() > 1) {          // Print '(' if more than one element
        cout << "("; 
    }
    for (auto i : v) {
        cout << i << " ";       // Print each element followed by a space   

    }
     
    if (v.size() > 1) {
        cout << ")";            // Print ')' if more than one element
    }

    
}



// Initializes a VEC with individual elements of a given connection vector
template <class T>
void initVec(VEC<T> &v, ELEM<T> &&conn) {
    for (int i = 0; i < conn.size(); i++) {
        v.push_back(ELEM<T>({ conn[i] }));    // Adds each element of conn as a separate ELEM in VEC
    }
   
}



// Function to print the contents of a VEC, with formatting
template <class T>
void printVec(VEC<T> &v) {
    cout << "[";                    // Start of VEC output
    for (auto &row : v) {           
        printElem(row);             // Print each row in VEC
        cout << ",";
    }
    
    cout << "\b]\n";                // Remove last comma and close the output with ']'
}





// Generates a VEC of N elements using function f
template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> result;
   
    for (int i = 0; i < N; i++) {
        result.push_back(ELEM<T>({ f(i) }));     // Applies f to each i and stores the result as an ELEM in VEC
    }
    
    return result;
}



// Combines elements of two VECs into a single VEC by pairing their rows
template <class T>
VEC<T> zip(VEC<T> &v, VEC<T> &w) {
    VEC<T> result;
    int size = min(v.size(), w.size());        // Use the smaller size of v and w for zipping
    for (int i = 0; i < size; i++) {
        
        ELEM<T> row;
        for (int j = 0; j < v[i].size(); j++) {  // Add elements from v[i] to row
             row.push_back(v[i][j]);
            
        }
        for (int j = 0; j < w[i].size(); j++) {   // Add elements from w[i] to row
            row.push_back(w[i][j]);
            
        }
        
        result.push_back(row);                  // Add combined row to result
    }
    return result;
}



// Filters elements of VEC based on a predicate function
template <class T>
VEC<T> filter(VEC<T>& v, pred_t<T> f) {
    VEC<T> result;
    for (auto& row : v) {
        ELEM<T> filteredRow;
        for (auto& elem : row) {
            if (f(elem)) {                       // Adds element to filteredRow if predicate f is true
                filteredRow.push_back(elem);
            }
        }
        if (!filteredRow.empty()) {
            result.push_back(filteredRow);       // Only add non-empty filtered rows to result
        }
    }
    return result;
}



// Applies a mapping function to each element in a VEC
template <class T>
VEC<T> map(VEC<T>& v, action_t<T> f) {
    VEC<T> result;
    for (auto& row : v) {
        ELEM<T> mappedRow;
        for (size_t i = 0; i < row.size(); i++) {
            mappedRow.push_back(f(row[i]));           // Apply function f to each element and store in mappedRow
        }
        result.push_back(mappedRow);                   // Add mappedRow to result
    }
    return result;
}



// Reduces a VEC to a single ELEM by applying a binary function to each element
template <class T>
ELEM<T> reduce(VEC<T>& v, map_t<T> f, ELEM<T> ident) {
    T result = ident[0];                    // Start with identity value
    for (auto& row : v) {
        for (auto& elem : row) {
            result = f(result, elem);        // Apply function f cumulatively to each element
        }
    }
    return ELEM<T>{result};    // Return result as a single-element ELEM
}


// Simple addition function for two value
template <class T>
T k(T i, T j) {
    return i + j;
}



// Test functions for generate, filter, and map
int f(int x) { return x * x; }                  // Squares input
bool g(int x) { return x > 0; }                 // Returns true if input is positive
int h(int x) { return x > 0 ? 1 : 0; }          // Returns 1 if positive, 0 otherwise



// Main function to test the defined functions
int main() {
    VEC<int> v;
    initVec(v, ELEM<int>{1, 2, 3, 4});             // Initializes v with {1, 2, 3, 4}
    VEC<int> w;
    initVec(w, ELEM<int>{-1, 3, -3, 4});           // Initializes w with {-1, 3, -3, 4}
    printVec(v);
    cout << string(10, '*') << endl;
    printVec(w);
    cout << string(10, '*') << endl;
    VEC<int> z = zip(v, w);                        // Zip v and w into z
    printVec(z);
    cout << string(10, '*') << endl;
    VEC<int> x = zip(z, z);                        // Zip z with itself
    printVec(x);

    cout << string(10, '*') << endl;
    VEC<int> a = generate(10, f);                   // Generate a with squares of first 10 numbers
    printVec(a);
    VEC<int> y = filter(w, g);                      // Filter w with predicate g (positive values)
    printVec(y);
    VEC<int> u = map(w, h);                         // Map w with function h (convert to 1 or 0)
    printVec(u);
    ELEM<int> e = reduce(u, k, ELEM<int>{0});       // Reduce u with addition function k and initial 0
    printElem(e);

    cout << endl << string(10, '$') << endl;
    VEC<string> ws;
    initVec(ws, ELEM<string>{"hello", "there", "franco", "carlacci"});     // Initialize ws with strings
    printVec(ws);
    ELEM<string> es = reduce(ws, k, ELEM<string>{""});      // Concatenate all strings
    printElem(es);

    VEC<char> wc;
    initVec(wc, ELEM<char>{'a', 'b', 'c', 'd'});            // Initialize wc with chars
    cout << endl << string(10, '$') << endl;
    printVec(wc);
    ELEM<char> ec = reduce(wc, k, ELEM<char>{' '});         // Concatenate chars with space
    cout << string(10, '$') << endl;
    printElem(ec);

    return 0;

}
