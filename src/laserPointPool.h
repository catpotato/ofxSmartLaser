//
//  laserPointPool.h
//  laserProjector
//
//  Created by Clark Addis on 6/1/17.
//
//

#ifndef laserPointPool_h
#define laserPointPool_h

#include <stdio.h>
#include "laserPoly.h"
#include "laserStructs.h"
#include <math.h> 

namespace Laser {


    class PointPool{
        public:
            vector <Laser::Poly> original_polys;        
            int total_points;
            int point_density;
            vector <vector <int>> allowed_points;
        
            parameters params;
            float total_perimeter;
            int spacing_points = 2;
            int points_for_drawing;
        
            void setup(parameters _params);
            void update_polys(vector <Laser::Poly> polys);
            void update_params(parameters _params);
        
            int get_allowed_points(int poly, int vertex);
            int get_blank_points();
        
        
    };
}

#endif /* laserPointPool_h */
