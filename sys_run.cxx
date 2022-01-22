#pragma once

#define __SYSDEF__
//#define _TS 9999999999
#define _TS 10000000016

#if _TS == 9999999999 && __has_include("LLR_CCorder_9999999999.h")
#   include "LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("LLR_CCorder_10000000016.h")
#   include "LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#	include "./BDT/bininfo.h"
#   define ana_bm ana_bm_comb
#endif

#include "doConstraintFit_SYSBDTERR_v2.cxx"
#include "doConstraintFit_SYSBDTERR_v2_Seff.cxx"
#include "doConstraintFit_SYSBDTERR_v2_Prop.cxx"
#include "doConstraintFit_SYSBDTERR_v2_SCAN.cxx"
#include "doConstraintFit_SYSSIGPAR_v2.cxx"
#include "doConstraintFit_SYSHFBDT_v2.cxx"
#include "doConstraintFit_SYSSIGPDF_v2.cxx"

void sys_run(string type, int global_step =1, int step = 111){
	if(strcmp(type.c_str(),"BDT")==0) doConstraintFit_SYSBDTERR_v2(global_step, step);
	if(strcmp(type.c_str(),"BDTSEFF")==0) doConstraintFit_SYSBDTERR_v2_Seff(global_step, step);
	if(strcmp(type.c_str(),"BDTSCAN")==0) doConstraintFit_SYSBDTERR_v2_SCAN(global_step, step);
	if(strcmp(type.c_str(),"BDTPROP")==0) doConstraintFit_SYSBDTERR_v2_Prop(global_step, step);
	if(strcmp(type.c_str(),"PAR")==0) doConstraintFit_SYSSIGPAR_v2(step);
	if(strcmp(type.c_str(),"PDF")==0) doConstraintFit_SYSSIGPDF_v2(step);
	if(strcmp(type.c_str(),"HF")==0) doConstraintFit_SYSHFBDT_v2(global_step, step);
};