#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupDial(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupDial;
	const char *type = NULL;
	Ihandle* v;
	VALUE v_type;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_type = rb_hash_delete(argv[0],ID2SYM(rb_intern("type")));
	} else {
		rb_scan_args(argc,argv,"10",&v_type);
	}
	if(v_type!=Qnil)
		type = RSTRING_PTR(v_type);
	IupControlsOpen();
	v = IupDial(type);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupDial,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}
