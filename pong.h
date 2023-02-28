#ifndef PONG_H
#define PONG_H

#define MAX_POINTS 30
typedef struct{
    char x,y
} POINT, *PPOINT;

typedef struct {
    int numpoints;
    int sizex;
    int sizey;
    POINT px[MAX_POINTS];
} GEOMETRY, *PGEOMETRY;

GEOMETRY ball_geometry = {
        12,
        4,4,
        {
            {0,1},{0,2},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{2,3},{3,1},{3,2}
        }
};
GEOMETRY paddle_geometry = {
        27,
        5,9,
        {
            {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},{1,0},{1,8},{2,0},{2,3},{2,4},{2,5},{2,8},{3,0},{3,8},{4,0},{4,1},{4,2},{4,3},{4,4},{4,5},{4,6},{4,7},{4,8}
        }
};

typedef struct tObj{
    PGEOMETRY geo;
    int dirx,diry;
    int posx,posy;
    void (*draw) (struct tObj *);
    void (*clear) (struct tObj *);
    void (*move) (struct tObj *);
    void (*set_speed) (struct tObj *, int, int);
} OBJECT, *POBJECT;

void draw_object(POBJECT o);
void clear_object(POBJECT o);
void set_object_speed(POBJECT o, int speedx, int speedy);
void move_ballobject(POBJECT o);
void move_paddleobject(POBJECT o);
int exact_overlap(POBJECT o1,POBJECT o2);
int approx_overlap(POBJECT o1,POBJECT o2);
int objects_overlap(POBJECT o1,POBJECT o2);
void check_contact_with_ball_and_paddle(POBJECT ball,POBJECT paddle);
void reset_pong(POBJECT ptrball, POBJECT ptrpaddle);

#endif