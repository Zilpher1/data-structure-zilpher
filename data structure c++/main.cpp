#include <iostream>
#include <queue>
using namespace std;

// TreeNode structure
struct TreeNode
{
    int empID;
    string empName;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int id, string name) : empID(id), empName(name), left(nullptr), right(nullptr) {}
};

class BinaryTree
{
private:
    TreeNode *root;

    // Helper function for recursive insertion
    TreeNode *insertHelper(TreeNode *node, int empID, string empName)
    {
        if (node == nullptr)
        {
            return new TreeNode(empID, empName);
        }

        if (empID < node->empID)
        {
            node->left = insertHelper(node->left, empID, empName);
        }
        else if (empID > node->empID)
        {
            node->right = insertHelper(node->right, empID, empName);
        }

        return node;
    }

    // Helper function for recursive search
    TreeNode *searchHelper(TreeNode *node, int empID)
    {
        if (node == nullptr || node->empID == empID)
        {
            return node;
        }

        if (empID < node->empID)
        {
            return searchHelper(node->left, empID);
        }
        else
        {
            return searchHelper(node->right, empID);
        }
    }

    // Helper function for finding minimum value node
    TreeNode *findMin(TreeNode *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Helper function for recursive deletion
    TreeNode *deleteHelper(TreeNode *node, int empID)
    {
        if (node == nullptr)
            return node;

        if (empID < node->empID)
        {
            node->left = deleteHelper(node->left, empID);
        }
        else if (empID > node->empID)
        {
            node->right = deleteHelper(node->right, empID);
        }
        else
        {
            // Node with only one child or no child
            if (node->left == nullptr)
            {
                TreeNode *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get inorder successor
            TreeNode *temp = findMin(node->right);
            node->empID = temp->empID;
            node->empName = temp->empName;
            node->right = deleteHelper(node->right, temp->empID);
        }
        return node;
    }

    // Helper functions for traversals
    void inOrderHelper(TreeNode *node)
    {
        if (node == nullptr)
            return;
        inOrderHelper(node->left);
        cout << "ID: " << node->empID << ", Name: " << node->empName << endl;
        inOrderHelper(node->right);
    }

    void preOrderHelper(TreeNode *node)
    {
        if (node == nullptr)
            return;
        cout << "ID: " << node->empID << ", Name: " << node->empName << endl;
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }

    void postOrderHelper(TreeNode *node)
    {
        if (node == nullptr)
            return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << "ID: " << node->empID << ", Name: " << node->empName << endl;
    }

    // Helper function to count nodes
    int countNodesHelper(TreeNode *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
    }

    // Helper function to calculate height
    int heightHelper(TreeNode *node)
    {
        if (node == nullptr)
            return -1;
        return 1 + max(heightHelper(node->left), heightHelper(node->right));
    }

public:
    BinaryTree() : root(nullptr) {}

    // Insert operation
    void insert(int empID, string empName)
    {
        root = insertHelper(root, empID, empName);
    }

    // Search operation
    TreeNode *search(int empID)
    {
        return searchHelper(root, empID);
    }

    // Delete operation
    void remove(int empID)
    {
        root = deleteHelper(root, empID);
    }

    // Traversal operations
    void inOrderTraversal()
    {
        cout << "In-order Traversal:" << endl;
        inOrderHelper(root);
        cout << endl;
    }

    void preOrderTraversal()
    {
        cout << "Pre-order Traversal:" << endl;
        preOrderHelper(root);
        cout << endl;
    }

    void postOrderTraversal()
    {
        cout << "Post-order Traversal:" << endl;
        postOrderHelper(root);
        cout << endl;
    }

    void levelOrderTraversal()
    {
        if (root == nullptr)
            return;

        cout << "Level-order Traversal:" << endl;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();
            cout << "ID: " << current->empID << ", Name: " << current->empName << endl;

            if (current->left != nullptr)
            {
                q.push(current->left);
            }
            if (current->right != nullptr)
            {
                q.push(current->right);
            }
        }
        cout << endl;
    }

    // Other operations
    int countNodes()
    {
        return countNodesHelper(root);
    }

    int height()
    {
        return heightHelper(root);
    }

    bool isEmpty()
    {
        return root == nullptr;
    }

    // Find minimum and maximum
    TreeNode *findMinimum()
    {
        if (root == nullptr)
            return nullptr;
        return findMin(root);
    }

    TreeNode *findMaximum()
    {
        if (root == nullptr)
            return nullptr;

        TreeNode *current = root;
        while (current->right != nullptr)
        {
            current = current->right;
        }
        return current;
    }
};

int main()
{
    BinaryTree empTree;

    // Insert operations
    empTree.insert(101, "John Doe");
    empTree.insert(105, "Jane Smith");
    empTree.insert(98, "Alice Johnson");
    empTree.insert(110, "Bob Brown");
    empTree.insert(103, "Charlie Davis");
    empTree.insert(95, "Eve Wilson");

    // Display traversals
    empTree.inOrderTraversal();
    empTree.preOrderTraversal();
    empTree.postOrderTraversal();
    empTree.levelOrderTraversal();

    // Search operation
    int searchID = 105;
    TreeNode *found = empTree.search(searchID);
    if (found != nullptr)
    {
        cout << "Employee found - ID: " << found->empID << ", Name: " << found->empName << endl
             << endl;
    }
    else
    {
        cout << "Employee with ID " << searchID << " not found." << endl
             << endl;
    }

    // Tree information
    cout << "Total employees (nodes): " << empTree.countNodes() << endl;
    cout << "Tree height: " << empTree.height() << endl;

    // Min and max
    TreeNode *minEmp = empTree.findMinimum();
    TreeNode *maxEmp = empTree.findMaximum();
    cout << "Employee with smallest ID: " << minEmp->empName << " (" << minEmp->empID << ")" << endl;
    cout << "Employee with largest ID: " << maxEmp->empName << " (" << maxEmp->empID << ")" << endl
         << endl;

    // Delete operation
    int deleteID = 101;
    cout << "Deleting employee with ID " << deleteID << endl;
    empTree.remove(deleteID);
    empTree.inOrderTraversal();

    return 0;
}