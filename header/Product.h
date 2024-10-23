/**
 * @file Product.h
 * 
 * @authors Eng. Mostafa Samy Mohammed,
 *          Eng. Ahmed Osama Elgendy,
 *          Eng. Ingy Ahmed Sherif
 * 
 * @brief   This header file contains the declaration of the Product class-
 *          -which is used to store the information of a product.
 *          The information includes the name of the product, the price, its count, expiration date,-
 *          -and number of outlet the product come out of.
 * @version 0.4
 * @date 2023-12-30
*/
#ifndef PRODUCT_H
#define PRODUCT_H

#include "LIB.h"

using namespace std;


class Product
{
public:
    string name;
    float price;
    int count;
    string expirationDate;
    int outlet;

    Product(string _name, float _price, int _count, string _expirationDate, int _outlet);
    Product();
};
#endif
