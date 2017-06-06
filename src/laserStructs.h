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
#include "ofxGui.h"

namespace Laser {
    enum resampling {vertex, uniform, adjusted};
    
    struct parameters{
        // deafult values for params
        ofParameter <int> pps = 25000;
        ofParameter <int> max_points = 500;
        ofParameter <int> blank_points = 0;
        ofParameter <resampling> resample_type = adjusted;
        ofParameter <bool> constant_point_per_line = false;
        ofParameter <int> points_per_line = 5;
        
        bool show_params = true;
        
    };
}

#endif /* laserStructs_h */
