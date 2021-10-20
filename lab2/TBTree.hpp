#ifndef LAB2_TBTREE_HPP
#define LAB2_TBTREE_HPP

#include <cstdio>
#include "TItem.hpp"
#include "TVector.hpp"


struct TNode {
    bool leaf;
    int n;
    TVector<TItem> thisNode;
    TVector<TNode*> children;
    TNode() : thisNode(1), children(2){
        leaf = true;
        n = 0;
    }
};

void SaveFile (TNode *&, FILE *);
bool LoadFile (TNode *&, FILE *);

class TBTree {
private:
    TNode* root;
public:
    TBTree();
    ~TBTree();
    void Create ();
    void TBTreeDelete (TNode* &);

    void Insert (TItem &);
    void BTreeInsert (TNode* &, TItem &);
    static void BTreeSplitChildren (TNode* &, int);

    void Print (int);
    void vecPrint (TNode* &, int);

    void DeleteItem (TItem &);
    static void DeleteFromNode (TNode* &, TItem &, int);
    void DeleteLeaf (TNode* &, TNode* &, TItem &, int);
    void repair (TNode* &, TNode* &, int);
    void remove (TNode* &, TNode* &, TItem &, int);
    static void concatenation (TNode* &, TNode* &);

    bool Search (TItem &);
    TNode* BTreeSearch (TNode* &, TNode* &, TItem &, int &);
    TNode* FindParent (TNode* &, TNode* &, TItem &, int &);
    TNode* SearchItem (TItem &, int &);

    void Save (FILE *);
    void Load (FILE *);
    bool LoadFile(TNode *&, FILE *);
};


// Constructor, destructor and functions for create and delete B-tree
TBTree::TBTree() {
    root = nullptr;
}

TBTree::~TBTree() {
    TBTreeDelete(root);
    delete root;
}

void TBTree::Create() {
    root = new TNode;
    root->children[0] = nullptr;
    root->children[1] = nullptr;
}

void TBTree::TBTreeDelete(TNode* &node) {
    if (node == nullptr) return;
    if (!node->leaf) {
        for (int i = 0; i < node->children.Size(); i++) {
            if (node->children[i] != nullptr) {
                TBTreeDelete(node->children[i]);
                delete node->children[i];
            }
        }
    }
    node->thisNode.Erase();
    node->children.Erase();
}


// Functions for search:
TNode* TBTree::FindParent (TNode *&x, TNode *&parent, TItem &k, int &index) {
    if (root == nullptr) {
        return nullptr;
    }
    short i = 0;
    while (i < x->n and k > x->thisNode[i]) {
        i++;
    }
    if (i < x->n and k == x->thisNode[i]) {
        return x;
    } else if (x->leaf) {
        return nullptr;
    }
    else {
        index = i;
        parent = x;
        return FindParent(x->children[i], parent, k, index); // +x -parent
    }
}

bool TBTree::Search (TItem& k) {
    TNode* search;
    int index;
    TNode* parent = root;
    search = BTreeSearch(root, parent, k, index);
    if (search != nullptr) {
        return true;
    }
    return false;
}

TNode* TBTree::SearchItem(TItem &k, int &index) {
    TNode* search;
    TNode* parent = root;
    search = BTreeSearch(root, parent, k, index);
    return search;
}

TNode* TBTree::BTreeSearch(TNode *&x, TNode *&parent, TItem &k, int &index) {
    if (root == nullptr) {
        return nullptr;
    }
    short i = 0;
    while (i < x->n and k > x->thisNode[i]) {
        i++;
    }
    if (i < x->n and k == x->thisNode[i]) {
        index = i;
        return x;
    } else if(x->leaf) {
        return nullptr;
    }
    else {
        parent = x; //
        return BTreeSearch(x->children[i], parent, k, index);
    }
}

// Functions for insert item:
void TBTree::Insert (TItem &k) {
    if (root == nullptr) {
        Create();
    }
    TNode* r = root;
    if (r->n == 2 * t - 1) {
        auto* s = new TNode;
        root = s;
        s->leaf = false;
        s->thisNode.SetSize(0);
        s->children[0] = r;
        s->children.SetSize(1);
        BTreeSplitChildren(s, 0);
        BTreeInsert(s, k);
    } else {
        BTreeInsert(r, k);
    }
}

