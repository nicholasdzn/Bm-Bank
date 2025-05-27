#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> // Include for std::fixed and std::setprecision
#include <limits>  // Include for numeric_limits
using namespace std;

int USER_ID = 1; // Constant for user ID

struct User // Structure to represent a user
{
    int id;
    string name;
    int age;
    double balance;
    User *next;
};

User *head = nullptr; // Global head pointer for the linked list

void writeUsersToFile() // Write Operation number to file (1 for insert, 2 for delete, etc.)
{
    ofstream file("users.txt", ios::out | ios::trunc);
    if (file.is_open())
    {
        file << USER_ID - 1 << endl;
        file << std::fixed;           // Set fixed-point notation
        file << std::setprecision(2); // Set precision to 2 decimal places
        for (User *temp = head; temp != nullptr; temp = temp->next)
        {
            file << temp->name << "," << temp->age << "," << temp->balance << endl;
        }
    }
    else
    {
        cout << "Error to open the file" << endl;
    }
}

void insertNewUser()
{ // Function to insert a new user
    User *newUser = new User;
    newUser->id = USER_ID++; // Remember, the compiler first initializes the variable and then assigns the value, so this will not increment the ID in the first iteration
    string tempName;
    cin.ignore(); // Ensure buffer is clear before first getline
    do
    {
        cout << "Enter user name (max 100 characters): ";
        getline(cin, tempName);
        if (tempName.empty())
        {
            cout << "Name cannot be empty. Please enter a valid name." << endl;
            continue;
        }
        if (tempName.length() > 100)
        {
            cout << "Name too long. Please enter up to 100 characters." << endl;
        }
        else
        {
            bool isNumber = true;
            for (char c : tempName)
            {
                if (!isdigit(c))
                {
                    isNumber = false;
                    break;
                }
            }
            if (isNumber)
            {
                cout << "Name cannot be a number. Please enter a valid name." << endl;
                tempName.clear();
            }
        }
    } while (tempName.empty() || tempName.length() > 100);
    newUser->name = tempName;
    int tempAge;
    while (true)
    {
        cout << "Enter user age: ";
        if (cin >> tempAge && tempAge > 0)
        {
            newUser->age = tempAge;
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid age (positive integer)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    double tempBalance;
    while (true)
    {
        cout << "Enter initial balance (ex. xxxx.xx): ";
        if (cin >> tempBalance && tempBalance >= 0)
        {
            newUser->balance = tempBalance;
            break;
        }
        else
        {
            cout << "Invalid input. Please enter a valid balance (non-negative number)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    newUser->next = nullptr;

    if (head == nullptr)
    {
        head = newUser;
    }
    else
    {
        User *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newUser;
    }
    cout << "User inserted successfully with ID: " << newUser->id << endl;
}

void deleteUser(int userId) // Function to delete a user
{
    User *temp = head;
    User *prev = nullptr;

    while (temp != nullptr && temp->id != userId)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        cout << "User not found." << endl;
        return;
    }

    if (prev == nullptr)
    {
        head = temp->next; // Deleting the head
    }
    else
    {
        prev->next = temp->next; // Bypass the node to delete it
    }
    cout << "User " << temp->id << " deleted successfully." << endl;
    delete temp;
}

void searchUser(int id) // Function to search for a user
{
    User *temp = head;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << "User " << temp->id << " have R$" << temp->balance << " in the account." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "User not found." << endl;
}

void transferMoney(int user1, int user2, double money) // Function to transfer money
{
    User *temp1 = head;
    User *temp2 = head;

    while (temp1 != nullptr && temp1->id != user1)
    {
        temp1 = temp1->next;
    }

    while (temp2 != nullptr && temp2->id != user2)
    {
        temp2 = temp2->next;
    }

    if (temp1 == nullptr || temp2 == nullptr)
    {
        cout << "User not found." << endl;
        return;
    }

    if (temp1->balance < money)
    {
        cout << "Insufficient balance." << endl;
        return;
    }

    temp1->balance -= money;
    temp2->balance += money;

    cout << "Transfer successful. New balance for user " << user1 << ": R$" << temp1->balance << endl;
}

void loadFileToMemory() // Function to load a file (.txt) and write it in the memory
{
    if (head != nullptr)
    {
        cout << "Memory already loaded. Please restart the program to load a new file." << endl;
        return;
    }
    ifstream file("users.txt");
    if (!file.is_open())
    {
        cout << "Erro ao abrir o arquivo para leitura." << endl;
        return;
    }

    string line;
    User *last = nullptr;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos)
            continue;

        User *newUser = new User;
        newUser->id = USER_ID++;
        newUser->name = line.substr(0, pos1);
        newUser->age = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        newUser->balance = stod(line.substr(pos2 + 1));
        newUser->next = nullptr;

        if (head == nullptr)
        {
            head = newUser;
        }
        else
        {
            last->next = newUser;
        }
        last = newUser;
    }
    file.close();
    cout << "Users loaded from file successfully." << endl;
}

int main()
{
    int choice;
    do
    {
        cout << "1. Insert new user" << endl;
        cout << "2. Delete user" << endl;
        cout << "3. Search user" << endl;
        cout << "4. Transfer money" << endl;
        cout << "5. Load file to memory" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "How many users do you want to insert? ";
            int numUsers;
            cin >> numUsers;
            for (int i = 0; i < numUsers; i++)
            {
                insertNewUser();
            }
            numUsers == 1 ? cout << "User with id " << USER_ID - 1 << " inserted sucessfully" << endl : cout << numUsers << " Users with id " << USER_ID - numUsers << " to id " << USER_ID - 1 << " inserted succesfully" << endl;
            break;
        case 2:
            int userId;
            cout << "Enter user ID to delete: ";
            cin >> userId;
            deleteUser(userId);
            break;
        case 3:
            cout << "Enter user ID to search: ";
            cin >> userId;
            searchUser(userId);
            break;
        case 4:
            int user1, user2;
            double money;
            cout << "Enter sender user ID: ";
            cin >> user1;
            cout << "Enter receiver user ID: ";
            cin >> user2;
            cout << "Enter amount to transfer: ";
            cin >> money;
            if (user1 == user2)
            {
                cout << "You cannot transfer money to yourself." << endl;
                break;
            }
            transferMoney(user1, user2, money);
            break;
        case 5:
            loadFileToMemory();
            break;
        case 0:
            writeUsersToFile(); // Save users to file before exiting
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}