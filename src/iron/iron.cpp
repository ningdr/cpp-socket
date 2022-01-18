#include <iostream>

using namespace std;

void Merge(const int *A, int p, int mid, int r, int * C) {
    // 左半边，最大是 mid
    int i = p;
    // 右半边，最大是 r
    int j = mid + 1;
    // 待排的起点是 p，终点是 r
    int k = p;
    // 把左边或者右边的元素全排好，放入结果
    while (i <= mid && j <= r) {
        if (A[i] <= A[j]) {
            C[k] = A[i];
            // 每次指向下一个待比较的元素
            i++;
        } else {
            C[k] = A[j];
            // 每次指向下一个待比较的元素
            j++;
        }
        // 存放结果，每次需要指向空位置
        k++;
    }

    if (i > mid) {
        // i > mid，说明左半边已全部放入结果，只剩下右边的未放入，全部放进去
        for (; j <= r; j++, k++) {
            C[k] = A[j];
        }
    } else {
        for (; i <= mid; i++, k++) {
            C[k] = A[i];
        }
    }
}

void MergeSort(int *A, int p, int r) {
    // p == r 时，代表“分”到了最小的一层，即只有一个元素，不做任何操作
    if (p < r) {
        // 取中点，int 含有向下取整的功能
        int mid = int((p + r) / 2);
        // 分
        MergeSort(A, p, mid);
        MergeSort(A, mid + 1, r);
        int * C = (int *) malloc(sizeof(int) * 10);
        if (C == nullptr) {
            return;
        }
        // 合
        Merge(A, p, mid, r, C);
        for (int i = p; i <= r; i++) {
            // 每一次合并后，都要更新原数组
            A[i] = C[i];
        }
        free(C);
    }
}

int main() {

    int a[] = {5, 4, 3, 2, 8, 9, 0, 1, 6, 7};
    int last = sizeof(a) / sizeof(int) - 1;
    MergeSort(a, 0, last);
    for (int i : a) {
        cout << i << endl;
    }
    return 0;
}