void TBTree::BTreeInsert (TNode *&x, TItem &k) {
    int i = x->n;
    if (x->leaf) {
        x->thisNode.AddSize();

        while (i >= 1 and k < x->thisNode[i - 1]) {
            x->thisNode[i] = x->thisNode[i - 1];
            i--;
        }
        x->thisNode[i] = k;
        x->n++;
        x->thisNode.SetSize(x->n);
    } else {
        while (i >= 1 and k < x->thisNode[i - 1]) {
            i--;
        }
        if (x->children[i]->n == 2 * t - 1) {
            BTreeSplitChildren(x, i);
            if (k > x->thisNode[i]) {
                i++;
            }
        }
        BTreeInsert(x->children[i], k);
    }
}

void TBTree::BTreeSplitChildren (TNode *&x, int i) {
    auto* z = new TNode;
    TNode* y = x->children[i];
    z->leaf = y->leaf;
    z->thisNode.resize(t - 1);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) {
        z->thisNode.push_back(y->thisNode[j + t]);
    }
    if (!y->leaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
        z->children.SetSize(t);
        y->children.resize(t);
    }
    TItem median = y->thisNode[t - 1];
    y->thisNode.resize(t - 1);
    y->n = t - 1;
    x->children.resize(x->children.Size() + 1);
    for (int j = x->children.Size(); j > i + 1; j--) {
        x->children[j] = x->children[j - 1];
    }
    x->children[i + 1] = z;
    x->children.SetSize(x->children.Size() + 1);
    x->thisNode.AddSize();
    for (int j = x->n; j > i; j--) {
        x->thisNode[j] = x->thisNode[j - 1];
    }
    x->thisNode[i] = median;
    x->n++;
    x->thisNode.SetSize(x->n);
}


// Functions for delete item:
void TBTree::DeleteItem (TItem &k) {
    TNode* x;
    TNode* parent = root;
    int index;
    x = BTreeSearch(root, parent, k, index);
    if (x->leaf) {
        if (x->n > (t - 1)) {
            DeleteFromNode(x, k, index);
        } else {
            DeleteLeaf(x, parent, k, index);
        }
    } else {
        remove(x, parent, k, index);
    }
}

void TBTree::DeleteFromNode (TNode *&x, TItem &k, int index) {
    if (k == x->thisNode[index]) {
        for (int j = index; j < x->n - 1; j++) {
            x->thisNode[j] = x->thisNode[j + 1];
        }
        x->thisNode.resize(x->n - 1);
        x->n--;
    }
}

void TBTree::DeleteLeaf (TNode *&x, TNode *&parent, TItem &k, int index) {
    if (x == root and x->n == 1) {
        DeleteFromNode(x, k, index);
        root->thisNode.Erase();
        root->children.Erase();
        delete root;
        root = nullptr;
        return;
    }
    if (x == root) {
        DeleteFromNode(x, k, index);
        return;
    }
    if (x->n > (t - 1)) {
        DeleteFromNode(x, k, index);
        return;
    }
    int positionSon = -1;
    for (int j = 0; j < parent->n + 1; j++) {
        if (parent->children[j] == x) {
            positionSon = j;
            break;
        }
    }

    if (positionSon == 0) {
        if (parent->children[positionSon + 1]->n > (t - 1)) {
            TItem k1 = parent->children[positionSon + 1]->thisNode[0];
            TItem k2 = parent->thisNode[positionSon];
            x->thisNode.AddSize();
            x->thisNode[x->n] = k2;
            x->thisNode.SetSize(x->n + 1);
            x->n++;
            DeleteFromNode(x, k, index);
            DeleteFromNode(parent->children[positionSon + 1], k1, 0);
            parent->thisNode[positionSon] = k1;
        } else {
            DeleteFromNode(x, k, index);
            if (x->n <= (t - 2)) {
                repair(x, parent, positionSon);
            }
        }
    } else {
        if (positionSon == parent->n) {
            if (parent->children[positionSon - 1]->n > (t - 1)) {
                TItem k1 = parent->children[positionSon - 1]->thisNode[parent->children[positionSon - 1]->n - 1];
                TItem k2 = parent->thisNode[positionSon - 1];
                DeleteFromNode(x, k, index);
                x->thisNode.AddSize();
                for (int i = x->n; i > 0; i--) {
                    x->thisNode[i] = x->thisNode[i - 1];
                }
                x->thisNode[0] = k2;
                x->thisNode.SetSize(x->n + 1);
                x->n++;
                DeleteFromNode(parent->children[positionSon - 1], k1, parent->children[positionSon - 1]->n - 1);
                parent->thisNode[positionSon - 1] = k1;
            } else {
                DeleteFromNode(x, k, index);
                if (x->n <= (t - 2)) {
                    repair(x, parent, positionSon);
                }
            }
        } else {
            if (parent->children[positionSon + 1]->n > (t - 1)) {
                TItem k1 = parent->children[positionSon + 1]->thisNode[0];
                TItem k2 = parent->thisNode[positionSon];
                x->thisNode.push_back(k2);
                x->n++;
                DeleteFromNode(x, k, index);
                parent->thisNode[positionSon] = k1;
                DeleteFromNode(parent->children[positionSon + 1], parent->children[positionSon + 1]->thisNode[0], 0);
            } else if (parent->children[positionSon - 1]->n > (t - 1)) {
                TItem k1 = parent->children[positionSon - 1]->thisNode[parent->children[positionSon - 1]->n - 1];
                TItem k2 = parent->thisNode[positionSon - 1];
                DeleteFromNode(x, k, index);
                x->thisNode.AddSize();
                for (int i = x->n; i > 0; i--) {
                    x->thisNode[i] = x->thisNode[i - 1];
                }
                x->thisNode[0] = k2;
                x->thisNode.SetSize(x->n + 1);
                x->n++;
                parent->thisNode[positionSon - 1] = k1;
                parent->children[positionSon - 1]->thisNode.resize(parent->children[positionSon - 1]->n - 1);
                parent->children[positionSon - 1]->n--;
            } else {
                DeleteFromNode(x, k, index);
                if (x->n <= (t - 2)) {
                    repair(x, parent, positionSon);
                }
            }
        }
    }
}

