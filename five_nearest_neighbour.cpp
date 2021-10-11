/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or   
 * (at your option) any later version.                                 
 *                                                                      
 * This program is distributed in the hope that it will be useful,     
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     
 * GNU General Public License for more details.     

 *  This file is part of Zebra Technologies Path Planning Assignment.
 *  @file find_five_nearest_points_to_target.cpp
 *  @author Mohit Arvind Khakharia
 *  @version 1.0 
 *  @date_modified 2021-10-10
 */

#include <bits/stdc++.h>
#include <iostream>
#include <queue>
#include <random>
#include <fstream>
#include <string>

using namespace std;

class Points2D{
    /**
     * This class is defines a a data type that represents a point in our program.
     *
     * @param:      x,y represent a point in the cartesian coordinate system.
     * @return:     object of the type Points2D.
       Declaration: Points2D(x,y)
     */
    public:
        Points2D(double x,double y):_x(x),_y(y){
        }
        virtual ~Points2D(){
        }
        double getDist(const Points2D &target_point) const{
            /**
                Calculates the distance of the given Point(X,Y) from a target point target_point.
                Note: We do not take the square root of the answer as the actual distance 
                      is not needed for the given problem.
                @param target_point<Points2D> the target point that is input.
                @return a dist<double> that is a representation of the distance between the two points.
            */
            double xDist = (target_point.GetX() - _x);
            double yDist = (target_point.GetY() - _y);
            double dist = ((xDist*xDist) + (yDist*yDist));
            return dist;
        }
        
        double GetX() const {return _x;} // Returns point X in Point(X,Y)
        double GetY() const {return _y;} // Returns point Y in Point(X,Y)
    private:
        double _x; // Represents point X in Point(X,Y)
        double _y; // Represents point Y in Point(X,Y)
};


class NearestPoint2D{
        /**
         * This class is defines a a data type where you can add points and get the k nearest neighbors 
         * of a target point.
         *
         * @param:      x,y represent a point in the cartesian coordinate system.
         * @return:     object of the type NearestPoint2D.
           Declaration: NearestPoint2D(x,y)
     */
    public:
        NearestPoint2D() {}
        virtual ~NearestPoint2D() {}
        
        void addPoints(const Points2D &points){
            _points.push_back(points);
        }
        
        bool getNearestPoints(const Points2D &target_point,vector<Points2D> &nearest_points,int K){
            priority_queue<pair<int,pair<int,int>>>nearest_points_pqueue;
            double close_x,close_y;
            ofstream near_points_file("near_points_file.txt");

            for(Points::iterator itr = _points.begin(); itr != _points.end(); ++itr){
                double distance= itr->getDist(target_point);
                near_points_file << itr->GetX()<<" "<<itr->GetY()<<_blue<<endl;
                if(nearest_points_pqueue.size()<K){
                    nearest_points_pqueue.push({distance,{itr->GetX(),itr->GetY()}});
                }else{
                    int topp = nearest_points_pqueue.top().first;
                    if(topp > distance){
                        nearest_points_pqueue.pop();
                        nearest_points_pqueue.push({distance,{itr->GetX(),itr->GetY()}});
                    }
                }
            }
            while(!nearest_points_pqueue.empty()){
                close_x = nearest_points_pqueue.top().second.first;
                close_y = nearest_points_pqueue.top().second.second;
                nearest_points.push_back({close_x,close_y});
                near_points_file << close_x<<" "<<close_y<<_red<<endl;
                nearest_points_pqueue.pop();
            }
            near_points_file << target_point.GetX()<<" "<<target_point.GetY()<<_yellow;
            near_points_file.close();       
            return true;
        }
    private:
        typedef vector<Points2D> Points;
        Points _points;
        string _blue = " 22";
        string _red = " 55";
        string _yellow = " 100";

};

int main(int argc, const char * argv[]) {
    /**
     * The main program generates a set of 1000 random points and adds them to the object of NearestPoint2D Class.
     * The program calls getNearestPoints() function to get the K nearest points from the set of random points.
     * @param Takes in the value of 'K' and a target point 'P'.
     * @return : Prints the 'K' nearest points from the randomly generated thousand points.
     */

    const int RANDOM_POINTS_MAX_VALUE = 100; // The maximum value of X and Y for a random point.
    const int RANDOM_POINTS_COUNT = 1000; // The number of random points to generate.
    std::mt19937 eng; // Declare a random number engine. C++11
    //Using modulo may introduce bias into the random sequence and thus using random distribution.
    eng.seed(std::random_device{}());
    // Create a unifom random distribution generator for the given range.
    std::uniform_int_distribution<> dist(-RANDOM_POINTS_MAX_VALUE, RANDOM_POINTS_MAX_VALUE);
    
    NearestPoint2D points_container;
    for(int i = 0; i < RANDOM_POINTS_COUNT; i++) {
        int random_x = dist(eng); //Generate a random number for X value of (X,Y)
        int random_y = dist(eng); //Generate a random number for X value of (X,Y)
        points_container.addPoints(Points2D(random_x,random_y)); //Create Points2D(X,Y) and add it to the Points_container
    }
    vector<Points2D> nearest_points;
    points_container.getNearestPoints(Points2D(50,-50),nearest_points,5);
    for(vector<Points2D>::iterator itr = nearest_points.begin(); itr != nearest_points.end(); ++itr){
        cout<<"Nearest Point " << itr->GetX()<<" "<<itr->GetY()<<endl;
    }
    cout<<endl;
    return 0;
}