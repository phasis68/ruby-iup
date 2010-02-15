#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupGauge(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupGauge;
	Ihandle* v;
	IupControlsOpen();
	v = IupGauge();
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupGauge,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}
