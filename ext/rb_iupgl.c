#include <ruby.h>
#include "iup.h"
#include "rb_iup.h"

VALUE rb_IupGLCanvasOpen(VALUE self)
{
	IupGLCanvasOpen();
	return Qnil;
}

VALUE rb_IupGLCanvas(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupGLCanvas;
	const char *action = NULL;
	Ihandle* v;
	VALUE v_action;
        IupGLCanvasOpen();
	rb_scan_args(argc,argv,"01",&v_action);
	if(v_action!=Qnil) action = RSTRING_PTR(v_action);
	v = IupGLCanvas(action);
	if(v)
		return rb_funcall(rb_cIupGLCanvas,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupGLMakeCurrent(VALUE self,VALUE node)
{
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupGLMakeCurrent((Ihandle*)NUM2ULONG(v_ih));
	return Qnil;
}

VALUE rb_IupGLIsCurrent(VALUE self,VALUE node)
{
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupGLIsCurrent((Ihandle*)NUM2ULONG(v_ih));
	return INT2FIX((int)v);
}

VALUE rb_IupGLSwapBuffers(VALUE self,VALUE node)
{
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupGLSwapBuffers((Ihandle*)NUM2ULONG(v_ih));
	return Qnil;
}

VALUE rb_IupGLPalette(VALUE self,VALUE node,VALUE v_index,VALUE v_r,VALUE v_g,VALUE v_b)
{
	float r,g,b;
	int index = NUM2INT(v_index);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	r = RFLOAT_VALUE(v_r);
	g = RFLOAT_VALUE(v_g);
	b = RFLOAT_VALUE(v_b);
	IupGLPalette((Ihandle*)NUM2ULONG(v_ih),index,r,g,b);
	return Qnil;
}
