//
//  laserStructs.h
//  multipoly
//
//  Created by Clark Addis on 6/5/17.
//
//

#ifndef laserStructs_h
#define laserStructs_h

#include <stdio.h>

namespace Laser {
    enum resampling {vertex, uniform, adjusted};
    
    struct parameters{
        int pps;
        int max_points;
        int blank_points;
        resampling resample_type = adjusted;
    };
}

#endif /* laserStructs_h */
