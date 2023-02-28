
#include "pong.h"



void draw_object(POBJECT o)
{
    for(int i = 0; i < o->geo->numpoints; i++){
        graphic_pixel_set(o->posx + o->geo->px[i].x, o->posy + o->geo->px[i].y);
    }
}
void clear_object(POBJECT o){
    for(int i = 0; i < o->geo->numpoints; i++){
        graphic_pixel_clear(o->posx + o->geo->px[i].x, o->posy + o->geo->px[i].y);
    }
}
void set_object_speed(POBJECT o, int speedx, int speedy){
    o->dirx = speedx;
    o->diry = speedy;
}
void move_ballobject(POBJECT o){
    clear_object(o);
    if(o->posx < 1)
    {
        o->set_speed(o, -o->dirx, o->diry);
    }
    
    // Om bollen går till högersidan av displayen så ska den gå tillbaka till mitten av skärmen.
    if(o->posx + o->geo->sizex > 128){
        o->posx = 64;
        o->posy = 32;
    }
    
    if(o->posy < 1)
    {
        o->set_speed(o, o->dirx, -o->diry);
    }
    
    if(o->posy + o->geo->sizey > 64)
    {
        o->set_speed(o, o->dirx, -o->diry);
    }
    
    o->posx += o->dirx;
    o->posy += o->diry;
    
    draw_object(o);
}
void move_paddleobject(POBJECT o){
    clear_object(o);
    
    if(o->posy < 1 & o->diry < 0)
    {
        o->set_speed(o,o->dirx,0);
    }
    
    if(o->posy + o->geo->sizey > 64 & o->diry > 0)
    {
        o->set_speed(o,o->dirx,0);
    }
    
    o->posy += o->diry;
    draw_object(o);
}
int exact_overlap(POBJECT o1,POBJECT o2){
  int offset1x = o1->posx;
  int offset1y = o1->posy;
  int offset2x = o2->posx;
  int offset2y = o2->posy;
  
  for (int i = 0; i < o1->geo->numpoints; i++) {
    for (int j = 0; j < o2-> geo->numpoints; j++){
        char pixel_o1_x = offset1x + o1->geo->px[i].x;
        char pixel_o1_y = offset1y + o1->geo->px[i].y;
        
        char pixel_o2_x = offset2x + o2->geo->px[j].x;
        char pixel_o2_y = offset2y + o2->geo->px[j].y;
        
        if ((pixel_o1_x == pixel_o2_x) & (pixel_o1_y == pixel_o2_y)){
            return 1;
        }
    }
  }
  return 0;
}
int approx_overlap(POBJECT o1,POBJECT o2){
    char o1_right = o1->posx + o1->geo->sizex;
    char o1_left = o1->posx;
    char o1_top = o1->posy;
    char o1_bottom = o1->posy + o1->geo->sizey;
    
    char o2_right = o2->posx + o2->geo->sizex;
    char o2_left = o2->posx;
    char o2_top = o2->posy;
    char o2_bottom = o2->posy + o2->geo->sizey;
    
    if(o1_left > o2_right || o2_left > o1_right){
        return 0;
    }
    
    if(o1_top > o2_bottom || o2_top > o1_bottom){
        return 0;
    }
    
    return 1;
}
int objects_overlap(POBJECT o1,POBJECT o2){
    /* Om object o1 överlappar object o2 returnera 1, annars 0*/
    
    // En approximativ overlap görs med mindre komplexitet
    if(approx_overlap(o1,o2)){
        // En exakt overlap, görs för att jämföra varje pixel, hög komplexitet
        if(exact_overlap(o1,o2)){
           return 1; 
        }
    }
    else{
        return 0;
    }
}
void check_contact_with_ball_and_paddle(POBJECT ball,POBJECT paddle){
    if(objects_overlap(ball,paddle) && (ball->dirx > 0) && (ball->dirx > 0))
    {
        ball->set_speed(ball,-ball->dirx, -ball->diry);
    }
}
void reset_pong(POBJECT ptrball, POBJECT ptrpaddle){
    graphic_clear_screen();
    ptrball->posx = 64;
    ptrball->posy = 32;
    ptrpaddle->posx = 120;
    ptrpaddle->posy = 32;
}