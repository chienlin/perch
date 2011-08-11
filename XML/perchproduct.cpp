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


perchProduct::perchProduct(poXMLNode productNode)
{
    rootNode = productNode;//nth prodouct
    displaynum = 0;

    
    tb = new poTextBox(200,200);
    tb->textColor = poColor::white; 
    tb->text(rootNode.getChild("name").innerString())->layout();
//    tb->drawBounds = 1;
    addChild(tb);

    
}
void perchProduct::update()
{
    char buffer [50];
    if (displaynum > 5) displaynum = 0;
    
    switch (displaynum) {
        case 1:
            tb->text("name:"+rootNode.getChild("name").innerString())->layout();
            break;
        case 2:
            sprintf(buffer,"price:%d",rootNode.getChild("price").innerInt());
            tb->text(buffer)->layout();
            break;
        case 3:
            sprintf(buffer,"size:%d",rootNode.getChild("size").innerInt());
            tb->text(buffer)->layout();            
            break;
        case 4:
            tb->text("color:"+rootNode.getChild("color").innerString())->layout();
            break;
        case 5:
            tb->text("description:"+rootNode.getChild("description_short").innerString())->layout();
            break;
        default:
            tb->text("")->layout();
            break;
    }


}
void perchProduct::eventhandler(poEvent *E)
{



}
