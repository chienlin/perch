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

    lookUpAndSetPath("resources");
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "XML", 100, 100, 1280, 800);
}

void cleanupApplication() {
}

XMLApp::XMLApp() {
    
 
    controlbun_click = false;
    savebun_click = false;

    addModifier(new poCamera2D(poColor::white));

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
    
    //Add an add frame button
    addImg = getImage("add.png");
    addbun = new poRectShape(addImg->texture());
    addbun->position = poPoint(getWindowWidth()-savebun->bounds.width()*2-addbun->bounds.width()/2,addbun->bounds.height()/2);
    addbun->alignment(PO_ALIGN_CENTER_CENTER);
    addbun->addEvent(PO_MOUSE_OVER_EVENT, this,"mouse over");
    addbun->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this,"add a new frame");
    addChild(addbun);
    
    //Add an delete frame button
    deleteImg = getImage("delete.png");
    deletebun = new poRectShape(deleteImg->texture());
    deletebun->position = poPoint(getWindowWidth()-savebun->bounds.width()*2-deletebun->bounds.width()*3/2,deletebun->bounds.height()/2);
    deletebun->alignment(PO_ALIGN_CENTER_CENTER);
    deletebun->addEvent(PO_MOUSE_OVER_EVENT, this,"mouse over");
    deletebun->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this,"delete a frame");
    addChild(deletebun);
   
    
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
       
       
        for (int i = 0; i < rootNode.numChildren(); i++) 
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
    if(E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "add a new frame")
    {
        printf("add a new frame\n");
//        poXMLNode newframe = rootNode.addChild("frame");
//        newframe.addChild("frameID").setInnerInt(4);
//        newframe.addChild("scale").setInnerInt(4);
//        newframe.addChild("posx").setInnerInt(4);
//        newframe.addChild("posy").setInnerInt(4);
//        
//        doc.write("frames2.xml");
//        printf("%d",rootNode.numChildren());
    }
    
    if(E->type == PO_MOUSE_OVER_EVENT&& E->message =="mouse over")
    {
        //one you finish the click then the save button turn to pink
        saveImg = getImage("save_off.png");
    }
    
  }

