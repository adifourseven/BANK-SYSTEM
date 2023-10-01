


#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <regex>  // Include regex library for password validation
using namespace std;

// Admin password
const string ADMIN_PASSWORD = "9881";

class Customer
{
public:
    int AccountNumber;
    string FirstName;
    string MiddleName;
    string LastName;
    string Address; // Change to string for address
    int DOB;
    int Balance;
    string Password; // Individual customer password

    Customer()
    {
        // Generate a random account number
        srand(static_cast<unsigned int>(std::time(nullptr)));
        AccountNumber = rand();
        Balance = 0;
    }

    // Function to format and set the name
    void SetName(const string& firstName, const string& middleName, const string& lastName)
    {
        FirstName = firstName;
        MiddleName = middleName;
        LastName = lastName;
    }
};

class BANKOFINDIA
{
private:
    vector<Customer> customers;  // Store customer information
    int TotalMoneyInBank;       // Total money in the bank
    bool isAdminLoggedIn;       // Flag to track admin login status
    bool isCustomerLoggedIn;    // Flag to track customer login status
    int loggedInCustomerIndex;  // Index of the logged-in customer

public:
    BANKOFINDIA()
    {
        TotalMoneyInBank = 0;
        isAdminLoggedIn = false;
        isCustomerLoggedIn = false;
    }

    // Function to display a welcome message
    void DisplayWelcomeMessage()
    {
        cout << "Welcome to Aditya Co-Operative Bank!" << endl;
        cout << "Thank you for using our services." << endl;
    }

    void CreateAccount()
    {
        Customer customer;

        // Prompt the user for input
        cout << "Enter your first name: ";
        string firstName;
        cin >> firstName;

        cout << "Enter your middle name: ";
        string middleName;
        cin >> middleName;

        cout << "Enter your last name: ";
        string lastName;
        cin >> lastName;

        // Format and set the name
        customer.SetName(firstName, middleName, lastName);

        // Prompt for and validate date of birth (DOB)
        cout << "Enter your date of birth (YYYYMMDD): ";
        if (!(cin >> customer.DOB) || customer.DOB < 19000101 || customer.DOB > 21001231)
        {
            cout << "Invalid date of birth. Please enter a valid date (YYYYMMDD)." << endl;
            return;
        }

        // Set individual customer password and validate its strength
        while (true)
        {
            cout << "Set a strong password (at least 8 characters with special characters): ";
            cin >> customer.Password;

            if (IsPasswordStrong(customer.Password))
            {
                break;
            }
            else
            {
                cout << "Password is weak. Please use at least 8 characters with special characters." << endl;
            }
        }

        // Prompt for and set address
        cout << "Enter your address: ";
        cin.ignore();
        getline(cin, customer.Address);

        // Add the new customer to the bank
        customers.push_back(customer);

        // Output the account details
        cout << "Your account has been created successfully." << endl;
        cout << "Account Number: " << customer.AccountNumber << endl;
    }

    // Function to check password strength
    bool IsPasswordStrong(const string& password)
    {
        // Use a regular expression to validate the password
        regex passwordPattern("^(?=.*[A-Za-z])(?=.*[@#$%^&+=])(?=\\S+$).{8,}$");
        return regex_match(password, passwordPattern);
    }

    bool Authenticate(int accountNumber, const string& password)
    {
        for (int i = 0; i < customers.size(); ++i)
        {
            if (customers[i].AccountNumber == accountNumber && customers[i].Password == password)
            {
                isCustomerLoggedIn = true;
                loggedInCustomerIndex = i;
                return true;
            }
        }
        return false;
    }

    void AddMoney(int amountToAdd)
    {
        if (isCustomerLoggedIn)
        {
            customers[loggedInCustomerIndex].Balance += amountToAdd;
            TotalMoneyInBank += amountToAdd; // Update the total money in the bank
            cout << "Money added successfully. New balance: " << customers[loggedInCustomerIndex].Balance << endl;
        }
        else
        {
            cout << "Customer not logged in. Money not added." << endl;
        }
    }

    void WithdrawMoney(int amountToWithdraw)
    {
        if (isCustomerLoggedIn)
        {
            if (customers[loggedInCustomerIndex].Balance >= amountToWithdraw)
            {
                customers[loggedInCustomerIndex].Balance -= amountToWithdraw;
                TotalMoneyInBank -= amountToWithdraw; // Update the total money in the bank
                cout << "Money withdrawn successfully. New balance: " << customers[loggedInCustomerIndex].Balance << endl;
            }
            else
            {
                cout << "Insufficient balance. Money not withdrawn." << endl;
            }
        }
        else
        {
            cout << "Customer not logged in. Money not withdrawn." << endl;
        }
    }

    void CheckBalance()
    {
        if (isCustomerLoggedIn)
        {
            cout << "Account Number: " << customers[loggedInCustomerIndex].AccountNumber << endl;
            cout << "Name: " << customers[loggedInCustomerIndex].FirstName << " " << customers[loggedInCustomerIndex].MiddleName << " " << customers[loggedInCustomerIndex].LastName << endl;
            cout << "Address: " << customers[loggedInCustomerIndex].Address << endl;
            cout << "Date of Birth: " << customers[loggedInCustomerIndex].DOB << endl;
            cout << "Balance: " << customers[loggedInCustomerIndex].Balance << endl;
        }
        else
        {
            cout << "Customer not logged in. Cannot check balance." << endl;
        }
    }

