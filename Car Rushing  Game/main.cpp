#include <windows.h> // for MS Windows

#include <GL/glut.h> // GLUT, include glu.h and gl.h

#include <iostream>

#include <ctime>

#include <cmath>

using namespace std;

float moveAmount = 0.001f; // Initial amount of movement in each step

bool moveLeft = false; //   indicate whether the car is moving left

bool moveRight = false; //   indicate whether the car is moving right

//mid point of the car=(-0.00014, -0.28558).

float main_car_x = -0.00014f; // Initial x position

float main_car_y = -0.28558f; // Initial y position

float position1_x =0.2f;

float position1 = 1.0f;

float position2 = 1.20f;

float position3 = 1.50f;

float position4 = 1.90f;

float position1_x_1 =-0.425f;

float position1_x_2 =0.425f;

float B1=-0.2f;

float B2=1.2f;

float H1=-0.2f;

int collisionCount = 0;

int gameover = 0;

int lives = 3;

bool collisionOccurred = false;

time_t collisionStartTime;

float distance(float x1, float y1, float x2, float y2) {

    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

}

void increaseLife() {

  lives=lives+1; // Increase life

}

bool liveCollisionOccurred = false; // Flag to track live collision occurrence

bool checkCollision() {

    float collisionThreshold = 0.1f;

    // Flag to check if any collision occurs

    bool collisionDetected = false;

    // Check for collision with other cars and obstacles

    if (distance(position1_x, position1, main_car_x, main_car_y) < collisionThreshold ||

        distance(position1_x_1, position2, main_car_x, main_car_y) < collisionThreshold ||

        distance(position1_x_2, position3, main_car_x, main_car_y) < collisionThreshold ||

        distance(B1, B2, main_car_x, main_car_y) < collisionThreshold) {

        if (!collisionOccurred) {

            collisionOccurred = true;

            collisionStartTime = time(NULL);

            collisionDetected = true; // Collision detected with other objects

            collisionCount++; // Increment collision count

        }

    }

    // Check for collision with Live object

    if (distance(H1, position4, main_car_x, main_car_y) < collisionThreshold) {

        if (!liveCollisionOccurred) {

            increaseLife(); // Increase life if collision with Live object only if no collision occurred previously

            liveCollisionOccurred = true; // Set live collision flag

        }

        collisionDetected = true; // Collision detected with Live object

    } else {

        liveCollisionOccurred = false; // Reset live collision flag if no collision with Live object

    }

    // Check if the car becomes invisible

    if (distance(position1_x, position1, main_car_x, main_car_y) < collisionThreshold ||

        distance(position1_x_1, position2, main_car_x, main_car_y) < collisionThreshold ||

        distance(position1_x_2, position3, main_car_x, main_car_y) < collisionThreshold ||

        distance(B1, B2, main_car_x, main_car_y) < collisionThreshold) {

        if (!collisionOccurred) {

            collisionOccurred = false;

            collisionStartTime = time(NULL);

        }

    }

    // Handle collision duration and life deduction

    if (collisionOccurred) {

        time_t currentTime = time(NULL);

        double duration = difftime(currentTime, collisionStartTime);

        if (duration >= 0.50) {

            lives--; // Decrease by 1 life after 0.50 seconds

            collisionOccurred = false; // Reset collision flag

        }

    }

    return collisionDetected; // Return whether any collision occurred

}

///reduce heart

void drawHearts() {

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for hearts

     int maxLives = std::min(lives, 5);

    for (int i = 0; i < maxLives; i++) {

        glPushMatrix();

        glTranslatef(-0.5f + i * 0.1f, 0.8f, 0.0f); // Adjust heart positions

        glColor3f(1.0f, 0.0f, 0.0f); // Red color for filling

        glScalef(0.1,0.1,0);

        //glTranslatef(1, 1, 0.0f);

        glBegin(GL_POLYGON);

        glVertex2f(0,0.5);   //1

        glVertex2f(0.1248, 0.5541);   //2

        glVertex2f(0.2434, 0.5333); //3

        glVertex2f(0.3162, 0.4397);     //4

        glVertex2f(0.3162, 0.3273);    //5

        glVertex2f(0.2704, 0.2296);   //6

        glVertex2f(0.1914, 0.1318);//o

        glVertex2f(0.1144, 0.0444);//o

        glVertex2f(0, -0.0388);

        glEnd();

        glBegin(GL_POLYGON);

        glVertex2f(0,0.5);   //1

        glVertex2f(-0.1248, 0.5541);   //2

        glVertex2f(-0.2434, 0.5333); //3

        glVertex2f(-0.3162, 0.4397);     //4

        glVertex2f(-0.3162, 0.3273);    //5

        glVertex2f(-0.2704, 0.2296);   //6

        glVertex2f(-0.1914, 0.1318);//o

        glVertex2f(-0.1144, 0.0444);//o

        glVertex2f(0, -0.0388);

        glEnd();

        glPopMatrix();

    }

}


///main car movement

void Main_car()

