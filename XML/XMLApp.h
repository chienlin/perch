/*	Created by Chien on 7/7/11.
 *	Copyright 2011 Potion Design. All rights reserved.
 */

#include "poObject.h"
#include "perchFrame.h"
#include <list>
using namespace std;

typedef list<perchFrame*> LIST;

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
    
  
    //add frame button
    poRectShape* addbun;
    poImage* addImg;
    
    //delete frame button
    poRectShape* deletebun;
    poImage* deleteImg;

    perchFrame* F;
    
//    perchFrame* F[100];
    bool controlbun_click;
    bool savebun_click;
  

    //create a list to store perchframe objects
    LIST::iterator iter;
    LIST framelist;


    bool control;
   

};