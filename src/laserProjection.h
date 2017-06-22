//
//  laserProjection.h
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/7/17.
//
//

#ifndef laserProjection_h
#define laserProjection_h

#include <stdio.h>
#include "ofMain.h"
#include "laserPoly.h"
#include "laserStructs.h"
#include "ofxIldaPoint.h"
#include "laserBezier.h"

namespace Laser {
    class Projection : public ofPolyline{
        public:
            vector <ofColor> colors;
            vector <Laser::Bezier> beziers;
            vector <ofVec2f> lines;
        
        
            void add_poly(Laser::Poly poly);
            void connect_to(ofVec2f p2);
            void add_point(ofVec2f pt, Laser::Poly poly, int index);
            void finish(parameters params);
            void setup_lines(parameters params);

            vector <ofxIlda::Point> get_points();
            void draw_to_screen(parameters params);
        
    };
}

#endif /* laserProjection_h */
