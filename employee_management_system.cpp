#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Employee structure
struct Employee
{
	int id;
	string name;
	string department;
	double salary;
	Employee *next;

	// Constructor
	Employee(int empId, string empName, string empDept, double empSalary)
	{
		id = empId;
		name = empName;
		department = empDept;
		salary = empSalary;
		next = nullptr;
	}
};

// Employee Management System Class
class EmployeeManagementSystem
{
private:
	Employee *head;
	int employeeCount;

public:
	// Constructor
	EmployeeManagementSystem()
	{
		head = nullptr;
		employeeCount = 0;
	}

	// Destructor to free memory
	~EmployeeManagementSystem()
	{
		clearList();
	}

	// Add new employee
	void addEmployee(int id, string name, string department, double salary)
	{
		// Check if ID already exists
		if (findEmployee(id) != nullptr)
		{
			cout << "Error: Employee ID " << id << " already exists!\n";
			return;
		}

		Employee *newEmployee = new Employee(id, name, department, salary);

		if (head == nullptr)
		{
			head = newEmployee;
		}
		else
		{
			Employee *temp = head;
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = newEmployee;
		}
		employeeCount++;
		cout << "Employee added successfully!\n";
	}

	// Display all employees
	void displayEmployees()
	{
		if (head == nullptr)
		{
			cout << "No employees in the system.\n";
			return;
		}

		cout << "\n"
			 << string(80, '-') << "\n";
		cout << left << setw(10) << "ID" << setw(20) << "Name"
			 << setw(20) << "Department" << setw(15) << "Salary" << "\n";
		cout << string(80, '-') << "\n";

		Employee *temp = head;
		while (temp != nullptr)
		{
			cout << left << setw(10) << temp->id
				 << setw(20) << temp->name
				 << setw(20) << temp->department
				 << setw(15) << fixed << setprecision(2) << temp->salary << "\n";
			temp = temp->next;
		}
		cout << string(80, '-') << "\n";
		cout << "Total employees: " << employeeCount << "\n";
	}

	// Find employee by ID
	Employee *findEmployee(int id)
	{
		Employee *temp = head;
		while (temp != nullptr)
		{
			if (temp->id == id)
			{
				return temp;
			}
			temp = temp->next;
		}
		return nullptr;
	}

	// Search employee by ID
	void searchEmployee(int id)
	{
		Employee *emp = findEmployee(id);
		if (emp != nullptr)
		{
			cout << "\nEmployee Found:\n";
			cout << "ID: " << emp->id << "\n";
			cout << "Name: " << emp->name << "\n";
			cout << "Department: " << emp->department << "\n";
			cout << "Salary: $" << fixed << setprecision(2) << emp->salary << "\n";
		}
		else
		{
			cout << "Employee with ID " << id << " not found.\n";
		}
	}

	// Update employee information
	void updateEmployee(int id)
	{
		Employee *emp = findEmployee(id);
		if (emp == nullptr)
		{
			cout << "Employee with ID " << id << " not found.\n";
			return;
		}

		cout << "Current Information:\n";
		cout << "Name: " << emp->name << "\n";
		cout << "Department: " << emp->department << "\n";
		cout << "Salary: $" << emp->salary << "\n";

		cout << "\nEnter new information (leave blank to keep current):\n";

		cin.ignore(); // Clear input buffer
		string newName, newDept;
		double newSalary;

		cout << "Enter new name: ";
		getline(cin, newName);
		if (!newName.empty())
		{
			emp->name = newName;
		}

		cout << "Enter new department: ";
		getline(cin, newDept);
		if (!newDept.empty())
		{
			emp->department = newDept;
		}

		cout << "Enter new salary (0 to keep current): ";
		cin >> newSalary;
		if (newSalary > 0)
		{
			emp->salary = newSalary;
		}

		cout << "Employee information updated successfully!\n";
	}

