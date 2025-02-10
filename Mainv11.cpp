#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <conio.h>
using namespace std;
class Accessories
{
private:
    struct Acc
    {
        string name;
        int Qty;
        double price;
    };
    Acc a1[20];
    string acc_name;

protected:
    string AccessoriesBasket[100];
    int AccItemCount;
    int NoOfAccessories[100];
    double IndividualAccprice[100];
    double AccessoriesTotal;

public:
    Accessories() : AccItemCount(0), AccessoriesTotal(0)
    {
        ofstream outFile("accessories.txt", ios ::app);
        ifstream inFile("accessories.txt");
        if (inFile.is_open())
        {
            for (int i = 0; i < 20; i++)
            {
                inFile >> a1[i].name >> a1[i].Qty >> a1[i].price;
            }
            inFile.close(); // Memory efficiency //
        }
        else
        {
            cout << "\t\t\t\t\t Unable to open the file." << endl;
            return;
        }
    }
    void chk_accessories();
    double purchaseStockupdate();
    void updateAccfile();
};
void Accessories ::chk_accessories()
{
    bool available = false;
    cout << "Enter the name of Accessories and press Enter: ";
    cin >> acc_name;
    for (int i = 0; i < 20; i++)
    {
        if (a1[i].name == acc_name && a1[i].Qty > 0)
        {
            cout << "\t\t\t\t\t Available" << endl;
            AccessoriesBasket[AccItemCount] = acc_name;
            AccItemCount++;
            available = true;
            break;
        }
    }
    if (!available)
    {
        cout << "\t\t\t\t\t Not Available" << endl;
    }
}
void Accessories ::updateAccfile()
{
    ofstream outFile("accessories.txt"); // overwrite//
    for (int i = 0; i < 20; i++)
    {
        outFile << a1[i].name << " " << a1[i].Qty << " " << a1[i].price << endl;
    }
    outFile.close();
}
double Accessories::purchaseStockupdate()
{
    for (int i = 0; i < AccItemCount; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (a1[j].name == AccessoriesBasket[i] && a1[j].Qty > 0)
            {
                cout << "\t\t\t\t\t Enter how many " << a1[j].name << " you want: ";
                cin >> NoOfAccessories[i];
                IndividualAccprice[i] = a1[j].price;
                while (NoOfAccessories[i] > a1[j].Qty)
                {
                    cout << "\t\t\t\t\t Not enough quantity, Available quantity is " << a1[j].Qty << endl;
                    cout << "\t\t\t\t\t Enter how many " << a1[j].name << " you want(Under available quantity): ";
                    cin >> NoOfAccessories[i];
                }
                a1[j].Qty -= NoOfAccessories[i];
                AccessoriesTotal = AccessoriesTotal + a1[j].price * NoOfAccessories[i];
                break;
            }
        }
    }
    updateAccfile(); // Update the file after the purchase
    return AccessoriesTotal;
}
class medicine
{
private:
    struct med
    {
        string name;
        string formula;
        int Availability;
        int price;
        string category;
    };
    med m1[76];
    string userMed;

protected:
    string MedicineBasket[100];
    int NoOfMed[100];
    int ItemCount;
    int IndividualMedprice[100];
    double MedTotal;

public:
    medicine() : ItemCount(0), MedTotal(0)
    {
        ofstream outFile("medicines.txt", ios ::app);
        ifstream inFile("medicines.txt");

        if (inFile.is_open())
        {
            for (int i = 0; i < 76; i++)
            {
                inFile >> m1[i].name >> m1[i].formula >> m1[i].Availability >> m1[i].price >> m1[i].category;
            }
            inFile.close(); // memory efficiency //
        }
        else
        {
            cout << "\t\t\t\t\t Unable to open the file." << endl;
            return;
        }
    }
    void checkMed();
    void updateMedFile();
    double purchase_Stockupdate();
   
};
void medicine ::checkMed()
{
    cout << "\t\t\t\t\t Enter the name of the medicine and press Enter: ";
    cin >> userMed;
    string userFormula;
    bool userMedFormulaFound = false;
    bool Available = false;
    bool formula = false;
    for (int i = 0; i < 76; i++)
    {
        if (m1[i].name == userMed && m1[i].Availability > 0)
        {
            cout << "\t\t\t\t\t " << m1[i].name << " is available and came under " << m1[i].category << endl;
            Available = true;
            MedicineBasket[ItemCount] = userMed;
            ItemCount++;
            break;
        }
        if (m1[i].name == userMed)
        {
            userFormula = m1[i].formula;
            userMedFormulaFound = true;
        }
    }
    if (userMedFormulaFound && !Available)
    {
        cout << "\t\t\t\t\t " << userMed << " is not available, here is alternative" << endl;
        for (int i = 0; i < 76; i++)
        {
            if (m1[i].formula == userFormula && m1[i].Availability > 0)
            {
                cout << "\t\t\t\t\t " << m1[i].name << " is Available and came under " << m1[i].category << endl;
                char confirmPurchase;
                cout << "\t\t\t\t\t Do you want to purchase it (y/n) ";
                cin >> confirmPurchase;
                if (confirmPurchase == 'y' || confirmPurchase == 'Y')
                {
                    MedicineBasket[ItemCount] = m1[i].name;
                    ItemCount++;
                    break;
                }
                else
                {
                    break; // Break out of the loop if the user chooses not to purchase
                }
            }
        }
    }
    if (!userMedFormulaFound && !Available)
    {
        cout << "\t\t\t\t\t Enter formula: ";
        cin >> userFormula;

        for (int i = 0; i < 76; i++)
        {
            if (m1[i].formula == userFormula && m1[i].Availability > 0)
            {
                cout << "\t\t\t\t\t " << m1[i].name << " is Available and came under " << m1[i].category << endl;
                char confirmPurchase;
                cout << "\t\t\t\t\t Do you want to purchase it (y/n): " << endl;
                cin >> confirmPurchase;
                if (confirmPurchase == 'y' || confirmPurchase == 'Y')
                {
                    MedicineBasket[ItemCount] = m1[i].name;
                    formula = true;
                    ItemCount++;
                    break;
                }
                else
                {
                    break; // Break out of the loop if the user chooses not to purchase
                }
            }
        }
    }
    if (!userMedFormulaFound && !Available && !formula)
    {
        cout << "\t\t\t\t\t Medicine not found." << endl;
        cout << "\t\t\t\t\t Sorry" << endl;
        return;
    }
}
void medicine ::updateMedFile()
{
    ofstream outFile("medicines.txt");
    for (int i = 0; i < 76; i++)
    {
        outFile << m1[i].name << " " << m1[i].formula << " " << m1[i].Availability << " " << m1[i].price << " " << m1[i].category << endl;
    }
    outFile.close();
}

