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
        
            void setup_lines(parameters params);
            void add_poly(Laser::Poly poly);
            void finish(parameters params);
            void spew();

            void copy(Laser::Poly poly, ofColor color, int index);
            void connect_the_dots(vector <Laser::Poly> original_polys, parameters params);
            vector <ofxIlda::Point> get_points();
            void draw_to_screen(parameters params);
        
        
    };
}

#endif /* laserProjection_h */
