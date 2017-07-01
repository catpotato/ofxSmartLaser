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
        
        if(beziers.size()) connect_to(poly.get_starting_point());
        
        for(int i = 0; i < poly.size(); i++){
            
            beziers.push_back(poly.beziers[i]);
            cout << "pushing back " << poly.color << endl;
            colors.push_back(poly.color);
        
        }
    }
    
    void Projection::connect_to(ofVec2f p2){
        
        
        //for(int i = 0; i < beziers.size(); i++) beziers[i].spew();
        
        ofVec2f p1 = beziers[beziers.size()-1].get_final_point();
        ofVec2f diff = p2 -p1;
        
        // makes a bezier that is exactly a line
        ofVec2f cp1 = p1 + diff/3;
        ofVec2f cp2 = p1 + 2*diff/3;
        

        beziers.push_back(Laser::Bezier(p1,cp1,cp2,p2));
        colors.push_back(ofColor::black);
        
    }

    
    void Projection::finish(parameters params){
        // close shape
        // once again, really f-ed up hack
        if(beziers[0].get_point(0).distance(beziers[beziers.size()-1].get_point(1)) > 2) connect_to(beziers[0].get_point(0));

    }
    

    void Projection::add_laser_dot(ofVec2f pt, ofColor color){
        
        this->addVertex(pt);
        this->colors.push_back(color);
    }
    
    ofColor Projection::get_color(int color_offset, int point, int points_in, int points_allowed){
        ofColor current_color = colors[point];
        
        if(color_offset > 0){
            ofColor prev_color = colors[(point+colors.size()-1)%colors.size()];
            
            if(points_in < color_offset) return prev_color;
        
        }
        else{
            ofColor next_color = colors[point%(colors.size()-1)];
            
            if(points_in > points_allowed+color_offset) return next_color;
        
        }
        
        return current_color;
        
    }
    
    void Projection::draw_to_screen(parameters params){
        if(colors.size()){

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
    
    float Projection::get_perimeter(){
        
        float total_perimeter;
        
        for(int i = 0; i < beziers.size(); i++) total_perimeter += (beziers[i].get_starting_point().distance(beziers[i].get_final_point()));
        
        return total_perimeter;
    
    
    }
    
    

}
