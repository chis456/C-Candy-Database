#include <iostream>
#include <string>
using namespace std;

class Candy
{
    private:
    string name;
    double price;
    int amount;
    int calories;
    double pricePerPiece;

    public:
    Candy()
    {
        name = "";
        price = 0.0;
        amount = 0;
        calories = 0;
        pricePerPiece = 0;
    }
    Candy(string n, double p, int a, int c) : name(n), price(p), amount(a), calories(c)
    {
        pricePerPiece = price / amount;
    }

    string getName()
    {
        return name;
    }
    double getPrice()
    {
        return price;
    }
    int getAmount()
    {
        return amount;
    }
    int getCal()
    {
        return calories;
    }
    double pricePer()
    {
        return pricePerPiece;
    }
    void printc()
    {
        cout << name << " - $" << price << " - " << 
            amount << " pieces per package - " << calories << 
            " calories per package - $" << pricePerPiece << " per piece" << endl;
    }
};
