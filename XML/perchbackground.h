//
//  background.h
//  XML
//
//  Created by chien on 8/9/11.
//  Copyright 2011 Potion Design. All rights reserved.
//

#ifndef XML_background_h
#define XML_background_h
#include "poShapeBasics2D.h"
#include "poXML.h"

class perchbackground : public poObject
{
public:
    perchbackground(poXMLNode node);
    void draw();
    void update();
    void eventhandler(poEvent* E);




};

#endif