{

    glPushMatrix(); // Save current matrix

    glTranslatef(main_car_x, main_car_y, 0.0f); // Apply translation to the car

    glScalef(0.5,0.5,0);

    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for filling

    glVertex2f(-0.0014, -0.057); //1

    glVertex2f(0.0529, -0.0679);      //2

    glVertex2f(0.0816, -0.125);  //3

    glVertex2f(0.0816, -0.45);   //4

    glVertex2f(0.0461, -0.5);   //6

    glVertex2f(0, -0.508);     //7

    glVertex2f(-0.0461, -0.5);  //8

    glVertex2f(-0.0816, -0.455);   //9

    glVertex2f(-0.0816, -0.125); //10

    glVertex2f(-0.0529, -0.0679); //11

    glVertex2f(-0.0014, -0.057); //1

    glEnd();

    ///In side of car

    glColor3f(0.0f, 1.0f, 1.0f); // Black color for filling

    glBegin(GL_POLYGON);

    glVertex2f(0.0,-0.1 );   // 1

    glVertex2f( 0.03327, -0.1065);         // 2

    glVertex2f(0.0615, -0.114 );    // 3

    glVertex2f( 0.05057, -0.1359); // 4

    glVertex2f(0.0338, -0.1566 );     // 5

    glVertex2f(0.01597, -0.1514 );// 6

    glVertex2f(0, -0.15 );// 7

    glVertex2f(-0.01597, -0.1514 );//8

    glVertex2f( -0.0338, -0.1566);//9

    glVertex2f( -0.05057, -0.1359);//10

    glVertex2f(-0.0615, -0.114 );//11

    glVertex2f( -0.03327, -0.1065);//12

    glVertex2f(0.0,-0.1 );//1

    glEnd();

///back glass

    glColor3f(0.0f, 1.0f, 1.0f); // Black color for filling

    glBegin(GL_POLYGON);

    glColor3f(0.5f, 0.0f, 0.5f); // Purple color for filling

    glVertex2f (0.00119, -0.4439) ;// 1

    glVertex2f (0.02, -0.44) ;

    glVertex2f (0.0379, -0.4296) ;

    glVertex2f (0.0509, -0.454) ;

    glVertex2f (0.0319, -0.4674) ;

    glVertex2f(-0.00260, -0.47397)  ;

    glVertex2f (-0.0319, -0.4674) ;

    glVertex2f(-0.0509, -0.454)  ;

    glVertex2f (-0.0379, -0.4296) ;

    glVertex2f (-0.02, -0.44) ;

    glVertex2f (0.00119, -0.4439) ;

    glEnd();

/// left side glass

    glColor3f(1.5f, 0.0f, 0.5f); // Purple color for filling

    glBegin(GL_POLYGON);

    glVertex2f  (-0.06944, -0.16024);

    glVertex2f(-0.04986, -0.1809)  ;

    glVertex2f (-0.04986, -0.26427) ;

    glVertex2f (-0.06944, -0.26427) ;

    glVertex2f(-0.06944, -0.16024)  ;

    glEnd();

/// back left side  glass

    glColor3f(0.5f, 1.0f, 0.5f); // Purple color for filling

    glBegin(GL_POLYGON);

    glVertex2f(-0.0498, -0.3008)  ;

    glVertex2f(-0.04982, -0.38428)  ;

    glVertex2f(-0.07004, -0.40471)  ;

    glVertex2f (-0.0694, -0.3008) ;

    glVertex2f (-0.0498, -0.3008) ;

    glEnd();


/// right side glass

    glColor3f(1.5f, 0.0f, 0.5f); // Purple color for filling

    glBegin(GL_POLYGON);

    glVertex2f  (0.06944, -0.16024);

    glVertex2f(0.04986, -0.1809)  ;

    glVertex2f (0.04986, -0.26427) ;

    glVertex2f (0.06944, -0.26427) ;

    glVertex2f(0.06944, -0.16024)  ;

    glEnd();


/// back right side  glass

    glColor3f(0.5f, 1.0f, 0.5f); // Purple color for filling

    glBegin(GL_POLYGON);

    glVertex2f(0.0498, -0.3008)  ;

    glVertex2f(0.04982, -0.38428)  ;

    glVertex2f(0.07004, -0.40471)  ;

    glVertex2f (0.0694, -0.3008) ;

    glVertex2f (0.0498, -0.3008) ;

    glEnd();

/// roof

    glColor3f(0.5f, 1.0f, 0.5f); // Purple color for filling

    glBegin(GL_POLYGON);

    glVertex2f(-0.0311, -0.1822 )  ;

    glVertex2f(0.0311, -0.18171)  ;

    glVertex2f(0.0311, -0.3669)  ;

    glVertex2f(-0.0311, -0.3669)  ;

    glVertex2f(-0.0311, -0.1822)  ;

    glEnd();

    // Draw other parts of the car (back glass, side glasses, roof)...

    glPopMatrix(); // Restore previous matrix

}




void update(int value)

