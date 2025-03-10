#include <iostream>
#include <stack>
using namespace std;

class QueueusingStack{
private:
    stack<int> s1, s2;

public:
    void enqueue(int x){
        s1.push(x);
    }

    int dequeue(){
        if (s2.empty()){
            if (s1.empty()){
                cout << "Queue is empty" << endl;
                return -1;
            }
            while (!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        int popped = s2.top();
        s2.pop();
        return popped;
    }

    int front(){
        if (s2.empty()){
            if (s1.empty()){
                cout << "Queue is empty" << endl;
                return -1;
            }
            while (!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    bool isEmpty(){
        return s1.empty() && s2.empty();
    }
};

int main(){
    QueueusingStack q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << q.dequeue() << endl;
    cout << q.front() << endl;

    return 0;
}
