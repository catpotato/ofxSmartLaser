//
//  laserNormalize.h
//  laserProjector
//
//  Created by Clark Addis on 6/1/17.
//
//

#ifndef laserNormalize_h
#define laserNormalize_h

#include <stdio.h>
#include "laserPoly.h"

namespace Laser {
    void normalize(vector <Laser::Poly> resampled_polys, vector <Laser::Poly> & normalized_polys, ofVec2f window_dimensions);
}

#endif /* laserNormalize_h */
