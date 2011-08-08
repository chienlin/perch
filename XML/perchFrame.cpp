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

perchFrame::perchFrame( poXMLNode node )
{
    
    controlswitch = false;
    alignhorizontal = false;
    alignvertical = false;
    num = 0;
    
    
    frameNode = node;
    
    // object position
    position = poPoint( frameNode.getChild("posx").innerInt(), frameNode.getChild("posy").innerInt() );

    // make image frame
    float S = frameNode.getChild("scale").innerFloat();
    std::string imageName = frameNode.getChild("image").innerString();
    
    R = new poRectShape( imageName );
    R->alignment( PO_ALIGN_CENTER_CENTER );
    R->scale.set( S,S,1 );
    R->calculateBounds();
    R->addEvent( PO_MOUSE_DRAG_EVENT, this, "drag the frame" );
    R->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT,this, "click the frame");
    addChild( R );
    
        
    //text box for info
    tb = new poTextBox(getWindowWidth(), getWindowHeight()/2);
	tb->textAlignment(PO_ALIGN_TOP_LEFT);
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
    
}

void perchFrame::eventHandler( poEvent* E )
{
    
     if (controlswitch) 
     {
    
                 
         
        if ( E->type == PO_MOUSE_DRAG_EVENT && E->message == "drag the frame")
        {
            //move by invisible grid line
            position.x = int(E->position.x/grid)*grid;
            position.y = int(E->position.y/grid)*grid;
            //save the new position back to XML
            frameNode.getChild("posx").setInnerInt(position.x);
            frameNode.getChild("posy").setInnerInt(position.y);
                  
         }
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
             frameNode.getChild("scale").setInnerFloat(R->scale.x);
         }
  
     
     }
    
   
}


