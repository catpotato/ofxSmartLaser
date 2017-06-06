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
//  [ ] make smarter resampling function that:
//      [ ] leaves room for blanking
//      [ ] takes extra points if it can use them
//
//  [ ] ofPolyline -> Laser::Poly conversion


#include "laserDispatch.h"
namespace Laser{
    
    void Dispatch::setup(float window_width, float window_height){
        window_dimensions.x = window_width;
        window_dimensions.y = window_height;
        etherdream.setup();
        
        ofBackground(0);
        
        pps = 26000;
        //number_of_points = 500;
        resample = true;
        
        etherdream.setPPS(pps);
        
        params.max_points = 500;
        params.resample_type = adjusted;
        params.blank_points = 200;
        
        point_pool.update_params(params);
    }
    

    
    void Dispatch::set_polys(vector <Laser::Poly> polys){
        
        //cout << polys[0].size();
        
        // make the polys calcualte their lines
        for(int i = 0; i < polys.size(); i++){
            polys[i].setup_lines();
        }
        
        // update the point pool
        point_pool.update_polys(polys);
        
        // points are not cleared here to leave something to give to the projector
        original_polys = polys;
        
        //find total perimeter of polygons
        float total_perimeter;
        
        for(int i = 0; i < polys.size(); i++){
            total_perimeter += polys[i].getPerimeter();
        }
        
    
        // resample polys
        Laser::resample(original_polys, resampled_polys, params, point_pool);
        //Laser::resample(/*original_polys, resampled_polys, number_of_points, total_perimeter, !resample*/);
        
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
        
        int temp_size = temp_points.size();
        for(int i = 0; i < (params.max_points - temp_size); i++){
            ofxIlda::Point point;
            point.set(original_polys[0][0], ofColor::white);
            temp_points.push_back(point);
        }
        
        points.clear();
        points = temp_points;
        //cout << points.size() << endl;
        
    }
    
    
    void Dispatch::draw_polys(){
        
        //cout << resampled_polys.size() << endl;
        
        for(int i = 0; i < resampled_polys.size(); i++){
            ofSetColor(resampled_polys[i].color);
            //cout << resampled_polys[i].size() << endl;
            resampled_polys[i].draw();
        }
    }
    
    void Dispatch::draw_points(){ for(int i = 0; i < display_points.size(); i++)ofDrawCircle(display_points[i], 1.3);
    }
    
    void Dispatch::set_pps(int _pps){
        pps = _pps;
    }
    
    void Dispatch::set_max_points( int _pts){
        number_of_points = _pts;
        set_polys(original_polys);
    }
    
    void Dispatch::update_params(parameters _params){
        params = _params;
        point_pool.update_params(params);
        set_polys(original_polys);
    }
    
    void Dispatch::project(){
        etherdream.setPPS(pps);
        etherdream.setPoints(points);
    }
}
