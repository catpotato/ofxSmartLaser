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
#include "ofMain.h"
namespace Laser{
    
    class Bezier{
        public:
            ofPoint control_point;
            int resolution;
        
            Bezier(ofPoint cp, int res);
    };
}

#endif /* laserBezier_h */
