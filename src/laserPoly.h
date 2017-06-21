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
            void setup_lines();
        
            void add_vertex_bez(ofPoint pt1, ofPoint pt2, Laser::Bezier bz);
            void add_vertex(ofPoint pt);
            void slice_off_edges();
            //void translate();
        
            Poly(ofPolyline p, ofColor c);
            Poly();
        
            void reset();
        
            ofVec2f get_starting_point();
    };
}



#endif /* laserPoly_h */
