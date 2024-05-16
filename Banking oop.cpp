#include <vector>
#include<algorithm>
#include<iostream>
using namespace std;

class account_query
{

public:
    string account_number;
    string firstName;
    string lastName;
    string credit_card;
    string phone_number;
    int pin;
    float total_Balance;
    void read_data(); //responsible for collecting information from the user to create a new account
    void show_data(account_query temp); //designed to display the details of an account.
    void read_rec(); //designed to read and display records from the vec vector
    virtual void deposit()
    {

    }
    virtual void withdraw()
    {

    }
    //Virtual functions, to be overridden by derived classes.

};
vector <account_query> vec;
//vector named vec that can store objects of the account_query (base) class. It is used to store and manage multiple account records.

class bills : public account_query
{
public:
    int n; //record number
    int b = rand(); //Initializes b with a random number using the rand() function.
    int sumOfBills = 0;
    vector <int> BillsInAccount; //A vector named BillsInAccount of integers to store bills.

    void withdraw() //Overrides the withdraw() function from the base class account_query.
    {
        vec[n - 1].total_Balance -= sumOfBills;  //It subtracts sumOfBills from the total balance of the account 
    }

    //a function to generate rand no of bill max from (0 to 14) 15 bills, and each one of value from 1 to 1000.
    void GenerateBills()
    {
        int count = vec.size(); //Determines the number of records in the global vector vec
        if (count == 0)
        {
            cout << "\nError in opening! File Not Found!!\n" << endl;
            return;
        }
        cout << "\n There are " << count << " record in the file";
        cout << "\n Enter Record Number to Search: ";
        cin >> n;

        b %= 15; //Reduces the value of b. It ensures that b is within the range [0, 14].
        if (b == 0)
        {
            cout << "\nYou Have No Bills!!\n";
            return;
        }
        for (int i = 0; i < b; i++)
        {
            int tempNum = (rand() % 1000) + 1; // Generates a random number between 1 and 1000 and assigns it to tempNum.
            BillsInAccount.push_back(tempNum); //Adds the generated tempNum to (the end) of the BillsInAccount vector.
            sumOfBills += tempNum; //Updates the total sum of bills by adding the current tempNum value.
        }
        sort(BillsInAccount.begin(), BillsInAccount.end()); 
        //Sorts the bills in ascending order.
    }

    void ShowBills()
    {
        cout << "\n-------The Bills You Have-------\n";
        GenerateBills(); //call the function to generate bills for display.
        for (int i = 1; i <= b; i++)
        {
            cout << "Bill Number " << i << ": " << BillsInAccount[i - 1] << '\n';
        }
        //Prints each bill's number and amount.
    }

