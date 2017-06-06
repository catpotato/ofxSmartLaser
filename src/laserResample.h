//
//  laserResample.h
//  laserProjector
//
//  Created by Clark Addis on 5/31/17.
//
//

#ifndef laserResample_h
#define laserResample_h

#include <stdio.h>
#include "laserPoly.h"
//#include "laserStructs.h"
//#include "laserPointPool.h"
#include <cmath>
namespace Laser{
    
    /*float ease_func(float t){
        //float x = t*t;
        float x;
        float exp = 2;
        if(t < .5){
            x = .5*pow(2*t, exp);
        }
        else{
            x = -.5*pow(2*(t-.5), exp) + 1;
        }
        //float x = .5*(2*t)*(2*t);
        return x;
    }*/
    
    /*void resample(vector <Laser::Poly> original_polys, vector <Laser::Poly> & resampled_polys, parameters params, Laser::PointPool point_pool){
        
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
                    
                    float pct = ((float)k)/((float)(allowed_points-1));
                    
                    switch (params.resample_type) {
                            
                        case vertex: resampled_poly.addVertex(current_poly[j]); break;
                            
                        case uniform: resampled_poly.addVertex(starting_point + pct*direction); break;
                            
                        case adjusted: resampled_poly.addVertex(starting_point + ease_func(pct)*direction); break;
                            break;
                    }
                    
                }
                
            }
            
            resampled_polys.push_back(Laser::Poly(resampled_poly, original_polys[i].color));
            
        }
        
    }*/
    
    
    /*void resample(vector <Laser::Poly> original_polys, vector <Laser::Poly> & resampled_polys, int number_of_points, float total_perimeter, bool lazy){
        
        // get that squared away
        //resampled_polys.clear();
        
        // for each polygon
        /*for(int i = 0; i < original_polys.size(); i++){
            
            ofPolyline resampled_poly;
            Laser::Poly current_poly = original_polys[i];
            
            // find the number of poitns they're allowed to use
            float poly_perimeter = current_poly.getPerimeter();
            int allowed_points = ((float)number_of_points)*(poly_perimeter/total_perimeter);
            int points_per_lazy = allowed_points/current_poly.size();
            
            ofVec2f starting_point = current_poly[current_poly.size()-1];
            
            // go through each line of the polyline
            for(int j = 0; j < current_poly.size(); j++){
                
                if(!lazy){
                    
                    // figure out how many points this line of the poly line gets
                    // there is room for a smarter function here methinks
                    
                    ofVec2f final_point = current_poly[j];
                    //cout << "current_poly.lines : " << current_poly.lines[j] << endl;
                    float distance = starting_point.distance(final_point);
                    int line_allowed_points = ((float)allowed_points)*(distance/poly_perimeter);
                    
                    for(int k = 0; k < line_allowed_points; k++){
                        
                        // by using the easing function above
                        float pct = ((float)k)/((float)(line_allowed_points-1));*/
                        //float t = pct/*ease_func(pct)*/;
                        /*
                        //make a vector valued function
                        ofVec2f direction = final_point - starting_point;
                        
                        ofVec2f eased_point = starting_point + t*direction;
                        resampled_poly.addVertex(eased_point);
                        
                    }
                    
                    // old fashioned "previous = current"
                    starting_point = final_point;
                }
                
                else{
                    for(int k = 0; k < points_per_lazy; k++){
                        resampled_poly.addVertex(current_poly[j]);
                    }
                }
                
                
            }
            //push back the polygon that you made
            resampled_polys.push_back(Laser::Poly(resampled_poly, original_polys[i].color));
            
        }
        cout << "what the fuck is going on";
        
    }
                         */
    
    
}

#endif /* laserResample_h */