{

    // No need to continuously move the car in this version

    glutPostRedisplay();

}


GLfloat position = 0.0f;

GLfloat speed = 0.1f;

GLfloat speed1 = 0.05f;

GLfloat speed2 = 0.05f;

GLfloat speed3 = 0.05f;

GLfloat speed4 = 0.05f;

///move other car from y axis to - y


///


///enviroment

void env()

{

    glClearColor(0.2f, 0.8f, 0.2f, 1.0f); // Set background color to a shade of green

    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    //glLoadIdentity(); // Reset the transformation matrix

    // Draw the grass

    glColor3f(0.2f, 0.8f, 0.2f); // Green color for the grass

    glBegin(GL_QUADS);

    glVertex2f(-1.0f, -0.5f); // Bottom-left corner of the grass

    glVertex2f(1.0f, -0.5f); // Bottom-right corner of the grass

    glVertex2f(1.0f, 1.0f); // Top-right corner of the grass

    glVertex2f(-1.0f, 1.0f); // Top-left corner of the grass

    glEnd();

    glScalef(0.8,1,0);

    // Draw the main road

    glColor3f(0.5f, 0.5f, 0.5f); // Gray color for the road

    glBegin(GL_QUADS);

    glVertex2f(-0.65f, -1.0f); // Bottom-left corner of the road

    glVertex2f(0.65f, -1.0f); // Bottom-right corner of the road

    glVertex2f(0.65f, 1.0f); // Top-right corner of the road

    glVertex2f(-0.65f, 1.0f); // Top-left corner of the road

    glEnd();

    // Draw the Left divider

    glColor3f(1.0f, 1.0f, 1.0f); // White color for the divider

    glBegin(GL_QUADS);

    glVertex2f(-0.32f, -1.0f); // Bottom-left corner of the divider

    glVertex2f(-0.3f, -1.0f); // Bottom-right corner of the divider

    glVertex2f(-0.3f, 1.0f); // Top-right corner of the divider

    glVertex2f(-0.32f, 1.0f); // Top-left corner of the divider

    glEnd();

    // Draw the middle divider

    glColor3f(1.0f, 1.0f, 1.0f); // White color for the divider

    glBegin(GL_QUADS);

    glVertex2f(-0.01f, -1.0f); // Bottom-left corner of the divider

    glVertex2f(0.01f, -1.0f); // Bottom-right corner of the divider

    glVertex2f(0.01f, 1.0f); // Top-right corner of the divider

    glVertex2f(-0.01f, 1.0f); // Top-left corner of the divider

    glEnd();

    // Draw the right divider

    glColor3f(1.0f, 1.0f, 1.0f); // White color for the divider

    glBegin(GL_QUADS);

    glVertex2f(0.32f, -1.0f); // Bottom-left corner of the divider

    glVertex2f(0.3f, -1.0f); // Bottom-right corner of the divider

    glVertex2f(0.3f, 1.0f); // Top-right corner of the divider

    glVertex2f(0.32f, 1.0f); // Top-left corner of the divider

    glEnd();

    // Draw the left border

    glColor3f(0.3f, 0.3f, 0.3f); // Darker shade for the border

    glBegin(GL_QUADS);

    glVertex2f(-0.675f, -1.0f); // Bottom-left corner of the border

    glVertex2f(-0.65f, -1.0f); // Bottom-right corner of the border

    glVertex2f(-0.65f, 1.0f); // Top-right corner of the border

    glVertex2f(-0.675f, 1.0f); // Top-left corner of the border

    glEnd();

    // Draw the right border

    glBegin(GL_QUADS);

    glVertex2f(0.65f, -1.0f); // Bottom-left corner of the border

    glVertex2f(0.675f, -1.0f); // Bottom-right corner of the border

    glVertex2f(0.675f, 1.0f); // Top-right corner of the border

    glVertex2f(0.65f, 1.0f); // Top-left corner of the border

    glEnd();

    glLoadIdentity();

    glFlush();

}


void Tree(float x, float y, float sfxy)

{

    glScalef(sfxy,sfxy,0);

    glTranslatef(x, y, 0.0f);

    glColor3ub(165, 42, 42); // Brown color

    glBegin(GL_POLYGON);

    glVertex2f(-0.0694, -0.4018);

    glVertex2f(0.0650, -0.4018);

    glVertex2f(0.0300, -0.1404);

    glVertex2f(-0.0373, -0.1404);

    glEnd();

    // base 1

    glColor3ub(34, 139, 34);

    glBegin(GL_POLYGON);

    glVertex2f(0.4, -0.2);

    glVertex2f(0.0300, -0.1404);

    glVertex2f(-0.0373, -0.1404);

    glVertex2f(-0.4, -0.2);

    glVertex2f(0, 0.1279);

    glEnd();

    // base 2

    glColor3ub(76, 187, 23);

    glBegin(GL_POLYGON);

    glVertex2f(-0.1546, 0.0011); // j

    glVertex2f(-0.3933, -0.0343); // k

    glVertex2f(0, 0.4); // t

    glVertex2f(0.3977, -0.0454); // l

    glVertex2f(0.1560, 0); // m

    glEnd();

    // base 3

    glColor3ub(80, 200, 120);

    glBegin(GL_POLYGON);

    glVertex2f(-0.1896, 0.1906); // n

    glVertex2f(-0.3556, 0.1723); // o

    glVertex2f(0, 0.5257); // p

    glVertex2f(0.3622, 0.1612); // q

    glVertex2f(0.1881, 0.1893); // r

    glEnd();

    // base 4

    glColor3ub(0, 255, 0);

    glBegin(GL_POLYGON);

    glVertex2f(0, 0.4); // t

    glVertex2f(-0.2578, 0.3612); // s

    glVertex2f(0, 0.7190); // g

    glVertex2f(0.2733, 0.3590); // u

    glEnd();

}

