#include <ruby.h>
#include "rb_iup.h"

static int PPlotOpen = 0;
VALUE rb_IupPPlotOpen(VALUE self)
{
	IupPPlotOpen();
	return Qnil;
}

VALUE rb_IupPPlot(VALUE self)
{
	extern VALUE rb_cIupPPlot;
	Ihandle* v;
	if(!PPlotOpen) {
		IupPPlotOpen();
		PPlotOpen = 1;
	}
	v = IupPPlot();
	if(v)
		return rb_funcall(rb_cIupPPlot,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupPPlotBegin(VALUE node,VALUE v_strXdata)
{
	int strXdata = NUM2INT(v_strXdata);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupPPlotBegin((Ihandle*)NUM2ULONG(v_ih),strXdata);
	return Qnil;
}

VALUE rb_IupPPlotAdd(VALUE node,VALUE v_x,VALUE v_y)
{
	float x,y;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	if(TYPE(v_x)==T_FIXNUM)
		x = NUM2INT(v_x);
	else
		x = RFLOAT_VALUE(v_x);
	if(TYPE(v_y)==T_FIXNUM)
		y = NUM2INT(v_y);
	else		
		y = RFLOAT_VALUE(v_y);
	IupPPlotAdd((Ihandle*)NUM2ULONG(v_ih),x,y);
	return Qnil;
}

VALUE rb_IupPPlotAddStr(VALUE node,VALUE v_x,VALUE v_y)
{
	float y;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	const char* x = RSTRING_PTR(v_x);
	if(TYPE(v_y)==T_FIXNUM)
		y = NUM2INT(v_y);
	else if(TYPE(v_y)==T_FLOAT)
		y = RFLOAT_VALUE(v_y);
	else
		y = 0;
	
	IupPPlotAddStr((Ihandle*)NUM2ULONG(v_ih),x,y);
	return Qnil;
}

VALUE rb_IupPPlotEnd(VALUE node)
{
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupPPlotEnd((Ihandle*)NUM2ULONG(v_ih));
	return INT2FIX(v);
}

VALUE rb_IupPPlotInsertStr(VALUE node,VALUE v_index,VALUE v_sample_index,VALUE v_x,VALUE v_y)
{
	float y;
	int index = NUM2INT(v_index);
	int sample_index = NUM2INT(v_sample_index);
	const char* x = RSTRING_PTR(v_x);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	y = RFLOAT_VALUE(v_y);
	IupPPlotInsertStr((Ihandle*)NUM2ULONG(v_ih),index,sample_index,x,y);
	return Qnil;
}

VALUE rb_IupPPlotInsert(VALUE node,VALUE v_index,VALUE v_sample_index,VALUE v_x,VALUE v_y)
{
	float x,y;
	int index = NUM2INT(v_index);
	int sample_index = NUM2INT(v_sample_index);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	if(TYPE(v_x)==T_FIXNUM)
		x = NUM2INT(v_x);
	else
		x = RFLOAT_VALUE(v_x);
	if(TYPE(v_y)==T_FIXNUM)
		y = NUM2INT(v_y);
	else		
		y = RFLOAT_VALUE(v_y);
	IupPPlotInsert((Ihandle*)NUM2ULONG(v_ih),index,sample_index,x,y);
	return Qnil;
}

VALUE rb_IupPPlotTransform(VALUE node,VALUE v_x,VALUE v_y)
{
	float x,y;
	int ix,iy;
	VALUE v_r;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	if(TYPE(v_x)==T_FIXNUM)
		x = NUM2INT(v_x);
	else
		x = RFLOAT_VALUE(v_x);
	if(TYPE(v_y)==T_FIXNUM)
		y = NUM2INT(v_y);
	else		
		y = RFLOAT_VALUE(v_y);
	IupPPlotTransform((Ihandle*)NUM2ULONG(v_ih),x,y,&ix,&iy);
	v_r = rb_ary_new3(2,INT2FIX(ix),INT2FIX(iy));
	return v_r;
}

VALUE rb_IupPPlotPaintTo(VALUE node,VALUE v_cnv)
{
	void* cnv = (void*)NUM2ULONG(v_cnv);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupPPlotPaintTo((Ihandle*)NUM2ULONG(v_ih),cnv);
	return Qnil;
}
