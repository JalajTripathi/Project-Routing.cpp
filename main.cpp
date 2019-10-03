#include <stdio.h>
#include <stdlib.h>
#include <GL/GLUT.h>
#include <math.h>
#include <time.h>
#define PI 3.1415927
#define INFINITY 9999
#define MAX 5
int dispflag=0;
bool nextw=false;
float linex=0.0,liney=0.0;
int selectFlag=0,startsim=0;
float startx=0.0,starty=0.0,endx=0.0,endy=0.0,incx=0.0,incy=0.0;
int endflag=0;
int startnode=0,endnode=0;
int drawpath[MAX]={0,0,0,0,0};
int drawindex=MAX-1;
int DIST[MAX][MAX]={{0,10,0,30,100},{10,0,50,0,0},{0,50,0,20,10},{30,0,20,0,60},{100,0,10,60,0}};
float points[MAX+1][2]={{-2.0,0.0},{-1.0,-1.0},{1.0,-1.0},{2.0,0.0},{0.0,1.0},{0.0,0.0}};
int pathlength=0;
int pathiteration=0;
int nodeval;
float switchx=0.0,switchy=0.0;
  int doz=0;
  float taby=0.0;
  int finalpath[8]={0,0,0,0,0,0,0,0};
int finali=0,finalv=0,k;
float sx=5.0,sy=5.0;
float ex=5.0,ey=5.0;
char table[8][10]={"","","","","","","",""};
int tabi=0;
 char noden[10]="";
char* dest;
char* dst;
char fin[10]="";
char node[10]="Node ";
void drawString(float x, float y, float z, char * string) {
    char * c;
    glRasterPos3f(x, y, z);
    for (c = string; * c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, * c);
    }
}
void drawString1(float x, float y, float z, char * string) {
    char * c;
    glRasterPos3f(x, y, z);
    for (c = string; * c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, * c);
    }
}
void drawString2(float x, float y, float z, char * string) {
    char * c;

    glRasterPos3f(x, y, z);
    for (c = string; * c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, * c);
    }
}
void drawString3(float x, float y, float z, char * string) {
    char * c;
    glColor3f(0.5,0.3,1.0);
    glRasterPos3f(x, y, z);
    for (c = string; * c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, * c);
    }
}

void dijkstra(int G[MAX][MAX],int n,int startnode,int finish)
{

	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],countl,mindistance,nextnode,i,j;
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				cost[i][j]=INFINITY;
			else
				cost[i][j]=G[i][j];

	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	countl=1;

	while(countl<n-1)
	{
		mindistance=INFINITY;
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			//check if a better path exists through nextnode
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+cost[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+cost[nextnode][i];
						pred[i]=nextnode;
					}
		countl++;
	}
	//print the path and distance of each node
		if(finish!=startnode)
		{
			drawpath[drawindex--]=finish;
			j=finish;
			do
			{
				j=pred[j];
				drawpath[drawindex--]=j;
			}while(j!=startnode);
	}
}

