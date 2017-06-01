//
//  laserDispatch.h
//  laserProjector
//
//  Created by Clark Addis on 5/31/17.
//
//

#include "ofxIldaPoint.h"
#include "ofxEtherdream.h"
#include "ofMain.h"
#include "laserResample.h"
#include "laserNormalize.h"
#include "laserPoly.h"

#ifndef laserDispatch_h
#define laserDispatch_h

#include <stdio.h>

namespace Laser {
    class Dispatch{

    public:
        //ofxEtherdream & etherdream;
        ofxEtherdream etherdream;
        
        ofPoint window_dimensions;
        
        vector <ofxIlda::Point> points;
        vector <ofVec2f> display_points;
        
        vector <Laser::Poly> original_polys;
        vector <Laser::Poly> resampled_polys;
        vector <Laser::Poly> normalized_polys;
        
        void set_poly(ofPolyline poly, ofColor color, int allowed_points);
        void set_polys(vector <Laser::Poly> polys);
        
        void draw_polys();
        void draw_points();
        void project();
        
        void setup(float window_width, float window_height);
        
        int pps;
        int number_of_points;
        bool resample;
    
        
    };
}

#endif /* laserDispatch_h */
