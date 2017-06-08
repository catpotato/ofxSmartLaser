//
//  laserPoly.h
//  laserProjector
//
//  Created by Clark Addis on 6/1/17.
//
//

#ifndef laserPoly_h
#define laserPoly_h

#include <stdio.h>
#include "ofMain.h"

namespace Laser{
    class Poly : public ofPolyline{
        public:
            ofColor color;
            // this is a clever vector of vectors which just has the direction that the line goes at the given index with starting point at that index in the polygon
            vector <ofVec2f> lines;
            void setup_lines();
            Poly(ofPolyline p, ofColor c);
            Poly();
    };
}



#endif /* laserPoly_h */
