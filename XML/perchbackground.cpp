//
//  background.cpp
//  XML
//
//  Created by chien on 8/9/11.
//  Copyright 2011 Potion Design. All rights reserved.
//

#include <iostream>
#include "perchbackground.h"
#include "poApplication.h"
#include "poResourceStore.h"
#include <boost/format.hpp>

perchbackground::perchbackground(poXMLNode node)
{

    poXMLNode framenode = node;
    std::string backgroundpicture = framenode.getChild("backgroundpicture").innerString();
    std::string logo = framenode.getChild("logo").innerString();
    
    poRectShape* R = new poRectShape(backgroundpicture);
    R->alignment(PO_ALIGN_TOP_LEFT);
    addChild(R);
    
    //logo
    poRectShape* logoR = new poRectShape(logo);
    logoR->alignment(PO_ALIGN_TOP_LEFT);
    addChild(logoR);



}

void perchbackground:: draw()
{



}
void perchbackground:: update()
{

}
void perchbackground::eventhandler(poEvent *E)
{



}