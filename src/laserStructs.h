//
//  laserStructs.h
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/5/17.
//
//

#ifndef laserStructs_h
#define laserStructs_h

#include <stdio.h>
#include "ofxGui.h"

namespace Laser {
    enum resampling {vertex, uniform, adjusted, curves};
    enum bezier_sampling {exact, midpoint};
    
    struct parameters{

            // deafult values for params
            ofParameter <int> pps = 25000;
            ofParameter <int> max_points = 500;
            ofParameter <int> blank_points = 0;
            ofParameter <int> resample_type = adjusted;
            ofParameter <int> bezier_sample_type = midpoint;
            ofParameter <int> midpoints = 1;
            ofParameter <int> color_offset = 5;

        
    };
}

#endif /* laserStructs_h */
