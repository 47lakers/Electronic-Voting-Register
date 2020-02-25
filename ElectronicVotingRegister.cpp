#include <iostream>
using namespace std;

//Ira Porchia
//Electronic Voting Register
//2-24-20

/////////Node Class///////////////
class Node
{
    friend class Tree;
private:
    Node *_left;
    int _number;
    string _data;
    Node *_right;
private:
    Node(int const &number, string const &data);
public:
    void clear();
    void insertNum(int const &number, string const &data);
    Node* removeNum(Node* owner, int const &number);
    string findNum(int const &number);
    Node * minValueNode(Node* node);
    string changeData(int const &number);
};
////////////////Tree Class//////////////
class Tree
{
private:
    Node *_root;
public:
    Tree();
    ~Tree();
    void clear();
    void insertNum(int const &number, string const &data);
    Node* removeNum(int const &number);
    string findNum(int const &number);
    Node * minValueNode(Node* node);
    string changeData(int const &number);
};
//////////////////Constructors/////////////////////////////
Tree::Tree():
    _root(nullptr){
    }

Node::Node(int const &number, string const &data):
    _left(nullptr), _number(number), _data(data), _right(nullptr){
    }
//////////////////////Destructor//////////////////////////
Tree::~Tree()
{
    clear();
}
//////////////////Clear Method////////////////////////
void Tree::clear()
{
    if(_root != nullptr){
        _root->clear();
        _root = nullptr;
    }
}

void Node::clear()
{
    if(_left != nullptr){
        delete _left;
        _left = nullptr;
    }
    if(_right != nullptr){
        delete _right;
        _right = nullptr;
    }
    delete this;
}
////////////////////InsertNum Method///////////////////////
void Tree::insertNum(int const &number, string const &data)
{
    if(_root == nullptr){
        _root = new Node(number, data);
    }
    _root->insertNum(number, data);
}

void Node::insertNum(int const &number, string const &data)
{
    if(number == _number){
        _data = data;
    }
    if(number > _number){
        if(_right == nullptr){
            _right = new Node(number, data);
        }else{
            _right->insertNum(number, data);
        }
    }
    if(number < _number){
        if(_left == nullptr){
            _left = new Node(number, data);
        }else{
            _left->insertNum(number, data);
        }
    }
}
//////////////////Remove Num Method///////////////////////////////
Node* Tree::removeNum(int const &number)
{
    if(_root == nullptr){
    }else{
        return _root->removeNum(_root, number);
    }
}

Node* Node::removeNum(Node* owner, int const &number)
{
    if(number < owner->_number){
        owner->_left = removeNum(owner->_left, number);
    }else if(number > owner->_number){
        owner->_right = removeNum(owner->_right, number);
    }else{
        if(owner->_left == nullptr){
            Node *temp = owner->_right;
            delete owner;
            owner = nullptr;
            return temp;
        }else if(owner->_right == nullptr){
            Node *temp = owner->_left;
            delete owner;
            owner = nullptr;
            return temp;
        }
        Node* temp = minValueNode(owner->_right);
        owner->_number = temp->_number;
        owner->_data = temp->_data;
        owner->_right = removeNum(owner->_right, temp->_number);
    }
    return owner;
}
////////////////////Find Num Method////////////////////////////////
string Tree::findNum(int const &number)
{
    if(_root == nullptr){
        return "The social security number is not valid\n";
    }
    return _root->findNum(number);
}

string Node::findNum(int const &number)
{
    if(number > _number){
        if(_right == nullptr){
            return "The social security number is not valid\n";
        }else{
            return _right->findNum(number);
        }
    }
    if(number < _number){
        if(_left == nullptr){
            return "The social security number is not valid\n";
        }else{
            return _left->findNum(number);
        }
    }
    return _data;
}
////////////////////Min Value Method/////////////////////////
Node* Tree::minValueNode(Node* node)
{
    if(_root == nullptr){
    }
    _root->minValueNode(node);
}

Node* Node::minValueNode(Node* node)
{
    Node* current = node;
    while(current && current->_left != nullptr){
        current = current->_left;
    }
    return current;
}
/////////////////Change Data Method/////////////////////
string Tree::changeData(int const &number){
    if(_root == nullptr){
    }
    _root->changeData(number);
}

string Node::changeData(int const &number){
    if(number > _number){
        if(_right == nullptr){
            return "The social security number is not valid\n";
        }else{
            return _right->changeData(number);
        }
    }
    if(number < _number){
        if(_left == nullptr){
            return "The social security number is not valid\n";
        }else{
            return _left->changeData(number);
        }
    }
    if(_data == "You are eligible to vote\n"){
        _data = "You are not eligible to vote\n";
        return _data;
    }
    if(_data == "You are not eligible to vote\n"){
        _data = "You are eligible to vote\n";
        return _data;
    }
}
////////////////Main//////////////////////
int main()
{
    Tree Tree1;
    Tree1.insertNum(5555, "You are eligible to vote\n");
    Tree1.insertNum(4444, "You are not eligible to vote\n");
    Tree1.insertNum(6666, "You are eligible to vote\n");
    Tree1.insertNum(3333, "You are not eligible to vote\n");
    Tree1.insertNum(7777, "You are eligible to vote\n");
    Tree1.insertNum(2222, "You are not eligible to vote\n");
    cout << Tree1.findNum(3333);
    cout << Tree1.findNum(5555);
    cout << Tree1.findNum(7777);
    Tree1.removeNum(5555);
    cout << Tree1.findNum(3333);
    cout << Tree1.findNum(5555);
    cout << Tree1.findNum(7777);
    Tree1.changeData(3);
    cout << Tree1.findNum(3333);
    cout << Tree1.findNum(5555);
    cout << Tree1.findNum(7777);
    return 0;
}
