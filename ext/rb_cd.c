#include <ruby.h>
#include "rb_iup.h"

extern VALUE rb_cCdCanvas;

VALUE rb_cCdCanvas_initialize(VALUE self,VALUE v_canvas)
{	
	if(NUM2ULONG(v_canvas)==0) return Qnil;
	rb_iv_set(self,"@canvas",v_canvas);
	return self;
}

VALUE rb_cdVersion(VALUE self)
{
	char* v;
	v = cdVersion();
	return  rb_str_new2(v);
}

VALUE rb_cdVersionDate(VALUE self)
{
	char* v;
	v = cdVersionDate();
	return  rb_str_new2(v);
}

VALUE rb_cdActiveCanvas(VALUE self)
{
	cdCanvas* v;
	v = cdActiveCanvas();
	if(v==NULL) return Qnil;
	return rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
}

VALUE rb_cdActivate(VALUE self)
{
	int v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdActivate((cdCanvas*)NUM2ULONG(v_canvas));
	return ULONG2NUM((unsigned long)v); 
}

VALUE rb_cdCreateCanvas(VALUE self,VALUE v_context,VALUE v_data)
{
	cdCanvas* v;
	void* data;
	if(TYPE(v_data)==T_FIXNUM || TYPE(v_data)==T_BIGNUM)
		data = (void*)NUM2ULONG(v_data);
	else if(TYPE(v_data)==T_STRING)
		data = (void*)RSTRING_PTR(v_data);
	else {
		VALUE v_ih = rb_iv_get(v_data,"@ihandle");
		data = (void*)NUM2ULONG(v_ih);
	}
	v = cdCreateCanvas((cdContext*)NUM2ULONG(v_context),data);
	if(v) 
		return rb_funcall(rb_cCdCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)v));	
	return Qnil;
}

VALUE rb_cdKillCanvas(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdKillCanvas((cdCanvas*)NUM2ULONG(v_canvas));
	return Qnil;
}

