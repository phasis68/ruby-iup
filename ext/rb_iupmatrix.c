#include <ruby.h>
#include "rb_iup.h"

VALUE rb_IupMatrix(int argc,VALUE *argv,VALUE self)
{
	extern VALUE rb_cIupMatrix;
	char *action = NULL;
	Ihandle* v;
	VALUE v_action;
	if(argc==1 && TYPE(argv[0])==T_HASH) {
		v_action = rb_hash_delete(argv[0],ID2SYM(rb_intern("action")));
	} else {
		rb_scan_args(argc,argv,"01",&v_action);
	}
	if(v_action!=Qnil)
		action = RSTRING_PTR(v_action);
	IupControlsOpen();
	v = IupMatrix(action);
	if(argc==1 && TYPE(argv[0])==T_HASH)
		rb_set_attribute(v,argv[0]);	
	if(v)
		return rb_funcall(rb_cIupMatrix,rb_intern("new"),1,ULONG2NUM((unsigned long)v));
	return Qnil;
}

VALUE rb_IupMatSetAttribute(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c,VALUE v_v)
{
	const char* a = RSTRING_PTR(v_a);
	int l = NUM2INT(v_l);
	int c = NUM2INT(v_c);
	char* v = RSTRING_PTR(v_v);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupMatSetAttribute((Ihandle*)NUM2ULONG(v_ih),a,l,c,v);
	return Qnil;
}

VALUE rb_IupMatStoreAttribute(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c,VALUE v_v)
{
	const char* a = RSTRING_PTR(v_a);
	int l = NUM2INT(v_l);
	int c = NUM2INT(v_c);
	char* v = RSTRING_PTR(v_v);
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	IupMatStoreAttribute((Ihandle*)NUM2ULONG(v_ih),a,l,c,v);
	return Qnil;
}

VALUE rb_IupMatGetAttribute(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c)
{
	const char* a = RSTRING_PTR(v_a);
	int l = NUM2INT(v_l);
	int c = NUM2INT(v_c);
	char* v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupMatGetAttribute((Ihandle*)NUM2ULONG(v_ih),a,l,c);
	return  rb_str_new2(v);
}

VALUE rb_IupMatGetInt(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c)
{
	const char* a = RSTRING_PTR(v_a);
	int l = NUM2INT(v_l);
	int c = NUM2INT(v_c);
	int v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupMatGetInt((Ihandle*)NUM2ULONG(v_ih),a,l,c);
	return INT2FIX(v);
}

VALUE rb_IupMatGetFloat(VALUE node,VALUE v_a,VALUE v_l,VALUE v_c)
{
	const char* a = RSTRING_PTR(v_a);
	int l = NUM2INT(v_l);
	int c = NUM2INT(v_c);
	float v;
	VALUE v_ih = rb_iv_get(node,"@ihandle");
	v = IupMatGetFloat((Ihandle*)NUM2ULONG(v_ih),a,l,c);
	return INT2FIX(v);
}

