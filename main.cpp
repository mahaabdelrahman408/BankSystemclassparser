//Phase.1&2
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>


using namespace std;

class Person
{
private:
    int id;
    string name;
    string password;
    bool isAliphatic(string s)
    {
        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if (!isalpha(c))
            {
                return false;
            }
        }
        return true;
    }
public:
    void setId(int i)
    {
        id=i;
    }
    void setName(string n)
    {
        if(n.size()>=5 && n.size()<=20 && isAliphatic(n) )
        {

            name=n;
        }
        else
        {
            cout<<"The name must be alphabetic and size between 5 and 20 "<<endl;
            cout<<"Try again to enter the name : ";
            cin>>n;
            setName(n);
            return;
        }
    }
    void setPassword(std::string newPassword)
    {
        if (newPassword.size() >= 8 && newPassword.size() <= 20)
        {
            password = std::move(newPassword);
        }
        else
        {
            cin >> password;
            cout << "Password must be between 8 and 20 characters.\n";
            cout << "Please try again: ";
            setPassword(password);
        }
    }
    int getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }
    std::string getPassword() const
    {
        return password;
    }
};


class Client:public Person
{
private:
    double balance;
public:
    void setBalance(double b)
    {
        if(b>=1500)
        {
            balance=b;
        }
        else
        {
            cout<<"The minimum balance must be 1500 "<<endl;
            return;
        }
    }
    double getBalance()
    {
        return balance;
    }
    void deposit(double amount)
    {
        if(amount>0)
        {
            balance+=amount;
            cout<<"The client balance after deposit "<<amount<<" = "<<balance<<endl;
        }
        else
        {
            cout<<"Deposit’s amount should be positive (Invalid amount).";
        }
    }
    void withdraw(double amount)
    {
        if(amount>0 && amount<=balance)
        {
            balance-=amount;
            cout<<"The client balance after withdraw "<<amount<<" = "<<balance<<endl;
        }
        else
        {
            cout<<"Invalid withdraw’s amount "<<endl;
        }
    }
    void transferTo(double amount, Client& recipient)
    {
        if(amount>0 && amount<=balance)
        {
            recipient.balance+=amount;
            cout<<"The balance that recipient received = "<<recipient.balance<<endl;
            balance-=amount;
            cout<<"The remain balance of the client = "<<balance<<endl;
        }
        else
        {
            cout<<"Invalid transfer amount "<<endl;
        }
    }
    void checkBalance()
    {
        cout<<"Your current balance : "<<balance<<endl;
    }
    void display()
    {
        cout << "Client Information:" << endl;
        cout <<"Name : "<<getName() << endl;
        cout <<"ID : "<< getId() << endl;
        cout <<"Balance : "<<getBalance() << endl;
        cout<<"Password : "<<getPassword()<<endl;
    }
};


class Employee:public Person
{
private:
    double salary;
public:
    void setSalary(double s)
    {
        if(s<5000)
        {
            cout<<"Salary must be at least 5000 "<<endl;
            cout<<"Try again to enter your salary : ";
            cin>>s;
            setSalary(s);
        }
        else
        {
            salary=s;
        }
    }
    double getSalary()
    {
        return salary;
    }
    void display()
    {
        cout << "Employee Information:" << endl;
        cout << "Name: " << getName() << endl;
        cout << "ID: " << getId() << endl;
        cout << "Password: " << getPassword() <<endl;
        cout << "Salary: " << getSalary() << endl;
    }
};


