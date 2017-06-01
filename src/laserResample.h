//
//  laserResample.h
//  laserProjector
//
//  Created by Clark Addis on 5/31/17.
//
//

#ifndef laserResample_h
#define laserResample_h

#include <stdio.h>
#include "laserPoly.h"
namespace Laser{
    void resample(vector <Laser::Poly> original_polys, vector <Laser::Poly> & resampled_polys, int number_of_points, float perimeter, bool lazy);
}

#endif /* laserResample_h */
