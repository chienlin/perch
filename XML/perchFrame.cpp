//
//  perchFrame.cpp
//  XML
//
//  Created by chien on 8/2/11.
//  Copyright 2011 Potion Design. All rights reserved.
//

#include <iostream>
#include "perchFrame.h"
#include "poApplication.h"
#include "poResourceStore.h"
#include <boost/format.hpp>
#define grid 15


perchFrame* perchFrame::activeFrame = NULL;

perchFrame::perchFrame( poXMLNode _framesNode, poXMLNode _productNode )
{
    
    controlswitch = false;
    framesNode = _framesNode;
    productNode = _productNode;

    
    // object position
    position = poPoint( framesNode.getChild("posx").innerInt(), framesNode.getChild("posy").innerInt() );

    // make image frame
    float S = framesNode.getChild("scale").innerFloat();
    std::string imageName = framesNode.getChild("image").innerString();
    
    frameImg = getImage(imageName);
    R = new poRectShape( imageName );
    R->alignment( PO_ALIGN_CENTER_CENTER );
    R->scale.set( S,S,1 );
    R->strokeColor = poColor::red;
    R->addEvent( PO_MOUSE_DRAG_EVENT, this, "drag the frame" );
    R->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT,this, "click the frame");
    addChild( R );
    
        
    //text box for info
    tb = new poTextBox(getWindowWidth(), getWindowHeight()/2);
	tb->textAlignment(PO_ALIGN_TOP_LEFT);
    tb->textColor = poColor::green;
    tb->font(getFont("Courier", 12));
	addChild(tb);
    
    //small rectangles to control the scale
    SR1 = new poRectShape(30,30);
    SR1->fillColor = poColor::green;
    SR1->alignment(PO_ALIGN_CENTER_CENTER);
    SR1->drawBounds = false;
    SR1->position = poPoint(0,0);
    SR1->addEvent(PO_MOUSE_DRAG_EVENT, this, "drag the green rect");
    SR1->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT,this, "click the green rect");
    R->addChild(SR1);
    
    //show the info of this product
    productInfo = new perchProduct(productNode);//according to current frameID find the product info in product.xml
//    productInfo->position = poPoint(R->bounds.width()*R->scale.x/2,R->bounds.height()*R->scale.x/2);
    productInfo->position = poPoint(80,80);
    productInfo->alignment(PO_ALIGN_TOP_LEFT);
    productInfo->visible = false; 
    productInfo->displaynum = 0;
    R->addChild(productInfo);
   
       
    
}
void perchFrame::draw(){




}
void perchFrame::update(){
    
    //open frame bounds when controlswitch on
    R->drawBounds = controlswitch;

    //open textbox when contolswitch on
    tb->position.set(R->bounds.width()*R->scale.x/2,0,1);
    tb->visible = controlswitch;
    char buffer [50];
    sprintf(buffer,"position:(%f,%f) scale: %f",position.x,position.y,R->scale.x);
    tb->text(buffer)->layout();
    
    //open green scale-control rectangle
    SR1->visible = controlswitch;
    
    // make the static activeFrame for delete function
    if ( this == activeFrame )
    {
        framesNode.setName("Selected");
        productNode.setName("Selected");
        R->generateStroke(6);
    }
    else
    {    
        framesNode.setName("frame");
        productNode.setName("product");
        R->generateStroke(0);
    }
    
    // assign active frame when it is not in select mode
    if (!controlswitch) 
    {
        activeFrame = NULL;
    }else
    {
//        productInfo->visible = false;
    }
    // for changing frame image
    R->calculateBounds();
    R->placeTexture(frameImg->texture());
    
    
}

void perchFrame::eventHandler( poEvent* E )
{
    
     if (controlswitch) 
     {
    
                 
        //frames 
        if ( E->type == PO_MOUSE_DRAG_EVENT && E->message == "drag the frame")
        {
            activeFrame = this;
            
            //move by invisible grid line
            position.x = int(E->position.x/grid)*grid;
            position.y = int(E->position.y/grid)*grid;
            //save the new position back to XML
            framesNode.getChild("posx").setInnerInt(position.x);
            framesNode.getChild("posy").setInnerInt(position.y);
                  
         }
         if ( E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "click the frame")
         {
             activeFrame = this;
           
         }
         
         //green scale control
         if ( E->type == PO_MOUSE_DRAG_EVENT && E->message == "drag the green rect")
         {
        
             
             poPoint tempPosition = R->objectToLocal(SR1,E->local_position); 
             printf("tempPosition(%f,%f)\n",tempPosition.x,tempPosition.y);

             //Because SR1 is the child of R, so we need to transform the event local position of SR1 into local position of R
             SR1->position = R->objectToLocal(SR1,E->local_position);
             //Fix the green rectangle to left corner
             if (SR1->position.x != 0 && SR1->position.y != 0) {
                 SR1->position.x = 0;
                 SR1->position.y = 0;

             }
             //caculate distance
             double distance = sqrt(pow((E->position.x - position.x),2) + pow((E->position.y - position.y),2));
             double origindistance = R->bounds.width()/2*R->scale.x*sqrt(2);
             
             if(distance != origindistance)
             {
                 R->scale.x *= distance/origindistance;
                 R->scale.y = R->scale.x;
                 
             }
             framesNode.getChild("scale").setInnerFloat(R->scale.x);
         }
  
     
     }
//     else// control switch = false
//     {
     
     
         if ( E->type == PO_MOUSE_DOWN_INSIDE_EVENT && E->message == "click the frame")
         {
             productInfo->visible = true;
             productInfo->displaynum ++;
             if (productInfo->displaynum == 1) frameImg = getImage("box_open.png");
             if (productInfo->displaynum == 6) frameImg = getImage("box_close.png");

             printf("%d\n",productInfo->displaynum);
         }
     
     
     
    
   
}


