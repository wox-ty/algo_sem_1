#include "iostream"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    bool check = true, check_sub=true;

    std::cin >> N;

    char word[N];
    for (int i = 0; i < N; ++i) {
        std::cin >> word[i];
    }

    for (int a = 0; a < (N/2); ++a)
    {
        if (word[a] != word[N - 1 - a])
        {
            for (int b = a; b < (N / 2); ++b)
            {
                if (word[b + 1] != word[N - 1 - b])
                {
                    check_sub = false;
                    break;
                }
            }
            if (not check_sub)
            {
                check_sub = true;
                for (int c = a; c < (N / 2); ++c)
                {
                    if (word[c] != word[N - c - 2])
                    {
                        check_sub = false;
                        break;
                    }
                }
                if (not check_sub)
                {
                    check = false;
                }
            }
        }
        break;
    }

    if (check) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

        return 0;
}