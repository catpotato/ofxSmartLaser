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
#include "ofxSvg.h"

namespace Laser {

    float ease_func(float t);
    
    vector <Laser::Poly> get_polys_from_svg(string path);
    
    vector <Laser::Poly> initialize(vector <Laser::Poly> polys);
    Laser::Projection connect_the_dots(vector <Laser::Poly> original_polys, parameters params);
    Laser::Projection resample(Laser::Projection projection, parameters params, Laser::PointPool point_pool);
    Laser::Projection normalize(Laser::Projection projection, ofVec2f window_dimensions);
    
    
    
    

}

#endif /* laserHelpers_h */