void TBTree::repair (TNode *&x, TNode *&parent, int positionSon) {
    if (x == parent) {
        if (root->children[0] != nullptr) {
            TNode* s = root->children[0];
            root->children[1]->thisNode.Erase();
            root->children[1]->children.Erase();
            delete root->children[1];
            root->thisNode.Erase();
            root->children.Erase();
            delete root;
            root = s;
        } else {
            delete root;
            root = nullptr;
        }
        return;
    }
    if (x == root and x->n >= 1) return;
    if (x == root and x->n == 0) {
        if (root->children[0] != nullptr) {
            TNode* s = root->children[0];
            root->children[1]->thisNode.Erase();
            root->children[1]->children.Erase();
            delete root->children[1];
            root->thisNode.Erase();
            root->children.Erase();
            delete root;
            root = s;
            root->children.resize(2);
        } else {
            delete root;
            root = nullptr;
        }
        return;
    }

    if (positionSon == 0) {
        x->thisNode.AddSize();
        x->thisNode[x->n] = parent->thisNode[positionSon];
        x->thisNode.SetSize(x->n + 1);
        x->n++;

        if (parent->children[positionSon + 1]->n > t) {
            parent->thisNode[positionSon] = parent->children[positionSon + 1]->thisNode[0];

            x->children.AddSize();
            x->children[x->children.Size()] = parent->children[positionSon + 1]->children[0];
            x->children.SetSize(x->children.Size() + 1);

            for (int i = 0; i < parent->children[positionSon + 1]->children.Size() - 1; i++) {
                parent->children[positionSon + 1]->children[i] = parent->children[positionSon + 1]->children[i + 1];
            }
            parent->children[positionSon + 1]->children.resize(parent->children[positionSon + 1]->children.Size() - 1);

            DeleteFromNode(parent->children[positionSon + 1], parent->children[positionSon + 1]->thisNode[0], 0);
        } else {
            concatenation(x, parent->children[positionSon + 1]);
            if (parent->children.Size() > 2) {
                parent->children[positionSon + 1]->thisNode.Erase();
                parent->children[positionSon + 1]->children.Erase();
                delete parent->children[positionSon + 1];
                for (int i = positionSon + 1; i < parent->n; i++) {
                    parent->children[i] = parent->children[i + 1];
                }
                parent->children.resize(parent->children.Size() - 1);
            }
            DeleteFromNode(parent, parent->thisNode[positionSon],
                           positionSon);
        }
        if (parent->n <= 0 and parent == root) {
            repair(parent, parent, positionSon);
        }
        else if (parent->n <= t - 2 and parent != root){
            TNode* grandparent;
            int index;
            parent = FindParent(root, grandparent, parent->thisNode[0], index);
            repair(parent, grandparent, index);
        }
    } else if (positionSon == parent->n) {
        x->thisNode.AddSize();
        for (int i = x->n + 1; i > 0; i--) {
            x->thisNode[i] = x->thisNode[i - 1];
        }
        x->thisNode[0] = parent->thisNode[positionSon - 1];
        x->thisNode.SetSize(x->n + 1);
        x->n++;

        if (parent->children[positionSon - 1]->n > t) {
            parent->thisNode[positionSon - 1] = parent->children[positionSon - 1]->thisNode[parent->children[positionSon - 1]->thisNode.Size() - 1];
            x->children.AddSize();
            for (int i = x->children.Size() + 1; i > 0; i--) {
                x->children[i] = x->children[i - 1];
            }
            x->children[0] = parent->children[positionSon - 1]->children[parent->children[positionSon - 1]->children.Size() - 1];
            x->children.SetSize(x->children.Size() + 1);

            parent->children[positionSon - 1]->children.resize(parent->children[positionSon - 1]->children.Size() - 1); //

            DeleteFromNode(parent->children[positionSon - 1],
                           parent->children[positionSon - 1]->thisNode[parent->children[positionSon - 1]->n - 1],
                           parent->children[positionSon - 1]->n - 1);
        }

        else {
            concatenation(parent->children[positionSon - 1], x);
            DeleteFromNode(parent, parent->thisNode[positionSon - 1],
                           positionSon - 1);
            if (parent->children.Size() > 2) {
                parent->children[parent->children.Size() - 1]->thisNode.Erase();
                parent->children[parent->children.Size() - 1]->children.Erase();
                delete parent->children[parent->children.Size() - 1];
                parent->children.resize(parent->children.Size() - 1);
            }
        }
        if (parent->n <= 0 and parent == root) {
            repair(parent, parent, positionSon);
        } else if (parent->n <= (t - 2) and parent != root) {
            TNode* grandparent;
            int index;
            parent = FindParent(root, grandparent, parent->thisNode[0], index);
            repair(parent, grandparent, index);
        }
    } else {
        x->thisNode.push_back(parent->thisNode[positionSon]);
        x->n++;
        if (parent->children[positionSon + 1]->n > t) {
            parent->thisNode[positionSon] = parent->children[positionSon + 1]->thisNode[0];
            x->children.AddSize();
            x->children[x->children.Size()] = parent->children[positionSon + 1]->children[0];
            x->children.SetSize(x->children.Size() + 1);

            for (int i = 0; i < parent->children[positionSon + 1]->children.Size() - 1; i++) {
                parent->children[positionSon + 1]->children[i] = parent->children[positionSon + 1]->children[i + 1];
            }
            parent->children[positionSon + 1]->children.resize(parent->children[positionSon + 1]->children.Size() - 1);
            DeleteFromNode(parent->children[positionSon + 1], parent->children[positionSon + 1]->thisNode[0], 0);
        } else {
            concatenation(x, parent->children[positionSon + 1]);
            parent->children[positionSon + 1]->thisNode.Erase();
            parent->children[positionSon + 1]->children.Erase();
            delete parent->children[positionSon + 1];
            for (int i = positionSon + 1; i < parent->n; i++) {
                parent->children[i] = parent->children[i + 1];
            }
            parent->children.resize(parent->children.Size() - 1);
            DeleteFromNode(parent, parent->thisNode[positionSon], positionSon);
        }
        if (parent->n <= 0 and parent == root) {
            repair(parent, parent, positionSon);
        } else if (parent->n <= (t - 2) and parent != root) {
            TNode* grandparent = nullptr;
            int index;
            parent = FindParent(root, grandparent, parent->thisNode[0], index);
            repair(parent, grandparent, index);
        }
    }
}

