//
//  laserPoly.h
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#ifndef laserPoly_h
#define laserPoly_h

#include <stdio.h>
#include "ofMain.h"
#include "laserBezier.h"

namespace Laser{
    class Poly : public ofPolyline{
        public:
            ofColor color;
            // this is a clever vector of vectors which just has the direction that the line goes at the given index with starting point at that index in the polygon
            vector <ofVec2f> lines;
            vector <Laser::Bezier> beziers;
            vector <Laser::Bezier> new_beziers;
            void setup_lines();
        
            void add_vertex_bez(ofPoint pt1, ofPoint pt2, Laser::Bezier bz);
            void add_vertex(ofVec2f v);

            Poly(ofPolyline p, ofColor c);
            Poly();
        
            ofVec2f get_starting_point();
            ofVec2f get_final_point();
            ofVec2f final_point;
            ofVec2f starting_point;
        
            bool start_point_set = false;
            bool final_point_set = false;
        
            void set_final_point(ofVec2f pt);
            void set_start_point(ofVec2f pt);
        
            void start_cut_bez(float t, Laser::Bezier bez);
            void end_cut_bez(float t, Laser::Bezier bez);
        
            void bez_to(ofVec2f cp1, ofVec2f cp2, ofVec2f p2);
            ofVec2f get_last_point();
        
            void close_bez();
        
    };
}



#endif /* laserPoly_h */
