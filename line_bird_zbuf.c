#include<stdio.h>
#include<Windows.h>
//#include<X11/Xwindows.h>
#include<GL/glut.h>

#include<SOIL.H>
#define OBS_MAX_HEIGHT 275
#define OBS_SPACING 75
#define BIRD_UP_SPEED 15
#define SCREEN_MOVE_SPEED 25
#define SLEEPTIME 50
#define SIZE 512
#define factor 25
GLuint texture,back,start,end;
GLfloat *z;
GLUquadric* qobj;
 GLuint selectBuf[SIZE];
   GLint hits;
   GLint viewport[4];
int obstacles[200][2];
int flag=0,flag_pos=0,flag_exit=0,game =0, start_game =0;
float bx=75,by=300;
int moveFactor=SCREEN_MOVE_SPEED,count_obs=2,count_tex=0;
void myDisplay();
void moveScreen();
void populateObstacles()
{
int i;
	for(i=0;i<200;i++)
	{
		obstacles[i][0]=rand()%OBS_MAX_HEIGHT;
		obstacles[i][1]=rand()%2;
	}
}
void game_over()
{

    /*  glBindTexture( GL_TEXTURE_2D, end);
      glPushMatrix();
glColor3f(1,1,1);
glBegin( GL_QUADS );

      glTexCoord2d(0,0); glVertex3f(-30+moveFactor,0,0);
        glTexCoord2d(0,1); glVertex3f(-30+moveFactor,500,0);
      glTexCoord2d(1,1); glVertex3f(500+moveFactor,500,0);
      glTexCoord2d(1,0); glVertex3f(500+moveFactor,0,0);
      glEnd();
      glFlush();
    glPopMatrix();*/
if(flag_exit)
{

flag_exit=0;
game = 0;
printf("SCORE: %d",count_obs+1);
	glRasterPos3i( 250,250,0);
	glColor3f(0,0,0);
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H'); // Print a character on the screen
glFlush();
}
    glutSwapBuffers();
    glColor3f(0,0,0);
    glutPostRedisplay();
}

void fake()
{

glEnable( GL_TEXTURE_2D );
      glBindTexture( GL_TEXTURE_2D, start);
      glPushMatrix();
glColor3f(1,1,1);
glBegin( GL_QUADS );

      glTexCoord2d(0,0); glVertex3f(0,0,+10);
        glTexCoord2d(0,1); glVertex3f(0,500,+10);
      glTexCoord2d(1,1); glVertex3f(500,500,+10);
      glTexCoord2d(1,0); glVertex3f(500,0,+10);
      glEnd();
      glFlush();
    glPopMatrix();
    glutSwapBuffers();
    glColor3f(0,0,0);
    glutPostRedisplay();

}
void keyboard (unsigned char key, int x, int y)
{
    if(key =='S' || key == 's')
    {
        if(start_game == 0)
        {


                game=1;
                start_game = 1;

                glutDisplayFunc(myDisplay);
	glutIdleFunc(moveScreen);
	}
    }
}
void myInit()
{
	populateObstacles();

	  texture = SOIL_load_OGL_texture
	(
		"/bird.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|SOIL_FLAG_MIPMAPS
		);

    if( 0 == texture)
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  end = SOIL_load_OGL_texture
	(
		"/end.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|SOIL_FLAG_MIPMAPS
		);

    if( 0 == end)
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}
glBindTexture(GL_TEXTURE_2D, end);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);


	  back = SOIL_load_OGL_texture
	(
		"/back.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|SOIL_FLAG_MIPMAPS
		);

    if( 0 == back)
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}
glBindTexture(GL_TEXTURE_2D, back);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  start = SOIL_load_OGL_texture
	(
		"/start.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|SOIL_FLAG_MIPMAPS
		);

    if( 0 == start)
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}
glBindTexture(GL_TEXTURE_2D, start);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);


glEnable(GL_DEPTH_TEST);
glDepthMask(GL_TRUE);
 glDepthFunc(	GL_ALWAYS);
 //glDepthRange(0,1);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,500.0,0.0,500.0,-10,10);
	glMatrixMode(GL_MODELVIEW);
    glClearColor(1,1,1,1);
	glColor3f(0.0,0.0,0.0);
    /*	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);*/

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

    	qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_FLAT);
	glShadeModel(GL_FILL);

}
void drawObstacles()
{
	int n;
	for(n=0;n<200;n++)
	{ glLoadName(1);
		//glBegin(GL_QUADS);

		if(obstacles[n][1]==1)  //obstacle up
		{
			glPushMatrix();
			glTranslatef(0.0,500.0-obstacles[n][0],0.0);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(qobj, 2, 10,obstacles[n][0] , 15, 5);
			glPopMatrix();
		}
		else if(obstacles[n][1]==0)  //obstacle down
		{
			glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			gluCylinder(qobj, 10, 2,obstacles[n][0] , 15, 5);
			glPopMatrix();
		}
		glEnd();
		glFlush();
		glTranslatef(OBS_SPACING,0.0,0.0);
	}
	glTranslatef(-(OBS_SPACING*200),0.0,0.0);
}
void drawBird()
{


	if(flag==1)
		by=by+BIRD_UP_SPEED;
	else if(flag==0)
		by=by-BIRD_UP_SPEED;
	bx=bx+SCREEN_MOVE_SPEED;

	//printf("%f %f\n",bx,by);
	glColor3f(1.0,1.0,1.0);

	//glPushMatrix();
glEnable( GL_TEXTURE_2D );
      glBindTexture( GL_TEXTURE_2D, texture);
      glLoadName(2);
glBegin( GL_QUADS );

      glTexCoord2d(0,0); glVertex3f(bx-factor,by-factor,-8);
      glTexCoord2d(0,1); glVertex3f(bx-factor,by+factor,-8);
      glTexCoord2d(1,1); glVertex3f(bx+factor,by+factor,-8);
      glTexCoord2d(1,0); glVertex3f(bx+factor,by-factor,-8);
      glEnd();
      glFlush();
//glPopMatrix();

	/*glBegin(GL_QUADS);
	glVertex2f(bx-10,by-10);
	glVertex2f(bx-10,by+10);
	glVertex2f(bx+10,by+10);
	glVertex2f(bx+10,by-10);
	glEnd();*/
	glutSwapBuffers();

	glColor3f(0.0,0.0,0.0);
}





