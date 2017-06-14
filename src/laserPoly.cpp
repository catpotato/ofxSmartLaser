//
//  laserPoly.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserPoly.h"
namespace Laser{
    Poly::Poly(ofPolyline p, ofColor c) : color(c){
        
        for(int i = 0; i < p.size(); i++) add_vertex(p[i]);
        setup_lines();
    }
    
    Poly::Poly() : ofPolyline(){ setup_lines(); }
    
    void Poly::setup_lines(){
        
        for(int i = 0; i < this->size(); i++){
            
            ofVec2f starting_point = (*this)[i];
            ofVec2f final_point = (*this)[(i+1)%(this->size())];
            
            ofVec2f direction = final_point - starting_point;
            lines.push_back(direction);
        }
    }
    
    void Poly::add_vertex_bez(ofPoint pt, Laser::Bezier bz){
        
        this->addVertex(pt);
        bz.p1 = pt;
        beziers.push_back(bz);
        
    };
    
    void Poly::add_vertex(ofPoint pt) { add_vertex_bez(pt, Laser::Bezier(false));}
}
