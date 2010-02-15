#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupSbox(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupSbox;
	Ihandle* v;
	VALUE v_ih; 	
	VALUE v_elem;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_elem = rb_hash_delete(argv[0],ID2SYM(rb_intern("elem")));
	} else {
		rb_scan_args(argc,argv,"10",&v_elem);
	}
	v_ih = rb_iv_get(v_elem,"@ihandle");
	v = IupSbox((Ihandle*)NUM2ULONG(v_ih));
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupSbox,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}
