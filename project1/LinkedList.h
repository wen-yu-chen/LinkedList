#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct LinkedList {

    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;
    unsigned int numOfNode;

    //accessors
    void PrintForward() const;
    unsigned int NodeCount() const;
    void PrintReverse() const;
    void FindAll(vector<Node *> &outData, const T&value) const;
    const Node *Find(const T &data) const;
    Node *Find(const T &data);
    const Node *GetNode(unsigned int index) const;
    Node *GetNode(unsigned int index);
    const Node *Head() const;
    Node *Head();
    const Node *Tail() const;
    Node *Tail();

    //insertion
    void AddHead(const T &data);
    void AddTail(const T &data);
    void AddNodesHead(const T *data, unsigned int count);
    void AddNodesTail(const T *data, unsigned int count);
    void InsertAfter(Node *node, const T &data);
    void InsertBefore(Node *node, const T &data);
    void InsertAt(const T &data, unsigned int index);

    //removal
    unsigned int Remove(const T &data);
    bool RemoveHead();
    bool RemoveTail();
    bool RemoveAt(unsigned int index);
    void Clear();


    //operators
    const T &operator[](unsigned int index) const;
    T &operator[](unsigned int index);
    bool operator==(const LinkedList<T> &rhs) const;
    LinkedList<T> &operator=(const LinkedList<T> &rhs);


    LinkedList();
    LinkedList(const LinkedList<T> &list);
    ~LinkedList();
};


template<typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return numOfNode;
}

template<typename T>
void LinkedList<T>::PrintForward() const {
    Node* temp = head;

    for (unsigned int i = 0; i < numOfNode; i++) {
        cout << temp->data << endl;

        temp = temp->next;
    }
}


template<typename T>
void LinkedList<T>::PrintReverse() const {
    Node* temp = tail;

    for (unsigned int i = 0; i < numOfNode; i++) {
        cout << temp->data << endl;

            temp = temp->prev;
    }
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node *> &outData, const T&value) const {
    Node* temp = head;


    while (temp != nullptr) {
        if (temp-> data == value) {
            outData.push_back(temp);
        }

        temp = temp->next;
    }
}


template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) const {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == data) {
            break;
        }

        temp = temp->next;
    }

    return temp;
}


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T &data) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == data) {
            break;
        }

        temp = temp->next;
    }

    return temp;
}


template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {

    if ((index < 0) || (index >= numOfNode)) {
        throw -1;
    }

    Node* temp = head;

    for (unsigned int i = 0; i < index; i++) {
        temp = temp->next;
    }

    return temp;
}


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if ((index < 0) || (index >= numOfNode)) {
        throw -1;
    }

    Node* temp = head;

    for (unsigned int i = 0; i < index; i++) {
        temp = temp->next;
    }

    return temp;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}


template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}


template<typename T>
unsigned int LinkedList<T>::Remove(const T &data) {
    unsigned int nodeRemoved = 0;
    Node* temp = head;

    if (head->data == data) {
        RemoveHead();
        nodeRemoved++;

    }

    else if (tail->data == data) {
        RemoveTail();
        nodeRemoved++;
    }

    while (temp != nullptr) {
        if (temp-> data == data) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            Node* temp2 = temp->next;
            delete temp;

            temp = temp2;
            nodeRemoved++;
            numOfNode--;
        }

        temp = temp->next;
    }

    return nodeRemoved;
}

