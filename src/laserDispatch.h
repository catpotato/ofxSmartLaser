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
#include "ofxGui.h"

#ifndef laserDispatch_h
#define laserDispatch_h

#include <stdio.h>

namespace Laser {
    
    class Dispatch{

    public:

        ofxEtherdream etherdream;
        
        ofPoint window_dimensions;
        
        vector <ofxIlda::Point> points;
        vector <ofVec2f> display_points;
        
        vector <Laser::Poly> original_polys;
        Laser::Poly connected_poly;
        vector <Laser::Poly> resampled_polys;
        vector <Laser::Poly> normalized_polys;
        
        void setup(float window_width, float window_height);
        void set_polys(vector <Laser::Poly> polys);

        void update();
        void draw();
        void project();
    
        Laser::PointPool point_pool;
        parameters params;
        ofParameterGroup gui_parameters;
        ofxPanel gui;
        
        
    
    };
}

#endif /* laserDispatch_h */
