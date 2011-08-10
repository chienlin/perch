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


class perchProduct: public poObject
{
public:
    perchProduct(poXMLNode productNode, int perchFrameID);
    void eventhandler(poEvent *E);
    
    poXMLNode rootNode;
    //use perchFrameID to find the corresponding product info in product.xml (When perchFrameID(n) = <product frameID n>)
    int findPerchProduct(int perchFrameID);


};


#endif