void TBTree::concatenation (TNode *&node, TNode *&otherNode) {
    if (node == nullptr) return;
    for (int i = 0; i < otherNode->n; i++) {
        node->thisNode.push_back(otherNode->thisNode[i]);
    }
    if (node->children[0] != nullptr) {
        for (int i = 0; i < otherNode->children.Size(); i++) {
            node->children.push_back(otherNode->children[i]);
        }
    }
    node->n = node->thisNode.Size();
}

void TBTree::remove (TNode* &x, TNode* &parent, TItem &k, int index) {
    TNode* tmp = x->children[index + 1];
    parent = x;
    TItem k1 = x->thisNode[0];
    while (!tmp->leaf) {
        parent = tmp;
        tmp = tmp->children[0];
    }
    if (tmp->n > t - 1) {
        k1 = tmp->thisNode[0];
        x->thisNode[index] = k1;
        DeleteFromNode(tmp, k1, 0);
    } else {
        k1 = tmp->thisNode[0];
        x->thisNode[index] = k1;
        DeleteLeaf(tmp, parent, k1, 0);
    }
}


// Functions for Load and Save file
void TBTree::Load (FILE* file) {
    TBTreeDelete(root);
    delete root;
    root = nullptr;
    bool check = LoadFile(root, file);
    if (!check) {
        TBTreeDelete(root);
        printf("ERROR: can't read the file\n");
        return;
    }
    printf("OK\n");
}

