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
#include <iostream>

float calculate_slope(float x1, float x2, float y1, float y2){
    return (y2-y1)/(x2-x1);
}

float lerp(float a, float b, float f){
    return a+(b-a)*f;
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
    track[x][y] = true;
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
    generate_waypoints();
    print();
    printf("\n");
    for(int i=0; i<waypoints.size(); i++){
        draw_path(i, (i+1)%waypoints.size());
    }
    print();
//    for (pair<int,int> p : track_list){
//        printf("x: %d, y: %d\n", p.first, p.second);
//    }
}

void Generator::generate_waypoints(){
    int num_waypoints = 2 * difficulty;
//    int tolerance = width / (1.*num_waypoints) + height / (1.*num_waypoints);
    waypoints.push_back(make_pair(0, height/2));
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
    for (int i=0; i<waypoints.size(); i++) {
        add_block(waypoints[i].first, waypoints[i].second);
    }
}

void Generator::draw_path(int w1, int w2){
    if(waypoints[w2].first < waypoints[w1].first){
        swap(w1, w2);
    }
    float y = waypoints[w1].second, y2 = waypoints[w2].second;
    int x1 = waypoints[w1].first, x2 = waypoints[w2].first;
    int d = x2 - x1;
    if(d!=0)
        d /= abs(d);
    else{
//        printf("vertical\n");
        d = y2 > y ? 1 : -1;
        for(int i=y; i!=y2; i+=d){
            add_block(x1, i);
        }
    }
    float m0 = (y2 - y)/(x2-x1);
    for(int x = x1; x!=x2; x+=d){
//        y = draw(x, y, x+d, (s(x)-y));
        y = draw(x, y, x+d, m0);
        //print();
    }
//    for(int x = x3; x!=x2; x+=d){
//        m = lerp(m0, m2, (float)(x - x3)/(float)(x2-x3));
//        y = draw(x, y, x+d, m);
//        print();
//    }
//    for(int x = x1; x!=x3; x+=d){
//        y = draw(x, y, x+d, m);
//        m = lerp(m1, m0, (float)(x - x1)/(float)(x2-x1));
//        print();
//    }
//    for(int x = x3; x!=x2; x+=d){
//        y = draw(x, y, x+d, m);
//        m = lerp(m0, m2, (float)(x - x1)/(float)(x2-x1));
//        print();
//    }
}