void Tree1(float x, float y, float sf)

{

    glScalef(sf,sf,0);

    glTranslatef(x, y, 0.0f);

    glColor3ub(165, 42, 42); // Brown color

    glBegin(GL_POLYGON);

    glVertex2f(-0.0694, -0.4018);

    glVertex2f(0.0650, -0.4018);

    glVertex2f(0.0300, -0.1404);

    glVertex2f(-0.0373, -0.1404);

    glEnd();

    // base 1

    glColor3ub(34, 139, 34);

    glBegin(GL_POLYGON);

    glVertex2f(0.4, -0.2);

    glVertex2f(0.0300, -0.1404);

    glVertex2f(-0.0373, -0.1404);

    glVertex2f(-0.4, -0.2);

    glVertex2f(0, 0.1279);

    glEnd();

    // base 2

    glColor3ub(76, 187, 23);

    glBegin(GL_POLYGON);

    glVertex2f(-0.1546, 0.0011); // j

    glVertex2f(-0.3933, -0.0343); // k

    glVertex2f(0, 0.4); // t

    glVertex2f(0.3977, -0.0454); // l

    glVertex2f(0.1560, 0); // m

    glEnd();

    // base 3

    glColor3ub(80, 200, 120);

    glBegin(GL_POLYGON);

    glVertex2f(-0.1896, 0.1906); // n

    glVertex2f(-0.3556, 0.1723); // o

    glVertex2f(0, 0.5257); // p

    glVertex2f(0.3622, 0.1612); // q

    glVertex2f(0.1881, 0.1893); // r

    glEnd();

}


void Building(float x, float y, float sfxy)
{
    glScalef(sfxy,sfxy,0);
    glTranslatef(x, y, 0.0f);
    glColor3ub(255, 255, 255); // white roof color
    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0.2);
    glVertex2f(0,0.2);
    glVertex2f(0,0);
    glVertex2f(-0.2, 0);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-0.1405, 0.1507);
    glVertex2f(-0.1405, 0.0497);

    glVertex2f(-0.0593, 0.1487);
    glVertex2f(-0.0587, 0.0497);

    glVertex2f(-0.1402, 0.1008);
    glVertex2f(-0.0590, 0.1008);
    glEnd();

    glColor3ub(135, 206, 235); // front sky blue color
    glBegin(GL_POLYGON);
    glVertex2f(-0.2, 0);
    glVertex2f(-0.1403, -0.0762);
    glVertex2f(0.0384, -0.0775);
    glVertex2f(0,0);
    glEnd();

    glColor3ub(135, 206, 235); // right sky blue color
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(0.0384, -0.0775);
    glVertex2f(0.0343, 0.0756);
    glVertex2f(0, 0.2);
    glEnd();

    glColor3ub(255, 255, 255);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2f(-0.1, 0);
    glVertex2f(-0.0670, -0.0767);

    glVertex2f(-0.1685, -0.0401);
    glVertex2f(0.0209, -0.0423);

    glVertex2f(0.0209, -0.0423);
    glVertex2f(0.0184, 0.1330);

    glVertex2f(0, 0.1);
    glVertex2f(0.0366, -0.0092);

    glVertex2f(0, 0);
    glVertex2f(0.0384, -0.0775);

    glVertex2f(-0.1479, 0);
    glVertex2f(-0.1103, -0.0764);

    glVertex2f(-0.05, 0);
    glVertex2f(-0.0137, -0.0768);

    glEnd();
}


void Home(float x, float y, float sfxy)

