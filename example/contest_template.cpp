// Utilities library
#include <bitset>
#include <functional>
#include <utility>
#include <tuple>
#include <limits>
#include <cinttypes>
#include <cassert>
// Strings library
#include <cctype>
#include <cstring>
#include <string>
//Containers library
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
// Algorithms library
#include <algorithm>
// Iterators library
#include <iterator>
// Numerics library
#include <cmath>
#include <complex>
#include <valarray>
#include <numeric>
// Input/Ouput library
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>
// Regular expressions library
#include <regex>

// Support code

using std::size_t;

template <class Function>
void repeat(std::size_t n, Function f) {
    while(n--) f();
}

template <class T>
T input_value(std::istream& input = std::cin) {
    T value;
    input >> value;
    return value;
}

// Program code

int main() {
    std::ios_base::sync_with_stdio(false);
}