void lines(int value)
{
    linex+=incx;
    liney+=incy;
    bool stop=false;
  endflag++;
    if(endflag>(10*pathiteration))
    {
    finalv++;
  sx=startx;
  sy=starty;
  ex=endx;
  ey=endy;
        if(pathiteration<pathlength-1)
        {
           nodeval=drawpath[drawindex++];
            itoa(nodeval+1,  noden, 10);
        dst=strcat(node,noden);
        strcpy(fin,dst);
         strcpy(node,"Node ");
       for(k=0;k<=5;k++)
        table[tabi][k]=fin[k];
       tabi++;
           startx=points[nodeval][0];
           starty=points[nodeval][1];
           nodeval=drawpath[drawindex];
            itoa(nodeval+1,  noden, 10);
        dst=strcat(node,noden);
        strcpy(fin,dst);
         strcpy(node,"Node ");
       for(k=0;k<=5;k++)
        table[tabi][k]=fin[k];
       tabi++;
           endx=points[nodeval][0];
           endy=points[nodeval][1];
           incx=(endx-startx)/10;
           incy=(endy-starty)/10;
           linex=startx;
           liney=starty;
           pathiteration++;
           endflag--;
        }
        else
        {
            stop=true;
        }
    }

        if(!stop){
                 glutPostRedisplay();
    glutTimerFunc(200,lines,0);
        }
}
void lines()
{
    glPushMatrix();
    glPushAttrib(GL_LINE_BIT);
    glLineStipple(15, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(startx,starty,-5.0);
    glVertex3f(linex,liney,-5.0);
    glEnd();
   glPopAttrib();
    glPopMatrix();

}

void linesw(int value)   //Moving amination
{
    linex+=incx;
    liney+=incy;
    bool stop=false;
    endflag++;
    if(endflag>10&&doz==0)
    {
        if(endx==0.0&&endy==1.0)
            taby=0.5;
        else if(endx==-2.0&&endy==0.0)
            taby=1.3;
            if(endx==-1.0&&endy==-1.0)
            taby=1.1;
            if(endx==1.0&&endy==-1.0)
            taby=0.9;
            if(endx==2.0&&endy==0.0)
            taby=0.7;
            startx=switchx;
            starty=switchy;
            incx=(endx-startx)/10;
            incy=(endy-starty)/10;
            linex=startx;
            liney=starty;
            doz=1;
            endflag--;
        }
        if(endflag>20)
            stop=true;
    if(!stop){
        glutPostRedisplay();
        glutTimerFunc(200,linesw,0);
    }
}
void linesw()
{
    glPushMatrix();
    glPushAttrib(GL_LINE_BIT);
    glLineStipple(15, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(startx,starty,-5.0);
    glVertex3f(linex,liney,-5.0);
    glEnd();
    glPopAttrib();
    glPopMatrix();
}

void draw_linex(float x1,float y1,float x2, float y2,int dash)
{

glColor3f(0.5,0.5,0.5);
glLineWidth(3.0);
 glBegin(GL_LINES);
 glVertex3f(x1,y1,-5.0);
 glVertex3f(x2,y2,-5.0);
 glEnd();

 if(dash==1){
   glPushMatrix();
    glPushAttrib(GL_LINE_BIT);
    glLineStipple(15, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(7.0);
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(x1,y1,-5.0);
    glVertex3f(x2,y2,-5.0);
    glEnd();
   glPopAttrib();
    glPopMatrix();
 }
}


void draw_cylinder(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;
    GLfloat width=5.0f;
    /** Draw the tube */
    glColor3ub(R+30,G-60,B-20);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        glVertex3f(x, y , 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y , height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
    glColor3ub(0,0,255);
    angle=1.75*PI;
    glLineWidth(width);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,height);
    glVertex3f(radius*cos(angle),radius * sin(angle),height);
    glEnd();

    angle=0.25*PI;
    glBegin(GL_LINES);

    glVertex3f(0.0,0.0,height);
    glVertex3f(radius*cos(angle),radius * sin(angle),height);
    glEnd();
    angle=0.75*PI;
    glBegin(GL_LINES);

    glVertex3f(0.0,0.0,height);
    glVertex3f(radius*cos(angle),radius * sin(angle),height);
    glEnd();
    angle=1.25*PI;
    glBegin(GL_LINES);

    glVertex3f(0.0,0.0,height);
    glVertex3f(radius*cos(angle),radius * sin(angle),height);
    glEnd();

}
void draw_line(float x1,float y1,float x2, float y2)
{
glColor3f(0.5,0.5,0.5);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex3f(x1,y1,-5.0);
    glVertex3f(x2,y2,-5.0);
    glEnd();
}
void draw_linef(float x1,float y1,float x2, float y2)
{
    glColor3f(1,0,0);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glVertex3f(x1,y1,-5.0);
    glVertex3f(x2,y2,-5.0);
    glEnd();
}
char* node1="";
char* node2="";
char* node3="";
char* node4="";
char* node5="";

int dstTime = 0; // milliseconds
void display()
{
    if (dispflag==0){
  //  const int curTime = glutGet( GLUT_ELAPSED_TIME );
    // figure out how far along duration we are, between 0.0 and 1.0
   // const float t = std::cos(float(curTime) * 0.001) * 0.5 + 0.5;
    // interpolate between two colors
   // Color curColor = lerp(makeColor(0.0, 0.3, 0.5), makeColor(0.5, 0.3, 1.0), t);
    glClearColor(0.5, 0.3, 1.0, 1 );
    glClear( GL_COLOR_BUFFER_BIT );

      glLoadIdentity();
    glPushMatrix();
     glColor3f(1.0, 1.0, 1.0);
 glTranslatef(-1.2,1.4,-5.0);
     drawString1(0.0, 0.0, 0.0, "Computer Graphics Project on Routing and Switching");
     drawString(0.0, -0.2, 0.0, "Done by - ");
      drawString(0.5, -0.2, 0.0, "Ivor D'Souza      4SO16CS040");
       drawString(0.5, -0.35, 0.0, "Jalaj Tripathi       4SO16CS042");
         drawString(0.0, -0.5, 0.0, "Under the guidance of Mr.Prithviraj");
     drawString1(0.8, -1.2, 0.0, "Options");
      drawString(0.8, -1.4, 0.0, "1 - Routing");
       drawString(0.8, -1.6, 0.0, "2 - Switching");
        drawString(0.8, -1.8, 0.0, "3 - About");
         drawString(0.8, -2.0, 0.0, "4 - Exit");
            glPopMatrix();
      glFlush();

 //  glutSwapBuffers();

    }
    else if(dispflag==2) {
 glClearColor( 0,0,0, 0 );
  glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-0.9,1.6,-5.0);
    drawString1(0.0, 0.0, 0.0, "Simulation of Switching of Packets");
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-3.0,1.6,-5.0);
    drawString(0.0, 0.0, 0.0, "R - Reset");
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-3.0,1.5,-5.0);
    drawString(0.0, 0.0, 0.0, "S - Start");
    glPopMatrix();

    draw_line(0.0,1.0,0.0,0.0);
    draw_line(-2.0,0.0,0.0,0.0);
    draw_line(-1.0,-1.0,0.0,0.0);
    draw_line(1.0,-1.0,0.0,0.0);
    draw_line(2.0,0.0,0.0,0.0);

    draw_line(1,0.3,1,1.5); //start table
    draw_line(1.82,0.3,1.82,1.5);
    draw_line(1,0.5,2.64,0.5);
    draw_line(1, 1.5, 2.64, 1.5);

    draw_line(1, 0.7, 2.64, 0.7);
    draw_line(1, 0.9, 2.64, 0.9);
    draw_line(1, 1.1, 2.64, 1.1);
    draw_line(1, 1.3, 2.64, 1.3);
    draw_line(2.64, 0.3, 2.64, 1.5);
      draw_line(1, 0.3, 2.64, 0.3); //end table
    glPushMatrix();

    glPopMatrix();
    //LEFT
    glPushMatrix();
    glTranslatef(-2.0,0.0,-5.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    if(node1=="Source"||node1=="Destination")
        draw_cylinder(0.2, 0.1, 100, 100, 100);
    else
        draw_cylinder(0.2, 0.1, 0, 255, 143);
    glColor3f(1.0, 1.0, 0.0);
    drawString(0.2, 0.1, 0, "Node A");
    glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node1);
    glPopMatrix();
    //BOTTOM LEFT
    glPushMatrix();
    glTranslatef(-1.0,-1.0,-5.0);
    glRotatef(-60, 1.0, 0.0, 0.0);
    if(node2=="Source"||node2=="Destination")
        draw_cylinder(0.2, 0.1, 100, 100, 100);
    else
        draw_cylinder(0.2, 0.1, 0, 255, 143);
    glColor3f(1.0, 1.0, 0.0);
    drawString(0.2, 0.1, 0, "Node B");
    glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node2);
    glPopMatrix();
    //BOTTOM RIGHT
    glPushMatrix();
    glTranslatef(1.0,-1.0,-5.0);
    glRotatef(-60, 1.0, 0.0, 0.0);
    if(node3=="Source"||node3=="Destination")
        draw_cylinder(0.2, 0.1, 100, 100, 100);
    else
        draw_cylinder(0.2, 0.1, 0, 255, 143);
    glColor3f(1.0, 1.0, 0.0);
    drawString(0.2, 0.1, 0, "Node C");
    glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node3);
    glPopMatrix();
    //TOP
    glPushMatrix();
    glTranslatef(0.0,1.0,-5.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    if(node5=="Source"||node5=="Destination")
        draw_cylinder(0.2, 0.1, 100, 100, 100);
    else
        draw_cylinder(0.2, 0.1, 0, 255, 143);
    glColor3f(1.0, 1.0, 0.0);
    drawString(0.2, 0.1, 0, "Node E");
    glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node5);
    glPopMatrix();
    //RIGHT
    glPushMatrix();
    glTranslatef(2.0,0.0,-5.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    if(node4=="Source"||node4=="Destination")
        draw_cylinder(0.2, 0.1, 100, 100, 100);
    else
        draw_cylinder(0.2, 0.1, 0, 255, 143);
    glColor3f(1.0, 1.0, 0.0);
    drawString(0.2, 0.1, 0, "Node D");

    glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node4);
    glPopMatrix();


     glPushMatrix();
       glTranslatef(1.02,1.37,-5.0);
        glColor3f(0.8,0.3,1.0);
     drawString2(0.0, 0.0, 0, "Switchport Number");
     drawString2(0.95, 0.0, 0, "MAC Address");
       drawString3(0.35, -0.2, 0, "1");
     drawString3(1.2, -0.2, 0, "A");
      drawString3(0.35, -0.4, 0, "2");
     drawString3(1.2, -0.4, 0, "B");
      drawString3(0.35, -0.6, 0, "3");
     drawString3(1.2, -0.6, 0, "C");
      drawString3(0.35, -0.8, 0, "4");
     drawString3(1.2, -0.8, 0, "D");
      drawString3(0.35, -1.0, 0, "5");
     drawString3(1.2, -1.0, 0, "E");
    glPopMatrix();
    glPushMatrix();
     glTranslatef(-0.1,-0.1,-5.0);
       glColor3f(0.5, 0.3, 1.0);
        glBegin(GL_POLYGON);
         glVertex3f(0.2 , -0.1, 0);
    glVertex3f(-0.2 , -0.1, 0);
    glVertex3f(-0.2 , 0.1, 0);
    glVertex3f(0.2 , 0.1, 0);
    glVertex3f(0.2 , -0.1, 0);
    glVertex3f(0.45 , 0.13, 0);
     glVertex3f(0.45 , 0.3, 0);
    glVertex3f(0.0 , 0.3, 0);
     glVertex3f(-0.2 , 0.1, 0);
     glVertex3f(0.2 , 0.1, 0);
      glVertex3f(0.45 , 0.3, 0);
    glEnd();
      glColor3f(1, 1, 0.0);
      glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.2 , -0.1, 0);
    glVertex3f(-0.2 , -0.1, 0);
    glVertex3f(-0.2 , 0.1, 0);
    glVertex3f(0.2 , 0.1, 0);
    glVertex3f(0.2 , -0.1, 0);
    glVertex3f(0.45 , 0.13, 0);
     glVertex3f(0.45 , 0.3, 0);
    glVertex3f(0.0 , 0.3, 0);
     glVertex3f(-0.2 , 0.1, 0);
     glVertex3f(0.2 , 0.1, 0);
      glVertex3f(0.45 , 0.3, 0);
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
      drawString(-0.02, 0.18, 0, "Switch");
          glColor3f(0.9, 1.0, 0.9);
      drawString(-0.3,0.15,0,"1");
      drawString(0.5,0.15,0,"4");
      drawString(-0.3,-0.2,0,"2");
      drawString(0.45,-0.2,0,"3");
      drawString(0.15,0.4,0,"5");
    glPopMatrix();
    if(startsim&&taby!=0.0)
    {
        draw_linef(1.0,taby,2.64,taby);
         draw_linef(1.0,taby-0.2,2.64,taby-0.2);
          draw_linef(1.0,taby,1.0,taby-0.2);
           draw_linef(2.64,taby,2.64,taby-0.2);
    }
    if(startsim)
    {
        glPushMatrix();
        linesw();
        glPopMatrix();
    }

    glFlush();
    }
    else if(dispflag==1)
    {glClearColor( 0,0,0, 0 );
         glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
     glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-0.9,1.6,-5.0);
     drawString1(0.0, 0.0, 0.0, "Simulation of Dijkstra's Algorithm in Routing");
     glPopMatrix();
       glPushMatrix();
     glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-3.0,1.6,-5.0);
     drawString(0.0, 0.0, 0.0, "R - Reset");
     glPopMatrix();
         glPushMatrix();
     glColor3f(1.0, 1.0, 1.0);
    glTranslatef(-3.0,1.5,-5.0);
     drawString(0.0, 0.0, 0.0, "S - Start");
     glPopMatrix();

       draw_linex(1.5,0.5,1.5,1.5,0); //start table
    draw_linex(2.5,0.5,2.5,1.5,0);
    draw_linex(1.5,0.5,2.5,0.5,0);
    draw_linex(1.5,1.5,2.5,1.5,0);
    draw_linex(1.5,0.7,2.5,0.7,0);
    draw_linex(1.5,0.9,2.5,0.9,0);
    draw_linex(1.5,1.1,2.5,1.1,0);
   draw_linex(1.5,1.3,2.5,1.3,0);
    draw_linex(2.0,0.5,2.0,1.5,0); //end table

     if(sx==0.0&&sy==1.0&&ex==-2.0&&ey==0.0||sx==-2.0&&sy==0.0&&ex==0.0&&ey==1.0)
        finalpath[0]=1;
       if(sx==-1.0&&sy==-1.0&&ex==-2.0&&ey==0.0||sx==-2.0&&sy==0.0&&ex==-1.0&&ey==-1.0)
        finalpath[1]=1;
    if(sx==-1.0&&sy==-1.0&&ex==1.0&&ey==-1.0||sx==1.0&&sy==-1.0&&ex==-1.0&&ey==-1.0)
        finalpath[2]=1;
     if(sx==1.0&&sy==-1.0&&ex==2.0&&ey==0.0||sx==2.0&&sy==0.0&&ex==1.0&&ey==-1.0)
        finalpath[3]=1;
       if(sx==0.0&&sy==1.0&&ex==2.0&&ey==0.0||sx==2.0&&sy==0.0&&ex==0.0&&ey==1.0)
        finalpath[4]=1;
      if(sx==0.0&&sy==1.0&&ex==1.0&&ey==-1.0||sx==1.0&&sy==-1.0&&ex==0.0&&ey==1.0)
        finalpath[5]=1;
      if(sx==0.0&&sy==1.0&&ex==-1.0&&ey==-1.0||sx==-1.0&&sy==-1.0&&ex==0.0&&ey==1.0)
        finalpath[6]=1;
     if(sx==2.0&&sy==0.0&&ex==-2.0&&ey==0.0||sx==-2.0&&sy==0.0&&ex==2.0&&ey==0.0)
        finalpath[7]=1;
    draw_linex(0.0,1.0,-2.0,0.0,finalpath[0]);
     draw_linex(-2.0,0.0,-1.0,-1.0,finalpath[1]);
      draw_linex(-1.0,-1.0,1.0,-1.0,finalpath[2]);
       draw_linex(1.0,-1.0,2.0,0.0,finalpath[3]);
        draw_linex(2.0,0.0,0.0,1.0,finalpath[4]);
            draw_linex(0.0,1.0,1.0,-1.0,finalpath[5]);
        draw_linex(0.0,1.0,-1.0,-1.0,finalpath[6]);
      draw_linex(-2.0,0.0,2.0,0.0,finalpath[7]);
    //LEFT
    glPushMatrix();
 glTranslatef(-2.0,0.0,-5.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    if(node1=="Source"||node1=="Destination")
          draw_cylinder(0.2, 0.1, 100, 100, 100);
else
  draw_cylinder(0.2, 0.1, 0, 255, 143);
 glColor3f(1.0, 1.0, 0.0);
    drawString(-0.6, 0.1, 0, "Node 1");
   glColor3f(0.9, 1.0, 0.9);
        drawString2(0.2, -0.4, 0, "10");
            drawString2(0.3, -0.1, 0, "30");
    drawString2(0.2, 0.4, 0, "100");
      glColor3f(1.0, 0.0, 0.0);
    drawString(-0.6, -0.1, 0, node1);
glPopMatrix();
//BOTTOM LEFT
  glPushMatrix();
    glTranslatef(-1.0,-1.0,-5.0);
    glRotatef(-60, 1.0, 0.0, 0.0);
    if(node2=="Source"||node2=="Destination")
          draw_cylinder(0.2, 0.1, 100, 100, 100);
else
  draw_cylinder(0.2, 0.1, 0, 255, 143);
 glColor3f(1.0, 1.0, 0.0);
     drawString(0.2, 0.1, 0, "Node 2");
           glColor3f(0.9, 1.0, 0.9);
         drawString2(-0.25, 0.3, 0, "10");
    drawString2(0.3, -0.1, 0, "50");

       glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.2, 0, node2);
