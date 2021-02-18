#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<time.h>


#define TOTALCOINS 15        // total number of coins to be placed in 3 tracks

int *arr;                  // 2d array consisting of 3 tracks(rows)
int *RandArr;  
int n;           // array of size 15 containing randomly generated numbers 
int car_pos[2][TOTALCOINS];
struct node{             // node of a link list  
	int no;          // vaiable having s.no 1,2,3....(upto total cells of array -1) for each node
	int* arrLink;        // link to the 2d array cell
	struct node* link;       //link to the next node
};                      

struct node *p=NULL;    // p points to first node of the link list
int Sno=0;              // integer variable(initialized to 0) used for assigning S.no to each node 



void init()
{
	glClearColor(0.101, 1.0, 0.980, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-10, 100, -30, 70);
}



void addNode(int i, int j,int n)   // function used to add node at the end of link list kathir
{
	if(p==NULL)
	{
		struct node *temp;
		temp=(struct node*)malloc(sizeof(struct node));
		temp->no=Sno;
		Sno++;
		temp->arrLink=(arr+n*i+j);
		temp->link=NULL;
		p=temp;
	}
	
	else
	{
		struct node *r;
		r=p;
		while(r->link!=NULL)
		r=r->link;
		struct node *temp;
		temp=(struct node*)malloc(sizeof(struct node));
		temp->no=Sno;
		Sno++;
		temp->arrLink=(arr+n*i+j);
		temp->link=NULL;
		r->link=temp;
	}
	
}

void prinLinLst()      // temporary function to print link list 
{
	printf("LinkList: ");
	struct node *q;
	q=p;
	while(q->link!=NULL)
	{
		printf("%d ",q->no);
		q=q->link;
		if(q->link==NULL)
		printf("%d ",q->no);
	}
	printf("\n\n\n");
}

void genRand(int n)          // function used to generate random numbers  
{
	srand(time(0));
	RandArr=(int*)malloc(TOTALCOINS*sizeof(int));
	int num;
	for(int i=0;i<TOTALCOINS;i++)
	{
		num=rand();
		num=num%(3*n-1);        //
		RandArr[i]=num;
	}
}

void PrintRandArr()          //temporary function to print random numbers generated 
{
	printf("RandArr=");
	for(int i=0;i<TOTALCOINS;i++)
	{
		printf("%d ",RandArr[i]);
	}
	printf("\n\n");
}


void draw(int x,int y)      
{
   glBegin(GL_LINE_STRIP);
   glColor3f(1.0,0,0 );
   glVertex2f(x,y);
   glVertex2f(x+5,y);
   glVertex2f(x+5,y+5);
   glVertex2f(x,y+5);
   glVertex2f(x,y);
   glEnd();
   
   
}

void fun2()      // calling draw2 fuction to draw car
{
   static int y=0;
   
   draw2(car_pos[0][y],car_pos[1][y]);
   y++;
}




void prinTrack(int n)     // function to print track     
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<n;j++)
		{        
			printf("%d  ",*(arr+n*i+j));
                        
		}
		printf("\n");
	}
	printf("\n\n");
	
}

void display()                //ankur
{
   
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(1000, 750);
   glutCreateWindow("Minor Project");
   init();
   glClear(GL_COLOR_BUFFER_BIT);
   
 
}   

void prinTrac(int n,int x, int y ,int t)     // function to print track      
{
	int i,j;
	if(t==0)
	display();
	char d[1]={'3'};
	if(t==0)
	{
	glColor3f(1,0,0);
	glRasterPos2f((x),(y+10));
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,"After placing coins on the tracks-:");
	}
	
	if(t==1)
	{
	glColor3f(1,0,0);
	glRasterPos2f((x),(y+10));
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,"Position of the car(c) on track-:");
	}
	for(i=0;i<3;i++)
	{
	         x=0;
	         if(i!=0)
	         y=y-5;
		for(j=0;j<n;j++)
		{        draw(x,y);
		         glColor3f(0,0,0);
		         glRasterPos2f((x+2.5),(y+2.5));
		         if(*(arr+n*i+j)==1||*(arr+n*i+j)==9)
		         d[0]='o';
		         else if(*(arr+n*i+j)==0)
		         d[0]=' ';
		         glutBitmapString(GLUT_BITMAP_HELVETICA_18,d);
			printf("%d  ",*(arr+n*i+j));
                         x=x+5;
		}
		printf("\n");
	}
	glFlush();
        //glutMainLoop ();
	printf("\n\n");
	
}

