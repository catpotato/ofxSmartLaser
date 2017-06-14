//
//  laserBezier.cpp
//  laserCurves
//
//  Created by Clark Addis on 6/11/17.
//
//

#include "laserBezier.h"
namespace Laser{
    

    Bezier::Bezier(ofPoint _cp1, ofPoint _cp2): cp1(_cp1), cp2(_cp2), exists(true){ cout << cp1 << endl << cp2<<endl;};
    Bezier::Bezier(bool _exists): exists(_exists){};
    
    ofVec2f Bezier::get_point(float t){
    
        ofVec2f result =    p1*pow((1-t), 3) +
                            cp1*3*pow((1-t), 2)*t +
                            cp2*3*(1-t)*pow(t,2) +
                            p2*pow(t,3);
        
        return result;
        
    }
    
    void Bezier::setup(ofVec2f _p2, parameters params){
        p2 = _p2;
        
        // if we are rendering midpoint style (this is here to prevent unesseacry calculations)
        if(params.bezier_sample_type == midpoint){
            float step_size = 1/((float)params.midpoints);
            
            for(int i = 0; i < params.midpoints; i++){
                
                // starts at zero, goes up by the step size count each time
                
                midpoint_starting_points.push_back(get_point(step_size*i));
                
            }
        
        }
        
    }
    
    
    
}
