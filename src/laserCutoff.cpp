//
//  laserCutoff.cpp
//  speed
//
//  Created by Clark Addis on 6/15/17.
//
//

#include "laserCutoff.h"

namespace Laser {
    /*vector <Laser::Poly> slice_off_edges(vector <Laser::Poly> polys){
     
        vector <Laser::Poly> final_polys;
     
        // for each poly
        for(int i = 0; i < polys.size(); i++){
     
            Laser::Poly final_poly;
     
            Laser::Poly current_poly = polys[i];
     
            for(int j = 0; j < current_poly.size(); j++){
     
                if(current_poly.beziers[j].exists){
                    // do the bezier chopping, FAIRLY complicated algorithm
                }
                else{
                    // should probably do a more generalized algebra solver here but sounds like too much work for what its worth
     
                    // might want a simple check up here to see if next line and stuff and within the boudnaries, not that impt tho, unless a performance bottleneck
     
     float x_top_val = solve_for_x(0, current_poly[i], current_poly.lines[i]);
     
     float x_bottom_val = solve_for_x(ofGetHeight(), current_poly[i], current_poly.lines[i]);
     
     float y_left_val = solve_for_y(0, current_poly[i], current_poly.lines[i]);
     
     float y_right_val = solve_for_y(ofGetWidth(), current_poly[i], current_poly.lines[i]);
     
     // make sure intersections are within bounds of border
     
     // corespodents
     enum sides {        x_top,  x_bottom,   y_left, y_right};
     bool valid[4] = {   true,   true,       true,   true};
     ofPoint points[4] = {ofPoint(x_top_val, 0), ofPoint(x_bottom_val, ofGetHeight()), ofPoint(0, y_left_val), ofPoint(ofGetWidth(), y_right_val)};
     
     // if past the boudnaries of the borders, then invalidate
     if(x_top_val < 0 || x_top_val > ofGetWidth()) valid[x_top] = false;
     if(x_bottom_val < 0 || x_bottom_val > ofGetWidth()) valid[x_bottom] = false;
     if(y_left_val < 0 || y_left_val > ofGetHeight()) valid[y_left] = false;
     if(y_right_val < 0 || y_left_val > ofGetHeight()) valid[y_right] = false;
     
     // if the line does not actually pass through the point
     // basically, when you plug in the numbers, do you get the same or different t values
     // potential room for optimization here, maybe let the
     // the point DOES lie on the line, the question is, is the t value required for that line not btween 1 and 0
     
     float x_top_t = get_t_x(x_top_val, current_poly[i], current_poly.lines[i]);
     float x_bottom_t = get_t_x(x_bottom_val, current_poly[i], current_poly.lines[i]);
     float y_left_t = get_t_y(y_left_val, current_poly[i], current_poly.lines[i]);
     float y_right_t = get_t_y(y_right_val, current_poly[i], current_poly.lines[i]);
     
     // get t values for the point that intersects the line
     
     // if the t values are not between 1 and 0, invalidate
     
     if(x_top_t > 1 || x_top_t < 0) valid[x_top] = false;
     if(x_bottom_t > 1 || x_bottom_t < 0) valid[x_bottom] = false;
     if(y_left_t > 1 || y_left_t < 0) valid[y_left] = false;
     if(y_right_t > 1 || y_right_t < 0) valid[y_right] = false;
     
     // now all validation is complete
     
     //count up number of valid intersections
     int valid_intersections = 0;
     for(int i = 0; i < 4; i++) if(valid[i]) valid_intersections++;
     // GET VALUES OF THE FREAKING X AND Y'S THAT THESE LITTLE SHITS DO
     
     switch(valid_intersections){
     case 0:{
     // figure out if both points are in or both points are out, can do that by figuring out if one point is in
     if(in_bounding_box(current_poly[i])) final_poly.add_vertex(current_poly[i]);
     // dont do anything otherwise, since that means it is a line drawn completey outside the box
     break;
     
     }
     
     case 1:
     // are we coming in from the outside, or going out from the inside
     //                            if(/*intersection going from current point to intersection*///){
    //                                final_poly.add_vertex(current_poly[i]);
    // add intersection point, and stop the polygon
    //                                final_poly.add_vertex(/*intersection point*/);
    // end this poly
    //                            }
    //                            else{
    // intersection going from intersection point to the next point
    // start a new poly
    //                                final_poly.add_vertex(/*intersection point*/);
    
