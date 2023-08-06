#include<bits/stdc++.h>
using namespace std;

void io() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}
class Node{
    public:
        Node* left;
        Node* right;
        int data;
    Node(int d){
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

Node* buildBST(Node* root, int d){
    if(!root){
        root = new Node(d);
        return root;
    }
    if(d > root->data){
        root->right = buildBST(root->right, d);
    }
    if(d <= root->data){
        root->left = buildBST(root->left, d);
    }
    return root;
}
void takeInput(Node* &root){
    int data;
    cin>>data;
    while(data != -1){
        root = buildBST(root, data);
        cin >> data;
    }
}
void levelOrder(Node* node){
    queue<Node*>q;
    q.push(node);
    q.push(NULL);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(!temp){
            cout<<endl;
            if(!q.empty())
                q.push(NULL);
        }
        else{
            cout<<temp->data<<" ";
            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);
        }
    }
}

bool recursiveSearchBST(Node* root, int key){
    if(!root){
        return false;
    }
    if(key > root->data){
        return recursiveSearchBST(root->right, key);
    }
    if(key < root->data){
        return recursiveSearchBST(root->left, key);
    }
    if(key == root->data){
        return true;
    }
    return false;
}
bool iterativeSearchBST(Node* root, int key){
    Node* temp = root;
    while(temp){
        if(temp->data == key)
            return true;
        if(key > temp->data)
            temp = temp->right;
        if(key < temp->data)
            temp = temp->left;
    }
    return false;
}

