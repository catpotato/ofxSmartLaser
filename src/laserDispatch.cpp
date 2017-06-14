//
//  laserDispatch.cpp
//  ofxSmartLaser
//
//  Created by Clark Addis on 5/31/17.
//
//
//  TODO
//
//  [ ] have a way to specify which points are to be the starting points and/or what path they should take
//
//  [ ] better way than laser polys to send polygons to laser
//
//  [ ] better way than laser.update to update things
//
//  [ ] make setting up a laser poly better
//
//  [ ] better color pushback (see laserHelpers)
//
//  [ ] make laser not do anything if updating/projectting nothing
//
//  [ ] make "add_vertex_bez" better
//
//  [ ] improve line setup
//
//  [ ] improve parameter handling in laserProjection
//
//  [ ] make paths into curves??




#include "laserDispatch.h"
namespace Laser{
    
    void Dispatch::setup(){
        
        ofSetFrameRate(60);
        
        
        window_dimensions.x = ofGetWidth();
        window_dimensions.y = ofGetHeight();
        
        //etherdream.setup();
        
        gui_parameters.add(params.pps.set("PPS", 25000, 500, 40000));
        gui_parameters.add(params.max_points.set("max points", 500, 5, 1000));
        gui_parameters.add(params.blank_points.set("blank points", 0, 0, 500));
        gui_parameters.add(params.constant_point_per_line.set("constant point per line", false));
        gui_parameters.add(params.points_per_line.set("points per line", 4, 1, 20));
        gui_parameters.add(params.resample_type.set("resampling", 2, 0, 2));
        gui_parameters.add(params.bezier_sample_type.set("bezier resampling", 1, 0, 1));
        gui_parameters.add(params.midpoints.set("midpoints", 1, 1, 20));
        
        gui.setup(gui_parameters);
        
        ofBackground(0);
        
        etherdream.setPPS(params.pps);
        point_pool.update_params(params);
    }
    

    
    void Dispatch::set_polys(vector <Laser::Poly> polys){
        
        // points are not cleared here to leave something to give to the projector
        original_polys = polys;
        
        // add spaces in between shape drawings
        spaced_projection = connect_the_dots(original_polys, params);

        // update point pool
        point_pool.update(spaced_projection);
        
        // resample
        resampled_projection = resample(spaced_projection, params, point_pool);
        
        // normalize
        normalized_projection = normalize(resampled_projection, window_dimensions);
    }
    
    
    void Dispatch::draw(){
        // draw gui
        gui.draw();
        resampled_projection.draw_to_screen(params);
    }
    
    void Dispatch::update(){
        point_pool.update_params(params);
        set_polys(original_polys);
    }
    
    void Dispatch::project(){
        //etherdream.setPPS(params.pps);
        points = normalized_projection.get_points();
        //etherdream.setPoints(points);
    }
}
