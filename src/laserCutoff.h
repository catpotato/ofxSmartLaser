//
//  laserCutoff.h
//  speed
//
//  Created by Clark Addis on 6/15/17.
//
//

#ifndef laserCutoff_h
#define laserCutoff_h

#include <stdio.h>
#include "ofMain.h"
#include "laserProjection.h"
#include "laserBezier.h"

namespace Laser{
    
    vector <Laser::Poly> slice_off_edges(vector <Laser::Poly> polys);
    bool in_bounding_box(ofVec2f pt);
    

}

#endif /* laserCutoff_h */
