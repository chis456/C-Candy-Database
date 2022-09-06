#include <iostream>
#include "Database.cpp"

using namespace std;

class Menu
{
    public:
    Database candyData;
    Menu()
    {
        cout << "Welcome to the Candy and Sweets Database - For all your sweet tooth needs" << endl;
        cout << "_________________________________________________________________________" << endl;
        mainMenu();
    }

    void mainMenu()
    {
        while(true)
        {
            cout << "Options:\n1. Add a Candy\n2. Remove a Candy"
            << "\n3. Find a Candy\n4. Display all Candy information\n5. Quit" << endl;
            cout << "Type the corresponding number to proceed with that option" << endl;
            string input;
            cin >> input;
            
            if(input == "1")
            {
                add();
            }

            else if(input == "2")
            {
                del();
            }
            
            else if(input == "3")
            {
                search();
            }

            else if(input == "4")
            {
                display();
            }

            else if(input == "5")
            {
                break;
            }

            else
            {
                cout << "Not a valid input" << endl;
            }
        }
    } 

    void add()
    {
        candyData.addCandy();
    }

    void del()
    {
        while(true)
        {
            cout << "Delete by which method?"
                 << "\n1. Delete one entry by name\n2. Delete multiple entries by name"
                 << "\n3. Delete one entry by price\n4. Delete multiple entries by price"
                 <<  "\n5. Delete one entry by amount of candies per package" 
                 << "\n6. Delete multiple entries by amount of candies per package"
                 <<  "\n7. Delete one entry by calories\n8. Delete multiple entries by calories"
                 << "\n9. Return to Main Menu" << endl;

            string delChoice;
            cin.ignore();
            cin >> delChoice;

            if(delChoice == "1")
            {
                string name;
                cout << "Enter the exact name of candy you want to remove:" << endl;
                cin.ignore();
                getline(cin, name);

                if(candyData.exactSearch(name, true) == 0)
                {
                    cout << "Are you sure you want to delete this entry?"
                    << " (y to proceed, any key to cancel)" << endl;
                    string choose;
                    cin >> choose;
                    if(choose == "y")
                    {
                        candyData.removeCandy(name);
                    }
                }
            }
            else if(delChoice == "2")
            {
                string name;
                cout << "Search for candies you want to remove:" << endl;
                cin.ignore();
                getline(cin, name);
                vector<Candy> candies = candyData.findAndPrint(name);
                if(candies.size() != 0)
                {
                    cout << "Are you sure you want to delete the following?" 
                    << "(y to proceed, any key to cancel)" << endl;
                    string choice;
                    cin >> choice;
                    if(choice == "y")
                    {
                        for(int i = 0; i < candies.size(); i++)
                        {
                            candyData.removeCandy(candies.at(i).getName());
                        }
                    }
                }
            }
            else if(delChoice == "3")
            {
                while(true)
                {
                    bool valid;
                    string p;
                    double price;
                    cout << "Enter exact price of candy you want to remove" << endl;
                    cin.ignore();
                    cin >> p;
                    try
                    {
                        price = stod(p);
                        if(price <= 0)
                        {
                            cout << "Price cannot be 0 or lower" << endl;
                            valid = false;
                        }
                        else
                        {
                            valid = true;
                        }
                        
                    }
                    catch(...)
                    {
                        valid = false;
                        cout << "Not a valid input" << endl;
                    }
                    if(valid)
                    {
                        if(candyData.exactSearch(price) == 0)
                        {
                            cout << "Are you sure you want to delete this entry?" 
                            << "(y to proceed, any key to cancel)" << endl;
                            string choice;
                            cin.ignore();
                            cin >> choice;
                            if(choice == "y")
                            {
                                candyData.removeCandy(price);
                            }
                        }
                    }
                    break;
                }
            }
            else if(delChoice == "4")
            {
                while(true)
                {
                    bool valid;
                    string p1;
                    string p2;
                    double price1;
                    double price2;
                    cout << "Enter minimum price" << endl;
                    cin.ignore();
                    cin >> p1;
                    cout << "Enter maximum price" << endl;
                    cin.ignore();
                    cin >> p2;
                    try
                    {
                        price1 = stod(p1);
                        price2 = stod(p2);
                        if(price1 <= 0 || price2 <= 0)
                        {
                            cout << "Each price must be a non-zero positive number" << endl;
                            valid = false;
                        }
                        else
                        {
                            valid = true;
                        }
                    }
                    catch(...)
                    {
                        valid = false;
                        cout << "Not a valid input" << endl;
                    }
                    if(valid)
                    {
                        vector<Candy> candies = candyData.rangeSearchPrice(price1, price2);
                        if(candies.size() != 0)
                        {
                            cout << "Are you sure want to delete these entries?" 
                            << " (y to proceed, any key to cancel)" << endl;
                            string choice;
                            cin.ignore();
                            cin >> choice;
                            if(choice == "y")
                            {
                                for(int i = 0; i < candies.size(); i++)
                                {
                                    candyData.removeCandy(candies.at(i).getPrice());
                                }
                            }
                        }
                        break;
                    }
                }
            }

            else if(delChoice == "5")
            {
                while(true)
                {
                    bool valid;
                    string a;
                    int amount;
                    cout << "Enter exact number of candies per package of the candy you want to remove" << endl;
                    cin.ignore();
                    cin >> a;
                    try
                    {
                        amount = stoi(a);
                        if(amount <= 0)
                        {
                            cout << "Amount cannot be 0 or lower" << endl;
                            valid = false;
                        }
                        else
                        {
                            valid = true;
                        }
                    }
                    catch(...)
                    {
                        valid = false;
                        cout << "Not a valid input" << endl;
                    }
                    if(valid)
                    {
                        if(candyData.exactSearchAmount(amount) == 0)
                        {
                            cout << "Are you sure you want to delete this entry?" 
                            << "(y to proceed, any key to cancel)" << endl;
                            string choice;
                            cin.ignore();
                            cin >> choice;
                            if(choice == "y")
                            {
                                candyData.removeCandy(amount);
                            }
                        }
                    }
                    break;
                }
            }

            else if(delChoice == "6")
            {
                while(true)
                {
                    bool valid;
                    string a1;
                    string a2;
                    double amount1;
                    double amount2;
                    cout << "Enter minimum amount" << endl;
                    cin.ignore();
                    cin >> a1;
                    cout << "Enter maximum amount" << endl;
                    cin.ignore();
                    cin >> a2;
                    try
                    {
                        amount1 = stoi(a1);
                        amount2 = stoi(a2);
                        if(amount1 <= 0 || amount2 <= 0)
                        {
                            cout << "Each amount must be a non-zero positive number" << endl;
                            valid = false;
                        }
                        else
                        {
                            valid = true;
                        }
                    }
                    catch(...)
                    {
                        valid = false;
                        cout << "Not a valid input" << endl;
                    }
                    if(valid)
                    {
                        vector<Candy> candies = candyData.rangeSearchAmount(amount1, amount2);
                        if(candies.size() != 0)
                        {
                            cout << "Are you sure want to delete these entries?" 
                            << " (y to proceed, any key to cancel)" << endl;
                            string choice;
                            cin.ignore();
                            cin >> choice;
                            if(choice == "y")
                            {
                                for(int i = 0; i < candies.size(); i++)
                                {
                                    candyData.removeCandy(candies.at(i).getAmount());
                                }
                            }
                        }
                        break;
                    }
                }
            }

            else if(delChoice == "7")
            {
                while(true)
                {
                    bool valid;
                    string c;
                    int cal;
                    cout << "Enter exact number of calories per package of the candy you want to remove" << endl;
                    cin.ignore();
                    cin >> c;
                    try
                    {
                        cal = stoi(c);
                        if(cal <= 0)
                        {
                            cout << "Calories cannot be 0 or lower" << endl;
                            valid = false;
                        }
                        else
                        {
                            valid = true;
                        }
                    }
                    catch(...)
                    {
                        valid = false;
                        cout << "Not a valid input" << endl;
                    }
                    if(valid)
                    {
                        if(candyData.exactSearchCal(cal) == 0)
                        {
                            cout << "Are you sure you want to delete this entry?" 
                            << "(y to proceed, any key to cancel)" << endl;
                            string choice;
                            cin.ignore();
                            cin >> choice;
                            if(choice == "y")
                            {
                                candyData.removeCandyCal(cal);
                            }
                        }
                    }
                    break;
                }
            }

            else if(delChoice == "8")
            {
                while(true)
                {
                    bool valid;
                    string c1;
                    string c2;
                    double cal1;
                    double cal2;
                    cout << "Enter minimum calories" << endl;
                    cin.ignore();
                    cin >> c1;
                    cout << "Enter maximum calories" << endl;
                    cin.ignore();
                    cin >> c2;
                    try
                    {
                        cal1 = stoi(c1);
                        cal2 = stoi(c2);
                        if(cal1 <= 0 || cal2 <= 0)
                        {
                            cout << "Each calorie count must be a non-zero positive number" << endl;
                            valid = false;
                        }
                        else
                        {
                            valid = true;
                        }
                    }
                    catch(...)
                    {
                        valid = false;
                        cout << "Not a valid input" << endl;
                    }
                    if(valid)
                    {
                        vector<Candy> candies = candyData.rangeSearchCal(cal1, cal2);
                        if(candies.size() != 0)
                        {
                            cout << "Are you sure want to delete these entries?" 
                            << " (y to proceed, any key to cancel)" << endl;
                            string choice;
                            cin.ignore();
                            cin >> choice;
                            if(choice == "y")
                            {
                                for(int i = 0; i < candies.size(); i++)
                                {
                                    candyData.removeCandyCal(candies.at(i).getCal());
                                }
                            }
                        }
                        break;
                    }
                }
            }
            else if(delChoice == "9")
            {
                break;
            }
            else
            {
                cout << "Invalid input" << endl;
            }
        }
    }

