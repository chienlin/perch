#include "XMLApp.h"
#include "poApplication.h"
#include "poCamera.h"

#include <fstream>

#include "Helpers.h"
#include "poXML.h"
#include "poTextBox.h"

poObject *createObjectForID(uint uid) {
	return new XMLApp();
}

void setupApplication() {
	fs::path path;
	pathToFolder("XML", &path);
	setCurrentPath(path);

	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "XML", 100, 100, 700, 700);
}

void cleanupApplication() {
}

XMLApp::XMLApp() {
    
    clicknum = 0;
    addModifier(new poCamera2D(poColor::black));

    // read XML 
    doc = poXMLDocument("frames.xml");
	poXMLNode rootNode = doc.rootNode();
    for( int i=0; i<rootNode.numChildren(); i++)
    {
        poXMLNode frameNode = rootNode.getChild(i); 
        F[i] = new perchFrame( frameNode );
        addChild( F[i] );
    }   

   


   
    //Add a control panel
    poRectShape* controlbun = new poRectShape("control.png");
    controlbun->position = poPoint(600,600);
    controlbun->alignment(PO_ALIGN_CENTER_CENTER);
    controlbun->fillColor = poColor::green;
    controlbun->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this, "click the control panel");
    addChild(controlbun);
    
    
    // use key press to save 
    addEvent( PO_KEY_DOWN_EVENT, this, "save the file");
    
   
    
	//applicationQuit();
}


void XMLApp::eventHandler( poEvent* E )
{
    if( E->type == PO_MOUSE_DOWN_INSIDE_EVENT )
    {
        for (int i = 0; i < 3; i++) {
             F[i]->controlswitch =!F[i]->controlswitch;
        } 
       
        if(clicknum%2 == 0)
        {
            static_cast<poShape2D*>(E->source)->fillColor = poColor::orange;

        }else{
            
            static_cast<poShape2D*>(E->source)->fillColor = poColor::green;

        }
        clicknum++;
    }
    
    
    
    if ( E->type == PO_KEY_DOWN_EVENT )
    {
        if ( E->keyChar == 's' && E->source == this)
        {
            printf("Save to frames.xml\n");
            doc.write("frames.xml");
        }
    }
}