    //                            }
    //                            break;
    //                        case 2:
    // make new poly
    //                            if(/*intersction goinf from first to second*/){
    //                                final_poly.add_vertex(/*first intersection*/);
    //                                final_poly.add_vertex(/*final intersection*/);
    //                            }
    //                            else{
    //                                final_poly.add_vertex(/*final intersection*/);
    //                                final_poly.add_vertex(/*first intersection*/);
    
    //                            }
    // end poly
    
    //                            break;
    //                    }
    // if it intersects no lines, consider not rendering it, if it is in bounds though, render completely
    
    // if it is intersecting two lines, render from the intersection onwards
    
    // if it is intersecting one line, render from intersection to point thats in
    // OR render from the point to the intersection
    
    
    
    
    
    
    //                }
    //
    //            }
    //        }
    //    }
    //    bool going_from_current_point(ofPoint )
    
    
    Vector_Line::Vector_Line(ofVec2f pt, ofVec2f dir): starting_point(pt), direction(dir){};
    
    bool Vector_Line::completely_inside(){
        
        if(!in_bounding_box(starting_point)) return false;
        if(!in_bounding_box(starting_point+direction)) return false;
        
        return true;
    
    }
    
    bool Vector_Line::completely_outside(){
    
        if(in_bounding_box(starting_point)) return false;
        if(in_bounding_box(starting_point+direction)) return false;
        
        return true;
        
    }
    
    Intersection::Intersection(Vector_Line l): line(l){};
    
    
    vector <Laser::Poly> slice_off_edges(vector <Laser::Poly> polys){
        
        vector <Laser::Poly> final_polys;
        
        // for each poly
        for(int i = 0; i < polys.size(); i++){
            
            Laser::Poly final_poly;
        
            Laser::Poly current_poly = polys[i];
            
            // for each point (minus the last one i guess?) look back at this  LOOK BACK AT THIS YOU CHUM!!!!!
            for(int j = 0; j < current_poly.size(); j++){
                //cout << j << " : ";
                Vector_Line current_line(current_poly[j], current_poly.lines[j]);
 
            
                if(current_poly.beziers[j].exists){
                
                    // bezier cutoff
                }
                else{
                
                    // normal cutoff
                    if(current_line.completely_inside()) {
                        final_poly.add_vertex(current_poly[j]);
                        //cout << "completely inside" << endl;
                    }
                
                    // don't render anything
                    //else if(current_line.completely_outside()); //cout << "completely outside" << endl;
                    
                    // figure out if there are one or two points of intersection
                    else{
                        
                        vector <ofVec2f> intersections = current_line.get_valid_intersections();
                        
                        // a single intersection
                        if(intersections.size() == 1){
                            //cout << "1 intersection" << endl;
                            // if current point is inside, means that intersection is next point, need to end a poly
                            if(in_bounding_box(current_poly[j])){
                                
                                //cout << "this point is inside" << endl;
                                
                                final_poly.add_vertex(current_poly[j]);
                                final_poly.add_vertex(intersections[0]);
                                
                                // ends the poly
                                final_polys.push_back(final_poly);
                                
                                // clears poly for next person to use
                                final_poly.clear();
                                
                            }
                            // if current point is outside, means we need to start a new shape with intersection as first point
                            else final_poly.add_vertex(intersections[0]);
                        
                        }
                        
                        // two intersections, only one possibly scenario, so need to start a new shape, add closer point, then add other point, then close shape
                        if(intersections.size() == 2){
                            //cout << "2 intersections" << endl;
                        
                            vector <ofVec2f> ordered_points = order_points(intersections, current_poly[j]);

                            final_poly.add_vertex(ordered_points[0]);
                            final_poly.add_vertex(ordered_points[1]);

                            final_polys.push_back(final_poly);
                            final_poly.clear();
                        
                        
                        }
                        
                    
                    }
                    
                }
                
            }
            if(in_bounding_box(current_poly[current_poly.size() - 1])){
                final_polys.push_back(final_poly);
            }
        
        }
        return final_polys;
        
    
    
    }
    
