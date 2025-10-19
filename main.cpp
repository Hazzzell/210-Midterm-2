#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Doubly Linked List Class
class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void delete_val(string name) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != name)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    // get the name of customer at the front
    string getFrontName() const {
        return head ? head->data : "";
    }

    // get the name of customer at the back
    string getBackName() const {
        return tail ? tail->data : "";
    }

    // check if line is empty
    bool isEmpty() const{
        return head == nullptr;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

// function prototypes
// vector<string>& names reads the comment from file names.txt
// arguments: const string &names
// returns: NA
void loadNames(vector<string>& names);
string getRandomName(const vector<string>& names);

int main() {
    srand(time(0));
    vector<string> names;
    loadNames(names);

    DoublyLinkedList line;

    cout << "Store opens:\n";

    // 5 customers at the opening 
    for (int i = 0; i < 5; i++){
        string name = getRandomName(names);
        line.push_back(name);
        cout << "    " << name << " joins the line\n";
    }

    
    return 0;
}

void loadNames(vector<string>& names){
    ifstream file("names.txt");
    string name;
    while (file >> name){
        names.push_back(name);
    }
}

string getRandomName(const vector<string>& names){
    if (names.empty()) return "Unknown";
    int index = rand() % names.size();
    return names[index];
}
