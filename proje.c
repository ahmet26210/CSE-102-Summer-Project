
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define pi 3.141592
typedef struct label{
	double x;
	double y;
	char text[30];
}label;
typedef struct point2D{
	double x;
	double y;
	label *label;
	struct point2D *nextp;
}point2D;
typedef struct Color
{	
	int red;
	int blue;
	int green;
}Color;
typedef struct text2D{
	double x,y;
	char write;
	label *label;
	struct text2D *nextt;
}text2D;
typedef struct CAD2D{
	point2D *point;
	double llx,lly,urx,ury;
	double resolution;
	double thickness;
	text2D *text;
	Color color;
	point2D *center;
	struct CAD2D *nextcad;
}CAD2D;
typedef struct hierarchy{
	struct CAD2D *cadlist;
	struct hierarchy *left;
	struct hierarchy *right;
}hierarchy;
CAD2D * c2d_startd();
CAD2D * c2d_startd1(double width,double height);
CAD2D * c2d_startdh(double width,double height,hierarchy *h);
void set_thickness_resolution(CAD2D *cad,double thickness,double resolution);
void set_color(CAD2D *cad,Color c);
hierarchy *c2d_create_hierarchystart(CAD2D *cad);
hierarchy *c2d_create_hierarchy_add_parent(CAD2D *cad,hierarchy *parent);
label* c2d_add_pointxy(CAD2D *cad,double x,double y);
label* c2d_add_pointp(CAD2D *cad,point2D *p);
label* c2d_add_pointph(CAD2D *cad,point2D *p, hierarchy *h);
label* c2d_add_pointphlabel(CAD2D *cad,point2D *p, hierarchy *h,const label *l);
label* c2d_add_poly_line_linkedlist(CAD2D *cad,point2D *poly_line,int n);
label* c2d_add_poly_line_array(CAD2D *cad,double poly_line[][2],int n);
label* c2d_add_poly_line_linkedlisth(CAD2D *cad,point2D *poly_line,int n, hierarchy *h);
label* c2d_add_poly_line_linkedlisthl(CAD2D *cad,point2D *poly_line,int n,hierarchy *h,const label *l);
label* c2d_add_text(CAD2D *cad,text2D *poly_text,int n);
label* c2d_add_text_array(CAD2D *cad,double poly_text[][2],int n);
label* c2d_add_text_linkedlisth(CAD2D *cad,text2D *poly_text,int n,hierarchy *h);
label* c2d_add_text_linkedlisthl(CAD2D *cad,text2D *poly_text,int n,hierarchy *h,const label *l);
label* c2d_add_polygon(CAD2D *cad,point2D *poly_line,int n);
label* c2d_add_polygon_array(CAD2D *cad,double poly_line[][2],int n);
label* c2d_add_polygon_linkedlisth(CAD2D *cad,point2D *poly_line,int n, hierarchy *h);
label* c2d_add_polygone_linkedlisthl(CAD2D *cad,point2D *poly_line,int n,hierarchy *h,const label *l);
label* c2d_add_ellipse(CAD2D *cad,point2D *center,double a,double b);
label* c2d_add_ellipse1(CAD2D *cad,double centerx,double centery,point2D *lengths);
label* c2d_add_ellipse_h(CAD2D *cad,point2D *center,double a,double b, hierarchy *h);
label* c2d_add_ellipse_h_label(CAD2D *cad,point2D *center,double a,double b, hierarchy *h,const label *l);
label* c2d_add_circle(CAD2D *cad,point2D *center,double r);
label* c2d_add_circle1(CAD2D *cad,double centerx,double centery,double r);
label* c2d_add_circle_h(CAD2D *cad,point2D *center,double r,hierarchy *h);
label* c2d_add_circle_h_label(CAD2D *cad,point2D *center,double r,hierarchy *h,label *l);
label* c2d_add_arc(CAD2D *cad,point2D *center,double degree1,double degree2,int choice,double r);
label* c2d_add_arc_h(CAD2D *cad,point2D *center,double degree1,double degree2,int choice,double r,hierarchy *h);
label* c2d_add_arc_h_label(CAD2D *cad,point2D *center,double degree1,double degree2,int choice,double r,hierarchy *h,label *l);
point2D* find_polygon_center(point2D *tempp);
void c2d_snap(CAD2D *cad,const label *ls,const label *lt);
double c2d_measure(CAD2D *cad,const label *ls,const label *lt);
point2D* draw_fx(CAD2D *cad,double f(double x),double start_x,double end_x,char choice);
void c2d_export(CAD2D *cad,char *file_name);

