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
//  [ ] implement colors into preview
//
//  [ ] make smarter resampling function that:
//      [ ] leaves room for blanking
//      [ ] takes extra points if it can use them


#include "laserDispatch.h"
namespace Laser{
    
    void Dispatch::setup(float window_width, float window_height){
        window_dimensions.x = window_width;
        window_dimensions.y = window_height;
        etherdream.setup();
        
        pps = 30000;
        number_of_points = 500;
        resample = true;
        etherdream.setPPS(pps);
    }
    

    
    void Dispatch::set_polys(vector <Laser::Poly> polys){
        
        // points are not cleared here to leave something to give to the projector
        original_polys = polys;
        
        //find total perimeter of polygons
        float total_perimeter;
        
        for(int i = 0; i < polys.size(); i++){
            total_perimeter += polys[i].getPerimeter();
        }
        
        // resample polys
        Laser::resample(original_polys, resampled_polys, number_of_points, total_perimeter, !resample);
        
        // normalize this junk
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
        
        points.clear();
        points = temp_points;

    }
    
    
    
    void Dispatch::draw_polys(){
        for(int i = 0; i < resampled_polys.size(); i++){
            ofSetColor(resampled_polys[i].color);
            resampled_polys[i].draw();
        }
    }
    
    void Dispatch::draw_points(){ for(int i = 0; i < display_points.size(); i++)ofDrawCircle(display_points[i], 1.3);}
    
    void Dispatch::project(){
        etherdream.setPPS(pps);
        etherdream.setPoints(points);
    }
}
