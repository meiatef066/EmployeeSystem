#include <bits/stdc++.h>
using namespace std;
class Employee
{
private:
    string name;
    string date_of_joining;
    string status;
    int id, salary;

public:
    Employee(string name = "", int id = 0, int salary = 0, string date_of_joining = "", string status = "working")
        : name(name), id(id), salary(salary), date_of_joining(date_of_joining), status(status) {}

    // Getter methods
    string getName() const
    {
        return name;
    }
    int getId() const
    {
        return id;
    }
    int getSalary() const
    {
        return salary;
    }
    string getDateOfJoining() const
    {
        return date_of_joining;
    }
    string getStatus() const
    {
        return status;
    }

    // Setter methods
    void setName(string name)
    {
        this->name = name;
    }
    void setId(int id)
    {
        this->id = id;
    }
    void setSalary(int salary)
    {
        this->salary = salary;
    }
    void setDateOfJoining(string date_of_joining)
    {
        this->date_of_joining = date_of_joining;
    }
    void setStatus(string status)
    {
        this->status = status;
    }
};
struct node
{
    Employee emp;
    node *next;
    node(Employee emp) : emp(emp), next(NULL){};
};
class EmployeeLinkedList
{
private:
    node *head, *tail;

public:
    node *headNotWorking, *tailNotWorking;
    EmployeeLinkedList() : head(nullptr), tail(nullptr), headNotWorking(nullptr), tailNotWorking(nullptr) {}

