//
//  laserDispatch.cpp
//  laserProjector
//
//  Created by Clark Addis on 5/31/17.
//
//  dispatch controls all parts of the laser like the etherdream and drawing to the window and handles the complexity of making points that fit to the ofIlda point with some little resampling hacks
//

//  TODO
//
//  [ ] make points change color in preview too
//
//  [ ] make spacing between things work
//
//  [ ] have a way to insert custom handmade paths into the code (NOT dynamically genarated stuff)


#include "laserDispatch.h"
namespace Laser{
    
    void Dispatch::setup(float window_width, float window_height){
        window_dimensions.x = window_width;
        window_dimensions.y = window_height;
        
        etherdream.setup();
        
        gui_parameters.add(params.pps.set("PPS", 25000, 500, 40000));
        gui_parameters.add(params.max_points.set("max points", 500, 0, 1000));
        gui_parameters.add(params.blank_points.set("blank points", 0, 0, 500));
        gui_parameters.add(params.constant_point_per_line.set("constant point per line", false));
        gui_parameters.add(params.points_per_line.set("points per line", 4, 0, 20));
        
        gui.setup(gui_parameters);
        
        
        ofBackground(0);
        
        etherdream.setPPS(params.pps);
        point_pool.update_params(params);
    }
    

    
    void Dispatch::set_polys(vector <Laser::Poly> polys){
        
        // make the polys calcualte their lines
        for(int i = 0; i < polys.size(); i++){
            polys[i].setup_lines();
        }
        
        // update the point pool
        point_pool.update_polys(polys);
        
        // points are not cleared here to leave something to give to the projector
        original_polys = polys;
        
        // add spaces in between shape drawings
        Laser::connect_the_dots(original_polys, connected_poly);
        
        // resample polys
        Laser::resample(original_polys, resampled_polys, params, point_pool);
        
        // normalize this junk i.e. make them be points from x : 0 -> 1 instead of x : 0 -> ofGetWidth()
        Laser::normalize(resampled_polys, normalized_polys, window_dimensions);
        
        // turn polys into points, use a temporary point so that points is not empty for as long as possible
        vector <ofxIlda::Point> temp_points;
        display_points.clear();
        
        
        for(int i = 0; i < normalized_polys.size(); i++){
            
            for(int j = 0; j < normalized_polys[i].size(); j++){
                
                ofxIlda::Point point;
                point.set(normalized_polys[i][j], normalized_polys[i].color);
                temp_points.push_back(point);
                
                //for the eyes!!
                display_points.push_back(resampled_polys[i][j]);
                
            }
        }
        
        
        int temp_size = temp_points.size();
        /*for(int i = 0; i < (params.max_points - temp_size); i++){
            ofxIlda::Point point;
            point.set(normalized_polys[0][0], ofColor::black);
            temp_points.push_back(point);
        }*/
        
        points.clear();
        points = temp_points;
        //cout << points.size() << endl;
        
    }
    
    
    void Dispatch::draw(){
        
        // draw points
        /*for(int i = 0; i < display_points.size(); i++){
            ofDrawCircle(display_points[i], 1.3);
        }*/
        
        // draw polys
        /*for(int i = 0; i < resampled_polys.size(); i++){
            ofSetColor(resampled_polys[i].color);
            //cout << resampled_polys[i].size() << endl;
            resampled_polys[i].draw();
        }*/
        
        connected_poly.draw();
        
        // draw gui
        gui.draw();
        
    }
    
    void Dispatch::update(){
        
        point_pool.update_params(params);
        set_polys(original_polys);
    }
    
    void Dispatch::project(){
        etherdream.setPPS(params.pps);
        etherdream.setPoints(points);
    }
}
