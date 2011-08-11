//
//  perchProduct.h
//  XML
//
//  Created by chien on 8/10/11.
//  Copyright 2011 Potion Design. All rights reserved.
//

#ifndef XML_perchproduct_h
#define XML_perchproduct_h

#include"poShapeBasics2D.h"
#include"poXML.h"
#include "poTextBox.h"

#include <iostream>
class perchProduct: public poObject
{
public:
    perchProduct(poXMLNode productNode);
    void eventhandler(poEvent *E);
    
    poXMLNode rootNode;
    poTextBox* tb;
    int displaynum;
    void update();


};


#endif
