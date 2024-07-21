/**
 * @file VendingMachine.cpp
 * @brief This file contains the implementation of the VendingMachine class methods.
 * @see VendingMachine.h
 * @version 0.6
 * @date 2023-12-30
 */
#include "LIB.h"
#include "Product.h"
#include "VendingMachine.h"

using namespace std;

/**
 * @brief Check if the products are expired or not
 *
 */
bool VendingMachine::checkExpirationDate(Product *product) const
{
    int expiryY, expiryM, expiryD, yearDifference, monthDifference, dayDifference;
    // Get the current time
    time_t currentTime;
    time(&currentTime);
    struct tm current = *localtime(&currentTime);

    // conversion of the expiration date to integer and put the year / month / day in different variables
    expiryY = atoi(product->expirationDate.substr(6, 4).c_str());
    expiryM = atoi(product->expirationDate.substr(3, 2).c_str());
    expiryD = atoi(product->expirationDate.substr(0, 2).c_str());

    //calculate the difference between the current date and the expiry date
    monthDifference = (expiryM) - (current.tm_mon + 1);
    yearDifference  = (expiryY) - (current.tm_year + 1900);
    dayDifference   = (expiryD) - (current.tm_mday);

    if (yearDifference < 0 || (yearDifference == 0 && monthDifference < 0) || (yearDifference == 0 && monthDifference == 0 && dayDifference < 0))
    {
        return false;
    }
    return true;

}

/**
* Displays products for the customer to select from
*/
void VendingMachine::displayProducts() const
{
    Product *product_ptr = new Product();

    cout << "Available Products: " << endl;
    for (int i = 0; i < products.size(); i++)
    {
        *product_ptr = products[i];
        //check if the product is not expired or out of stock
        if ((checkExpirationDate(product_ptr)) && product_ptr->count > 0)
        {
            cout << "Product " << i << ": \nName: " << product_ptr->name << ", Price: " << product_ptr->price << ", Count: " << product_ptr->count << "\n\n";
        }
    }
    delete product_ptr;
}

//function used by the vendor to add products
void VendingMachine::addProduct()
{
    string name;
    float price;
    int count;
    int outlet;
    string expirationDate;

    char choice;
    cout << "Do you want to add a product? (y/n): ";

    Product *product_ptr = new Product();

    while (cin >> choice)
    {

        if(choice == 'y' || choice == 'Y')
        {
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product price: ";
            cin >> price;
            cout << "Enter product count: ";
            cin >> count;
            cout << "Enter outlet used to dispense the product (1 for Juice, 2 for Water, 3 for Soda): ";
            cin >> outlet;
            cout << "Enter product expiration date (dd/mm/yyyy): ";
            cin >> expirationDate;

            product_ptr->expirationDate = expirationDate;
            //check if the added product is not expired
            if (checkExpirationDate(product_ptr))
            {
                products.push_back(Product(name, price, count, expirationDate, outlet));
            }
            else
            {
                cout << "\nThis product is expired. \n\n";
            }
            cout << "\nDo you want to add another product? (y/n): ";
        }
        else
        {
            break;
        }
    }
    delete product_ptr;
}

//function used by the vendor to view the expired or out of stock products and easily handle it
void VendingMachine::viewDefectProducts() const
{
    Product *product_ptr = new Product();

    for (int i=0; i<products.size(); i++)
    {
        *product_ptr = products[i];
        //out of stock condition
        if (product_ptr->count <= 0)
        {
            cout << "WATCH OUT!! Product " << i << " " << product_ptr->name << " is out of stock. Resupply it.\n\n";
        }
        //expired condition
        else if (!(checkExpirationDate(product_ptr)))
        {
            cout << "WATCH OUT!! Product " << i << " " << product_ptr->name << " is expired. Remove it please.\n\n";
        }
    }
    delete product_ptr;
}

