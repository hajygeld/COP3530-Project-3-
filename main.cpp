#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <random>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <random>
#include <map>
#include <cstdlib>
#include <ctime>
#include <stack>
using namespace std::chrono;

using namespace std;


// The BankAccount class serves to represent each customer account that is stored in the bank database.
// Given that this class is independent of the map implementations, there are no differences between objects of
// this class type stored in ordered and unordered maps.


class BankAccount{
private:
    int clientID;
    string name;
    int password;
    double balance;
public:
    BankAccount(string thisName, int thisPassword, double thisBalance, int thisClientID){
        name = thisName;
        password = thisPassword;
        balance = thisBalance;
        clientID = thisClientID;
    }
    double getBalance();
    int getID();
    int getPassword();
    string getName();
    void getBudget();
    void subtractFunds(double amount);
    bool transferMoney(int customerID, double amount);
    void setBalance(double b);

    BankAccount();
};

void BankAccount::setBalance(double b){
    balance = b;
}
int BankAccount::getID() {
    return clientID;
}

int BankAccount::getPassword() {
    return password;
}

double BankAccount::getBalance(){
    return balance;
}

string BankAccount::getName() {
    return name;
}

void BankAccount::getBudget(){
    cout << "Food: $" <<  0.2* balance << endl;
    cout << "Savings: $" << 0.2 * balance << endl;
    cout << "Other Expenses: $" << 0.25 * balance << endl;
    cout << "Disposable Income: $" << 0.05 * balance << endl;
    cout << "Insurance: $" << 0.10 * balance << endl;
    cout << "Monthly Bills: $" << 0.20 * balance << endl;
}
//Checks if the inputted ID matches an existing ID in the database. If not, the transfer request is rejected.
bool BankAccount::transferMoney(int customerID, double amount){
    if(customerID == BankAccount::getID()) {
        this->balance += amount;
        return true;
    } else{
        return false;
    }
}

//Called when a transfer is successful.
void BankAccount::subtractFunds(double amount) {
    this->balance -= amount;
}

BankAccount::BankAccount() {

}

