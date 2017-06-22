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
    
    void Poly::bez_to(ofVec2f cp1, ofVec2f cp2, ofVec2f p2){
        
        //new_beziers.push_back(Laser::Bezier(get_last_point(), cp1, cp2, p2));
        beziers.push_back(Laser::Bezier(get_last_point(), cp1, cp2, p2));
        this->addVertex(p2);
        
    }
    
    ofVec2f Poly::get_starting_point(){
        
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
    
    void Poly::start_cut_bez(float t, Laser::Bezier bez){
        
        // start new shape
        this->add_vertex_bez(bez.p1, bez.p2, bez);
        this->set_start_point(bez.get_point(t, bez.p1, bez.p2));
        
        // add start t
        this->beziers[this->size()-1].start_pct = t;
    
    
    }
    
    void Poly::end_cut_bez(float t, Laser::Bezier bez){
        
        // add end t
        this->beziers[this->size()-1].end_pct = t;
        
        // end shape
        this->add_vertex(bez.p2);
        this->set_final_point(bez.get_point(t, bez.p1, bez.p2));
    
    
    
    }
    
    ofVec2f Poly::get_last_point(){ return (*this)[this->size()-1];};
    
    void Poly::add_vertex(ofPoint pt) {
        //add_vertex_bez(pt, pt, Laser::Bezier(false));
        add_vert(pt);
    }
    
    void Poly::add_vert(ofVec2f v){
        
        // temp bezier storage while we get the whole shape, starting point for the other beziers
        if(this->size() == 0){
            this->beziers.push_back(Laser::Bezier(false));
        }
        
        else{
            
            ofVec2f start_pt = get_last_point();
            ofVec2f dir = v - start_pt;
            
            ofVec2f cp1 = start_pt + dir/3;
            ofVec2f cp2 = start_pt + 2*dir/3;
            
            // a line is  just a straight bezier!!!
            this->beziers.push_back(Laser::Bezier(start_pt, cp1, cp2, v));
            
            
        }
        
        this->addVertex(v);
    
    }
    
    
    void Poly::close_bez(){
        //cout << "closing bezier!!" << endl;
        // take last bezier in bezier list, and make it the first one
        for(int i = 0; i < this->size()-1; i++){
            beziers[i] = beziers[i+1];
            
        }
        
    }
}
