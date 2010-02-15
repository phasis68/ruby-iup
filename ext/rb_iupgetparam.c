#include <ruby.h>
#include "rb_iup.h"

static char ParamAction[100];
extern VALUE rb_cIupNode;

static int _param_action(Ihandle* dialog, int param_index, void* user_data)
{
	VALUE v;
	VALUE node;
	node = rb_funcall(rb_cIupNode,rb_intern("new"),1,ULONG2NUM((unsigned long)dialog));
	v = rb_funcall(rb_cObject,rb_intern(ParamAction),3,node,INT2FIX(param_index),ULONG2NUM((unsigned long)user_data));
	return NUM2INT(v);
}

VALUE rb_IupGetParam(int argc,VALUE *argv,VALUE self)
{
	extern int iupGetParamCount(const char *format, int *param_extra);

	const char* title = RSTRING_PTR(argv[0]);
	Iparamcb action = NULL;
	void* user_data = (void*)NUM2INT(argv[2]);
	const char* format = RSTRING_PTR(argv[3]);
	int param_count;
	int param_extra;
	void *param_data[50];
	int i,v;
        int n[50];
        float d[50];
        static char s[50][500];
        VALUE v_r;
	if(argv[1]!=Qnil) {
		strcpy(ParamAction,RSTRING_PTR(argv[1]));
		action = (Iparamcb)_param_action;	
	}
        param_count = iupGetParamCount(format, &param_extra);
        for(i=0;i<param_count && i+4<argc;i++) {
        	switch(TYPE(argv[i+4])) {
        		case T_FIXNUM:
        		case T_BIGNUM:
        			n[i] = NUM2INT(argv[i+4]);
        			param_data[i] = (void*)&n[i];
        			break;
        		case T_FLOAT:
        			d[i] = RFLOAT_VALUE(argv[i+4]);
        			param_data[i] = (void*)&d[i];
        			break;
        		case T_STRING:
        			strcpy(s[i],RSTRING_PTR(argv[i+4]));
        			param_data[i] = s[i];
        			break;
        	}        	
	}
	param_data[i] = NULL;
	v = IupGetParamv(title,action,user_data,format,param_count,param_extra,param_data);
	v_r = rb_ary_new();
	for(i=0;i<param_count;i++) {
        	switch(TYPE(argv[i+4])) {
        		case T_FIXNUM:
        		case T_BIGNUM:
        			rb_ary_push(v_r,INT2NUM(n[i]));
        			break;
        		case T_FLOAT:
        			sprintf(s[i],"%g",d[i]);
        			rb_ary_push(v_r,rb_float_new(atof(s[i])));
        			break;
        		case T_STRING:
        			rb_ary_push(v_r,rb_str_new2(s[i]));
        			break;
        	}        	
	}
	return v_r;
}

