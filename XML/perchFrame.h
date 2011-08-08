//
//  perchFrame.h
//  XML
//
//  Created by chien on 8/2/11.
//  Copyright 2011 Potion Design. All rights reserved.
//

#ifndef XML_perchFrame_h
#define XML_perchFrame_h

#include "poShapeBasics2D.h"
#include "poXML.h"
#include "poTextbox.h"

class perchFrame : public poObject
{
public:
     
    perchFrame( poXMLNode node);
    void eventHandler( poEvent* E );
    void draw();
    void update();
    
    
    poXMLNode   frameNode;
    //main rect
    poRectShape* R;
    //textbox for rect info
    poTextBox* tb;
    //small green rect to control scale
    poRectShape* SR1;
   
    // the switch to turn on control function or turn off
    bool controlswitch;
    // make all frames aligned to x
    bool alignhorizontal;
    // make all frames aligned to y
    bool alignvertical;
    int num;
};



#endif
