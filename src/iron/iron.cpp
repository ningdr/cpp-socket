#include "spdlog/spdlog.h"


const int n = 6;
int p[]= {0, 1, 4, 4, 7, 8, 9};
int R[n + 1] = {0,};

/// 1、确定状态，数组的每个元素的含义，数组的大小
/// 2、转移方程
/// 3、初始条件、边界条件
/// 4、计算顺序

int main() {
    using namespace std;
    spdlog::set_level(spdlog::level::debug);
    R[1] = p[1];
    for (int k = 2; k <= n; k++) {
        int q = p[k];
        for (int i = 0; i <= int(k / 2); i++) {
            if (q < R[i] + R[k - i]) {
                q = R[i] + R[k - i];
            }
        }
        /// R[k]依赖于之前的每一步的求解，只有求出全部的最大值，才能得出 k 长度时的最大值
        R[k] = q;
//        for (int i = 0; i < k; i++) {
//            /// 最大值记录错误
//            R[k] = max(R[i] + R[k - i], p[k]);
//        }
    }
    for (int i = 1; i <= n; i++) {
        spdlog::debug("Length: {}, Max value: {}", i, R[i]);
    }
    return 0;
}
