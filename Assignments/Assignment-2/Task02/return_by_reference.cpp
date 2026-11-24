#include <iostream>
#include <vector>

int& highestMark(int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[best]) {
            best = i;
        }
    }
    return marks[best];
}

const int& highestMarkConst(const int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[best]) {
            best = i;
        }
    }
    return marks[best];
}

int highestMarkCopy(const int marks[], int n) {
    int best = marks[0];
    for (int i = 1; i < n; ++i) {
        if (marks[i] > best) {
            best = marks[i];
        }
    }
    return best;
}

int main() {
    int marks[5] = {72, 88, 91, 84, 79};
    highestMark(marks, 5) += 2;

    std::cout << "Marks after +2 moderation on highest: ";
    for (int m : marks) std::cout << m << ' ';
    std::cout << '\n';

    std::cout << "Const ref highest: " << highestMarkConst(marks, 5) << '\n';
    std::cout << "Copy highest     : " << highestMarkCopy(marks, 5) << '\n';

    std::vector<int> vec = {70, 85, 90};
    const int* oldAddr = &vec[2];
    for (int i = 0; i < 50; ++i) {
        vec.push_back(60 + i);
    }
    const int* newAddr = &vec[2];
    std::cout << "Vector reallocated? " << std::boolalpha << (oldAddr != newAddr) << '\n';
    return 0;
}