double medicine ::purchase_Stockupdate()
{
    for (int i = 0; i < ItemCount; i++)
    {
        for (int j = 0; j < 76; j++)
        {
            if (m1[j].name == MedicineBasket[i] && m1[j].Availability > 0)
            {
                cout << "\t\t\t\t\t Enter how many " << m1[j].name << " you want: ";
                cin >> NoOfMed[i];
                IndividualMedprice[i] = m1[j].price;

                while (NoOfMed[i] > m1[j].Availability)
                {
                    cout << "\t\t\t\t\t Not enough quantity, Available quantity is " << m1[j].Availability << endl;
                    cout << "\t\t\t\t\t Enter how many " << m1[j].name << " you want(under available quantity): ";
                    cin >> NoOfMed[i];
                }
                m1[j].Availability -= NoOfMed[i];
                MedTotal = MedTotal + m1[j].price * NoOfMed[i];
                break;
            }
        }
    }
    updateMedFile(); // Update the file after the purchase
    return MedTotal;
}
class ProductAndBIll : public medicine, public Accessories
{
private:
    double Bill;
    int Bronze = 2000;
    int Silver = 3500;
    int Gold = 5000;
    time_t Now = time(0);

public:
    void SetPrice()
    {
        purchaseStockupdate();
        purchase_Stockupdate();
    }

