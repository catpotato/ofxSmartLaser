//
//  laserHelpers.h
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#ifndef laserHelpers_h
#define laserHelpers_h

#include <stdio.h>
#include <cmath>
#include <algorithm>
#include "laserPoly.h"
#include "laserPointPool.h"
#include "laserProjection.h"

namespace Laser {

    float ease_func(float t);
    
    Laser::Projection resample(Laser::Projection projection, parameters params, Laser::PointPool point_pool);
    Laser::Projection normalize(Laser::Projection projection, ofVec2f window_dimensions);
    

}

#endif /* laserHelpers_h */
