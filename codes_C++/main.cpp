/**
 * @file Vending Machine main file
 * 
 * @authors Eng. Mostafa Samy Mohammed,
 *          Eng. Ahmed Osama Elgendy,
 *          Eng. Ingy Ahmed Sherif
 * 
 * @brief This file contains the main function that runs the vending machine.
 * @version 0.8
 * @date 2023-12-30
 */
#include "LIB.h"            //Include the header file that contains all the libraries and classes needed for the program
#include "Product.h"        //Include the header file that contains the declaration of the Product class methods
#include "VendingMachine.h" //Include the header file that contains the declaration of the VendingMachine class methods

//Including namespace standard instead of writing std::
using namespace std;

//Function main which is the first function to be excuted when run the project
int main()
{
    //Create an object for the class VendingMachine
    VendingMachine *vendingMachine_ptr = new VendingMachine();

    //Call the function predefinedProducts
    vendingMachine_ptr->predefinedProducts();

    //Initiate variables to control the flow of the program
    char x, y = '0';
    cout << "Welcome to our Vending Machine! \n\nTo continue, press 0.\n\nFor programming mode, press 1.\n";
    cin >> x;

    //Choose which mode to enter
    if (!(cin.fail()) && x == '1')
    {
        int pass;
        cout << "\nEnter password: \n";

        //Check if the password is correct
        while (cin >> pass)
        {
            if (pass == 1234)
            {
                cout << "\t********Programming Mode********" << endl;

                //Calling the functions that the programmer might need
                vendingMachine_ptr->viewDefectProducts(); //Makes all products visible for the vendor
                vendingMachine_ptr->addProduct();         //Allows the vendor to add products
                vendingMachine_ptr->removeProduct();      //Allows the vendor to remove products
                vendingMachine_ptr->editPrice();          //Allows the vendor to edit a product's price

                break;                               //Exits the while loop to enter the next mode or exit the machine.
            }
            else if (pass == 0) break;
            else cout << "Password is wrong. Click 0 to exit.\n";
        }

        //Choose the next destination for the user
        cout << "\nClick 0 to enter operating mode, or click 1 to exit.\n";
        cin >> y;

        if (y == '1') return 0;   //If user chose to exit, the program shuts down.
    }

    //Enters the operating mode
    if (y == '0')
    {
        char choice;

        //Enter the function at least one time
        do
        {
            vendingMachine_ptr->displayProducts();       //Displays available product to the customer
            vendingMachine_ptr->chooseProduct();         //Choose a product to buy

            cout << "\nWould you like to get another product? (y/n)\n";
            cin >> choice;
        }
        while (choice == 'y' || choice == 'Y');

        //Ends the program
        cout << "Thank you for choosing our Vending Machine!\n";

    }
    return 0;
}
