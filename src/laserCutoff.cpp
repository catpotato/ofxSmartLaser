//
//  laserCutoff.cpp
//  speed
//
//  Created by Clark Addis on 6/15/17.
//
//

#include "laserCutoff.h"

namespace Laser {
    
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

                Vector_Line current_line(current_poly[j], current_poly.lines[j]);
 
                //cout << "poly number: " << j << endl;
            
                if(current_poly.beziers[j].exists){
                    
                    //final_polys = polys;
                    
                    // bezier cutoff
                    Laser::Bezier current_bezier = current_poly.beziers[j];
                    
                    // find intersection between this bezier and the lines
                    vector <float> intersections = current_bezier.get_valid_intersections(current_poly[j], current_poly.lines[j]);
                    
                    // intialize for use in loop
                    int step = 0;
                    
                    // if first point for bezier is not in the bounding box
                    
                    cout << "current_poly[j]: " << current_poly[j] << endl;
                    if(in_bounding_box(current_poly[j])){
                        step = 1;
                        final_poly.add_vertex_bez(current_poly[j], current_poly.lines[j], current_bezier);
                        cout << "j: " << j << endl;
                        cout << "final_poly.size(): "<< final_poly.size() << endl;
                    }
                    
                    cout << "step: "  << step << endl;
                    
                    //cout << intersections.size() << " intersections were found" << endl;
                    cout << "final_poly.size(): "<< final_poly.size() << endl;
                    for(int k = 0; k < intersections.size(); k++){
                        //cout << intersections[k];
                        step++;
                        cout << "step: "  << step << endl;
                        
                        cout << "1 % 2: " << 1%2 << endl;
                        cout << "step % 2: " << step%2 << endl;
                        if(step % 2 == 1){
                            cout << "HONK" << endl;
                            // start new shape
                            final_poly.add_vertex_bez(current_poly[j], current_poly.lines[j], current_bezier);
                            
                            // add start t
                            final_poly.beziers[final_poly.size()-1].start_pct = intersections[k];
                            
                        }
                        
                        // step is even, first point is in bounds
                        if(step % 2 == 0){
                            
                            // add bezier
                            // final_poly.add_vertex_bez(current_poly[j], current_poly.lines[j], current_bezier);
                            // check if previous was a bezier??
                            cout << "step: "  << step << endl;
                            // add end t on last element
                            cout << final_poly.size() << endl;
                            final_poly.beziers[final_poly.size()-1].end_pct = intersections[k];
                            
                            // end shape
                            final_polys.push_back(final_poly);
                            final_poly.clear();
                            
                        }
                        
                        
                        
                        
                    }
                 
                    
                    
                }
                else{
                
                    // nothing to do
                    if(current_line.completely_inside()) final_poly.add_vertex(current_poly[j]);

                    
                    // figure out if there are one or two points of intersection
                    else{
                        
                        vector <ofVec2f> intersections = current_line.get_valid_intersections();
                        
                        // a single intersection
                        if(intersections.size() == 1){
                            
                            // if current point is inside, means that intersection is next point, need to end a poly
                            if(in_bounding_box(current_poly[j])){
                                
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
                        
                            vector <ofVec2f> ordered_points = order_points(intersections, current_poly[j]);
            
                            final_poly.add_vertex(ordered_points[0]);
                            final_poly.add_vertex(ordered_points[1]);

                            final_polys.push_back(final_poly);
                            final_poly.clear();
            
                        }
                    }
                }
            }
            
            if(in_bounding_box(current_poly[current_poly.size() - 1])) final_polys.push_back(final_poly);
        
        }
        //final_polys = polys;
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
        if(pt.squareDistance(intersections[0]) < pt.squareDistance(intersections[1])){
            ordered_points.push_back(intersections[0]);
            ordered_points.push_back(intersections[1]);
            
        }
        else {
            ordered_points.push_back(intersections[1]);
            ordered_points.push_back(intersections[0]);
            
        }
        
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