VALUE rb_cdCanvasGetContext(VALUE self)
{
	cdContext* v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdCanvasGetContext((cdCanvas*)NUM2ULONG(v_canvas));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasActivate(VALUE self)
{
	cdCanvas* canvas = NULL;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int v;
	if(v_canvas!=Qnil) canvas = (cdCanvas*)NUM2ULONG(v_canvas);
	v = cdActivate(canvas);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasDeactivate(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasDeactivate((cdCanvas*)NUM2ULONG(v_canvas));
	return Qnil;
}

VALUE rb_cdUseContextPlus(VALUE self,VALUE v_use)
{
	int use = NUM2ULONG(v_use);
	unsigned long v;
	v = cdUseContextPlus(use);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdContextRegisterCallback(VALUE self,VALUE v_context,VALUE v_cb,VALUE v_func)
{
	unsigned long cb = NUM2ULONG(v_cb);
	int v;
	void *func = (void*)NUM2ULONG(v_func);
	v = cdContextRegisterCallback((cdContext*)NUM2ULONG(v_context),cb,func);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdContextCaps(VALUE self,VALUE v_context)
{
	long v;
	v = cdContextCaps((cdContext*)NUM2ULONG(v_context));
	return LONG2NUM(v);
}

VALUE rb_cdCanvasSimulate(VALUE self,VALUE v_mode)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	unsigned long mode = NUM2ULONG(v_mode);
	int v;
	v = cdCanvasSimulate((cdCanvas*)NUM2ULONG(v_canvas),mode);
	return INT2NUM(v);
}

VALUE rb_cdCanvasFlush(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasFlush((cdCanvas*)NUM2ULONG(v_canvas));
	return Qnil;
}

VALUE rb_cdCanvasClear(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasClear((cdCanvas*)NUM2ULONG(v_canvas));
	return Qnil;
}

VALUE rb_cdCanvasSaveState(VALUE self)
{
	cdState* v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdCanvasSaveState((cdCanvas*)NUM2ULONG(v_canvas));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasRestoreState(VALUE self,VALUE v_state)
{
	cdState* state = (cdState*)NUM2ULONG(v_state);
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasRestoreState((cdCanvas*)NUM2ULONG(v_canvas),state);
	return Qnil;
}

VALUE rb_cdReleaseState(VALUE self,VALUE v_state)
{
	cdState* state = (cdState*)NUM2ULONG(v_state);
	cdReleaseState(state);
	return Qnil;
}

VALUE rb_cdCanvasSetAttribute(VALUE self,VALUE v_name,VALUE v_data)
{
	const char* name = RSTRING_PTR(v_name);
	char* data = RSTRING_PTR(v_data);
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasSetAttribute((cdCanvas*)NUM2ULONG(v_canvas),name,data);
	return Qnil;
}

VALUE rb_cdCanvasGetAttribute(VALUE self,VALUE v_name)
{
	const char* name = RSTRING_PTR(v_name);
	char* v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdCanvasGetAttribute((cdCanvas*)NUM2ULONG(v_canvas),name);
	return  rb_str_new2(v);
}

VALUE rb_cdCanvasPlay(VALUE self,VALUE v_context,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax,VALUE v_data)
{
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	void *data = (void*)NUM2ULONG(v_data);
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int v;
	v = cdCanvasPlay((cdCanvas*)NUM2ULONG(v_canvas),(cdContext*)NUM2ULONG(v_context),xmin,xmax,ymin,ymax,data);
	return INT2NUM(v);
}

VALUE rb_cdCanvasGetSize(VALUE self,VALUE v_width,VALUE v_height,VALUE v_width_mm,VALUE v_height_mm)
{
	int width;
	int height;
	double mm_width;
	double mm_height;
	VALUE v_r;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasGetSize((cdCanvas*)NUM2ULONG(v_canvas),&width,&height,&mm_width,&mm_height);
	v_r = rb_ary_new3(4,INT2FIX(width),INT2FIX(height),rb_float_new(mm_width),rb_float_new(mm_height));
	return v_r;
}

VALUE rb_cdCanvasUpdateYAxis(VALUE self,VALUE v_y)
{
	int y = NUM2INT(v_y);
	int v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdCanvasUpdateYAxis((cdCanvas*)NUM2ULONG(v_canvas),&y);
	return INT2NUM(y);
}

VALUE rb_cdfCanvasUpdateYAxis(VALUE self,VALUE v_y)
{
	double y = RFLOAT_VALUE(v_y);
	double v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdfCanvasUpdateYAxis((cdCanvas*)NUM2ULONG(v_canvas),&y);
	return rb_float_new(y);
}

VALUE rb_cdCanvasInvertYAxis(VALUE self,VALUE v_y)
{
	int y = NUM2INT(v_y);
	int v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdCanvasInvertYAxis((cdCanvas*)NUM2ULONG(v_canvas),y);
	return INT2NUM(y);
}

VALUE rb_cdfCanvasInvertYAxis(VALUE self,VALUE v_y)
{
	double y = RFLOAT_VALUE(v_y);
	double v;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	v = cdfCanvasInvertYAxis((cdCanvas*)NUM2ULONG(v_canvas),y);
	return rb_float_new(v);
}

VALUE rb_cdCanvasMM2Pixel(VALUE self,VALUE v_mm_dx,VALUE v_mm_dy)
{
	double mm_dx = RFLOAT_VALUE(v_mm_dx);
	double mm_dy = RFLOAT_VALUE(v_mm_dy);
	int dx;
	int dy;
	VALUE v_r;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasMM2Pixel((cdCanvas*)NUM2ULONG(v_canvas),mm_dx,mm_dy,&dx,&dy);
	v_r = rb_ary_new3(2,INT2FIX(dx),INT2FIX(dy));
	return v_r;
}

VALUE rb_cdCanvasPixel2MM(VALUE self,VALUE v_dx,VALUE v_dy)
{
	double mm_dx;
	double mm_dy;
	int dx = NUM2INT(v_dx);
	int dy = NUM2INT(v_dy);
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	VALUE v_r;
	cdCanvasPixel2MM((cdCanvas*)NUM2ULONG(v_canvas),dx,dy,&mm_dx,&mm_dy);
	v_r = rb_ary_new3(2,rb_float_new(mm_dx),rb_float_new(mm_dy));
	return v_r;
}

VALUE rb_cdfCanvasMM2Pixel(VALUE self,VALUE v_mm_dx,VALUE v_mm_dy,VALUE v_dx,VALUE v_dy)
{
	double mm_dx = RFLOAT_VALUE(v_mm_dx);
	double mm_dy = RFLOAT_VALUE(v_mm_dy);
	double dx;
	double dy;
	VALUE v_r;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdfCanvasMM2Pixel((cdCanvas*)NUM2ULONG(v_canvas),mm_dx,mm_dy,&dx,&dy);
	v_r = rb_ary_new3(2,rb_float_new(dx),rb_float_new(dy));
	return v_r;
}

VALUE rb_cdfCanvasPixel2MM(VALUE self,VALUE v_dx,VALUE v_dy)
{
	double mm_dx;
	double mm_dy;
	double dx = RFLOAT_VALUE(v_dx);
	double dy = RFLOAT_VALUE(v_dy);
	VALUE v_r;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdfCanvasPixel2MM((cdCanvas*)NUM2ULONG(v_canvas),dx,dy,&mm_dx,&mm_dy);
	v_r = rb_ary_new3(2,rb_float_new(mm_dx),rb_float_new(mm_dy));
	return v_r;
}

VALUE rb_cdCanvasOrigin(VALUE self,VALUE v_x,VALUE v_y)
{
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasOrigin((cdCanvas*)NUM2ULONG(v_canvas),x,y);
	return Qnil;
}

VALUE rb_cdfCanvasOrigin(VALUE self,VALUE v_x,VALUE v_y)
{
	double x = RFLOAT_VALUE(v_x);
	double y = RFLOAT_VALUE(v_y);
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdfCanvasOrigin((cdCanvas*)NUM2ULONG(v_canvas),x,y);
	return Qnil;
}

VALUE rb_cdCanvasGetOrigin(VALUE self)
{
	int x;
	int y;
	VALUE v_r;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasGetOrigin((cdCanvas*)NUM2ULONG(v_canvas),&x,&y);
	v_r = rb_ary_new3(2,INT2FIX(x),INT2FIX(y));
	return v_r;
}

VALUE rb_cdfCanvasGetOrigin(VALUE self,VALUE v_x,VALUE v_y)
{
	double x;
	double y;
	VALUE v_r;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdfCanvasGetOrigin((cdCanvas*)NUM2ULONG(v_canvas),&x,&y);
	v_r = rb_ary_new3(2,rb_float_new(x),rb_float_new(y));
	return v_r;
}

VALUE rb_cdCanvasTransform(VALUE self,VALUE v_matrix)
{
	double *matrix = NULL;
	int i;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	if(v_matrix!=Qnil) {
		matrix = xmalloc(sizeof(double)*6);
		for(i=0;i<RARRAY_LEN(v_matrix) && i<6;i++)
		  	matrix[i] = RFLOAT_VALUE(RARRAY_PTR(v_matrix)[i]);
	}
	cdCanvasTransform((cdCanvas*)NUM2ULONG(v_canvas),matrix);
	if(matrix) free(matrix);
	return Qnil;
}

VALUE rb_cdCanvasGetTransform(VALUE self)
{
	double* v;
	int i;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	VALUE v_r = rb_ary_new();
	v = cdCanvasGetTransform((cdCanvas*)NUM2ULONG(v_canvas));
	if(v==NULL) return Qnil;
	for(i=0;i<6;i++)
		rb_ary_push(v_r,rb_float_new(v[i]));
	return v_r;
}

VALUE rb_cdCanvasTransformMultiply(VALUE self,VALUE v_matrix)
{
	double *matrix = NULL;
	int i;
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	if(v_matrix!=Qnil) {
		matrix = xmalloc(sizeof(double)*6);
		for(i=0;i<RARRAY_LEN(v_matrix) && i<6;i++)
		  	matrix[i] = RFLOAT_VALUE(RARRAY_PTR(v_matrix)[i]);
	}
	cdCanvasTransformMultiply((cdCanvas*)NUM2ULONG(v_canvas),matrix);
	return Qnil;
}

VALUE rb_cdCanvasTransformRotate(VALUE self,VALUE v_angle)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double angle = RFLOAT_VALUE(v_angle);
	cdCanvasTransformRotate((cdCanvas*)NUM2ULONG(v_canvas),angle);
	return Qnil;
}

VALUE rb_cdCanvasTransformScale(VALUE self,VALUE v_sx,VALUE v_sy)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double sx = RFLOAT_VALUE(v_sx);
	double sy = RFLOAT_VALUE(v_sy);
	cdCanvasTransformScale((cdCanvas*)NUM2ULONG(v_canvas),sx,sy);
	return Qnil;
}

VALUE rb_cdCanvasTransformTranslate(VALUE self,VALUE v_dx,VALUE v_dy)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double dx = RFLOAT_VALUE(v_dx);
	double dy = RFLOAT_VALUE(v_dy);
	cdCanvasTransformTranslate((cdCanvas*)NUM2ULONG(v_canvas),dx,dy);
	return Qnil;
}

VALUE rb_cdCanvasTransformPoint(VALUE self,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int tx;
	int ty;
	VALUE v_r;
	cdCanvasTransformPoint((cdCanvas*)NUM2ULONG(v_canvas),x,y,&tx,&ty);
	v_r = rb_ary_new3(2,INT2FIX(tx),INT2FIX(ty));
	return v_r;
}

VALUE rb_cdfCanvasTransformPoint(VALUE self,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double x = RFLOAT_VALUE(v_x);
	double y = RFLOAT_VALUE(v_y);
	double tx;
	double ty;
	VALUE v_r;
	cdfCanvasTransformPoint((cdCanvas*)NUM2ULONG(v_canvas),x,y,&tx,&ty);
	v_r = rb_ary_new3(2,rb_float_new(tx),rb_float_new(ty));
	return v_r;
}

VALUE rb_cdCanvasClip(VALUE self,VALUE v_mode)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int mode = NUM2INT(v_mode);
	int v;
	v = cdCanvasClip((cdCanvas*)NUM2ULONG(v_canvas),mode);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasClipArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	cdCanvasClipArea((cdCanvas*)NUM2ULONG(v_canvas),xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdCanvasGetClipArea(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	int v;
	VALUE v_r;
	v = cdCanvasGetClipArea((cdCanvas*)NUM2ULONG(v_canvas),&xmin,&xmax,&ymin,&ymax);
	v_r = rb_ary_new3(4,INT2FIX(xmin),INT2FIX(xmax),INT2FIX(ymin),INT2FIX(ymax));
	return v_r;
}

VALUE rb_cdfCanvasClipArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double xmin = RFLOAT_VALUE(v_xmin);
	double xmax = RFLOAT_VALUE(v_xmax);
	double ymin = RFLOAT_VALUE(v_ymin);
	double ymax = RFLOAT_VALUE(v_ymax);
	cdfCanvasClipArea((cdCanvas*)NUM2ULONG(v_canvas),xmin,xmax,ymin,ymax);	
	return Qnil;
}

VALUE rb_cdfCanvasGetClipArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	int v;
	VALUE v_r;
	v = cdfCanvasGetClipArea((cdCanvas*)NUM2ULONG(v_canvas),&xmin,&xmax,&ymin,&ymax);
	v_r = rb_ary_new3(4,rb_float_new(xmin),rb_float_new(xmax),rb_float_new(ymin),rb_float_new(ymax));
	return v_r;
}

