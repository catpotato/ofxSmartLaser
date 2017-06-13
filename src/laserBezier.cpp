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
    
    ofPolyline Bezier::get_bezier(){
        
        ofPoint dir1 = cp1 - p1;
        ofPoint dir2 = cp2 - cp1;
        ofPoint dir3 = p2 - cp2;
        
        ofPoint mid1 = p1 + .5*dir1;
        ofPoint mid2 = cp1 + .5*dir2;
        ofPoint mid3 = cp2 + .5*dir3;
        
        ofPoint dir4 = mid2 - mid1;
        ofPoint dir5 = mid3 - mid2;
        
        ofPoint mid4 = mid1 + .5*dir4;
        ofPoint mid5 = mid2 + .5*dir5;
        
        ofPolyline bezier;
        
        bezier.addVertex(p1);
        bezier.addVertex(mid1);
        bezier.addVertex(mid4);
        bezier.addVertex(mid2);
        bezier.addVertex(mid5);
        bezier.addVertex(mid3);
        bezier.addVertex(p2);
        
        return bezier;
    }
    
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
