//
//  generator.cpp
//  TrackGenerator
//
//  Created by James Lennon on 1/6/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "generator.h"
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

float calculate_slope(float x1, float x2, float y1, float y2){
    return (y2-y1)/(x2-x1);
}

float calc_dist(pair<int,int> a, pair<int, int> b){
    float dx = a.first-b.first, dy = a.second-b.second;
    return sqrt(dx*dx+dy*dy);
}

float lerp(float a, float b, float f){
    return a+(b-a)*f;
}

double catmullrom(double t, double a, double b, double c, double d){
    return 0.5 *((2 * b) +
                 (-a + c) * t +
                 (2*a - 5*b + 4*c - d) *t*t +
                 (-a + 3*b- 3*c + d) * t*t*t);
}

pair<int, int> Generator::interpolate(double t, int w1){
    int w0 = (w1-1+waypoints.size())%waypoints.size();
    int w2 = (w1+1)%waypoints.size();
    int w3 = (w1+2)%waypoints.size();
    return make_pair((int)catmullrom(t, waypoints[w0].first, waypoints[w1].first, waypoints[w2].first, waypoints[w3].first), (int)catmullrom(t, waypoints[w0].second, waypoints[w1].second, waypoints[w2].second, waypoints[w3].second));
}

float Generator::avg_slope(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3){
    //    pair<int, int> p1 = waypoints[w1], p2 = waypoints[w2], p3 = waypoints[w3];
    float dx1 = p2.first - p1.first, dx2 = p3.first - p2.first;
    float dy1 = p2.second - p1.second, dy2 = p3.second - p2.second;
    return calculate_slope(0, (dx1+dx2)/2, 0, (dy1+dy2)/2);
    //    float m1 = calculate_slope(p1.first, p2.first, p1.first, p2.first), m2 = calculate_slope(p1.first, p2.first, p1.second, p2.second);
    //    return (m1 + m2)/2;
}

Generator::Generator(int w, int h, int d){
    width = w;
    height = h;
    difficulty = d;
    memset(track, 0, sizeof(track));
    srand((int)time(0));
}

int Generator::min_dist(pair<int, int> pt){
    int min = -1;
    for(int i=0; i<waypoints.size(); i++){
        int d = abs(waypoints[i].first - pt.first) + abs(waypoints[i].second - pt.second);
        if(min==-1 || d<min){
            min = d;
        }
    }
    return min;
}

void Generator::print(){
    for(int y=height-1; y>=0; y--){
        for(int x=0; x<width; x++){
            char c = track[x][y] ? '#' : '.';
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Generator::add_block(int x, int y){
    if(x>=0 && y>=0 && x<width && y<width)
        track[x][y] = true;
    if(track_list.empty() || track_list.back().first != x || track_list.back().second != y)
        track_list.push_back(make_pair(x, y));
}

float Generator::draw(int x1, float y1, int x2, float m){
    float y2 = y1 + m*(x2-x1);
    int d = y2 > y1 ? 1 : -1;
    if((int)y2 != (int)y1){
        y1 += d;
    }
    if(y1<=y2)
        for(int i=y1; i<=(int)y2; i++){
            add_block(x2, i);
        }
    else
        for(int i=y1; i>=(int)y2; i--){
            add_block(x2, i);
        }
    return y2;
}

void Generator::generate(){
    track_list.clear();
    waypoints.clear();
    generate_waypoints();
    for(int i=0; i<waypoints.size(); i++){
        draw_path(i, (i+1)%waypoints.size());
    }
//    print();
    filter();
//    print();
}

void Generator::filter(){
    vector<pair<int,int> > new_list;
    //int j = (i-1+track_list.size())%track_list.size();
    int j=0;
    for(int i=0; i<track_list.size(); i++){
        float d = calc_dist(track_list[i], track_list[j]);
        if(d>1.5){
            new_list.push_back(track_list[i]);
            j = i;
        }else{
//            track[track_list[i].first][track_list[i].second] = false;
        }
    }
}

void Generator::generate_waypoints(){
    int num_waypoints = difficulty;
    //    int tolerance = width / (1.*num_waypoints) + height / (1.*num_waypoints);
    waypoints.push_back(make_pair(width/8, height/2));
    for(int i=1; i<num_waypoints; i++){
        pair<int, int> maxp;
        int max = -1;
        for(int i=0; i<5; i++){
            pair<int, int> next;
            next.first = rand() % width;
            next.second = rand() % height;
            int d = min_dist(next);
            if(d>max){
                max = d;
                maxp = next;
            }
        }
        waypoints.push_back(maxp);
    }
}

void Generator::draw_path(int w1, int w2){
    for(double i=0; i<=1.0; i += .01){
        pair<int, int> pt = interpolate(i, w1);
        add_block(pt.first, pt.second);
    }
}
