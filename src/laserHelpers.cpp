//
//  laserHelpers.cpp
//  ofxSmartLaser
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
    
    float bez_ease_func(float t){
        //float x = t*t;
        float x;
        float exp = 2;
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
        if(params.resample_type != curves){
            
            for(int i = 0; i < projection.size(); i++){
                
                int allowed_points = point_pool.get_allowed_points(i);
            
                // make a vector valued function
                ofVec2f direction = projection.lines[i];
                ofVec2f starting_point = projection[i];
                
                // get bezier poly
                Laser::Bezier bezier = projection.beziers[i];
                
                // find percentage area that each segment gets
                if(bezier.exists){
                    
                    // saves on calculation
                    ofVec2f current_point = starting_point;
                    ofVec2f next_point = starting_point+direction;
                    
                    switch (params.bezier_sample_type) {
                            
                        case exact:
                            // for each point
                            for(int j = 0; j < allowed_points; j++){
                                
                                float pct = ((float)j)/((float)(allowed_points));
                                
                                // get point that is pct into the bezier curve and add it to the poly
                                resampled_projection.addVertex(bezier.get_point(pct, current_point, next_point));
                                resampled_projection.colors.push_back(projection.colors[i]);
                                
                            }
                            break;
                            
                        case midpoint:

                            // for each section created by a midpoint
                            for(int j = 0; j <= params.midpoints; j++){
                                
                                int allowed_points_per_bez_sec = allowed_points/(params.midpoints+1);

                                // for the allowed points
                                for(int k = 0; k < allowed_points_per_bez_sec; k++){
                                    
                                    float pct =  ((float)k)/((float)allowed_points_per_bez_sec);
                                    float step_size = 1/((float)params.midpoints+1);
                                    
                                    // move through based on easing function
                                    float adjusted_pct = j*step_size + step_size*ease_func(pct);

                                    // add a vertex corresponding to the bezier curve, and add the colot
                                    resampled_projection.addVertex(bezier.get_point(adjusted_pct, current_point, next_point));
                                    resampled_projection.colors.push_back(projection.colors[i]);

                                }
                                
                            }
                            break;
                    }

                
                }
                else{
                    // for each allowed point
                    for(int j = 0; j < allowed_points; j++){
                        
                        float pct = ((float)j)/((float)(allowed_points));
                        
                        // swap colors over, could use a lot of work
                        resampled_projection.colors.push_back(projection.colors[i]);
                        switch (params.resample_type) {
                                
                            case vertex: resampled_projection.addVertex(projection[i]); break;
                                
                            case uniform: resampled_projection.addVertex(starting_point + pct*direction); break;
                                
                            case adjusted: resampled_projection.addVertex(starting_point + ease_func(pct)*direction); break;
                                
                        }
                        
                    }
                
                }
            
            }
        }
        
        
        return resampled_projection;
    }
    
    Laser::Projection connect_the_dots(vector <Laser::Poly> original_polys, parameters params){
        
        Laser::Projection spaced_projection;
 
        
        vector <Laser::Poly> nn_polys = original_polys;
        
        // start out with the first shape
        Laser::Poly current_poly = nn_polys[0];
        
        // remove first poly form the list so it doesnt decide to connect to itself
        nn_polys.erase(nn_polys.begin());
        
        for(int i = 1; i < original_polys.size(); i++){
            
            float shortest_distance = 1000000;
            int shortest_index;
            
            // look at the points remaining and find the closest one
            for(int j = 0; j < nn_polys.size(); j++){
                
                float distance = current_poly[0].squareDistance(nn_polys[j][0]);
                
                if(distance < shortest_distance){
                    
                    shortest_distance = distance;
                    shortest_index = j;
                    
                }
            }
            
            // add current poly to connected polys
            spaced_projection.add_poly(current_poly);
            
            // move to the next poly for the next round
            current_poly = nn_polys[shortest_index];
            
            // remove nearest neighbor from the list
            nn_polys.erase(nn_polys.begin() + shortest_index);
        }
        
        // add the last one
        spaced_projection.add_poly(current_poly);
        
        //connect to the end
        spaced_projection.finish(params);
        
        return spaced_projection;
        
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
