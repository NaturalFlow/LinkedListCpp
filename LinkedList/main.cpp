#include <iostream>
#include <functional>
#include <vector>

template<typename T>
class Node {
public:
    T data;
    Node* next = nullptr;
};
template <typename T>
class LinkedList {
public:
    Node<T>* header = nullptr;
    Node<T>* tail = nullptr;
    void enqueue(T data);
    Node<T>* item(int index);
    Node<T> searchItem(T data);
    void insertItem(int index, T data);
    void deleteItem(int index);
    void transverse(std::function<void(Node<T>)> lambda);
    void printAll();
};
template<typename T>
void LinkedList<T>::enqueue(T data) {
    Node<T>* newNode = new Node<T>;
    newNode->data = data;
    if(header == nullptr){
        header = newNode;
        tail = newNode;
    }else {
        tail->next = newNode;
        tail = newNode;
    }
}
template<typename T>
Node<T>* LinkedList<T>::item(int index) {
    Node<T>* current = header;
    int position = 0;
    while(current != nullptr) {
        if (position == index){
            return current;
        }
        position++;
        current = current->next;
    }
    return current;
}
template<typename T>
Node<T> LinkedList<T>::searchItem(T data) {
    Node<T>* current = header;
    while (current != nullptr){
        if(current->data == data) {
            return *current;
        }
        current = current->next;
    }
    return *current;
}
template<typename T>
void LinkedList<T>::insertItem(int index,T data) {
    Node<T>* newNode = new Node<T>;
    newNode->data = data;
    if(index != 0){
    Node<T>* temp = item(index-1);
    newNode->next = temp->next;
    temp->next = newNode;
    }else {
        newNode->next = header;
        header = newNode;
    }
}
template<typename T>
void LinkedList<T>::deleteItem(int index) {
    if(index !=0){
        Node<T>* temp = item(index-1);
        temp->next = temp->next->next;
    }else {
        header = header->next;
    }

}
template<typename T>
void LinkedList<T>::transverse(std::function<void(Node<T>)> lambda) {
    Node<T>* current = header;
    while(current != nullptr) {
        lambda(*current);
        current = current->next;
    }
}
template<typename T>
void LinkedList<T>::printAll() {
    auto lambda= [](Node<T> node){
        std::cout << node.data << '\n';
    };
    transverse(lambda);
}
int main() {
    LinkedList<int> linkedList;

    //Add item
    linkedList.enqueue(10);
    linkedList.enqueue(20);
    linkedList.enqueue(30);
    linkedList.printAll();

    //Search an item
    auto item = linkedList.searchItem(20);
    std::cout << '\n'<< item.data << '\n';

    //Insert item
    linkedList.insertItem(0,11);
    linkedList.printAll();

    //Delete item
    std::cout << '\n';
    linkedList.deleteItem(0);
    linkedList.printAll();

    //Tranverse
    auto lambda = [](Node<int> node) {
        std::cout <<"Lambda: "<< node.data << '\n';
    };
    linkedList.transverse(lambda);
    std::vector<Node<int>> items;

    auto getData= [&items](Node<int> node) {
         items.push_back(node);
    };
    linkedList.transverse(getData);

    std::cout << "Content of vector items:\n";
    for (auto item : items) {
        std::cout << item.data << '\n';
    }
}