VALUE rb_cdCanvasIsPointInRegion(VALUE self,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int v;
	v = cdCanvasIsPointInRegion((cdCanvas*)NUM2ULONG(v_canvas),x,y);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasOffsetRegion(VALUE self,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2ULONG(v_x);
	int y = NUM2ULONG(v_y);
	cdCanvasOffsetRegion((cdCanvas*)NUM2ULONG(v_canvas),x,y);
	return Qnil;
}

VALUE rb_cdCanvasGetRegionBox(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	VALUE v_r;
	cdCanvasGetRegionBox((cdCanvas*)NUM2ULONG(v_canvas),&xmin,&xmax,&ymin,&ymax);
	v_r = rb_ary_new3(4,INT2FIX(xmin),INT2FIX(xmax),INT2FIX(ymin),INT2FIX(ymax));
	return v_r;
}

VALUE rb_cdCanvasRegionCombineMode(VALUE self,VALUE v_mode)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int mode = NUM2INT(v_mode);
	int v;
	v = cdCanvasRegionCombineMode((cdCanvas*)NUM2ULONG(v_canvas),mode);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasPixel(VALUE self,VALUE v_x,VALUE v_y,VALUE v_color)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	long int color = NUM2LONG(v_color);
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	cdCanvasPixel((cdCanvas*)NUM2ULONG(v_canvas),x,y,color);
	return Qnil;
}

VALUE rb_cdCanvasMark(VALUE self,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	cdCanvasMark((cdCanvas*)NUM2ULONG(v_canvas),x,y);
	return Qnil;
}

VALUE rb_cdCanvasLine(VALUE self,VALUE v_x1,VALUE v_y1,VALUE v_x2,VALUE v_y2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x1 = NUM2INT(v_x1);
	int y1 = NUM2INT(v_y1);
	int x2 = NUM2INT(v_x2);
	int y2 = NUM2INT(v_y2);
	cdCanvasLine((cdCanvas*)NUM2ULONG(v_canvas),x1,y1,x2,y2);
	return Qnil;
}

VALUE rb_cdCanvasBegin(VALUE self,VALUE v_mode)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int mode = NUM2INT(v_mode);
	cdCanvasBegin((cdCanvas*)NUM2ULONG(v_canvas),mode);
	return Qnil;
}

VALUE rb_cdCanvasVertex(VALUE self,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	cdCanvasVertex((cdCanvas*)NUM2ULONG(v_canvas),x,y);
	return Qnil;
}

VALUE rb_cdCanvasEnd(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	cdCanvasEnd((cdCanvas*)NUM2ULONG(v_canvas));
	return Qnil;
}

