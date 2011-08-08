#include "XMLApp.h"
#include "poApplication.h"
#include "poCamera.h"

#include <fstream>

#include "Helpers.h"
#include "poXML.h"
#include "poTextBox.h"
#include "poResourceStore.h"

poObject *createObjectForID(uint uid) {
	return new XMLApp();
}

void setupApplication() {
	fs::path path;
	pathToFolder("XML", &path);
	setCurrentPath(path);

	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "XML", 100, 100, 1280, 800);
}

void cleanupApplication() {
}

XMLApp::XMLApp() {
    
 
    controlbun_click = false;
    savebun_click = false;

    addModifier(new poCamera2D(poColor::black));

    // read XML 
    doc = poXMLDocument("frames.xml");
	rootNode = doc.rootNode();
    for( int i=0; i<rootNode.numChildren(); i++)
    {
        poXMLNode frameNode = rootNode.getChild(i); 
        F[i] = new perchFrame( frameNode );
        addChild( F[i] );
    }   

   


   
    //Add a control panel
    controlImg = getImage("control_off.png");
    controlbun = new poRectShape(controlImg->texture());
    controlbun->position = poPoint(getWindowWidth()-(controlbun->bounds.width()*3/2),controlbun->bounds.height()/2);
    controlbun->alignment(PO_ALIGN_CENTER_CENTER);
    controlbun->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this, "click the control panel");
    addChild(controlbun);
    
    
    // Add a save button to save 
    saveImg =getImage("save_off.png");
    savebun = new poRectShape(saveImg->texture());
    savebun->position = poPoint(getWindowWidth()-savebun->bounds.width()/2,savebun->bounds.height()/2);
    savebun->alignment(PO_ALIGN_CENTER_CENTER);
    savebun->addEvent(PO_MOUSE_OVER_EVENT, this,"mouse over");
    savebun->addEvent( PO_MOUSE_DOWN_INSIDE_EVENT, this, "save the file");
    addChild(savebun);
    
    //Add an align button
    alignbun = new poRectShape(160,61);
    alignbun->fillColor = poColor::grey;
    alignbun->position = poPoint(980,600);
    alignbun->alignment(PO_ALIGN_CENTER_CENTER);
    alignbun->addEvent(PO_MOUSE_OVER_EVENT, this,"mouse over");
    alignbun->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this,"align horizontally");
    addChild(alignbun);
    
    
   
    
	//applicationQuit();
}
void XMLApp::update()
{

   
    savebun->placeTexture(saveImg->texture());
    controlbun->placeTexture(controlImg->texture());
//    alignbun->visible = false;


}




void XMLApp::eventHandler( poEvent* E )
{
    if( E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "click the control panel")
    {
       
       
        for (int i = 0; i < 3; i++) 
        {
            F[i]->controlswitch =!F[i]->controlswitch;
      
        } 
        //control button
        
        controlbun_click =! controlbun_click;
        if(controlbun_click)
        {
            controlImg = getImage("control_on.png");
        }else{
            controlImg = getImage("control_off.png");
        }
        
       
    }
       
    if( E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "save the file")
    {
          
            printf("Save to frames.xml\n");
            doc.write("frames.xml");
             //save button
            //once you click then the save button turn to red
            saveImg = getImage("save_on.png");
      
        
    }
    if(E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "align horizontally")
    {
        printf("align horizontally\n");
        float averagey = 0;
        for (int i = 0; i < 3; i++) 
        {
        
            averagey = averagey + F[i]->position.y ;
            
        }
        for (int i = 0; i < 3; i++) 
        {
            F[i]->position.y = averagey/3;
        }
        printf("align horizontally:%f\n",averagey);
    
    }
    
    if(E->type == PO_MOUSE_OVER_EVENT&& E->message =="mouse over")
    {
        //one you finish the click then the save button turn to pink
        saveImg = getImage("save_off.png");
    }
    
  }