{

    glScalef(sfxy,sfxy,0);

    glTranslatef(x, y, 0.0f);

    //// Building

    glBegin(GL_POLYGON);

    glColor3ub(255, 0, 0);

    glVertex2f(-.2911,-.2593);

    glVertex2f(-.0015,-0.2055);

    glVertex2f(-.0028,0.2654);

    glVertex2f(-0.2930,.1384);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3ub(255, 0, 100);

    glVertex2f(-.0015,-0.2055);

    glVertex2f(.2736,-0.2547);

    glVertex2f(.2743,0.1470);

    glVertex2f(-.0028,0.2654);

    glEnd();

    // body yellow

    glBegin(GL_POLYGON);

    glColor3ub(255, 240, 0);

    glVertex2f(-0.2495, -0.2516);

    glVertex2f(-0.2298, -0.3041);

    glVertex2f(0.00, -0.3011);

    glVertex2f(-0.0015, -0.2055);

    glEnd();

    // body yellow

    glBegin(GL_POLYGON);

    glColor3ub(255, 240, 0);

    glVertex2f(-0.0015, -0.2055);

    glVertex2f(0.2379,-0.2483);

    glVertex2f(0.2283, -0.2982);

    glVertex2f(0.00, -0.3011);

    glEnd();

    // door

    glBegin(GL_POLYGON);

    glColor3ub(0, 50, 250);

    glVertex2f(-0.0935, -0.2551);

    glVertex2f(0.0854, -0.2546);

    glVertex2f(0.0599, -0.3004);

    glVertex2f(-0.0684, -0.3020);

    glEnd();

    glBegin(GL_POLYGON);

    glColor3ub(255, 120, 0);

    glVertex2f(-0.2298, -0.3041);

    glVertex2f(-0.2811, -0.3246);

    glVertex2f(0.2825, -0.3174);

    glVertex2f(0.2283, -0.2982);

    glEnd();

}


void Palm_Tree(float x, float y, float sfxy)
{
    glScalef(sfxy,sfxy,0);
    glTranslatef(x, y, 0.0f);

    glBegin(GL_POLYGON);
    glColor3ub(150, 75, 0);
    glVertex2f(-0.02, -0.7);
    glVertex2f(0.02, -0.7);
    glVertex2f(0.02, 0.4);
    glVertex2f(-0.02, 0.4);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(1, 100, 32);
    glVertex2f(0, 0.4); //L
    glVertex2f(.2, .4); // E
    glVertex2f(.1, .6); // F
    glVertex2f(0, .6); // O
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(.1, .6); // F
    glVertex2f(.3,.5); // G
    glVertex2f(.3, .9); // H
    glVertex2f(.1, .8); // I
    glVertex2f(.2, 1); // J
    glVertex2f(0, 1); // M
    glVertex2f(0, .6); // O

    glEnd();





    glBegin(GL_POLYGON);
    glColor3ub(1, 100, 32);
    glVertex2f(0, 0.4); //L
    glVertex2f(-.2, .4); // E
    glVertex2f(-.1, .6); // F
    glVertex2f(0, .6); // O
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-.1, .6); // F
    glVertex2f(-.3,.5); // G
    glVertex2f(-.3, .9); // H
    glVertex2f(-.1, .8); // I
    glVertex2f(-.2, 1); // J
    glVertex2f(0, 1); // M
    glVertex2f(0, .6); // O

    glEnd();


}





/// car 1

void car1(int b)

{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glPushMatrix();

    glTranslatef(position1_x, position1, 0.0f); // Apply translation

    glScalef(0.5,0.5,0);

    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for filling

    glVertex2f(-0.0014, -0.057); //1

    glVertex2f(0.0529, -0.0679); //2

    glVertex2f(0.0816, -0.125);  //3

    glVertex2f(0.0816, -0.45);   //4

    glVertex2f(0.0461, -0.5);    //6

    glVertex2f(0, -0.508);       //7

    glVertex2f(-0.0461, -0.5);   //8

    glVertex2f(-0.0816, -0.455); //9

    glVertex2f(-0.0816, -0.125); //10

    glVertex2f(-0.0529, -0.0679);//11

    glVertex2f(-0.0014, -0.057); //1

    glEnd();

    glColor3f(0.0f, 1.0f, 1.0f); // Black color for filling

    glBegin(GL_POLYGON);

    glVertex2f(0.0, -0.1);   // 1

    glVertex2f(0.03327, -0.1065); // 2

    glVertex2f(0.0615, -0.114);   // 3

    glVertex2f(0.05057, -0.1359);// 4

    glVertex2f(0.0338, -0.1566);  // 5

    glVertex2f(0.01597, -0.1514);// 6

    glVertex2f(0, -0.15);    // 7

    glVertex2f(-0.01597, -0.1514);//8

    glVertex2f(-0.0338, -0.1566);//9

    glVertex2f(-0.05057, -0.1359);//10

    glVertex2f(-0.0615, -0.114); //11

    glVertex2f(-0.03327, -0.1065);//12

    glVertex2f(0.0, -0.1);   //1

    glEnd();

    // Drawing other parts of the car (back glass, side glasses, roof) follows the same pattern...

    glPopMatrix();

    glutSwapBuffers(); // Swap front and back buffers

}

/// car 2

void car2(int c)

