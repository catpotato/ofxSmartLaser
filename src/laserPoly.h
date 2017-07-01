//
//  laserPoly.h
//  ofxSmartLaser
//
//  Created by Clark Addis on 6/1/17.
//
//

#ifndef laserPoly_h
#define laserPoly_h

#include <stdio.h>
#include "ofMain.h"
#include "laserBezier.h"

namespace Laser{
    class Poly : public ofPolyline{
        public:
            ofColor color;
        
            void add_vertex_bez(ofPoint pt1, ofPoint pt2, Laser::Bezier bz);
            void add_vertex(ofVec2f v);

            ofVec2f get_starting_point();
            ofVec2f get_final_point();
            ofVec2f final_point;
            ofVec2f starting_point;
        
            bool start_point_set = false;
            bool final_point_set = false;
        
            void set_final_point(ofVec2f pt);
            void set_start_point(ofVec2f pt);
        
            void start_cut_bez(float t, Laser::Bezier bez);
            void end_cut_bez(float t, Laser::Bezier bez);
        
            void bez_to(ofVec2f cp1, ofVec2f cp2, ofVec2f p2);
            ofVec2f get_last_point();
        
            void close_bez();
        
            void translate(ofVec2f v);
            void scale(float scalar);
        
        
            vector <Laser::Bezier> beziers;
            int size();
        
            ofVec2f & operator[](const int & i);
        
    private:
        //vector <Laser::Point> points;
    };
}



#endif /* laserPoly_h */
