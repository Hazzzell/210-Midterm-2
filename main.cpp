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

    void delete_name(string name) {
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

    cout << "    Resulting line:\n";
    line.print();

    // 20 min run simulation 
    for (int t = 2; t <= 20; ++t){
        cout << "Time step #" << t << ":\n";

        // 40% - customer being helped at beginning 
        int prob = rand() % 100 + 1;             // prob of 1-100
        if (prob <= 40 && !line.isEmpty()){
            cout << "    " << line.getFrontName() << " is served\n";
            line.pop_front();
        }

        // 60% - new customer join at the end
        if (prob <= 60){
            string name = getRandomName(names);
            line.push_back(name);
            cout << "    " << name << " joined the line\n";
        }   

        // 20% - customer at end don't want to wait and leave
        if (prob <= 20 && !line.isEmpty()){
            cout << "    " << line.getBackName() << " (at the rear) left the line\n";
            line.pop_back();
        }

        // 10% - any customer don't want to wait and leave
        if (prob <= 10 && !line.isEmpty()){
            string name = getRandomName(names);
            cout << "    " << name << " left the line\n";
            line.delete_name(name);
        }
        // 10% - VIP joins
        if (prob <= 10 && !line.isEmpty()){
            string name = getRandomName(names);
            line.push_front(name);
            cout << "    " << name << " (VIP) joins the front of the line\n";
        }

        cout << "    Resulting line:\n";
        line.print();
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
