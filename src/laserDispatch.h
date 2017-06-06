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
#include "laserHelpers.h"
#include "laserPointPool.h"
#include "laserStructs.h"

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
        
        //void set_poly(/*ofPolyline poly, ofColor color, int allowed_points*/);
        void set_polys(vector <Laser::Poly> polys);
        void set_pps(int _pps);
        void set_max_points(int _pts);
        
        void draw_polys();
        void draw_points();
        void project();
        
        void setup(float window_width, float window_height);
        
        parameters params;
        void update_params(parameters _params);
        
        int pps;
        int number_of_points;
        bool resample;
        
        Laser::PointPool point_pool;
    
    };
}

#endif /* laserDispatch_h */
