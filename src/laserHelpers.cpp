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
    
    void resample(vector <Laser::Poly> original_polys, vector <Laser::Poly> & resampled_polys, parameters params, Laser::PointPool point_pool){
        
        // get that squared away
        
        resampled_polys.clear();
        
        // for each polygon
        for(int i = 0; i < original_polys.size(); i++){
            
            ofPolyline resampled_poly;
            Laser::Poly current_poly = original_polys[i];
            
            // for each vertex
            for(int j = 0; j < original_polys[i].size(); j++){
                
                //ask the point pool how many points it gets
                int allowed_points = point_pool.get_allowed_points(i, j);
                
                //set up the vector valued function for the k loop to use
                ofVec2f direction = original_polys[i].lines[j];
                ofVec2f starting_point = original_polys[i][j];
                
                // for each allowed point
                for(int k = 0; k < allowed_points; k++){
                    
                    
                    float pct = ((float)k)/((float)(allowed_points));
                    
                    switch (params.resample_type) {
                            
                        case vertex: resampled_poly.addVertex(current_poly[j]); break;
                            
                        case uniform: resampled_poly.addVertex(starting_point + pct*direction); break;
                            
                        case adjusted:{
                            resampled_poly.addVertex(starting_point + ease_func(pct)*direction);
                            break;
                        
                        }
                        
                    }
                    
                }
                
            }
            
            resampled_polys.push_back(Laser::Poly(resampled_poly, original_polys[i].color));
            
        }
        
    }
    
    /*
     
     spacer: adds spaces betwixt shapes and specific instructions for how they should be drawn to help minimize overshooting
     
     this takes advtange of the fact that resampled polys gives me back still discrete polygons
     
     */
    
    void connect_the_dots(vector <Laser::Poly> original_polys, Laser::Poly & connected_poly){
        
        vector <Laser::Poly> nn_polys = original_polys;
        
        // start out with the first shape
        Laser::Poly current_poly = nn_polys[0];
        
        // remove first poly form the list so it doesnt decide to connect to itself
        nn_polys.erase(nn_polys.begin());
        
        // for each starting point, except for the last one (because it is special, needs to get back to the starting point)
        for(int i = 1; i < original_polys.size(); i++){
            
            //cout << i << endl;
            
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
            
            // add all of the vertexes from the current poly
            for(int j = 0 ; j < current_poly.size(); j++) connected_poly.addVertex(current_poly[j]);
            
            // move to the next poly for the next round
            current_poly = nn_polys[shortest_index];
            
            // remove nearest neighbor from the list
            nn_polys.erase(nn_polys.begin() + shortest_index);
        }
        
        for(int i = 0; i < current_poly.size(); i++){
            connected_poly.addVertex(current_poly[i]);
        }
        
        connected_poly.close();
    
    }
    
    /*
     
     noarmalizer: laser takes coordinates from 0 -> 1 so they have to be normalized. they also need to be flipped cause my projector is strange
     
     */

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
