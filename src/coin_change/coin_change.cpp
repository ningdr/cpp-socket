#include <iostream>

#include "spdlog/spdlog.h"
// https://www.bilibili.com/video/BV1gp4y1t7xe/?spm_id_from=333.788.recommend_more_video.3
int change(int *A, int Alen, int M) {

    int *f = (int *) malloc(sizeof(int) * (M + 1));
    f[0] = 0;
    for (int i = 1; i <= M; i++) {
        f[i] = std::numeric_limits<int>::max();
    }
    for (int i = 1; i <= M; i++) {
        /// last coin A[0]¡¢A[1]¡¢A[2]¡¢A[3]...
        /// f[i] = min{f[i - A[0]], f[i - A[1]], f[i - A[2]]}
        for (int j = 0; j < Alen; j++) {
            if (i >= A[j] && f[i - A[j]] != std::numeric_limits<int>::max()) {
                f[i] = std::min(f[i], f[i - A[j]] + 1);
            }
        }
    }
    if (f[M] == std::numeric_limits<int>::max()) {
        f[M] = -1;
    }
    int res = f[M];
    free(f);
    return res;
}

int main() {
    spdlog::set_level(spdlog::level::debug);
    int A[] = {2, 5, 7};
    int m = change(A, 3, 27);
    spdlog::debug("min number: {}", m);
    return 0;
}