void placeCoins()          // places coins on the track  
{
	int i;
	int plCoins=0;
	struct node *q=p;
	for(i=0;i<TOTALCOINS;i++)
	{
		q=p;
		while(q->link!=NULL)
		{
	        if(q->no==RandArr[i])
	        {
	        	if(*(q->arrLink)==0)
	        	plCoins++;
	        *(q->arrLink)=1;
	        }
	        q=q->link;
            if(q->link==NULL&&q->no==RandArr[i])
            {
            	if(*(q->arrLink)==0)
	        	plCoins++;
						
			*(q->arrLink)=1;
		    }
			
		}
	
	}
	printf("Coins placed on track= %d\n",plCoins);
}

void draw2(int p,int q)        
{
    p=p+2;
    q=q+2;
    glBegin(GL_POLYGON);
    glColor3f(1.0,0,0 );
    glVertex2f(p,q);
    glVertex2f(p+2,q);
    glVertex2f(p+2,q+2);
    glVertex2f(p,q+2);
    glEnd();
    glFlush();
}

void searchCoins(int n)      // decide the coins to be collected by the car
{
	int coinColl=0;    
	int i,j;     // i for columns        j for for row 
	int *prev=NULL;
	int flag=0;    // for 1st coin collection
	int flag2=0;   //  for prev<current
	for(int j=0;j<n;j++)
	{
		for(int i=0;i<3;i++)   
		{
			if((arr+n*i+j)>prev)
			flag2=1;    // flag2 is 1 if crrent adress is greater
			else if((arr+n*i+j)<prev)
			flag2=0;   // flag2 is 0 if prev is greater
			
			if(*(arr+n*1+j)==1)    // if 2nd row has coin it will be collected
			{
				coinColl=coinColl+*(arr+n*1+j);
				*(arr+n*1+j)=9;
                prev=arr+n*1+j;
                i=3;
                flag=1;
			}
			
			else if(*(arr+n*i+j)!=0&&abs((arr+n*i+j)-prev)!=(2*n+1)&&flag2==1||*(arr+n*i+j)!=0&&abs((arr+n*i+j)-prev)!=(2*n-1)&&flag2==0||*(arr+n*i+j)!=0&&flag==0)
			{          // collecting coins and avoiding jumping condition
				coinColl=coinColl+*(arr+n*i+j);      
				*(arr+n*i+j)=9;
				prev=arr+n*i+j;
				i=3;
				flag=1;
			}
		}
	}
	printf("Coins COLLECTED= %d\n",coinColl);

}



void fun1()        //function to assign values to car_pos          
{
           int i=0;
           int p=0;      // x coordinate to plot car
           int Y=0;     // columns of car_pos
           
           glColor3f(0,0,1);     
           for(i=0;i<n;i++)
           {
           int q=0;     // y coordinate to plot car
           for(int j=0;j<3;j++)
           {
                
                
                if(*(arr+j*n+i)==9)
                {
                     //glRasterPos2f(p+0.25,q+0.25);
                     
                     //glutBitmapString(GLUT_BITMAP_HELVETICA_18,"c");
                     car_pos[0][Y]=p;     // providing x coordinate
                     car_pos[1][Y]=q;     // providing y coordinate
                     Y++;
                     
                     j=3;
                   
                    
                }
                q=q-5;    // to move to next row in a column
           }
           p=p+5;        // to move to next column
           }
           
           
           
     
}











int main(int argc, char** argv)
{
        glutInit(&argc, argv);
	int i,j;
	printf("Enter the size of a track ");
	scanf("%d",&n);
	arr=(int*)malloc(3*n*sizeof(int));
	for(i=0;i<3;i++)
	{
		for(j=0;j<n;j++)
		{
			addNode(i,j,n);      // adds a node for each cell of the 2d array
			*(arr+n*i+j)=0;
		}
	}
	prinLinLst();
	genRand(n);
	PrintRandArr();
	prinTrack(n);
	placeCoins();
	glutDisplayFunc(display);
	prinTrac(n,0,50,0);
	searchCoins(n);
	fun1();        // gives coordinates to car_pos
        prinTrac(n,0,0,1);
        while(1)
        {
             printf("\n press 1 to move car forward ");
             int ch=0;
             int val;
             scanf("%d",&val);
             switch(val)
             {
                case 1: fun2();  // calls draw2 to plot car
                          break;
                default: ch=1;
                        break;        
             }
             if(ch==1)
             break;
        }
	
	
	
	printf("\n");
	
	glutMainLoop();
}
