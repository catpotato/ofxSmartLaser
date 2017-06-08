//
//  laserDispatch.cpp
//  laserProjector
//
//  Created by Clark Addis on 5/31/17.
//
//
//  TODO
//
//  [ ] have a way to psecify which points are to be the starting points and/or what path they should take
//



#include "laserDispatch.h"
namespace Laser{
    
    void Dispatch::setup(){
        window_dimensions.x = ofGetWidth();
        window_dimensions.y = ofGetHeight();
        
        etherdream.setup();
        
        gui_parameters.add(params.pps.set("PPS", 25000, 500, 40000));
        gui_parameters.add(params.max_points.set("max points", 500, 5, 1000));
        gui_parameters.add(params.blank_points.set("blank points", 0, 0, 500));
        gui_parameters.add(params.constant_point_per_line.set("constant point per line", false));
        gui_parameters.add(params.points_per_line.set("points per line", 4, 1, 20));
        
        gui.setup(gui_parameters);
        
        ofBackground(0);
        
        etherdream.setPPS(params.pps);
        point_pool.update_params(params);
    }
    

    
    void Dispatch::set_polys(vector <Laser::Poly> polys){
        
        // points are not cleared here to leave something to give to the projector
        original_polys = polys;
        
        // add spaces in between shape drawings
        projection.connect_the_dots(original_polys);
        
        // update point pool
        point_pool.update(projection);
        
        // resample
        resampled_projection = resample(projection, params, point_pool);
        
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
        etherdream.setPPS(params.pps);
        etherdream.setPoints(normalized_projection.get_points());
    }
}