glPopMatrix();
//BOTTOM RIGHT
  glPushMatrix();
    glTranslatef(1.0,-1.0,-5.0);
    glRotatef(-60, 1.0, 0.0, 0.0);
    if(node3=="Source"||node3=="Destination")
          draw_cylinder(0.2, 0.1, 100, 100, 100);
else
  draw_cylinder(0.2, 0.1, 0, 255, 143);
 glColor3f(1.0, 1.0, 0.0);
         drawString(0.2, 0.1, 0, "Node 3");
               glColor3f(0.9, 1.0, 0.9);
             drawString2(-0.3, -0.1, 0, "50");
    drawString2(0.3, 0.5, 0, "20");
    drawString2(-0.2, 0.4, 0, "10");
           glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node3);
glPopMatrix();
//TOP
glPushMatrix();
    glTranslatef(0.0,1.0,-5.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    if(node5=="Source"||node5=="Destination")
          draw_cylinder(0.2, 0.1, 100, 100, 100);
else
  draw_cylinder(0.2, 0.1, 0, 255, 143);
 glColor3f(1.0, 1.0, 0.0);
       drawString(0.2, 0.1, 0, "Node 5");
          glColor3f(0.9, 1.0, 0.9);
           drawString2(-0.4, -0.2, 0, "100");
    drawString2(0.3, -0.2, 0, "60");
               drawString2(0.0, -0.4, 0, "10");
         glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node5);
