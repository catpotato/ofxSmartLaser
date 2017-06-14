//
//  laserDispatch.h
//  ofxSmartLaser
//
//  Created by Clark Addis on 5/31/17.
//

#include "ofxIldaPoint.h"
#include "ofxEtherdream.h"
#include "ofMain.h"
#include "laserHelpers.h"
#include "laserPointPool.h"
#include "laserStructs.h"
#include "ofxGui.h"
#include "laserProjection.h"

#ifndef laserDispatch_h
#define laserDispatch_h

#include <stdio.h>

namespace Laser {
    
    class Dispatch{

    public:
        
        // etherdream connection
        ofxEtherdream etherdream;
        
        // window stuff for drawing to the screen
        ofPoint window_dimensions;
        
        // polys that were sent from the user
        vector <Laser::Poly> original_polys;
        
        // intermediate variables for drawing to the laser
        Laser::Projection spaced_projection;
        Laser::Projection resampled_projection;
        Laser::Projection normalized_projection;
        
        // point pool where you can ask for points for, is dumb now, but makes it easy to add smarts in the futre
        Laser::PointPool point_pool;
        // simple parameters
        parameters params;
        // gui stuff
        ofParameterGroup gui_parameters;
        ofxPanel gui;
        
        vector <ofxIlda::Point> points;
        
        // pass a vector of laser polys to the dispatch and it will set them. If you just have one that's fine too. just pass it as a vector with a single element
        void set_polys(vector <Laser::Poly> polys);
        
        // must be called at begining, helps the etherdream setup and puts default parameters for gui in
        void setup();
        // update is really only called to update parameters. If you are not planning to update the parameters durring runtime, you do not have to use this
        void update();
        // draws to screen
        void draw();
        // draws to projector
        void project();
        void update_polys();
        void paramter_changed(ofAbstractParameter &e);
        
    
        
    
    };
}

#endif /* laserDispatch_h */
