#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupTabsv(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupTabs;
	Ihandle* v;
	Ihandle* params[100];
	int i;
	VALUE node;
	VALUE v_params,v_hash;
	rb_scan_args(argc,argv,"11",&v_params,&v_hash);
	for(i=0;i<RARRAY_LEN(v_params) && i<100;i++) {
		node = RARRAY_PTR(v_params)[i];
		if(node==Qnil)
	  		params[i] = NULL;
	  	else
	  		params[i] = (Ihandle*)NUM2ULONG(rb_iv_get(node,"@ihandle"));	
	}
	params[i] = NULL;
	IupControlsOpen();
	v = IupTabsv(params);
	if(TYPE(v_hash)==T_HASH) 
		rb_set_attribute(v,v_hash);	
	if(v)
		return rb_funcall(rb_cIupTabs,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

