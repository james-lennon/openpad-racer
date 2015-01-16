//
//  generator.h
//  TrackGenerator
//
//  Created by James Lennon on 1/6/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#ifndef __TrackGenerator__generator__
#define __TrackGenerator__generator__

#include <stdio.h>
#include <vector>

using namespace std;

#define MAX_WIDTH 200
#define MAX_HEIGHT 200

class Generator {
    
public:
    Generator(int width, int height, int difficulty);
    void generate();
    void print();
    
    int width, height, difficulty;
    bool track[MAX_WIDTH][MAX_HEIGHT];
    vector<pair<int, int> > track_list;
    
private:
    int min_dist(pair<int, int> pt);
    void generate_waypoints();
    float draw(int x1, float y1, int x2, float m);
    void draw_path(int w1, int w2);
    void add_block(int x, int y);
    float avg_slope(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3);
    
    vector<pair<int, int> > waypoints;
};

#endif /* defined(__TrackGenerator__generator__) */
