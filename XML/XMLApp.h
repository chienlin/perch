/*	Created by Joshua Fisher on 7/7/11.
 *	Copyright 2011 Potion Design. All rights reserved.
 */

#include "poObject.h"
#include "perchFrame.h"


class XMLApp : public poObject {
    
public:
	XMLApp();
    void eventHandler( poEvent* E );
    
    poXMLDocument doc;
    poRectShape* controlbun;
    perchFrame* F[100];


    
    int clicknum;
    int clicknum1;

    bool control;
   

};