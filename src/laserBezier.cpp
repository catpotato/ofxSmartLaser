//
//  laserBezier.cpp
//  laserCurves
//
//  Created by Clark Addis on 6/11/17.
//
//

#include "laserBezier.h"
namespace Laser{
    

    Bezier::Bezier(ofPoint _cp1, ofPoint _cp2): cp1(_cp1), cp2(_cp2), exists(true){};
    Bezier::Bezier(bool _exists): exists(_exists){};
    
    ofVec2f Bezier::get_point(float t, ofPoint _p1, ofPoint _p2){
        
        p1 = _p1;
        p2 = _p2;
        cp1 = p1 + cp1_diff;
        cp2 = p2 + cp2_diff;
        
        
        // the meat of the bezier
        ofVec2f result =    p1*pow((1-t), 3) +
                            cp1*3*pow((1-t), 2)*t +
                            cp2*3*(1-t)*pow(t,2) +
                            p2*pow(t,3);
        
        return result;
        
    }
    
    void Bezier::setup(ofVec2f _p1, ofVec2f _p2, parameters params){
        //cout << "setup" << endl;
        p1 = _p1;
        p2 = _p2;
        
        // these are here so we can define the point relativley to p1 and p2 and as such are able to move around curves easily
        cp1_diff = cp1 - p1;
        cp2_diff = cp2 - p2;
        
        // if we are rendering midpoint style (this is here to prevent unesseacry calculations)
        if(params.bezier_sample_type == midpoint){
            float step_size = 1/((float)params.midpoints);
            
            for(int i = 0; i < params.midpoints; i++){
                
                // starts at zero, goes up by the step size count each time
                midpoint_starting_points.push_back(get_point(step_size*i, p1, p2));
                
            }
        
        }
        
    }
    
    void Bezier::draw(){
        //cout << "drawing!" << endl;
        ofSetColor(ofColor::green);
        ofDrawCircle(p1, 1.2);
        ofDrawCircle(p2, 1.2);
        
        ofSetColor(ofColor::red);
        ofDrawCircle(cp1, 1.2);
        ofDrawCircle(cp2, 1.2);
    
    }
    
    
    
}
