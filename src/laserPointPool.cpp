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
        
        // give me the polygons!
        original_polys = polys;
    }
    
    
    void PointPool::update_params(parameters _params){
    
        params = _params;
        
        //total_points = params.allowed_points;
        
        
    }
    
    /*void PointPool::update_params(params){
    
    }*/
    
    int PointPool::get_allowed_points(int poly, int vertex){
        
        ofVec2f direction = original_polys[poly].lines[vertex];
        float length = direction.distance(direction.zero());
        
        float pct = length/total_perimeter;
        
        //cout << int(pct*(params.max_points - params.blank_points)) << endl;
        
        return int(pct*(params.max_points - params.blank_points));
        
        
        //cout << "length : " << length << endl;
        
        //cout << "help i'm trapped in a funciton!!";
        
        //return 4;
        
    }
}