VALUE rb_cdCanvasRect(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	cdCanvasRect((cdCanvas*)NUM2ULONG(v_canvas),xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdCanvasBox(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	cdCanvasBox((cdCanvas*)NUM2ULONG(v_canvas),xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdCanvasArc(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xc = NUM2INT(v_xc);
	int yc = NUM2INT(v_yc);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	double angle1 = RFLOAT_VALUE(v_angle1);
	double angle2 = RFLOAT_VALUE(v_angle2);
	cdCanvasArc((cdCanvas*)NUM2ULONG(v_canvas),xc,yc,w,h,angle1,angle2);
	return Qnil;
}

VALUE rb_cdCanvasSector(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xc = NUM2INT(v_xc);
	int yc = NUM2INT(v_yc);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	double angle1 = RFLOAT_VALUE(v_angle1);
	double angle2 = RFLOAT_VALUE(v_angle2);
	cdCanvasSector((cdCanvas*)NUM2ULONG(v_canvas),xc,yc,w,h,angle1,angle2);
	return Qnil;
}

VALUE rb_cdCanvasChord(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xc = NUM2INT(v_xc);
	int yc = NUM2INT(v_yc);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	double angle1 = RFLOAT_VALUE(v_angle1);
	double angle2 = RFLOAT_VALUE(v_angle2);
	cdCanvasChord((cdCanvas*)NUM2ULONG(v_canvas),xc,yc,w,h,angle1,angle2);
	return Qnil;
}

VALUE rb_cdCanvasText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	const char* s = RSTRING_PTR(v_s);
	cdCanvasText((cdCanvas*)NUM2ULONG(v_canvas),x,y,s);
	return Qnil;
}

VALUE rb_cdfCanvasLine(VALUE self,VALUE v_x1,VALUE v_y1,VALUE v_x2,VALUE v_y2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double x1 = RFLOAT_VALUE(v_x1);
	double y1 = RFLOAT_VALUE(v_y1);
	double x2 = RFLOAT_VALUE(v_x2);
	double y2 = RFLOAT_VALUE(v_y2);	
	cdfCanvasLine((cdCanvas*)NUM2ULONG(v_canvas),x1,y1,x2,y2);
	return Qnil;
}

VALUE rb_cdfCanvasVertex(VALUE self,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double x = RFLOAT_VALUE(v_x);
	double y = RFLOAT_VALUE(v_y);
	cdfCanvasVertex((cdCanvas*)NUM2ULONG(v_canvas),x,y);
	return Qnil;
}

VALUE rb_cdfCanvasRect(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double xmin = RFLOAT_VALUE(v_xmin);
	double xmax = RFLOAT_VALUE(v_xmax);
	double ymin = RFLOAT_VALUE(v_ymin);
	double ymax = RFLOAT_VALUE(v_ymax);
	cdfCanvasRect((cdCanvas*)NUM2ULONG(v_canvas),xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdfCanvasBox(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double xmin = RFLOAT_VALUE(v_xmin);
	double xmax = RFLOAT_VALUE(v_xmax);
	double ymin = RFLOAT_VALUE(v_ymin);
	double ymax = RFLOAT_VALUE(v_ymax);
	cdfCanvasBox((cdCanvas*)NUM2ULONG(v_canvas),xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdfCanvasArc(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double xc = RFLOAT_VALUE(v_xc);
	double yc = RFLOAT_VALUE(v_yc);
	double w = RFLOAT_VALUE(v_w);
	double h = RFLOAT_VALUE(v_h);
	double angle1 = RFLOAT_VALUE(v_angle1);
	double angle2 = RFLOAT_VALUE(v_angle2);
	cdfCanvasArc((cdCanvas*)NUM2ULONG(v_canvas),xc,yc,w,h,angle1,angle2);
	return Qnil;
}

VALUE rb_cdfCanvasSector(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double xc = RFLOAT_VALUE(v_xc);
	double yc = RFLOAT_VALUE(v_yc);
	double w = RFLOAT_VALUE(v_w);
	double h = RFLOAT_VALUE(v_h);
	double angle1 = RFLOAT_VALUE(v_angle1);
	double angle2 = RFLOAT_VALUE(v_angle2);
	cdfCanvasSector((cdCanvas*)NUM2ULONG(v_canvas),xc,yc,w,h,angle1,angle2);
	return Qnil;
}

VALUE rb_cdfCanvasChord(VALUE self,VALUE v_xc,VALUE v_yc,VALUE v_w,VALUE v_h,VALUE v_angle1,VALUE v_angle2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double xc = RFLOAT_VALUE(v_xc);
	double yc = RFLOAT_VALUE(v_yc);
	double w = RFLOAT_VALUE(v_w);
	double h = RFLOAT_VALUE(v_h);
	double angle1 = RFLOAT_VALUE(v_angle1);
	double angle2 = RFLOAT_VALUE(v_angle2);
	cdfCanvasChord((cdCanvas*)NUM2ULONG(v_canvas),xc,yc,w,h,angle1,angle2);
	return Qnil;
}

VALUE rb_cdfCanvasText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double x = RFLOAT_VALUE(v_x);
	double y = RFLOAT_VALUE(v_y);
	const char* s = RSTRING_PTR(v_s);
	cdfCanvasText((cdCanvas*)NUM2ULONG(v_canvas),x,y,s);
	return Qnil;
}

VALUE rb_cdCanvasSetBackground(VALUE self,VALUE v_color)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	long color = NUM2LONG(v_color);
	cdCanvasSetBackground((cdCanvas*)NUM2ULONG(v_canvas),color);
	return Qnil;
}

VALUE rb_cdCanvasSetForeground(VALUE self,VALUE v_color)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	long color = NUM2LONG(v_color);
	cdCanvasSetForeground((cdCanvas*)NUM2ULONG(v_canvas),color);
	return Qnil;
}

VALUE rb_cdCanvasBackground(VALUE self,VALUE v_color)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	long color = NUM2LONG(v_color);
	long v;
	v = cdCanvasBackground((cdCanvas*)NUM2ULONG(v_canvas),color);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasForeground(VALUE self,VALUE v_color)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	long color = NUM2LONG(v_color);
	long v;
	v = cdCanvasForeground((cdCanvas*)NUM2ULONG(v_canvas),color);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasBackOpacity(VALUE self,VALUE v_opacity)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int opacity = NUM2INT(v_opacity);
	int v;
	v = cdCanvasBackOpacity((cdCanvas*)NUM2ULONG(v_canvas),opacity);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasWriteMode(VALUE self,VALUE v_mode)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int mode = NUM2INT(v_mode);
	int v;
	v = cdCanvasWriteMode((cdCanvas*)NUM2ULONG(v_canvas),mode);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasLineStyle(VALUE self,VALUE v_style)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int style = NUM2INT(v_style);
	int v;
	v = cdCanvasLineStyle((cdCanvas*)NUM2ULONG(v_canvas),style);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasLineStyleDashes(VALUE self,VALUE v_dashes)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int dashes[100];
	int i;
	int count = RARRAY_LEN(v_dashes);
	for(i=0;i<count;i++)
	  dashes[i] = NUM2INT(RARRAY_PTR(v_dashes)[i]);
	cdCanvasLineStyleDashes((cdCanvas*)NUM2ULONG(v_canvas),dashes,count);
	return Qnil;
}

VALUE rb_cdCanvasLineWidth(VALUE self,VALUE v_width)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int width = NUM2INT(v_width);
	int v;
	v = cdCanvasLineWidth((cdCanvas*)NUM2ULONG(v_canvas),width);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasLineJoin(VALUE self,VALUE v_join)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int join = NUM2INT(v_join);
	int v;
	v = cdCanvasLineJoin((cdCanvas*)NUM2ULONG(v_canvas),join);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasLineCap(VALUE self,VALUE v_cap)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int cap = NUM2INT(v_cap);
	int v;
	v = cdCanvasLineCap((cdCanvas*)NUM2ULONG(v_canvas),cap);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasInteriorStyle(VALUE self,VALUE v_style)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int style = NUM2INT(v_style);
	int v;
	v = cdCanvasInteriorStyle((cdCanvas*)NUM2ULONG(v_canvas),style);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasHatch(VALUE self,VALUE v_style)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int style = NUM2INT(v_style);
	int v;
	v = cdCanvasHatch((cdCanvas*)NUM2ULONG(v_canvas),style);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasStipple(VALUE self,VALUE v_w,VALUE v_h,VALUE v_stipple)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	const unsigned char* stipple = (unsigned char*)RSTRING_PTR(v_stipple);
	cdCanvasStipple((cdCanvas*)NUM2ULONG(v_canvas),w,h,stipple);
	return Qnil;
}

VALUE rb_cdCanvasGetStipple(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int n;
	int m;
	char* v;
	VALUE v_r;
	v = (char*)cdCanvasGetStipple((cdCanvas*)NUM2ULONG(v_canvas),&n,&m);
	v_r = rb_ary_new3(3,rb_str_new(v,n*m),INT2FIX(n),INT2FIX(m));
	return v_r;
}

VALUE rb_cdCanvasPattern(VALUE self,VALUE v_w,VALUE v_h,VALUE v_pattern)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	long int pattern[100];
	int i;
	for(i=0;i<w*h && i<RARRAY_LEN(v_pattern);i++)
		pattern[i] = NUM2LONG(RARRAY_PTR(v_pattern)[i]);
	cdCanvasPattern((cdCanvas*)NUM2ULONG(v_canvas),w,h,pattern);
	return Qnil;
}

VALUE rb_cdCanvasGetPattern(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int n;
	int m;
	long* v;
	int i;
	VALUE v_r,v_p;
	v = cdCanvasGetPattern((cdCanvas*)NUM2ULONG(v_canvas),&n,&m);
	v_p = rb_ary_new();
	for(i=0;i<n*m;i++)
		rb_ary_push(v_p,LONG2NUM(v[i]));
	v_r = rb_ary_new3(3,v_p,INT2FIX(n),INT2FIX(m));
	return v_r;
}

VALUE rb_cdCanvasFillMode(VALUE self,VALUE v_mode)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int mode = NUM2INT(v_mode);
	int v;
	v = cdCanvasFillMode((cdCanvas*)NUM2ULONG(v_canvas),mode);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasFont(VALUE self,VALUE v_type_face,VALUE v_style,VALUE v_size)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	const char* type_face = NULL;
	int style = NUM2INT(v_style);
	int size = NUM2INT(v_size);
	int v;
	if(v_type_face!=Qnil)
		type_face = RSTRING_PTR(v_type_face);
	v = cdCanvasFont((cdCanvas*)NUM2ULONG(v_canvas),type_face,style,size);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasGetFont(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	char type_face[100];
	int style;
	int size;
	VALUE v_r;
	cdCanvasGetFont((cdCanvas*)NUM2ULONG(v_canvas),type_face,&style,&size);
	v_r = rb_ary_new3(3,rb_str_new2(type_face),INT2FIX(style),INT2FIX(size));
	return Qnil;
}

VALUE rb_cdCanvasNativeFont(VALUE self,VALUE v_font)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	const char* font = RSTRING_PTR(v_font);
	char* v;
	v = cdCanvasNativeFont((cdCanvas*)NUM2ULONG(v_canvas),font);
	return  rb_str_new2(v);
}