    // add
    void addEmployee(Employee e)
    {
        node *newnode = new node(e);
        if (head == NULL)
        {
            head = tail = newnode;
        }
        else
        {
            tail->next = newnode;
            tail = newnode;
        }
    }
    void generateReport(string sort_by = "")
    {
        // Convert linked list to vector for easy sorting
        vector<Employee> employees;
        node *current = head;
        while (current)
        {
            employees.push_back(current->emp);
            current = current->next;
        }

        // Sort the vector based on sort_by criteria
        if (sort_by == "name")
        {
            sort(employees.begin(), employees.end(), [](const Employee &a, const Employee &b)
                 { return a.getName() < b.getName(); });
        }
        else if (sort_by == "id")
        {
            sort(employees.begin(), employees.end(), [](const Employee &a, const Employee &b)
                 { return a.getId() < b.getId(); });
        }
        else if (sort_by == "salary")
        {
            sort(employees.begin(), employees.end(), [](const Employee &a, const Employee &b)
                 { return a.getSalary() < b.getSalary(); });
        }
        else if (sort_by == "date")
        {
            sort(employees.begin(), employees.end(), [](const Employee &a, const Employee &b)
                 { return a.getDateOfJoining() < b.getDateOfJoining(); });
        }

        cout << "Report sorted by " << sort_by << ":" << endl;
        displayArray(employees);
    }
    void displayArray(const vector<Employee> &v)
    {
        for (const Employee &emp : v)
        {
            cout << "Name: " << emp.getName() << endl;
            cout << "ID: " << emp.getId() << endl;
            cout << "Salary: " << emp.getSalary() << endl;
            cout << "Date of Joining: " << emp.getDateOfJoining() << endl;
            cout << "Status: " << emp.getStatus() << endl;
            cout << endl;
        }
    }
    void displayAllEmployee(node *h = NULL)
    {
        node *temp = NULL;
        if (h == NULL)
        {
            temp = head;
            cout << "Working :\n";
            while (temp != NULL)
            {
                cout << "Name: " << temp->emp.getName() << ", ID: " << temp->emp.getId()
                     << ", Salary: " << temp->emp.getSalary() << ", Date of Joining: " << temp->emp.getDateOfJoining()
                     << ", Status: " << temp->emp.getStatus() << endl;
                temp = temp->next;
            }
        }
        else if (headNotWorking != NULL)
        {
            temp = headNotWorking;
            cout << "Not Working (Fierd) :\n";
            while (temp != NULL)
            {
                cout << "Name: " << temp->emp.getName() << ", ID: " << temp->emp.getId()
                     << ", Salary: " << temp->emp.getSalary() << ", Date of Joining: " << temp->emp.getDateOfJoining()
                     << ", Status: " << temp->emp.getStatus() << endl;
                temp = temp->next;
            }
        }
    }
    Employee *Search(string serchItem, string search_by = "name")
    {
        node *temp = head;
        while (temp != NULL)
        {
            if (search_by == "id" && temp->emp.getId() == stoi(serchItem))
            {
                return &temp->emp;
            }
            else if (temp->emp.getName() == serchItem)
            {
                return &temp->emp;
            }
            temp = temp->next;
        }
        return NULL;
    }
    bool updateById(Employee newData, string findBy = "id")
    {
        Employee *emp = Search(to_string(newData.getId()), findBy);
        if (emp)
        {
            if (newData.getSalary() != 0)
                emp->setSalary(newData.getSalary());
            if (newData.getName() != "")
                emp->setName(newData.getName());
            if (newData.getDateOfJoining() != "")
                emp->setDateOfJoining(newData.getDateOfJoining());
            if (newData.getStatus() != "working")
                emp->setStatus(newData.getStatus());
            return true;
        }
        return false;
    }
    bool deleteEmployee(int id)
    {
        node *current = head;
        node *prev = nullptr;
        while (current && current->emp.getId() != id)
        {
            prev = current;
            current = current->next;
        }
        if (current->emp.getId() == id)
        {
            if (current->next == NULL)
            {
                prev->next = NULL;
            }
            else
            {
                prev->next = current->next;
            }
            // add to not working list
            {
                current->emp.setStatus("notWorking");
                if (headNotWorking == NULL)
                {
                    headNotWorking = tailNotWorking = current;
                }
                else
                {
                    tailNotWorking->next = current;
                    tailNotWorking = current;
                }
            }
            return true;
        }
        return false;
    }
    vector<Employee> getEmployeesInSalaryRange(int min_salary, int max_salary)
    {
        vector<Employee> result;
        node *current = head;
        while (current)
        {
            if (current->emp.getSalary() >= min_salary && current->emp.getSalary() <= max_salary)
            {
                result.push_back(current->emp);
            }
            current = current->next;
        }
        return result;
    }
};
void Administrator();
void Guest();
void menu();
EmployeeLinkedList employee_list;
int main()
{
    menu();
    return 0;
}
void menu()
{
    cout << "***********************************************\n";
    cout << "                Welcome to our System          \n";
    cout << "***********************************************\n";
    cout << "Login as :                        \n";
    cout << "1) Administrator Mode \n";
    cout << "2) Guest Mode \n";
    cout << "3) close system \n";
    cout << "Enter your choice : ";
    int n;
    cin >> n;
    switch (n)
    {
    case 1:
        Administrator();
        break;
    case 2:
        Guest();
        break;
    case 3:
        exit(0);
    default:
        cout << "Error Please enter exist choice\n";
    }
    cout << "\n";
}
void Administrator()
{
    while (true)
    {
        cout << "\nAdministrator Menu:\n";
        cout << "1. Add New Employee\n";
        cout << "2. Update Employee Details\n";
        cout << "3. Delete Employee\n";
        cout << "4. Search Employee\n";
        cout << "5. Display All Employees\n";
        cout << "6. Generate Report\n";
        cout << "7. Exit\n";
        int choice;
        cout << "Please Enter your choice :";
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {
            // add emp name , id, sal,date,satus
            string name, date_of_joining;
            int employee_id;
            double salary;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Employee ID: ";
            cin >> employee_id;
            cout << "Enter Salary: ";
            cin >> salary;
            cout << "Enter Date of Joining: ";
            cin >> date_of_joining;
            Employee e(name, employee_id, salary, date_of_joining);
            employee_list.addEmployee(e);
        }
        else if (choice == 2)
        {
            // update
            int employee_id;
            string new_name, new_date_of_joining;
            int new_salary;
            cout << "Enter Employee Id : ";
            cin >> employee_id;
            cout << "Enter New Name (leave empty to keep current): ";
            cin.ignore();
            getline(cin, new_name);
            cout << "Enter New Salary (0 to keep current): ";
            cin >> new_salary;
            cout << "Enter New Date of Joining (leave empty to keep current): ";
            cin.ignore();
            getline(cin, new_date_of_joining);

            Employee e(new_name, employee_id, new_salary, new_date_of_joining);
            employee_list.updateById(e);
        }
        else if (choice == 3)
        {
            // delete
            int id;
            cout << "Enter employee id you want to delete : ";
            cin >> id;
            employee_list.deleteEmployee(id);
        }
        else if (choice == 4)
        {
            // Search by name , id
            string search_term, by;
            cout << "Enter Name or Employee ID to search: ";
            cin >> search_term;
            cout << "Search by (name/employee_id): ";
            cin >> by;
            Employee *emp = employee_list.Search(search_term, by);
            if (emp != NULL)
            {
                cout << "Name: " << emp->getName() << ", ID: " << emp->getId() << ", Salary: " << emp->getSalary()
                     << ", Date of Joining: " << emp->getDateOfJoining() << ", Status: " << emp->getStatus() << endl;
            }
            else
            {
                cout << "Employee not found.\n";
            }
        }
        else if (choice == 5)
        {
            // display all emp working , not working  // size of them
            employee_list.displayAllEmployee();
            //  employee_list.displayAllEmployee(employee_list.headNotWorking);
        }
        else if (choice == 6)
        {
            // generate report // sort by id,name,salary, date|| range of salary => size of them
            string sort_by;
            cout << "Sort by (name/employee_id/salary/date_of_joining): ";
            cin >> sort_by;
            employee_list.generateReport(sort_by);
        }
        else if (choice == 7)
        {
            menu();
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
void Guest()
{
    while (true)
    {
        cout << "\nGuest Menu:\n";
        cout << "1. Search Employee\n";
        cout << "2. Generate Report\n";
        cout << "3. Generate Report of employee with range salary (min , max)\n";
        cout << "4. Exit\n";
        int choice;
        cout << "Please Enter your choice :";
        cin >> choice;
        cout << endl;
        if (choice == 1)
        {
            // search => working || non working
            string search_term, by;
            cout << "Enter Name or Employee ID to search: ";
            cin >> search_term;
            cout << "Search by (name/employee_id): ";
            cin >> by;
            Employee *emp = employee_list.Search(search_term, by);
            if (emp)
            {
                cout << "Name: " << emp->getName() << ", ID: " << emp->getId() << ", Salary: " << emp->getSalary()
                     << ", Date of Joining: " << emp->getDateOfJoining() << ", Status: " << emp->getStatus() << endl;
            }
            else
            {
                cout << "Employee not found.\n";
            }
        }
        else if (choice == 2)
        {
            // generate report  sort by name or id
            string sort_by;
            cout << "Sort by (name/id/salary/date_of_joining): ";
            cin >> sort_by;
            employee_list.generateReport(sort_by);
        }
        else if (choice == 3)
        {
            int mn, mx;
            cout << "enter min salary : ";
            cin >> mn;
            cout << "enter max salary : ";
            cin >> mx;
            employee_list.displayArray(employee_list.getEmployeesInSalaryRange(mn, mx));
        }
        else if (choice == 4)
        {
            menu();
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
