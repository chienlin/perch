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

perchFrame::perchFrame( poXMLNode node )
{
    
    controlswitch = false;
    
    
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
    
    //for press down to change scale of c
    addEvent(PO_KEY_DOWN_EVENT, this, "click C to scale");
    
    
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
    
    //open frame bounds when contolswitch on
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
    
        if ( E->type == PO_KEY_DOWN_EVENT )
        {
                if (E->keyChar=='c') 
                {
                    R->scale.x *= 1.1;
                    R->scale.y = R->scale.x;
                }
                if (E->keyChar=='x') 
                {
                    R->scale.x *= 0.9;
                    R->scale.y = R->scale.x;
                }
            
            frameNode.getChild("scale").setInnerFloat(R->scale.x);
        }
         
         
        if ( E->type == PO_MOUSE_DRAG_EVENT && E->message == "drag the frame")
        {
            position = E->position;
            frameNode.getChild("posx").setInnerInt(position.x);
            frameNode.getChild("posy").setInnerInt(position.y);
      
         }
         if ( E->type == PO_MOUSE_DRAG_EVENT && E->message == "drag the green rect")
         {
             SR1->position = R->objectToLocal(SR1,E->local_position);
             if(SR1->position.x >= 0)
             {
                 R->scale.x *= (1+abs(SR1->position.x)/(256*R->scale.x));
                 R->scale.y = R->scale.x;
             
             }
     
         }
  
     
     }
    
   
}


