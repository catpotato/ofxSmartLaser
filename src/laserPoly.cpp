//
//  laserPoly.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserPoly.h"
namespace Laser{
    Poly::Poly(ofPolyline p, ofColor c) : ofPolyline(p), color(c){ setup_lines(); }
    Poly::Poly() : ofPolyline(){ setup_lines(); }
    
    void Poly::setup_lines(){
        
        for(int i = 0; i < this->size(); i++){
            
            ofVec2f starting_point = (*this)[i];
            ofVec2f final_point = (*this)[(i+1)%(this->size())];
            
            ofVec2f direction = final_point - starting_point;
            lines.push_back(direction);
        }
    }
}
