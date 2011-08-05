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
    //control button
    poRectShape* controlbun;
    poImage* controlImg;   
    //save button
    poRectShape* savebun;
    poImage* saveImg;
    perchFrame* F[100];



    bool controlbun_click;
    bool savebun_click;
    void update();




    bool control;
   

};