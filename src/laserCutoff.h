//
//  laserCutoff.h
//  speed
//
//  Created by Clark Addis on 6/15/17.
//
//

#ifndef laserCutoff_h
#define laserCutoff_h

#include <stdio.h>
#include "ofMain.h"
#include "laserProjection.h"
#include "laserCrawler.h"
#include "laserBezier.h"

namespace Laser{
    vector <Laser::Poly> slice_off_edges(vector <Laser::Poly> polys);
    
    bool in_bounding_box(ofVec2f pt);
    
    class Vector_Line{
        
        public:
        
            ofVec2f starting_point;
            ofVec2f direction;
        
            Vector_Line(ofVec2f pt, ofVec2f dir);
        
            bool completely_inside();
            bool completely_outside();
        
            vector <ofVec2f> get_valid_intersections();
        
        
    };
    
    class Intersection{
        
        public:
        
            Intersection(Vector_Line l);
            //Intersection(Bezier b);
        
            ofVec2f point;
            vector <ofVec2f> points;
            Vector_Line line;
            //Vector_Line bezier;
            bool valid = true;
        
            void set_x(float x);
            void set_y(float y);
        
        
        
        
    };
    
    vector <Intersection> get_all_intersections(Vector_Line line);
    vector <ofVec2f> order_points(vector <ofVec2f> intersections, ofVec2f pt);
    vector <float> order_values(float v1, float v2);
    

}

#endif /* laserCutoff_h */
