//
//  laserBezier.cpp
//  laserCurves
//
//  Created by Clark Addis on 6/11/17.
//
//

#include "laserBezier.h"
namespace Laser{
    

    Bezier::Bezier(ofPoint _cp1, ofPoint _cp2): cp1(_cp1), cp2(_cp2), exists(true), not_setup(true){};
    Bezier::Bezier(bool _exists): exists(_exists), not_setup(true){};
    Bezier::Bezier(ofPoint _p1, ofPoint _cp1, ofPoint _cp2, ofPoint _p2): p1(_p1), cp1(_cp1), cp2(_cp2), p2(_p2), exists(true){
        
        // these are here so we can define the point relativley to p1 and p2 and as such are able to move around curves easily
        cp1_diff = cp1 - p1;
        cp2_diff = cp2 - p2;
        
        not_setup = false;
    
    };
    
    ofVec2f Bezier::get_point(float t, ofPoint _p1, ofPoint _p2){
    
        p1 = _p1;
        p2 = _p2;
        
        update_control_points();
        
        ofSetColor(255, 255, 0);
        ofDrawCircle(cp1, 5);
        
        float t_range = end_pct - start_pct;
        float pct = t* t_range + start_pct;
        
        // the meat of the bezier
        ofVec2f result =    p1*pow((1-pct), 3) +
                            cp1*3*pow((1-pct), 2)*pct +
                            cp2*3*(1-pct)*pow(pct,2) +
                            p2*pow(pct,3);
        
        return result;
        
    }
    
    ofVec2f Bezier::get_point(float t){ return get_point(t, p1, p2); }
    
    void Bezier::update_control_points(){
        cp1 = p1 + cp1_diff;
        cp2 = p2 + cp2_diff;
    
    }
    
    void Bezier::set_midpoints(parameters params){
        
        // if we are rendering midpoint style (this is here to prevent unesseacry calculations)
        if(params.bezier_sample_type == midpoint){
            float step_size = 1/((float)params.midpoints);
            
            for(int i = 0; i < params.midpoints; i++){
                
                // starts at zero, goes up by the step size count each time
                midpoint_starting_points.push_back(get_point(step_size*i, p1, p2));
                
            }
            
        }
        
    }
    
    void Bezier::setup(ofVec2f _p1, ofVec2f _p2){
        
        p1 = _p1;
        p2 = _p2;
        
        
        // these are here so we can define the point relativley to p1 and p2 and as such are able to move around curves easily
        cp1_diff = cp1 - p1;
        cp2_diff = cp2 - p2;
        
        not_setup = false;

    }
    
    void Bezier::draw(){

        ofSetColor(ofColor::green);
        ofDrawCircle(p1, 1.2);
        ofDrawCircle(p2, 1.2);
        
        ofSetColor(ofColor::red);
        ofDrawCircle(cp1, 1.2);
        ofDrawCircle(cp2, 1.2);
    
    }
    
    vector <float> Bezier::get_ts_from_x(float x){
        
        // just so that its easier to interface with math stuff
        double p_0 = p1.x;
        double p_1 = p1.x + cp1_diff.x;
        double p_2 = p2.x + cp2_diff.x;
        double p_3 = p2.x;
        
        
        // find a, b, c, d
        double a = -p_0 + 3*p_1 - 3*p_2 + p_3;
        double b = 3*p_0  - 6*p_1 + 3*p_2;
        double c = -3*p_0 + 3*p_1;
        double d = p_0 - x;
        
        double roots_arr[3];
        int number_of_roots = SolveP3(roots_arr, b/a, c/a, d/a);
    
        vector <float> roots;
        
        for(int i = 0; i < number_of_roots; i++) roots.push_back(roots_arr[i]);
        
        return roots;
        
    }
    
    vector <float> Bezier::get_ts_from_y(float y){
        
        // just so that its easier to interface with math stuff
        double p_0 = p1.y;
        double p_1 = p1.y + cp1_diff.y;
        double p_2 = p2.y + cp2_diff.y;
        double p_3 = p2.y;
        
        // find a, b, c, d
        double a = -p_0 + 3*p_1 - 3*p_2 + p_3;
        double b = 3*p_0  - 6*p_1 + 3*p_2;
        double c = -3*p_0 + 3*p_1;
        double d = p_0 - y;
        
        double roots_arr[3];
        int number_of_roots = SolveP3(roots_arr, b/a, c/a, d/a);
        
        vector <float> roots;
        
        for(int i = 0; i < number_of_roots; i++) roots.push_back(roots_arr[i]);
        
        return roots;
        
    }
    
    bool Bezier::valid(float t){
    
        // make sure t is btwn 0 and 1;
        if(t <= 0) return false;
        if(t >= 1) return false;
        
        // get the value of the bez
        ofVec2f pt = this->get_point(t);
        
        // FUCKING DODGIEST HACK U EVER SEEN M8, CASTING THE FLOATS TO AN INT TO PREVENT INSTABILITY IN THE VALIDATOR
        if((int)pt.x < 0) return false;
        if((int)pt.x > ofGetWidth()) return false;
        if((int)pt.y < 0) return false;
        if((int)pt.y > ofGetHeight()) return false;
        
        return true;
        
    }
    
    vector <float> Bezier::get_valid_intersections(){
        
        // go through each case and find the answer
        // x = 0                y = ?
        // x = ofGetWidth()     y = ?
        // x = ?                y = 0
        // x = ?                y = ofGetHeight

        
        // get t from x
        vector <vector <float>> intersections;
        intersections.push_back(get_ts_from_y(0));
        intersections.push_back(get_ts_from_y(ofGetHeight()));
        intersections.push_back(get_ts_from_x(0));
        intersections.push_back(get_ts_from_x(ofGetWidth()));
                                
        vector <float> final_intersections;
        
        for(int i = 0; i < intersections.size(); i++) for(int j = 0; j < intersections[i].size(); j++) if(valid(intersections[i][j])) final_intersections.push_back(intersections[i][j]);
    
        
        return final_intersections;
    
    }
                                
                            
    
}
