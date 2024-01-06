#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

// Expression Tree Node
struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;
};

// Function to create a new tree node
TreeNode* createNode(string value) {
    TreeNode* newNode = new TreeNode;
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to construct Expression Tree from prefix expression
TreeNode* constructExpressionTree(string prefix) {
    stack<TreeNode*> st;
    TreeNode* newNode, *operand1, *operand2;

    for (int i = prefix.size() - 1; i >= 0; --i) {
        if (isspace(prefix[i]))
            continue;

        if (!isOperator(prefix[i])) {
            newNode = createNode(string(1, prefix[i]));
            st.push(newNode);
        } else {
            newNode = createNode(string(1, prefix[i]));

            operand1 = st.top();
            st.pop();
            operand2 = st.top();
            st.pop();

            newNode->left = operand1;
            newNode->right = operand2;

            st.push(newNode);
        }
    }

    return st.top();
}

// Non-recursive Inorder traversal of Expression Tree
void inorderTraversal(TreeNode* root) {
    if (!root)
        return;

    stack<TreeNode*> st;
    TreeNode* current = root;

    while (current || !st.empty()) {
        while (current) {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        cout << current->value << " ";

        current = current->right;
    }
}

// Non-recursive Preorder traversal of Expression Tree
void preorderTraversal(TreeNode* root) {
    if (!root)
        return;

    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* current = st.top();
        st.pop();

        cout << current->value << " ";

        if (current->right)
            st.push(current->right);

        if (current->left)
            st.push(current->left);
    }
}

// Non-recursive Postorder traversal of Expression Tree
void postorderTraversal(TreeNode* root) {
    if (!root)
        return;

    stack<TreeNode*> st;
    stack<TreeNode*> result;
    st.push(root);

    while (!st.empty()) {
        TreeNode* current = st.top();
        st.pop();
        result.push(current);

        if (current->left)
            st.push(current->left);

        if (current->right)
            st.push(current->right);
    }

    while (!result.empty()) {
        cout << result.top()->value << " ";
        result.pop();
    }
}

int main() {
    string prefixExpression = "*+abc*de";
    TreeNode* root = constructExpressionTree(prefixExpression);

    cout << "Inorder traversal: ";
    inorderTraversal(root);
    cout << endl;

    cout << "Preorder traversal: ";
    preorderTraversal(root);
    cout << endl;

    cout << "Postorder traversal: ";
    postorderTraversal(root);
    cout << endl;

    return 0;
}
