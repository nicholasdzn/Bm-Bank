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

void insertNewUser() // Function to insert a new user
{
    static User *head = nullptr; // Head of the linked list

    User *newUser = new User;
    newUser->id = USER_ID++;
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

void deleteUser() // Function to delete a user
{
    cout << "Delete user" << endl;
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
            insertNewUser();
            break;
        case 2:
            deleteUser();
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