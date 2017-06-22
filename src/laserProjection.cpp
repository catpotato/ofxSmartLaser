//
//  laserProjection.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/7/17.
//
//

#include "laserProjection.h"

namespace Laser{
    
    // called by connect the dots to add a poly to this big poly
    void Projection::add_poly(Laser::Poly poly){
        

        // add first point
        this->addVertex(poly.get_starting_point());
        
        this->beziers.push_back(poly.beziers[0]);
        this->colors.push_back(poly.color);
        // loops through everything except first and last points
        for(int i = 1; i < poly.size()-1; i++){
            this->addVertex(poly[i]);
            this->beziers.push_back(poly.beziers[i]);
            this->colors.push_back(poly.color);
        }
        // last point
        this->addVertex(poly.get_final_point());
        //cout << "final point" << poly.get_final_point() << endl;
        this->beziers.push_back(Laser::Bezier(false));
        this->colors.push_back(ofColor::black);
        
        
    };
    
    void Projection::finish(parameters params){
        //close shape
        this->close();
        // make lines
        this->setup_lines(params);
    }
    
    void Projection::setup_lines(parameters params){
        
        // this makes lines for rendering, but also fills in the p2's for the bezier's
        for(int i = 0; i < this->size(); i++){
            
            ofVec2f starting_point = (*this)[i];
            ofVec2f final_point = (*this)[(i+1)%(this->size())];
            
            this->beziers[i].set_midpoints(params);
            
            ofVec2f direction = final_point - starting_point;
            lines.push_back(direction);
            
        }
    }
    
    vector <ofxIlda::Point> Projection::get_points(){
        vector <ofxIlda::Point> points;
        
        for(int i = 0; i < this->size(); i++){
            
            ofxIlda::Point point;
            ofVec2f temp =(*this)[i];
            
            point.set(temp, this->colors[i]);
            points.push_back(point);
        }
        
        return points;
        
    }
    
    void Projection::connect_the_dots(vector <Laser::Poly> original_polys, parameters params){
        
        // clear polyline, since there could be guff in there from before
        this->clear();
        // same with colors
        colors.clear();
        
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
            this->add_poly(current_poly);
            
            // move to the next poly for the next round
            current_poly = nn_polys[shortest_index];
            
            // remove nearest neighbor from the list
            nn_polys.erase(nn_polys.begin() + shortest_index);
        }
        
        // add the last one
        this->add_poly(current_poly);
        
        //connect to the end
        this->finish(params);
        
    }
    
    void Projection::draw_to_screen(parameters params){
        
        for(int i = 0; i < this->size() - 1; i++){
            
            ofColor color = this->colors[i];
            
            // so that black shows up
            if(color == ofColor::black) color = ofColor::grey;
            ofSetColor(color);
            
            // draw each point
            ofDrawCircle((*this)[i], 1.3);
            // draw each line
        }
    }
    
    void Projection::copy(Laser::Poly poly, ofColor color, int index){
        // if first point
        /*if(index == 0){
            
            this->addVertex(poly.get_starting_point());
        
        }
        else if(index == poly.size()-1){
            this->addVertex(poly.get_final_point());
        }
        else{
            
        }*/
        poly.setup_lines();
        poly.beziers[index].p1 = poly[index];
        poly.beziers[index].p2 = poly[index] + poly.lines[index];
        poly.beziers[index].update_control_points();
        
        this->addVertex(poly[index]);
        
        
        this->beziers.push_back(poly.beziers[index]);
        this->colors.push_back(color);
    }
    
    
}
