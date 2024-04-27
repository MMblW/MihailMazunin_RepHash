#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

const int HashArraySize = 10;
const double PiOverFour = M_PI_4;
int CollisionCounter = 0;

struct Node
{
    string key = " ";
    string value = " ";
    Node* next = nullptr;
    Node* prev = nullptr;
};

struct HashTable
{
    Node* table[HashArraySize];
    HashTable()
    {
        for (int i = 0; i < HashArraySize; ++i)
        {
            table[i] = nullptr;
        }
    }
};

double mod1(double var)
{
    int intPart = static_cast<int>(var);
    return var - intPart;
}

int GetHash(double var)
{
    return static_cast<int>(HashArraySize * mod1(var * PiOverFour));
}

int GetHash(string line)
{
    int var = 0;
    for (int i = 0; i < line.size(); i++)
    {
        var += static_cast<int>(pow(line[i], 2) * M_2_SQRTPI + abs(line[i]) * M_SQRT1_2);
    }
    return GetHash(abs(var));
}

bool Add(HashTable& mytable, string key, string element)
{
    Node* newNode = new Node;
    newNode -> key = key;
    newNode -> value = element;
    newNode -> next = nullptr;
    newNode -> prev = nullptr;
    int hash = GetHash(key);
    if(mytable.table[hash] == nullptr)
    {
        mytable.table[hash] = newNode;
        return true;
    }
    else
    {
        Node* current = mytable.table[hash];
        while (current -> next != nullptr)
        {
            current = current -> next;
        }
        current -> next = newNode;
        newNode -> prev = current;
        CollisionCounter++;
        return true;
    }
}

bool RemoveByKey (HashTable& mytable, string key)
{
    int hash = GetHash(key);
    Node* current = mytable.table[hash];
    while (current != nullptr)
    {
        if (current -> key == key)
        {
            if (current -> prev != nullptr)
            {
                current -> prev -> next = current -> next;
            }
            else
            {
                mytable.table[hash] = current -> next;
            }
            if (current -> next != nullptr)
            {
                current -> next -> prev = current -> prev;
            }
            delete current;
            return true;
        }
        current = current -> next;
    }
    return false;
}

bool RemoveByValue (HashTable& mytable, string elem)
{
    for (int i = 0; i < HashArraySize; i++)
    {
        Node* current = mytable.table[i];
        while (current != nullptr)
        {
            if (current -> value == elem)
            {
                if (current -> prev != nullptr)
                {
                    current -> prev -> next = current -> next;
                }
                else
                {
                    mytable.table[i] = current -> next;
                }
                if (current -> next != nullptr)
                {
                    current -> next -> prev = current -> prev;
                }
                delete current;
                return true;
            }
            current = current -> next;
        }
    }
    return false;
}

Node* Get(HashTable& mytable, string key)
{
    int hash = GetHash(key);
    Node* current = mytable.table[hash];
    while (current != nullptr)
    {
        if (current -> key == key)
        {
            return current;
        }
        current = current -> next;
    }
    return nullptr;
}

void Print(HashTable& mytable)
{
    for (int i = 0; i < HashArraySize; i++)
    {
        Node* current = mytable.table[i];
        while (current != nullptr)
        {
            cout << "[" << current -> key << " : " << current -> value << "]" << endl;
            current = current -> next;
        }
    }
    cout << endl;
}

string Surnames[] = {
    "Lawson", "Romero", "Henry", "Edwards", "Myers", 
    "Goodwin", "Ortiz", "Fields", "Colins", "Hernandez",
    "Jones", "Adams", "Gonzales", "Mullins", "Anderson",
    "Nyte", "Brewer", "Brown", "Wright", "White",
    "Murray", "Schtirlietz", "Lynch", "Webb", "Smith",
    "Munoz", "Morales", "Berry", "Lambert", "Thompson"
};