bool TBTree::LoadFile(TNode* &node, FILE* file) {
    int size;
    bool leaf;
    if (fread(&size, sizeof(int), 1, file) == 0) return false;
    if (size == 0) return true;
    if (fread(&leaf, sizeof(bool), 1, file) == 0) return false;

    if (leaf) {
        node = new TNode;
        TItem tmp{};
        node->thisNode.resize(size);
        node->children.resize(0);
        node->n = size;
        node->leaf = true;
        for (int i = 0; i < size; i++) {
            if (fread(tmp.key, sizeof(char), KEY_SIZE + 1, file) == 0) return false;
            if (fread(&tmp.keySize, sizeof(short), 1, file) == 0) return false;
            if (fread(&tmp.value, sizeof(unsigned long long), 1, file) == 0) return false;
            node->thisNode.push_back(tmp);
            tmp.clear();
        }
        return true;
    } else {
        node = new TNode;
        TItem tmp{};
        node->thisNode.resize(size);
        node->children.resize(size + 1);
        node->leaf = false;
        node->n = size;
        for (int i = 0; i < size; i++) {
            if (fread(tmp.key, sizeof(char), KEY_SIZE + 1, file) == 0) return false;
            if (fread(&tmp.keySize, sizeof(short), 1, file) == 0) return false;
            if (fread(&tmp.value, sizeof(unsigned long long), 1, file) == 0) return false;
            node->thisNode.push_back(tmp);
            tmp.clear();
        }

        bool check;
        for (int i = 0; i < size + 1; i++) {
            check = LoadFile(node->children[i], file);
            if (!check) return false;
        }
        node->children.SetSize(size + 1);
        return true;
    }
}

void TBTree::Save (FILE *file) {
    SaveFile(root, file);
}

void SaveFile (TNode *&node, FILE *file) {
    int size;
    bool leaf;
    if (node == nullptr) {
        size = 0;
        fwrite(&size, sizeof(int), 1, file);
        return;
    }
    size = node->thisNode.Size();
    leaf = node->leaf;
    fwrite(&size, sizeof(int), 1, file);
    fwrite(&leaf, sizeof(bool), 1, file);
    for (int i = 0; i < node->thisNode.Size(); i++) {
        fwrite(&node->thisNode[i].key, sizeof(char), KEY_SIZE + 1, file);
        fwrite(&node->thisNode[i].keySize, sizeof(short), 1, file);
        fwrite(&node->thisNode[i].value, sizeof(unsigned long long), 1, file);
    }
    if (!node->leaf) {
        for (int i = 0; i < node->children.Size(); i++) {
            SaveFile(node->children[i], file);
        }
    }
}


// Functions for print B-tree:
void TBTree::Print (int tab) {
    if (root->leaf) {
        for (int i = 0; i < root->n; i++) {
            printf("%s ", root->thisNode[i].key);
        }
        printf("\n");
    }
    else {
        vecPrint(root, tab);
    }
    printf("\n");
    //printf("root->children.size() = %d\n", root->children.Size());
}

void TBTree::vecPrint (TNode *&x, int tab) {
    if (x->children[0] != nullptr) {
        for (int i = x->children.Size() - 1; i >= 0; i--){ // >= 0
            vecPrint(x->children[i], tab + 1);
        }
    }
    for (int i = 0; i < tab; i++) {
        printf("\t");
    }
    printf("size: %d, %d:", x->thisNode.Size(), x->n);
    for (int i = 0; i < x->thisNode.Size(); i++) {
        printf("%s ", x->thisNode[i].key);
    }
    printf("\n");
    //printf("             children.size() = %d\n",x->children.Size());
}


#endif //LAB2_TBTREE_HPP