{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glPushMatrix();

    glTranslatef(position1_x_1, position2, 0.0f); // Apply translation

    glScalef(0.5,0.5,0);

    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for filling

    glVertex2f(-0.0014, -0.057); //1

    glVertex2f(0.0529, -0.0679); //2

    glVertex2f(0.0816, -0.125);  //3

    glVertex2f(0.0816, -0.45);   //4

    glVertex2f(0.0461, -0.5);    //6

    glVertex2f(0, -0.508);       //7

    glVertex2f(-0.0461, -0.5);   //8

    glVertex2f(-0.0816, -0.455); //9

    glVertex2f(-0.0816, -0.125); //10

    glVertex2f(-0.0529, -0.0679);//11

    glVertex2f(-0.0014, -0.057); //1

    glEnd();

    glColor3f(0.0f, 1.0f, 1.0f); // Black color for filling

    glBegin(GL_POLYGON);

    glVertex2f(0.0, -0.1);   // 1

    glVertex2f(0.03327, -0.1065); // 2

    glVertex2f(0.0615, -0.114);   // 3

    glVertex2f(0.05057, -0.1359);// 4

    glVertex2f(0.0338, -0.1566);  // 5

    glVertex2f(0.01597, -0.1514);// 6

    glVertex2f(0, -0.15);    // 7

    glVertex2f(-0.01597, -0.1514);//8

    glVertex2f(-0.0338, -0.1566);//9

    glVertex2f(-0.05057, -0.1359);//10

    glVertex2f(-0.0615, -0.114); //11

    glVertex2f(-0.03327, -0.1065);//12

    glVertex2f(0.0, -0.1);   //1

    glEnd();

    // Drawing other parts of the car (back glass, side glasses, roof) follows the same pattern...

    glPopMatrix();

    glutSwapBuffers(); // Swap front and back buffers

}

/// car 3

void car3(int d)

{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glPushMatrix();

    glTranslatef(position1_x_2, position3, 0.0f); // Apply translation

    glScalef(0.5,0.5,0);

    glBegin(GL_POLYGON);

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for filling

    glVertex2f(-0.0014, -0.057); //1

    glVertex2f(0.0529, -0.0679); //2

    glVertex2f(0.0816, -0.125);  //3

    glVertex2f(0.0816, -0.45);   //4

    glVertex2f(0.0461, -0.5);    //6

    glVertex2f(0, -0.508);       //7

    glVertex2f(-0.0461, -0.5);   //8

    glVertex2f(-0.0816, -0.455); //9

    glVertex2f(-0.0816, -0.125); //10

    glVertex2f(-0.0529, -0.0679);//11

    glVertex2f(-0.0014, -0.057); //1

    glEnd();

    glColor3f(0.0f, 1.0f, 1.0f); // Black color for filling

    glBegin(GL_POLYGON);

    glVertex2f(0.0, -0.1);   // 1

    glVertex2f(0.03327, -0.1065); // 2

    glVertex2f(0.0615, -0.114);   // 3

    glVertex2f(0.05057, -0.1359);// 4

    glVertex2f(0.0338, -0.1566);  // 5

    glVertex2f(0.01597, -0.1514);// 6

    glVertex2f(0, -0.15);    // 7

    glVertex2f(-0.01597, -0.1514);//8

    glVertex2f(-0.0338, -0.1566);//9

    glVertex2f(-0.05057, -0.1359);//10

    glVertex2f(-0.0615, -0.114); //11

    glVertex2f(-0.03327, -0.1065);//12

    glVertex2f(0.0, -0.1);   //1

    glEnd();

    // Drawing other parts of the car (back glass, side glasses, roof) follows the same pattern...

    glPopMatrix();

    glutSwapBuffers(); // Swap front and back buffers

}

/// bomb

///


void bomb()

{

    // Draw bomb body

     glPushMatrix();

    glTranslatef(B1, B2, 0.0f); // Apply translation

    glColor3f(1.0f, 1.0f, 1.0f); // Red color for filling

     glScalef(0.6,0.6,0);

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,0.1);
    glVertex2f(0.0196, 0.0980);
    glVertex2f(0.0398, 0.0917);
    glVertex2f(0.06, 0.08);
    glVertex2f(0.08, 0.06);
    glVertex2f(0.0916, 0.0401);
    glVertex2f(0.0980, 0.0196);
    glVertex2f(0.1, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,-0.1);
    glVertex2f(0.0196, -0.0980);
    glVertex2f(0.0398, -0.0917);
    glVertex2f(0.06, -0.08);
    glVertex2f(0.08, -0.06);
    glVertex2f(0.0916, -0.0401);
    glVertex2f(0.0980, -0.0196);
    glVertex2f(0.1, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(-0,0.1);
    glVertex2f(-0.0196, 0.0980);
    glVertex2f(-0.0398, 0.0917);
    glVertex2f(-0.06, 0.08);
    glVertex2f(-0.08, 0.06);
    glVertex2f(-0.0916, 0.0401);
    glVertex2f(-0.0980, 0.0196);
    glVertex2f(-0.1, 0);

    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(-0,-0.1);
    glVertex2f(-0.0196, -0.0980);
    glVertex2f(-0.0398, -0.0917);
    glVertex2f(-0.06, -0.08);
    glVertex2f(-0.08, -0.06);
    glVertex2f(-0.0916, -0.0401);
    glVertex2f(-0.0980, -0.0196);
    glVertex2f(-0.1, 0);

    glEnd();

    glColor3ub(255, 174, 66);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0.1);
    glVertex2f(0.0196, 0.0980);
    glVertex2f(0.0815, 0.1470);
    glVertex2f(0.0563, 0.1750);
    glEnd();

    glColor3ub(255, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0815, 0.1470);
    glVertex2f(0.0563, 0.1750);
    glVertex2f(0.0529, 0.2051);
    glVertex2f(0.0685, 0.1879);
    glVertex2f(0.0861, 0.2047);
    glVertex2f(0.0853, 0.1785);
    glVertex2f(0.1086, 0.1765);
    glVertex2f(0.0906, 0.1609);
    glVertex2f(0.1196, 0.1482);
    glEnd();

    glPopMatrix();

    glutSwapBuffers();

}

