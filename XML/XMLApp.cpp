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
    
    addModifier(new poCamera2D(poColor::white));
    
    //click declare 
    controlbun_click = false;
    savebun_click = false;
    
    //read background
    poXMLDocument doc_background = poXMLDocument("background.xml");
    poXMLNode doc_rootNode = doc_background.rootNode();
    perchbackground* B = new perchbackground(doc_rootNode.getChild(0));
    addChild(B);

    // read frames XML 
    doc = poXMLDocument("frames.xml");
	rootNode = doc.rootNode();
    for( int i=0; i<rootNode.numChildren(); i++)
    {
        poXMLNode frameNode = rootNode.getChild(i); 
        //F[i] = new perchFrame( frameNode);
        //addChild(F[i]);
        F = new perchFrame( frameNode );
        framelist.insert(framelist.end(), F);
        addChild( F );
    }   
    

   
    //Add a control panel
    controlImg = getImage("control/control_off.png");
    controlbun = new poRectShape(controlImg->texture());
    controlbun->position = poPoint(getWindowWidth()-(controlbun->bounds.width()*3/2),controlbun->bounds.height()/2);
    controlbun->alignment(PO_ALIGN_CENTER_CENTER);
    controlbun->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this, "click the control panel");
    addChild(controlbun);
    
    
    // Add a save button to save 
    saveImg =getImage("control/save_off.png");
    savebun = new poRectShape(saveImg->texture());
    savebun->position = poPoint(getWindowWidth()-savebun->bounds.width()/2,savebun->bounds.height()/2);
    savebun->alignment(PO_ALIGN_CENTER_CENTER);
    savebun->addEvent(PO_MOUSE_OVER_EVENT, this,"mouse over");
    savebun->addEvent( PO_MOUSE_DOWN_INSIDE_EVENT, this, "save the file");
    addChild(savebun);
    
    //Add an add frame button
    addImg = getImage("control/add.png");
    addbun = new poRectShape(addImg->texture());
    addbun->position = poPoint(getWindowWidth()-savebun->bounds.width()*2-addbun->bounds.width()/2,addbun->bounds.height()/2);
    addbun->alignment(PO_ALIGN_CENTER_CENTER);
    addbun->addEvent(PO_MOUSE_OVER_EVENT, this,"mouse over");
    addbun->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this,"add a new frame");
    addChild(addbun);
    
    //Add an delete frame button
    deleteImg = getImage("control/delete.png");
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
    // only in control mode, you can add and delete frames
    addbun->visible = controlbun_click;
    deletebun->visible = controlbun_click;


}



void XMLApp::eventHandler( poEvent* E )
{
    if( E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "click the control panel")
    {
       
       
        for (iter=framelist.begin();iter!=framelist.end();++iter) (*iter)->controlswitch =!(*iter)->controlswitch ; 

      
        //control button
        
        controlbun_click =! controlbun_click;
        if(controlbun_click)
        {
            controlImg = getImage("control/control_on.png");
        }else{
            controlImg = getImage("control/control_off.png");
        }
        
       
    }
       
    if( E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "save the file")
    {
          
        printf("Save to frames.xml\n");
        doc.write("frames.xml");
         //save button
        //once you click then the save button turn to red
        saveImg = getImage("control/save_on.png");
      
        
    }
    if(E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "add a new frame")
    {
        addnewframe(rootNode);
        
    }
    
    if(E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "delete a frame")
    {
        if(perchFrame::activeFrame != NULL)
        {
            perchFrame::activeFrame->parent()->removeChild( perchFrame::activeFrame );// remove from window
            rootNode.removeChild(perchFrame::activeFrame->frameNode.name());//remove from XML file
//            framelist.remove(perchFrame::activeFrame);// remove from framelist
            perchFrame::activeFrame = NULL;// set the activeFrame to Null
//            printf("listsize:%d",int(framelist.size()));
          
        }
       
    }
    
    if(E->type == PO_MOUSE_OVER_EVENT&& E->message =="mouse over")
    {
        //one you finish the click then the save button turn to pink
        saveImg = getImage("control/save_off.png");
    }
    
  }

void XMLApp::addnewframe(poXMLNode oriRootNode)
{
    
    poXMLNode newframe = oriRootNode.addChild("frame");
    //default setting of new frame
    newframe.addChild("frameID").setInnerInt(int(framelist.size())+1);
    newframe.addChild("scale").setInnerFloat(1.0);
    newframe.addChild("posx").setInnerInt(150);
    newframe.addChild("posy").setInnerInt(150);
    newframe.addChild("image").setInnerString(oriRootNode.getChild(0).getChild("image").innerString());
    //add a new frame to the screen
    F = new perchFrame(newframe);
    framelist.insert(framelist.end(), F);
    //make sure the new frame in the same control mode as other
    F->controlswitch = controlbun_click;
    addChild( F );

    printf("add a new frame\n");
    
    
}

