/**
 * @file Product.cpp
 * 
 * @authors Eng. Mostafa Samy Mohammed,
 *          Eng. Ahmed Osama Elgendy,
 *          Eng. Ingy Ahmed Sherif
 * 
 * @brief This file contains the implementation of the Product class methods.
 * @see Product.h
 * @version 0.4
 * @date 2023-12-30
 */
#include "LIB.h"
#include "Product.h"

using namespace std;

Product::Product(string _name, float _price, int _count, string _expirationDate, int _outlet)
{
    name = _name;
    price = _price;
    count = _count;
    expirationDate = _expirationDate;
    outlet = _outlet;
}

Product::Product()
{
    //Default constructor
}
