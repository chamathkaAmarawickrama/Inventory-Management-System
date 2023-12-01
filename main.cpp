#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Product {
public:
    string name;
    int quantity;

    Product(string name, int quantity) {
        this->name = name;
        this->quantity = quantity;
    }

    string toString() {
        return name + " (" + to_string(quantity) + ")";
    }
};

class Node {
public:
    int id;
    Product* product;
    unordered_map<int, Node*> children;

    Node(int id, Product* product) {
        this->id = id;
        this->product = product;
    }

    void addChild(int id, Node* child) {
        children[id] = child;
    }

    string toString() {
        string result = to_string(id) + ": " + product->toString();
        if (!children.empty()) {
            result += " [";
            for (auto it = children.begin(); it != children.end(); ++it) {
                if (it != children.begin()) {
                    result += ", ";
                }
                result += it->second->toString();
            }
            result += "]";
        }
        return result;
    }
};

class Inventory {
public:
    Node* root;
    unordered_map<int, Node*> nodes;
    int nextId;

    Inventory() {
        root = nullptr;
        nextId = 1;
    }

    void insert() {

        int quantity;
        string name;
        int id;
        cout << ">Enter product name: ";
        cin >> name;
        cout << ">Enter product id: ";
        cin >> id;
        cout << ">Enter product quantity: ";
        cin >> quantity;
        Product* product = new Product(name, quantity);
        Node* node = new Node(nextId, product);
        nodes[nextId] = node;
        nextId++;
        if (root == nullptr) {
            root = node;
        } else
        cout << "Product added successfully!" << endl;
    }

    void search() {
        int id;
        cout << ">Enter product ID to search: ";
        cin >> id;
        Node* node =  nodes[id];
        if (node == nullptr) {
            cout << "Product with ID " << id << " not found!" << endl;
        } else {
            cout << "Product found: " << node->product->toString() << endl;
        }
    }

    void update() {
    int id;
    cout << ">Enter product ID to update: ";
    cin >> id;
    Node* node = nodes[id];
    if (node == nullptr) {
        cout << "Product with ID " << id << " not found!" << endl;
    } else {
        string newName;
        int newQuantity;
        cout << ">Enter new product name (or leave blank to keep the existing name): ";
        cin.ignore();
        getline(cin, newName);
        if (newName.empty()) {
            newName = node->product->name;
        }
        cout << ">Enter new product quantity (or 0 to keep the existing quantity): ";
        cin >> newQuantity;
        if (newQuantity == 0) {
            newQuantity = node->product->quantity;
        }
        node->product->name = newName;
        node->product->quantity = newQuantity;
        cout << "Product updated successfully!" << endl;
    }
}

void remove() {
    int id;
    cout << ">Enter product ID to delete: ";
    cin >> id;
    Node* node = nodes[id];
    if (node == nullptr) {
        cout << "Product with ID " << id << " not found!" << endl;
    } else {

   cout << "Product deleted successfully!" << endl;
    }
}
void show() {

    if (root != nullptr) {
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            Node* node = it->second;
            cout << "ID: " << node->id << endl;
            cout << "Product Details: " << node->product->toString() << endl;
            cout << "Children: ";
            if (!node->children.empty()) {
                cout << "[ ";
                for (auto childIt = node->children.begin(); childIt != node->children.end(); ++childIt) {
                    cout << childIt->first << " ";
                }
                cout << "]";
            }
            cout << endl << endl;
        }
    } else {
        cout << "Inventory is empty." << endl;
    }
}


    void printInventory() {
        if (root != nullptr) {
            for (auto it = nodes.begin(); it != nodes.end(); ++it) {
                Node* node = it->second;
                if (node->id == root->id) {
                    cout << node->toString() << endl;
                }
            }
        }
    }
};

int main() {
    Inventory inventory;
    int choice;
    while (true) {
        cout << "           ====================================================" << endl;
        cout <<"           -Welcome To Inventory Management System Application-   " << endl;
        cout << "           ====================================================\n" << endl;
        cout << "                 ------Inventory Management System------\n" << endl;
        cout << "s.no\tFunction\t\t\tDescription" << endl;
        cout << "1\tAllocate Product\t\tInsert New Product" << endl;
        cout << "2\tSearch Products\t\t\tSearch Product Using ProductID" << endl;
        cout << "3\tUpdate Product Record\t\tUpdate Product Records" << endl;
        cout << "4\tDelete Product\t\t\tDelete Product" << endl;
        cout << "5\tShow All Product Record\t\tShow Product Records That(We Added)" << endl;
        cout << "6\tExit\n" << endl;
        cout << ">>Enter Your Choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                inventory.insert();

                break;
            case 2:
                inventory.search();
                break;
            case 3:
                inventory.update();
                break;
            case 4:
                inventory.remove();
               break;
            case 5:
                inventory.show();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    }

}
