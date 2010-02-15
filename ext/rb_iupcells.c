#include <ruby.h>
#include "rb_iup.h"
 
void rb_set_attribute(Ihandle *v,VALUE arg);
VALUE rb_IupCells(int argc,VALUE *argv, VALUE self)
{
	extern VALUE rb_cIupCells;	
	Ihandle* v;
	IupControlsOpen();
	v = IupCells();
        if(argc==1 && TYPE(argv[0])==T_HASH)
                rb_set_attribute(v,argv[0]);
	if(v)
		return rb_funcall(rb_cIupCells,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}
