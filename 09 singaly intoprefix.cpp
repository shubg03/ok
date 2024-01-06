#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// NOTE:
// Use Stack as an ADT

class Stack {
private:
    struct Node {
        char data;
        Node* next;
    };

    Node* top;

public:
    Stack() {
        top = NULL;
    }

    bool isEmpty() {
        return (top == NULL);
    }

    void push(char value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return '\0';
        } else {
            Node* temp = top;
            char popped = temp->data;
            top = top->next;
            delete temp;
            return popped;
        }
    }

    char peek() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return '\0';
        } else {
            return top->data;
        }
    }

    ~Stack() {
        while (top != NULL) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

string infixToPrefix(string infix) {
    Stack stack;
    string prefix;
    reverse(infix.begin(), infix.end());

    for (size_t i = 0; i < infix.length(); ++i) {
        char character = infix[i];
        if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9')) {
            prefix += character;
        } else if (character == '(') {
            stack.push(character);
        } else if (character == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                prefix += stack.pop();
            }
            if (!stack.isEmpty() && stack.peek() != '(') {
                cout << "Invalid expression.\n";
                return "";
            } else {
                stack.pop();  // Pop the '(' from the stack
            }
        } else {
            while (!stack.isEmpty() && precedence(character) <= precedence(stack.peek())) {
                prefix += stack.pop();
            }
            stack.push(character);
        }
    }

    while (!stack.isEmpty()) {
        if (stack.peek() == '(' || stack.peek() == ')') {
            cout << "Invalid expression.\n";
            return "";
        }
        prefix += stack.pop();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}

int main() {
    string infixExpression;

    cout << "Enter an infix expression: ";
    getline(cin, infixExpression);

    string prefixExpression = infixToPrefix(infixExpression);
    if (!prefixExpression.empty()) {
        cout << "The prefix expression is: " << prefixExpression << endl;
    }

    return 0;
}