    void TransferMoney(int receiverAccountNumber, int amountToTransfer)
    {
        if (isCustomerLoggedIn)
        {
            if (customers[loggedInCustomerIndex].Balance >= amountToTransfer)
            {
                for (int i = 0; i < customers.size(); ++i)
                {
                    if (customers[i].AccountNumber == receiverAccountNumber)
                    {
                        customers[loggedInCustomerIndex].Balance -= amountToTransfer;
                        customers[i].Balance += amountToTransfer;
                        TotalMoneyInBank += amountToTransfer; // Update the total money in the bank
                        cout << "Money transferred successfully. New balance: " << customers[loggedInCustomerIndex].Balance << endl;
                        return;
                    }
                }
                cout << "Receiver account not found." << endl;
            }
            else
            {
                cout << "Insufficient balance for transfer. Money not transferred." << endl;
            }
        }
        else
        {
            cout << "Customer not logged in. Money not transferred." << endl;
        }
    }

    void ShowAllCustomerInfo(const string& adminPassword)
    {
        if (adminPassword != ADMIN_PASSWORD)
        {
            cout << "Admin password is incorrect. Access denied." << endl;
            return;
        }

        cout << "Customer Information:" << endl;
        for (const Customer& customer : customers)
        {
            cout << "Account Number: " << customer.AccountNumber << endl;
            cout << "Name: " << customer.FirstName << " " << customer.MiddleName << " " << customer.LastName << endl;
            cout << "Address: " << customer.Address << endl;
            cout << "Date of Birth: " << customer.DOB << endl;
            cout << "Balance: " << customer.Balance << endl << endl;
        }
    }

    void CheckTotalMoneyInBank(const string& adminPassword)
    {
        if (adminPassword != ADMIN_PASSWORD)
        {
            cout << "Admin password is incorrect. Access denied." << endl;
            return;
        }

        cout << "Total Money in Bank: " << TotalMoneyInBank << endl;
    }

    void Start()
    {
        while (true)
        {
            int choice;
            cout << "\nAre you an admin or a customer?\n";
            cout << "1. Admin\n";
            cout << "2. Customer\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                AdminMenu();
                break;
            case 2:
                CustomerMenu();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    void AdminMenu()
    {
        cout << "Enter admin password: ";
        string adminPassword;
        cin >> adminPassword;

        if (adminPassword == ADMIN_PASSWORD)
        {
            isAdminLoggedIn = true;

            while (isAdminLoggedIn)
            {
                int adminChoice;
                cout << "\nAdmin Menu:\n";
                cout << "1. Show All Customer Info\n";
                cout << "2. Check Total Money in Bank\n";
                cout << "3. Logout\n";
                cout << "Enter your choice: ";
                cin >> adminChoice;

                switch (adminChoice)
                {
                case 1:
                    ShowAllCustomerInfo(adminPassword);
                    break;
                case 2:
                    CheckTotalMoneyInBank(adminPassword);
                    break;
                case 3:
                    isAdminLoggedIn = false;
                    cout << "Admin logged out." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else
        {
            cout << "Admin password is incorrect. Access denied." << endl;
        }
    }

    void CustomerMenu()
    {
        int customerChoice;

        while (true)
        {
            cout << "\nCustomer Menu:\n";
            cout << "1. Login as Existing Customer\n";
            cout << "2. Create a New Account\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> customerChoice;

            switch (customerChoice)
            {
            case 1:
                CustomerLogin();
                break;
            case 2:
                CreateAccount();
                break;
            case 3:
                isCustomerLoggedIn = false;
                cout << "Customer logged out." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    void CustomerLogin()
    {
        int accountNumber;
        string password;

        cout << "Enter your account number: ";
        cin >> accountNumber;

        cout << "Enter your password: ";
        cin >> password;

        if (Authenticate(accountNumber, password))
        {
            cout << "Customer logged in." << endl;

            while (isCustomerLoggedIn)
            {
                int customerChoice;
                cout << "\nCustomer Options:\n";
                cout << "1. Check Balance\n";
                cout << "2. Add Money\n";
                cout << "3. Withdraw Money\n";
                cout << "4. Transfer Money\n";
                cout << "5. Logout\n";
                cout << "Enter your choice: ";
                cin >> customerChoice;

                switch (customerChoice)
                {
                case 1:
                    CheckBalance();
                    break;
                case 2:
                    int amountToAdd;
                    cout << "Enter amount to add: ";
                    cin >> amountToAdd;
                    AddMoney(amountToAdd);
                    break;
                case 3:
                    int amountToWithdraw;
                    cout << "Enter amount to withdraw: ";
                    cin >> amountToWithdraw;
                    WithdrawMoney(amountToWithdraw);
                    break;
                case 4:
                    int receiverAccountNumber, amountToTransfer;
                    cout << "Enter receiver's account number: ";
                    cin >> receiverAccountNumber;
                    cout << "Enter amount to transfer: ";
                    cin >> amountToTransfer;
                    TransferMoney(receiverAccountNumber, amountToTransfer);
                    break;
                case 5:
                    isCustomerLoggedIn = false;
                    cout << "Customer logged out." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else
        {
            cout << "Invalid account number or password. Login failed." << endl;
        }
    }
};

int main()
{
    BANKOFINDIA bank;

    // Display a welcome message
    bank.DisplayWelcomeMessage();

    // Start the banking application
    bank.Start();

    return 0;
}
