//
//  laserHelpers.cpp
//  laserProjector
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserHelpers.h"
namespace Laser{
    
    /*
     
     easing function for "adjusted" resampling
     
     */
    
    float ease_func(float t){
        //float x = t*t;
        float x;
        float exp = 4;
        if(t < .5){
            x = .5*pow(2*t, exp);
        }
        else{
            x = -.5*pow(2*(t-1), exp) + 1;
        }
        //float x = .5*(2*t)*(2*t);
        return x;
    }
    
    /*
     
     resampler: takes in original polys, modifies them based on paramerters, then spits out the resampled polys
     
     */
    
    Laser::Projection resample(Laser::Projection projection, parameters params, Laser::PointPool point_pool){
        
        // get that squared away
        Laser::Projection resampled_projection;
        
        // for each vertex
        for(int i = 0; i < projection.size(); i++){
            
            int allowed_points = point_pool.get_allowed_points(i);
            
            // make a vector valued function
            ofVec2f direction = projection.lines[i];
            ofVec2f starting_point = projection[i];
            
            // for each allowed point
            for(int j = 0; j < allowed_points; j++){
                
                float pct = ((float)j)/((float)(allowed_points));
                
                // swap the colors over << THIS COULD USE SOME REAL WORK
                resampled_projection.colors.push_back(projection.colors[i]);
                
                switch (params.resample_type) {
                        
                    case vertex: resampled_projection.addVertex(projection[i]); break;
                        
                    case uniform: resampled_projection.addVertex(starting_point + pct*direction); break;
                        
                    case adjusted: resampled_projection.addVertex(starting_point + ease_func(pct)*direction); break;
                }
            }
        }
        
        return resampled_projection;
    }
    
    
    
    /*
     
     noarmalizer: laser takes coordinates from 0 -> 1 so they have to be normalized. they also need to be flipped cause my projector is strange
     
     */

    Laser::Projection normalize(Laser::Projection projection, ofVec2f window_dimensions){
        for(int i = 0; i < projection.size(); i++){
            
            projection[i].x = 1 - projection[i].x/window_dimensions.x;
            projection[i].y = 1 - projection[i].y/window_dimensions.y;

        
        }
        return projection;
    }
}
