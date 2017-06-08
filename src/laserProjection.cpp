//
//  laserProjection.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/7/17.
//
//

#include "laserProjection.h"

namespace Laser{
    
    void Projection::add_poly(Laser::Poly poly){
        
        for(int i = 0; i < (int)poly.size(); i++){

            ofColor color;
            
            // if it's the last one of a poly, add in a black point, since there will be a move after it
            if(i == (poly.size() - 1)) color = ofColor::black;
            
            else color = poly.color;
            
            this->addVertex(poly[i]);
            colors.push_back(color);
        }
        
    };
    
    void Projection::finish(){
        //close shape
        this->close();
        // make lines
        this->setup_lines();
    }
    
    void Projection::setup_lines(){
        
        for(int i = 0; i < this->size(); i++){
            
            ofVec2f starting_point = (*this)[i];
            ofVec2f final_point = (*this)[(i+1)%(this->size())];
            
            ofVec2f direction = final_point - starting_point;
            lines.push_back(direction);
            
        }
    }
    
    vector <ofxIlda::Point> Projection::get_points(){
        vector <ofxIlda::Point> points;
        
        for(int i = 0; i < this->size(); i++){
            ofxIlda::Point point;
            point.set((*this)[i], this->colors[i]);
            points.push_back(point);
        }
        
        return points;
        
    }
    
    void Projection::spew(){
        for(int i = 0; i < this->size(); i++){
            cout << "point : " << (*this)[i] << ", color : " << this->colors[i] << endl;
        }
    }
    
    void Projection::connect_the_dots(vector <Laser::Poly> original_polys){
        
        this->clear();
        
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
        this->finish();
        
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
            ofDrawLine((*this)[i], (*this)[i+1]);
        }
    }
    
    
}