VALUE rb_cdCanvasTextAlignment(VALUE self,VALUE v_alignment)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int alignment = NUM2INT(v_alignment);
	int v;
	v = cdCanvasTextAlignment((cdCanvas*)NUM2ULONG(v_canvas),alignment);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasTextOrientation(VALUE self,VALUE v_angle)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double angle = RFLOAT_VALUE(v_angle);
	double v;
	v = cdCanvasTextOrientation((cdCanvas*)NUM2ULONG(v_canvas),angle);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasMarkType(VALUE self,VALUE v_type)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int type = NUM2INT(v_type);
	int v;
	v = cdCanvasMarkType((cdCanvas*)NUM2ULONG(v_canvas),type);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasMarkSize(VALUE self,VALUE v_size)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int size = NUM2INT(v_size);
	int v;
	v = cdCanvasMarkSize((cdCanvas*)NUM2ULONG(v_canvas),size);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasVectorText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	const char* s = RSTRING_PTR(v_s);
	cdCanvasVectorText((cdCanvas*)NUM2ULONG(v_canvas),x,y,s);
	return Qnil;
}

VALUE rb_cdCanvasMultiLineVectorText(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	const char* s = RSTRING_PTR(v_s);
	cdCanvasMultiLineVectorText((cdCanvas*)NUM2ULONG(v_canvas),x,y,s);
	return Qnil;
}

