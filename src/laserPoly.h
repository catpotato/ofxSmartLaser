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
            Poly(ofPolyline p, ofColor c);
    };
}



#endif /* laserPoly_h */