	// Delete employee by ID
	void deleteEmployee(int id)
	{
		if (head == nullptr)
		{
			cout << "No employees in the system.\n";
			return;
		}

		// If head node itself holds the key to be deleted
		if (head->id == id)
		{
			Employee *temp = head;
			head = head->next;
			delete temp;
			employeeCount--;
			cout << "Employee deleted successfully!\n";
			return;
		}

		// Search for the employee to be deleted
		Employee *current = head;
		Employee *prev = nullptr;

		while (current != nullptr && current->id != id)
		{
			prev = current;
			current = current->next;
		}

		// If employee was not found
		if (current == nullptr)
		{
			cout << "Employee with ID " << id << " not found.\n";
			return;
		}

		// Unlink the node from linked list
		prev->next = current->next;
		delete current;
		employeeCount--;
		cout << "Employee deleted successfully!\n";
	}

	// Display employees by department
	void displayByDepartment(string department)
	{
		if (head == nullptr)
		{
			cout << "No employees in the system.\n";
			return;
		}

		cout << "\nEmployees in " << department << " department:\n";
		cout << string(60, '-') << "\n";
		cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Salary" << "\n";
		cout << string(60, '-') << "\n";

		Employee *temp = head;
		bool found = false;
		while (temp != nullptr)
		{
			if (temp->department == department)
			{
				cout << left << setw(10) << temp->id
					 << setw(20) << temp->name
					 << setw(15) << fixed << setprecision(2) << temp->salary << "\n";
				found = true;
			}
			temp = temp->next;
		}

		if (!found)
		{
			cout << "No employees found in " << department << " department.\n";
		}
		cout << string(60, '-') << "\n";
	}

	// Calculate total salary expenditure
	void totalSalaryExpenditure()
	{
		if (head == nullptr)
		{
			cout << "No employees in the system.\n";
			return;
		}

		double total = 0;
		Employee *temp = head;
		while (temp != nullptr)
		{
			total += temp->salary;
			temp = temp->next;
		}

		cout << "Total salary expenditure: $" << fixed << setprecision(2) << total << "\n";
		cout << "Average salary: $" << fixed << setprecision(2) << (total / employeeCount) << "\n";
	}

	// Get employee count
	int getEmployeeCount()
	{
		return employeeCount;
	}

	// Clear all employees
	void clearList()
	{
		while (head != nullptr)
		{
			Employee *temp = head;
			head = head->next;
			delete temp;
		}
		employeeCount = 0;
	}

	// Display menu
	void displayMenu()
	{
		cout << "\n=== EMPLOYEE MANAGEMENT SYSTEM ===\n";
		cout << "1. Add Employee\n";
		cout << "2. Display All Employees\n";
		cout << "3. Search Employee\n";
		cout << "4. Update Employee\n";
		cout << "5. Delete Employee\n";
		cout << "6. Display by Department\n";
		cout << "7. Total Salary Expenditure\n";
		cout << "8. Employee Count\n";
		cout << "9. Clear All Data\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
	}
};

// Main function
int main()
{
	EmployeeManagementSystem ems;
	int choice, id;
	string name, department;
	double salary;

	cout << "Welcome to Employee Management System!\n";

	do
	{
		ems.displayMenu();
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "Enter Employee ID: ";
			cin >> id;
			cin.ignore();
			cout << "Enter Name: ";
			getline(cin, name);
			cout << "Enter Department: ";
			getline(cin, department);
			cout << "Enter Salary: ";
			cin >> salary;
			ems.addEmployee(id, name, department, salary);
			break;

		case 2:
			ems.displayEmployees();
			break;

		case 3:
			cout << "Enter Employee ID to search: ";
			cin >> id;
			ems.searchEmployee(id);
			break;

		case 4:
			cout << "Enter Employee ID to update: ";
			cin >> id;
			ems.updateEmployee(id);
			break;

		case 5:
			cout << "Enter Employee ID to delete: ";
			cin >> id;
			ems.deleteEmployee(id);
			break;

		case 6:
			cin.ignore();
			cout << "Enter Department: ";
			getline(cin, department);
			ems.displayByDepartment(department);
			break;

		case 7:
			ems.totalSalaryExpenditure();
			break;

		case 8:
			cout << "Total employees: " << ems.getEmployeeCount() << "\n";
			break;

		case 9:
			ems.clearList();
			cout << "All employee data cleared!\n";
			break;

		case 0:
			cout << "Thank you for using Employee Management System!\n";
			break;

		default:
			cout << "Invalid choice! Please try again.\n";
		}
	} while (choice != 0);

	return 0;
}