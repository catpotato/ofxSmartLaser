//
//  laserPoly.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#include "laserPoly.h"
namespace Laser{
    
    void Poly::add_vertex_bez(ofPoint pt1, ofPoint pt2, Laser::Bezier bz){
        
        // make sure no strange values happen
        if(bz.exists && bz.not_setup){
            bz.setup(pt1, pt2);
        }
        
        beziers.push_back(bz);
        
    };
    
    void Poly::bez_to(ofVec2f cp1, ofVec2f cp2, ofVec2f p2){
        
        beziers.push_back(Laser::Bezier(get_last_point(), cp1, cp2, p2));
        
    
    }
    
    ofVec2f Poly::get_starting_point(){

        if(beziers[0].exists) if(start_point_set) return starting_point;
        
        return beziers[0].p1;
        
    }
    ofVec2f Poly::get_final_point(){

        if(beziers[size()-2].exists) if(final_point_set) return final_point;
        
        return beziers[size()-1].p2;
        
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
        beziers[size()-1].start_pct = t;
    
    
    }
    
    void Poly::end_cut_bez(float t, Laser::Bezier bez){
        
        // add end t
        beziers[size()-1].end_pct = t;
        
        // end shape
        //this->add_vertex(bez.p2);
        this->set_final_point(bez.get_point(t, bez.p1, bez.p2));
    
    
    
    }
    
    ofVec2f Poly::get_last_point(){
        return beziers[size()-1].p2;
        //return points[size()-1].bezier.p2;
    
    }
    
    void Poly::add_vertex(ofVec2f v){
        
        Laser::Bezier bez(false);
        
        // better way to do this??
        bez.p2 = v;
        
        if(size() != 0){
            
            ofVec2f start_pt = get_last_point();
            ofVec2f dir = v - start_pt;
            
            ofVec2f cp1 = start_pt + dir/3;
            ofVec2f cp2 = start_pt + 2*dir/3;
            
            // a line is  just a straight bezier!!!
            bez = Laser::Bezier(start_pt, cp1, cp2, v);
            
            
        }
        
        beziers.push_back(bez);
        //points.push_back(Laser::Point(v, color, bez));
        
        
    }

    
    void Poly::close_bez(){

        // take last bezier in bezier list, and make it the first one
        for(int i = 0; i < size()-1; i++) beziers[i] = beziers[i+1];
        
        beziers.erase(beziers.end()-1);
        
    }
    
    int Poly::size(){return beziers.size();}
    
    
    void Poly::translate(ofVec2f v){
        
        /*Bezier next_bez = points[i].bezier;
        Bezier prev_bez(false);
        
        if(i == 0) prev_bez = points[points.size()-1].bezier;
        else prev_bez = points[i-1].bezier;
        
        ofVec2f next_cp1 = next_bez.cp1_diff;
        ofVec2f next_cp2 = next_bez.cp2_diff;
        ofVec2f prev_cp1 = prev_bez.cp1_diff;
        ofVec2f prev_cp2 = prev_bez.cp2_diff;
    
        ofVec2f next_bez_axis = next_bez.p2 - next_bez.p1;
        ofVec2f prev_bez_axis = (-1)*(prev_bez.p2 - prev_bez.p1);
        
        ofVec2f next_translation_axis = next_bez_axis - v;
        ofVec2f prev_translation_axis = (-1)*(prev_bez_axis - v);

        float next_translation_axis_scalar = next_translation_axis.distance(ofVec2f::zero())/next_bez_axis.distance(ofVec2f::zero());
        float prev_translation_axis_scalar = prev_translation_axis.distance(ofVec2f::zero())/prev_bez_axis.distance(ofVec2f::zero());
        
        ofVec2f next_orth_bez_axis = ofVec2f(-next_bez_axis.y, next_bez_axis.x);
        ofVec2f prev_orth_bez_axis = ofVec2f(next_bez_axis.y, -next_bez_axis.x);
        
        ofVec2f next_orth_translation_axis = ofVec2f(-next_translation_axis.y, next_translation_axis.x);
        ofVec2f prev_orth_translation_axis = ofVec2f(next_translation_axis.y, -next_translation_axis.x);
        
        float next_bez_axis_cp1_comp = next_bez_axis.dot(next_cp1);
        float next_bez_axis_cp2_comp = next_bez_axis.dot(next_cp2);
        
        float next_orth_bez_axis_cp1_comp = next_orth_bez_axis.dot(next_cp1);
        float next_orth_bez_axis_cp2_comp = next_orth_bez_axis.dot(next_cp2);
        
        float prev_bez_axis_cp1_comp = prev_bez_axis.dot(prev_cp1);
        float prev_bez_axis_cp2_comp = prev_bez_axis.dot(prev_cp2);
        
        float prev_orth_bez_axis_cp1_comp = prev_orth_bez_axis.dot(prev_cp1);
        float prev_orth_bez_axis_cp2_comp = prev_orth_bez_axis.dot(prev_cp2);
        
        ofVec2f next_p1 = next_bez.p1 + v;
        ofVec2f next_p2 = next_bez.p2;
        ofVec2f next_cp1 = ofVec2f();
        ofVec2f next_cp2 =
*/        
        for(int i = 0; i < beziers.size();i++) beziers[i].translate(v);
        
        
        
    
    
    }
}
