#include <iostream>
#include <string>
#include <fstream>
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

void writeOperationToFile(int operationNumber) // Write Operation number to file (1 for insert, 2 for delete, etc.)
{
    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << operationNumber << endl;
        file.close();
    }
}
void insertNewUser()
{ // Function to insert a new user
    User *newUser = new User;
    newUser->id = USER_ID++; // Remember, the compiler first initializes the variable and then assigns the value, so this will not increment the ID in the first iteration
    cout << "Enter user name: ";
    cin.ignore();
    getline(cin, newUser->name);
    cout << "Enter user age: ";
    cin >> newUser->age;
    cout << "Enter initial balance: ";
    cin >> newUser->balance;
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

    // Grava o novo usuário em um arquivo CSV
    ofstream file("users.txt", ios::app);
    if (file.is_open())
    {
        file << newUser->id << "," << newUser->name << "," << newUser->age << "," << newUser->balance << endl;
        file.close();
        cout << "Usuário gravado no arquivo com sucesso." << endl;
    }
    else
    {
        cout << "Erro ao abrir o arquivo para gravação." << endl;
    }
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
    delete temp;

    cout << "User deleted successfully." << endl;
}

void searchUser() // Function to search for a user
{
    cout << "Search user" << endl;
}

void transferMoney() // Function to transfer money
{
    cout << "Transfer money" << endl;
}

void loadFileToMemory() // Function to load a file (.txt) and write it in the memory
{
    cout << "Load file" << endl;
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
            writeOperationToFile(1); // Log the operation
            for (int i = 0; i < numUsers; i++)
            {
                insertNewUser();
            }
            break;
        case 2:
            writeOperationToFile(2); // Log the operation
            int userId;
            cout << "Enter user ID to delete: ";
            cin >> userId;
            deleteUser(userId);
            break;
        case 3:
            searchUser();
            break;
        case 4:
            transferMoney();
            break;
        case 5:
            loadFileToMemory();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}