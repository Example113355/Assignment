#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

static long long cur = 1;

class parNode {
public:
    long long id;
    parNode* left;
    parNode* right;
    int height;

    parNode() {

    }

    parNode(long long id) {
        this->id = id;
        left = right = 0;
        height = 1;
    }
};

class ParentsTree {
public:
    parNode* root;
    int count;

    ParentsTree() {
        root = 0;
        count = 0;
    }

    int size() const {
        return this->count;
    }

    string print(parNode* node) const {
        string h = "(id=";
        h += to_string(node->id);
        h += ')';
        return h;
    }

    string to_stringRec(parNode* node) const {
        if (node == 0)
            return "";
        else {
            if (node == root) {
                return print(node) + to_stringRec(node->left) + to_stringRec(node->right);
            }
            else {
                return ";" + print(node) + to_stringRec(node->left) + to_stringRec(node->right);
            }
        }
    }

    string toStringPreOrder() const {
        string h = "ParentsTree[";
        h += to_stringRec(root);
        h += ']';
        return h;
    }

    int getHeightRec(parNode* node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->left);
        int rh = this->getHeightRec(node->right);
        return (lh > rh ? lh : rh) + 1;
    }

    int getHeight()
    {
        return this->getHeightRec(this->root);
    }

    parNode* rightRotate(parNode* y)
    {
        parNode* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }
    parNode* leftRotate(parNode* x)
    {
        parNode* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    int getBalance(parNode* N)
    {
        if (N == NULL)
            return 0;
        return getHeightRec(N->left) - getHeightRec(N->right);
    }
    parNode* insert(parNode* node, long long key)
    {
        if (node == NULL) {
            parNode* temp = new parNode(key);
            return temp;
        }
        if (key < node->id)
            node->left = insert(node->left, key);
        else if (key >= node->id)
            node->right = insert(node->right, key);

        int balance = getBalance(node);
        // Left Left Case  
        if (balance > 1 && key < node->left->id)
            return rightRotate(node);

        // Right Right Case  
        if (balance < -1 && key >= node->right->id)
            return leftRotate(node);

        // Left Right Case  
        if (balance > 1 && key >= node->left->id)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right Left Case  
        if (balance < -1 && key < node->right->id)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    void add(const long long& value)
    {
        // TODO
        this->count++;
        this->root = insert(this->root, value);
    }

    parNode* maxValueparNode(parNode* node)
    {
        parNode* current = node;

        /* loop down to find the leftmost leaf */
        while (current->right != NULL)
            current = current->right;

        return current;
    }

    parNode* deleteparNode(parNode* root, int key)
    {
        // STEP 1: PERFORM STANDARD BST DELETE  
        if (root == NULL)
            return root;
        // If the key to be deleted is smaller  
        // than the root's key, then it lies 
        // in left subtree  
        if (key < root->id)
            root->left = deleteparNode(root->left, key);
        // If the key to be deleted is greater  
        // than the root's key, then it lies  
        // in right subtree  
        else if (key > root->id)
            root->right = deleteparNode(root->right, key);

        // if key is same as root's key, then  
        // This is the parNode to be deleted  
        else
        {
            // parNode with only one child or no child  
            if ((root->left == NULL) ||
                (root->right == NULL))
            {
                parNode* temp = root->left ?
                    root->left :
                    root->right;

                // No child case  
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else // One child case  
                    *root = *temp; // Copy the contents of  
                                   // the non-empty child  
                free(temp);
            }
            else
            {
                parNode* temp = maxValueparNode(root->left);
                root->id = temp->id;
                root->left = deleteparNode(root->left,
                    temp->id);
            }
        }
        if (root == NULL)
            return root;
        // STEP 3: GET THE BALANCE FACTOR OF  
        // THIS parNode (to check whether this  
        // parNode became unbalanced)  
        int balance = getBalance(root);

        // If this parNode becomes unbalanced,  
        // then there are 4 cases  

        // Left Left Case  
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        // Left Right Case  
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case  
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case  
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    void remove(const long long& value)
    {
        // TODO
        this->count--;
        this->root = deleteparNode(root, value);
    }
};

class Node {
public:
    int leftSize;
    int size;
    string data;
    Node* left;
    Node* right;
    ParentsTree* par;

    Node() {
        leftSize = size = 0;
        data = "";
        left = right = 0;
        this->par = new ParentsTree();
        this->par->root = new parNode(cur);
        this->par->count++;
        cur++;
        if (cur > 10000000)
            throw overflow_error("Id is overflow!");
    }

    Node(int leftSize, int size, string data, Node* left, Node* right) {
        this->leftSize = leftSize;
        this->size = size;
        this->data = data;
        this->left = left;
        this->right = right;
        this->par = new ParentsTree();
        this->par->root = new parNode(cur);
        this->par->count++;
        cur++;
        if (cur > 10000000)
            throw overflow_error("Id is overflow!");
    }

    Node(string data) {
        this->data = data;
        size = data.size();
        left = right = 0;
        leftSize = 0;
        this->par = new ParentsTree();
        this->par->root = new parNode(cur);
        this->par->count++;
        cur++;
        if (cur > 10000000)
            throw overflow_error("Id is overflow!");
    }

    string reverseStr()
    {
        string h = data;
        int n = h.length();
        for (int i = 0; i < n / 2; i++)
            swap(h[i], h[n - i - 1]);
        return h;
    }

    Node* copyNode(Node* node) {
        if (node == 0) return node;

        Node* temp = new Node();
        temp->leftSize = node->leftSize;
        temp->size = node->size;
        temp->data = node->data;
        temp->left = copyNode(node->left);
        temp->right = copyNode(node->right);
        return temp;
    }

    int getIndex(char c) {
        if (data != "") {
            for (int i = 0; i < size; i++) {
                if (data[i] == c)
                    return i;
            }
            return -1;
        }
        int temp = left->getIndex(c);
        if (temp == -1)
            return leftSize + right->getIndex(c);
        else
            return temp;
    }

    Node* subRec(int from, int to) {
        if (this == 0)
            return 0;
        Node* temp = new Node();
        temp->size = to - from;
        if (data == "") {
            if (from >= leftSize) {
                temp->right = right->subRec(from - leftSize, to - leftSize);
                temp->leftSize = 0;
            }
            else if (from < leftSize && to > leftSize) {
                temp->left = left->subRec(from, leftSize);
                temp->right = right->subRec(0, to - leftSize);
                temp->leftSize = temp->left->size;
            }
            else {
                temp->left = left->subRec(from, to);
                temp->leftSize = temp->left->size;
            }
        }
        else {
            temp->leftSize = 0;
            temp->data = data.substr(from, to - from);
        }
        return temp;
    }
};

class ConcatStringTree {
public:
    Node* root;
public:
    ConcatStringTree(const char* s) {
        string h = s;
        root = new Node(h);
    }
    ConcatStringTree() {
        root = new Node();
    }
    int length() const {
        return this->root->size;
    }
    char get(int index) {
        if (index < 0 || index >= this->length()) {
            throw out_of_range("Index of string is invalid!");
        }
        return this->toString()[index + 18];
    }
    int indexOf(char c) {
        return root->getIndex(c);
    }
    string print(Node* node) const {
        string temp = "(";
        temp += "LL=" + to_string(node->leftSize);
        temp += ",L=" + to_string(node->size);
        if (node->data != "") {
            temp += ',';
            temp += '"';
            temp += node->data;
            temp += '"';
            temp += ')';
        }
        else
            temp += ",<NULL>)";
        return temp;
    }
    string to_stringRec(Node* node) const {
        if (node == 0)
            return "";
        else {
            if (node == root) {
                return print(node) + to_stringRec(node->left) + to_stringRec(node->right);
            }
            else {
                return ";" + print(node) + to_stringRec(node->left) + to_stringRec(node->right);
            }
        }
    }
    string toStringPreOrder() const {
        string temp = "ConcatStringTree[";
        temp += to_stringRec(root);
        temp += "]";
        return temp;
    }
    string stringRec(Node* node) const {
        if (node == 0) {
            return "";
        }
        else if (node->data != "") {
            return node->data + stringRec(node->left) + stringRec(node->right);
        }
        else {
            return stringRec(node->left) + stringRec(node->right);
        }
    }
    string toString() const {
        string temp = "ConcatStringTree[";
        temp += '"';
        temp += stringRec(root);
        temp += '"';
        temp += ']';
        return temp;
    }
    ConcatStringTree concat(const ConcatStringTree& otherS) const {
        ConcatStringTree temp;
        temp.root->left = this->root;
        Node* leftNode = temp.root->left;
        leftNode->par->add(cur - 1);
        temp.root->right = otherS.root;
        Node* rightNode = temp.root->right;
        rightNode->par->add(cur - 1);
        temp.root->leftSize = this->root->size;
        temp.root->size = this->root->size + otherS.root->size;
        return temp;
    }
    ConcatStringTree(ConcatStringTree&& obj)
        : root{ obj.root }
    {
        // Nulling out the pointer to the temporary data
        obj.root = nullptr;
    }
    void revRec(Node*& node) {
        if (node == 0)
            return;
        else {
            revRec(node->left);
            revRec(node->right);
            node->data = node->reverseStr();
            swap(node->left, node->right);
            if (node->left == 0) {
                node->leftSize = 0;
            }
            else {
                node->leftSize = node->left->size;
            }
        }
    }
    ConcatStringTree reverse() const {
        ConcatStringTree temp;
        temp.root = temp.root->copyNode(this->root);
        temp.revRec(temp.root);
        return temp;
    }
    ConcatStringTree subString(int from, int to) const {
        //cout << "121212 " << from << " " << to << " " << this->root->size << endl;
        if (from < 0 || to < 0 || from >= root->size || to > root->size)
            throw  out_of_range("Index of string is invalid!");
        if (from >= to)
            throw  logic_error("Invalid range!");
        ConcatStringTree temp;
        temp.root = root->subRec(from, to);
        return temp;
    }
    Node* nodeByQuery(Node* node, string query) const {
        if (query[0] != 'l' && query[0] != 'r' && query != "")
            throw runtime_error("Invalid character of query");
        if (node == 0)
            throw runtime_error("Invalid query: reaching NULL");
        if (query.empty()) {
            return node;
        }
        else {
            if (query[0] == 'l')
                return nodeByQuery(node->left, query.substr(1));
            else
                return nodeByQuery(node->right, query.substr(1));
        }
    }
    void delRecId(Node*& node, long long id) {
        if (node == 0) return;
        long long temp = node->par->root->id;
        node->par->remove(id);
        //cout << node->par->toStringPreOrder() << endl;
        if (node->par->count == 0) {
            if (node->left) delRecId(node->left, temp);
            if (node->right) delRecId(node->right, temp);
            delete node;
        }
    }
    ~ConcatStringTree() {
        /*root->left->par->root = root->left->par->deleteNode(root->left->par->root, root->par->root->id);
        root->right->par->root = root->right->par->deleteNode(root->right->par->root, root->par->root->id);*/
        if (root != 0)
            this->delRecId(root, root->par->root->id);
    }
    int getParTreeSize(const string& query) const {
        Node* temp = nodeByQuery(root, query);
        return temp->par->size();
    }
    string getParTreeStringPreOrder(const string& query) const {
        Node* temp = nodeByQuery(root, query);
        return temp->par->toStringPreOrder();
    }
    /*
    */
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash; // forward declaration

class HashConfig {
public:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    HashConfig() {
        p = initSize = 0;
        c1 = c2 = lambda = alpha = 0;
    }
    HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize) {
        this->p = p;
        this->c1 = c1;
        this->c2 = c2;
        this->lambda = lambda;
        this->alpha = alpha;
        this->initSize = initSize;
    }
    friend class ReducedConcatStringTree;
    friend class LitStringHash;
};
class hashNode {
public:
    string data;
    int count;

    hashNode() {
        data = "";
        count = 0;
    }
    hashNode(string data) {
        this->data = data;
        count = 1;
    }
};
class LitStringHash {
public:
    hashNode* arr;
    int p;
    double c1, c2, lambda, alpha;
    int size;
    int count;
    int lastIndex;
    LitStringHash() {
        p = size = count = 0;
        c1 = c2 = lambda = alpha = 0;
        lastIndex = -1;
        arr = 0;
    }
    LitStringHash(const HashConfig& hashConfig) {
        this->p = hashConfig.p;
        this->c1 = hashConfig.c1;
        this->c2 = hashConfig.c2;
        this->lambda = hashConfig.lambda;
        this->alpha = hashConfig.alpha;
        this->size = hashConfig.initSize;
        this->arr = new hashNode[size];
        this->lastIndex = -1;
        this->count = 0;
    }
    long long power(int key, int time) {
        long long sum = 1;
        if (time == 0) {
            return 1;
        }
        for (int i = 0; i < time; i++) {
            sum *= key;
        }
        return sum;
    }
    int hashFunc(string h) {
        int key = 0;
        for (int i = 0; i < h.length(); i++) {
            key += (h[i] * power(this->p, i)) % size;
        }
        return key % size;
    }
    int hashFuncI(int key, int i) {
        key += c1 * i + c2 * power(i, 2);
        return key % size;
    }
    void insert(hashNode* temp) {
        if (arr == 0) {
            arr = new hashNode[size];
        }
        count++;
        if ((double)count / size > lambda) {
            //cout << "rehash"<<endl;
            this->rehashing();
        }
        int key = hashFunc(temp->data);
        if ((arr + key)->data == "") {
            arr[key] = *temp;
            lastIndex = key;
            return;
        }
        else if ((arr + key)->data != "" && (arr + key)->data == temp->data) {
            (arr + key)->count++;
            return;
        }
        else {
            int tmp;
            for (int i = 1; i < size; i++) {
                tmp = hashFuncI(key, i);
                if ((arr + tmp)->data == "") {
                    arr[tmp] = *temp;
                    lastIndex = tmp;
                    break;
                }
                else if (arr[tmp].data != "" && arr[tmp].data == temp->data) {
                    arr[tmp].count++;
                    break;
                }
            }
            return;
        }
        throw runtime_error("No possible slot");
    }
    int search(string temp) {
        int key = hashFunc(temp);
        if (arr[key].data == temp) {
            return key;
        }
        else {
            int tmp;
            for (int i = 1; i < size; i++) {
                tmp = hashFuncI(key, i);
                if (arr[tmp].data == temp) {
                    return tmp;
                }
            }
        }
        return -1;
    }
    void rehashing() {
        //cout << "rehashing " << endl;
        int newSize = alpha * size;
        int oldSize = size;
        //cout << newSize << endl;
        this->count = 0;
        this->size = newSize;
        hashNode* temp = arr;
        arr = new hashNode[newSize];
        for (int i = 0; i < oldSize; i++) {
            if (temp[i].data != "") {
                insert(&temp[i]);
            }
        }
        delete[]temp;
    }
    void remove(string temp) {
        int index = search(temp);
        arr[index].count--;
        if (arr[index].count == 0) {
            arr[index].data = "";
            size--;
        }
        if (count == 0) {
            delete[] arr;
        }
    }
    int getLastInsertedIndex() const {
        if (arr == 0)
            return -1;
        else
            return lastIndex;
    }
    string toString() const {
        string h = "LitStringHash[";
        if (arr[0].data == "") {
            h += "()";
        }
        else {
            h += '(';
            h += "litS=";
            h += '"';
            h += arr[0].data;
            h += '"';
            h += ')';
        }
        for (int i = 1; i < size; i++) {
            if (arr[i].data == "") {
                h += ";()";
            }
            else {
                h += ";(litS=";
                h += '"';
                h += arr[i].data;
                h += '"';
                h += ')';
            }
        }
        h += ']';
        return h;
    }
    
};

class ReducedConcatStringTree :public ConcatStringTree {
public:
    LitStringHash* litStringHash;
    ReducedConcatStringTree(const char* s, LitStringHash* litStringHash) {
        string h = s;
        root->data = h;
        root->leftSize = 0;
        root->size = h.length();
        root->left = root->right = 0;
        this->litStringHash = litStringHash;
        litStringHash->insert(new hashNode(h));
    }
    ReducedConcatStringTree() {
        
    }
    ReducedConcatStringTree(ReducedConcatStringTree&& other)
    {
        root = other.root;
        litStringHash = other.litStringHash;
        other.litStringHash = nullptr;
        other.root = nullptr;
    }
    ReducedConcatStringTree concat(const ReducedConcatStringTree& otherS) const {
        ReducedConcatStringTree temp;
        temp.root->size = this->root->size + otherS.root->size;
        temp.root->data = "";
        temp.root->leftSize = this->root->size;
        temp.root->left = this->root;
        temp.root->right = otherS.root;
        temp.litStringHash = this->litStringHash;
        return temp;
    }
    ~ReducedConcatStringTree() {
        if(root)
            litStringHash->remove(root->data);
    }
};


#endif // __CONCAT_STRING_TREE_H__