void check()
{
if(flag_pos==2)
{

        if(obstacles[count_obs][1]==1) //up
        {
           // printf(" up :BX:%f,BY:%f,obs:%d  count:%d",bx,by,obstacles[count_obs][0],count_obs);

                        if( (by+10)<=500 && 500-(by+10) <= obstacles[count_obs][0] )
                {       printf("hitt up\n");
                        flag_exit=1;
                glutIdleFunc(NULL);
                Sleep(500);
                glutDisplayFunc(game_over);
                glutPostRedisplay();
       //exit(0);
                }
        }
        else  //down
            {
                            // printf(" down :BX:%f,BY:%f,obs:%d  count:%d",bx,by,obstacles[count_obs][0],count_obs);
                             if( (by-10)>=0 &&(by-10) <= obstacles[count_obs][0] )
                            {
                                printf("hit down\n");
                            flag_exit=1;
                            glutIdleFunc(NULL);
                             Sleep(500);
                              glutDisplayFunc(game_over);
                glutPostRedisplay();
        //exit(0);
                            }

            }
            count_obs++;
            flag_pos=0;
}

else
flag_pos++;

if(by<0 || by>500 )
{   flag_exit=1;
    glutIdleFunc(NULL);
     Sleep(500);
      glutDisplayFunc(game_over);
                glutPostRedisplay();

}

}




void moveScreen(void)
{

check();
   //checkcollision();

	Sleep(SLEEPTIME);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0+moveFactor,500.0+moveFactor,0.0,500.0,-10,10);
	glMatrixMode(GL_MODELVIEW);
	moveFactor=moveFactor+SCREEN_MOVE_SPEED;
	//count_obs=moveFactor/SCREEN_MOVE_SPEED;
	//glReadPixels(bx,by,10,10,GL_DEPTH_COMPONENT,GL_FLOAT,z);
	//printf("%d\n",moveFactor);


//printf("depth: %u\n",(*z));

	/*if(moveFactor>3500)
        moveFactor=SCREEN_MOVE_SPEED;*/
        if(flag_exit ==0)
	glutPostRedisplay();



/*glMatrixMode (GL_PROJECTION);
glPushMatrix ();
glRenderMode(GL_SELECT);

   glLoadIdentity ();
   gluPickMatrix ((GLdouble) bx, (GLdouble) (viewport[3] -by),
                  1.0, 1.0, viewport);
   gluOrtho2D(0.0+moveFactor,500.0+moveFactor,0.0,500.0);
   //drawObstacles();
	//drawBird();

    glMatrixMode (GL_PROJECTION);
      glPopMatrix ();

     hits = glRenderMode (GL_RENDER);
     printf("hits =%d",hits);
     if(hits>1)
        glutIdleFunc(NULL);
    processHits (hits, selectBuf);*/
  // glutPostRedisplay();

  //



}



void moveBird(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		flag=1;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		flag=0;
	}
}



void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//check();
//glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, back);
      glPushMatrix();
glColor3f(1,1,1);
glBegin( GL_QUADS );

      glTexCoord2d(0,0); glVertex3f(0+SCREEN_MOVE_SPEED*count_tex,0,-10);
        glTexCoord2d(0,1); glVertex3f(0+SCREEN_MOVE_SPEED*count_tex,500,-10);
      glTexCoord2d(1,1); glVertex3f(530+SCREEN_MOVE_SPEED*count_tex,500,-10);
      glTexCoord2d(1,0); glVertex3f(530+SCREEN_MOVE_SPEED*count_tex++,0,-10);
      glEnd();
      glFlush();
    glPopMatrix();
    glColor3f(0,0,0);
	drawObstacles();
	drawBird();


}
int main(int argc,char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH );
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,100);
	glutCreateWindow("Line Birds");



	if(game ==0)
	{
	    glutDisplayFunc(fake);
	    glutIdleFunc(NULL);
	}
	else
	{


	glutDisplayFunc(myDisplay);
	glutIdleFunc(moveScreen);
	}
	glutMouseFunc(moveBird);
	glutKeyboardFunc(keyboard);
	//glutReshapeFunc(myReshape);
	myInit();
	glutMainLoop();
	return 0;
}


