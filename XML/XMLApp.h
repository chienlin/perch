/*	Created by Joshua Fisher on 7/7/11.
 *	Copyright 2011 Potion Design. All rights reserved.
 */

#include "poObject.h"
#include "perchFrame.h"


class XMLApp : public poObject {
    
public:
	XMLApp();
    void update();
    void eventHandler( poEvent* E );
    
    poXMLDocument doc;
    poXMLNode rootNode;
    //control button
    poRectShape* controlbun;
    poImage* controlImg;   
    //save button
    poRectShape* savebun;
    poImage* saveImg;
    
  
    //align button
    poRectShape* alignbun;


    perchFrame* F[100];
    bool controlbun_click;
    bool savebun_click;
  




    bool control;
   

};