VALUE rb_cdCanvasVectorFont(VALUE self,VALUE v_filename)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	const char *filename = NULL;
	char *v;
	if(v_filename!=Qnil) filename = RSTRING_PTR(v_filename);
	v = cdCanvasVectorFont((cdCanvas*)NUM2ULONG(v_canvas),filename);
	if(v==NULL) return Qnil;
	return rb_str_new2(v);
}

VALUE rb_cdCanvasVectorTextDirection(VALUE self,VALUE v_x1,VALUE v_y1,VALUE v_x2,VALUE v_y2)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x1 = NUM2INT(v_x1);
	int y1 = NUM2INT(v_y1);
	int x2 = NUM2INT(v_x2);
	int y2 = NUM2INT(v_y2);
	cdCanvasVectorTextDirection((cdCanvas*)NUM2ULONG(v_canvas),x1,y1,x2,y2);
	return Qnil;
}

VALUE rb_cdCanvasVectorTextTransform(VALUE self,VALUE v_matrix)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	double* v;
	double *matrix = NULL;
	int i;
	VALUE v_r;
	if(v_matrix!=Qnil) {
		matrix = xmalloc(sizeof(double)*6);
		for(i=0;i<RARRAY_LEN(v_matrix) && i<6;i++)
		  	matrix[i] = RFLOAT_VALUE(RARRAY_PTR(v_matrix)[i]);
	}
	v = cdCanvasVectorTextTransform((cdCanvas*)NUM2ULONG(v_canvas),matrix);
	if(matrix) free(matrix);
	v_r = rb_ary_new();
	for(i=0;i<6;i++)
		rb_ary_push(v_r,rb_float_new(v[i]));
	return v_r;
}

VALUE rb_cdCanvasVectorTextSize(VALUE self,VALUE v_size_x,VALUE v_size_y,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int size_x = NUM2INT(v_size_x);
	int size_y = NUM2INT(v_size_y);
	const char* s = RSTRING_PTR(v_s);
	cdCanvasVectorTextSize((cdCanvas*)NUM2ULONG(v_canvas),size_x,size_y,s);
	return Qnil;
}

VALUE rb_cdCanvasVectorCharSize(VALUE self,VALUE v_size)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int size = NUM2INT(v_size);
	int v;
	v = cdCanvasVectorCharSize((cdCanvas*)NUM2ULONG(v_canvas),size);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasGetVectorTextSize(VALUE self,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	const char* s = RSTRING_PTR(v_s);
	int x;
	int y;
	VALUE v_r;
	cdCanvasGetVectorTextSize((cdCanvas*)NUM2ULONG(v_canvas),s,&x,&y);
	v_r = rb_ary_new3(2,INT2FIX(x),INT2FIX(y));
	return Qnil;
}

VALUE rb_cdCanvasGetVectorTextBounds(VALUE self,VALUE v_s,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	const char* s = RSTRING_PTR(v_s);
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int rect[8];
	VALUE v_r;
	int i;
	cdCanvasGetVectorTextBounds((cdCanvas*)NUM2ULONG(v_canvas),s,x,y,rect);
	v_r = rb_ary_new();
	for(i=0;i<8;i++)
		rb_ary_push(v_r,INT2FIX(rect[i]));
	return v_r;
}

VALUE rb_cdCanvasGetFontDim(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int max_width;
	int height;
	int ascent;
	int descent;
	VALUE v_r;
	cdCanvasGetFontDim((cdCanvas*)NUM2ULONG(v_canvas),&max_width,&height,&ascent,&descent);
	v_r = rb_ary_new3(4,INT2FIX(max_width),INT2FIX(height),INT2FIX(ascent),INT2FIX(descent));
	return v_r;
}

VALUE rb_cdCanvasGetTextSize(VALUE self,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	const char* s = RSTRING_PTR(v_s);
	int width;
	int height;
	VALUE v_r;
	cdCanvasGetTextSize((cdCanvas*)NUM2ULONG(v_canvas),s,&width,&height);
	v_r = rb_ary_new3(2,INT2FIX(width),INT2FIX(height));
	return v_r;
}

VALUE rb_cdCanvasGetTextBox(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	const char* s = RSTRING_PTR(v_s);
	int xmin;
	int xmax;
	int ymin;
	int ymax;
	VALUE v_r;
	cdCanvasGetTextBox((cdCanvas*)NUM2ULONG(v_canvas),x,y,s,&xmin,&xmax,&ymin,&ymax);
	v_r = rb_ary_new3(4,INT2FIX(xmin),INT2FIX(xmax),INT2FIX(ymin),INT2FIX(ymax));
	return v_r;
}

VALUE rb_cdCanvasGetTextBounds(VALUE self,VALUE v_x,VALUE v_y,VALUE v_s)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	const char* s = RSTRING_PTR(v_s);
	int rect[8];
	VALUE v_r;
	int i;
	cdCanvasGetTextBounds((cdCanvas*)NUM2ULONG(v_canvas),x,y,s,rect);
	v_r = rb_ary_new();
	for(i=0;i<8;i++)
		rb_ary_push(v_r,INT2FIX(rect[i]));
	return v_r;
}

VALUE rb_cdCanvasGetColorPlanes(VALUE self)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int v;
	v = cdCanvasGetColorPlanes((cdCanvas*)NUM2ULONG(v_canvas));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdCanvasPalette(VALUE self,VALUE v_palette,VALUE v_mode)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int n = RARRAY_LEN(v_palette);
	long int *palette = xmalloc(n*sizeof(long));
	int mode = NUM2INT(v_mode);
	int i;
	for(i=0;i<n;i++)
		palette[i] = NUM2LONG(RARRAY_PTR(v_palette)[i]);
	cdCanvasPalette((cdCanvas*)NUM2ULONG(v_canvas),n,palette,mode);
	free(palette);
	return Qnil;
}