///live

void health(int a) {

    glPushMatrix();

    glTranslatef(H1, position4, 0.0f); // Apply translation

    glColor3f(1.0f, 0.0f, 0.0f); // Red color for filling

    glScalef(0.1,0.1,0);

    glBegin(GL_POLYGON);

        glVertex2f(0,0.5);   //1

        glVertex2f(0.1248, 0.5541);   //2

        glVertex2f(0.2434, 0.5333); //3

        glVertex2f(0.3162, 0.4397);     //4

        glVertex2f(0.3162, 0.3273);    //5

        glVertex2f(0.2704, 0.2296);   //6

        glVertex2f(0.1914, 0.1318);//o

        glVertex2f(0.1144, 0.0444);//o

        glVertex2f(0, -0.0388);

        glEnd();

        glBegin(GL_POLYGON);

        glVertex2f(0,0.5);   //1

        glVertex2f(-0.1248, 0.5541);   //2

        glVertex2f(-0.2434, 0.5333); //3

        glVertex2f(-0.3162, 0.4397);     //4

        glVertex2f(-0.3162, 0.3273);    //5

        glVertex2f(-0.2704, 0.2296);   //6

        glVertex2f(-0.1914, 0.1318);//o

        glVertex2f(-0.1144, 0.0444);//o

        glVertex2f(0, -0.0388);

        glEnd();

    glPopMatrix();

    glutSwapBuffers();

}

void update1(int value1) {

    // Unconditionally update positions of all cars and obstacles

    position1 -= speed1;

    position2 -= speed2;

    position3 -= speed3;

    position4 -= speed4;

    B2 -= speed4;

    // Check if any car is still on the road

    if (position1 > -1.0 || position2 > -1.0 || position3 > -1.0 || position4 > -1.0) {

        // Request a redraw

        glutPostRedisplay();

        // Schedule the next update

        glutTimerFunc(100, update1, 0);

    } else {

        // Generate a new random number to determine the type of car

        int randomCar = rand() % 4;

        // Update the position of the car and obstacles based on the random number

        if (randomCar == 0) {

            position1_x = 1.9f;

            B1 = 0.0f;

        } else if (randomCar == 1) {

            position1_x_1 = 1.5f;

        } else if (randomCar == 2) {

            position1_x_2 = 1.5f;

            B1 = 0.0f;

        } else if (randomCar == 3) {

            H1 = 1.5f;

        }

        // Reset positions

        position1 = 0.0f;

        position2 = 1.20f;

        position3 = 1.50f;

        position4 = 1.90f;

        B2 = 1.2f;

        // Request a redraw

        glutPostRedisplay();

        // Schedule the next update

        glutTimerFunc(100, update1, 0);

    }

}

/*

void update1(int value1) {

    if (position1 > -1.0 ) {

        position1 -= speed1;

         glutPostRedisplay();

        glutTimerFunc(100, update1, 0);

    }

}

*/



void display() {

    glClearColor(0.2f, 0.8f, 0.2f, 1.0f); // Set background color to a shade of green

    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    // Draw environment (grass, road, dividers, borders, etc.)

    env();

    if (lives > 0) {

        drawHearts(); // Draw hearts representing lives left

        // Draw main car

        Main_car();

        /// call function which will mov

         car1(0);

         car2(0);

         car3(0);

         health(0);

        bomb();

                // Check for collision

glColor3f(1.0f, 1.0f, 1.0f); // White color

    glRasterPos2f(-0.9f, 0.9f); // Position of the text

    std::string collisionCountStr = "Collisions: " + std::to_string(collisionCount);

    for (char c : collisionCountStr) {

        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);

    }

        if (checkCollision()) {

            if (lives <= 0)

            {

                glColor3f(1.0f, 0.0f, 0.0f);

                glRasterPos2f(-0.3f, 0.0f);

                const char* gameOverMessage = "Game Over";

                for (int i = 0; gameOverMessage[i] != '\0'; i++) {

                    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOverMessage[i]);


                }

            }

        }

    }

    else {

        glColor3f(1.0f, 0.0f, 0.0f);

        glRasterPos2f(-0.3f, 0.0f);

        const char* gameOverMessage = "Game Over";

        for (int i = 0; gameOverMessage[i] != '\0'; i++) {

            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOverMessage[i]);

        }

    }


    // right
    glLoadIdentity();
    Tree(3.8,-1.3,  0.2);
    glLoadIdentity();
    Home(2.2,-1.1, .4);
    glLoadIdentity();
    Tree1(6.2, -1.6, .15);
    glLoadIdentity();
    glLoadIdentity();
    Tree1(4, -1.8, .15);
    glLoadIdentity();

    // left
    glLoadIdentity();
    Tree(-3.6,1.8,  0.2);
    glLoadIdentity();
    Home(-1.8,.5, .4);
    glLoadIdentity();
    Tree1(-4, 2.4, .15);
    glLoadIdentity();

    // Hospital
    Building(.65,.1, 1.3);
    glLoadIdentity();

    // left
    Palm_Tree(-2.75, 1.55, .3);
    glLoadIdentity();

    Palm_Tree(-5.2, 2.1 ,.18);
    glLoadIdentity();



    glFlush();

}


