#include <iostream>
#include <queue>
using namespace std;

class StackusingQueue{
private:
    queue<int> q1, q2;
    
public:
    void push(int x){
        q1.push(x);
    }

    int pop(){
        if (q1.empty()){
            cout << "Stack is empty" << endl;
            return -1;
        }
        while (q1.size() > 1){
            q2.push(q1.front());
            q1.pop();
        }

        int popped = q1.front();
        q1.pop();
        
        swap(q1, q2);
        
        return popped;
    }

    int top(){
        if (q1.empty()){
            cout << "Stack is empty" << endl;
            return -1;
        }
        while (q1.size() > 1){
            q2.push(q1.front());
            q1.pop();
        }

        int topele = q1.front();
        q2.push(q1.front());
        q1.pop();
        
        swap(q1, q2);
        
        return topele;
    }

    bool isEmpty(){
        return q1.empty();
    }
};

int main(){
    StackusingQueue s;

    s.push(1);
    s.push(2);
    s.push(3);

    cout << s.pop() << endl;
    cout << s.top() << endl;

    return 0;
}