    void search()
    {
        while(true)
        {
            cout << "Search by which parameter?" << endl;
            cout << "1. Name\n2. Price\n3. No. of candies per package"
                << " \n4. Calorie Count\n5. Price per piece\n6. Return to Main Menu" << endl;
            string choice;
            cin >> choice;
            if(choice == "1")
            {
                cout << "Search method?" 
                << "\n1. Search for exact name\n2. Search with keyword" << endl;
                string choose;
                string name;
                cin.ignore();
                cin >> choose;
                if(choose == "1")
                {
                    cout << "Enter name of candy" << endl;
                    cin.ignore();
                    getline(cin, name);
                    candyData.exactSearch(name, false);
                }
                else if(choose == "2")
                {
                    cout << "Enter keyword" << endl;
                    cin.ignore();
                    getline(cin, name);
                    candyData.findAndPrint(name);
                }
                else
                {
                    cout << "Not a valid input" << endl;
                }
            }
            else if(choice == "2")
            {
                cout << "Search Method?\n" 
                << "1. Search by exact price\n2. Search by price range" << endl;
                string choose;
                cin.ignore();
                cin >> choose;
                if(choose == "1")
                {
                    while(true)
                    {
                        string price;
                        double p;
                        cin.ignore();
                        cout << "Enter price" << endl;
                        cin >> price;
                        bool valid;
                        try
                        {
                            p = stod(price);
                            if(p <= 0)
                            {
                                cout << "Price cannot be 0 or lower" << endl;
                                valid = false;
                            }
                            else
                            {
                                valid = true;
                            }
                        }
                        catch(...)
                        {
                            valid = false;
                            cout << "not a valid input" << endl;
                        }
                        if(valid)
                        {
                            candyData.exactSearch(p);
                            break;
                        }
                    }
                }
                if(choose == "2")
                {
                    while(true)
                    {
                        bool valid;
                        string price1;
                        string price2;
                        double p1;
                        double p2;
                        cin.ignore();
                        cout << "Enter minimum price" << endl;
                        cin >> price1;
                        cout << "Enter maximum price" << endl;
                        cin >> price2;
                        try 
                        {
                            p1= stod(price1);
                            p2 = stod(price2);
                            if(p1 <= 0 || p2 <= 0)
                            {
                                cout << "Price cannot be 0 or less" << endl;
                                valid = false;
                            }
                            else
                            {  
                                valid = true;
                            }
                        }
                        catch(...)
                        {
                            cout << "Not a valid input" << endl;
                            valid = false;
                        }
                        if(valid)
                        {
                            candyData.rangeSearchPrice(p1, p2);
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Not a valid input" << endl;
                }
            }
            else if(choice == "3")
            {
                cout << "Search Method?\n" 
                << "1. Search by exact amount\n2. Search by amount range" << endl;
                string choose;
                cin.ignore();
                cin >> choose;
                if(choose == "1")
                {
                    while(true)
                    {
                        string amount;
                        int a;
                        cin.ignore();
                        cout << "Enter amount" << endl;
                        cin >> amount;
                        bool valid;
                        try
                        {
                            a = stoi(amount);
                            if(a <= 0)
                            {
                                cout << "input must be atleast 1" << endl;
                                valid = false;
                            }
                            else
                            {
                                valid = true;
                            }
                        }
                        catch(...)
                        {
                            valid = false;
                            cout << "not a valid input" << endl;
                        }
                        if(valid)
                        {
                            candyData.exactSearchAmount(a);
                            break;
                        }
                    }
                }
                if(choose == "2")
                {
                    while(true)
                    {
                        bool valid;
                        string amount1;
                        string amount2;
                        double a1;
                        double a2;
                        cin.ignore();
                        cout << "Enter minimum amount" << endl;
                        cin >> amount1;
                        cout << "Enter maximum amount" << endl;
                        cin >> amount2;
                        try 
                        {
                            a1 = stoi(amount1);
                            a2 = stoi(amount2);
                            if(a1 <= 0 || a2 <= 0)
                            {
                                cout << "Input must be atleast 1" << endl;
                                valid = false;
                            }
                            else
                            {
                                valid = true;
                            }
                        }
                        catch(...)
                        {
                            cout << "Not a valid input" << endl;
                            valid = false;
                        }
                        if(valid)
                        {
                            candyData.rangeSearchAmount(a1, a2);
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Not a valid input" << endl;
                }
            }
            else if(choice == "4")
            {
                cout << "Search Method?\n" 
                << "1. Search by exact calories\n2. Search by calorie range" << endl;
                string choose;
                cin.ignore();
                cin >> choose;
                if(choose == "1")
                {
                    while(true)
                    {
                        string amount;
                        int a;
                        cin.ignore();
                        cout << "Enter calories" << endl;
                        cin >> amount;
                        bool valid;
                        try
                        {
                            a = stoi(amount);
                            if(a <= 0)
                            {
                                cout << "input must be atleast 1" << endl;
                                valid = false;
                            }
                            else
                            {
                                valid = true;
                            }
                        }
                        catch(...)
                        {
                            valid = false;
                            cout << "not a valid input" << endl;
                        }
                        if(valid)
                        {
                            candyData.exactSearchAmount(a);
                            break;
                        }
                    }
                }
                if(choose == "2")
                {
                    while(true)
                    {
                        bool valid;
                        string cal1;
                        string cal2;
                        double c1;
                        double c2;
                        cin.ignore();
                        cout << "Enter minimum amount" << endl;
                        cin >> cal1;
                        cout << "Enter maximum amount" << endl;
                        cin >> cal2;
                        try 
                        {
                            c1 = stod(cal1);
                            c2 = stod(cal2);
                            if(c1 <= 0 || c2 <= 0)
                            {
                                cout << "Input must be atleast 1" << endl;
                                valid = false;
                            }
                            else
                            {
                                valid = true;
                            }
                        }
                        catch(...)
                        {
                            cout << "Not a valid input" << endl;
                            valid = false;
                        }
                        if(valid)
                        {
                            candyData.rangeSearchCal(c1, c2);
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Not a valid input" << endl;
                }
            }
            else if(choice == "5")
            {
                cout << "Search Method?\n" 
                << "1. Search by exact price Per Piece\n2. Search by price range" << endl;
                string choose;
                cin.ignore();
                cin >> choose;
                if(choose == "1")
                {
                    while(true)
                    {
                        string price;
                        double p;
                        cin.ignore();
                        cout << "Enter price per piece" << endl;
                        cin >> price;
                        bool valid;
                        try
                        {
                            p = stod(price);
                            if(p <= 0)
                            {
                                cout << "Price cannot be 0 or less" << endl;
                                valid = false;
                            }
                            else
                            {
                                valid = true;
                            }
                        }
                        catch(...)
                        {
                            valid = false;
                            cout << "not a valid input" << endl;
                        }
                        if(valid)
                        {
                            candyData.exactSearchPricePer(p);
                            break;
                        }
                    }
                }
                if(choose == "2")
                {
                    while(true)
                    {
                        bool valid;
                        string price1;
                        string price2;
                        double p1;
                        double p2;
                        cin.ignore();
                        cout << "Enter minimum price per piece" << endl;
                        cin >> price1;
                        cout << "Enter maximum price per piece" << endl;
                        cin >> price2;
                        try 
                        {
                            p1= stod(price1);
                            p2 = stod(price2);
                            if(p1 <= 0 || p2 <= 0)
                            {
                                cout << "Price cannot be 0 or less" << endl;
                            }
                            valid = true;
                        }
                        catch(...)
                        {
                            cout << "Not a valid input" << endl;
                            valid = false;
                        }
                        if(valid)
                        {
                            candyData.rangeSearchPricePer(p1, p2);
                            break;
                        }
                    }
                }
                else
                {
                    cout << "Not a valid input" << endl;
                }
            }
            else if(choice == "6")
            {
                break;
            }
            else
            {
                cout << "Not a valid input" << endl;
            }
        }
    }

    void display()
    {
        while(true)
        {
            cout << "1. Display alphabetically by name\n" 
            << "2. Display by name reverse alphabetically"
            << "\n3. Display by price ascending\n4. Display by price descending" 
            << "\n5. Display by amount of candies per package ascending"
            << "\n6. Display by amount of candies per package descending" 
            << "\n7. Display by calories ascending\n8. Display by calories descending" 
            << "\n9. Back to main menu" << endl;
            string choice;
            cin.ignore();
            cin >> choice;
            if(choice == "1")
            {
                candyData.displayA(true);
            }
            else if(choice == "2")
            {
                candyData.displayA(false);
            }
            else if(choice == "3")
            {
                candyData.displayPrice(true);
            }
            else if(choice == "4")
            {
                candyData.displayPrice(false);
            }
            else if(choice == "5")
            {
                candyData.displayAmount(false);
            }
            else if(choice == "6")
            {
                candyData.displayAmount(true);
            }
            else if(choice == "7")
            {
                candyData.displayCal(false);
            }
            else if(choice == "8")
            {
                candyData.displayCal(true);
            }
            else if(choice == "9")
            {
                break;
            }
            else
            {
                cout << "Not a valid input" << endl;
            }
        }
    }
};