class unorderedmap{
public:
    vector<vector<BankAccount>> map;
    int hashindex;
    unorderedmap(int hashin);
    unorderedmap();
};
unorderedmap::unorderedmap(int hashin){
    hashindex = hashin;
}
unorderedmap::unorderedmap(){

}
struct AVLTree{
public:
    BankAccount* b;
    int ID = 0;
    string name;
    AVLTree* left;
    AVLTree* right;
    AVLTree* grandchild;
    AVLTree* newParent;
    int height = 0;
    AVLTree(){
        b = this->b;
        ID = this->ID;
        name = this->name;
        left = nullptr;
        right = nullptr;
        grandchild = nullptr;
        newParent = nullptr;
        height = 0;
    };
    //Initializes a new node that includes a pointer to a BankAccount object to store both the account and
    //the associated features.
    ~AVLTree();
    AVLTree* createNewNode(int x, BankAccount* &bank){
        AVLTree *node = new AVLTree();
        node->ID = bank->getID();
        node->b = bank;
        //cout << node->b->getID() << endl;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }

    int getHeight(AVLTree* node){
        if (node == nullptr) {
            return 0;
        }
        else {
            // The two lines of code below will find the heights of the left and right subtrees, respectively.
            int leftSubtree = getHeight(node->left);
            int rightSubtree = getHeight(node->right);

            // Following the height formula:
            return max(leftSubtree, rightSubtree) + 1;
        }
    }

    //Concept for code structure derived from https://cppsecrets.com/users/1039649505048495348575464115971151161149746979946105110/C00-AVL-Rotations.php.
    AVLTree* leftRotation(AVLTree *root)
    {
        if(root != nullptr){
            //temp is A
            AVLTree *temp;
            AVLTree *secondTemp;
            temp = root;
            secondTemp = temp->left;

            temp->left = secondTemp->right;
            secondTemp->right = temp;

            return secondTemp;
        }else{
            return root;
        }
    }

    //Concept for code structure derived from https://cppsecrets.com/users/1039649505048495348575464115971151161149746979946105110/C00-AVL-Rotations.php.
    AVLTree* rightRotation(AVLTree *node)
    {
        if(node != nullptr){
            AVLTree *temp;
            AVLTree *secondTemp;
            temp = node;
            secondTemp = temp->right;

            temp->right = secondTemp->left;
            secondTemp->left = temp;

            return secondTemp;
        }else{
            return node;
        }
    }

    //Concept for code structure derived from https://cppsecrets.com/users/1039649505048495348575464115971151161149746979946105110/C00-AVL-Rotations.php.
    AVLTree* rotateLeftRight(AVLTree *root)
    {
        if(root != nullptr){
            AVLTree *p;
            AVLTree *temp;
            AVLTree *secondTemp;
            p = root;
            temp = p->left;
            secondTemp =p->left->right;

            p -> left = secondTemp->right;
            temp ->right = secondTemp->left;
            secondTemp ->right = p;
            secondTemp->left = temp;

            return secondTemp;
        }else{
            return root;
        }
    }

    //Concept for code structure derived from https://cppsecrets.com/users/1039649505048495348575464115971151161149746979946105110/C00-AVL-Rotations.php.
    AVLTree* rotateRightLeft(AVLTree *node)
    {
        if(node != nullptr){
            AVLTree *p;
            AVLTree *temp;
            AVLTree *secondTemp;
            p = node;
            temp = p->right;
            secondTemp =p->right->left;

            p -> right = secondTemp->left;
            temp ->left = secondTemp->right;
            secondTemp ->left = p;
            secondTemp->right = temp;

            return secondTemp;
        }else{
            return node;
        }
    }

    //Insert function.
    //Insert function. If the inserted root does not already exist, calls the createNewNode function.
    //Uses the BankAccount class to pass in the customer account into the tree.
    //Recursively goes through the tree to insert the node.
    //Depending on the balance factor, performs the necessary rotations.
    AVLTree* insert(AVLTree* root, int id, BankAccount* account){
        if(root == nullptr){
            string temp;
            root = createNewNode(id, account);
            return root;
        }

        if (id < root->ID) {
            root->left = insert(root->left, id, account);
        } else {
            root->right = insert(root->right, id, account);
        }
        int balanceFactor = getHeight(root->left) - getHeight(root->right);
        if (balanceFactor < -1) {
            if (id > root->right->ID) {
                return rightRotation(root);
            }
            if (id < root->right->ID) {
                return rotateRightLeft(root);
            }
        }
        if (balanceFactor > 1) {
            if (id < root->left->ID) {
                return leftRotation(root);
            }
            if (id > root->left->ID) {
                return rotateLeftRight(root);
            }
        }

        return root;
    }

    //Potential insert helper function.
    //Remove function.


    //Search function.
    //Search function that returns a BankAccount object. Uses a stack to temporarily store nodes and compare them based on their ID values.
    //If the key equals the value, the function will return the BankAccount object. If the key is greater, search from the right child, otherwise continue the search from the left child.
    BankAccount* searchID(AVLTree* root, int val) {
        if (root == nullptr) return nullptr;
        stack<AVLTree*> st;
        st.push(root);
        while (!st.empty()) {
            auto cur = st.top();
            st.pop();
            if (cur == nullptr) continue;
            if (val == cur->ID) {
                return cur->b;
            }
            if (val > cur->ID) {
                st.push(cur->right);
            } else {
                st.push(cur->left);
            }
        }
        return nullptr;
    }

    int inOrderIterator(AVLTree* root, int &levelNumber, int counter){
        if(root != nullptr){
            counter = inOrderIterator(root->left, levelNumber, counter);
            if (counter > levelNumber) {
                return counter;
            }
            if (counter == levelNumber) {
                return root->ID;
            }
            counter++;
            counter = inOrderIterator(root->right, levelNumber, counter);
        }
        return counter;
    }

    //Print level count.

    void printLevelCount(AVLTree* root, int &temp){
        if(root == nullptr){
            height = getHeight(root);

        } else {
            height = getHeight(root);
            temp++;
        }
        cout << height << endl;
    }
    //Any other helper functions that will make the other functions easier to write.

};

AVLTree::~AVLTree() = default;

void helperDestructor(AVLTree* root){
    if(root == nullptr){
        return;
    }

    helperDestructor(root->left);
    helperDestructor(root->right);

    delete root;
}

void deleteNode(AVLTree** temp){
    helperDestructor(*temp);
    *temp = nullptr;
}

//This class builds an ordered map that is backed up by an AVL tree. It embodies the basic functionalities
//that a built-in map would have, such as insertion. The class uses the tree to retrieve BankAccount objects.
//These objects are then stored in the ordered map after all necessary rotations are performed by the tree.
class Map{
public:
    AVLTree* a;
    Map(){
        a = this->a;
    }
    void insert(AVLTree* &root, int key, BankAccount* &bank);
    BankAccount* get(AVLTree* &root, int key, bool &chagra);
    double getBalance(AVLTree* root, int key, bool chagra);
    string getName(AVLTree* root, int key);
    int getPassword(AVLTree* root, int key);
};

void Map::insert(AVLTree* &root, int key, BankAccount* &bank) {
    root = this->a->insert(root,key, bank);
}
BankAccount* Map::get(AVLTree* &root, int key, bool &chagra) {
    return this->a->searchID(root, key);
}

double Map::getBalance(AVLTree* root, int key, bool chagra) {
    BankAccount* b = get(root,key, chagra);
    if(b == nullptr){
        return -1;
    }
    return b->getBalance();
}
//string Map::getName(AVLTree* root, int key) {
//    BankAccount* b = get(root,key);
//    if(b == nullptr){
//        return "";
//    }
//    return b->getName();
//}
//



//Instantiate AVL Tree.
//Two AVLTree objects are created. The node object is used as an input for the AVLTree functions.
//The test object is used to instantiate these functions in the main() function.

//The main function relies on a series of count variables to keep track of the number of commands that are
//predicted to be inputted by the program and how many commands were already executed.
//If the number of commands executed reaches the same value as the variable that stores the number of commands
//in total, the while loop will end and the tree will be destructed.



//The main function allows the user to choose between an ordered or unordered map implementation.
//In either case, the program will begin to read in all of the data from the data.csv file. During the
//reading, objects of type BankAccount are inserted into the corresponding map implementation.
//From there, the user will receive a series of prompts that are similar between the two map implementations.
int main() {
    int mchoice = 0;
    cout << "[1] ordered map" << endl;
    cout << "[2] unordered map" << endl;
    cin >> mchoice;
    if (mchoice == 1) {
        int username;
        int select;
        bool menu = true;
        bool testBoolean = true;
        Map mapObject;
        BankAccount *b;
        AVLTree *node = nullptr;
        //AVLTree* node;
        bool start = true;
        bool bank;
        //parse input
        map<int, BankAccount *> container;
        string temp = "test";
        fstream someFile;
        int count = 0;
        someFile.open("data.csv");
        auto timer = high_resolution_clock::now();
        if (someFile.is_open()) {
            string lineFile;

            getline(someFile, lineFile);


            while (getline(someFile, lineFile)) {
                istringstream stream(lineFile);
                string password;
                int clientID = 0;
                string temporaryNumber;
                string name;
                int userPassword = 0;
                string balance;
                double userBalance = 0;
                string tempPieceCount;
                string tempPrice;
                getline(stream, temporaryNumber, ',');
                clientID = stoi(temporaryNumber);

                getline(stream, name, ',');

                getline(stream, password, ',');
                userPassword = stoi(password);

                getline(stream, balance, ',');
                userBalance = stod(balance);

                b = new BankAccount(name, userPassword, userBalance, clientID);

                mapObject.insert(node, clientID, b);
                count++;
            }


        } else {
            cout << "This file has failed to open. Please, examine the code for any faults.";
        }
        someFile.close();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - timer);

        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;

        int input;
        int number;
        time_t timev;
        cout << "Welcome to Freedom Bank. How can we help you today?" << endl;
        cout << "[1] Login " << endl;
        cout << "[2] Create New Account " << endl;
        int choice;
        cin >> choice;
        //After the data is read, the customer can either log in into an existing account or create a new one entirely.
        // The username MUST match an ID in the dataset for the customer to successfully log into an account.
        // Otherwise, when creating an account, the ID of choice CANNOT be the same as any other ID in the dataset.

        while (start) {
            if (choice == 1) {
                cout << "Username: " << endl;
                cin >> input;
                username = input;
                cout << "Password: " << endl;
                cin >> number;
                int password = number;

                if (mapObject.get(node, username, testBoolean)->getPassword() != number) {
                    cout << "Incorrect password please try again." << endl;
                } else {
                    start = false;
                }
            }
            if (choice == 2) {
                int newID;
                int newPassword;
                string newName;
                double newBalance;
                cout << "Enter an ID: ";
                cin >> newID;
                cout << "Enter a password: ";
                cin >> newPassword;
                cout << "Enter a name to be associated with this account: ";
                cin >> newName;
                cout << "Enter a minimum of $25 to be deposited: ";
                cin >> newBalance;

                if (newBalance < 25) {
                    cout << "Error: Please, make an initial deposit of at least $25." << endl;
                } else if (newID <= 100000) {
                    cout << "Error: ID must be unique." << endl;
                } else {
                    b = new BankAccount(newName, newPassword, newBalance, newID);
                    mapObject.insert(node, newID, b);
                    cout << "Success! Welcome, " << mapObject.get(node, newID, testBoolean)->getName()
                         << "! Your account is now ready for use." << endl;
                    username = newID;
                    start = false;
                }
            }
        }

        //The customer is now able to choose to view the current account balance, budget distribution and money transfers.
        // The customer can also alternatively change the budget distribution based on his or her balance, which is
        // split into percentages.
        // If the customer wants to send money, the recipient's ID must be an existing ID.
        // Furthermore, the customer cannot send more money that is stored in his or her bank account.

        while (menu) {
            cout << "Select an option: " << endl;
            cout << "[1] Check Balance " << endl;
            cout << "[2] Budget Calculator " << endl;
            cout << "[3] Send Money " << endl;
            cout << "[4] Sign Out" << endl;
            cin >> select;

            if (select == 1) {
                auto timer = high_resolution_clock::now();

                cout << "Hi, " << mapObject.get(node, username, testBoolean)->getName() << ", your balance is $"
                     << mapObject.get(node, username, testBoolean)->getBalance() << endl;
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - timer);
                cout << "This took " << duration.count() << " microseconds" << endl << endl;
            }
            if (select == 2) {
                auto timer = high_resolution_clock::now();
                int sel = 0;
                cout << "Breakdown of Current Budget: " << endl;
                cout << "[1] Change budget percents" << endl;
                cout << "[2] Use recommended values" << endl;
                cin >> sel;


                if (sel == 1) {
                    cout << "DO NOT ADD PERCENT (%) SIGN" << endl;
                    double food = 0;
                    double savings = 0;
                    double oe = 0;
                    double di = 0;
                    double ins = 0;
                    double mb = 0;
                    cout << "Food percentage: " << endl;
                    cin >> food;
                    cout << "Savings percentage: " << endl;
                    cin >> savings;
                    cout << "Other Expenses percentage: " << endl;
                    cin >> oe;
                    cout << "Disposable Income percentage: " << endl;
                    cin >> di;
                    cout << "Insurance percentage: " << endl;
                    cin >> ins;
                    cout << "Monthly Bills percentage: " << endl;
                    cin >> mb;


                    cout << "Food: $" << food * mapObject.get(node, username, testBoolean)->getBalance() / 100 << endl;
                    cout << "Savings: $" << savings * mapObject.get(node, username, testBoolean)->getBalance() / 100
                         << endl;
                    cout << "Other Expenses: $" << oe * mapObject.get(node, username, testBoolean)->getBalance() / 100
                         << endl;
                    cout << "Disposable Income: $"
                         << di * mapObject.get(node, username, testBoolean)->getBalance() / 100 << endl;
                    cout << "Insurance: $" << ins * mapObject.get(node, username, testBoolean)->getBalance() / 100
                         << endl;
                    cout << "Monthly Bills: $" << mb * mapObject.get(node, username, testBoolean)->getBalance() / 100
                         << endl;
                    cout << endl;

                } else {
                    mapObject.get(node, username, testBoolean)->getBudget();
                }
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - timer);
                cout << "This took " << duration.count() << " microseconds" << endl << endl;
            }
            if (select == 3) {
                auto timer = high_resolution_clock::now();

                int recipient;
                double amount;
                cout << "Please, enter the ID of the desired recipient: ";
                cin >> recipient;
                cout << endl;
                cout << "Got it. Now, enter the amount that you want to send: ";
                cin >> amount;
                bool verification = false;
                if (recipient <= 100000) {
                    if (amount <= mapObject.get(node, username, testBoolean)->getBalance()) {
                        verification = mapObject.get(node, recipient, testBoolean)->transferMoney(recipient, amount);
                    } else {
                        cout << "Error! Insufficient funds." << endl;
                        continue;
                    }
                }
                if (verification) {
                    cout << "Success!" << endl;
                    mapObject.get(node, username, testBoolean)->subtractFunds(amount);
                } else {
                    cout << "Error! Transfer unsuccessful. Please, verify the recipient's ID." << endl;
                }
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - timer);
                cout << "This took " << duration.count() << " microseconds" << endl << endl;
            }
            if (select == 4) {
                cout << "Thank you for using the Freedom Bank Online Banking System!" << endl;
                menu = false;
            }
        }
        //ordered map
        return 0;
    } else {
        //create unordered map
        unorderedmap m(100000000000000);
        vector<vector<BankAccount>> umap = m.map;

        hash<double> hasher;
        BankAccount user;
        //push empty vectors into bankaccount
        for (int i = 0; i < 200000; i++) {
            umap.push_back(vector<BankAccount>());
        }


        fstream someFile;
        int count = 0;
        someFile.open("data.csv");
        auto timeStart = high_resolution_clock::now();
        if (someFile.is_open()) {
            string lineFile;

            getline(someFile, lineFile);

            //timing method via geeks for geeks


            //insert() read values from file O(n) where n is number of values in file
            while (getline(someFile, lineFile) && count != 100000) {
                istringstream stream(lineFile);
                string password;
                int clientID = 0;
                string temporaryNumber;
                string name;
                int userPassword = 0;
                string balance;
                double userBalance = 0;
                string tempPieceCount;
                double price = 0.00;
                string tempPrice;

                getline(stream, temporaryNumber, ',');
                clientID = stoi(temporaryNumber);

                getline(stream, name, ',');

                getline(stream, password, ',');
                userPassword = stoi(password);

                getline(stream, balance, ',');
                userBalance = stod(balance);

                int index = hasher(clientID) / 100000000000000;
                //cout << index << endl;

                umap[index].push_back(BankAccount(name, userPassword, userBalance, clientID));

                count++;
            }

        } else {
            cout << "This file has failed to open. Please, examine the code for any faults." << endl;
        }
        someFile.close();
        //via geeks for geeks
        auto timeStop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(timeStop - timeStart);

        cout << "Insertion of 100,000 elements into unordered map took " << duration.count() << " microseconds" << endl
             << endl;


        time_t timev;
        int username;
        int password;
        cout << "Welcome to Freedom Bank. How can we help you today?" << endl;
        bool start = true;
        int select = 0;
        int inp = 0;
        cout << "Select an option: " << endl;
        cout << "[1] Login " << endl;
        cout << "[2] Create New Account " << endl;
        cin >> inp;
        if (inp == 2) {
            string name;
            int clientID;
            int userPassword;
            double userBalance;
            cout << "Enter an ID: " << endl;
            cin >> clientID;
            cout << "Enter a password: " << endl;
            cin >> userPassword;
            cout << "Enter a name to be associated with this account: " << endl;
            cin >> name;
            cout << "Enter a minimum of $25 to be deposited: " << endl;
            cin >> userBalance;
            int index = hasher(clientID) / 100000000000000;
            umap[index].push_back(BankAccount(name, userPassword, userBalance, clientID));
            cout << "Success! Welcome, " << name << "! Your account is now ready for use." << endl;

        }


        //main loop O(N) where N is operations done by user
        while (start) {
            cout << "Username: " << endl;
            cin >> username;
            cout << "Password: " << endl;
            cin >> password;

            bool valid = false;

            //cout << umap[username][45279].getID()<< endl;
            int index = hasher(username) / 100000000000000;

            for (int i = 0; i < umap[index].size(); i++) {
                if (umap[index][i].getID() == username && umap[index][i].getPassword() == password) {
                    cout << "Welcome " << umap[index][i].getName() << "!" << endl;
                    user = umap[index][i];
                    valid = true;
                    start = false;
                }

            }
            if (!valid) {
                cout << "Incorrect Username or Password." << endl;

            }


        }


        bool menu = true;
        while (menu) {
            cout << "Select an option: " << endl;
            cout << "[1] Check Balance " << endl;
            cout << "[2] Budget Calculator " << endl;
            cout << "[3] Send Money " << endl;
            cout << "[4] Sign Out" << endl;
            cin >> select;

            //check balance O(1)
            if (select == 1) {
                auto timer = high_resolution_clock::now();
                cout << "Hi, " << user.getName() << ", your balance is $" << user.getBalance() << endl;
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - timer);
                cout << "This took " << duration.count() << " microseconds" << endl << endl;

            }
            //get current budget O(1)
            if (select == 2) {
                auto timer = high_resolution_clock::now();

                int sel = 0;
                cout << "Breakdown of Current Budget: " << endl;
                cout << "[1] Change budget percents" << endl;
                cout << "[2] Use recommended values" << endl;
                cin >> sel;
                //set budget amount
                if (sel == 1) {
                    cout << "DO NOT ADD PERCENT (%) SIGN" << endl;
                    double food = 0;
                    double savings = 0;
                    double oe = 0;
                    double di = 0;
                    double ins = 0;
                    double mb = 0;
                    cout << "Food percentage: " << endl;
                    cin >> food;
                    cout << "Savings percentage: " << endl;
                    cin >> savings;
                    cout << "Other Expenses percentage: " << endl;
                    cin >> oe;
                    cout << "Disposable Income percentage: " << endl;
                    cin >> di;
                    cout << "Insurance percentage: " << endl;
                    cin >> ins;
                    cout << "Monthly Bills percentage: " << endl;
                    cin >> mb;
                    cout << "Food: $" << food * user.getBalance() / 100 << endl;
                    cout << "Savings: $" << savings * user.getBalance() / 100 << endl;
                    cout << "Other Expenses: $" << oe * user.getBalance() / 100 << endl;
                    cout << "Disposable Income: $" << di * user.getBalance() / 100 << endl;
                    cout << "Insurance: $" << ins * user.getBalance() / 100 << endl;
                    cout << "Monthly Bills: $" << mb * user.getBalance() / 100 << endl;
                    cout << endl;
                    //use default values
                } else {
                    user.getBudget();
                }

                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - timer);
                cout << "This took " << duration.count() << " microseconds" << endl << endl;
            }

            //transferMoney O(N) where N is the amount of collissions at index
            if (select == 3) {
                auto timer = high_resolution_clock::now();

                int recipient;
                double amount;
                string recname;
                cout << "Please, enter the ID of the desired recipient: ";
                cin >> recipient;
                cout << "Please, enter the name of the desired recipient: ";
                cin >> recname;

                cout << "Got it. Now, enter the amount that you want to send: ";
                cin >> amount;
                bool verification = false;
                bool infunds = false;
                recipient = hasher(recipient) / 100000000000000;

                for (int i = 0; i < umap[recipient].size(); i++) {
                    if (umap[recipient][i].getName() == recname) {
                        if (user.getBalance() - amount < 0) {
                            cout << "Error! Insufficient funds." << endl;
                            infunds = true;
                        } else {
                            umap[recipient][i].setBalance(umap[recipient][i].getBalance() + amount);
                            user.setBalance(user.getBalance() - amount);

                            verification = true;
                        }
                    }

                    if (verification) {
                        cout << "Success!" << endl;
                    } else if (infunds) {

                    } else {
                        cout << "Error! Transfer unsuccessful. Please, verify the recipient's ID." << endl;
                    }

                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - timer);
                    cout << "This took " << duration.count() << " microseconds" << endl << endl;
                }

                //exit while loop
                if (select == 4) {
                    cout << "Thank you for using the Freedom Bank Online Banking System!" << endl;
                    menu = false;
                }
            }
        }
        return 0;
    }
}