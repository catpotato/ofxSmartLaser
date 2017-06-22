//
//  laserProjection.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/7/17.
//
//

#include "laserProjection.h"

namespace Laser{
    
    // called by connect the dots to add a poly to this big poly
    void Projection::add_poly(Laser::Poly poly){
        
        // deal with previous bezier
        if(this->size() != 0) this->connect_to(poly.get_starting_point());
        
        // loops through all points
        for(int i = 0; i < poly.size(); i++){
            
            ofVec2f pt = poly[i];
            
            // first point
            if(i == 0) pt = poly.get_starting_point();
            
            // last point
            if(i == poly.size()-1) pt = poly.get_final_point();
            
            this->add_point(pt, poly, i);
        
        }
        
    }
    
    void Projection::connect_to(ofVec2f p2){
        
        ofVec2f p1 = (*this)[this->size()-1];
        ofVec2f diff = p2 -p1;
        
        // makes a bezier that is exactly a line
        ofVec2f cp1 = p1 + diff/3;
        ofVec2f cp2 = p1 + 2*diff/3;
        
        this->beziers[beziers.size()-1] = Laser::Bezier(p1,cp1,cp2,p2);
        this->colors[colors.size()-1] = ofColor::black;
        
    }
    
    void Projection::add_point(ofVec2f pt, Laser::Poly poly, int index){
        
        this->addVertex(pt);
        this->beziers.push_back(poly.beziers[index]);
        this->colors.push_back(poly.color);
        
    }
    
    void Projection::finish(parameters params){
        //close shape
        this->connect_to((*this)[0]);
        
        // has to be done
        this->close();

        // make lines
        this->setup_lines(params);
        
    }
    
    void Projection::setup_lines(parameters params){
        
        // this makes lines for rendering, but also fills in the p2's for the bezier's
        for(int i = 0; i < this->size(); i++){
            
            ofVec2f starting_point = (*this)[i];
            ofVec2f final_point = (*this)[(i+1)%(this->size())];
            
            this->beziers[i].set_midpoints(params);
            
            ofVec2f direction = final_point - starting_point;
            lines.push_back(direction);
            
        }
    }
    
    void Projection::draw_to_screen(parameters params){
        
        for(int i = 0; i < this->size() - 1; i++){
            
            ofColor color = this->colors[i];
            
            // so that black shows up
            if(color == ofColor::black) color = ofColor::grey;
            ofSetColor(color);
            
            // draw each point
            ofDrawCircle((*this)[i], 1.3);
            // draw each line
        }
    }
    
    vector <ofxIlda::Point> Projection::get_points(){
        vector <ofxIlda::Point> points;
        
        for(int i = 0; i < this->size(); i++){
            
            ofxIlda::Point point;
            ofVec2f temp =(*this)[i];
            
            point.set(temp, this->colors[i]);
            points.push_back(point);
        }
        
        return points;
        
    }

}