VALUE rb_cdCanvasGetImageRGB(VALUE self,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	unsigned char* r = (unsigned char*)xmalloc(w*h);
	unsigned char* g = (unsigned char*)xmalloc(w*h);
	unsigned char* b = (unsigned char*)xmalloc(w*h);
	VALUE v_r;
	cdCanvasGetImageRGB((cdCanvas*)NUM2ULONG(v_canvas),r,g,b,x,y,w,h);
	v_r = rb_ary_new3(rb_str_new((char*)r,w*h),rb_str_new((char*)g,w*h),rb_str_new((char*)b,w*h));
	free(r);
	free(g);
	free(b);
	return v_r;
}

VALUE rb_cdCanvasPutImageRectRGB(VALUE self,VALUE v_iw,VALUE v_ih,VALUE v_r,VALUE v_g,VALUE v_b,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int iw = NUM2INT(v_iw);
	int ih = NUM2INT(v_ih);
	const unsigned char* r = (unsigned char*)RSTRING_PTR(v_r);
	const unsigned char* g = (unsigned char*)RSTRING_PTR(v_g);
	const unsigned char* b = (unsigned char*)RSTRING_PTR(v_b);
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	cdCanvasPutImageRectRGB((cdCanvas*)NUM2ULONG(v_canvas),iw,ih,r,g,b,x,y,w,h,xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdCanvasPutImageRectRGBA(VALUE self,VALUE v_iw,VALUE v_ih,VALUE v_r,VALUE v_g,VALUE v_b,VALUE v_a,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int iw = NUM2INT(v_iw);
	int ih = NUM2INT(v_ih);
	const unsigned char* r = (unsigned char*)RSTRING_PTR(v_r);
	const unsigned char* g = (unsigned char*)RSTRING_PTR(v_g);
	const unsigned char* b = (unsigned char*)RSTRING_PTR(v_b);
	const unsigned char* a = NULL;
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	if(v_a!=Qnil) a = (unsigned char*)RSTRING_PTR(v_a);
	cdCanvasPutImageRectRGBA((cdCanvas*)NUM2ULONG(v_canvas),iw,ih,r,g,b,a,x,y,w,h,xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdCanvasPutImageRectMap(VALUE self,VALUE v_iw,VALUE v_ih,VALUE v_index,VALUE v_colors,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int iw = NUM2INT(v_iw);
	int ih = NUM2INT(v_ih);
	const unsigned char* index = (unsigned char*)RSTRING_PTR(v_index);
	long int *colors = xmalloc(RARRAY_LEN(v_colors)*sizeof(long));
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	int i;
	for(i=0;i<RARRAY_LEN(v_colors);i++)
		colors[i] = NUM2LONG(RARRAY_PTR(v_colors)[i]);
	cdCanvasPutImageRectMap((cdCanvas*)NUM2ULONG(v_canvas),iw,ih,index,colors,x,y,w,h,xmin,xmax,ymin,ymax);
	free(colors);
	return Qnil;
}

VALUE rb_cdCanvasCreateImage(VALUE self,VALUE v_w,VALUE v_h)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	cdImage* v;
	v = cdCanvasCreateImage((cdCanvas*)NUM2ULONG(v_canvas),w,h);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdKillImage(VALUE self,VALUE v_image)
{
	cdImage* image = (cdImage*)NUM2ULONG(v_image);
	cdKillImage(image);
	return Qnil;
}

VALUE rb_cdCanvasGetImage(VALUE self,VALUE v_image,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	cdImage* image = (cdImage*)NUM2ULONG(v_image);
	cdCanvasGetImage((cdCanvas*)NUM2ULONG(v_canvas),image,x,y);
	return Qnil;
}

VALUE rb_cdCanvasPutImageRect(VALUE self,VALUE v_image,VALUE v_x,VALUE v_y,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	cdImage* image = (cdImage*)NUM2ULONG(v_image);
	cdCanvasPutImageRect((cdCanvas*)NUM2ULONG(v_canvas),image,x,y,xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdCanvasScrollArea(VALUE self,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax,VALUE v_dx,VALUE v_dy)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	int dx = NUM2INT(v_dx);
	int dy = NUM2INT(v_dy);
	cdCanvasScrollArea((cdCanvas*)NUM2ULONG(v_canvas),xmin,xmax,ymin,ymax,dx,dy);
	return Qnil;
}

VALUE rb_cdCreateBitmap(VALUE self,VALUE v_w,VALUE v_h,VALUE v_type)
{
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	int type = NUM2INT(v_type);
	cdBitmap* v;
	v = cdCreateBitmap(w,h,type);
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdInitBitmap(int argc,VALUE *argv,VALUE self)
{
	int w = NUM2INT(argv[0]);
	int h = NUM2INT(argv[1]);
	int type = NUM2INT(argv[2]);
	cdBitmap* v;
	unsigned char* red = NULL;
	unsigned char* green = NULL;
	unsigned char* blue = NULL;
	unsigned char* alpha = NULL;
	unsigned char* index = NULL;
	long int* colors = NULL;
	int i;
	if(type==CD_RGBA) {
		red = (unsigned char*)RSTRING_PTR(argv[3]);
		green = (unsigned char*)RSTRING_PTR(argv[4]);
		blue = (unsigned char*)RSTRING_PTR(argv[5]);
		alpha = (unsigned char*)RSTRING_PTR(argv[6]);
		v = cdInitBitmap(w,h,type,red,green,blue,alpha);
	}
	else if(type==CD_RGB) {
		red = (unsigned char*)RSTRING_PTR(argv[3]);
		green = (unsigned char*)RSTRING_PTR(argv[4]);
		blue = (unsigned char*)RSTRING_PTR(argv[5]);
		v = cdInitBitmap(w,h,type,red,green,blue);
	}
	else if(type==CD_MAP) {
		index = (unsigned char*)RSTRING_PTR(argv[5]);		
		colors = xmalloc(RARRAY_LEN(argv[4]));
		for(i=0;i<RARRAY_LEN(argv[4]);i++)
			colors[i] = RARRAY_PTR(argv[4])[i];
		v = cdInitBitmap(w,h,type,index,colors);
	}
	else {
		rb_raise(rb_eArgError,"Invalid Argument");
	}
	if(colors) free(colors);
	return ULONG2NUM((unsigned long)v);
}


VALUE rb_cdKillBitmap(VALUE self,VALUE v_bitmap)
{
	cdKillBitmap((cdBitmap*)NUM2ULONG(v_bitmap));
	return Qnil;
}

VALUE rb_cdBitmapGetData(VALUE self,VALUE v_bitmap,VALUE v_dataptr)
{
	int dataptr = NUM2INT(v_dataptr);
	char* v;
	v = (char*)cdBitmapGetData((cdBitmap*)NUM2ULONG(v_bitmap),dataptr);
	return  rb_str_new2(v);
}

VALUE rb_cdBitmapSetRect(VALUE self,VALUE v_bitmap,VALUE v_xmin,VALUE v_xmax,VALUE v_ymin,VALUE v_ymax)
{
	int xmin = NUM2INT(v_xmin);
	int xmax = NUM2INT(v_xmax);
	int ymin = NUM2INT(v_ymin);
	int ymax = NUM2INT(v_ymax);
	cdBitmapSetRect((cdBitmap*)NUM2ULONG(v_bitmap),xmin,xmax,ymin,ymax);
	return Qnil;
}

VALUE rb_cdCanvasPutBitmap(VALUE self,VALUE v_bitmap,VALUE v_x,VALUE v_y,VALUE v_w,VALUE v_h)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	int w = NUM2INT(v_w);
	int h = NUM2INT(v_h);
	cdBitmap* bitmap = (cdBitmap*)NUM2ULONG(v_bitmap);
	cdCanvasPutBitmap((cdCanvas*)NUM2ULONG(v_canvas),bitmap,x,y,w,h);
	return Qnil;
}

VALUE rb_cdCanvasGetBitmap(VALUE self,VALUE v_bitmap,VALUE v_x,VALUE v_y)
{
	VALUE v_canvas = rb_iv_get(self,"@canvas");
	int x = NUM2INT(v_x);
	int y = NUM2INT(v_y);
	cdBitmap* bitmap = (cdBitmap*)NUM2ULONG(v_bitmap);
	cdCanvasGetBitmap((cdCanvas*)NUM2ULONG(v_canvas),bitmap,x,y);
	return Qnil;
}

VALUE rb_cdBitmapRGB2Map(VALUE self,VALUE v_bitmap_rgb,VALUE v_bitmap_map)
{
	cdBitmapRGB2Map((cdBitmap*)NUM2ULONG(v_bitmap_rgb),(cdBitmap*)NUM2ULONG(v_bitmap_map));
	return Qnil;
}

VALUE rb_cdEncodeColor(VALUE self,VALUE v_red,VALUE v_green,VALUE v_blue)
{
	unsigned char red = (unsigned char)NUM2INT(v_red);
	unsigned char green = (unsigned char)NUM2INT(v_green);
	unsigned char blue = (unsigned char)NUM2INT(v_blue);
	long v;
	v = cdEncodeColor(red,green,blue);
	return LONG2NUM(v);
}

VALUE rb_cdDecodeColor(VALUE self,VALUE v_color)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	VALUE v_r;
	cdDecodeColor((long)NUM2LONG(v_color),&red,&green,&blue);
	v_r = rb_ary_new3(3,INT2FIX(red),INT2FIX(green),INT2FIX(blue));
	return v_r;
}

VALUE rb_cdDecodeAlpha(VALUE self,VALUE v_color)
{
	char v;
	v = cdDecodeAlpha((long)NUM2LONG(v_color));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdEncodeAlpha(VALUE self,VALUE v_color,VALUE v_alpha)
{
	unsigned char alpha = (unsigned char)NUM2INT(v_alpha);
	long v;
	v = cdEncodeAlpha((long)NUM2LONG(v_color),alpha);
	return LONG2NUM(v);
}

VALUE rb_cdAlpha(VALUE self,VALUE v_color)
{
	char v;
	v = cdAlpha(NUM2LONG(v_color));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdReserved(VALUE self,VALUE v_color)
{
	char v;
	v = cdReserved(NUM2LONG(v_color));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdRed(VALUE self,VALUE v_color)
{
	char v;
	v = cdRed(NUM2LONG(v_color));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdGreen(VALUE self,VALUE v_color)
{
	char v;
	v = cdGreen(NUM2LONG(v_color));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdBlue(VALUE self,VALUE v_color)
{
	char v;
	v = cdBlue(NUM2LONG(v_color));
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdRGB2Map(VALUE self,VALUE v_width,VALUE v_height,VALUE v_red,VALUE v_green,VALUE v_blue,VALUE v_index,VALUE v_pal_size,VALUE v_color)
{
	int width = NUM2INT(v_width);
	int height = NUM2INT(v_height);
	const unsigned char* red = (unsigned char*)RSTRING_PTR(v_red);
	const unsigned char* green = (unsigned char*)RSTRING_PTR(v_green);
	const unsigned char* blue = (unsigned char*)RSTRING_PTR(v_blue);
	unsigned char* index = (unsigned char*)RSTRING_PTR(v_index);
	int pal_size = NUM2INT(v_pal_size);
	int i;
	long *color = xmalloc(RARRAY_LEN(v_color)*sizeof(long));
	for(i=0;i<RARRAY_LEN(v_color);i++)
		color[i] = NUM2LONG(RARRAY_PTR(v_color)[i]);
	cdRGB2Map(width,height,red,green,blue,index,pal_size,color);
	free(color);
	return Qnil;
}

VALUE rb_cdContextIup() 
{
	cdContext* v;
	v = cdContextIup();
	return ULONG2NUM((unsigned long)v);
}

VALUE rb_cdContextPDF() 
{
	cdContext* v;
	v = cdContextPDF();
	return ULONG2NUM((unsigned long)v);
}
