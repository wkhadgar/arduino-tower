#include <VarSpeedServo.h>

VarSpeedServo bottom; // bottom servo, 180 horizontal 
VarSpeedServo mid; // mid servo, +180 horizontal
VarSpeedServo top; // top servo, 180 vertical 

int vert_pos = 0; // vertical move
int hor_posA = 0; // horizontal move 1
int hor_posB = 0; // horizontal move 2
int speed = 0; // speed 
char speed_chars = ['c', 'v', 'b']; //slow, medium, fast
int all_speeds = [10, 120, 225];
int mode; // to control the actions
int step = 4; // size of the servo steps
int temp = 3; // wait for step movement

void setup()    {
    Serial.begin(9600);
    top.attach(9); // vertical servo on pin 9
    mid.attach(10); // horizontal servo 2 on pin 10
    bottom.attach(11); // horizontal servo 1 on pin 11 

    bottom.write(180, all_speeds[0]);
    mid.write(180, all_speeds[0]);
    top.write(180, all_speeds[0]);
    delay(2700);
    bottom.write(hor_posA, all_speeds[0]);
    mid.write(hor_posB, all_speeds[0]);
    top.write(vert_pos, all_speeds[0]);
    delay(2700);
}

void loop() {
    if (Serial.available())   {
        mode = Serial.read(); // tera term output
        // def the movement speed
        for (int i = 0; i < 3; i++)
        {
            if (mode == speed_chars[i])    {
                speed = all_speeds[i]
            }
        }
        
        // this controlls the servos to make a laser attached to the top servo able to point at any point surrounding the tower
        // controll of the axis: bottom and mid are attached servos with half circle of movement, top is also, but attached to the mid servo at 90 degrees for vertical movement
        if (mode == 'a')    {
            hor_posA += step;
            if (hor_posA > 179)     {
                hor_posA = 180;
                hor_posB += step;
                mid.write(hor_posB, speed);
            }
            else    {
            bottom.write(hor_posA, speed);
            }
            
            delay(temp);
        }

        else if (mode == 'd')    {
            hor_posA -= step;
            if (hor_posA < 0)     {
                hor_posA = 0;
                hor_posB -= step;
                mid.write(hor_posB, speed);
            }
            else    {
            bottom.write(hor_posA, speed);
            }
            
            delay(temp);
        }

        if (mode == 's')    {
            vert_pos += step;
            if (vert_pos > 179)    {
                vert_pos = 180;
            }
            top.write(vert_pos, speed);
            delay(temp); 

        }

        else if (mode == 'w')    {
            vert_pos -= step;
            if (vert_pos < 0)  {
                vert_pos = 0;
            }
            top.write(vert_pos, speed);
            delay(temp); 
        }

       
    }
}