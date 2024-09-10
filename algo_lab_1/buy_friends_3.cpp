#include "iostream"

int evkid(int x, int y){
    int res;
    while (x != 0 and y != 0) {
        if (x > y) {
            x = x % y;
        } else {
            y = y % x;
        }
    }
    res = x + y;
    return res;
}


int main(){

    int A, B;

    std::cin >> A >> B;

    std::cout << evkid(A, B) << "\n";

    return 0;
}