#include <bits/stdc++.h>

using namespace std;

class Stack {
private:
    vector<int> items;
    int capacity;
    int top;
public:
    Stack(int size) {
        capacity = size;
        items.resize(size);
        top = -1;
    }
    
    bool isEmpty() {
        return top == -1;
    }

    void push(int value) {
        if (top == capacity - 1) {
            cout << "stack overflow!" << endl;
        }
        items[++top] = value;
    }

    int peek() {
        if (isEmpty()) {
            return INT_MIN;
        }
        return items[top];
    }

    void pop() {
        if (isEmpty()) return;
        top--;
    }
};

void moveDisk(char from, char to, int disk) {
    cout << "Move the disk " << disk << " from " << from << " to " << to << endl;
}

void move(Stack &src, Stack &des, char s, char d) {
    int top1 = src.peek();
    src.pop();
    int top2 = des.peek();
    des.pop();
    if (top1 == INT_MIN) {
        src.push(top2);
        moveDisk(d, s, top2);
    }
    else if (top2 == INT_MIN) {
        des.push(top1);
        moveDisk(s, d, top1);
    }
    else if (top1 > top2) {
        src.push(top1);
        src.push(top2);
        moveDisk(d, s, top2);
    }
    else {
        des.push(top2);
        des.push(top1);
        moveDisk(s, d, top1);
    }

}

void towerOfHanoiIterative(int noOfDisks, Stack &src, Stack &aux, Stack &des) {
    int noOfMoves = pow(2, noOfDisks) - 1;
    char s = 'S', a = 'A', d = 'D';
    if (noOfDisks % 2 == 0) {
        swap(a, d);
    }
    for (int i = noOfDisks; i >= 1; i--) {
        src.push(i);
    }
    for (int i = 1; i <= noOfMoves; i++) {
        if (i % 3 == 1) {
            move(src, des, s, d);
        }
        else if (i % 3 == 2) {
            move(src, aux, s, a);
        }
        else {
            move(aux, des, a, d);
        }
    }
}

int main() {
    int n = 3;
    Stack src = Stack(n);
    Stack aux = Stack(n);
    Stack des = Stack(n);

    towerOfHanoiIterative(n, src, aux, des);
    return 0;
}