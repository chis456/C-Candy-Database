using namespace std;
#include <vector>
#include <iostream>
#include "Candy.cpp"
#include <fstream>
#include <stdio.h>
#include <algorithm>
class Database
{
    private:
    vector<Candy> list;
    public:
    //constructor
    Database()
    {
        ifstream dataFile("list.txt");
        while(true)
        {
            if(dataFile.eof())
            {
                break;
            }
            string name = "";
            string priceStr = "";
            double price = 0.0;
            string amountStr = "";
            int amount = 0;
            string calStr = "";
            int calories = 0;
            string next = "";
            getline(dataFile, next);

            //loads each piece of data based on comma position, with quotations to allow for commas to be in the name
            if(next != "")
            {
                int quoteCount = 0;
                while(true)
                {
                    if(next.at(0) == '"')
                    {
                        quoteCount++;
                        if(quoteCount == 1)
                        {
                            next.erase(next.begin());
                        }
                        if(quoteCount == 2)
                        {
                            next.erase(next.begin(), next.begin() + 2);
                            break;
                        }
                    }
                    else if(next.at(0) != '"')
                    {
                        name.push_back(next.at(0));
                        next.erase(next.begin());
                    }
                }
                while(true)
                {
                    if(next.at(0) == ',')
                    {
                        next.erase(next.begin(), next.begin() + 1);
                        break;
                    }
                    priceStr.push_back(next.at(0));
                    next.erase(next.begin());
                }
                price = stod(priceStr);
                while(true)
                {
                    if(next.at(0) == ',')
                    {
                        next.erase(next.begin(), next.begin() + 1);
                        break;
                    }
                    amountStr.push_back(next.at(0));
                    next.erase(next.begin());
                }
                amount = stoi(amountStr);
                for(int i = 0; i < next.size(); i++)
                {
                    calStr.push_back(next.at(i));
                }
                calories = stoi(calStr);

                Candy newCandy(name, price, amount, calories);
                list.push_back(newCandy);
            }
        }
        dataFile.close();
    }

    vector<Candy> getList()
    {
        return list;
    }

    void add(Candy c)
    {
        list.push_back(c);
    }

    vector<Candy> findAndPrint(string name) //search based on keyword
    {
        vector<Candy> foundCandies;
        bool found = false;
        for(int i = 0; i < list.size(); i++)
        {
            if(list.at(i).getName().find(name) != string::npos)
            {
                found = true;
                Candy c = list.at(i);
                c.printc();
                foundCandies.push_back(c);
            }
        }
        if(!found)
        {
            cout << "No candies with the name " << "\'" << name << "\'" << " were found" << endl;
        }
        return foundCandies;
    }

    int exactSearch(string name, bool single) //search based on exact name
    {
        bool found = false;
        for(int i = 0; i < list.size(); i++)
        {
            if(list.at(i).getName() == name)
            {
                found = true;
                Candy c = list.at(i);
                c.printc();
                if(single)
                {
                    break;
                }
            }
        }
        if(!found)
        {
            cout << "No candies with the name " << "\'" << name << "\'" << " were found" << endl;
            return -1;
        }
        return 0;
    }
    
