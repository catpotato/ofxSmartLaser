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
        // really not supposed to access these
            ofPoint cp1;
            ofPoint cp2;
            ofPoint p1;
            ofPoint p2;
        
        public:

            float start_pct;
            float end_pct;
        
            ofPoint cp1_diff;
            ofPoint cp2_diff;
        
            bool exists;
            void setup(ofVec2f _p1, ofVec2f _p2);
            vector <ofVec2f> midpoint_starting_points;
        
            Bezier(ofPoint _cp1, ofPoint _cp2);
            Bezier(bool _exists);
        
            void set_midpoints(parameters params);
            ofVec2f get_point(float t, ofPoint p1, ofPoint p2);
            void update_control_points();
        
            void draw();
        
        
        
    };
}

#endif /* laserBezier_h */