glPopMatrix();
//RIGHT
glPushMatrix();
    glTranslatef(2.0,0.0,-5.0);
    glRotatef(-40, 1.0, 0.0, 0.0);
    if(node4=="Source"||node4=="Destination")
          draw_cylinder(0.2, 0.1, 100, 100, 100);
else
  draw_cylinder(0.2, 0.1, 0, 255, 143);
 glColor3f(1.0, 1.0, 0.0);
     drawString(0.2, 0.1, 0, "Node 4");
        glColor3f(0.9, 1.0, 0.9);
         drawString2(-0.4, -0.1, 0, "30");
    drawString2(-0.2, -0.3, 0, "20");
    drawString2(-0.3, 0.3, 0, "60");
      glColor3f(1.0, 0.0, 0.0);
    drawString(0.2, -0.1, 0, node4);
glPopMatrix();
 glPushMatrix();
       glTranslatef(1.6,1.37,-5.0);
        glColor3f(0.8,0.3,1.0);
     drawString2(0.0, 0.0, 0, "Source");
     drawString2(0.43, 0.0, 0, "Destination");
     drawString3(0.0, -0.2, 0, table[0]);
     drawString3(0.5, -0.2, 0, table[1]);
     drawString3(0.0, -0.4, 0,  table[2]);
     drawString3(0.5, -0.4, 0,  table[3]);
     drawString3(0.0, -0.6, 0,  table[4]);
     drawString3(0.5, -0.6, 0,  table[5]);
     drawString3(0.0, -0.8, 0,  table[6]);
     drawString3(0.5, -0.8, 0,  table[7]);

    glPopMatrix();
