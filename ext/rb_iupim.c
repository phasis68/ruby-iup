#include <ruby.h>
#include "iup.h"
#include "rb_iup.h"

VALUE rb_IupLoadImage(VALUE self,VALUE v_file_name)
{
	extern VALUE rb_cIupImage;
	const char* file_name = RSTRING_PTR(v_file_name);
	Ihandle* v;
	v = IupLoadImage(file_name);
	if(v)
		return rb_funcall(rb_cIupImage,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupSaveImage(VALUE self,VALUE node,VALUE v_file_name,VALUE v_format)
{
	const char* file_name = RSTRING_PTR(v_file_name);
	const char* format = RSTRING_PTR(v_format);
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupSaveImage((Ihandle*)NUM2ULONG(v_ih),file_name,format);
	return INT2FIX((int)v);
}

