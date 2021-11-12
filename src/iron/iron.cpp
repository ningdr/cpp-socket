#include "spdlog/spdlog.h"


const int n = 6;
int p[]= {0, 1, 4, 4, 7, 8, 9};
int R[n + 1] = {0,};

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
        /// R[k]������֮ǰ��ÿһ������⣬ֻ�����ȫ�������ֵ�����ܵó� k ����ʱ�����ֵ
        R[k] = q;
//        for (int i = 0; i < k; i++) {
//            /// ���ֵ��¼����
//            R[k] = max(R[i] + R[k - i], p[k]);
//        }
    }
    for (int i = 1; i <= n; i++) {
        spdlog::debug("Length: {}, Max value: {}", i, R[i]);
    }
    return 0;
}