    double getbill()
    {
        Bill = MedTotal + AccessoriesTotal;
        return Bill;
    }
    void GenerateBill();
    void ProductIput();
};
void ProductAndBIll::ProductIput()
{
    int Option;
    cout << "\t\t\t\t\t What do you want to purchase:" << endl;
    cout << "\t\t\t\t\t Press 1 for Medicines" << endl;
    cout << "\t\t\t\t\t Press 2 for Accessories" << endl;
    cout << "\t\t\t\t\t ";
    cin >> Option;

    switch (Option)
    {
    case 1:
        cin.ignore();
        checkMed();
        break;
    case 2:
        cin.ignore();
        chk_accessories();
        break;
    default:
        cout << "\t\t\t\t\t Invalid option. Please choose a valid option." << endl;
        ProductIput();
        break;
    }
    char continueOption;
    cout << "\t\t\t\t\t Do you want to make another purchase? (y/n): ";
    cin >> continueOption;
    if (continueOption == 'y' || continueOption == 'Y')
    {
        cin.ignore();
        ProductIput(); // Recursive call to continue the process
    }
    else
    {
        SetPrice();
        GenerateBill();
    }
}

void ProductAndBIll ::GenerateBill()
{
    if (getbill() > 0)
    {
        cout << "\t\t\t\t\t "
             << "Name"
             << "\t\t"
             << "Quantity"
             << "\t\t"
             << "$/-"
             << "\t\t"
             << "Price" << endl;
        for (int i = 0; i < ItemCount; i++)
        {
            cout << "\t\t\t\t\t " << MedicineBasket[i] << "\t\t\t" << NoOfMed[i] << "\t\t" << IndividualMedprice[i] << "\t\t" << NoOfMed[i] * IndividualMedprice[i] << endl;
        }
        for (int i = 0; i < AccItemCount; i++)
        {
            cout << "\t\t\t\t\t " << AccessoriesBasket[i] << "\t\t\t" << NoOfAccessories[i] << "\t\t" << IndividualAccprice[i] << "\t\t" << NoOfAccessories[i] * IndividualAccprice[i] << endl;
        }
        if (getbill() >= Gold)
        {
            cout << "\t\t\t\t\t You Got Gold level discount as you made a purchase more than 5000" << endl;
            cout << "\t\t\t\t\t Your Total Bill was: " << getbill() << endl;
            cout << "\t\t\t\t\t Your Bill after discount: " << getbill() - (getbill() * 0.30) << endl;
            cout << "\t\t\t\t\t Time is:  " << ctime(&Now) << endl;
        }
        else if (getbill() >= Silver)
        {
            cout << "\t\t\t\t\t You Got Silver level discount as you made a purchase more than 3500" << endl;
            cout << "\t\t\t\t\t Your Total Bill was: " << getbill() << endl;
            cout << "\t\t\t\t\t Your Bill after discount: " << getbill() - (getbill() * 0.20) << endl;
            cout << "\t\t\t\t\t Time is:  " << ctime(&Now) << endl;
        }
        else if (getbill() >= Bronze)
        {
            cout << "\t\t\t\t\t You Got Bronze level discount as you made a purchase more than 2000" << endl;
            cout << "\t\t\t\t\t Your Total Bill was: " << getbill() << endl;
            cout << "\t\t\t\t\t Your Bill after discount: " << getbill() - (getbill() * 0.10) << endl;
            cout << "\t\t\t\t\t Time is:  " << ctime(&Now) << endl;
        }
        else
        {
            cout << "\t\t\t\t\t Your total bill is: " << getbill() << endl;
            cout << "\t\t\t\t\t Time is:  " << ctime(&Now) << endl;
        }
    }
    else
    {
        cout << "\t\t\t\t\t Thank you :)" << endl;
    }
}
class Access : public ProductAndBIll
{
protected:
    struct info
    {
        string id;
        string pass;
    };
    info oldUser;
    info newUser;
    info check_info;
    ofstream outfile;
    ifstream infofile;
    bool loginSuccessful = false;
    int ask;

public:
    Access() : ask(0)
    {
        outfile.open("data.txt", ios::app);
        infofile.open("data.txt");
    }
    void logIn();
    void signIn();
};
void Access ::signIn()
{
    cout << "\n\t\t\t\t\t Enter your name: ";
    cin >> newUser.id;
    if (infofile.is_open())
    {
        infofile.clear();            // Clear the end-of-file flag
        infofile.seekg(0, ios::beg); // Move the file pointer to the beginning taky file ko start se read kry
        while (infofile >> check_info.id >> check_info.pass)
            if (newUser.id == check_info.id)
            {
                infofile.clear(); // Clear the end-of-file flag
                infofile.seekg(0, ios::beg);
                cout << "\t\t\t\t\t Enter different name, This name already exists" << endl;
                cout << "\t\t\t\t\t Enter your name: ";
                cin >> newUser.id;
            }
    }
    do
    {
        cout << "\t\t\t\t\t Enter your pin: ";
        char ch;
        int i = 0;
        while ((ch = _getch()) != '\r')
        {
            if (ch == '\b')
            {
                if (i > 0)
                {
                    cout << "\b \b";
                    newUser.pass.pop_back();
                    i--;
                }
            }
            else
            {
                newUser.pass = newUser.pass + ch;
                cout << "*";
                i++;
            }
        }
        cout << endl;
        if (newUser.pass.empty())
        {
            cout << "\t\t\t\t\t Password cannot be empty. Please enter a password." << endl;
            continue;
        }
    } while (newUser.pass.empty());

    outfile.clear();
    if (outfile.is_open())
    {
        outfile << newUser.id << " " << newUser.pass << endl;
        cout << "\t\t\t\t\t SignIn Complete." << endl;
        system("cls");
        ofstream newoutfile(newUser.id + ".txt", ios ::app);
        newoutfile << "Name"
                   << "\t\t"
                   << "Quantity"
                   << "\t\t"
                   << "$/-"
                   << "\t\t"
                   << "Price" << endl;
    }
    else
    {
        cout << "\t\t\t\t\t Error Occured while signing In" << endl;
    }
}
void Access::logIn()
{

    do
    {
        cout << "\t\t\t\t\t Enter username: ";
        cin >> oldUser.id;
        cout << endl;
        if (oldUser.id.empty()) // agr password wali blank khaali haii
        {
            cout << "\t\t\t\t\t Username cannot be empty. Please enter aa Username." << endl;
            continue; // loop shuro se shuro hojayegi //
        }
        oldUser.pass = "";
        cout << "\t\t\t\t\t Enter password: ";
        char ch;
        int i = 0;
        while ((ch = _getch()) != '\r')
        {
            if (ch == '\b')
            {
                if (i > 0)
                {
                    cout << "\b \b";
                    oldUser.pass.pop_back();
                    i--;
                }
            }
            else
            {
                oldUser.pass += ch;
                cout << '*'; // asterik print hongy for hiding password//
                i++;
            }
        }
        cout << endl;
        if (oldUser.pass.empty()) // agr password wali blank khaali haii
        {
            cout << "\t\t\t\t\t Password cannot be empty. Please enter a password." << endl;
            continue; // loop shuro se shuro hojayegi //
        }
        loginSuccessful = false;
        infofile.clear(); // Clear any error flags
        infofile.seekg(0, ios::beg);
        while (infofile >> check_info.id >> check_info.pass)
        {
            if (oldUser.id == check_info.id && oldUser.pass == check_info.pass)
            {
                cout << "\t\t\t\t\t Login Done" << endl;
                system("cls");
                loginSuccessful = true;
                break;
            }
        }

        if (!loginSuccessful)
        {
            cout << "\t\t\t\t\t Try Again" << endl;
        }
        infofile.clear();
        infofile.seekg(0, ios::beg);

    } while (!loginSuccessful);
    infofile.close();
}
class CustomerLog : public Access
{
private:
public:
    void creatlog()
    {
        time_t Now = time(0);
        if (ask == 1)
        {
            ofstream newoutfile(newUser.id + ".txt", ios ::app);
            if (getbill() > 0)
            {
                if (ItemCount > 0)
                    for (int i = 0; i < ItemCount; i++)
                    {
                        newoutfile << MedicineBasket[i] << "\t\t" << NoOfMed[i] << "\t\t" << IndividualMedprice[i] << "\t\t" << NoOfMed[i] * IndividualMedprice[i] << endl;
                    }
                if (AccItemCount > 0)
                    for (int i = 0; i < ItemCount; i++)
                    {
                        newoutfile << AccessoriesBasket[i] << "\t\t" << NoOfAccessories[i] << "\t\t" << IndividualAccprice[i] << "\t\t" << NoOfAccessories[i] * IndividualAccprice[i] << endl;
                    }
                newoutfile << "Your Total bill is: " << getbill() << endl;
                newoutfile << "Time is: ";
                newoutfile << ctime(&Now) << endl;
            }
        }
        else
        {
            ofstream oldoutfile(oldUser.id + ".txt", ios::app);
            if (getbill() > 0)
            {
                if (ItemCount > 0)
                {
                    for (int i = 0; i < ItemCount; i++)
                    {
                        oldoutfile << MedicineBasket[i] << "\t\t" << NoOfMed[i] << "\t\t" << IndividualMedprice[i] << "\t\t" << NoOfMed[i] * IndividualMedprice[i] << endl;
                    }
                }
                if (AccItemCount > 0)
                {
                    for (int i = 0; i < AccItemCount; i++)
                    {
                        oldoutfile << AccessoriesBasket[i] << "\t\t" << NoOfAccessories[i] << "\t\t" << IndividualAccprice[i] << "\t" << NoOfAccessories[i] * IndividualAccprice[i] << endl;
                    }
                }
                oldoutfile << "Your Total bill is: " << getbill() << endl;
                oldoutfile << "Time is: ";
                oldoutfile << ctime(&Now) << endl;
                oldoutfile << endl
                           << endl
                           << endl;
            }
        }
    }
    