    vector <ofVec2f> Vector_Line::get_valid_intersections(){
        
        vector <Intersection> intersections = get_all_intersections((*this));
        vector <ofVec2f> valid_intersections;
        
        for(int i = 0; i < intersections.size(); i++){
        
            if(intersections[i].valid){
            
                valid_intersections.push_back(intersections[i].point);
                
            }
            
        }
        
        return valid_intersections;
        
    
    }
    
    vector <Intersection> get_all_intersections(Vector_Line line){
    
        vector <Intersection> intersections;
        
        // for each, find t
        Intersection top(line);
        Intersection bottom(line);
        Intersection left(line);
        Intersection right(line);
        
        // fill in what we know to be true about each point
        top.set_y(0);
        bottom.set_y(ofGetHeight());
        left.set_x(0);
        right.set_x(ofGetWidth());
        
        // push back to final array
        intersections.push_back(top);
        intersections.push_back(bottom);
        intersections.push_back(left);
        intersections.push_back(right);
        
        // send it off
        return intersections;
        
    
    }
    
    void Intersection::set_x(float x){
        
        float t = (x - line.starting_point.x)/line.direction.x;
        float y = line.starting_point.y + line.direction.y*t;
        
        // validate within canvas
        if(y > ofGetHeight()) valid = false;
        if(y < 0) valid = false;
        
        // validate within line for y
        vector <float> ordered_y = order_values(line.starting_point.y, line.starting_point.y + line.direction.y);
        if(y < ordered_y[0]) valid = false;
        if(y > ordered_y[1]) valid = false;
        
        // validate within line for x
        vector <float> ordered_x = order_values(line.starting_point.x, line.starting_point.x + line.direction.x);
        if(x < ordered_x[0]) valid = false;
        if(x > ordered_x[1]) valid = false;
    
        point = ofVec2f(x,y);
        
    }
    void Intersection::set_y(float y){
        
        float t = (y - line.starting_point.y)/line.direction.y;
        float x = line.starting_point.x + line.direction.x*t;
        
        // validate
        if(x > ofGetWidth()) valid = false;
        if(x < 0) valid = false;
        
        // validate within line for x
        vector <float> ordered_x = order_values(line.starting_point.x, line.starting_point.x + line.direction.x);
        if(x < ordered_x[0]) valid = false;
        if(x > ordered_x[1]) valid = false;
        
        // validate within line for y
        vector <float> ordered_y = order_values(line.starting_point.y, line.starting_point.y + line.direction.y);
        if(y < ordered_y[0]) valid = false;
        if(y > ordered_y[1]) valid = false;
        
        point = ofVec2f(x,y);
        
        
    }
    vector <ofVec2f> order_points(vector <ofVec2f> intersections, ofVec2f pt){
        
        vector <ofVec2f> ordered_points;
        
        // if intersections[0] is closer than intersections[1]
        if(pt.squareDistance(intersections[0]) < pt.squareDistance(intersections[1])) ordered_points.push_back(intersections[0]);
        else ordered_points.push_back(intersections[1]);
        
        return ordered_points;
    
    }
    
    vector <float> order_values(float v1, float v2){
        vector <float> final;
        if(v1 < v2){
            final.push_back(v1);
            final.push_back(v2);
        }
        else{
            final.push_back(v2);
            final.push_back(v1);
        
        }
        return final;
    }
    
    bool in_bounding_box(ofVec2f pt){
        if(pt.y > ofGetWidth()) return false;
        if(pt.y < 0) return false;
        if(pt.x > ofGetHeight()) return false;
        if(pt.x < 0) return false;
        
        return true;
    
    }
    
}
