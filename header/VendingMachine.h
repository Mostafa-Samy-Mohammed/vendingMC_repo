/**
 * @file VendingMachine.h
 * 
 * @authors Eng. Mostafa Samy Mohammed,
 *          Eng. Ahmed Osama Elgendy,
 *          Eng. Ingy Ahmed Sherif
 * 
 * @brief This header file contains the declaration of the VendingMachine class methods.
 * @version 0.6
 * @date 2023-12-30
 */
#ifndef VENDINGMC_H
#define VENDINGMC_H

#include "LIB.h"
#include "Product.h"

using namespace std;

class VendingMachine
{
private:

    vector<Product> products;

public:
    bool checkExpirationDate(Product *product) const;
    void displayProducts() const;
    void addProduct();
    void removeProduct();
    void viewDefectProducts() const;
    void chooseProduct();
    void predefinedProducts();
    void editPrice();
};
#endif
