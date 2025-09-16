#include <iostream>
using namespace std;

struct node {
    string val;
    struct node *next;
};

int main() {
    string arr[5] = {"0", "1", "2", "3", "4"};

    node *next, *last, *head;
    head->val = arr[0];
    head->next = nullptr;
    last = head;
    for(int i=1;i<5;i++) {
        next = new node();
        next->val = arr[i];
        next->next = nullptr;
        last->next = next;
        last = next;
    }

    last = head;
    while(last != nullptr) {
        cout << last->val << endl;
        last = last->next;
    }

    cout << endl;

    next = head;
    last = head;
    while(head->next != nullptr) {
        next = head->next;
        head->next = next->next;
        next->next = last;
        last = next;
    }   
    head = next;

    last = head;
    while(last != nullptr) {
        cout << last->val << endl;
        last = last->next;
    }

    return 0;
}