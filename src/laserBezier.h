//
//  laserBezier.h
//  laserCurves
//
//  Created by Clark Addis on 6/11/17.
//
//

#ifndef laserBezier_h
#define laserBezier_h

#include <stdio.h>
#include <cmath>
#include "ofMain.h"
#include "laserStructs.h"

namespace Laser{
    
    class Bezier{
        public:
            ofPoint cp1;
            ofPoint cp2;
            ofPoint p1;
            ofPoint p2;
        
            bool exists;
            void setup(ofVec2f _p2, parameters params);
            vector <ofVec2f> midpoint_starting_points;
        
            Bezier(ofPoint _cp1, ofPoint _cp2);
            Bezier(bool _exists);
        
            ofVec2f get_point(float t);
        
        
        
    };
}

#endif /* laserBezier_h */
