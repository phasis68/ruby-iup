#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupColorBrowser(VALUE self)
{
	extern VALUE rb_cIupColorBrowser;
	Ihandle* v;
	IupControlsOpen();
	v = IupColorBrowser();
	if(v)
		return rb_funcall(rb_cIupColorBrowser,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}
