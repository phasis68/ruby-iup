#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupSpin(VALUE self)
{
	extern VALUE rb_cIupSpin;
	Ihandle* v;
	v = IupSpin();
	if(v)
		return rb_funcall(rb_cIupSpin,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupSpinbox(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupSpinbox;
	Ihandle* v;
	VALUE v_ctrl;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_ctrl = rb_hash_delete(argv[0],ID2SYM(rb_intern("ctrl")));
	} else {
		rb_scan_args(argc,argv,"10",&v_ctrl);
	}
	v = IupSpinbox((Ihandle*)NUM2ULONG(v_ctrl));
	if(v)
		return rb_funcall(rb_cIupSpinbox,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}
