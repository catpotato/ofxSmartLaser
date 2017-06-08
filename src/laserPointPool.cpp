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
        
        total_perimeter = projection.getPerimeter();
        
        // do a lazy first passthrough of all points
        
        int used_points = 0;
        allowed_points.clear();
        
            
        for(int i = 0; i < projection.size(); i++){
            ofVec2f direction = projection.lines[i];
            float length = direction.distance(direction.zero());
            
            float pct = length/total_perimeter;
            allowed_points.push_back(round(pct*(params.max_points)));
        }
        
    }
    
    
    void PointPool::update_params(parameters _params){
    
        params = _params;
        
    }
    
    int PointPool::get_allowed_points(int index){
        
        if(params.constant_point_per_line){
            return params.points_per_line;
        }
        else{
            
            return allowed_points[index];
        }
        
        
        
    }
}
