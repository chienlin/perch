//
//  perchProduct.cpp
//  XML
//
//  Created by chien on 8/10/11.
//  Copyright 2011 Potion Design. All rights reserved.
//

#include <iostream>
#include "poApplication.h"
#include "perchProduct.h"


perchProduct::perchProduct(poXMLNode perchProductNode, int perchFrameID)
{
    rootNode = perchProductNode;
    int a =findPerchProduct(perchFrameID);//a = nth perchProduct

    
    poTextBox* tb = new poTextBox(150,150);
    tb->textColor = poColor::white; 
    tb->text(rootNode.getChild(a).getChild("description_short").innerString())->layout();
 //   tb->position = tb->parent()->position/2;

    addChild(tb);

    
}
int perchProduct::findPerchProduct(int ID)
{
    for (int i = 0; i<rootNode.numChildren(); i++) {
       if(rootNode.getChild(i).intAttribute("frameID") == ID) return i;
    }

}