/*
** epslib.h:
**
** The header file declaring eps format library functions.
**
** Author:Ahmet Furkan Kurban
**
**
*/
#ifndef EPSLIB_H
#define EPSLIB_H
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
label *c2d_add_polygon(CAD2D *cad,point2D *poly_line,int n);
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

#endif
