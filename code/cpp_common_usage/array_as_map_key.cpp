#include <iostream>  
#include <unordered_map>  
#include <array>  

struct ArrayHasher {
    std::size_t operator()(const std::array<int, 3>& a) const {
        std::size_t h = 0;

        for (auto e : a) {
            h ^= std::hash<int>{}(e)+0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};
int main() {
    std::unordered_map< std::array<int, 3>, int, ArrayHasher >  test;
    test[{{0, 1, 2}}] = 1;
}