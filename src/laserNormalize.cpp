//
//  laserNormalize.cpp
//  laserProjector
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserNormalize.h"

namespace Laser{
    void normalize(vector <Laser::Poly> resampled_polys, vector <Laser::Poly> & normalized_polys, ofVec2f window_dimensions){
        normalized_polys = resampled_polys;
        for(int i = 0; i < resampled_polys.size(); i++){
            for(int j = 0; j < resampled_polys[i].size(); j++){
                normalized_polys[i][j].x = 1 - resampled_polys[i][j].x/window_dimensions.x;
                normalized_polys[i][j].y = 1 - resampled_polys[i][j].y/window_dimensions.y;
            }
        }
    }
}
