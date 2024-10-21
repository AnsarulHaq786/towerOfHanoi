#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<int> A, B, C;
int num, step=0;

void display(stack<int> A, stack<int> B, stack<int> C) {
    for (int i = num; i > 0; i--) {
        cout << (i <= A.size() ? to_string(A.top()) : " ") << "\t";
        cout << (i <= B.size() ? to_string(B.top()) : " ") << "\t";
        cout << (i <= C.size() ? to_string(C.top()) : " ") << "\n";
        if (i <= A.size()) A.pop();
        if (i <= B.size()) B.pop();
        if (i <= C.size()) C.pop();
    }
    cout << "A\tB\tC\n";
    cout <<"Step:"<<step<<endl;
    step++;
}

void toh(stack<int>& source, stack<int>& auxiliary, stack<int>& sink, int n) {
    if (n == 1) {
        sink.push(source.top());
        source.pop();
        display(A, B, C);
        return;
    }
    toh(source, sink, auxiliary, n - 1);
    toh(source, auxiliary, sink, 1);
    toh(auxiliary, source, sink, n - 1);
}

int main() {
    cout << "Enter number of discs: ";
    cin >> num;
    for (int i = num; i > 0; i--) {
        A.push(i);
    }
    display(A, B, C);  
    toh(A, B, C, num);  
    return 0;
}
