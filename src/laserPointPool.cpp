//
//  laserPointPool.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserPointPool.h"
namespace Laser{
    
    
    void PointPool::update(Laser::Projection projection){

        total_perimeter = projection.get_perimeter();
        
        
        // do a lazy first passthrough of all points
        int used_points = 0;
        allowed_points.clear();
        
            
        for(int i = 0; i < projection.beziers.size(); i++){
            ofVec2f direction = projection.beziers[i].p1 - projection.beziers[i].p2;
            float length = direction.distance(direction.zero());
            
            float pct = length/total_perimeter;

                
            allowed_points.push_back(round(pct*(params.max_points)));
        }
        
    }
    
    
    void PointPool::update_params(parameters _params){
    
        params = _params;
        
    }
    
    int PointPool::get_allowed_points(int index){
        
        return allowed_points[index];
        
        
        
    }
}
