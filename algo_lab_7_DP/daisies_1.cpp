#include <vector>
#include "iostream"


int Greedy(std::vector<std::vector<int>> &field, int end_x, int end_y){
    int p1 = 0, p2 = 0;

    int p1_sx = 0, p1_sy = 0;
    int p2_sx = field.size()-1, p2_sy = field[0].size()-1;



    return p1 + p2;
}


int main(){
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> field;
    field.resize(n);

    int tmp;

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            std::cin >> tmp;
            field[i].push_back(tmp);
        }
    }

    int pairs_num;
    std::cin >> pairs_num;
    std::vector<int> ans;

    for (int i = 0; i < pairs_num; ++i){
        int x, y;
        std::cin >> x >> y;
        int amount = Greedy(field, x, y);
        ans.push_back(amount);
    }

    for (int i : ans){
        std::cout << i << "\n";
    }

    return 0;
}