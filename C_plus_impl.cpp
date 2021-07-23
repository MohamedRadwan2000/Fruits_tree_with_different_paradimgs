#include <iostream>
#include <regex>
using namespace std;
class CaloriesCalculator{
public :
    double calculateCalories(int w, double rate){ return w * rate; }
};

class Fruit{
protected:
    CaloriesCalculator c;
public :
    int weight;
    string name;
    virtual double CalculateCalories(){ return 0; }
    bool operator > (Fruit& fr2){
        if (weight > fr2.weight)
            return true;
        else
            return false;
    }

    bool operator == (Fruit& fr2){
        if (weight == fr2.weight)
            return true;
        else
            return false;
    }
};

class TinyFruit : virtual public Fruit{
public:
    virtual double CalculateCalories(){ return c.calculateCalories(weight, 1.5); }
};

class RedFruit : virtual public Fruit{
public:
    virtual double CalculateCalories(){ return c.calculateCalories(weight, 2.3); }
};

class Berry : public TinyFruit{
};

class BlackBerry : public Berry{
public:
    BlackBerry(int w){ weight = w; name = "BlackBerry"; }
};

class BlueBerry : public Berry{
public:
    BlueBerry(int w){ weight = w; name = "BlueBerry";}
};

class Cherries : public TinyFruit, public RedFruit{
public:
    Cherries(int w){ weight = w; name = "Cherries";}
    double CalculateCalories(){ return c.calculateCalories(weight, 3.77); }
};

class Node{
public :
    Fruit f;
    Node* left;
    Node* right;

    bool operator > (Node& n2) {
        return f > n2.f;
    }

    bool operator == (Node& n2) {
        return f == n2.f;
    }
};

class Bst{
private :
    Node * root;
    int size;
public :
    Bst(){ root = NULL; size = 0;}
    ~Bst(){ delete(root); }
    int getSize(){ return size; }

    Node* insertfr(Node* node, Fruit fr){
        if (node == NULL){
            node = new Node();
            node->f = fr;
            node->left = node->right = NULL;
        }
        else {
            Fruit& f2 = node->f;

            if (fr == f2)
                node->f = fr;
            else if (fr > f2)
                node->right = insertfr(node->right, fr);
            else
                node->left = insertfr(node->left, fr);
        }

        return node;
    }

    void insert(Fruit fr){
        root = insertfr(root, fr);
        size++;
    }

    void Iterate(Node* node){
        if (node == NULL)
            return;

        Iterate(node->left);
        Fruit& ff = node->f;
        cout << ff.name << " of weight = " << ff.weight << ", ";
        Iterate(node->right);
    }

    void Iterate(){
        cout << "inorder traversal of the tree : ";
        Iterate(root);
        cout << endl;
    }

    Node* findHeaviest(){
        Node* node = root;

        while (node->right != NULL)
            node = node->right;

        return node;
    }
    Node* findLightest(){
        Node* node = root;

        while (node->left != NULL)
            node = node->left;

        return node;
    }
    void filterByWeight(int weight){
    cout << "inorder traversal of the tree : ";
    filterByWeightHelper(root,weight);
}
    void filterByWeightHelper(Node* node, int weight){
    if (node==NULL){
        return;
    }
        filterByWeightHelper(node->left, weight);
    Fruit& ff = node->f;
    if(weight<ff.weight){
        cout << ff.name << " of weight = " << ff.weight << ", ";
    }
        filterByWeightHelper(node->right, weight);
}
    void filterByType(regex type){
        cout << "inorder traversal of the tree : ";
        filterByTypeHelper(root, type);
        cout << endl;
    }

    void filterByTypeHelper(Node* node, regex type){
        if (node == NULL)
            return;

        filterByTypeHelper(node->left, type);

        Fruit& ff = node->f;
        if (regex_match(ff.name, type))
            cout << ff.name << " of weight = " << ff.weight << ", ";

        filterByTypeHelper(node->right, type);
    }
    void magnifyByType(regex Type, int weight){
    Bst newTree;
    magnifyByTypeHelper(root,&newTree,Type,weight);

        this->root=newTree.root;
}
void magnifyByTypeHelper(Node *node,Bst* newTree,regex type,int weight){
    if(node==NULL){return;}
    magnifyByTypeHelper(node->left,newTree,type,weight);
    Fruit& ff = node->f;
    if (regex_match(ff.name, type)){
        Fruit f=node->f;
        f.weight+=weight;
        newTree->insert(f);}
    else{Fruit f=node->f;
        newTree->insert(f);
    }
    magnifyByTypeHelper(node->right,newTree,type,weight);
}
};

int main()
{

    //Cherries c1(50);
    Cherries c2(15);

    BlueBerry b1(10);
    BlackBerry b2(20);
    BlueBerry b3(5000);
    BlueBerry b4(5);
    BlueBerry b5(22);
    Fruit f=b5;
    f.weight+=2000000;
    Bst b;
    //b.insert(c1);
    b.insert(c2);
    b.insert(b1);
    b.insert(b2);
    b.insert(b3);
    b.insert(b4);
    b.insert(b5);

    b.Iterate();
    cout << b.getSize() << endl;
    regex str_expr("BlueBerry");
    b.magnifyByType(str_expr,50);
    b.Iterate();
    cout<<b.findHeaviest()->f.weight<<"\n";
    cout<<b.findLightest()->f.weight<<"\n";
    return 0;
}
