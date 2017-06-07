//
//  laserHelpers.h
//  laserProjector
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

namespace Laser {
    
    void normalize(vector <Laser::Poly> resampled_polys, vector <Laser::Poly> & normalized_polys, ofVec2f window_dimensions);
    
    float ease_func(float t);
    
    void resample(vector <Laser::Poly> original_polys, vector <Laser::Poly> & resampled_polys, parameters params, Laser::PointPool point_pool);
    
    void connect_the_dots(vector <Laser::Poly> original_polys, Laser::Poly & connected_poly);
    
}

#endif /* laserHelpers_h */
