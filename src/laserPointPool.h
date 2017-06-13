//
//  laserPointPool.h
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#ifndef laserPointPool_h
#define laserPointPool_h

#include <stdio.h>
#include "laserProjection.h"
#include "laserPoly.h"
#include "laserStructs.h"
#include <math.h> 

namespace Laser {


    class PointPool{
        public:
            vector <Laser::Poly> original_polys;        
            vector <int> allowed_points;
        
            parameters params;
            float total_perimeter;
            int points_for_drawing;

            void update_polys(vector <Laser::Poly> polys);
            void update_params(parameters _params);
            void update(Laser::Projection projection);
        
            int get_allowed_points(int index);
            int get_blank_points();
        
            int number_of_verticies;
        
        
    };
}

#endif /* laserPointPool_h */
