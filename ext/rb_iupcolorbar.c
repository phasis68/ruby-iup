#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupColorbar(VALUE self)
{
	extern VALUE rb_cIupColorbar;
	Ihandle* v;
	IupControlsOpen();
	v = IupColorbar();
	if(v)
		return rb_funcall(rb_cIupColorbar,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}