Node* minVal(Node* root){
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

Node* deletionInBST(Node* root, int key) {
    if(!root){
        return root;
    }
    else if(root->data == key){
        //0 child
        if(!root->left && !root->right){
            delete root;
            return NULL;
        }
        //1 child
        //right
        if(!root->left && root->right){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        //left
        if(root->left && !root->right){
            Node* temp = root->left;
            delete root;
            return temp;
        }
        //2 child
        if(root->left && root->right){
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deletionInBST(root->right, mini);
            return root;
        }
    }
    else if(root->data > key){
        root->left = deletionInBST(root->left, key);
        return root;
    }
    else{
        root->right = deletionInBST(root->right, key);
        return root;
    }
    return root;
}
bool isBST(Node* root, int max, int min){
    if(!root){
        return true;
    }
    if(root->data >= min && root->data <= max){
        bool left = isBST(root->left, root->data, min);
        bool right = isBST(root->right, max, root->data);
        return left && right;
    }
    else{
        return false;
    }
}

int kthSmallestBST(Node* node, int& i, int k){
    if(!node)
        return -1;
    int left = kthSmallestBST(node->left, i, k);
    if(left != -1)
        return left;
    i++;
    if(i == k)
        return node->data;
    return kthSmallestBST(node->right, i, k);
}

Node* LCA(Node* node, int p, int q){
    while(node){
        if(node->data > p && node->data > q)
            node = node->left;
        else if(node->data < p && node->data < q)
            node = node->right;
        else
            return node;
    }
    return node;
}

void findSum(Node* root, Node* node, int sum){
    if(!node)
        return ;
    findSum(root, node->left, sum);
    int x = node->data;
    int y = sum - x;
    if(iterativeSearchBST(root, y)){
        cout<<"("<<x<<", "<<y<<")"<<endl;
    }
    findSum(root, node->right, sum);
}

Node* flattenBSTSorted(vector<Node*> vec){
    int n = vec.size();
    Node* root = vec[0];
    Node* curr = root;
    for(int i=1;i<n;i++){
        Node* temp = vec[i];
        curr->left = NULL;
        curr->right = temp;
        curr = temp;
    }
    curr->left = NULL;
    curr->right = NULL;
    return root;
}

Node* balancedBST(int start, int end, vector<int>inValue){
    if(start > end)
        return NULL;
    int mid = (start+end)/2;
    Node* balancedRoot = new Node(inValue[mid]);
    balancedRoot->left = balancedBST(start, mid-1, inValue);
    balancedRoot->right = balancedBST(mid+1, end, inValue);
    return balancedRoot;
}

Node* BSTfromPreorder(int max, int min, vector<int>pre, int &i){
    if(i >= pre.size()){
        return NULL;
    }
    if(pre[i] > max || pre[i] < min){
        return NULL;
    }
    Node* root = new Node(pre[i]);
    i++;
    root->left = BSTfromPreorder(root->data, min, pre, i);
    root->right = BSTfromPreorder(max, root->data, pre, i);
    return root;
}

Node* BSTfromInorder(int start, int end, vector<int>inorder){
    if(start > end)
        return NULL;
    int mid = (start+end)/2;
    Node* root = new Node(inorder[mid]);
    root->left = BSTfromInorder(start, mid-1, inorder);
    root->right = BSTfromInorder(mid+1, end, inorder);
    return root;
}

void inorderNode(Node* root, vector<Node*>& inorderNo){
    if(!root)
        return ;
    inorderNode(root->left, inorderNo);
    inorderNo.push_back(root);
    inorderNode(root->right, inorderNo);
}
void inorderValue(Node* root, vector<int>& inorderVal){
    if(!root)
        return ;
    inorderValue(root->left, inorderVal);
    inorderVal.push_back(root->data);
    inorderValue(root->right, inorderVal);
}
void preorder(Node* root, vector<int>& pre){
    if(!root)
        return ;
    pre.push_back(root->data);
    preorder(root->left, pre);
    preorder(root->right, pre);
}

int sizeOfBST(Node* node){
    if(!node){
        return 0;
    }
    int left = sizeOfBST(node->left);
    int right = sizeOfBST(node->right);
    return left + right + 1;
}

void maxPossibleBST(Node* node, int& maxSize){
    if(!node)
        return ;
    maxPossibleBST(node->left, maxSize);
    if(isBST(node, INT_MAX, INT_MIN)){
        maxSize = max(maxSize, sizeOfBST(node));
    }
    maxPossibleBST(node->right, maxSize);
}

void buildTreeLevelOrder(Node* &tree){
    queue<Node*>q;
    int data;
    cin>>data;
    tree = new Node(data);
    q.push(tree);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        cin>>data;
        if(data != -1){
            temp->left = new Node(data);
            q.push(temp->left);
        }
        cin>>data;
        if (data != -1) {
            temp->right = new Node(data);
            q.push(temp->right);
        }
    }
}

class largestBSTInTree{
    public:
        int maxi;
        int mini;
        bool BST;
        int size;
};

largestBSTInTree largestBST(Node* node, int& maxSize){
    if(node == NULL){
        return {INT_MIN, INT_MAX, true, 0};
    }
    largestBSTInTree left = largestBST(node->left, maxSize);
    largestBSTInTree right = largestBST(node->right, maxSize);

    largestBSTInTree curr;
    curr.size = left.size + right.size + 1;
    curr.maxi = max(node->data, right.maxi);
    curr.mini = min(node->data, left.mini);

    if(left.BST && right.BST && (node->data > left.maxi && node->data < right.mini)){
        curr.BST = true;
    }
    else{
        curr.BST = false;
    }
    if(curr.BST){
        maxSize = max(maxSize, curr.size);
    }
    return curr;
}

int main(){
    io();
    Node* root = NULL;
    takeInput(root);
    cout<<"Level order traversal of BST:\n";
    levelOrder(root);
    //time complexity of search is O(H) for worst case O(N)
    cout<<"Search in BST (searching 70):\n";
    recursiveSearchBST(root, 70)?cout<<"70 is present\n":cout<<"70 is not present\n";
    iterativeSearchBST(root, 70)?cout<<"70 is present\n":cout<<"70 is not present\n";
    //Max element in BST
    //Min element in BST
    //Inorder successor in BST
    //Inorder predecessor in BST
    cout<<"Deletion in a BST: \n";
    root = deletionInBST(root, 90);
    levelOrder(root);
    isBST(root, INT_MAX, INT_MIN)?cout<<"Tree is a BST\n":cout<<"Tree is not a BST\n";
    int i = 0;
    cout<<"kth smallest element from a BST: ";
    cout<<kthSmallestBST(root, i, 1)<<endl;
    i = 0;
    cout<<"Kth largest element from a BST: ";
    cout<<kthSmallestBST(root, i, 5)<<endl;
    cout<<"Lowest common ancestor: ";
    cout<<LCA(root, 30, 110)->data<<endl;
    //O(N^2)
    //for O(N) do inorder traversal and store it in array then apply 2 pointer method
    // on the array to find the pair
    cout<<"Find sum(90) Brute force all possible pairs:\n";
    // findSum(root, root, 90);
    cout<<"Flatten a BST:\n";
    vector<Node*>inNo;
    inorderNode(root, inNo);
    root = flattenBSTSorted(inNo);
    levelOrder(root);
    cout<<"Making a balanced BST\n";
    vector<int>inVal;
    inorderValue(root, inVal);
    Node* balancedRoot = balancedBST(0, inVal.size()-1, inVal);
    levelOrder(balancedRoot);
    root = balancedBST(0, inVal.size() - 1, inVal);
    vector<int>pre;
    preorder(root, pre);
    i=0;
    //1st method make BST from preorder considering it just the array of inputs O(N^2)
    //2nd method find inorder by sorting preorder and use both to make the BST O(NlogN)
    //3rd method O(N) ->
    //further optimisation no need to send min only max can be used to make BST
    cout<<"BST using preorder: \n";
    root = BSTfromPreorder(INT_MAX, INT_MIN, pre, i);
    levelOrder(root);
    // Merge two BST Tc = O(m+n) and Sc = O(m+n)
    // 1 -> find inorder of both the array
    // 2 -> merge the inorder(merge two sorted array)
    // 3 -> make a BST using the merged inorder array
    // space can be optimized Sc = O(h1+h2)
    // flatten the two BST and then simply merge two sorted linked list
    // then make a BST from this merged linked list

    Node* treeRoot = NULL;
    buildTreeLevelOrder(treeRoot);
    int maxSize = 0;
    maxPossibleBST(treeRoot, maxSize);
    cout<<"Max size BST O(n): "<<maxSize;
    maxSize = 0;
    largestBSTInTree temp = largestBST(treeRoot, maxSize);
    cout<<"\nMax size BST O(n): "<<maxSize;
    return 0;
}