// Function to draw text on the screen
void drawText(const std::string& text, float x, float y) {
    glRasterPos2f(x, y); // Set the position for the text
    // Loop through each character in the string and draw it
    for (const char& c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c); // Render each character
    }
}



///first intructions page

void drawText(const char *text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void drawText3(const char *text, float x, float y) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
}

void firstPage() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 1.0f);
    drawText("INSTRUCTIONS", -0.5f, 0.03f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText("Press 'Enter' To Start", -0.5f, -0.1f);
    drawText("Press 'w' for up", -0.5f, -0.2f);
    drawText("Press 's' for down", -0.5f, -0.3f);
    drawText("Press 'a' for left", -0.5f, -0.4f);
    drawText("Press 'd' for right", -0.5f, -0.5f);

    glutSwapBuffers();
}

void coverPage() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2235f, 0.5176f, 0.5686f);
    drawText3("AMERICAN INTERNATIONAL UNIVERSITY-BANGLADESH", -0.8f, 0.8f);
    glColor3f(0.2157f, 0.4039f, 0.5490f);
    drawText("Faculty of Science and Technology", -0.3f, 0.65f);
    glColor3f(0.3216f, 0.1333f, 0.1412f);
    drawText("Course: Computer Graphics", -0.22f, 0.5f);
    glColor3f(0.1764f, 0.1764f, 0.3804f);
    drawText("Section: E", -0.1f, 0.35f);
     glColor3f(0.1764f, 0.1764f, 0.3804f);
    drawText("Project Title: Car Rushing Game", -0.25f, 0.22f);
     glColor3f(0.1764f, 0.1764f, 0.3804f);
    drawText("Supervised By: Mahfujur Rahman", -0.25f, 0.15f);
    glColor3f(0.7686f, 0.0784f, 0.0784f);
    drawText("Group Members:", -0.2f, -0.1f);
    glColor3f(0.7686f, 0.0784f, 0.0784f);
    drawText3("1.   Dip Achorjee Shokal    (ID:22-46788-1)", -0.7f, -0.2f);
    drawText3("2.   Shourav Mistry         (ID:22-46077-1)", -0.7f, -0.3f);
    drawText3("3.   MD. Bahauddin Sakib    (ID:22-46093-1)", -0.7f, -0.4f);
    drawText3("4.   P.M. Tasriful Islam    (ID:22-47885-2)", -0.7f, -0.5f);
    drawText3("5.   Fardil Chowdhury       (ID:22-46109-1)", -0.7f, -0.6f);
    drawText3("Press n to go Next Page", 0.2f, -0.8f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawText("Press 'N' to go Next", 0.4f, -0.89f);
    glutSwapBuffers();
}


///control function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
        exit(0);
        break;
    case '0':
        main_car_x = -0.00014f; // Reset to initial position
        break;
    case 'a':
        main_car_x -= 0.1f; // Decrease x value by 0.1
        break;
    case 'd':
        main_car_x += 0.1f; // Increase x value by 0.1
        break;
        case 'w':
        main_car_y += 0.1f; // Reset to initial position
        break;
    case 's':
        main_car_y -= 0.1f; // Decrease x value by 0.1
        break;

 case 27: // Escape key
            if (gameover == 1)
                exit(0);
            break;
        case 13: // Enter key
            if (gameover == 0)
                glutDisplayFunc(display); // Replace 'display' with your function
            break;
        case 'n': // 'N' key
            glutDisplayFunc(firstPage);
            break;
        default:
            std::cout << "Invalid input\n";
            break;
    }
    glutPostRedisplay();
}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(425, 0);
    glutCreateWindow("Road with Car");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100, update, 0);
    glutTimerFunc(100, update1, 0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(coverPage);
    glutKeyboardFunc(keyboard);

    sndPlaySound("aa", SND_ASYNC|SND_LOOP);

    glutMainLoop();



    return 0;
}
