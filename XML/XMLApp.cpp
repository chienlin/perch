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
    
    //read background.XML
    poXMLDocument doc_background = poXMLDocument("background.xml");
    poXMLNode rootNode_background = doc_background.rootNode();
    perchbackground* B = new perchbackground(rootNode_background.getChild(0));
    addChild(B);

    // read frames.XML 
    doc_frames = poXMLDocument("frames.xml");
	rootNode_frames = doc_frames.rootNode();
    
    // read product.XML
    doc_product = poXMLDocument("product.xml");
    rootNode_product = doc_product.rootNode();
    
    //Print the frames we have
    for( int i=0; i<rootNode_frames.numChildren(); i++)
    {
        poXMLNode frameNode = rootNode_frames.getChild(i);
        poXMLNode productNode = rootNode_product.getChild(i);

        F = new perchFrame( frameNode,productNode );
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
        doc_frames.write("frames.xml");
        printf("Save to product.xml\n");
        doc_product.write("product.xml");
        
        //save button
        //once you click then the save button turn to red
        saveImg = getImage("control/save_on.png");
      
        
    }
    if(E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "add a new frame")
    {
        addnewframe(rootNode_frames,rootNode_product);
        
    }
    
    if(E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "delete a frame")
    {
        if(perchFrame::activeFrame != NULL)
        {
            perchFrame::activeFrame->parent()->removeChild( perchFrame::activeFrame );// remove from window
            rootNode_frames.removeChild(perchFrame::activeFrame->framesNode.name());//remove from frames.xml file
            rootNode_product.removeChild(perchFrame::activeFrame->productNode.name());//remove from product.xml file
            perchFrame::activeFrame = NULL;// set the activeFrame to Null
            
            framelist.remove(perchFrame::activeFrame);// remove from framelist
            printf("listsize:%d",int(framelist.size()));
          
        }
       
    }
    
    if(E->type == PO_MOUSE_OVER_EVENT&& E->message =="mouse over")
    {
        //one you finish the click then the save button turn to pink
        saveImg = getImage("control/save_off.png");
    }
    
  }

void XMLApp::addnewframe(poXMLNode oriRootNode_frames,poXMLNode oriRootNode_product)
{
    int latestFrameID = 0;
    latestFrameID = rootNode_frames.getChild(rootNode_frames.numChildren()-1).getChild("frameID").innerInt();

    printf("latestFrameID = %d",latestFrameID);
    
    poXMLNode newframe = oriRootNode_frames.addChild("frame");
    //default setting of new frame
    newframe.addChild("frameID").setInnerInt(latestFrameID+1);
    newframe.addChild("scale").setInnerFloat(1.0);
    newframe.addChild("posx").setInnerInt(150);
    newframe.addChild("posy").setInnerInt(150);
    newframe.addChild("image").setInnerString(oriRootNode_frames.getChild(0).getChild("image").innerString());
    
    
    
    poXMLNode newproduct = oriRootNode_product.addChild("product");
    //default setting of new frame
    newproduct.addChild("productID").setInnerInt(latestFrameID+1);
    newproduct.addChild("name").setInnerString("Shoe");
    newproduct.addChild("price").setInnerInt(150);
    newproduct.addChild("size").setInnerInt(6);
    newproduct.addChild("color").setInnerString("Red");
    newproduct.addChild("description_short").setInnerString("Please enter the short description");
    
    
    //add a new frame to the screen
    F = new perchFrame(newframe,newproduct);
    framelist.insert(framelist.end(), F);
    //make sure the new frame in the same control mode as other
    F->controlswitch = controlbun_click;
    addChild( F );

    printf("add a new frame\n");
    
    
}