    void PayBills()
    {
        ShowBills(); //Calls the ShowBills function to display the bills.
        cout << "Do You Want To Pay Your Bills? \n";
        string answer;
        while (true)
        {
            cin >> answer;
            for (int i = 0; i < answer.size(); i++)
            {
                answer[i] = towlower(answer[i]); //Converts the user's response to lowercase
            }
            if (answer == "yes")
            {
                if (sumOfBills <= vec[n - 1].total_Balance)
                {
                    withdraw();
                    cout << "You Paid All Your Bills!! \n";
                    cout << "Your Total Balance Is " << vec[n - 1].total_Balance << '\n';
                    break;
                }
                else
                {
                    int tempsum = 0, cnt = 0;
                    //tempsum: A temporary variable used to accumulate the sum of bill amounts.
                    //cnt : A counter variable to keep track of the number of bills that can be paid.

                    for (int i = 0; i < b; i++)
                    {

                        tempsum += BillsInAccount[i];
                        //Adds the amount of the bill at index i in the vector BillsInAccount to the tempsum.

                        if (tempsum <= vec[n - 1].total_Balance)
                        {
                            cnt++;
                        }
                        //If cnt is not zero, it means some bills can be paid.
                        // Asks the user if they want to pay those bills.
                        else if (cnt) 
                        {
                            tempsum -= BillsInAccount[i];

                            cout << "You Can Pay " << cnt << " Bills.\n";
                            cout << "DO You Want To Pay Them?\n";
                            cout << "Yes/No\n";
                            string str;
                            cin >> str;
                            for (int i = 0; i < answer.size(); i++)
                            {
                                str[i] = towlower(str[i]);
                            }
                            if (str == "no")
                            {
                                return;
                            }
                            else if (str == "yes")
                            {
                                sumOfBills = tempsum;
                                withdraw();
                                cout << "You Paied " << cnt << " Bills!!\n";
                                cout << "Your Total Balance Is " << vec[n - 1].total_Balance << '\n';
                                return;
                            }
                            else 
                            {
                                cout << "invaild input try again\n";
                                return;
                            }
                        }
                        else //If cnt is zero, the user doesn't have enough money to pay any bills.
                        {
                            cout << "You Dont Have Enough!!\n";
                            return;
                        }
                    }
                }
            }
            else if (answer == "no")
            {
                cout << "Ok Thanks For Your Visit \n";
                break;
            }
            else
            {
                cout << "Invalid Input Please Enter a Valid Input\nEthier YES or NO \n";
            }
        }

    }
};
class see_taxes
{
private:
    int tempPin; //temporary PIN entered by the user
    string tempAcc; //temporary account number entered by the user.
public:
    // A member function that calculates and displays taxes for a given account.
    void getTaxes()
    {
        int n, count = vec.size();
        //record number  //the size of the vector
        if (count == 0) //Checks if there are records in the file
        {
            cout << "\nError in opening! File Not Found!!\n" << endl;
            return;
        }
        cout << "\n There are " << count << " record in the file";
        cout << "\n Enter Record Number to Search: ";
        cin >> n;
        cout << "\nenter your pin then your account number : \n";
        cin >> tempPin >> tempAcc;

        // Checks if the entered PIN and account number match the stored values in the vector vec.
        if (tempPin == vec[n - 1].pin && tempAcc == vec[n - 1].account_number)
        {
            if (vec[n - 1].total_Balance != 0)
            {
                if (vec[n - 1].total_Balance <= 50000)
                {
                    cout << "\ntaxes for this account is : " << (vec[n - 1].total_Balance * 0.10) << '\n';
                    //Checks if the balance is non-zero and less than or equal to 50000. If true, calculates taxes as 10%.
                }
                else
                {
                    cout << "\ntaxes for this account is : " << (vec[n - 1].total_Balance * 0.15) << '\n';
                    //If the balance is greater than 50000, calculates taxes as 15%.
                }
            }
            else //If the balance is zero, indicates that there are no taxes for this account.
            {
                cout << "\nthere is no taxes for this account :)\n";
            }
        }
        else
        {
            cout << "incorect pin or account number \n";
            cout << "Do You Want to Try again? \n";
            string tempanswer;
            while (true)
            {
                cin >> tempanswer;
                for (int i = 0; i < tempanswer.size(); i++)
                {
                    tempanswer[i] = tolower(tempanswer[i]);
                }
                if (tempanswer == "yes")
                {
                    getTaxes();
                    break;
                }
                else if (tempanswer == "no")
                {
                    cout << "\n------thanks------\n" << endl;
                    break;
                }
                else
                {
                    cout << "invalid input try again\n";
                }
            }


        }

    }
};
class exchange
{
protected:
    double ex, egp, res;
    //Variables to store the exchange choice, the amount in Egyptian Pounds, and the result
    bool can = false; //A flag to indicate whether the withdrawal is possible
    int n; //Record number
    const double sr = 6.5, $ = 24.73, uae = 6.73, euro = 26.29, kwd = 80.79;
public:
    void withdraw()
    {
        if (egp > vec[n - 1].total_Balance)
        {
            cout << "You Dont Have This Amount Of Money In Your Account!!\n";
        }
        else
        {
            vec[n - 1].total_Balance -= egp;
            can = true;
        } //If the balance is enough, updates the account balance and sets the flag can to true.
    }
    void Exchange()
    {
        int count = vec.size(); //Determines the number of records in the global vector vec

        // Get the number of records in the file.
        // If there are no records, display an error message and return.
        if (count == 0)
        {
            cout << "\nError in opening! File Not Found!!\n" << endl;
            return;
        }
        cout << "\n There are " << count << " record in the file";
        cout << "\n Enter Record Number to Search: ";
        cin >> n;
        cout << "You are now in the foreign currency exchange list " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Enter the amount of money you want to exchange " << endl;
        cin >> egp;
        //Prompt the user to enter the amount in Egyptian Pounds.

        withdraw();
        //Call the withdraw function to check if the user has sufficient balance and update the can flag accordingly.
        //If the withdrawal is possible (can == true)

        if (can)
        {
            cout << "USD--> 1 " << endl;
            cout << "EURO--> 2 " << endl;
            cout << "UAE--> 3 " << endl; //UAE dirham
            cout << "SAR--> 4 " << endl; //Saudi riyal
            cout << "KWD--> 5" << endl; //Kuwaiti Dinar
            cin >> ex;

            if (ex == 1)
            {
                res = egp / $;
                cout << " Your amount of money now in Dollars = " << res << endl;
            }
            else if (ex == 2)
            {
                res = egp / euro;
                cout << " Your amount of money now in EUROs = " << res << endl;
            }
            else if (ex == 3)
            {
                res = egp / uae;
                cout << "Your amount of money now in UAE dirham = " << res << endl;
            }
            else if (ex == 4)

            {
                res = egp / sr;
                cout << "Your amount of money now in Saudi riyal = " << res << endl;
            }
            else if (ex == 5)
            {
                res = egp / kwd;
                cout << "Your amount of money now in Kuwaiti Dinar = " << res << endl;

            }
            else
            {
                cout << "Invaild Input \n";
            }
        }
    }
};
class Loan
{
protected:
    int currentDay, currentMonth, currentYear, paymentDay, paymentMonth, paymentYear, n;
    //Represent the current date and Represent the payment due date.
    float loan, taxes, monthlypayment;
    //loan: The loan amount taken by the customer.
    //taxes: The percentage of taxes to be added to the loan amount.

public:
    void read_loan()
    {
        int n, count = vec.size();
        if (count == 0)
        {
            cout << "\nError in opening! File Not Found!!\n" << endl;
            return;
        }
        cout << "\n There are " << count << " record in the file";
        cout << "\n Enter Record Number to Search: ";
        cin >> n;
        cout << "The curent day :" << endl;
        cin >> currentDay;
        cout << "The curent month :" << endl;
        cin >> currentMonth;
        cout << "Enter the curent year :" << endl;
        cin >> currentYear;
        cout << "The payment day :" << endl;
        cin >> paymentDay;
        cout << "The payment month :" << endl;
        cin >> paymentMonth;
        cout << "Enter the payment year :" << endl;
        cin >> paymentYear;
        int l;
        cout << "The cash you want to laon it :" << endl;
        cin >> l;
        loan = l;

        deposit();
        //Calls the deposit() method to add the loan amount to the customer's total balance.

        cout << "The taxes will added :" << endl;
        taxes = 0.10; //Sets the taxes to 10%.

        int numyears = paymentYear - currentYear;
        int nummonths = 12;
        monthlypayment = (loan + (loan * taxes)) / (numyears * nummonths);
        //Calculates the monthlypayment based on the loan amount, taxes, and the number of years.
        
        show_loan();
    }

