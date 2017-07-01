//
//  laserCutoff.cpp
//  speed
//
//  Created by Clark Addis on 6/15/17.
//
//

#include "laserCutoff.h"

namespace Laser {
    
    vector <Laser::Poly> slice_off_edges(vector <Laser::Poly> polys){

        vector <Laser::Poly> final_polys;
        
        // for each poly
        for(int i = 0; i < polys.size(); i++){
            
            Laser::Poly final_poly;
            Laser::Poly current_poly = polys[i];

            // for each point
            for(int j = 0; j < current_poly.size(); j++){
                
                Laser::Bezier current_bezier = current_poly.beziers[j];

                // find intersection between this bezier and the lines
                vector <float> intersections = current_bezier.get_valid_intersections();
                    
                // intialize for use in loop
                int step = 0;
                    
                // if first point for bezier is in the bounding box
                if(in_bounding_box(current_poly.beziers[j].p1)){
                        
                    // such that step will be odd when it enters the loop
                    step = 1;
                        
                    // add a bezier; this also is to ensure that normal beziers still pass
                    final_poly.add_vertex_bez(current_poly.beziers[j].p1, current_poly.beziers[j].p2, current_bezier);
                }

                for(int k = 0; k < intersections.size(); k++, step++){

                    // if odd, or if first point is out of bounds
                    if(step % 2 == 0) final_poly.start_cut_bez(intersections[k], current_bezier);
                        
                    // step is even, first point is in bounds
                    if(step % 2 == 1){
                            
                        final_poly.end_cut_bez(intersections[k], current_bezier);
                            
                        // send final shape
                        final_poly.color = current_poly.color;
                        final_polys.push_back(final_poly);
                        final_poly = Laser::Poly();
                            
                    }
                        
                }
                
            }
            if(final_poly.size()) final_poly.color = current_poly.color; final_polys.push_back(final_poly);
        
        }
        return final_polys;
    
    }

    bool in_bounding_box(ofVec2f pt){
        
        if(pt.y > ofGetWidth()) return false;
        if(pt.y < 0) return false;
        if(pt.x > ofGetHeight()) return false;
        if(pt.x < 0) return false;
        
        return true;
    
    }
    
}
