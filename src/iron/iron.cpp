#include <iostream>

using namespace std;

void Merge(const int *A, int p, int mid, int r, int * C) {
    // ���ߣ������ mid
    int i = p;
    // �Ұ�ߣ������ r
    int j = mid + 1;
    // ���ŵ������ p���յ��� r
    int k = p;
    // ����߻����ұߵ�Ԫ��ȫ�źã�������
    while (i <= mid && j <= r) {
        if (A[i] <= A[j]) {
            C[k] = A[i];
            // ÿ��ָ����һ�����Ƚϵ�Ԫ��
            i++;
        } else {
            C[k] = A[j];
            // ÿ��ָ����һ�����Ƚϵ�Ԫ��
            j++;
        }
        // ��Ž����ÿ����Ҫָ���λ��
        k++;
    }

    if (i > mid) {
        // i > mid��˵��������ȫ����������ֻʣ���ұߵ�δ���룬ȫ���Ž�ȥ
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
    // p == r ʱ�������֡�������С��һ�㣬��ֻ��һ��Ԫ�أ������κβ���
    if (p < r) {
        // ȡ�е㣬int ��������ȡ���Ĺ���
        int mid = int((p + r) / 2);
        // ��
        MergeSort(A, p, mid);
        MergeSort(A, mid + 1, r);
        int * C = (int *) malloc(sizeof(int) * 10);
        if (C == nullptr) {
            return;
        }
        // ��
        Merge(A, p, mid, r, C);
        for (int i = p; i <= r; i++) {
            // ÿһ�κϲ��󣬶�Ҫ����ԭ����
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