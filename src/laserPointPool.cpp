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
        float total_bezier_perimeter;
        
        /*for(int i = 0; i < projection.size(); i++){
        
            if(projection.beziers[i].exists){
                // find distance to the next point
                total_bezier_perimeter += projection[i].distance(projection[(i+1)%(projection.size()-1)]);
            }
        }*/
        
        total_perimeter = projection.get_perimeter();
        
        //float bezier_pct;
        
        //float adjusted_perimeter = total_perimeter - total_bezier_perimeter + total_bezier_perimeter*bezier_pct;
        
        // do a lazy first passthrough of all points
        
       // number_of_verticies = projection.size();
        
        int used_points = 0;
        allowed_points.clear();
        
            
        for(int i = 0; i < projection.beziers.size(); i++){
            ofVec2f direction = projection.beziers[i].p1 - projection.beziers[i].p2;
            float length = direction.distance(direction.zero());
            
            float pct = length/total_perimeter;
            
            //if(projection.beziers[i].exists) bezier_pct *= pct;
                
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
