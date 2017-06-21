//
//  laserPoly.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserPoly.h"
namespace Laser{
    Poly::Poly(ofPolyline p, ofColor c) : color(c){
        
        for(int i = 0; i < p.size(); i++) add_vertex(p[i]);
        setup_lines();
    }
    
    Poly::Poly() : ofPolyline(){ setup_lines(); }
    
    void Poly::setup_lines(){
        // make sure they aren't already full
        if(!lines.size()){
            for(int i = 0; i < this->size(); i++){
            
                ofVec2f starting_point = (*this)[i];
                ofVec2f final_point = (*this)[(i+1)%(this->size())];
            
                ofVec2f direction = final_point - starting_point;
                lines.push_back(direction);
            }
        }
    }
    
    
    void Poly::add_vertex_bez(ofPoint pt1, ofPoint pt2, Laser::Bezier bz){
        
        //cout << "add_vertex_bez called" << endl;
        this->addVertex(pt1);
        
        // make sure no strange values happen
        if(bz.exists && bz.not_setup){
            bz.setup(pt1, pt2);
        }
        
        beziers.push_back(bz);
        
    };
    
    ofVec2f Poly::get_starting_point(){
        
        //cout << "p1: " << (*this)[0]
        if(beziers[0].exists) if(start_point_set) return starting_point;
            
        return (*this)[0];
        
    }
    ofVec2f Poly::get_final_point(){

        if(beziers[this->size()-2].exists) if(final_point_set) return final_point;
        
        return (*this)[this->size()-1];
        
    }
    void Poly::set_start_point(ofVec2f pt){
    
        start_point_set = true;
        starting_point = pt;
    }
    
    void Poly::set_final_point(ofVec2f pt){
        
        final_point_set = true;
        final_point = pt;
    }
    
    void Poly::add_vertex(ofPoint pt) { add_vertex_bez(pt, pt, Laser::Bezier(false));}
}