    void mainMenu()
    {
        cout << "\t\t\t\t\t Enter for following." << endl;
        cout << "\t\t\t\t\t Press 1 for SignUp" << endl;
        cout << "\t\t\t\t\t Press 2 for LogIn" << endl;
        cout << "\t\t\t\t\t Press 3 for exit" << endl;
        cout << "\t\t\t\t\t ";
        cin >> ask;

        system("cls");
        if (ask == 1)
        {
            signIn();
            mainMenu();
        }
        else if (ask == 2)
        {
            logIn();
            if (loginSuccessful)
            {
                ProductIput();
                creatlog();
            }
        }
        else if (ask == 3)
        {
            cout << "\t\t\t\t\t GoodBye" << endl;
            exit(0);
        }

        else
        {
            cout << "\t\t\t\t\t Invalid Choice! Try Again" << endl;
            cin.ignore(); // Clear the input buffer
            mainMenu();
        }
    }
};
void displayWelcomePage()
{
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setfill(' ') << setw(100) << "* Welcome to Pharmacy Management system *" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
    cout << setw(160) << setfill('*') << "" << endl;
}
int main()
{
    displayWelcomePage();

    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\t Press Enter to continue...";
    char ch;
    ch = _getch();

    system("cls");

    CustomerLog c;
    c.mainMenu();;
}