if(startsim)
{
    glPushMatrix();
lines();
glPopMatrix();

}

    glFlush();
    }
    else if (dispflag==3){
  //  const int curTime = glutGet( GLUT_ELAPSED_TIME );
    // figure out how far along duration we are, between 0.0 and 1.0
   // const float t = std::cos(float(curTime) * 0.001) * 0.5 + 0.5;
    // interpolate between two colors
   // Color curColor = lerp(makeColor(0.0, 0.3, 0.5), makeColor(0.5, 0.3, 1.0), t);
    glClearColor(0.0, 0.3, 0.5, 1 );
    glClear( GL_COLOR_BUFFER_BIT );
      glLoadIdentity();
    glPushMatrix();
     glColor3f(1.0, 1.0, 1.0);
 glTranslatef(-1.2,1.4,-5.0);
     drawString1(1.0, 0.0, 0.0, "About");
     drawString1(-1.5, -0.3, 0.0, "Routing using Dijkstra's Algorithm");
      drawString(-1.5, -0.45, 0.0, "- It finds the shortest path from source to destination from a weighted directed graph");
       drawString(-1.5, -0.6, 0.0, "- At the first iteration, the algorithm finds the closest node from the source node which must be a neighbor of the source node.");
         drawString(-1.5, -0.75, 0.0, "- At the second iteration, the algorithm finds the second-closest node from the source node. This node must be a neighbor of either the");
     drawString(-1.5, -0.85, 0.0, "   source node or the closest node found in the first iteration.");
      drawString(-1.5, -1.0, 0.0, "- At the third iteration, the algorithm finds the third-closest node from the source node. This node must be a neighbor of either the source node");
       drawString(-1.5, -1.1, 0.0, "   or one of the first two closest nodes.");
        drawString(-1.5, -1.25, 0.0, "- The process continues. At the kth iteration, the algorithm finds the first k closest nodes from the source node.");
         drawString1(-1.5, -1.8, 0.0, "Switching");
           drawString(-1.5, -1.95, 0.0, "- The switch forwards a packet from source node to destination node based on the MAC address of destination node.");
           drawString(-1.5, -2.1, 0.0, "- The switch maintains a switching table that maps the MAC address of each node to the port at which it is connected.");
                  drawString(-1.5, -2.25, 0.0, "- When a packet arrives at the switch, it checks the MAC address of destination node specified in the packet, looks up the address");
                  drawString(-1.5, -2.35, 0.0, "   in the switching table and sends the packet to the port it is mapped to.");
            glPopMatrix();
      glFlush();

    }

}

