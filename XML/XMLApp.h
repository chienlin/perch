/*	Created by Chien on 7/7/11.
 *	Copyright 2011 Potion Design. All rights reserved.
 */

#include "poObject.h"
#include "perchFrame.h"
#include "perchbackground.h"
#include <list>
using namespace std;

typedef list<perchFrame*> LIST;

class XMLApp : public poObject {
    
public:
	XMLApp();
    void update();
    void eventHandler( poEvent* E );
    
    poXMLDocument doc_frames;//frame.xml
    poXMLNode rootNode_frames;//rootNode for frame.xml
    poXMLDocument doc_product;//product.xml
    poXMLNode rootNode_product;//rootNode for product.xml

    
    
    
    
    //control button
    poRectShape* controlbun;
    poImage* controlImg;
    bool controlbun_click;
    
    //save button
    poRectShape* savebun;
    poImage* saveImg;
    bool savebun_click;
  
    //add frame button
    poRectShape* addbun;
    poImage* addImg;
    
    //delete frame button
    poRectShape* deletebun;
    poImage* deleteImg;

    perchFrame* F;
    //create a list to store perchframe objects
    LIST::iterator iter;
    LIST framelist;
    
    


    void addnewframe(poXMLNode oriRootNode_frames,poXMLNode oriRootNode_product);

   

};