    void show_loan()
    {
        cout << "*The Curent Date :" << currentDay << " / " << currentMonth << " / " << currentYear << " ***" << endl;
        cout << "*The Payment Date :" << paymentDay << " / " << paymentMonth << "/ " << paymentYear << " ***" << endl;
        cout << "*The Loan taken by the custmor :" << loan << " ***" << endl;
        cout << "*The Taxes added to the loan " << taxes * 100 << "%" << " ***" << endl;
        cout << "*The Montly Payment : " << monthlypayment << " ***" << endl;
    }

    void deposit()
    {
        vec[n - 1].total_Balance += loan;
        //Adds the loan amount to the customer's total balance in the vector.
    }

};

class Transaction
{
protected:
    int Deposit, Withdraw, n;

public:
    void trans()
    {
        int count = vec.size();
        if (count == 0)
        {
            cout << "\nError in opening! File Not Found!!\n" << endl;
            return;
        }
        cout << "\n There are " << count << " record in the file";
        cout << "\n Enter Record Number to Search: ";
        cin >> n;

        int choice;
        cout << "deposit--> 1\nwithdraw--> 2\n";
        cin >> choice;
        if (choice == 1)
        {
            deposit();
        }
        else if (choice == 2)
        {
            withdraw();
        }
        else
        {
            cout << "Invalid Input\n";
        }
    }