string Names[] = {
    "Kevin", "Nathan", "Thomas", "Stephen", "William",
    "James", "David", "Gregory", "Philipp", "John",
    "Billy", "Christopher", "Robert", "Roy", "Max",
    "Richard", "Raymond", "Michael", "Andrew", "Travis",
    "Daniel", "Don", "Joseph", "Duane", "Juan",
    "Howard", "Felix", "Jerry", "Brian", "Leslie"
};

string SecNames[] = {
    "Kevin", "Nathan", "Thomas", "Stephen", "William",
    "James", "David", "Gregory", "Philipp", "John",
    "Billy", "Christopher", "Robert", "Roy", "Max",
    "Richard", "Raymond", "Michael", "Andrew", "Travis",
    "Daniel", "Don", "Joseph", "Duane", "Juan",
    "Howard", "Felix", "Jerry", "Brian", "Leslie"
};

string GenerateFullName()
{
    string surname = Surnames[rand() % 30];
    string name = Names[rand() % 30];
    string secname;
    do
    {
        secname = SecNames[rand() % 30];
    } while (name == secname);
    return name + " " + secname + " " + surname;
}

string CorrectString(int n, int length)
{
    string tempstring = to_string(n);
    while (tempstring.size() < length)
    {
        tempstring = '0' + tempstring;
    }
    while (tempstring.size() > length)
    {
        tempstring.erase(0, 1);
    }
    return tempstring;
}

string GenerateBirthDay()
{
    return CorrectString(rand() % 28 + 1, 2) + "." + CorrectString(rand() % 12 + 1, 2) + "." + to_string(rand() % 80 + 1930);
}

string GeneratePassportNum()
{
    return CorrectString(rand() % 10000, 4) + " " + CorrectString(rand() % 1000000 * 100, 6);
}

int main()
{
    srand(time(NULL));
    HashTable mytable;
    for (int i = 0; i < HashArraySize; i++)
    {
        string BirthDay = GenerateBirthDay();
        string NewHuman = GenerateFullName() + " | " + BirthDay + " | " + GeneratePassportNum();
        Add(mytable, BirthDay, NewHuman);
    }
    cout << "Hash-table creation successful: " << endl;
    Print(mytable);

    int ExistingInd = rand() % HashArraySize;
    while (mytable.table[ExistingInd] == nullptr)
    {
        ExistingInd = rand() % HashArraySize;
    }
    Node* RandomHuman = mytable.table[ExistingInd];
    string Key = RandomHuman -> key;
    cout << "Removing by key '" << Key << "': " << endl;
    if (RemoveByKey(mytable, Key))
    {
        cout << "Element successfully removed." << endl;
    }
    else
    {
        cout << "Removing error. Element not found: " << endl;
    }
    Print(mytable);

    ExistingInd = rand() % HashArraySize;
    while (mytable.table[ExistingInd] == nullptr)
    {
        ExistingInd = rand() % HashArraySize;
    }
    RandomHuman = mytable.table[ExistingInd];
    string Val = RandomHuman -> value;
    cout << "Removing by value '" << Val << "': " << endl;
    if (RemoveByValue(mytable, Val))
    {
        cout << "Element successfully removed." << endl;
    }
    else
    {
        cout << "Removing error. Element not found: " << endl;
    }
    Print(mytable);

    ExistingInd = rand() % HashArraySize;
    while (mytable.table[ExistingInd] == nullptr)
    {
        ExistingInd = rand() % HashArraySize;
    }
    RandomHuman = mytable.table[ExistingInd];
    string KeyToGet = RandomHuman -> key;
    cout << "Getting element by key '" << KeyToGet << "': "<< endl;
    Node* node = Get(mytable, KeyToGet);
    if (node != nullptr)
    {
        cout << "Got element " << node -> value << endl;
    }
    else
    {
        cout << "Getting error. Element not found" << endl;
    }
    cout << "Amount of collisions: " << CollisionCounter << endl;
    return 0;
}