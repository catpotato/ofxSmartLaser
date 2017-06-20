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
#include "poly34.h"

namespace Laser{
    
    class Bezier{
        // really not supposed to access these
        
        
        public:
        
            ofPoint cp1;
            ofPoint cp2;
            ofPoint p1;
            ofPoint p2;

            float start_pct = 0;
            float end_pct = 1;
        
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
        
            vector <float> get_valid_intersections(ofVec2f current_point, ofVec2f current_line);
            vector <float> get_ts_from_x(float x);
            vector <float> get_ts_from_y(float y);
            bool valid(float t, ofVec2f current_point, ofVec2f current_line);
        
        
        
    };
}

#endif /* laserBezier_h */