//function used by the vendor to remove products
void VendingMachine::removeProduct()
{
    char choice;
    int productNumber;
    cout << "\nDo you want to remove a product? (y/n): ";
    cin >> choice;
    while (choice == 'y' || choice == 'Y')
    {
        //Display all the products to let the vendor choose which product to edit its price
        for (int i = 0; i < products.size(); i++) cout << "Product " << i << ": \nName: " << products[i].name << ", Price: " << products[i].price << ", Count: " << products[i].count << "\n\n";

        cout << "Please enter the product's number you want to remove: ";
        // removing the element from the vector and rearranging it
        while (cin >> productNumber)
        {

            if (productNumber < products.size())
            {
                for (int i = productNumber; i < products.size() - 1; i++)
                {
                    products[i] = products[i + 1];
                }
                products.pop_back();
                break;
            }
            else
                cout << "Wrong number, this product doesn't exist, try again... ";
        }
        viewDefectProducts();
        cout << "\nDo you want to remove another product? (y/n): ";
        cin >> choice;
    }
}

//function used by the customer to choose the valid products
void VendingMachine::chooseProduct()
{
    cout<< "Which product would you like to choose?\n";
    int choice;
    cin>>choice;

    if (!(cin.fail()) && choice >= 0 && choice < products.size())
    {
        Product *product_ptr = new Product();
        *product_ptr = products[choice];
        //check if the product is not expired or out of stock
        if (checkExpirationDate(product_ptr) && product_ptr->count > 0)
        {
            cout << "Please enter " << product_ptr->price << " LE in the money input slot.\n";
            double moneyIn, moreMoney;
            cin>> moneyIn;
            while (moneyIn < product_ptr->price)
            {
                cout << "Please enter "<< product_ptr->price - moneyIn << " LE in the money input slot.";
                cin >> moreMoney;
                moneyIn+=moreMoney;
            }
            if(moneyIn >= product_ptr->price)
            {
                cout << "Get your "<< product_ptr->name<< " from vending slot number " << product_ptr->outlet
                     << ".\nYou'll receive " << moneyIn - product_ptr->price << " LE from the money output slot.\n";
                product_ptr->count --;
            }
            delete product_ptr;
        }
        else
        {
            cout << "\nProduct is not available. \n\n";
            chooseProduct();
        }
    }
    else
    {
        cout << "Product doesn't exist, try again... \n";
        chooseProduct();
    }
}

//function used by the vendor to edit the price of products
void VendingMachine::editPrice()
{
    char choice;
    int _product;
    float newPrice;

    cout << "\nDo you want to edit a product's price? (y/n): ";
    while (cin >> choice)
    {
        if (choice == 'y' || choice == 'Y')
        {
            //Display all the products to let the vendor choose which product to edit its price
            for (int i = 0; i < products.size(); i++) cout << "Product " << i << ": \nName: " << products[i].name << ", Price: " << products[i].price << ", Count: " << products[i].count << "\n\n";

            cout<< "\nWhich product would you like to edit its price?\n";
            cin >> _product;

            //check if the product's number exist and edit the price
            if (_product >= 0 && _product < products.size())
            {
                cout << "\nPlease enter the new price: \n";
                cin >> newPrice;

                products[_product].price = newPrice;

                cout << "\nThe price have changed :)\n";
                cout << "Do you want to edit another product's price? (y/n): ";
            }
            else
            {
                cout << "Product doesn't exist.\n";
                editPrice();
            }
        }
        else break;
    }
}

// Products in the vending machine to check the program with every time we run the project
void VendingMachine::predefinedProducts()
{
    products.push_back(Product("Orange Juice", 2.5, 5, "31-12-2024", 1));

    products.push_back(Product("Apple Juice", 3.0, 1, "31-12-2024", 1));

    products.push_back(Product("Mini Water", 1.0, 10, "31-12-2022", 2));

    products.push_back(Product("Large Water", 1.5, 5, "31-12-2024", 2));

    products.push_back(Product("Pepsi", 2.0, 0, "31-12-2024", 3));

    products.push_back(Product("7UP", 2.0, 6, "31-12-2024", 3));
}