    void deposit()
    {
        int d;
        cout << " ***Enter the number you want to deposit : *****" << endl;
        cin >> d;
        Deposit = d;
        vec[n - 1].total_Balance = vec[n - 1].total_Balance + Deposit;
        show_Deposit();  //method to display deposit details.
    }
    void show_Deposit()
    {
        cout << " **The number you have entered : " << Deposit << "" << endl;
        cout << " **The Total Balance :" << vec[n - 1].total_Balance << "" << endl;
    }
    void withdraw()
    {
        int w;
        cout << "The number you want to withdraw :" << endl;
        cin >> w;
        Withdraw = w;

        if (w <= vec[n - 1].total_Balance)
        {
            vec[n - 1].total_Balance = vec[n - 1].total_Balance - w;
        }
        else
            cout << "You don't have enough money " << endl;

        show_withdraw();
        //Displays the amount withdrawn and the updated total balance.
    }
    void show_withdraw()
    {
        cout << "The number you withdrawd :" << Withdraw << "" << endl;
        cout << "The Total balance : " << vec[n - 1].total_Balance << "" << endl;
    }

};

class bank : public  Transaction, public Loan, public bills, public see_taxes, public exchange
{
public:
    bank()
    {
        cout << "\n\tWelcom To The Bank :)\n";
    }

    ~bank()
    {
        cout << "\n\tGoodbye <:\n";
    }
};
/*
The read_data function within the account_query class is responsible for
collecting information from the user to create a new account
and then adding that account to the vec vector.
*/
void account_query::read_data()
{
    account_query temp;
    //Creates a local variable temp of type account_query to temporarily
    //store the user input before adding it to the vector.
    
    string acc, f, l, cc, pn;
    int pin;
    float t;

    //Assigns the user-input values to the corresponding members of the temp object.
    cout << "\nEnter Account Number: ";
    cin >> acc;
    temp.account_number = acc;

    cout << "Enter First Name: ";
    cin >> f;
    temp.firstName = f;

    cout << "Enter Last Name: ";
    cin >> l;
    temp.lastName = l;

    cout << "Enter Balance: ";
    cin >> t;
    temp.total_Balance = t;

    cout << "Enter Card Number: ";
    cin >> cc;
    temp.credit_card = cc;

    cout << "Enter Your Phone Number: ";
    cin >> pn;
    temp.phone_number = pn;

    cout << "Enter The Pin Code: ";
    cin >> pin;
    temp.pin = pin;

    cout << endl;
    vec.push_back(temp);
    //Adds the temp object (which now holds the user's input) to the vec vector using vec.push_back(temp).
}

/*void account_query::show_data(account_query account):
This function is a member of the account_query class,
and it takes an account_query object as a parameter.*/
void account_query::show_data(account_query account)
{
    cout << "Account Number: " << account.account_number << endl;
    cout << "First Name: " << account.firstName << endl;
    cout << "Last Name: " << account.lastName << endl;
    cout << "Current Balance: Rs.  " << account.total_Balance << endl;
    cout << "Your Phone Number: " << account.phone_number << endl;
    cout << "Card Number: " << account.credit_card << endl;
    cout << "-------------------------------" << endl;
}

/*designed to read and display records from the vec vector,
which presumably contains information about multiple accounts.*/
void account_query::read_rec()
{
    //Checks the size of the vec vector to determine if it contains any records.
    int sz = vec.size();
    if (sz == 0)
    {
        cout << "\nError in Opening! File Not Found!!\n" << endl;
        return;
    }

    cout << "\n**Data from file" << endl;
    for (int i = 0; i < sz; i++)
    {
        show_data(vec[i]);
    }
    //Calls the show_data function to display the details of each account.
}

int main()
{
    bank A;
    int choice;
    bool f = true;
    cout << "*Account Information System*" << endl;
    while (f)
    {
        cout << "Select one option below ";
        cout << "\n\t1-->Add record to file";
        cout << "\n\t2-->Show record from file";
        cout << "\n\t3-->See Taxes";
        cout << "\n\t4-->See Bills";
        cout << "\n\t5-->Exchange";
        cout << "\n\t6-->Loan Services";
        cout << "\n\t7-->Transaction";
        cout << "\n\t8-->Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            A.read_data();
            break;
        case 2:
            A.read_rec();
            break;
        case 3:
            A.getTaxes();
            break;
        case 4:
            A.PayBills();
            break;
        case 5:
            A.Exchange();
            break;
        case 6:
            A.read_loan();
            break;
        case 7:
            A.trans();
            break;
        case 8:
            f = false;
            break;
        default:
            cout << "\nEnter corret choice";
            f = false;
        }
    }
    return 0;