void reshape(int width, int height)
{
    if (width == 0 || height == 0) return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)width/(GLdouble)height,
                   0.5, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
}

void mouse(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN&&selectFlag<2)
    {

        if(x>220&&y>320&&y<400&&x<320){
            if(selectFlag==0){
                node1="Source";
                selectFlag=1;
                startnode=1;
                startx=-2.0;
                starty=0.0;
            }
            else{
                node1="Destination";
                endnode=1;
                selectFlag=2;
                endx=-2.0;
                endy=0.0;
            }

        }
        else if(x>1050&&y>320&&y<400&&x<1150){
            if(selectFlag==0){
                node4="Source";
                startnode=4;
                selectFlag=1;
                startx=2.0;
                starty=0.0;
            }
            else{
                node4="Destination";
                selectFlag=2;
                endnode=4;
                endx=2.0;
                endy=0.0;
            }
        }
        else if(x>625&&y>120&&y<200&&x<725){
            if(selectFlag==0){
                node5="Source";
                startnode=5;
                selectFlag=1;
                startx=0.0;
                starty=1.0;
            }
            else{
                node5="Destination";
                selectFlag=2;
                endnode=5;
                endx=0.0;
                endy=1.0;
            }
        }
        else if(x>420&&y>520&&y<620&&x<520){
            if(selectFlag==0){
                node2="Source";
                startnode=2;
                selectFlag=1;
                startx=-1.0;
                starty=-1.0;
            }
            else{
                node2="Destination";
                selectFlag=2;
                endnode=2;
                endx=-1.0;
                endy=-1.0;
            }
        }
        else if(x>840&&y>520&&y<620&&x<940){
            if(selectFlag==0){
                node3="Source";
                startnode=3;
                selectFlag=1;
                startx=1.0;
                starty=-1.0;
            }
            else{
                node3="Destination";
                selectFlag=2;
                endnode=3;
                endx=1.0;
                endy=-1.0;
            }
        }

        glFlush();
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
if(dispflag==0)
{
    switch(key){
        case '1':dispflag=1;
            display();
            break;
        case '2':dispflag=2;
            display();
            break;
    case '3':dispflag=3;
            display();
            break;
        case '4':exit(0);
        break;
    }

}
if(dispflag==2)
{
 if(key=='0'){
      dispflag=0;
      selectFlag=0;
        node1="";
        node2="";
        node3="";
        node4="";
        node5="";
        startx=0.0;
        endx=0.0;
        starty=0.0;
        endy=0.0;
        linex=0.0;
        liney=0.0;
        incx=0.0;
        incy=0.0;
        startsim=0;
        endflag=0;
        doz=0;
        taby=0.0;
     display();
 }

  if(key=='R'||key=='r')
    {
        selectFlag=0;
        node1="";
        node2="";
        node3="";
        node4="";
        node5="";
        startx=0.0;
        endx=0.0;
        starty=0.0;
        endy=0.0;
        linex=0.0;
        liney=0.0;
        incx=0.0;
        incy=0.0;
        startsim=0;
        endflag=0;
        doz=0;
        taby=0.0;
    }
    glFlush();
    glutPostRedisplay();
    if(selectFlag==2&&(key=='S'||key=='s'))
    {
          incx=(switchx-startx)/10;
            incy=(switchy-starty)/10;
        linex=startx;
        liney=starty;
           startsim=1;
           glutTimerFunc(100,linesw,0);
    }
}
else if(dispflag==1)
{
    if(key=='0'){
      dispflag=0;
       selectFlag=0;
        node1="";
        node2="";
        node3="";
        node4="";
        node5="";
      startx=0.0;
      endx=0.0;
      starty=0.0;
      endy=0.0;
      linex=0.0;
      liney=0.0;
      incx=0.0;
      incy=0.0;
      startsim=0;
      endflag=0;
      tabi=0;
    for(k=0;k<8;k++)
    {
        strcpy(table[k],"");
        finalpath[k]=0;
    }
    sx=-5.0;
    sy=-5.0;
    ex=-5.0;
    ey=-5.0;
     display();
 }
    if(key=='R'||key=='r')
    {
        selectFlag=0;
        node1="";
        node2="";
        node3="";
        node4="";
        node5="";
      startx=0.0;
      endx=0.0;
      starty=0.0;
      endy=0.0;
      linex=0.0;
      liney=0.0;
      incx=0.0;
      incy=0.0;
      startsim=0;
      endflag=0;
      tabi=0;
    for(k=0;k<8;k++)
    {
        strcpy(table[k],"");
        finalpath[k]=0;
    }
    sx=-5.0;
    sy=-5.0;
    ex=-5.0;
    ey=-5.0;

    }
      glFlush();
    glutPostRedisplay();
    if(selectFlag==2&&(key=='S'||key=='s'))
    {
             dijkstra(DIST,5,startnode-1,endnode-1);
        drawindex++;
        pathlength=MAX-drawindex;
        pathiteration=1;
         endflag=0;
        nodeval=drawpath[drawindex++];
           startx=points[nodeval][0];
           starty=points[nodeval][1];

  itoa(nodeval+1,  noden, 10);
        dest=strcat(node,noden);
        strcpy(fin,dest);
       for(k=0;k<=5;k++)
        table[tabi][k]=fin[k];
        strcpy(node,"Node ");
        tabi++;
           nodeval=drawpath[drawindex];
           endx=points[nodeval][0];
           endy=points[nodeval][1];

           incx=(endx-startx)/10;
            incy=(endy-starty)/10;
        linex=startx;
        liney=starty;
           startsim=1;
        itoa(nodeval+1,  noden, 10);
        dst=strcat(node,noden);
        strcpy(fin,dst);
         strcpy(node,"Node ");
       for(k=0;k<=5;k++)
        table[tabi][k]=fin[k];
       tabi++;
             glutTimerFunc(100,lines,0);

    }
}
else if(dispflag==3){
    if(key=='0'){
      dispflag=0;
      display();
    }
}

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1366,768);
    glutInitWindowPosition(0,0);
       glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Routing and Switching");
    glClearColor(0.0,0.0,0.0,0.0);
     gluOrtho2D(0.0,1366.0,0.0,768.0);
 glutDisplayFunc(display);
glutMouseFunc(mouse);
 glutReshapeFunc(reshape);
 // glEnable(GL_DEPTH_TEST);
glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