template<typename T>
bool LinkedList<T>::RemoveHead() {

    //linkedlist is empty
    if (head == nullptr) {
        return false;
    }

    else {
        if (numOfNode != 1) {
            head = head->next;

            delete head->prev;

            head->prev = nullptr;
        }

        //one element left
        else {
            delete head;

            head = nullptr;
            tail = nullptr;
        }

        numOfNode--;

        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveTail() {

    //linkedlist is empty
    if (tail == nullptr) {
        return false;
    }

    else {
        if (numOfNode != 1) {
            tail = tail->prev;
            delete tail->next;

            tail->next = nullptr;
        }

        //one element left
        else {
            delete tail;

            tail = nullptr;
            head = nullptr;
        }

        numOfNode--;

        return true;
    }
}

template<typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    Node* temp = head;

    if ((index < 0) || (index >= numOfNode) ) {
        return false;
    }

    for (unsigned int i = 0; i < index; i++) {
        if (temp->next == nullptr) {
            return false;
        }

        temp = temp->next;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    numOfNode--;

    return true;
}

template<typename T>
void LinkedList<T>::Clear() {
    Node* temp = head;

    while (temp != nullptr) {
        head = head->next;
        delete temp;
        temp = head;
    }

    numOfNode = 0;
    head = nullptr;
    tail = nullptr;
}


template<typename T>
void LinkedList<T>::AddHead(const T &data) {
    Node* n = new Node;
    n->data = data;

    if (head == nullptr) {
        head = n;
        tail = n;
    }

    else {
        n->next = head;
        head->prev = n;
        head = n;
    }

    numOfNode++;
}

template<typename T>
void LinkedList<T>::AddTail(const T &data) {
    Node* n = new Node;
    n->data = data;

    if (tail == nullptr) {
        tail = n;
        head = n;
    }

    else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }

    numOfNode++;
}

template<typename T>
void LinkedList<T>::AddNodesHead(const T *data, unsigned int count) {
    for (unsigned int i = 1; i < count + 1; i++) {

        AddHead(data[count - i]);
    }
}

template<typename T>
void LinkedList<T>::AddNodesTail(const T *data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {

        AddTail(data[i]);
    }
}

template<typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &data) {

    //if node is tail
    if (node->next == nullptr) {
        AddTail(data);
    }

    else {
        Node *n = new Node;
        n->data = data;

        n->next = node->next;
        node->next->prev = n;

        n->prev = node;
        node->next = n;

        numOfNode++;
    }
}


template<typename T>
void LinkedList<T>::InsertBefore(Node *node, const T &data) {

    //if node is head
    if (node->prev == nullptr) {
        AddHead(data);
    }

    else {
        Node* n = new Node;
        n->data = data;


        n->prev = node->prev;
        node->prev->next = n;

        n->next = node;
        node->prev = n;

        numOfNode++;
    }
}

template<typename T>
void LinkedList<T>::InsertAt(const T &data, unsigned int index) {
    Node* temp = head;

    if ((index < 0) || (index > numOfNode)) {
        throw -1;
    }


    if (index == numOfNode) {
        AddTail(data);
    }

    else {
        for (unsigned int i = 0; i < index; i++) {

            temp = temp->next;
        }

        InsertBefore(temp, data);
    }
}

//bracket operator const version
template<typename T>
const  T& LinkedList<T>::operator[](unsigned int index) const {
    Node* temp = head;

    if (index < 0) {
        throw -1;
    }

    for (unsigned int i = 0; i < index; i++) {
        if (temp->next == nullptr){
            throw -1;
        }

        temp = temp->next;
    }

    return temp;
}

//bracket operator
template<typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    Node* temp = head;

    if (index < 0) {
        throw -1;
    }

    for (unsigned int i = 0; i < index; i++) {
        if (temp->next == nullptr){
            throw -1;
        }

        temp = temp->next;
    }

    return temp->data;
}

//equality operator
template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const {
    if (this->numOfNode != rhs.numOfNode) {
        return false;
    }

    Node* temp1 = this->head;
    Node* temp2 = rhs.head;

    for (unsigned int i = 0; i < this->numOfNode; i++) {
        if (temp1->data != temp2->data) {
            return false;
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return true;
}

//assignment operator
template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    Node* temp = rhs.head;
    this->tail = nullptr;

    while (temp != nullptr) {
        this->AddTail(temp->data);
        temp = temp->next;
    }

    return *this;
}


//default constructor
template<typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    numOfNode = 0;
}

//copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) {
    Node* temp = list.head;
    this->tail = nullptr;

    while (temp != nullptr) {
        this->AddTail(temp->data);
        temp = temp->next;
    }

}

//destructor
template<typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}