    int exactSearch(double price) //search based on exact price
    {
        bool found = false;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            double p = c.getPrice();
            if(p == price)
            {
                found = true;
                c.printc();
                break;
            }
        }
        if(!found)
        {
            cout << "No candies with the price " << "$" << price << " were found" << endl;\
            return -1;
        }
        return 0;
    }

    vector<Candy> rangeSearchPrice(double price1, double price2) //search based on range of prices
    {
        vector<Candy> candies;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            double p = c.getPrice();
            if(p >= price1 && p <= price2)
            {
                c.printc();
                candies.push_back(c);
            }
        }
        if(candies.size() == 0)
        {
            cout << "No candies within the price range $" << price1 << " - $" << price2 << endl;
        }
        return candies;
    }

    vector<Candy> rangeSearchAmount(int a1, int a2) //search based on range of amounts
    {
        vector<Candy> candies;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            if(a1 <= c.getAmount() && a2 >= c.getAmount())
            {
                c.printc();
                candies.push_back(c);
            }
        }
        if(candies.size() == 0)
        {
            cout << "No candies within the range " << a1 << " - " 
            << a2 << " candies per package were found" << endl;
        }
        return candies;
    }

    int exactSearchAmount(int amount) //search based on exact amount
    {
        bool found = false;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            if(amount == c.getAmount())
            {
                found = true;
                c.printc();
                break;
            }
        }
        if(!found)
        {
            cout << "No candies with " << amount << " candies per package were found" << endl;
            return -1;
        }
        return 0;
    }

    int exactSearchCal(int calories) //search based on exact calorie count
    {
        bool found = false;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            if(calories == c.getCal())
            {
                found = true;
                c.printc();
                break;
            }
        }
        if(!found)
        {
            cout << "No candies with " << calories << " calories per package were found" << endl;
            return -1;
        }
        return 0;
    }
    vector<Candy> rangeSearchCal(int c1, int c2) //search based on range of calories
    {
        vector<Candy> candies;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            if(c1 <= c.getCal() && c2 >= c.getCal())
            {
                c.printc();
                candies.push_back(c);
            }
        }
        if(candies.size() == 0)
        {
            cout << "No candies within the range " << c1 << " to "
            << c2 << " calories per package were found" << endl;
        }
        return candies;
    }

    int exactSearchPricePer(double price) //search based on exact price per piece
    {
        bool found = false;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            double p = c.pricePer();
            if(p == price)
            {
                found = true;
                c.printc();
                break;
            }
        }
        if(!found)
        {
            cout << "No candies with " << "$" << price 
            << " per candy were found" << endl;
            return -1;
        }
        return 0;
    }
    //search based on range of price per piece
    vector<Candy> rangeSearchPricePer(double price1, double price2) 
    {
        vector<Candy> candies;
        for(int i = 0; i < list.size(); i++)
        {
            Candy c = list.at(i);
            double p = c.pricePer();
            if(p >= price1 && p <= price2)
            {
                c.printc();
                candies.push_back(c);
            }
        }
        if(candies.size() == 0)
        {
            cout << "No candies within the price per piece range " 
            << price1 << " - " << price2 << " " << endl;
        }
        return candies;
    }
    //alphbetically (or reverse alphabetically) display all entries
    void displayA(bool alphabetically) 
    {
        vector<Candy> candies = list;
        
        for(int i = 0; i < candies.size(); i++)
        {
            for(int j = 1; j < candies.size() - i; j++)
            {
                if(candies.at(j - 1).getName() > candies.at(j).getName())
                {
                    Candy temp = candies.at(j);
                    candies.at(j) = candies.at(j - 1);
                    candies.at(j - 1) = temp;
                }
            }
        }
        if(!alphabetically)
        {
            for(int i = 0; i < candies.size() / 2; i++)
            {
                Candy temp = candies.at(i);
                candies.at(i) = candies.at(candies.size() - i - 1);
                candies.at(candies.size() - i - 1) = temp;
            }
        }
        for(int i = 0; i < candies.size(); i++)
        {
            candies.at(i).printc();
        }
    }
    //display all entries from lowest to highest price (or vice versa)
    void displayPrice(bool ascending) 
    {
        vector<Candy> candies = list;
        for(int i = 0; i < candies.size(); i++)
        {
            for(int j = 1; j < candies.size() - i; j++)
            {
                if(candies.at(j - 1).getPrice() > candies.at(j).getPrice())
                {
                    Candy temp = candies.at(j);
                    candies.at(j) = candies.at(j - 1);
                    candies.at(j - 1) = temp;
                }
            }
        }
        if(!ascending)
        {
            for(int i = 0; i < candies.size() / 2; i++)
            {
                Candy temp = candies.at(i);
                candies.at(i) = candies.at(candies.size() - i - 1);
                candies.at(candies.size() - i - 1) = temp;
            }
        }
        for(int i = 0; i < candies.size(); i++)
        {
            candies.at(i).printc();
        }
    }
    //display all entries from lowest to highest calories (or vice versa)
    void displayCal(bool ascending) 
    {
        vector<Candy> candies = list;
        for(int i = 0; i < candies.size(); i++)
        {
            for(int j = 1; j < candies.size() - i; j++)
            {
                if(candies.at(j - 1).getCal() > candies.at(j).getCal())
                {
                    Candy temp = candies.at(j);
                    candies.at(j) = candies.at(j - 1);
                    candies.at(j - 1) = temp;
                }
            }
        }
        if(!ascending)
        {
            for(int i = 0; i < candies.size() / 2; i++)
            {
                Candy temp = candies.at(i);
                candies.at(i) = candies.at(candies.size() - i - 1);
                candies.at(candies.size() - i - 1) = temp;
            }
        }
        for(int i = 0; i < candies.size(); i++)
        {
            candies.at(i).printc();
        }
    }
    //display all entries from lowest to highest amount (or vice versa)
    void displayAmount(bool ascending) 
    {
        vector<Candy> candies = list;
        for(int i = 0; i < candies.size(); i++)
        {
            for(int j = 1; j < candies.size() - i; j++)
            {
                if(candies.at(j - 1).getAmount() > candies.at(j).getAmount())
                {
                    Candy temp = candies.at(j);
                    candies.at(j) = candies.at(j - 1);
                    candies.at(j - 1) = temp;
                }
            }
        }
        if(!ascending)
        {
            for(int i = 0; i < candies.size() / 2; i++)
            {
                Candy temp = candies.at(i);
                candies.at(i) = candies.at(candies.size() - i - 1);
                candies.at(candies.size() - i - 1) = temp;
            }
        }
        for(int i = 0; i < candies.size(); i++)
        {
            candies.at(i).printc();
        }
    }

    //create and add candy to list.txt and candy vector based on inputted data from user
    void addCandy() 
    {
        string name;
        string priceS;
        string amountS;
        string caloriesS;

        ofstream dataFile;
        string dataLine = "\n";

        dataFile.open("list.txt", std::ios_base::app);
        cout << "Enter name of Candy:" << endl;
        cin.ignore();
        getline(cin, name);
        dataLine.append('"' + name + '"' + ", ");

        double price;
        while(true)
        {
            bool valid;
            cout << "Enter price of Candy:" << endl;
            cin >> priceS;
            try
            {
                price = stod(priceS);
                if(price <= 0)
                {
                    cout << "Price must be atleast a non-zero positive number" << endl;
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
                dataLine.append(priceS + ", ");
                price = stod(priceS);
                break;
            }
        }

        int amount;
        while(true)
        {
            bool valid;
            cout << "Enter number of candies per package:" << endl;
            cin >> amountS;
            try
            {
                amount = stoi(amountS);
                if(amount <= 0)
                {
                    cout << "Amount must be atleast 1" << endl;
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
                dataLine.append(amountS + ", ");
                amount = stoi(amountS);
                break;
            }
        }

        int calories;
        while(true)
        {
            bool valid;
            cout << "Enter number of calories per package:" << endl;
            cin >> caloriesS;
            try
            {
                calories = stoi(caloriesS);
                if(calories <= 0)
                {
                    cout << "Calories must be atleast 1" << endl;
                    valid = false;
                }
                else
                {
                    valid = true;
                }
            }
            catch(...)
            {
                cout << "not a valid input" << endl;
                valid = false;
            }
            if(valid)
            {
                dataLine.append(caloriesS);
                calories = stoi(caloriesS);
                break;
            }
        }

        bool alreadyExists = false;
        ifstream data("list.txt");
        while(true)
        {
            if(data.fail())
            {
                break;
            }
            string nextLine;
            string realNextLine = "\n";
            getline(data, nextLine);
            realNextLine.append(nextLine);
            if(realNextLine == dataLine)
            {
                cout << "This candy already exists in the database" << endl;
                alreadyExists = true;
            }
        }
        data.close();
        if(!alreadyExists)
        {
            Candy candy(name, price, amount, calories);
            list.push_back(candy);
            dataFile << dataLine;
            cout << dataLine << endl;
            dataFile.close();

            cout << name << " has been added to the Database" << endl;
        }
    }
    //remove candy from list.txt and candy vector based on name of candy
    void removeCandy(string name) 
    {
        string lineDel;
        ifstream dataFile("list.txt");
        while(true)
        {
            if(dataFile.eof())
            {
                break;
            }
            string nextLine;
            string nextName;
            getline(dataFile, nextLine);
            for(int i = 0; i < nextLine.size(); i++)
            {
                if(nextLine.at(i) == ',')
                {
                    break;
                }
                if(nextLine.at(i) != '"')
                {
                    nextName.push_back(nextLine.at(i));
                }
            }
            if(nextName == name)
            {
                lineDel = nextLine;
                break;
            }
        }
        dataFile.close();
        string lineData;
        ifstream data("list.txt"); //create temporary txt file
        ofstream temp("temp.txt");

        while(true)
        {
            if(data.eof())
            {
                break;
            }
            string nextLine;
            getline(data, nextLine);
            if(nextLine != lineDel)
            {
                temp << nextLine << endl; 
                //copy all entries except 
                //the one to be deleted into the temporary txt file
            }
        }
        data.close();
        temp.close();
        //delete list.txt and rename temporary txt file
        //to list.txt
        remove("list.txt");
        rename("temp.txt", "list.txt");
        Candy toRemove;
        for(int i = 0; i < list.size(); i++)
        {
            if(name == list.at(i).getName())
            {
                toRemove = list.at(i);
                list.erase(list.begin() + i);
            }
        }
        cout << name << " has been removed" << endl;
    }

    void removeCandy(double price) //remove candy based on price 
    //same algorithm as removeCandy(string name)
    {
        double p;
        string lineDel = "";
        ifstream dataFile("list.txt");
        while(true)
        {
            if(dataFile.eof())
            {
                break;
            }
            string nextLine;
            string nextPrice;
            getline(dataFile, nextLine);
            if(nextLine == "")
            {
                continue;
            }
            string nextLineClone = nextLine;
            int quoteCount = 0;
            while(true)
            {
                if(nextLineClone.at(0) == '"')
                {
                    quoteCount++;
                    if(quoteCount == 2)
                    {
                        nextLineClone.erase(nextLineClone.begin(), nextLineClone.begin() + 2);
                        break;
                    }
                }
                nextLineClone.erase(nextLineClone.begin());
            }
            for(int i = 0; i < nextLineClone.size(); i++)
            {
                if(nextLineClone.at(i) == ',')
                {
                    break;
                }
                nextPrice.push_back(nextLineClone.at(i));
            }
            p = stod(nextPrice);
            if(p == price)
            {
                lineDel = nextLine;
                break;
            }
        }
        dataFile.close();
        ifstream data("list.txt");
        ofstream temp("temp.txt");
        if(lineDel != "")
        {
            while(true)
            {
                if(data.eof())
                {
                    break;
                }
                string nextLine;
                getline(data, nextLine);
                if(nextLine != lineDel)
                {
                    temp << nextLine << endl;
                }
            }
            data.close();
            temp.close();
            remove("list.txt");
            rename("temp.txt", "list.txt");
            string remove;
            for(int i = 0; i < list.size(); i++)
            {
                if(p == list.at(i).getPrice())
                {
                    remove = list.at(i).getName();
                    list.erase(list.begin() + i);
                    break;
                }
            }
            cout << remove << " has been removed" << endl;
        }
        else
        {
            cout << "No entries with price " << price << " were found" << endl;
        }
    }

    void removeCandy(int amount) //remove candy based on amount
    //same algorithm as removeCandy(string name)
    {
        int a;
        string lineDel = "";
        ifstream dataFile("list.txt");
        while(true)
        {
            if(dataFile.eof())
            {
                break;
            }
            string nextLine;
            string nextAmount;
            getline(dataFile, nextLine);
            if(nextLine == "")
            {
                continue;
            }
            string nextLineClone = nextLine;
            int quoteCount = 0;
            while(true)
            {
                if(nextLineClone.at(0) == '"')
                {
                    quoteCount++;
                    if(quoteCount == 2)
                    {
                        nextLineClone.erase(nextLineClone.begin(), nextLineClone.begin() + 2);
                        break;
                    }
                }
                nextLineClone.erase(nextLineClone.begin());
            }
            while(true)
            {
                if(nextLineClone.at(0) == ',')
                {
                    nextLineClone.erase(nextLineClone.begin(), nextLineClone.begin() + 1);
                    break;
                }
                nextLineClone.erase(nextLineClone.begin());
            }
            for(int i = 0; i < nextLineClone.size(); i++)
            {
                if(nextLineClone.at(i) == ',')
                {
                    break;
                }
                nextAmount.push_back(nextLineClone.at(i));
            }
            a = stoi(nextAmount);
            if(a == amount)
            {
                lineDel = nextLine;
                break;
            }
        }
        dataFile.close();
        ifstream data("list.txt");
        ofstream temp("temp.txt");
        if(lineDel != "")
        {
            while(true)
            {
                if(data.eof())
                {
                    break;
                }
                string nextLine;
                getline(data, nextLine);
                if(nextLine != lineDel)
                {
                    temp << nextLine << endl;
                }
            }
            data.close();
            temp.close();
            remove("list.txt");
            rename("temp.txt", "list.txt");
            string remove;
            for(int i = 0; i < list.size(); i++)
            {
                if(a == list.at(i).getAmount())
                {
                    remove = list.at(i).getName();
                    list.erase(list.begin() + i);
                    break;
                }
            }
            cout << remove << " has been removed" << endl;
        }
        else
        {
            cout << "No entries with amount " << amount << " were found" << endl;
        }
    }

    void removeCandyCal(int cal) //remove candy based on calories
    //same algorithm as removeCandy(string name)
    {
        int c;
        string lineDel = "";
        ifstream dataFile("list.txt");
        while(true)
        {
            if(dataFile.eof())
            {
                break;
            }
            string nextLine;
            string nextCal;
            getline(dataFile, nextLine);
            if(nextLine == "")
            {
                continue;
            }
            string nextLineClone = nextLine;
            int quoteCount = 0;
            while(true)
            {
                if(nextLineClone.at(0) == '"')
                {
                    quoteCount++;
                    if(quoteCount == 2)
                    {
                        nextLineClone.erase(nextLineClone.begin(), nextLineClone.begin() + 2);
                        break;
                    }
                }
                nextLineClone.erase(nextLineClone.begin());
            }
            while(true)
            {
                if(nextLineClone.at(0) == ',')
                {
                    nextLineClone.erase(nextLineClone.begin(), nextLineClone.begin() + 1);
                    break;
                }
                nextLineClone.erase(nextLineClone.begin());
            }
            while(true)
            {
                if(nextLineClone.at(0) == ',')
                {
                    nextLineClone.erase(nextLineClone.begin(), nextLineClone.begin() + 1);
                    break;
                }
                nextLineClone.erase(nextLineClone.begin());
            }
            for(int i = 0; i < nextLineClone.size(); i++)
            {
                if(nextLineClone.at(i) == ',')
                {
                    break;
                }
                nextCal.push_back(nextLineClone.at(i));
            }
            c = stoi(nextCal);
            if(c == cal)
            {
                lineDel = nextLine;
                break;
            }
        }
        dataFile.close();
        ifstream data("list.txt");
        ofstream temp("temp.txt");
        if(lineDel != "")
        {
            while(true)
            {
                if(data.eof())
                {
                    break;
                }
                string nextLine;
                getline(data, nextLine);
                if(nextLine != lineDel)
                {
                    temp << nextLine << endl;
                }
            }
            data.close();
            temp.close();
            remove("list.txt");
            rename("temp.txt", "list.txt");
            string remove;
            for(int i = 0; i < list.size(); i++)
            {
                if(c == list.at(i).getCal())
                {
                    remove = list.at(i).getName();
                    list.erase(list.begin() + i);
                    break;
                }
            }
            cout << remove << " has been removed" << endl;
        }
        else
        {
            cout << "No entries with " << cal << " calories were found" << endl;
        }
    }
};