class Admin:public Employee
{
public:
    void display()
    {
        cout<<"Admin Information : "<<endl;
        cout <<"Name : "<<getName()<< endl;
        cout <<"ID : "<< getId() << endl;
        cout <<"Password : "<<getPassword()<< endl;
        cout<<"Salary : "<<getSalary()<<endl;
    }
};
class parser
{
private:
    static vector<string> split(string line)
    {
        stringstream stream(line);
        string token;
        vector<string> info;
        while(getline(stream,token,'&'))
            info.push_back(token);
        return info;
    }
public:
    static Client parseTOclient(string line)
    {
        vector<string> info = split(line);
        Client client;
        client.setId(stoi(info[0]));
        client.setName(info[1]);
        client.setPassword(info[2]);
        client.setBalance(stod(info[3]));
        return client;
    }
    static Employee parseToEmployee(string line)
    {
        vector<string> info = split(line);
        Employee employee;
        employee.setId(stoi(info[0]));
        employee.setName(info[1]);
        employee.setPassword(info[2]);
        employee.setSalary(stod(info[3]));
        return employee;
    }
    static Admin parseToAdmin(string line)
    {
        vector<string> info = split(line);
        Admin admin;
        admin.setId(stoi(info[0]));
        admin.setName(info[1]);
        admin.setPassword(info[2]);
        admin.setSalary(stod(info[3]));
        return admin;
    }
};

class FileManager {
private:
    const string clientsFilePath = "clients.txt";
    const string employeesFilePath = "employees.txt";
    const string adminsFilePath = "admins.txt";

    void writeToFile(const string& filePath, const string& data);
    std::vector<std::string> readFromFile(const string& filePath);

public:
    void addClient(const Client& client);
    void addEmployee(const Employee& employee);
    void addAdmin(const Admin& admin);

    std::vector<Client> getAllClients();
    std::vector<Employee> getAllEmployees();
    std::vector<Admin> getAllAdmins();

    void removeAllClients();
    void removeAllEmployees();
    void removeAllAdmins();
};

void FileManager::addClient(const Client& client) {
    string clientData = client.getName() + "," + to_string(client.getId()) + "," + client.getPassward() + "," + to_string(client.getBalance());
    writeToFile(clientsFilePath, clientData);
}

void FileManager::writeToFile(const string& filePath, const string& data) {
    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << data << endl;
        file.close();
    } else {
        cerr << "Not found this file" << filePath << endl;
    }
}

std::vector<std::string> FileManager::readFromFile(const string& filePath) {
    std::vector<std::string> data;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            data.push_back(line);
        }
        file.close();
    } else {
        cerr << "Error opening file: " << filePath << endl;
    }
    return data;
}

    void writeToFile(const string& filePath, const string& data);
    std::vector<std::string> readFromFile(const string& filePath);

public:
    void addClient(const Client& client);
    void addEmployee(const Employee& employee);
    void addAdmin(const Admin& admin);

    std::vector<Client> getAllClients();
    std::vector<Employee> getAllEmployees();
    std::vector<Admin> getAllAdmins();

    void removeAllClients();
    void removeAllEmployees();
    void removeAllAdmins();
};

void FileManager::addClient(const Client& client) {
    string clientData = client.getName() + "," + to_string(client.getId()) + "," + client.getPassward() + "," + to_string(client.getBalance());
    writeToFile(clientsFilePath, clientData);
}

void FileManager::writeToFile(const string& filePath, const string& data) {
    ofstream file(filePath, ios::app);
    if (file.is_open()) {
        file << data << endl;
        file.close();
    } else {
        cerr << "Not found this file" << filePath << endl;
    }
}

std::vector<std::string> FileManager::readFromFile(const string& filePath) {
    std::vector<std::string> data;
    ifstream file(filePath);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            data.push_back(line);
        }
        file.close();
    } else {
        cerr << "Error opening file: " << filePath << endl;
    }
    return data;
}



int main()
{
    Client c;
    Client ob;
    c.setName("Ali");
    c.setId(305051952005);
    c.setPassword("123456789");
    c.setBalance(2300);
    cout<<"Your balance before any thing = "<<c.getBalance()<<endl;
    c.deposit(500);
    c.withdraw(200);
    c.transferTo(100,ob);
    c.checkBalance();
    c.display();

    Employee f;
    f.setName("John");
    f.setId(1001);
    f.setPassword("password123");
    f.setSalary(9000);
    f.display();

    Admin a;
    a.setId(1234566879);
    a.setName("Ahmad");
    a.setPassword("14567859");
    a.setSalary(70000);
    a.display();

     FileManager fileManager;
Client client;
fileManager.addClient(client);

    return 0;
}
