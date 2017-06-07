//
//  laserPointPool.cpp
//  laserProjector
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserPointPool.h"
namespace Laser{
    
    void PointPool::update_polys(vector <Laser::Poly> polys){
        
        // update total perimeter
        total_perimeter = 0;
        
        for(int i = 0; i < polys.size(); i++){
            total_perimeter += polys[i].getPerimeter();
        }
        
        // do a lazy first passthrough of all points
        
        int used_points = 0;
        allowed_points.clear();
        
        for(int i = 0; i < polys.size(); i++){
            
            Laser::Poly current_poly = polys[i];
            vector <int> poly_allowed_points;
            
            for(int j = 0; j < current_poly.size(); j++){
                
                ofVec2f direction = current_poly.lines[j];
                float length = direction.distance(direction.zero());
                
                float pct = length/total_perimeter;
                int temp_allowed_points = round(pct*(params.max_points - params.spacing_points*polys.size()));
                
                used_points += temp_allowed_points;
                poly_allowed_points.push_back(temp_allowed_points);
                
            }
            
            allowed_points.push_back(poly_allowed_points);
            
        }
        
        // i could implement giving extra points to smaller lines here, but it really seems like more hassle than it is worth, considering i can just use the dense point thing if it really does make a difference
        
        
        
        
        // give me the polygons!
        original_polys = polys;
    }
    
    
    void PointPool::update_params(parameters _params){
    
        params = _params;
        
    }
    
    int PointPool::get_allowed_points(int poly, int vertex){
        
        ofVec2f direction = original_polys[poly].lines[vertex];
        float length = direction.distance(direction.zero());
        
        float pct = length/total_perimeter;
        
        if(params.constant_point_per_line){
            return params.points_per_line;
        }
        else{
            
            return allowed_points[poly][vertex];
        }
        
        
        
    }
}
