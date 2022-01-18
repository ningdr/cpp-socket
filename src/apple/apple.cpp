#include <iostream>
#include <cmath>

struct Best {
    int M;
    int i;
    int j;
};

Best profit(int *B, int *S, int L, int R);


int main() {
    using namespace std;
    int B[] = {5, 4, 8, 2, 7, 9};
    int S[] = {3, 3, 7, 1, 6, 7};

    Best b = profit(B, S, 0, 5);
    std::cout << b.M << ", " << b.i << ", " << b.j << std::endl;
}

Best profit(int *B, int *S, int L, int R) {
    if (R == L) {
        Best b{};
        b.M = S[L] - B[L];
        b.i = L;
        b.j = L;
        return b;
    } else {
        Best bL{}, bR{};
        int Mid = int((L + R) / 2);
        std::cout << "Mid: " << Mid << ", L: " << L << ", R: " << R << std::endl;
        bL = profit(B, S, L, Mid);
        bR = profit(B, S, Mid + 1 , R);

        Best bc{};
        int minB = 99999;
        for (int i = L; i <= Mid; i++) {
            if (minB > B[i]) {
                minB = B[i];
                bc.i = i;
            }
        }
        int maxS = -99999;
        for (int j = Mid + 1; j <= R; j++) {
            if (maxS < S[j]) {
                maxS = S[j];
                bc.j = j;
            }
        }
        bc.M = maxS - minB;
        if (bc.M > bL.M && bc.M > bR.M) {
            return bc;
        } else if (bL.M > bR.M) {
            return bL;
        }
        return bR;
    }
}