int main(){
	hierarchy *h1;
	int n=4;
	char *file_name="new.eps";
	Color c;
	c.red=1;
	point2D *p,*p1,*center,*lengths;
	p=(point2D*)malloc(sizeof(point2D));
	p1=(point2D*)malloc(sizeof(point2D));
	center=(point2D*)malloc(sizeof(point2D));
	lengths=(point2D*)malloc(sizeof(point2D));
	point2D poly_line2[5]={{10,10},{10,20},{20,20},{20,10}};
	double poly_line[5][2]={{10,10},{10,20},{20,20},{20,10}};
	point2D poly_line1[3]={{5,10},{6,20},{30,15}};
	double poly_line3[3][2]={{5,10},{6,20},{30,15}};
	double width=500,height=500;
	p->x=11.0;
	p->y=11.0;
	p1->x=15.0;
	p1->y=15.0;
	center->x=10.0;
	center->y=10.0;
	lengths->x=10.0;
	lengths->y=5.0;
	double r=20.0;
	double centerx=10.0;
	double centery=10.0;
	double x=10.0,y=10.0;
	double a=10,b=5;
	double degree1=190,degree2=100;
	double distance=0.0;
	int choice=TRUE;
	label *l1,*l2,*l3,*l4,*l5,*l6,*l7,*l8,*l9,*l10,*l11,*l12,*l13,*l14,*l15,*l16,*l17,*l18,*l19,*l20,*l21,*l22,*l23;
	CAD2D *cad,*cad1,*cad2,*cad3,*cad4,*cad5,*cad6,*cad7,*cad8,*cad9,*cad10;
	cad=c2d_startd1(width,height);
	text2D poly_text[2]={{'a'},{'b'}};
	//cad1=c2d_startd1(width,height);
	//cad2=c2d_startdh(width,height,h1);
	set_thickness_resolution(cad,1,1);
	set_color(cad,c);
	h1=c2d_create_hierarchystart(cad);
	//l1=c2d_add_pointxy(cad,x,y);
	//l2=c2d_add_pointp(cad,p);
	//l3=c2d_add_pointph(cad,p,h1);
	//l4=c2d_add_pointphlabel(cad,p1,h1,l1);
	//l5=c2d_add_poly_line_linkedlist(cad,poly_line1,n);
	//l6=c2d_add_poly_line_array(cad,poly_line3,n);
	//l7=c2d_add_poly_line_linkedlisth(cad,poly_line1,n,h1);
	//l8=c2d_add_poly_line_linkedlisthl(cad,poly_line1,n,h1,l1);
	//l9=c2d_add_polygon(cad,poly_line2,n);
	//l10=c2d_add_polygon_array(cad,poly_line,n);
	//l11=c2d_add_polygon_linkedlisth(cad,poly_line2,n,h1);
	//l12=c2d_add_polygone_linkedlisthl(cad,poly_line2,n,h1,l1);
	//l13=c2d_add_ellipse(cad,center,a,b);
	//l14=c2d_add_ellipse1(cad,centerx,centery,lengths);
	//l15=c2d_add_ellipse_h(cad,center,a,b,h1);
	//l16=c2d_add_ellipse_h_label(cad,center,a,b,h1,l1);
	l17=c2d_add_circle(cad,center,r);
	//l18=c2d_add_circle1(cad,centerx,centery,r);
	//l19=c2d_add_circle_h(cad,center,r,h1);
	//l20=c2d_add_circle_h_label(cad,center,r,h1,l1);
	//l21=c2d_add_arc(cad,center,degree1,degree2,choice,r);
	//l22=c2d_add_text(cad,poly_text,n);
	//l22=c2d_add_arc_h(cad,center,degree1,degree2,choice,r,h1);
	//l23=c2d_add_arc_h_label(cad,center,degree1,degree2,choice,r,h1,l1);
	//c2d_snap(cad,l1,l9);
	//distance=c2d_measure(cad,l5,l9);
	//printf("DİSTANCE: %lf\n",distance);
	c2d_export(cad,file_name);
}
CAD2D * c2d_startd(){//to start cad and send the created hierarchy
	CAD2D *cd;
	cd=(CAD2D*)malloc(sizeof(CAD2D));
	cd->point=NULL;
	return cd;
}
CAD2D * c2d_startd1(double width,double height){//to start cad and send the created hierarchy and determine corner points
	CAD2D *cd;
	cd=(CAD2D*)malloc(sizeof(CAD2D));
	cd->urx=width/2.0;
	cd->ury=height/2.0;
	cd->llx=-width/2.0;
	cd->lly=-height/2.0;
	return cd;
}
CAD2D * c2d_startdh(double width,double height,hierarchy *h){//to start cad and send the given hierarchy and determine corner points 
	CAD2D *cd;
	cd=(CAD2D*)malloc(sizeof(CAD2D));
	cd->urx=width/2.0;
	cd->ury=height/2.0;
	cd->llx=-width/2.0;
	cd->lly=-height/2.0;
	c2d_create_hierarchy_add_parent(cd,h);
	return cd;
}	
void set_thickness_resolution(CAD2D *cad,double thickness,double resolution){//thickness resolution 
	cad->thickness=thickness;
	cad->resolution=resolution;
}
void set_color(CAD2D *cad,Color c){//color rgb
	cad->color.red=c.red;
	cad->color.blue=c.blue;
	cad->color.green=c.green;
}
hierarchy *c2d_create_hierarchystart(CAD2D *cad){//first create hierarchy and send the cad to the top of the hierarchy
	hierarchy *root;
	root=(hierarchy*)malloc(sizeof(hierarchy));
	root->cadlist=(CAD2D*)malloc(sizeof(CAD2D));
	root->cadlist=cad;
	root->right=NULL;
	root->left=NULL;
	return root;
}
hierarchy *c2d_create_hierarchy_add_parent(CAD2D *cad,hierarchy *parent){
	/*to be able to add the cad to the given parent head or child*/
	if(parent->right==NULL && parent->left==NULL){
		parent->left=(hierarchy*)malloc(sizeof(hierarchy));
		parent->left->cadlist=(CAD2D*)malloc(sizeof(CAD2D));
		parent->left->cadlist=cad;
		parent->left->right=NULL;
		parent->left->left=NULL;
	}
	else if(parent->right!=NULL||parent->left!=NULL){
		hierarchy *temph;
		temph=parent;
		temph=temph->left;
		while(temph->right!=NULL){
			temph=temph->right;
		}
		temph->right=(hierarchy*)malloc(sizeof(hierarchy));
		temph->right->cadlist=(CAD2D*)malloc(sizeof(CAD2D));
		temph->right->cadlist=cad;
		temph->right->left=NULL;
		temph->right->right=NULL;
	}
}
void insert_point(point2D *headp,double x,double y,char charchoice){
	//add the newp end of the list
	point2D *tempp,*newp;
	tempp=headp;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	newp=(point2D*)malloc(sizeof(point2D));
	newp->label=(label*)malloc(sizeof(label));
	newp->x=x;
	newp->y=y;
	newp->nextp=NULL;
	newp->label->x=newp->x;
	newp->label->y=newp->y;
	if(charchoice=='G'){
		strcpy(newp->label->text,"polygon");
		
	}
	else if(charchoice=='P'){
		strcpy(newp->label->text,"polyline");
	}
	else if(charchoice=='E'){
		strcpy(newp->label->text,"ellipse");
	}
	else if(charchoice=='C'){
		strcpy(newp->label->text,"circle");
	}
	else if(charchoice=='A'){
		strcpy(newp->label->text,"arc");
	}
	tempp->nextp=newp;//add newp to the end of the headp
}
void insert_text(text2D *text,char write,double x,double y){
	//insert char by one by to create text
	text2D *tempt;
	text2D *newt=(text2D*)malloc(sizeof(text2D));
	newt->label=(label*)malloc(sizeof(label));
	newt->write=write;
	newt->x=x;
	newt->y=y;
	newt->nextt=NULL;
	newt->label->x=x;
	newt->label->y=y;
	strcpy(newt->label->text,"text");
	tempt=text;
	while(tempt->nextt!=NULL){
		tempt=tempt->nextt;
	}
	tempt->nextt=newt;//add new charto the end of the head char
}
void insert_cad(CAD2D *headcad,CAD2D *newcad){
	//to make a cad linkedlist 
	CAD2D *tempcad;
	tempcad=headcad;
	char text1[30];
	strcpy(text1,newcad->point->label->text);
	while(tempcad->nextcad!=NULL){
		tempcad=tempcad->nextcad;	
	}
	newcad->nextcad=NULL;
	tempcad->nextcad=newcad;
	strcpy(newcad->point->label->text,text1);
}
label* c2d_add_pointxy(CAD2D *cad,double x,double y){
	//this function add point to the given cad
	point2D *newp;
	CAD2D *tempcad;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	tempcad=cad;
	newp=(point2D*)malloc(sizeof(point2D));
	newp->label=(label*)malloc(sizeof(label));
	newp->x=x;
	newp->y=y;
	newp->nextp=NULL;
	newp->label->x=x;
	newp->label->y=y;	
	strcpy(newp->label->text,"point");
	if(cad->point==NULL){//if first cad point is null we add the point first cad point
		cad->point=newp;
		return cad->point->label;
	}
	else if(cad->point!=NULL){//if first cad point is not null we add the point to the end of the cad point 	
		newcad->point=newp;
		insert_cad(cad,newcad);//reach the end of the cadlist and add the newcad to the cadlist
		return newcad->point->label;
	}
}
label* c2d_add_pointp(CAD2D *cad,point2D *p){
	//this function add point to the given cad
	point2D *newp;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	newp=(point2D*)malloc(sizeof(point2D));
	newp->label=(label*)malloc(sizeof(label));
	newp=p;
	newp->label->x=p->x;
	newp->label->y=p->y;
	strcpy(newp->label->text,"point");
	newp->nextp=NULL;
	if(cad->point==NULL){
		cad->point=newp;
		return cad->point->label;
	}
	else if(cad->point!=NULL){	
		newcad->point=newp;
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_pointph(CAD2D *cad,point2D *p,hierarchy *h){
	//this function add point to the given cad and add cad to the given hierarchy
	point2D *newp;
	CAD2D *tempcad;
	int control=0,control1=0;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	tempcad=cad;
	newp=(point2D*)malloc(sizeof(point2D));
	newp->label=(label*)malloc(sizeof(label));
	newp->x=p->x;
	newp->y=p->y;
	newp->label->x=p->x;
	newp->label->y=p->y;
	strcpy(newp->label->text,"point");
	newp->nextp=NULL;
	if(cad->point==NULL){
		cad->point=newp;
		control=1;
	}
	else if(cad->point!=NULL){
		newcad->point=newp;
		insert_cad(cad,newcad);
		control1=0;
	}
	c2d_create_hierarchy_add_parent(cad,h);
	if(control==1) return cad->point->label;
	else if(control1==1) return newcad->point->label;
}
label* c2d_add_pointphlabel(CAD2D *cad,point2D *p,hierarchy *h,const label *l){
	//this function add point to the given cad and add the cad to the given hierarchy before this things function check the given label is there in given cadlinkedlist if cadlist->point->x and y is the same with the given label this function dont add the given point to the cad and hierarchy.
	point2D *tempp;
	CAD2D *tempc;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point2D *newp=(point2D*)malloc(sizeof(point2D));
	tempc=cad;
	int control=0,control1=0,control2=0;
	newp->label=(label*)malloc(sizeof(label));
	newp->x=p->x;
	newp->y=p->y;
	newp->label->x=p->x;
	newp->label->y=p->y;
	strcpy(newp->label->text,"point");
	newp->nextp=NULL;
	if(cad->point==NULL){
		cad->point=newp;
		control1=1;
		control=1;
	}
	else if(cad->point!=NULL){
		tempp=cad->point;	
		while(tempc->nextcad!=NULL){
			while(tempp->nextp!=NULL){
				if(tempp->x==l->x && tempp->y==l->y){
					control=1;
				}
				tempp=tempp->nextp;
			}
			tempc=tempc->nextcad;
		}
		control2=1;
	}
	if(control==0){
		newcad->point=newp;
		tempc->nextcad=newcad;
		c2d_create_hierarchy_add_parent(cad,h);
	}
	else{
		printf("there is a point has same label you send becasuf of this we cant add any point to cad");
	}
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_text(CAD2D *cad,text2D *poly_text,int n){
	//this function add the text to the given cad,this text occur linkedlist text
	int sayac=0,i=0,j=0;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	text2D *text=(text2D*)malloc(sizeof(text2D));
	text->label=(label*)malloc(sizeof(label));
	text->x=poly_text[i].x;
	text->y=poly_text[i].y;
	text->write=poly_text[i].write;
	for(i=1;i<=n;i++){
		insert_text(text,poly_text[i].write,poly_text[i].x,poly_text[i].y);
	}
	text->label->x=text->x;
	text->label->y=text->y;
	strcpy(text->label->text,"text");
	if(cad->text==NULL){
		cad->text=text;
		return cad->text->label;
	}
	else if(cad->text!=NULL){	
		newcad->text=text;
		insert_cad(cad,newcad);
		return newcad->text->label;
	}
}
label* c2d_add_text_array(CAD2D *cad,double poly_text[][2],int n){
	//this function add the text to the given cad,this text occur arrey text
	int sayac=0,i=0,j=0;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	text2D *newtext=(text2D*)malloc(sizeof(text2D));
	newtext->label=(label*)malloc(sizeof(label));
	newtext->x=poly_text[0][0];
	newtext->y=poly_text[0][1];
	newtext->write=poly_text[0][2];
	for(i=1;i<=n;i++){
		insert_text(newtext,poly_text[i][2],poly_text[i][0],poly_text[i][1]);
	}
	newtext->label->x=poly_text[0][0];
	newtext->label->y=poly_text[0][1];
	strcpy(newtext->label->text,"text");
	if(cad->text==NULL){
		cad->text=newtext;
		return cad->text->label;
	}
	else if(cad->text!=NULL){	
		newcad->text=newtext;
		insert_cad(cad,newcad);
		return newcad->text->label;
	}
}
label* c2d_add_text_linkedlisth(CAD2D *cad,text2D *poly_text,int n,hierarchy *h){
	//this function add the text to the given cad,this text occur linkedlist text and add the cad to the given hierarchy
	int sayac=0,i=0,j=0;
	int control1=0,control2=0;
	text2D *text=(text2D*)malloc(sizeof(text2D));
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	text->label=(label*)malloc(sizeof(label));
	text->x=poly_text[i].x;
	text->y=poly_text[i].y;
	text->write=poly_text[i].write;
	for(i=1;i<=n;i++){
		insert_text(text,poly_text[i].write,poly_text[i].x,poly_text[i].y);
	}
	text->label->x=text->x;
	text->label->y=text->y;
	strcpy(text->label->text,"text");
	if(cad->text==NULL){
		cad->text=text;
		control1=1;
	}
	else if(cad->text!=NULL){	
		newcad->text=text;
		insert_cad(cad,newcad);
		control2=1;
	}
	c2d_create_hierarchy_add_parent(cad,h);
	if(control1==1) return cad->text->label;
	else if(control2==1) return newcad->text->label;
}
label* c2d_add_text_linkedlisthl(CAD2D *cad,text2D *poly_text,int n,hierarchy *h,const label *l){
	//this function add text to the given cad and add the cad to the given hierarchy before this things function check the given label is there in given cadlinkedlist if cadlist->text->x and y is the same with the given label this function dont add the given text to the cad and hierarchy.
	int sayac=0,i=0,j=0;
	int control=0,control1=0,control2=0;
	text2D *text=(text2D*)malloc(sizeof(text2D));
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	text->label=(label*)malloc(sizeof(label));
	text->x=poly_text[i].x;
	text->y=poly_text[i].y;
	text->write=poly_text[i].write;
	text2D *tempt;
	CAD2D *tempc;
	tempc=cad;
	for(i=1;i<=n;i++){
		insert_text(text,poly_text[i].write,poly_text[i].x,poly_text[i].y);
	}
	text->label->x=text->x;
	text->label->y=text->y;
	strcpy(text->label->text,"text");
	if(cad->text==NULL){
		cad->text=text;
		control1=1;
		control=1;
	}
	else if(cad->text!=NULL){
		tempt=cad->text;	
		while(tempc->nextcad!=NULL){
			while(tempt->nextt!=NULL){
				if(tempt->x==l->x && tempt->y==l->y){
					control=1;
				}
				tempt=tempt->nextt;
			}
			tempc=tempc->nextcad;
		}
		control2=1;
	}
	if(control==0){
		newcad->text=text;
		tempc->nextcad=newcad;
		c2d_create_hierarchy_add_parent(cad,h);
	}
	else{
		printf("there is a point has same label you send becasue of this we cant add any point to cad");
	}	
	if(control1==1) return cad->text->label;
	else if(control2==1) return newcad->text->label;
}
label* c2d_add_poly_line_linkedlist(CAD2D *cad,point2D *poly_line,int n){
	//this function add points to the given cad,this points occur linkedlist point to create poly_line.
	int sayac=0,i=0,j=0;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point2D *point=(point2D*)malloc(sizeof(point2D));
	point->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	point->x=poly_line[i].x;
	point->y=poly_line[i].y;
	for(i=1;i<n;i++){
		insert_point(point,poly_line[i].x,poly_line[i].y,'P');
	}
	point->label->x=point->x;
	point->label->y=point->y;
	strcpy(point->label->text,"polyline");
	if(cad->point==NULL){
		cad->point=point;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=point;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_poly_line_array(CAD2D *cad,double poly_line[][2],int n){
	//this function add points to the given cad,this points occur array point to create poly_line.
	point2D *point=(point2D*)malloc(sizeof(point2D));
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	cad->center=NULL;
	int sayac=0,i=0,j=0;
	point->x=poly_line[0][0];
	point->y=poly_line[0][1];
	for(i=1;i<n;i++){
		insert_point(point,poly_line[i][0],poly_line[i][1],'P');
	}
	point->label->x=poly_line[0][0];
	point->label->y=poly_line[0][1];
	strcpy(point->label->text,"polyline");
	if(cad->point==NULL){
		cad->point=point;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=point;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_poly_line_linkedlisth(CAD2D *cad,point2D *poly_line,int n, hierarchy *h){
	//this function add points to the given cad,this points occur linkedlist point to create poly_line and created cad will add to the given hierarchy.
	int sayac=0,i=0,j=0;
	int control1=0,control2=0;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point2D *point=(point2D*)malloc(sizeof(point2D));
	point->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	cad->center=NULL;
	point->x=poly_line[i].x;
	point->y=poly_line[i].y;
	for(i=1;i<n;i++){
		insert_point(point,poly_line[i].x,poly_line[i].y,'P');
	}
	point->label->x=point->x;
	point->label->y=point->y;
	strcpy(point->label->text,"polyline");
	if(cad->point==NULL){
		cad->point=point;
		control1=1;
	}
	else if(cad->point!=NULL){
		newcad->point=point;	
		insert_cad(cad,newcad);
		control2=1;
	}
	c2d_create_hierarchy_add_parent(cad,h);
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_poly_line_linkedlisthl(CAD2D *cad,point2D *poly_line,int n,hierarchy *h,const label *l){
	//this function add points to the given cad and add the cad to the given hierarchy before this things function check the given label is there in given cadlinkedlist if cadlist->point->x and y is the same with the given label this function dont add the given points to the cad and hierarchy.
	int sayac=0,i=0,j=0;
	int control1=0,control2=0;
	point2D *point=(point2D*)malloc(sizeof(point2D));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	cad->center=NULL;
	point->x=poly_line[i].x;
	point->y=poly_line[i].y;
	point2D *tempp;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point->label=(label*)malloc(sizeof(label));
	CAD2D *tempc;
	tempc=cad;
	int control=0;
	for(i=1;i<n;i++){
		insert_point(point,poly_line[i].x,poly_line[i].y,'P');
	}
	point->label->x=point->x;
	point->label->y=point->y;
	strcpy(point->label->text,"polyline");
	if(cad->point==NULL){
		cad->point=point;
		control1=1;
		control=1;
	}
	else if(cad->point!=NULL){
		tempp=cad->point;	
		while(tempc->nextcad!=NULL){
			while(tempp->nextp!=NULL){
				if(tempp->x==l->x && tempp->y==l->y){
					control=1;
				}
				tempp=tempp->nextp;
			}
			tempc=tempc->nextcad;
		}
		control2=1;
	}
	if(control==0){
		newcad->point=point;
		tempc->nextcad=newcad;
		c2d_create_hierarchy_add_parent(cad,h);
	}
	else{
		printf("there is a point has same label you send becasue of this we cant add any point to cad");
	}	
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label *c2d_add_polygon(CAD2D *cad,point2D *poly_line,int n){
	int sayac=0,i=0,j=0;
	point2D *center2;
	point2D *point=(point2D*)malloc(sizeof(point2D));
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point2D *firstp=(point2D*)malloc(sizeof(point2D));// for closepath
	firstp->label=(label*)malloc(sizeof(label));
	point->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	point2D *tempp;
	point->x=poly_line[i].x;
	point->y=poly_line[i].y;
	firstp->x=poly_line[i].x;
	firstp->y=poly_line[i].y;
	firstp->label->x=point->x;
	firstp->label->y=point->y;
	strcpy(firstp->label->text,"polygon");
	firstp->nextp=NULL;
	for(i=1;i<=n;i++){
		insert_point(point,poly_line[i].x,poly_line[i].y,'G');
	}
	point->label->x=point->x;
	point->label->y=point->y;
	strcpy(point->label->text,"polygon");
	tempp=point;//to reach the end of the polygon to closepath
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=firstp;
	center2=find_polygon_center(point);//finds the polygon center
	cad->center->x=center2->x;
	cad->center->y=center2->y;
	cad->center->label->x=center2->x;
	cad->center->label->y=center2->y;
	strcpy(cad->center->label->text,"polygon_center");
	if(cad->point==NULL){
		cad->point=point;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=point;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_polygon_array(CAD2D *cad,double poly_line[][2],int n){
	int sayac=0,i=0,j=0;
	point2D *point=(point2D*)malloc(sizeof(point2D));
	point2D *center2;
	point2D *tempp;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point2D *firstp=(point2D*)malloc(sizeof(point2D));
	firstp->label=(label*)malloc(sizeof(label));
	point->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	point->x=poly_line[0][0];
	point->y=poly_line[0][1];
	firstp->x=poly_line[0][1];
	firstp->y=poly_line[0][1];
	firstp->label=(label*)malloc(sizeof(label));
	firstp->label->x=point->x;
	firstp->label->y=point->y;
	strcpy(firstp->label->text,"polygon");
	for(i=1;i<=n;i++){
		insert_point(point,poly_line[i][0],poly_line[i][1],'G');
	}
	point->label->x=poly_line[0][0];
	point->label->y=poly_line[0][1];
	strcpy(point->label->text,"polygon");
	center2=find_polygon_center(point);
	cad->center->x=center2->x;
	cad->center->y=center2->y;
	cad->center->label->x=center2->x;
	cad->center->label->y=center2->y;
	strcpy(cad->center->label->text,"polygon_center");
	tempp=point;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=firstp;
	if(cad->point==NULL){
		cad->point=point;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=point;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_polygon_linkedlisth(CAD2D *cad,point2D *poly_line,int n, hierarchy *h){
	int sayac=0,i=0,j=0;
	int control1=0,control2=0;
	point2D *tempp;
	point2D *center2;
	point2D *point=(point2D*)malloc(sizeof(point2D));
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point2D *firstp=(point2D*)malloc(sizeof(point2D));
	firstp->label=(label*)malloc(sizeof(label));
	point->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	point->x=poly_line[i].x;
	point->y=poly_line[i].y;
	firstp->x=poly_line[i].x;
	firstp->y=poly_line[i].y;
	firstp->label->x=point->x;
	firstp->label->y=point->y;
	strcpy(firstp->label->text,"polygon");
	for(i=1;i<=n;i++){
		insert_point(point,poly_line[i].x,poly_line[i].y,'G');
	}
	point->label->x=point->x;
	point->label->y=point->y;
	strcpy(point->label->text,"polygon");
	center2=find_polygon_center(point);
	cad->center->x=center2->x;
	cad->center->y=center2->y;
	cad->center->label->x=center2->x;
	cad->center->label->y=center2->y;
	strcpy(cad->center->label->text,"polygon_center");
	tempp=point;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=firstp;
	if(cad->point==NULL){
		cad->point=point;
		control1=1;
	}
	else if(cad->point!=NULL){
		newcad->point=point;	
		insert_cad(cad,newcad);
		control2=1;
	}
	c2d_create_hierarchy_add_parent(cad,h);
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_polygone_linkedlisthl(CAD2D *cad,point2D *poly_line,int n,hierarchy *h,const label *l){
	int sayac=0,i=0,j=0;
	int control1=0,control2=0;
	CAD2D *tempc;
	tempc=cad;
	int control=0;
	point2D *point=(point2D*)malloc(sizeof(point2D));
	point2D *tempp,*center2;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	point->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	point2D *firstp=(point2D*)malloc(sizeof(point2D));
	firstp->label=(label*)malloc(sizeof(label));
	point->x=poly_line[i].x;
	point->y=poly_line[i].y;
	firstp->x=poly_line[i].x;
	firstp->y=poly_line[i].y;
	firstp->label->x=point->x;
	firstp->label->y=point->y;
	strcpy(firstp->label->text,"polygon");
	for(i=1;i<=n;i++){
		insert_point(point,poly_line[i].x,poly_line[i].y,'G');
	}
	point->label->x=point->x;
	point->label->y=point->y;
	strcpy(point->label->text,"polygon");
	center2=find_polygon_center(point);
	cad->center->x=center2->x;
	cad->center->y=center2->y;
	cad->center->label->x=center2->x;
	cad->center->label->y=center2->y;
	strcpy(cad->center->label->text,"polygon_center");
	tempp=point;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=firstp;
	if(cad->point==NULL){
		cad->point=point;
		control1=1;
		control=1;
	}
	else if(cad->point!=NULL){
		tempp=cad->point;	
		while(tempc->nextcad!=NULL){
			while(tempp->nextp!=NULL){
				if(tempp->x==l->x && tempp->y==l->y){
					control=1;
				}
				tempp=tempp->nextp;
			}
			tempc=tempc->nextcad;
		}
		control2=1;
	}
	if(control==0){
		newcad->point=point;
		tempc->nextcad=newcad;
		c2d_create_hierarchy_add_parent(cad,h);
	}
	else{
		printf("there is a point has same label you send becasue of this we cant add any point to cad");
	}	
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
point2D* find_polygon_center(point2D *point){
	//this function find the center of polygon
	double x0=0.0,y0=0.0,x1=0.0,y1=0.0,a=0.0;
	double signedarea=0.0;
	point2D *center1=(point2D*)malloc(sizeof(point2D));
	point2D *tempp=point;
	while(tempp->nextp!=NULL){
		x0=tempp->x;
		y0=tempp->y;
		x1=tempp->nextp->x;
		y1=tempp->nextp->y;
		a=x0*y1-x1*y0;
		signedarea+=a;
		center1->x+=(x0+x1)*a;
		center1->y+=(y0+y1)*a;
		tempp=tempp->nextp;
	}
	tempp=point;
	x0=tempp->x;
	y0=tempp->y;
	x1=point->x;
	y1=point->y;
	a=x0*y1-x1*y0;
	signedarea+=a;
	center1->x+=(x0+x1)*a;
	center1->y+=(y0+y1)*a;
	signedarea*=0.5;
	center1->x/=(6.0*signedarea);
	center1->y/=(6.0*signedarea);
	return center1;
}
label* c2d_add_ellipse(CAD2D *cad,point2D *center,double a,double b){
	//this function add points to the given cad,this points occur around the ellipse to create ellipse.
	double start_x,end_x;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	cad->center=(point2D*)malloc(sizeof(point2D));
	cad->center->label=(label*)malloc(sizeof(label));
	point2D *head1;
	point2D *head2;
	point2D *tempp;
	double x1=a;
	double y1=b;
	double pos_ellipse_func(double x){
		return sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	double neg_ellipse_func(double x){
		return -sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	start_x=-a;
	end_x=a;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'E');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'E');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"ellipse_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_ellipse1(CAD2D *cad,double centerx,double centery,point2D *lengths){
	double start_x,end_x;
	point2D *center=(point2D*)malloc(sizeof(point2D));
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	point2D *head1,*head2,*tempp;
	center->x=centerx;
	center->y=centery;
	double x1=lengths->x;// a length
	double y1=lengths->y;// b length
	double pos_ellipse_func(double x){
		return sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	double neg_ellipse_func(double x){
		return -sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	start_x=-lengths->x;
	end_x=lengths->x;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'E');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'E');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=centerx;
	center->label->y=centery;
	strcpy(center->label->text,"ellipse_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_ellipse_h(CAD2D *cad,point2D *center,double a,double b, hierarchy *h){
	double start_x,end_x;
	int control1=0,control2=0;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	point2D *head1,*head2,*tempp;
	double x1=a;
	double y1=b;
	double pos_ellipse_func(double x){
		return sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	double neg_ellipse_func(double x){
		return -sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	start_x=-a;
	end_x=a;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'E');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'E');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"ellipse_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		control1=1;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		control2=1;
	}
	c2d_create_hierarchy_add_parent(cad,h);
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_ellipse_h_label(CAD2D *cad,point2D *center,double a,double b,hierarchy *h,const label *l){
	double start_x,end_x;
	int control=0,control1=0,control2=0;
	CAD2D *tempc;
	point2D *tempp,*head1,*head2;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	tempc=cad;
	center->label=(label*)malloc(sizeof(label));
	double x1=a;
	double y1=b;
	double pos_ellipse_func(double x){
		return sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	double neg_ellipse_func(double x){
		return -sqrt((1-((x*x))/(x1*x1))*(y1*y1));
	}
	start_x=-a;
	end_x=a;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'E');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'E');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"ellipse_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		control1=1;
		control=1;
	}
	else if(cad->point!=NULL){
		tempp=head1;	
		while(tempc->nextcad!=NULL){
			while(tempp->nextp!=NULL){
				if(tempp->x==l->x && tempp->y==l->y){
					control=1;
				}
				tempp=tempp->nextp;
			}
			tempc=tempc->nextcad;
		}
		control2=1;
	}
	if(control==0){
		newcad->point=head1;
		tempc->nextcad=newcad;
		c2d_create_hierarchy_add_parent(cad,h);
	}
	else{
		printf("there is a point has same label you send becasue of this we cant add any point to cad");
	}
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_circle(CAD2D *cad,point2D *center,double r){
	double start_x,end_x;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	point2D *head1,*head2,*tempp;
	double pos_ellipse_func(double x){
		return sqrt((r*r)-(x*x));
	}
	double neg_ellipse_func(double x){
		return -sqrt((r*r)-(x*x));
	}
	start_x=-r;
	end_x=r;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'C');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'C');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"circle_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_circle1(CAD2D *cad,double centerx,double centery,double r){
	double start_x,end_x;
	point2D *center,*head1,*head2,*tempp;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center=(point2D*)malloc(sizeof(point2D));
	center->label=(label*)malloc(sizeof(label));
	center->x=centerx;
	center->y=centery;
	double pos_ellipse_func(double x){
		return sqrt((r*r)-(x*x));
	}
	double neg_ellipse_func(double x){
		return -sqrt((r*r)-(x*x));
	}
	start_x=-r;
	end_x=r;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'C');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'C');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=centerx;
	center->label->y=centery;
	strcpy(center->label->text,"circle_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_circle_h(CAD2D *cad,point2D *center,double r,hierarchy *h){
	double start_x,end_x;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	point2D *head1,*head2,*tempp;
	int control1=0,control2=0;
	double pos_ellipse_func(double x){
		return sqrt((r*r)-(x*x));
	}
	double neg_ellipse_func(double x){
		return -sqrt((r*r)-(x*x));
	}
	start_x=-r;
	end_x=r;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'C');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'C');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"circle_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		control1=1;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		control2=1;
	}
	c2d_create_hierarchy_add_parent(cad,h);
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_circle_h_label(CAD2D *cad,point2D *center,double r,hierarchy *h,label *l){
	double start_x,end_x;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	int control=0,control1=0,control2=0;
	CAD2D *tempc;
	tempc=cad;
	point2D *tempp,*head1,*head2;
	double pos_ellipse_func(double x){
		return sqrt((r*r)-(x*x));
	}
	double neg_ellipse_func(double x){
		return -sqrt((r*r)-(x*x));
	}
	start_x=-r;
	end_x=r;
	head1=draw_fx(cad,pos_ellipse_func,start_x,end_x,'C');
	head2=draw_fx(cad,neg_ellipse_func,start_x,end_x,'C');
	tempp=head1;
	while(tempp->nextp!=NULL){
		tempp=tempp->nextp;
	}
	tempp->nextp=head2;
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"circle_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		control1=1;
		control=1;
	}
	else if(cad->point!=NULL){
		tempp=head1;	
		while(tempc->nextcad!=NULL){
			while(tempp->nextp!=NULL){
				if(tempp->x==l->x && tempp->y==l->y){
					control=1;
				}
				tempp=tempp->nextp;
			}
			tempc=tempc->nextcad;
		}
		control2=1;
	}
	if(control==0){
		newcad->point=head1;
		tempc->nextcad=newcad;
		c2d_create_hierarchy_add_parent(cad,h);
	}
	else{
		printf("there is a point has same label you send becasue of this we cant add any point to cad");
	}
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_arc(CAD2D *cad,point2D *center,double degree1,double degree2,int choice,double r){
	double temp,temp1;
	double radyan1,radyan2;
	double start_x;
	point2D *head1,*head2,*head3,*tempp;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	double end_x;
	double arc_func_pos(double x){
		return sqrt((r*r)-(x*x));
	}
	double arc_func_neg(double x){
		return -sqrt((r*r)-(x*x));
	}
	if(choice==TRUE && (degree1<180 && degree2>180)||(degree2<180 && degree1>180)){
		if(degree2>degree1){
			temp=degree2-degree1;
			temp1=360-degree2+degree1;
			if(temp1>temp){
				start_x=r*cos(degree2);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=r*cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=r*cos(degree2);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=r*cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
		else if(degree1>degree2){
			temp=degree1-degree2;
			temp1=360-degree1+degree2;
			if(temp1>temp){
				start_x=r*cos(degree1);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				printf("%lf",start_x);
				start_x=r;
				end_x=r*cos(radyan2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=r*cos(degree1);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=r*cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
	}
	else if(choice==FALSE && (degree1<180 && degree2>180)||(degree2<180 && degree1>180)){
		if(degree2>degree1){
			temp=degree2-degree1;
			temp1=360-degree2+degree1;
			if(temp1>temp){
				start_x=r*cos(degree2);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=r*cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=r*cos(degree2);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=r*cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
		else if(degree1>degree2){
			temp=degree1-degree2;
			temp1=360-degree1+degree2;
			if(temp1>temp){
				start_x=r*cos(degree1);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=r*cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=r*cos(degree1);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=r*cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
	}
	else if(choice==TRUE && degree1<180 && degree2<180){
		if(degree1>degree2){
			start_x=r*cos(degree1);
			end_x=-r;
		head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
		head2=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=r*cos(degree2);
		head3=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
		else if(degree2>degree1){
			start_x=r*cos(degree2);
			end_x=-r;
		head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
		head2=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=r*cos(degree1);
			head3=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
	}
	else if(choice==FALSE && degree1<180 && degree2<180){
		if(degree1>degree2){
			start_x=r*cos(degree1);
			end_x=r*cos(degree2);
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
		}
		else if(degree2>degree1){
			start_x=r*cos(degree2);
			end_x=r*cos(degree1);
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
		}
	}
	else if(degree1>180 && degree2>180 && choice==TRUE){
		if(degree1>degree2){
			start_x=r*cos(degree2);
			end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=r*cos(degree1);
			head3=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
		else if(degree2>degree1){
			start_x=r*cos(degree1);
			end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=r*cos(degree2);
			head3=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
	}
	else if(choice==FALSE && degree1>180 && degree2>180){
		if(degree1>degree2){
			start_x=r*cos(degree2);
			end_x=r*cos(degree1);
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
		}
		else if(degree2>degree1){
			start_x=r*cos(degree1);
			end_x=r*cos(degree2);
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
		}
	}
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"arc_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		return cad->point->label;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		return newcad->point->label;
	}
}
label* c2d_add_arc_h(CAD2D *cad,point2D *center,double degree1,double degree2,int choice,double r,hierarchy *h){
	double temp,temp1;
	double start_x,end_x;
	point2D *tempp,*head1,*head2,*head3;
	CAD2D *tempcad;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D*));
	center->label=(label*)malloc(sizeof(label));
	int control1=0,control2=0;
	double arc_func_pos(double x){
		return sqrt((r*r)-(x*x));
	}
	double arc_func_neg(double x){
		return -sqrt((r*r)-(x*x));
	}
	if(choice==TRUE && (degree1<180 && degree2>180)||(degree2<180 && degree1>180)){
		if(degree2>degree1){
			temp=degree2-degree1;
			temp1=360-degree2+degree1;
			if(temp1>temp){
				start_x=cos(degree2);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree2);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
		else if(degree1>degree2){
			temp=degree1-degree2;
			temp1=360-degree1+degree2;
			if(temp1>temp){
				start_x=cos(degree1);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree1);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
	}
	else if(choice==FALSE && (degree1<180 && degree2>180)||(degree2<180 && degree1>180)){
		if(degree2>degree1){
			temp=degree2-degree1;
			temp1=360-degree2+degree1;
			if(temp1>temp){
				start_x=cos(degree2);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree2);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
		else if(degree1>degree2){
			temp=degree1-degree2;
			temp1=360-degree1+degree2;
			if(temp1>temp){
				start_x=cos(degree1);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree1);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
	}
	else if(choice==TRUE && degree1<180 && degree2<180){
		if(degree1>degree2){
			start_x=cos(degree1);
			end_x=-r;
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree2);
			head3=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
		else if(degree2>degree1){
			start_x=cos(degree2);
			end_x=-r;
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree1);
			head3=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
	}
	else if(choice==FALSE && degree1<180 && degree2<180){
		if(degree1>degree2){
			start_x=cos(degree1);
			end_x=cos(degree2);
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
		}
		else if(degree2>degree1){
			start_x=cos(degree2);
			end_x=cos(degree1);
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
		}
	}
	else if(degree1>180 && degree2>180 && choice==TRUE){
		if(degree1>degree2){
			start_x=cos(degree2);
			end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree1);
			head3=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
		else if(degree2>degree1){
			start_x=cos(degree1);
			end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree2);
			head3=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
	}
	else if(choice==FALSE && degree1>180 && degree2>180){
		if(degree1>degree2){
			start_x=cos(degree2);
			end_x=cos(degree1);
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
		}
		else if(degree2>degree1){
			start_x=cos(degree1);
			end_x=cos(degree2);
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
		}
	}
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"arc_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		control1=1;
	}
	else if(cad->point!=NULL){
		newcad->point=head1;	
		insert_cad(cad,newcad);
		control2=1;
	}
	c2d_create_hierarchy_add_parent(cad,h);
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
label* c2d_add_arc_h_label(CAD2D *cad,point2D *center,double degree1,double degree2,int choice,double r,hierarchy *h,label *l){
	CAD2D *tempc;
	int control=0;
	tempc=cad;
	double start_x,end_x;
	CAD2D *newcad=(CAD2D*)malloc(sizeof(CAD2D));
	center->label=(label*)malloc(sizeof(label));
	int control1=0,control2=0;
	double temp,temp1;
	point2D *tempp,*head1,*head2,*head3;
	double arc_func_pos(double x){
		return sqrt((r*r)-(x*x));
	}
	double arc_func_neg(double x){
		return -sqrt((r*r)-(x*x));
	}
	if(choice==TRUE && (degree1<180 && degree2>180)||(degree2<180 && degree1>180)){
		if(degree2>degree1){
			temp=degree2-degree1;
			temp1=360-degree2+degree1;
			if(temp1>temp){
				start_x=cos(degree2);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree2);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
		else if(degree1>degree2){
			temp=degree1-degree2;
			temp1=360-degree1+degree2;
			if(temp1>temp){
				start_x=cos(degree1);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree1);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
	}
	else if(choice==FALSE && (degree1<180 && degree2>180)||(degree2<180 && degree1>180)){
		if(degree2>degree1){
			temp=degree2-degree1;
			temp1=360-degree2+degree1;
			if(temp1>temp){
				start_x=cos(degree2);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree2);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree1);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
		else if(degree1>degree2){
			temp=degree1-degree2;
			temp1=360-degree1+degree2;
			if(temp1>temp){
				start_x=-cos(degree1);
				end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=-r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
			else if(temp>temp1){
				start_x=cos(degree1);
				end_x=r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
				start_x=r;
				end_x=cos(degree2);
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
				tempp=head1;
				while(tempp->nextp!=NULL){
					tempp=tempp->nextp;
				}
				tempp->nextp=head2;
			}
		}
	}
	else if(choice==TRUE && degree1<180 && degree2<180){
		if(degree1>degree2){
			start_x=cos(degree1);
			end_x=-r;
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree2);
			head3=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
		else if(degree2>degree1){
			start_x=cos(degree2);
			end_x=-r;
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree1);
			head3=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
	}
	else if(choice==FALSE && degree1<180 && degree2<180){
		if(degree1>degree2){
			start_x=cos(degree1);
			end_x=cos(degree2);
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
		}
		else if(degree2>degree1){
			start_x=cos(degree2);
			end_x=cos(degree1);
			head1=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
		}
	}
	else if(degree1>180 && degree2>180 && choice==TRUE){
		if(degree1>degree2){
			start_x=cos(degree2);
			end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree1);
			head3=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
		else if(degree2>degree1){
			start_x=cos(degree1);
			end_x=-r;
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			start_x=-r;
			end_x=r;
			head2=draw_fx(cad,arc_func_pos,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head2;
			start_x=r;
			end_x=cos(degree2);
			head3=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
			tempp=head1;
			while(tempp->nextp!=NULL){
				tempp=tempp->nextp;
			}
			tempp->nextp=head3;
		}
	}
	else if(choice==FALSE && degree1>180 && degree2>180){
		if(degree1>degree2){
			start_x=cos(degree2);
			end_x=cos(degree1);
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
		}
		else if(degree2>degree1){
			start_x=cos(degree1);
			end_x=cos(degree2);
			head1=draw_fx(cad,arc_func_neg,start_x,end_x,'A');
		}
	}
	center->label->x=center->x;
	center->label->y=center->y;
	strcpy(center->label->text,"arc_center");
	cad->center=center;
	if(cad->point==NULL){
		cad->point=head1;
		control1=1;
		control=1;
	}
	else if(cad->point!=NULL){
		tempp=head1;	
		while(tempc->nextcad!=NULL){
			while(tempp->nextp!=NULL){
				if(tempp->x==l->x && tempp->y==l->y){
					control=1;
				}
				tempp=tempp->nextp;
			}
			tempc=tempc->nextcad;
		}
		control2=1;
	}
	if(control==0){
		newcad->point=head1;
		tempc->nextcad=newcad;
		c2d_create_hierarchy_add_parent(cad,h);
	}
	else{
		printf("there is a point has same label you send becasue of this we cant add any point to cad");
	}
	if(control1==1) return cad->point->label;
	else if(control2==1) return newcad->point->label;
}
void c2d_snap(CAD2D *cad,const label *ls,const label *lt){
	point2D *tempp,*findpls,*findplt;
	CAD2D *tempc;
	tempc=cad;
	point2D *tempp1,*tempp2,*tempP,*tempP1,*tempp3;
	double result=999.0;
	point2D *center,*poly_center;
	int control=0,control1=0,counter=0;
	double longdistance=0.0;
	double smalldistance=999.0;
	while(tempc!=NULL){
		tempp=tempc->point;
		if(!strcmp(tempc->point->label->text,"point")&&tempp->x==ls->x && tempp->y==ls->y){
			findpls=tempc->point;
			counter++;
			control=1;
		}
		else if(!strcmp(tempc->point->label->text,"point")&&tempp->x==lt->x && tempp->y==lt->y){
			findplt=tempc->point;
			control1=1;
			counter++;
		}
		else{
			while(tempp->nextp!=NULL){
				if(tempp->x==ls->x && tempp->y==ls->y){
					control=1;
					findpls=tempp;
					counter++;
				}
				if(tempp->x==lt->x && tempp->y==lt->y){
					control1=1;
					findplt=tempp;
					counter++;
				}
				tempp=tempp->nextp;
			}	
		}
		tempc=tempc->nextcad;
		if(counter==2) break;
		
	}
	if(control==0){
		printf("there is no ls point in cad data like this");
	}
	else if(control==1){
		printf("you find the ls data in cad structure");
	}
	if(control1==0){
		printf("there is no lt point in cad data like this");
	}
	else if(control1==1){
		printf("you find the lt data in cad structure");
	}
	if(!strcmp(ls->text,"point") && !strcmp(lt->text,"point")){
		findpls->x=findplt->x;
		findpls->y=findplt->y;
	}
	else if(!strcmp(ls->text,"point") && !strcmp(lt->text,"polyline")){
		tempp=findplt;
		while(tempp->nextp!=NULL){
			if(result<smalldistance){
				smalldistance=result;
				tempP->x=tempp->x;
				tempP->y=tempp->y;			
			}
			result=sqrt((tempp->x-findpls->x)*(tempp->x-findpls->x)+(tempp->y-findpls->y)*(tempp->y-findpls->y));
			tempp=tempp->nextp;
		}
		findpls->x=tempP->x;
		findpls->y=tempP->y;
	}
	else if(!strcmp(ls->text,"point") && !strcmp(lt->text,"polygon")){
		tempp=findplt;
		poly_center=find_polygon_center(tempp);
		findpls->x=poly_center->x;
		findpls->y=poly_center->y;
	}
	else if(!strcmp(ls->text,"point") && !strcmp(lt->text,"arc_center")){
		findpls->x=findplt->x;
		findpls->y=findplt->y;
	}
	else if(!strcmp(ls->text,"polyline") && !strcmp(lt->text,"point")){
		tempp=findpls;
		tempp1=findpls;
		while(tempp->nextp!=NULL){
			if(result<smalldistance){
				smalldistance=result;
				tempP->x=tempp->x;
				tempP->y=tempp->y;			
			}
			result=sqrt((tempp->x-findplt->x)*(tempp->x-findplt->x)+(tempp->y-findplt->y)*(tempp->y-findplt->y));
			tempp=tempp->nextp;
		}
		while(tempp1->nextp!=NULL){
			if(tempp1->x==tempP->x && tempp1->y==tempP->y){
				tempp1->x=findplt->x;
				tempp1->y=findplt->y;
				break;
			}
			tempp1=tempp1->nextp;
		}
	}
	else if(!strcmp(ls->text,"polyline") && !strcmp(lt->text,"polyline")){
		tempp=findplt;
		tempp3=findplt;
		tempp1=findpls;
		tempp2=findpls;
		while(tempp->nextp!=NULL){
			tempp1=findpls;
			while(tempp1->nextp!=NULL){
				if(result<smalldistance){
					smalldistance=result; 
					tempP->x=tempp->x;
					tempP->y=tempp->y;
					tempP1->x=tempp1->x;
					tempP1->y=tempp1->y;			
				}
				result=sqrt((tempp->x-tempp1->x)*(tempp->x-tempp1->x)+(tempp->y-tempp1->y)*(tempp->y-tempp1->y));
				tempp1=tempp1->nextp;
			}
			tempp=tempp->nextp;
		}
		while(tempp2->nextp!=NULL){
			if(tempp2->x==tempP1->x && tempp2->y==tempP1->y){
				break;
			}
			tempp2=tempp2->nextp;
		}
		while(tempp3->nextp!=NULL){
			if(tempp3->x==tempP->x && tempp3->y==tempP->y){
				tempp2->x=tempp3->x;
				tempp2->y=tempp3->y;
				break;
			}
			tempp3=tempp3->nextp;
		}
	}
	else if(!strcmp(ls->text,"polyline") && !strcmp(lt->text,"polygon")){
		tempp=findplt;
		poly_center=find_polygon_center(tempp);
		tempp1=findpls;
		tempp2=findpls;
		while(tempp1->nextp!=NULL){
			if(result<smalldistance){
				smalldistance=result;
				tempP->x=tempp1->x;
				tempP->y=tempp1->y;			
			}
			result=sqrt((tempp1->x-poly_center->x)*(tempp1->x-poly_center->x)+(tempp->y-poly_center->y)*(tempp->y-poly_center->y));
			tempp1=tempp1->nextp;
		}
		while(tempp2->nextp!=NULL){
			if(tempp2->x==tempP->x && tempp2->y==tempP->y){
				tempp2->x=poly_center->x;
				tempp2->y=poly_center->y;
				break;
			}
			tempp2=tempp2->nextp;
		}
	}
	else if(!strcmp(ls->text,"polygon") && !strcmp(lt->text,"point")){
		tempp=findpls;
		poly_center=find_polygon_center(tempp);
		poly_center->x=findplt->x;
		poly_center->y=findplt->y;
	}
	else if(!strcmp(ls->text,"polygon") && !strcmp(lt->text,"polyline")){
		tempp=findplt;
		tempp3=findplt;
		while(tempp->nextp!=NULL){
			tempp1=findpls;
			tempp2=findpls;
			while(tempp1->nextp!=NULL){
				if(result<smalldistance){
					smalldistance=result;
					tempP->x=tempp->x;
					tempP->y=tempp->y;
					tempP1->x=tempp1->x;
					tempP1->y=tempp1->y;			
				}
				result=sqrt((tempp->x-tempp1->x)*(tempp->x-tempp1->x)+(tempp->y-tempp1->y)*(tempp->y-tempp1->y));
				tempp1=tempp1->nextp;
			}
			tempp=tempp->nextp;
		}
		while(tempp2->nextp!=NULL){
			if(tempp2->x==tempP1->x && tempp2->y==tempP1->y){
				break;
			}
			tempp2=tempp2->nextp;
		}
		while(tempp3->nextp!=NULL){
			if(tempp3->x==tempP->x && tempp3->y==tempP->y){
				tempp2->x=tempp3->x;
				tempp2->y=tempp3->y;
				break;
			}
			tempp3=tempp3->nextp;
		}
	}
	else if(!strcmp(ls->text,"arc") && !strcmp(lt->text,"point")){
		tempp1=findpls;
		tempp2=findpls;
		while(tempp1->nextp!=NULL){
			if(result<smalldistance){
				smalldistance=result;
				tempP->x=tempp1->x;
				tempP->y=tempp1->y;			
			}
			result=sqrt((tempp1->x-findplt->x)*(tempp1->x-findplt->x)+(tempp->y-findplt->y)*(tempp->y-findplt->y));
			tempp1=tempp1->nextp;
		}
		while(tempp2->nextp!=NULL){
			if(tempp2->x==tempP->x && tempp2->y==tempP->y){
				tempp2->x=findplt->x;
				tempp2->y=findplt->y;
				break;
			}
			tempp2=tempp2->nextp;
		}
	}
	else if(!strcmp(ls->text,"arc_center") && !strcmp(lt->text,"polyline")){
		tempp=findplt;
		while(tempp->nextp!=NULL){
			if(result>longdistance){
				longdistance=result;
				findpls->x=tempp->x;
				findpls->y=tempp->y;			
			}
			result=sqrt((tempp->x-findpls->x)*(tempp->x-findpls->x)+(tempp->y-findpls->y)*(tempp->y-findpls->y));
			tempp=tempp->nextp;
		}
	}
}
double c2d_measure(CAD2D *cad,const label *ls,const label *lt){
	point2D *tempp,*tempp1,*findpls,*findplt;
	CAD2D *tempc;
	tempc=cad;
	tempp=cad->point;   
	double result=999.0;
	int choice=0,counter=0;
	int control=0,control1=0;
	double smalldistance=999.0;
	printf("Please enter 0 for point measure enter 1 for closest distance: ");
	scanf("%d",&choice);
	while(tempc!=NULL){
		tempp=tempc->point;
		if(!strcmp(tempc->point->label->text,"point")&&tempp->x==ls->x && tempp->y==ls->y){
			findpls=tempc->point;
			counter++;
			control=1;
		}
		else if(!strcmp(tempc->point->label->text,"point")&&tempp->x==lt->x && tempp->y==lt->y){
			findplt=tempc->point;
			control1=1;
			counter++;
		}
		else{
			while(tempp->nextp!=NULL){
				if(tempp->x==ls->x && tempp->y==ls->y){
					control=1;
					findpls=tempp;
					counter++;
				}
				if(tempp->x==lt->x && tempp->y==lt->y){
					control1=1;
					findplt=tempp;
					counter++;	
				}
				tempp=tempp->nextp;
			}
		}
		tempc=tempc->nextcad;
		if(counter==2) break;
	}
	if(!strcmp(ls->text,"point")&&!strcmp(lt->text,"point")&&choice==0){
		result=sqrt((findplt->x-findpls->x)*(findplt->x-findpls->x)+(findplt->y-findpls->y)*(findplt->y-findpls->y));
		return result;
	}
	else if(!strcmp(ls->text,"point")&&!strcmp(lt->text,"polyline")&&choice==0){
		tempp=findplt;
		while(tempp->nextp!=NULL){
			if(result<smalldistance){
				smalldistance=result;			
			}
			result=sqrt((tempp->x-findpls->x)*(tempp->x-findpls->x)+(tempp->y-findpls->y)*(tempp->y-findpls->y));
			tempp=tempp->nextp;
		}
		return smalldistance;
	}
	else if(!strcmp(ls->text,"point")&&!strcmp(lt->text,"polygon")&&choice==0){
		tempp=findplt;
		printf("%lf ",findplt->nextp->nextp->x);
		while(tempp->nextp!=NULL){
			if(result<smalldistance){
				smalldistance=result;			
			}
			result=sqrt((tempp->x-findpls->x)*(tempp->x-findpls->x)+(tempp->y-findpls->y)*(tempp->y-findpls->y));
			tempp=tempp->nextp;
		}
		return smalldistance;
	}
	else if(!strcmp(ls->text,"point")&&!strcmp(lt->text,"arc")&&choice==0){
		tempp=findplt;
		while(tempp->nextp!=NULL){
			if(result<smalldistance){
				smalldistance=result;			
			}
			result=sqrt((tempp->x-findpls->x)*(tempp->x-findpls->x)+(tempp->y-findpls->y)*(tempp->y-findpls->y));
			tempp=tempp->nextp;
		}
		return smalldistance;
	}
	else if(choice==1){
		tempp1=findpls;
		tempp=findplt;
		while(tempp->nextp!=NULL){
			while(tempp1->nextp!=NULL){
				if(result<smalldistance){
					smalldistance=result;		
				}
				result=sqrt((tempp->x-tempp1->x)*(tempp->x-tempp1->x)+(tempp->y-tempp1->y)*(tempp->y-tempp1->y));
				tempp1=tempp1->nextp;
			}
			tempp=tempp->nextp;
		}
		return smalldistance;
	}
}
point2D* draw_fx(CAD2D *cad,double f(double x),double start_x,double end_x,char choice){
	double temp,temp1;
	point2D *headp=(point2D*)malloc(sizeof(point2D));
	headp->label=(label*)malloc(sizeof(label));
	headp->x=start_x;
	headp->y=f(start_x);
	headp->label->x=start_x;
	headp->label->y=f(start_x);
	if(choice=='E'){
		strcpy(headp->label->text,"ellipse");
	}
	else if(choice=='C'){
		strcpy(headp->label->text,"circle");
	}
	else if(choice=='A'){
		strcpy(headp->label->text,"arc");
	}
	temp=start_x;
	temp1=(1.0/cad->resolution);
	for(temp;temp<=end_x;temp+=temp1){
		insert_point(headp,temp,f(temp),choice);
	}
	return headp;	
}
void c2d_export(CAD2D *cad,char *file_name){
	point2D *tempp;
	CAD2D *tempcad;
	tempcad=cad;
	tempp=cad->point;
	FILE *fp;
	fp=fopen(file_name,"wt");
	fprintf(fp,"%%!PS-ADOBE-3.0 EPSF-3.0\n");
	fprintf(fp,"%%%%BoundingBox: %d %d %d %d\n",(int)cad->llx,(int)cad->lly,(int)cad->urx,(int)cad->ury);
	fprintf(fp,"%d setlinewidth\n",(int)cad->thickness);
	fprintf(fp,"%d %d %d  setrgbcolor\n",cad->color.red,cad->color.green,cad->color.blue);
	fprintf(fp,"newpath\n");
	if(tempcad->nextcad==NULL){
		if(cad->text!=NULL){
			fprintf(fp,"/Times-Romanfindfont\n12scalefont\nsetfont\n");
			while(cad->text->nextt!=NULL){
				fprintf(fp,"%d %d moveto\n",(int)cad->text->x,(int)cad->text->y);
				fprintf(fp,"(%c) show\n",cad->text->write);
				cad->text=cad->text->nextt;
			}
		}	
		if(cad->point!=NULL){
			if(!strcmp(cad->point->label->text,"point")){
				fprintf(fp,"%.1f %.1f moveto\n",cad->point->x,cad->point->y);
				fprintf(fp,"%.1f %.1f ",tempp->x+0.1,tempp->y+0.1);
				fprintf(fp,"lineto\n");
			}
			else{
				fprintf(fp,"%.1f %.1f moveto\n",cad->point->x,cad->point->y);
				for(tempp=cad->point->nextp;tempp!=NULL;tempp=tempp->nextp){	
					fprintf(fp,"%.1f %.1f ",tempp->x,tempp->y);
					fprintf(fp,"lineto\n");
				}
			}
		}
		fprintf(fp,"stroke\n");
		fclose(fp);
	}
	else if(tempcad->nextcad!=NULL){
		while(tempcad!=NULL){
			if(tempcad->text!=NULL){
				fprintf(fp,"/Times-Romanfindfont\n5scalefont\nsetfont\n");
				while(tempcad->text->nextt!=NULL){
					fprintf(fp,"%d %d moveto\n",(int)tempcad->text->x,(int)tempcad->text->y);
					fprintf(fp,"(%d) show\n",tempcad->text->write);
					tempcad->text=tempcad->text->nextt;
				}
			}
			if(tempcad->point!=NULL){
				if(!strcmp(tempcad->point->label->text,"point")){
					tempp=tempcad->point;
					fprintf(fp,"%.1f %.1f moveto\n",tempcad->point->x,tempcad->point->y);
					fprintf(fp,"%.1f %.1f ",tempp->x+0.1,tempp->y+0.1);
					fprintf(fp,"lineto\n");
				}
				else{
					for(tempp=tempcad->point->nextp;tempp!=NULL;tempp=tempp->nextp){
						fprintf(fp,"%.1f %.1f moveto\n",tempcad->point->x,cad->point->y);		
						fprintf(fp,"%.1f %.1f ",tempp->x,tempp->y);
						fprintf(fp,"lineto\n");
					}
				}
				tempcad=tempcad->nextcad;
			}
		}
		fprintf(fp,"stroke\n");
		fclose(fp);
	}
}
