#define _M_IX86 400#define WIN32#define __STDC__ 0#define _WIN32#define _RELEASE#define _CONSOLE#define _UNICODE#define UNICODE

#define _M_IX86#define __stdcall#define __fastcall#define __pragma(x)  #define __inline  #define  __cdecl  #define __declspec(x)          #define __int64 long long



#pragma dir #pragma dir #pragma dir #pragma dir #pragma dir #pragma dir #pragma dir 



#include <stdio.h>













#pragma once#define _INC_STDIO

#include <corecrt.h>













#pragma once

#include <vcruntime.h>







































#ifndef _UCRT    #define _UCRT#endif









#ifndef _CRTIMP    #define _VCRT_DEFINED_CRTIMP    #if defined CRTDLL && defined _CRTBLD        define _CRTIMP __declspec(dllexport)

    #else        #ifdef _DLL            define _CRTIMP __declspec(dllimport)

        #else            #define _CRTIMP        #endif    #endif#endif

#ifndef _VCRUNTIME_H#define _VCRUNTIME_H

#include <sal.h>

#pragma once





#define __ATTR_SAL

#ifndef _SAL_VERSION#define _SAL_VERSION 20#endif

#ifndef __SAL_H_VERSION#define __SAL_H_VERSION 180000000#endif

#ifdef _PREFAST_ // [



#ifndef _USE_DECLSPECS_FOR_SAL // [define _USE_DECLSPECS_FOR_SAL 1

#endif // ]

#if _USE_DECLSPECS_FOR_SAL // [undef _USE_ATTRIBUTES_FOR_SAL

define _USE_ATTRIBUTES_FOR_SAL 0

#elif !defined(_USE_ATTRIBUTES_FOR_SAL) // ][#if _MSC_VER >= 1400 // [define _USE_ATTRIBUTES_FOR_SAL 1

#else // ][define _USE_ATTRIBUTES_FOR_SAL 0

#endif // ]#endif // ]



#if !_USE_DECLSPECS_FOR_SAL // [#if !_USE_ATTRIBUTES_FOR_SAL // [#if _MSC_VER >= 1400 // [undef _USE_ATTRIBUTES_FOR_SAL

define _USE_ATTRIBUTES_FOR_SAL 1

#else // ][undef _USE_DECLSPECS_FOR_SAL

define _USE_DECLSPECS_FOR_SAL  1

#endif // ]#endif // ]#endif // ]

#else





#ifndef _USE_DECLSPECS_FOR_SAL // [#define _USE_DECLSPECS_FOR_SAL 0#endif // ]#ifndef _USE_ATTRIBUTES_FOR_SAL // [#define _USE_ATTRIBUTES_FOR_SAL 0#endif // ]

#endif // ]



#if _USE_DECLSPECS_FOR_SAL && ( defined( MIDL_PASS ) || defined(__midl) || defined(RC_INVOKED) || !defined(_PREFAST_) ) // [undef _USE_DECLSPECS_FOR_SAL

define _USE_DECLSPECS_FOR_SAL 0

#endif // ]#if _USE_ATTRIBUTES_FOR_SAL && ( !defined(_MSC_EXTENSIONS) || defined( MIDL_PASS ) || defined(__midl) || defined(RC_INVOKED) ) // [undef _USE_ATTRIBUTES_FOR_SAL

define _USE_ATTRIBUTES_FOR_SAL 0

#endif // ]

#if _USE_DECLSPECS_FOR_SAL || _USE_ATTRIBUTES_FOR_SAL



enum __SAL_YesNo {_SAL_notpresent, _SAL_no, _SAL_maybe, _SAL_yes, _SAL_default};



#endif

#if defined(BUILD_WINDOWS) && !_USE_ATTRIBUTES_FOR_SAL define _SAL1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1") _GrouP_(annotes _SAL_nop_impl_)

define _SAL1_1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.1") _GrouP_(annotes _SAL_nop_impl_)

define _SAL1_2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.2") _GrouP_(annotes _SAL_nop_impl_)

define _SAL2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _GrouP_(annotes _SAL_nop_impl_)



#ifndef _SAL_L_Source_

define _SAL_L_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _GrouP_(annotes _SAL_nop_impl_)

#endif #else#define _SAL1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1") _Group_(annotes _SAL_nop_impl_)#define _SAL1_1_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.1") _Group_(annotes _SAL_nop_impl_)#define _SAL1_2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "1.2") _Group_(annotes _SAL_nop_impl_)#define _SAL2_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _Group_(annotes _SAL_nop_impl_)

#ifndef _SAL_L_Source_

#define _SAL_L_Source_(Name, args, annotes) _SA_annotes3(SAL_name, #Name, "", "2") _Group_(annotes _SAL_nop_impl_)#endif #endif























#define _At_(target, annos)            _At_impl_(target, annos _SAL_nop_impl_)









#define _At_buffer_(target, iter, bound, annos)  _At_buffer_impl_(target, iter, bound, annos _SAL_nop_impl_)





#define _When_(expr, annos)            _When_impl_(expr, annos _SAL_nop_impl_)#define _Group_(annos)                 _Group_impl_(annos _SAL_nop_impl_)#define _GrouP_(annos)                 _GrouP_impl_(annos _SAL_nop_impl_)



#define _Success_(expr)                  _SAL2_Source_(_Success_, (expr), _Success_impl_(expr))





#define _Return_type_success_(expr)      _SAL2_Source_(_Return_type_success_, (expr), _Success_impl_(expr))



#define _On_failure_(annos)              _On_failure_impl_(annos _SAL_nop_impl_)





#define _Always_(annos)                  _Always_impl_(annos _SAL_nop_impl_)







#define _Use_decl_annotations_         _Use_decl_anno_impl_







#define _Notref_                       _Notref_impl_



#define _Pre_defensive_             _SA_annotes0(SAL_pre_defensive)#define _Post_defensive_            _SA_annotes0(SAL_post_defensive)

#define _In_defensive_(annotes)     _Pre_defensive_ _Group_(annotes _SAL_nop_impl_)#define _Out_defensive_(annotes)    _Post_defensive_ _Group_(annotes _SAL_nop_impl_)#define _Inout_defensive_(annotes)  _Pre_defensive_ _Post_defensive_ _Group_(annotes _SAL_nop_impl_)











#define _Reserved_                      _SAL2_Source_(_Reserved_, (), _Pre1_impl_(__null_impl))





#define _Const_                         _SAL2_Source_(_Const_, (), _Pre1_impl_(__readaccess_impl_notref))















#define _In_                            _SAL2_Source_(_In_, (), _Pre1_impl_(__notnull_impl_notref) _Pre_valid_impl_ _Deref_pre1_impl_(__readaccess_impl_notref))#define _In_opt_                        _SAL2_Source_(_In_opt_, (), _Pre1_impl_(__maybenull_impl_notref) _Pre_valid_impl_ _Deref_pre_readonly_)





#define _In_z_                          _SAL2_Source_(_In_z_, (),     _In_     _Pre1_impl_(__zterm_impl))#define _In_opt_z_                      _SAL2_Source_(_In_opt_z_, (), _In_opt_ _Pre1_impl_(__zterm_impl))







#define _In_reads_(size)               _SAL2_Source_(_In_reads_, (size), _Pre_count_(size)          _Deref_pre_readonly_)#define _In_reads_opt_(size)           _SAL2_Source_(_In_reads_opt_, (size), _Pre_opt_count_(size)      _Deref_pre_readonly_)#define _In_reads_bytes_(size)         _SAL2_Source_(_In_reads_bytes_, (size), _Pre_bytecount_(size)      _Deref_pre_readonly_)#define _In_reads_bytes_opt_(size)     _SAL2_Source_(_In_reads_bytes_opt_, (size), _Pre_opt_bytecount_(size)  _Deref_pre_readonly_)#define _In_reads_z_(size)             _SAL2_Source_(_In_reads_z_, (size), _In_reads_(size)     _Pre_z_)#define _In_reads_opt_z_(size)         _SAL2_Source_(_In_reads_opt_z_, (size), _Pre_opt_count_(size)      _Deref_pre_readonly_     _Pre_opt_z_)#define _In_reads_or_z_(size)          _SAL2_Source_(_In_reads_or_z_, (size), _In_ _When_(_String_length_(_Curr_) < (size), _Pre_z_) _When_(_String_length_(_Curr_) >= (size), _Pre1_impl_(__count_impl(size))))#define _In_reads_or_z_opt_(size)      _SAL2_Source_(_In_reads_or_z_opt_, (size), _In_opt_ _When_(_String_length_(_Curr_) < (size), _Pre_z_) _When_(_String_length_(_Curr_) >= (size), _Pre1_impl_(__count_impl(size))))







#define _In_reads_to_ptr_(ptr)         _SAL2_Source_(_In_reads_to_ptr_, (ptr), _Pre_ptrdiff_count_(ptr)     _Deref_pre_readonly_)#define _In_reads_to_ptr_opt_(ptr)     _SAL2_Source_(_In_reads_to_ptr_opt_, (ptr), _Pre_opt_ptrdiff_count_(ptr) _Deref_pre_readonly_)#define _In_reads_to_ptr_z_(ptr)       _SAL2_Source_(_In_reads_to_ptr_z_, (ptr), _In_reads_to_ptr_(ptr) _Pre_z_)#define _In_reads_to_ptr_opt_z_(ptr)   _SAL2_Source_(_In_reads_to_ptr_opt_z_, (ptr), _Pre_opt_ptrdiff_count_(ptr) _Deref_pre_readonly_  _Pre_opt_z_)



















#define _Out_                                  _SAL2_Source_(_Out_, (),     _Out_impl_)#define _Out_opt_                              _SAL2_Source_(_Out_opt_, (), _Out_opt_impl_)

#define _Out_writes_(size)                     _SAL2_Source_(_Out_writes_, (size), _Pre_cap_(size)            _Post_valid_impl_)#define _Out_writes_opt_(size)                 _SAL2_Source_(_Out_writes_opt_, (size), _Pre_opt_cap_(size)        _Post_valid_impl_)#define _Out_writes_bytes_(size)               _SAL2_Source_(_Out_writes_bytes_, (size), _Pre_bytecap_(size)        _Post_valid_impl_)#define _Out_writes_bytes_opt_(size)           _SAL2_Source_(_Out_writes_bytes_opt_, (size), _Pre_opt_bytecap_(size)    _Post_valid_impl_)#define _Out_writes_z_(size)                   _SAL2_Source_(_Out_writes_z_, (size), _Pre_cap_(size)            _Post_valid_impl_ _Post_z_)#define _Out_writes_opt_z_(size)               _SAL2_Source_(_Out_writes_opt_z_, (size), _Pre_opt_cap_(size)        _Post_valid_impl_ _Post_z_)

#define _Out_writes_to_(size,count)            _SAL2_Source_(_Out_writes_to_, (size,count), _Pre_cap_(size)            _Post_valid_impl_ _Post_count_(count))#define _Out_writes_to_opt_(size,count)        _SAL2_Source_(_Out_writes_to_opt_, (size,count), _Pre_opt_cap_(size)        _Post_valid_impl_ _Post_count_(count))#define _Out_writes_all_(size)                 _SAL2_Source_(_Out_writes_all_, (size), _Out_writes_to_(_Old_(size), _Old_(size)))#define _Out_writes_all_opt_(size)             _SAL2_Source_(_Out_writes_all_opt_, (size), _Out_writes_to_opt_(_Old_(size), _Old_(size)))

#define _Out_writes_bytes_to_(size,count)      _SAL2_Source_(_Out_writes_bytes_to_, (size,count), _Pre_bytecap_(size)        _Post_valid_impl_ _Post_bytecount_(count))#define _Out_writes_bytes_to_opt_(size,count)  _SAL2_Source_(_Out_writes_bytes_to_opt_, (size,count), _Pre_opt_bytecap_(size) _Post_valid_impl_ _Post_bytecount_(count))#define _Out_writes_bytes_all_(size)           _SAL2_Source_(_Out_writes_bytes_all_, (size), _Out_writes_bytes_to_(_Old_(size), _Old_(size)))#define _Out_writes_bytes_all_opt_(size)       _SAL2_Source_(_Out_writes_bytes_all_opt_, (size), _Out_writes_bytes_to_opt_(_Old_(size), _Old_(size)))

#define _Out_writes_to_ptr_(ptr)               _SAL2_Source_(_Out_writes_to_ptr_, (ptr), _Pre_ptrdiff_cap_(ptr)     _Post_valid_impl_)#define _Out_writes_to_ptr_opt_(ptr)           _SAL2_Source_(_Out_writes_to_ptr_opt_, (ptr), _Pre_opt_ptrdiff_cap_(ptr) _Post_valid_impl_)#define _Out_writes_to_ptr_z_(ptr)             _SAL2_Source_(_Out_writes_to_ptr_z_, (ptr), _Pre_ptrdiff_cap_(ptr)     _Post_valid_impl_ Post_z_)#define _Out_writes_to_ptr_opt_z_(ptr)         _SAL2_Source_(_Out_writes_to_ptr_opt_z_, (ptr), _Pre_opt_ptrdiff_cap_(ptr) _Post_valid_impl_ Post_z_)

















#define _Inout_                                _SAL2_Source_(_Inout_, (), _Prepost_valid_)#define _Inout_opt_                            _SAL2_Source_(_Inout_opt_, (), _Prepost_opt_valid_)





#define _Inout_z_                              _SAL2_Source_(_Inout_z_, (), _Prepost_z_)#define _Inout_opt_z_                          _SAL2_Source_(_Inout_opt_z_, (), _Prepost_opt_z_)



#define _Inout_updates_(size)                  _SAL2_Source_(_Inout_updates_, (size), _Pre_cap_(size)         _Pre_valid_impl_ _Post_valid_impl_)#define _Inout_updates_opt_(size)              _SAL2_Source_(_Inout_updates_opt_, (size), _Pre_opt_cap_(size)     _Pre_valid_impl_ _Post_valid_impl_)#define _Inout_updates_z_(size)                _SAL2_Source_(_Inout_updates_z_, (size), _Pre_cap_(size)         _Pre_valid_impl_ _Post_valid_impl_ _Pre1_impl_(__zterm_impl) _Post1_impl_(__zterm_impl))#define _Inout_updates_opt_z_(size)            _SAL2_Source_(_Inout_updates_opt_z_, (size), _Pre_opt_cap_(size)     _Pre_valid_impl_ _Post_valid_impl_ _Pre1_impl_(__zterm_impl) _Post1_impl_(__zterm_impl))

#define _Inout_updates_to_(size,count)         _SAL2_Source_(_Inout_updates_to_, (size,count), _Out_writes_to_(size,count) _Pre_valid_impl_ _Pre1_impl_(__count_impl(size)))#define _Inout_updates_to_opt_(size,count)     _SAL2_Source_(_Inout_updates_to_opt_, (size,count), _Out_writes_to_opt_(size,count) _Pre_valid_impl_ _Pre1_impl_(__count_impl(size)))

#define _Inout_updates_all_(size)              _SAL2_Source_(_Inout_updates_all_, (size), _Inout_updates_to_(_Old_(size), _Old_(size)))#define _Inout_updates_all_opt_(size)          _SAL2_Source_(_Inout_updates_all_opt_, (size), _Inout_updates_to_opt_(_Old_(size), _Old_(size)))



#define _Inout_updates_bytes_(size)            _SAL2_Source_(_Inout_updates_bytes_, (size), _Pre_bytecap_(size)     _Pre_valid_impl_ _Post_valid_impl_)#define _Inout_updates_bytes_opt_(size)        _SAL2_Source_(_Inout_updates_bytes_opt_, (size), _Pre_opt_bytecap_(size) _Pre_valid_impl_ _Post_valid_impl_)

#define _Inout_updates_bytes_to_(size,count)       _SAL2_Source_(_Inout_updates_bytes_to_, (size,count), _Out_writes_bytes_to_(size,count) _Pre_valid_impl_ _Pre1_impl_(__bytecount_impl(size)))#define _Inout_updates_bytes_to_opt_(size,count)   _SAL2_Source_(_Inout_updates_bytes_to_opt_, (size,count), _Out_writes_bytes_to_opt_(size,count) _Pre_valid_impl_ _Pre1_impl_(__bytecount_impl(size)))

#define _Inout_updates_bytes_all_(size)        _SAL2_Source_(_Inout_updates_bytes_all_, (size), _Inout_updates_bytes_to_(_Old_(size), _Old_(size)))#define _Inout_updates_bytes_all_opt_(size)    _SAL2_Source_(_Inout_updates_bytes_all_opt_, (size), _Inout_updates_bytes_to_opt_(_Old_(size), _Old_(size)))







































#define _Outptr_                         _SAL2_Source_(_Outptr_, (),                      _Out_impl_     _Deref_post2_impl_(__notnull_impl_notref,   __count_impl(1)))#define _Outptr_result_maybenull_        _SAL2_Source_(_Outptr_result_maybenull_, (),     _Out_impl_     _Deref_post2_impl_(__maybenull_impl_notref, __count_impl(1)))#define _Outptr_opt_                     _SAL2_Source_(_Outptr_opt_, (),                  _Out_opt_impl_ _Deref_post2_impl_(__notnull_impl_notref,   __count_impl(1)))#define _Outptr_opt_result_maybenull_    _SAL2_Source_(_Outptr_opt_result_maybenull_, (), _Out_opt_impl_ _Deref_post2_impl_(__maybenull_impl_notref, __count_impl(1)))





#define _Outptr_result_z_                _SAL2_Source_(_Outptr_result_z_, (),               _Out_impl_     _Deref_post_z_)#define _Outptr_opt_result_z_            _SAL2_Source_(_Outptr_opt_result_z_, (),           _Out_opt_impl_ _Deref_post_z_)#define _Outptr_result_maybenull_z_      _SAL2_Source_(_Outptr_result_maybenull_z_, (),     _Out_impl_     _Deref_post_opt_z_)#define _Outptr_opt_result_maybenull_z_  _SAL2_Source_(_Outptr_opt_result_maybenull_z_, (), _Out_opt_impl_ _Deref_post_opt_z_)





#define _Outptr_result_nullonfailure_       _SAL2_Source_(_Outptr_result_nullonfailure_, (),     _Outptr_      _On_failure_(_Deref_post_null_))#define _Outptr_opt_result_nullonfailure_   _SAL2_Source_(_Outptr_opt_result_nullonfailure_, (), _Outptr_opt_  _On_failure_(_Deref_post_null_))











#define _COM_Outptr_                        _SAL2_Source_(_COM_Outptr_, (),                      _Outptr_                      _On_failure_(_Deref_post_null_))#define _COM_Outptr_result_maybenull_       _SAL2_Source_(_COM_Outptr_result_maybenull_, (),     _Outptr_result_maybenull_     _On_failure_(_Deref_post_null_))#define _COM_Outptr_opt_                    _SAL2_Source_(_COM_Outptr_opt_, (),                  _Outptr_opt_                  _On_failure_(_Deref_post_null_))#define _COM_Outptr_opt_result_maybenull_   _SAL2_Source_(_COM_Outptr_opt_result_maybenull_, (), _Outptr_opt_result_maybenull_ _On_failure_(_Deref_post_null_))





#define _Outptr_result_buffer_(size)                      _SAL2_Source_(_Outptr_result_buffer_, (size),               _Out_impl_     _Deref_post2_impl_(__notnull_impl_notref, __cap_impl(size)))#define _Outptr_opt_result_buffer_(size)                  _SAL2_Source_(_Outptr_opt_result_buffer_, (size),           _Out_opt_impl_ _Deref_post2_impl_(__notnull_impl_notref, __cap_impl(size)))#define _Outptr_result_buffer_to_(size, count)            _SAL2_Source_(_Outptr_result_buffer_to_, (size, count),     _Out_impl_     _Deref_post3_impl_(__notnull_impl_notref, __cap_impl(size), __count_impl(count)))#define _Outptr_opt_result_buffer_to_(size, count)        _SAL2_Source_(_Outptr_opt_result_buffer_to_, (size, count), _Out_opt_impl_ _Deref_post3_impl_(__notnull_impl_notref, __cap_impl(size), __count_impl(count)))

#define _Outptr_result_buffer_all_(size)                  _SAL2_Source_(_Outptr_result_buffer_all_, (size),           _Out_impl_     _Deref_post2_impl_(__notnull_impl_notref, __count_impl(size)))#define _Outptr_opt_result_buffer_all_(size)              _SAL2_Source_(_Outptr_opt_result_buffer_all_, (size),       _Out_opt_impl_ _Deref_post2_impl_(__notnull_impl_notref, __count_impl(size)))

#define _Outptr_result_buffer_maybenull_(size)               _SAL2_Source_(_Outptr_result_buffer_maybenull_, (size),               _Out_impl_     _Deref_post2_impl_(__maybenull_impl_notref, __cap_impl(size)))#define _Outptr_opt_result_buffer_maybenull_(size)           _SAL2_Source_(_Outptr_opt_result_buffer_maybenull_, (size),           _Out_opt_impl_ _Deref_post2_impl_(__maybenull_impl_notref, __cap_impl(size)))#define _Outptr_result_buffer_to_maybenull_(size, count)     _SAL2_Source_(_Outptr_result_buffer_to_maybenull_, (size, count),     _Out_impl_     _Deref_post3_impl_(__maybenull_impl_notref, __cap_impl(size), __count_impl(count)))#define _Outptr_opt_result_buffer_to_maybenull_(size, count) _SAL2_Source_(_Outptr_opt_result_buffer_to_maybenull_, (size, count), _Out_opt_impl_ _Deref_post3_impl_(__maybenull_impl_notref, __cap_impl(size), __count_impl(count)))

#define _Outptr_result_buffer_all_maybenull_(size)           _SAL2_Source_(_Outptr_result_buffer_all_maybenull_, (size),           _Out_impl_     _Deref_post2_impl_(__maybenull_impl_notref, __count_impl(size)))#define _Outptr_opt_result_buffer_all_maybenull_(size)       _SAL2_Source_(_Outptr_opt_result_buffer_all_maybenull_, (size),       _Out_opt_impl_ _Deref_post2_impl_(__maybenull_impl_notref, __count_impl(size)))

#define _Outptr_result_bytebuffer_(size)                     _SAL2_Source_(_Outptr_result_bytebuffer_, (size),                     _Out_impl_     _Deref_post2_impl_(__notnull_impl_notref, __bytecap_impl(size)))#define _Outptr_opt_result_bytebuffer_(size)                 _SAL2_Source_(_Outptr_opt_result_bytebuffer_, (size),                 _Out_opt_impl_ _Deref_post2_impl_(__notnull_impl_notref, __bytecap_impl(size)))#define _Outptr_result_bytebuffer_to_(size, count)           _SAL2_Source_(_Outptr_result_bytebuffer_to_, (size, count),           _Out_impl_     _Deref_post3_impl_(__notnull_impl_notref, __bytecap_impl(size), __bytecount_impl(count)))#define _Outptr_opt_result_bytebuffer_to_(size, count)       _SAL2_Source_(_Outptr_opt_result_bytebuffer_to_, (size, count),       _Out_opt_impl_ _Deref_post3_impl_(__notnull_impl_notref, __bytecap_impl(size), __bytecount_impl(count)))

#define _Outptr_result_bytebuffer_all_(size)                 _SAL2_Source_(_Outptr_result_bytebuffer_all_, (size),                 _Out_impl_     _Deref_post2_impl_(__notnull_impl_notref, __bytecount_impl(size)))#define _Outptr_opt_result_bytebuffer_all_(size)             _SAL2_Source_(_Outptr_opt_result_bytebuffer_all_, (size),             _Out_opt_impl_ _Deref_post2_impl_(__notnull_impl_notref, __bytecount_impl(size)))

#define _Outptr_result_bytebuffer_maybenull_(size)                 _SAL2_Source_(_Outptr_result_bytebuffer_maybenull_, (size),               _Out_impl_     _Deref_post2_impl_(__maybenull_impl_notref, __bytecap_impl(size)))#define _Outptr_opt_result_bytebuffer_maybenull_(size)             _SAL2_Source_(_Outptr_opt_result_bytebuffer_maybenull_, (size),           _Out_opt_impl_ _Deref_post2_impl_(__maybenull_impl_notref, __bytecap_impl(size)))#define _Outptr_result_bytebuffer_to_maybenull_(size, count)       _SAL2_Source_(_Outptr_result_bytebuffer_to_maybenull_, (size, count),     _Out_impl_     _Deref_post3_impl_(__maybenull_impl_notref, __bytecap_impl(size), __bytecount_impl(count)))#define _Outptr_opt_result_bytebuffer_to_maybenull_(size, count)   _SAL2_Source_(_Outptr_opt_result_bytebuffer_to_maybenull_, (size, count), _Out_opt_impl_ _Deref_post3_impl_(__maybenull_impl_notref, __bytecap_impl(size), __bytecount_impl(count)))

#define _Outptr_result_bytebuffer_all_maybenull_(size)         _SAL2_Source_(_Outptr_result_bytebuffer_all_maybenull_, (size),               _Out_impl_     _Deref_post2_impl_(__maybenull_impl_notref, __bytecount_impl(size)))#define _Outptr_opt_result_bytebuffer_all_maybenull_(size)     _SAL2_Source_(_Outptr_opt_result_bytebuffer_all_maybenull_, (size),           _Out_opt_impl_ _Deref_post2_impl_(__maybenull_impl_notref, __bytecount_impl(size)))





#define _Outref_                                               _SAL2_Source_(_Outref_, (),                  _Out_impl_ _Post_notnull_)#define _Outref_result_maybenull_                              _SAL2_Source_(_Outref_result_maybenull_, (), _Pre2_impl_(__notnull_impl_notref, __cap_c_one_notref_impl) _Post_maybenull_ _Post_valid_impl_)

#define _Outref_result_buffer_(size)                           _SAL2_Source_(_Outref_result_buffer_, (size),                         _Outref_ _Post1_impl_(__cap_impl(size)))#define _Outref_result_bytebuffer_(size)                       _SAL2_Source_(_Outref_result_bytebuffer_, (size),                     _Outref_ _Post1_impl_(__bytecap_impl(size)))#define _Outref_result_buffer_to_(size, count)                 _SAL2_Source_(_Outref_result_buffer_to_, (size, count),               _Outref_result_buffer_(size) _Post1_impl_(__count_impl(count)))#define _Outref_result_bytebuffer_to_(size, count)             _SAL2_Source_(_Outref_result_bytebuffer_to_, (size, count),           _Outref_result_bytebuffer_(size) _Post1_impl_(__bytecount_impl(count)))#define _Outref_result_buffer_all_(size)                       _SAL2_Source_(_Outref_result_buffer_all_, (size),                     _Outref_result_buffer_to_(size, _Old_(size)))#define _Outref_result_bytebuffer_all_(size)                   _SAL2_Source_(_Outref_result_bytebuffer_all_, (size),                 _Outref_result_bytebuffer_to_(size, _Old_(size)))

#define _Outref_result_buffer_maybenull_(size)                 _SAL2_Source_(_Outref_result_buffer_maybenull_, (size),               _Outref_result_maybenull_ _Post1_impl_(__cap_impl(size)))#define _Outref_result_bytebuffer_maybenull_(size)             _SAL2_Source_(_Outref_result_bytebuffer_maybenull_, (size),           _Outref_result_maybenull_ _Post1_impl_(__bytecap_impl(size)))#define _Outref_result_buffer_to_maybenull_(size, count)       _SAL2_Source_(_Outref_result_buffer_to_maybenull_, (size, count),     _Outref_result_buffer_maybenull_(size) _Post1_impl_(__count_impl(count)))#define _Outref_result_bytebuffer_to_maybenull_(size, count)   _SAL2_Source_(_Outref_result_bytebuffer_to_maybenull_, (size, count), _Outref_result_bytebuffer_maybenull_(size) _Post1_impl_(__bytecount_impl(count)))#define _Outref_result_buffer_all_maybenull_(size)             _SAL2_Source_(_Outref_result_buffer_all_maybenull_, (size),           _Outref_result_buffer_to_maybenull_(size, _Old_(size)))#define _Outref_result_bytebuffer_all_maybenull_(size)         _SAL2_Source_(_Outref_result_bytebuffer_all_maybenull_, (size),       _Outref_result_bytebuffer_to_maybenull_(size, _Old_(size)))





#define _Outref_result_nullonfailure_                          _SAL2_Source_(_Outref_result_nullonfailure_, (), _Outref_    _On_failure_(_Post_null_))



#define _Result_nullonfailure_                                 _SAL2_Source_(_Result_nullonfailure_, (), _On_failure_(_Notref_impl_ _Deref_impl_ _Post_null_))#define _Result_zeroonfailure_                                 _SAL2_Source_(_Result_zeroonfailure_, (), _On_failure_(_Notref_impl_ _Deref_impl_ _Out_range_(==, 0)))



















#define _Ret_z_                             _SAL2_Source_(_Ret_z_, (), _Ret2_impl_(__notnull_impl,  __zterm_impl) _Ret_valid_impl_)#define _Ret_maybenull_z_                   _SAL2_Source_(_Ret_maybenull_z_, (), _Ret2_impl_(__maybenull_impl,__zterm_impl) _Ret_valid_impl_)



#define _Ret_notnull_                       _SAL2_Source_(_Ret_notnull_, (), _Ret1_impl_(__notnull_impl))#define _Ret_maybenull_                     _SAL2_Source_(_Ret_maybenull_, (), _Ret1_impl_(__maybenull_impl))#define _Ret_null_                          _SAL2_Source_(_Ret_null_, (), _Ret1_impl_(__null_impl))





#define _Ret_valid_                         _SAL2_Source_(_Ret_valid_, (), _Ret1_impl_(__notnull_impl_notref)   _Ret_valid_impl_)



#define _Ret_writes_(size)                  _SAL2_Source_(_Ret_writes_, (size), _Ret2_impl_(__notnull_impl,  __count_impl(size))          _Ret_valid_impl_)#define _Ret_writes_z_(size)                _SAL2_Source_(_Ret_writes_z_, (size), _Ret3_impl_(__notnull_impl,  __count_impl(size), __zterm_impl) _Ret_valid_impl_)#define _Ret_writes_bytes_(size)            _SAL2_Source_(_Ret_writes_bytes_, (size), _Ret2_impl_(__notnull_impl,  __bytecount_impl(size))      _Ret_valid_impl_)#define _Ret_writes_maybenull_(size)        _SAL2_Source_(_Ret_writes_maybenull_, (size), _Ret2_impl_(__maybenull_impl,__count_impl(size))          _Ret_valid_impl_)#define _Ret_writes_maybenull_z_(size)      _SAL2_Source_(_Ret_writes_maybenull_z_, (size), _Ret3_impl_(__maybenull_impl,__count_impl(size),__zterm_impl)  _Ret_valid_impl_)#define _Ret_writes_bytes_maybenull_(size)  _SAL2_Source_(_Ret_writes_bytes_maybenull_, (size), _Ret2_impl_(__maybenull_impl,__bytecount_impl(size))      _Ret_valid_impl_)



#define _Ret_writes_to_(size,count)                   _SAL2_Source_(_Ret_writes_to_, (size,count), _Ret3_impl_(__notnull_impl,  __cap_impl(size),     __count_impl(count))     _Ret_valid_impl_)#define _Ret_writes_bytes_to_(size,count)             _SAL2_Source_(_Ret_writes_bytes_to_, (size,count), _Ret3_impl_(__notnull_impl,  __bytecap_impl(size), __bytecount_impl(count)) _Ret_valid_impl_)#define _Ret_writes_to_maybenull_(size,count)         _SAL2_Source_(_Ret_writes_to_maybenull_, (size,count), _Ret3_impl_(__maybenull_impl,  __cap_impl(size),     __count_impl(count))     _Ret_valid_impl_)#define _Ret_writes_bytes_to_maybenull_(size,count)   _SAL2_Source_(_Ret_writes_bytes_to_maybenull_, (size,count), _Ret3_impl_(__maybenull_impl,  __bytecap_impl(size), __bytecount_impl(count)) _Ret_valid_impl_)





#define _Points_to_data_        _SAL2_Source_(_Points_to_data_, (), _Pre_ _Points_to_data_impl_)#define _Literal_               _SAL2_Source_(_Literal_, (), _Pre_ _Literal_impl_)#define _Notliteral_            _SAL2_Source_(_Notliteral_, (), _Pre_ _Notliteral_impl_)



#define _Check_return_           _SAL2_Source_(_Check_return_, (), _Check_return_impl_)#define _Must_inspect_result_    _SAL2_Source_(_Must_inspect_result_, (), _Must_inspect_impl_ _Check_return_impl_)



#define _Printf_format_string_  _SAL2_Source_(_Printf_format_string_, (), _Printf_format_string_impl_)#define _Scanf_format_string_   _SAL2_Source_(_Scanf_format_string_, (), _Scanf_format_string_impl_)#define _Scanf_s_format_string_  _SAL2_Source_(_Scanf_s_format_string_, (), _Scanf_s_format_string_impl_)

#define _Format_string_impl_(kind,where)  _SA_annotes2(SAL_IsFormatString2, kind, where)#define _Printf_format_string_params_(x)  _SAL2_Source_(_Printf_format_string_params_, (x), _Format_string_impl_("printf", x))#define _Scanf_format_string_params_(x)   _SAL2_Source_(_Scanf_format_string_params_, (x), _Format_string_impl_("scanf", x))#define _Scanf_s_format_string_params_(x) _SAL2_Source_(_Scanf_s_format_string_params_, (x), _Format_string_impl_("scanf_s", x))



#define _In_range_(lb,ub)           _SAL2_Source_(_In_range_, (lb,ub), _In_range_impl_(lb,ub))#define _Out_range_(lb,ub)          _SAL2_Source_(_Out_range_, (lb,ub), _Out_range_impl_(lb,ub))#define _Ret_range_(lb,ub)          _SAL2_Source_(_Ret_range_, (lb,ub), _Ret_range_impl_(lb,ub))#define _Deref_in_range_(lb,ub)     _SAL2_Source_(_Deref_in_range_, (lb,ub), _Deref_in_range_impl_(lb,ub))#define _Deref_out_range_(lb,ub)    _SAL2_Source_(_Deref_out_range_, (lb,ub), _Deref_out_range_impl_(lb,ub))#define _Deref_ret_range_(lb,ub)    _SAL2_Source_(_Deref_ret_range_, (lb,ub), _Deref_ret_range_impl_(lb,ub))#define _Pre_equal_to_(expr)        _SAL2_Source_(_Pre_equal_to_, (expr), _In_range_(==, expr))#define _Post_equal_to_(expr)       _SAL2_Source_(_Post_equal_to_, (expr), _Out_range_(==, expr))





#define _Unchanged_(e)              _SAL2_Source_(_Unchanged_, (e), _At_(e, _Post_equal_to_(_Old_(e)) _Const_))







#define _Pre_satisfies_(cond)       _SAL2_Source_(_Pre_satisfies_, (cond), _Pre_satisfies_impl_(cond))#define _Post_satisfies_(cond)      _SAL2_Source_(_Post_satisfies_, (cond), _Post_satisfies_impl_(cond))



#define _Struct_size_bytes_(size)                  _SAL2_Source_(_Struct_size_bytes_, (size), _Writable_bytes_(size))

#define _Field_size_(size)                         _SAL2_Source_(_Field_size_, (size), _Notnull_   _Writable_elements_(size))#define _Field_size_opt_(size)                     _SAL2_Source_(_Field_size_opt_, (size), _Maybenull_ _Writable_elements_(size))#define _Field_size_part_(size, count)             _SAL2_Source_(_Field_size_part_, (size, count), _Notnull_   _Writable_elements_(size) _Readable_elements_(count))#define _Field_size_part_opt_(size, count)         _SAL2_Source_(_Field_size_part_opt_, (size, count), _Maybenull_ _Writable_elements_(size) _Readable_elements_(count))#define _Field_size_full_(size)                    _SAL2_Source_(_Field_size_full_, (size), _Field_size_part_(size, size))#define _Field_size_full_opt_(size)                _SAL2_Source_(_Field_size_full_opt_, (size), _Field_size_part_opt_(size, size))

#define _Field_size_bytes_(size)                   _SAL2_Source_(_Field_size_bytes_, (size), _Notnull_   _Writable_bytes_(size))#define _Field_size_bytes_opt_(size)               _SAL2_Source_(_Field_size_bytes_opt_, (size), _Maybenull_ _Writable_bytes_(size))#define _Field_size_bytes_part_(size, count)       _SAL2_Source_(_Field_size_bytes_part_, (size, count), _Notnull_   _Writable_bytes_(size) _Readable_bytes_(count))#define _Field_size_bytes_part_opt_(size, count)   _SAL2_Source_(_Field_size_bytes_part_opt_, (size, count), _Maybenull_ _Writable_bytes_(size) _Readable_bytes_(count))#define _Field_size_bytes_full_(size)              _SAL2_Source_(_Field_size_bytes_full_, (size), _Field_size_bytes_part_(size, size))#define _Field_size_bytes_full_opt_(size)          _SAL2_Source_(_Field_size_bytes_full_opt_, (size), _Field_size_bytes_part_opt_(size, size))

#define _Field_z_                                  _SAL2_Source_(_Field_z_, (), _Null_terminated_)

#define _Field_range_(min,max)                     _SAL2_Source_(_Field_range_, (min,max), _Field_range_impl_(min,max))

















#define _Pre_                             _Pre_impl_#define _Post_                            _Post_impl_









#define _Valid_                           _Valid_impl_#define _Notvalid_                        _Notvalid_impl_#define _Maybevalid_                      _Maybevalid_impl_











#define _Readable_bytes_(size)            _SAL2_Source_(_Readable_bytes_, (size), _Readable_bytes_impl_(size))#define _Readable_elements_(size)         _SAL2_Source_(_Readable_elements_, (size), _Readable_elements_impl_(size))#define _Writable_bytes_(size)            _SAL2_Source_(_Writable_bytes_, (size), _Writable_bytes_impl_(size))#define _Writable_elements_(size)         _SAL2_Source_(_Writable_elements_, (size), _Writable_elements_impl_(size))

#define _Null_terminated_                 _SAL2_Source_(_Null_terminated_, (), _Null_terminated_impl_)#define _NullNull_terminated_             _SAL2_Source_(_NullNull_terminated_, (), _NullNull_terminated_impl_)



#define _Pre_readable_size_(size)         _SAL2_Source_(_Pre_readable_size_, (size), _Pre1_impl_(__count_impl(size))      _Pre_valid_impl_)#define _Pre_writable_size_(size)         _SAL2_Source_(_Pre_writable_size_, (size), _Pre1_impl_(__cap_impl(size)))#define _Pre_readable_byte_size_(size)    _SAL2_Source_(_Pre_readable_byte_size_, (size), _Pre1_impl_(__bytecount_impl(size))  _Pre_valid_impl_)#define _Pre_writable_byte_size_(size)    _SAL2_Source_(_Pre_writable_byte_size_, (size), _Pre1_impl_(__bytecap_impl(size)))

#define _Post_readable_size_(size)        _SAL2_Source_(_Post_readable_size_, (size), _Post1_impl_(__count_impl(size))     _Post_valid_impl_)#define _Post_writable_size_(size)        _SAL2_Source_(_Post_writable_size_, (size), _Post1_impl_(__cap_impl(size)))#define _Post_readable_byte_size_(size)   _SAL2_Source_(_Post_readable_byte_size_, (size), _Post1_impl_(__bytecount_impl(size)) _Post_valid_impl_)#define _Post_writable_byte_size_(size)   _SAL2_Source_(_Post_writable_byte_size_, (size), _Post1_impl_(__bytecap_impl(size)))







#define _Null_                            _SAL2_Source_(_Null_, (), _Null_impl_)#define _Notnull_                         _SAL2_Source_(_Notnull_, (), _Notnull_impl_)#define _Maybenull_                       _SAL2_Source_(_Maybenull_, (), _Maybenull_impl_)















#define _Pre_z_                           _SAL2_Source_(_Pre_z_, (), _Pre1_impl_(__zterm_impl) _Pre_valid_impl_)



#define _Pre_valid_                       _SAL2_Source_(_Pre_valid_, (), _Pre1_impl_(__notnull_impl_notref)   _Pre_valid_impl_)#define _Pre_opt_valid_                   _SAL2_Source_(_Pre_opt_valid_, (), _Pre1_impl_(__maybenull_impl_notref) _Pre_valid_impl_)

#define _Pre_invalid_                     _SAL2_Source_(_Pre_invalid_, (), _Deref_pre1_impl_(__notvalid_impl))



#define _Pre_unknown_                     _SAL2_Source_(_Pre_unknown_, (), _Pre1_impl_(__maybevalid_impl))



#define _Pre_notnull_                     _SAL2_Source_(_Pre_notnull_, (), _Pre1_impl_(__notnull_impl_notref))#define _Pre_maybenull_                   _SAL2_Source_(_Pre_maybenull_, (), _Pre1_impl_(__maybenull_impl_notref))#define _Pre_null_                        _SAL2_Source_(_Pre_null_, (), _Pre1_impl_(__null_impl_notref))















#define _Post_z_                         _SAL2_Source_(_Post_z_, (), _Post1_impl_(__zterm_impl) _Post_valid_impl_)



#define _Post_valid_                     _SAL2_Source_(_Post_valid_, (), _Post_valid_impl_)#define _Post_invalid_                   _SAL2_Source_(_Post_invalid_, (), _Deref_post1_impl_(__notvalid_impl))



#define _Post_ptr_invalid_               _SAL2_Source_(_Post_ptr_invalid_, (), _Post1_impl_(__notvalid_impl))



#define _Post_notnull_                   _SAL2_Source_(_Post_notnull_, (), _Post1_impl_(__notnull_impl))



#define _Post_null_                      _SAL2_Source_(_Post_null_, (), _Post1_impl_(__null_impl))

#define _Post_maybenull_                 _SAL2_Source_(_Post_maybenull_, (), _Post1_impl_(__maybenull_impl))

#define _Prepost_z_                      _SAL2_Source_(_Prepost_z_, (), _Pre_z_      _Post_z_)



#pragma region Input Buffer SAL 1 compatibility macros









#define _In_count_(size)               _SAL1_1_Source_(_In_count_, (size), _Pre_count_(size)         _Deref_pre_readonly_)#define _In_opt_count_(size)           _SAL1_1_Source_(_In_opt_count_, (size), _Pre_opt_count_(size)     _Deref_pre_readonly_)#define _In_bytecount_(size)           _SAL1_1_Source_(_In_bytecount_, (size), _Pre_bytecount_(size)     _Deref_pre_readonly_)#define _In_opt_bytecount_(size)       _SAL1_1_Source_(_In_opt_bytecount_, (size), _Pre_opt_bytecount_(size) _Deref_pre_readonly_)



#define _In_count_c_(size)             _SAL1_1_Source_(_In_count_c_, (size), _Pre_count_c_(size)         _Deref_pre_readonly_)#define _In_opt_count_c_(size)         _SAL1_1_Source_(_In_opt_count_c_, (size), _Pre_opt_count_c_(size)     _Deref_pre_readonly_)#define _In_bytecount_c_(size)         _SAL1_1_Source_(_In_bytecount_c_, (size), _Pre_bytecount_c_(size)     _Deref_pre_readonly_)#define _In_opt_bytecount_c_(size)     _SAL1_1_Source_(_In_opt_bytecount_c_, (size), _Pre_opt_bytecount_c_(size) _Deref_pre_readonly_)









#define _In_z_count_(size)               _SAL1_1_Source_(_In_z_count_, (size), _Pre_z_ _Pre_count_(size)         _Deref_pre_readonly_)#define _In_opt_z_count_(size)           _SAL1_1_Source_(_In_opt_z_count_, (size), _Pre_opt_z_ _Pre_opt_count_(size)     _Deref_pre_readonly_)#define _In_z_bytecount_(size)           _SAL1_1_Source_(_In_z_bytecount_, (size), _Pre_z_ _Pre_bytecount_(size)     _Deref_pre_readonly_)#define _In_opt_z_bytecount_(size)       _SAL1_1_Source_(_In_opt_z_bytecount_, (size), _Pre_opt_z_ _Pre_opt_bytecount_(size) _Deref_pre_readonly_)



#define _In_z_count_c_(size)             _SAL1_1_Source_(_In_z_count_c_, (size), _Pre_z_ _Pre_count_c_(size)         _Deref_pre_readonly_)#define _In_opt_z_count_c_(size)         _SAL1_1_Source_(_In_opt_z_count_c_, (size), _Pre_opt_z_ _Pre_opt_count_c_(size)     _Deref_pre_readonly_)#define _In_z_bytecount_c_(size)         _SAL1_1_Source_(_In_z_bytecount_c_, (size), _Pre_z_ _Pre_bytecount_c_(size)     _Deref_pre_readonly_)#define _In_opt_z_bytecount_c_(size)     _SAL1_1_Source_(_In_opt_z_bytecount_c_, (size), _Pre_opt_z_ _Pre_opt_bytecount_c_(size) _Deref_pre_readonly_)





#define _In_ptrdiff_count_(size)       _SAL1_1_Source_(_In_ptrdiff_count_, (size), _Pre_ptrdiff_count_(size)     _Deref_pre_readonly_)#define _In_opt_ptrdiff_count_(size)   _SAL1_1_Source_(_In_opt_ptrdiff_count_, (size), _Pre_opt_ptrdiff_count_(size) _Deref_pre_readonly_)





#define _In_count_x_(size)             _SAL1_1_Source_(_In_count_x_, (size), _Pre_count_x_(size)         _Deref_pre_readonly_)#define _In_opt_count_x_(size)         _SAL1_1_Source_(_In_opt_count_x_, (size), _Pre_opt_count_x_(size)     _Deref_pre_readonly_)#define _In_bytecount_x_(size)         _SAL1_1_Source_(_In_bytecount_x_, (size), _Pre_bytecount_x_(size)     _Deref_pre_readonly_)#define _In_opt_bytecount_x_(size)     _SAL1_1_Source_(_In_opt_bytecount_x_, (size), _Pre_opt_bytecount_x_(size) _Deref_pre_readonly_)









#define _Out_cap_(size)                   _SAL1_1_Source_(_Out_cap_, (size), _Pre_cap_(size)           _Post_valid_impl_)#define _Out_opt_cap_(size)               _SAL1_1_Source_(_Out_opt_cap_, (size), _Pre_opt_cap_(size)       _Post_valid_impl_)#define _Out_bytecap_(size)               _SAL1_1_Source_(_Out_bytecap_, (size), _Pre_bytecap_(size)       _Post_valid_impl_)#define _Out_opt_bytecap_(size)           _SAL1_1_Source_(_Out_opt_bytecap_, (size), _Pre_opt_bytecap_(size)   _Post_valid_impl_)



#define _Out_cap_c_(size)                 _SAL1_1_Source_(_Out_cap_c_, (size), _Pre_cap_c_(size)         _Post_valid_impl_)#define _Out_opt_cap_c_(size)             _SAL1_1_Source_(_Out_opt_cap_c_, (size), _Pre_opt_cap_c_(size)     _Post_valid_impl_)#define _Out_bytecap_c_(size)             _SAL1_1_Source_(_Out_bytecap_c_, (size), _Pre_bytecap_c_(size)     _Post_valid_impl_)#define _Out_opt_bytecap_c_(size)         _SAL1_1_Source_(_Out_opt_bytecap_c_, (size), _Pre_opt_bytecap_c_(size) _Post_valid_impl_)



#define _Out_cap_m_(mult,size)            _SAL1_1_Source_(_Out_cap_m_, (mult,size), _Pre_cap_m_(mult,size)     _Post_valid_impl_)#define _Out_opt_cap_m_(mult,size)        _SAL1_1_Source_(_Out_opt_cap_m_, (mult,size), _Pre_opt_cap_m_(mult,size) _Post_valid_impl_)#define _Out_z_cap_m_(mult,size)          _SAL1_1_Source_(_Out_z_cap_m_, (mult,size), _Pre_cap_m_(mult,size)     _Post_valid_impl_ _Post_z_)#define _Out_opt_z_cap_m_(mult,size)      _SAL1_1_Source_(_Out_opt_z_cap_m_, (mult,size), _Pre_opt_cap_m_(mult,size) _Post_valid_impl_ _Post_z_)





#define _Out_ptrdiff_cap_(size)           _SAL1_1_Source_(_Out_ptrdiff_cap_, (size), _Pre_ptrdiff_cap_(size)     _Post_valid_impl_)#define _Out_opt_ptrdiff_cap_(size)       _SAL1_1_Source_(_Out_opt_ptrdiff_cap_, (size), _Pre_opt_ptrdiff_cap_(size) _Post_valid_impl_)



#define _Out_cap_x_(size)                 _SAL1_1_Source_(_Out_cap_x_, (size), _Pre_cap_x_(size)         _Post_valid_impl_)#define _Out_opt_cap_x_(size)             _SAL1_1_Source_(_Out_opt_cap_x_, (size), _Pre_opt_cap_x_(size)     _Post_valid_impl_)#define _Out_bytecap_x_(size)             _SAL1_1_Source_(_Out_bytecap_x_, (size), _Pre_bytecap_x_(size)     _Post_valid_impl_)#define _Out_opt_bytecap_x_(size)         _SAL1_1_Source_(_Out_opt_bytecap_x_, (size), _Pre_opt_bytecap_x_(size) _Post_valid_impl_)







#define _Out_z_cap_(size)                 _SAL1_1_Source_(_Out_z_cap_, (size), _Pre_cap_(size)           _Post_valid_impl_ _Post_z_)#define _Out_opt_z_cap_(size)             _SAL1_1_Source_(_Out_opt_z_cap_, (size), _Pre_opt_cap_(size)       _Post_valid_impl_ _Post_z_)#define _Out_z_bytecap_(size)             _SAL1_1_Source_(_Out_z_bytecap_, (size), _Pre_bytecap_(size)       _Post_valid_impl_ _Post_z_)#define _Out_opt_z_bytecap_(size)         _SAL1_1_Source_(_Out_opt_z_bytecap_, (size), _Pre_opt_bytecap_(size)   _Post_valid_impl_ _Post_z_)



#define _Out_z_cap_c_(size)               _SAL1_1_Source_(_Out_z_cap_c_, (size), _Pre_cap_c_(size)         _Post_valid_impl_ _Post_z_)#define _Out_opt_z_cap_c_(size)           _SAL1_1_Source_(_Out_opt_z_cap_c_, (size), _Pre_opt_cap_c_(size)     _Post_valid_impl_ _Post_z_)#define _Out_z_bytecap_c_(size)           _SAL1_1_Source_(_Out_z_bytecap_c_, (size), _Pre_bytecap_c_(size)     _Post_valid_impl_ _Post_z_)#define _Out_opt_z_bytecap_c_(size)       _SAL1_1_Source_(_Out_opt_z_bytecap_c_, (size), _Pre_opt_bytecap_c_(size) _Post_valid_impl_ _Post_z_)



#define _Out_z_cap_x_(size)               _SAL1_1_Source_(_Out_z_cap_x_, (size), _Pre_cap_x_(size)         _Post_valid_impl_ _Post_z_)#define _Out_opt_z_cap_x_(size)           _SAL1_1_Source_(_Out_opt_z_cap_x_, (size), _Pre_opt_cap_x_(size)     _Post_valid_impl_ _Post_z_)#define _Out_z_bytecap_x_(size)           _SAL1_1_Source_(_Out_z_bytecap_x_, (size), _Pre_bytecap_x_(size)     _Post_valid_impl_ _Post_z_)#define _Out_opt_z_bytecap_x_(size)       _SAL1_1_Source_(_Out_opt_z_bytecap_x_, (size), _Pre_opt_bytecap_x_(size) _Post_valid_impl_ _Post_z_)





#define _Out_cap_post_count_(cap,count)                _SAL1_1_Source_(_Out_cap_post_count_, (cap,count), _Pre_cap_(cap)         _Post_valid_impl_ _Post_count_(count))#define _Out_opt_cap_post_count_(cap,count)            _SAL1_1_Source_(_Out_opt_cap_post_count_, (cap,count), _Pre_opt_cap_(cap)     _Post_valid_impl_ _Post_count_(count))#define _Out_bytecap_post_bytecount_(cap,count)        _SAL1_1_Source_(_Out_bytecap_post_bytecount_, (cap,count), _Pre_bytecap_(cap)     _Post_valid_impl_ _Post_bytecount_(count))#define _Out_opt_bytecap_post_bytecount_(cap,count)    _SAL1_1_Source_(_Out_opt_bytecap_post_bytecount_, (cap,count), _Pre_opt_bytecap_(cap) _Post_valid_impl_ _Post_bytecount_(count))





#define _Out_z_cap_post_count_(cap,count)               _SAL1_1_Source_(_Out_z_cap_post_count_, (cap,count), _Pre_cap_(cap)         _Post_valid_impl_ _Post_z_count_(count))#define _Out_opt_z_cap_post_count_(cap,count)           _SAL1_1_Source_(_Out_opt_z_cap_post_count_, (cap,count), _Pre_opt_cap_(cap)     _Post_valid_impl_ _Post_z_count_(count))#define _Out_z_bytecap_post_bytecount_(cap,count)       _SAL1_1_Source_(_Out_z_bytecap_post_bytecount_, (cap,count), _Pre_bytecap_(cap)     _Post_valid_impl_ _Post_z_bytecount_(count))#define _Out_opt_z_bytecap_post_bytecount_(cap,count)   _SAL1_1_Source_(_Out_opt_z_bytecap_post_bytecount_, (cap,count), _Pre_opt_bytecap_(cap) _Post_valid_impl_ _Post_z_bytecount_(count))



#define _Out_capcount_(capcount)             _SAL1_1_Source_(_Out_capcount_, (capcount), _Pre_cap_(capcount)         _Post_valid_impl_ _Post_count_(capcount))#define _Out_opt_capcount_(capcount)         _SAL1_1_Source_(_Out_opt_capcount_, (capcount), _Pre_opt_cap_(capcount)     _Post_valid_impl_ _Post_count_(capcount))#define _Out_bytecapcount_(capcount)         _SAL1_1_Source_(_Out_bytecapcount_, (capcount), _Pre_bytecap_(capcount)     _Post_valid_impl_ _Post_bytecount_(capcount))#define _Out_opt_bytecapcount_(capcount)     _SAL1_1_Source_(_Out_opt_bytecapcount_, (capcount), _Pre_opt_bytecap_(capcount) _Post_valid_impl_ _Post_bytecount_(capcount))

#define _Out_capcount_x_(capcount)           _SAL1_1_Source_(_Out_capcount_x_, (capcount), _Pre_cap_x_(capcount)         _Post_valid_impl_ _Post_count_x_(capcount))#define _Out_opt_capcount_x_(capcount)       _SAL1_1_Source_(_Out_opt_capcount_x_, (capcount), _Pre_opt_cap_x_(capcount)     _Post_valid_impl_ _Post_count_x_(capcount))#define _Out_bytecapcount_x_(capcount)       _SAL1_1_Source_(_Out_bytecapcount_x_, (capcount), _Pre_bytecap_x_(capcount)     _Post_valid_impl_ _Post_bytecount_x_(capcount))#define _Out_opt_bytecapcount_x_(capcount)   _SAL1_1_Source_(_Out_opt_bytecapcount_x_, (capcount), _Pre_opt_bytecap_x_(capcount) _Post_valid_impl_ _Post_bytecount_x_(capcount))



#define _Out_z_capcount_(capcount)           _SAL1_1_Source_(_Out_z_capcount_, (capcount), _Pre_cap_(capcount)         _Post_valid_impl_ _Post_z_count_(capcount))#define _Out_opt_z_capcount_(capcount)       _SAL1_1_Source_(_Out_opt_z_capcount_, (capcount), _Pre_opt_cap_(capcount)     _Post_valid_impl_ _Post_z_count_(capcount))#define _Out_z_bytecapcount_(capcount)       _SAL1_1_Source_(_Out_z_bytecapcount_, (capcount), _Pre_bytecap_(capcount)     _Post_valid_impl_ _Post_z_bytecount_(capcount))#define _Out_opt_z_bytecapcount_(capcount)   _SAL1_1_Source_(_Out_opt_z_bytecapcount_, (capcount), _Pre_opt_bytecap_(capcount) _Post_valid_impl_ _Post_z_bytecount_(capcount))







#define _Inout_count_(size)               _SAL1_1_Source_(_Inout_count_, (size), _Prepost_count_(size))#define _Inout_opt_count_(size)           _SAL1_1_Source_(_Inout_opt_count_, (size), _Prepost_opt_count_(size))#define _Inout_bytecount_(size)           _SAL1_1_Source_(_Inout_bytecount_, (size), _Prepost_bytecount_(size))#define _Inout_opt_bytecount_(size)       _SAL1_1_Source_(_Inout_opt_bytecount_, (size), _Prepost_opt_bytecount_(size))

#define _Inout_count_c_(size)             _SAL1_1_Source_(_Inout_count_c_, (size), _Prepost_count_c_(size))#define _Inout_opt_count_c_(size)         _SAL1_1_Source_(_Inout_opt_count_c_, (size), _Prepost_opt_count_c_(size))#define _Inout_bytecount_c_(size)         _SAL1_1_Source_(_Inout_bytecount_c_, (size), _Prepost_bytecount_c_(size))#define _Inout_opt_bytecount_c_(size)     _SAL1_1_Source_(_Inout_opt_bytecount_c_, (size), _Prepost_opt_bytecount_c_(size))





#define _Inout_z_count_(size)               _SAL1_1_Source_(_Inout_z_count_, (size), _Prepost_z_ _Prepost_count_(size))#define _Inout_opt_z_count_(size)           _SAL1_1_Source_(_Inout_opt_z_count_, (size), _Prepost_z_ _Prepost_opt_count_(size))#define _Inout_z_bytecount_(size)           _SAL1_1_Source_(_Inout_z_bytecount_, (size), _Prepost_z_ _Prepost_bytecount_(size))#define _Inout_opt_z_bytecount_(size)       _SAL1_1_Source_(_Inout_opt_z_bytecount_, (size), _Prepost_z_ _Prepost_opt_bytecount_(size))

#define _Inout_z_count_c_(size)             _SAL1_1_Source_(_Inout_z_count_c_, (size), _Prepost_z_ _Prepost_count_c_(size))#define _Inout_opt_z_count_c_(size)         _SAL1_1_Source_(_Inout_opt_z_count_c_, (size), _Prepost_z_ _Prepost_opt_count_c_(size))#define _Inout_z_bytecount_c_(size)         _SAL1_1_Source_(_Inout_z_bytecount_c_, (size), _Prepost_z_ _Prepost_bytecount_c_(size))#define _Inout_opt_z_bytecount_c_(size)     _SAL1_1_Source_(_Inout_opt_z_bytecount_c_, (size), _Prepost_z_ _Prepost_opt_bytecount_c_(size))

#define _Inout_ptrdiff_count_(size)       _SAL1_1_Source_(_Inout_ptrdiff_count_, (size), _Pre_ptrdiff_count_(size))#define _Inout_opt_ptrdiff_count_(size)   _SAL1_1_Source_(_Inout_opt_ptrdiff_count_, (size), _Pre_opt_ptrdiff_count_(size))

#define _Inout_count_x_(size)             _SAL1_1_Source_(_Inout_count_x_, (size), _Prepost_count_x_(size))#define _Inout_opt_count_x_(size)         _SAL1_1_Source_(_Inout_opt_count_x_, (size), _Prepost_opt_count_x_(size))#define _Inout_bytecount_x_(size)         _SAL1_1_Source_(_Inout_bytecount_x_, (size), _Prepost_bytecount_x_(size))#define _Inout_opt_bytecount_x_(size)     _SAL1_1_Source_(_Inout_opt_bytecount_x_, (size), _Prepost_opt_bytecount_x_(size))



#define _Inout_cap_(size)                 _SAL1_1_Source_(_Inout_cap_, (size), _Pre_valid_cap_(size)           _Post_valid_)#define _Inout_opt_cap_(size)             _SAL1_1_Source_(_Inout_opt_cap_, (size), _Pre_opt_valid_cap_(size)       _Post_valid_)#define _Inout_bytecap_(size)             _SAL1_1_Source_(_Inout_bytecap_, (size), _Pre_valid_bytecap_(size)       _Post_valid_)#define _Inout_opt_bytecap_(size)         _SAL1_1_Source_(_Inout_opt_bytecap_, (size), _Pre_opt_valid_bytecap_(size)   _Post_valid_)

#define _Inout_cap_c_(size)               _SAL1_1_Source_(_Inout_cap_c_, (size), _Pre_valid_cap_c_(size)         _Post_valid_)#define _Inout_opt_cap_c_(size)           _SAL1_1_Source_(_Inout_opt_cap_c_, (size), _Pre_opt_valid_cap_c_(size)     _Post_valid_)#define _Inout_bytecap_c_(size)           _SAL1_1_Source_(_Inout_bytecap_c_, (size), _Pre_valid_bytecap_c_(size)     _Post_valid_)#define _Inout_opt_bytecap_c_(size)       _SAL1_1_Source_(_Inout_opt_bytecap_c_, (size), _Pre_opt_valid_bytecap_c_(size) _Post_valid_)

#define _Inout_cap_x_(size)               _SAL1_1_Source_(_Inout_cap_x_, (size), _Pre_valid_cap_x_(size)         _Post_valid_)#define _Inout_opt_cap_x_(size)           _SAL1_1_Source_(_Inout_opt_cap_x_, (size), _Pre_opt_valid_cap_x_(size)     _Post_valid_)#define _Inout_bytecap_x_(size)           _SAL1_1_Source_(_Inout_bytecap_x_, (size), _Pre_valid_bytecap_x_(size)     _Post_valid_)#define _Inout_opt_bytecap_x_(size)       _SAL1_1_Source_(_Inout_opt_bytecap_x_, (size), _Pre_opt_valid_bytecap_x_(size) _Post_valid_)





#define _Inout_z_cap_(size)                  _SAL1_1_Source_(_Inout_z_cap_, (size), _Pre_z_cap_(size)            _Post_z_)#define _Inout_opt_z_cap_(size)              _SAL1_1_Source_(_Inout_opt_z_cap_, (size), _Pre_opt_z_cap_(size)        _Post_z_)#define _Inout_z_bytecap_(size)              _SAL1_1_Source_(_Inout_z_bytecap_, (size), _Pre_z_bytecap_(size)        _Post_z_)#define _Inout_opt_z_bytecap_(size)          _SAL1_1_Source_(_Inout_opt_z_bytecap_, (size), _Pre_opt_z_bytecap_(size)    _Post_z_)

#define _Inout_z_cap_c_(size)                _SAL1_1_Source_(_Inout_z_cap_c_, (size), _Pre_z_cap_c_(size)          _Post_z_)#define _Inout_opt_z_cap_c_(size)            _SAL1_1_Source_(_Inout_opt_z_cap_c_, (size), _Pre_opt_z_cap_c_(size)      _Post_z_)#define _Inout_z_bytecap_c_(size)            _SAL1_1_Source_(_Inout_z_bytecap_c_, (size), _Pre_z_bytecap_c_(size)      _Post_z_)#define _Inout_opt_z_bytecap_c_(size)        _SAL1_1_Source_(_Inout_opt_z_bytecap_c_, (size), _Pre_opt_z_bytecap_c_(size)  _Post_z_)

#define _Inout_z_cap_x_(size)                _SAL1_1_Source_(_Inout_z_cap_x_, (size), _Pre_z_cap_x_(size)          _Post_z_)#define _Inout_opt_z_cap_x_(size)            _SAL1_1_Source_(_Inout_opt_z_cap_x_, (size), _Pre_opt_z_cap_x_(size)      _Post_z_)#define _Inout_z_bytecap_x_(size)            _SAL1_1_Source_(_Inout_z_bytecap_x_, (size), _Pre_z_bytecap_x_(size)      _Post_z_)#define _Inout_opt_z_bytecap_x_(size)        _SAL1_1_Source_(_Inout_opt_z_bytecap_x_, (size), _Pre_opt_z_bytecap_x_(size)  _Post_z_)





#define _Ret_                   _SAL1_1_Source_(_Ret_, (), _Ret_valid_)#define _Ret_opt_               _SAL1_1_Source_(_Ret_opt_, (), _Ret_opt_valid_)



#define _In_bound_           _SAL1_1_Source_(_In_bound_, (), _In_bound_impl_)#define _Out_bound_          _SAL1_1_Source_(_Out_bound_, (), _Out_bound_impl_)#define _Ret_bound_          _SAL1_1_Source_(_Ret_bound_, (), _Ret_bound_impl_)#define _Deref_in_bound_     _SAL1_1_Source_(_Deref_in_bound_, (), _Deref_in_bound_impl_)#define _Deref_out_bound_    _SAL1_1_Source_(_Deref_out_bound_, (), _Deref_out_bound_impl_)#define _Deref_inout_bound_  _SAL1_1_Source_(_Deref_inout_bound_, (), _Deref_in_bound_ _Deref_out_bound_)#define _Deref_ret_bound_    _SAL1_1_Source_(_Deref_ret_bound_, (), _Deref_ret_bound_impl_)



#define _Deref_out_             _SAL1_1_Source_(_Deref_out_, (), _Out_ _Deref_post_valid_)#define _Deref_out_opt_         _SAL1_1_Source_(_Deref_out_opt_, (), _Out_ _Deref_post_opt_valid_)#define _Deref_opt_out_         _SAL1_1_Source_(_Deref_opt_out_, (), _Out_opt_ _Deref_post_valid_)#define _Deref_opt_out_opt_     _SAL1_1_Source_(_Deref_opt_out_opt_, (), _Out_opt_ _Deref_post_opt_valid_)



#define _Deref_out_z_           _SAL1_1_Source_(_Deref_out_z_, (), _Out_ _Deref_post_z_)#define _Deref_out_opt_z_       _SAL1_1_Source_(_Deref_out_opt_z_, (), _Out_ _Deref_post_opt_z_)#define _Deref_opt_out_z_       _SAL1_1_Source_(_Deref_opt_out_z_, (), _Out_opt_ _Deref_post_z_)#define _Deref_opt_out_opt_z_   _SAL1_1_Source_(_Deref_opt_out_opt_z_, (), _Out_opt_ _Deref_post_opt_z_)













#define _Deref_pre_z_                           _SAL1_1_Source_(_Deref_pre_z_, (), _Deref_pre1_impl_(__notnull_impl_notref) _Deref_pre1_impl_(__zterm_impl) _Pre_valid_impl_)#define _Deref_pre_opt_z_                       _SAL1_1_Source_(_Deref_pre_opt_z_, (), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__zterm_impl) _Pre_valid_impl_)





#define _Deref_pre_cap_(size)                   _SAL1_1_Source_(_Deref_pre_cap_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__cap_impl(size)))#define _Deref_pre_opt_cap_(size)               _SAL1_1_Source_(_Deref_pre_opt_cap_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__cap_impl(size)))#define _Deref_pre_bytecap_(size)               _SAL1_1_Source_(_Deref_pre_bytecap_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecap_impl(size)))#define _Deref_pre_opt_bytecap_(size)           _SAL1_1_Source_(_Deref_pre_opt_bytecap_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecap_impl(size)))



#define _Deref_pre_cap_c_(size)                 _SAL1_1_Source_(_Deref_pre_cap_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__cap_c_impl(size)))#define _Deref_pre_opt_cap_c_(size)             _SAL1_1_Source_(_Deref_pre_opt_cap_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__cap_c_impl(size)))#define _Deref_pre_bytecap_c_(size)             _SAL1_1_Source_(_Deref_pre_bytecap_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecap_c_impl(size)))#define _Deref_pre_opt_bytecap_c_(size)         _SAL1_1_Source_(_Deref_pre_opt_bytecap_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecap_c_impl(size)))



#define _Deref_pre_cap_x_(size)                 _SAL1_1_Source_(_Deref_pre_cap_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__cap_x_impl(size)))#define _Deref_pre_opt_cap_x_(size)             _SAL1_1_Source_(_Deref_pre_opt_cap_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__cap_x_impl(size)))#define _Deref_pre_bytecap_x_(size)             _SAL1_1_Source_(_Deref_pre_bytecap_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecap_x_impl(size)))#define _Deref_pre_opt_bytecap_x_(size)         _SAL1_1_Source_(_Deref_pre_opt_bytecap_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecap_x_impl(size)))



#define _Deref_pre_z_cap_(size)                 _SAL1_1_Source_(_Deref_pre_z_cap_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre2_impl_(__zterm_impl,__cap_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_z_cap_(size)             _SAL1_1_Source_(_Deref_pre_opt_z_cap_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre2_impl_(__zterm_impl,__cap_impl(size))     _Pre_valid_impl_)#define _Deref_pre_z_bytecap_(size)             _SAL1_1_Source_(_Deref_pre_z_bytecap_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre2_impl_(__zterm_impl,__bytecap_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_z_bytecap_(size)         _SAL1_1_Source_(_Deref_pre_opt_z_bytecap_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre2_impl_(__zterm_impl,__bytecap_impl(size)) _Pre_valid_impl_)

#define _Deref_pre_z_cap_c_(size)               _SAL1_1_Source_(_Deref_pre_z_cap_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre2_impl_(__zterm_impl,__cap_c_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_z_cap_c_(size)           _SAL1_1_Source_(_Deref_pre_opt_z_cap_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre2_impl_(__zterm_impl,__cap_c_impl(size))     _Pre_valid_impl_)#define _Deref_pre_z_bytecap_c_(size)           _SAL1_1_Source_(_Deref_pre_z_bytecap_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre2_impl_(__zterm_impl,__bytecap_c_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_z_bytecap_c_(size)       _SAL1_1_Source_(_Deref_pre_opt_z_bytecap_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre2_impl_(__zterm_impl,__bytecap_c_impl(size)) _Pre_valid_impl_)

#define _Deref_pre_z_cap_x_(size)               _SAL1_1_Source_(_Deref_pre_z_cap_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre2_impl_(__zterm_impl,__cap_x_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_z_cap_x_(size)           _SAL1_1_Source_(_Deref_pre_opt_z_cap_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre2_impl_(__zterm_impl,__cap_x_impl(size))     _Pre_valid_impl_)#define _Deref_pre_z_bytecap_x_(size)           _SAL1_1_Source_(_Deref_pre_z_bytecap_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre2_impl_(__zterm_impl,__bytecap_x_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_z_bytecap_x_(size)       _SAL1_1_Source_(_Deref_pre_opt_z_bytecap_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre2_impl_(__zterm_impl,__bytecap_x_impl(size)) _Pre_valid_impl_)



#define _Deref_pre_valid_cap_(size)             _SAL1_1_Source_(_Deref_pre_valid_cap_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__cap_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_valid_cap_(size)         _SAL1_1_Source_(_Deref_pre_opt_valid_cap_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__cap_impl(size))     _Pre_valid_impl_)#define _Deref_pre_valid_bytecap_(size)         _SAL1_1_Source_(_Deref_pre_valid_bytecap_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecap_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_valid_bytecap_(size)     _SAL1_1_Source_(_Deref_pre_opt_valid_bytecap_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecap_impl(size)) _Pre_valid_impl_)

#define _Deref_pre_valid_cap_c_(size)           _SAL1_1_Source_(_Deref_pre_valid_cap_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__cap_c_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_valid_cap_c_(size)       _SAL1_1_Source_(_Deref_pre_opt_valid_cap_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__cap_c_impl(size))     _Pre_valid_impl_)#define _Deref_pre_valid_bytecap_c_(size)       _SAL1_1_Source_(_Deref_pre_valid_bytecap_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecap_c_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_valid_bytecap_c_(size)   _SAL1_1_Source_(_Deref_pre_opt_valid_bytecap_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecap_c_impl(size)) _Pre_valid_impl_)

#define _Deref_pre_valid_cap_x_(size)           _SAL1_1_Source_(_Deref_pre_valid_cap_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__cap_x_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_valid_cap_x_(size)       _SAL1_1_Source_(_Deref_pre_opt_valid_cap_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__cap_x_impl(size))     _Pre_valid_impl_)#define _Deref_pre_valid_bytecap_x_(size)       _SAL1_1_Source_(_Deref_pre_valid_bytecap_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecap_x_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_valid_bytecap_x_(size)   _SAL1_1_Source_(_Deref_pre_opt_valid_bytecap_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecap_x_impl(size)) _Pre_valid_impl_)





#define _Deref_pre_count_(size)                 _SAL1_1_Source_(_Deref_pre_count_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__count_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_count_(size)             _SAL1_1_Source_(_Deref_pre_opt_count_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__count_impl(size))     _Pre_valid_impl_)#define _Deref_pre_bytecount_(size)             _SAL1_1_Source_(_Deref_pre_bytecount_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecount_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_bytecount_(size)         _SAL1_1_Source_(_Deref_pre_opt_bytecount_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecount_impl(size)) _Pre_valid_impl_)



#define _Deref_pre_count_c_(size)               _SAL1_1_Source_(_Deref_pre_count_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__count_c_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_count_c_(size)           _SAL1_1_Source_(_Deref_pre_opt_count_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__count_c_impl(size))     _Pre_valid_impl_)#define _Deref_pre_bytecount_c_(size)           _SAL1_1_Source_(_Deref_pre_bytecount_c_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecount_c_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_bytecount_c_(size)       _SAL1_1_Source_(_Deref_pre_opt_bytecount_c_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecount_c_impl(size)) _Pre_valid_impl_)



#define _Deref_pre_count_x_(size)               _SAL1_1_Source_(_Deref_pre_count_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__count_x_impl(size))     _Pre_valid_impl_)#define _Deref_pre_opt_count_x_(size)           _SAL1_1_Source_(_Deref_pre_opt_count_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__count_x_impl(size))     _Pre_valid_impl_)#define _Deref_pre_bytecount_x_(size)           _SAL1_1_Source_(_Deref_pre_bytecount_x_, (size), _Deref_pre1_impl_(__notnull_impl_notref)   _Deref_pre1_impl_(__bytecount_x_impl(size)) _Pre_valid_impl_)#define _Deref_pre_opt_bytecount_x_(size)       _SAL1_1_Source_(_Deref_pre_opt_bytecount_x_, (size), _Deref_pre1_impl_(__maybenull_impl_notref) _Deref_pre1_impl_(__bytecount_x_impl(size)) _Pre_valid_impl_)



#define _Deref_pre_valid_                       _SAL1_1_Source_(_Deref_pre_valid_, (), _Deref_pre1_impl_(__notnull_impl_notref)   _Pre_valid_impl_)#define _Deref_pre_opt_valid_                   _SAL1_1_Source_(_Deref_pre_opt_valid_, (), _Deref_pre1_impl_(__maybenull_impl_notref) _Pre_valid_impl_)#define _Deref_pre_invalid_                     _SAL1_1_Source_(_Deref_pre_invalid_, (), _Deref_pre1_impl_(__notvalid_impl))

#define _Deref_pre_notnull_                     _SAL1_1_Source_(_Deref_pre_notnull_, (), _Deref_pre1_impl_(__notnull_impl_notref))#define _Deref_pre_maybenull_                   _SAL1_1_Source_(_Deref_pre_maybenull_, (), _Deref_pre1_impl_(__maybenull_impl_notref))#define _Deref_pre_null_                        _SAL1_1_Source_(_Deref_pre_null_, (), _Deref_pre1_impl_(__null_impl_notref))



#define _Deref_pre_readonly_                    _SAL1_1_Source_(_Deref_pre_readonly_, (), _Deref_pre1_impl_(__readaccess_impl_notref))#define _Deref_pre_writeonly_                   _SAL1_1_Source_(_Deref_pre_writeonly_, (), _Deref_pre1_impl_(__writeaccess_impl_notref))













#define _Deref_post_z_                           _SAL1_1_Source_(_Deref_post_z_, (), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__zterm_impl) _Post_valid_impl_)#define _Deref_post_opt_z_                       _SAL1_1_Source_(_Deref_post_opt_z_, (), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__zterm_impl) _Post_valid_impl_)





#define _Deref_post_cap_(size)                   _SAL1_1_Source_(_Deref_post_cap_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__cap_impl(size)))#define _Deref_post_opt_cap_(size)               _SAL1_1_Source_(_Deref_post_opt_cap_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__cap_impl(size)))#define _Deref_post_bytecap_(size)               _SAL1_1_Source_(_Deref_post_bytecap_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecap_impl(size)))#define _Deref_post_opt_bytecap_(size)           _SAL1_1_Source_(_Deref_post_opt_bytecap_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecap_impl(size)))



#define _Deref_post_cap_c_(size)                 _SAL1_1_Source_(_Deref_post_cap_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__cap_c_impl(size)))#define _Deref_post_opt_cap_c_(size)             _SAL1_1_Source_(_Deref_post_opt_cap_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__cap_c_impl(size)))#define _Deref_post_bytecap_c_(size)             _SAL1_1_Source_(_Deref_post_bytecap_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecap_c_impl(size)))#define _Deref_post_opt_bytecap_c_(size)         _SAL1_1_Source_(_Deref_post_opt_bytecap_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecap_c_impl(size)))



#define _Deref_post_cap_x_(size)                 _SAL1_1_Source_(_Deref_post_cap_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__cap_x_impl(size)))#define _Deref_post_opt_cap_x_(size)             _SAL1_1_Source_(_Deref_post_opt_cap_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__cap_x_impl(size)))#define _Deref_post_bytecap_x_(size)             _SAL1_1_Source_(_Deref_post_bytecap_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecap_x_impl(size)))#define _Deref_post_opt_bytecap_x_(size)         _SAL1_1_Source_(_Deref_post_opt_bytecap_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecap_x_impl(size)))



#define _Deref_post_z_cap_(size)                 _SAL1_1_Source_(_Deref_post_z_cap_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post2_impl_(__zterm_impl,__cap_impl(size))       _Post_valid_impl_)#define _Deref_post_opt_z_cap_(size)             _SAL1_1_Source_(_Deref_post_opt_z_cap_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post2_impl_(__zterm_impl,__cap_impl(size))       _Post_valid_impl_)#define _Deref_post_z_bytecap_(size)             _SAL1_1_Source_(_Deref_post_z_bytecap_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post2_impl_(__zterm_impl,__bytecap_impl(size))   _Post_valid_impl_)#define _Deref_post_opt_z_bytecap_(size)         _SAL1_1_Source_(_Deref_post_opt_z_bytecap_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post2_impl_(__zterm_impl,__bytecap_impl(size))   _Post_valid_impl_)

#define _Deref_post_z_cap_c_(size)               _SAL1_1_Source_(_Deref_post_z_cap_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post2_impl_(__zterm_impl,__cap_c_impl(size))     _Post_valid_impl_)#define _Deref_post_opt_z_cap_c_(size)           _SAL1_1_Source_(_Deref_post_opt_z_cap_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post2_impl_(__zterm_impl,__cap_c_impl(size))     _Post_valid_impl_)#define _Deref_post_z_bytecap_c_(size)           _SAL1_1_Source_(_Deref_post_z_bytecap_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post2_impl_(__zterm_impl,__bytecap_c_impl(size)) _Post_valid_impl_)#define _Deref_post_opt_z_bytecap_c_(size)       _SAL1_1_Source_(_Deref_post_opt_z_bytecap_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post2_impl_(__zterm_impl,__bytecap_c_impl(size)) _Post_valid_impl_)

#define _Deref_post_z_cap_x_(size)               _SAL1_1_Source_(_Deref_post_z_cap_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post2_impl_(__zterm_impl,__cap_x_impl(size))     _Post_valid_impl_)#define _Deref_post_opt_z_cap_x_(size)           _SAL1_1_Source_(_Deref_post_opt_z_cap_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post2_impl_(__zterm_impl,__cap_x_impl(size))     _Post_valid_impl_)#define _Deref_post_z_bytecap_x_(size)           _SAL1_1_Source_(_Deref_post_z_bytecap_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post2_impl_(__zterm_impl,__bytecap_x_impl(size)) _Post_valid_impl_)#define _Deref_post_opt_z_bytecap_x_(size)       _SAL1_1_Source_(_Deref_post_opt_z_bytecap_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post2_impl_(__zterm_impl,__bytecap_x_impl(size)) _Post_valid_impl_)



#define _Deref_post_valid_cap_(size)             _SAL1_1_Source_(_Deref_post_valid_cap_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__cap_impl(size))       _Post_valid_impl_)#define _Deref_post_opt_valid_cap_(size)         _SAL1_1_Source_(_Deref_post_opt_valid_cap_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__cap_impl(size))       _Post_valid_impl_)#define _Deref_post_valid_bytecap_(size)         _SAL1_1_Source_(_Deref_post_valid_bytecap_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecap_impl(size))   _Post_valid_impl_)#define _Deref_post_opt_valid_bytecap_(size)     _SAL1_1_Source_(_Deref_post_opt_valid_bytecap_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecap_impl(size))   _Post_valid_impl_)                                                

#define _Deref_post_valid_cap_c_(size)           _SAL1_1_Source_(_Deref_post_valid_cap_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__cap_c_impl(size))     _Post_valid_impl_)#define _Deref_post_opt_valid_cap_c_(size)       _SAL1_1_Source_(_Deref_post_opt_valid_cap_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__cap_c_impl(size))     _Post_valid_impl_)#define _Deref_post_valid_bytecap_c_(size)       _SAL1_1_Source_(_Deref_post_valid_bytecap_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecap_c_impl(size)) _Post_valid_impl_)#define _Deref_post_opt_valid_bytecap_c_(size)   _SAL1_1_Source_(_Deref_post_opt_valid_bytecap_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecap_c_impl(size)) _Post_valid_impl_)                                                

#define _Deref_post_valid_cap_x_(size)           _SAL1_1_Source_(_Deref_post_valid_cap_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__cap_x_impl(size))     _Post_valid_impl_)#define _Deref_post_opt_valid_cap_x_(size)       _SAL1_1_Source_(_Deref_post_opt_valid_cap_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__cap_x_impl(size))     _Post_valid_impl_)#define _Deref_post_valid_bytecap_x_(size)       _SAL1_1_Source_(_Deref_post_valid_bytecap_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecap_x_impl(size)) _Post_valid_impl_)#define _Deref_post_opt_valid_bytecap_x_(size)   _SAL1_1_Source_(_Deref_post_opt_valid_bytecap_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecap_x_impl(size)) _Post_valid_impl_)





#define _Deref_post_count_(size)                 _SAL1_1_Source_(_Deref_post_count_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__count_impl(size))       _Post_valid_impl_)#define _Deref_post_opt_count_(size)             _SAL1_1_Source_(_Deref_post_opt_count_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__count_impl(size))       _Post_valid_impl_)#define _Deref_post_bytecount_(size)             _SAL1_1_Source_(_Deref_post_bytecount_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecount_impl(size))   _Post_valid_impl_)#define _Deref_post_opt_bytecount_(size)         _SAL1_1_Source_(_Deref_post_opt_bytecount_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecount_impl(size))   _Post_valid_impl_)



#define _Deref_post_count_c_(size)               _SAL1_1_Source_(_Deref_post_count_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__count_c_impl(size))     _Post_valid_impl_)#define _Deref_post_opt_count_c_(size)           _SAL1_1_Source_(_Deref_post_opt_count_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__count_c_impl(size))     _Post_valid_impl_)#define _Deref_post_bytecount_c_(size)           _SAL1_1_Source_(_Deref_post_bytecount_c_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecount_c_impl(size)) _Post_valid_impl_)#define _Deref_post_opt_bytecount_c_(size)       _SAL1_1_Source_(_Deref_post_opt_bytecount_c_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecount_c_impl(size)) _Post_valid_impl_)



#define _Deref_post_count_x_(size)               _SAL1_1_Source_(_Deref_post_count_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__count_x_impl(size))     _Post_valid_impl_)#define _Deref_post_opt_count_x_(size)           _SAL1_1_Source_(_Deref_post_opt_count_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__count_x_impl(size))     _Post_valid_impl_)#define _Deref_post_bytecount_x_(size)           _SAL1_1_Source_(_Deref_post_bytecount_x_, (size), _Deref_post1_impl_(__notnull_impl_notref) _Deref_post1_impl_(__bytecount_x_impl(size)) _Post_valid_impl_)#define _Deref_post_opt_bytecount_x_(size)       _SAL1_1_Source_(_Deref_post_opt_bytecount_x_, (size), _Deref_post1_impl_(__maybenull_impl_notref) _Deref_post1_impl_(__bytecount_x_impl(size)) _Post_valid_impl_)



#define _Deref_post_valid_                       _SAL1_1_Source_(_Deref_post_valid_, (), _Deref_post1_impl_(__notnull_impl_notref)   _Post_valid_impl_)#define _Deref_post_opt_valid_                   _SAL1_1_Source_(_Deref_post_opt_valid_, (), _Deref_post1_impl_(__maybenull_impl_notref) _Post_valid_impl_)

#define _Deref_post_notnull_                     _SAL1_1_Source_(_Deref_post_notnull_, (), _Deref_post1_impl_(__notnull_impl_notref))#define _Deref_post_maybenull_                   _SAL1_1_Source_(_Deref_post_maybenull_, (), _Deref_post1_impl_(__maybenull_impl_notref))#define _Deref_post_null_                        _SAL1_1_Source_(_Deref_post_null_, (), _Deref_post1_impl_(__null_impl_notref))









#define _Deref_ret_z_                            _SAL1_1_Source_(_Deref_ret_z_, (), _Deref_ret1_impl_(__notnull_impl_notref) _Deref_ret1_impl_(__zterm_impl))#define _Deref_ret_opt_z_                        _SAL1_1_Source_(_Deref_ret_opt_z_, (), _Deref_ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__zterm_impl))







#define _Deref2_pre_readonly_                    _SAL1_1_Source_(_Deref2_pre_readonly_, (), _Deref2_pre1_impl_(__readaccess_impl_notref))











#define _Ret_opt_valid_                   _SAL1_1_Source_(_Ret_opt_valid_, (), _Ret1_impl_(__maybenull_impl_notref) _Ret_valid_impl_)#define _Ret_opt_z_                       _SAL1_1_Source_(_Ret_opt_z_, (), _Ret2_impl_(__maybenull_impl,__zterm_impl) _Ret_valid_impl_)





#define _Ret_cap_(size)                   _SAL1_1_Source_(_Ret_cap_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__cap_impl(size)))#define _Ret_opt_cap_(size)               _SAL1_1_Source_(_Ret_opt_cap_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__cap_impl(size)))#define _Ret_bytecap_(size)               _SAL1_1_Source_(_Ret_bytecap_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__bytecap_impl(size)))#define _Ret_opt_bytecap_(size)           _SAL1_1_Source_(_Ret_opt_bytecap_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__bytecap_impl(size)))



#define _Ret_cap_c_(size)                 _SAL1_1_Source_(_Ret_cap_c_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__cap_c_impl(size)))#define _Ret_opt_cap_c_(size)             _SAL1_1_Source_(_Ret_opt_cap_c_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__cap_c_impl(size)))#define _Ret_bytecap_c_(size)             _SAL1_1_Source_(_Ret_bytecap_c_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__bytecap_c_impl(size)))#define _Ret_opt_bytecap_c_(size)         _SAL1_1_Source_(_Ret_opt_bytecap_c_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__bytecap_c_impl(size)))



#define _Ret_cap_x_(size)                 _SAL1_1_Source_(_Ret_cap_x_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__cap_x_impl(size)))#define _Ret_opt_cap_x_(size)             _SAL1_1_Source_(_Ret_opt_cap_x_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__cap_x_impl(size)))#define _Ret_bytecap_x_(size)             _SAL1_1_Source_(_Ret_bytecap_x_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__bytecap_x_impl(size)))#define _Ret_opt_bytecap_x_(size)         _SAL1_1_Source_(_Ret_opt_bytecap_x_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__bytecap_x_impl(size)))



#define _Ret_z_cap_(size)                 _SAL1_1_Source_(_Ret_z_cap_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret2_impl_(__zterm_impl,__cap_impl(size))     _Ret_valid_impl_)#define _Ret_opt_z_cap_(size)             _SAL1_1_Source_(_Ret_opt_z_cap_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret2_impl_(__zterm_impl,__cap_impl(size))     _Ret_valid_impl_)#define _Ret_z_bytecap_(size)             _SAL1_1_Source_(_Ret_z_bytecap_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret2_impl_(__zterm_impl,__bytecap_impl(size)) _Ret_valid_impl_)#define _Ret_opt_z_bytecap_(size)         _SAL1_1_Source_(_Ret_opt_z_bytecap_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret2_impl_(__zterm_impl,__bytecap_impl(size)) _Ret_valid_impl_)





#define _Ret_count_(size)                 _SAL1_1_Source_(_Ret_count_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__count_impl(size))     _Ret_valid_impl_)#define _Ret_opt_count_(size)             _SAL1_1_Source_(_Ret_opt_count_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__count_impl(size))     _Ret_valid_impl_)#define _Ret_bytecount_(size)             _SAL1_1_Source_(_Ret_bytecount_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__bytecount_impl(size)) _Ret_valid_impl_)#define _Ret_opt_bytecount_(size)         _SAL1_1_Source_(_Ret_opt_bytecount_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__bytecount_impl(size)) _Ret_valid_impl_)



#define _Ret_count_c_(size)               _SAL1_1_Source_(_Ret_count_c_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__count_c_impl(size))     _Ret_valid_impl_)#define _Ret_opt_count_c_(size)           _SAL1_1_Source_(_Ret_opt_count_c_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__count_c_impl(size))     _Ret_valid_impl_)#define _Ret_bytecount_c_(size)           _SAL1_1_Source_(_Ret_bytecount_c_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__bytecount_c_impl(size)) _Ret_valid_impl_)#define _Ret_opt_bytecount_c_(size)       _SAL1_1_Source_(_Ret_opt_bytecount_c_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__bytecount_c_impl(size)) _Ret_valid_impl_)



#define _Ret_count_x_(size)               _SAL1_1_Source_(_Ret_count_x_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__count_x_impl(size))     _Ret_valid_impl_)#define _Ret_opt_count_x_(size)           _SAL1_1_Source_(_Ret_opt_count_x_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__count_x_impl(size))     _Ret_valid_impl_)#define _Ret_bytecount_x_(size)           _SAL1_1_Source_(_Ret_bytecount_x_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret1_impl_(__bytecount_x_impl(size)) _Ret_valid_impl_)#define _Ret_opt_bytecount_x_(size)       _SAL1_1_Source_(_Ret_opt_bytecount_x_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret1_impl_(__bytecount_x_impl(size)) _Ret_valid_impl_)



#define _Ret_z_count_(size)               _SAL1_1_Source_(_Ret_z_count_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret2_impl_(__zterm_impl,__count_impl(size))     _Ret_valid_impl_)#define _Ret_opt_z_count_(size)           _SAL1_1_Source_(_Ret_opt_z_count_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret2_impl_(__zterm_impl,__count_impl(size))     _Ret_valid_impl_)#define _Ret_z_bytecount_(size)           _SAL1_1_Source_(_Ret_z_bytecount_, (size), _Ret1_impl_(__notnull_impl_notref) _Ret2_impl_(__zterm_impl,__bytecount_impl(size)) _Ret_valid_impl_)#define _Ret_opt_z_bytecount_(size)       _SAL1_1_Source_(_Ret_opt_z_bytecount_, (size), _Ret1_impl_(__maybenull_impl_notref) _Ret2_impl_(__zterm_impl,__bytecount_impl(size)) _Ret_valid_impl_)





#define _Pre_opt_z_                       _SAL1_1_Source_(_Pre_opt_z_, (), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__zterm_impl) _Pre_valid_impl_)



#define _Pre_readonly_                    _SAL1_1_Source_(_Pre_readonly_, (), _Pre1_impl_(__readaccess_impl_notref))#define _Pre_writeonly_                   _SAL1_1_Source_(_Pre_writeonly_, (), _Pre1_impl_(__writeaccess_impl_notref))





#define _Pre_cap_(size)                   _SAL1_1_Source_(_Pre_cap_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_impl(size)))#define _Pre_opt_cap_(size)               _SAL1_1_Source_(_Pre_opt_cap_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_impl(size)))#define _Pre_bytecap_(size)               _SAL1_1_Source_(_Pre_bytecap_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecap_impl(size)))#define _Pre_opt_bytecap_(size)           _SAL1_1_Source_(_Pre_opt_bytecap_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecap_impl(size)))



#define _Pre_cap_c_(size)                 _SAL1_1_Source_(_Pre_cap_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_c_impl(size)))#define _Pre_opt_cap_c_(size)             _SAL1_1_Source_(_Pre_opt_cap_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_c_impl(size)))#define _Pre_bytecap_c_(size)             _SAL1_1_Source_(_Pre_bytecap_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecap_c_impl(size)))#define _Pre_opt_bytecap_c_(size)         _SAL1_1_Source_(_Pre_opt_bytecap_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecap_c_impl(size)))#define _Pre_cap_c_one_                   _SAL1_1_Source_(_Pre_cap_c_one_, (), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_c_one_notref_impl))#define _Pre_opt_cap_c_one_               _SAL1_1_Source_(_Pre_opt_cap_c_one_, (), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_c_one_notref_impl))



#define _Pre_cap_m_(mult,size)            _SAL1_1_Source_(_Pre_cap_m_, (mult,size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__mult_impl(mult,size)))#define _Pre_opt_cap_m_(mult,size)        _SAL1_1_Source_(_Pre_opt_cap_m_, (mult,size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__mult_impl(mult,size)))





#define _Pre_cap_for_(param)              _SAL1_1_Source_(_Pre_cap_for_, (param), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_for_impl(param)))#define _Pre_opt_cap_for_(param)          _SAL1_1_Source_(_Pre_opt_cap_for_, (param), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_for_impl(param)))



#define _Pre_cap_x_(size)                 _SAL1_1_Source_(_Pre_cap_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_x_impl(size)))#define _Pre_opt_cap_x_(size)             _SAL1_1_Source_(_Pre_opt_cap_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_x_impl(size)))#define _Pre_bytecap_x_(size)             _SAL1_1_Source_(_Pre_bytecap_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecap_x_impl(size)))#define _Pre_opt_bytecap_x_(size)         _SAL1_1_Source_(_Pre_opt_bytecap_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecap_x_impl(size)))



#define _Pre_ptrdiff_cap_(ptr)            _SAL1_1_Source_(_Pre_ptrdiff_cap_, (ptr), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_x_impl(__ptrdiff(ptr))))#define _Pre_opt_ptrdiff_cap_(ptr)        _SAL1_1_Source_(_Pre_opt_ptrdiff_cap_, (ptr), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_x_impl(__ptrdiff(ptr))))



#define _Pre_z_cap_(size)                 _SAL1_1_Source_(_Pre_z_cap_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre2_impl_(__zterm_impl,__cap_impl(size))       _Pre_valid_impl_)#define _Pre_opt_z_cap_(size)             _SAL1_1_Source_(_Pre_opt_z_cap_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre2_impl_(__zterm_impl,__cap_impl(size))       _Pre_valid_impl_)#define _Pre_z_bytecap_(size)             _SAL1_1_Source_(_Pre_z_bytecap_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre2_impl_(__zterm_impl,__bytecap_impl(size))   _Pre_valid_impl_)#define _Pre_opt_z_bytecap_(size)         _SAL1_1_Source_(_Pre_opt_z_bytecap_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre2_impl_(__zterm_impl,__bytecap_impl(size))   _Pre_valid_impl_)

#define _Pre_z_cap_c_(size)               _SAL1_1_Source_(_Pre_z_cap_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre2_impl_(__zterm_impl,__cap_c_impl(size))     _Pre_valid_impl_)#define _Pre_opt_z_cap_c_(size)           _SAL1_1_Source_(_Pre_opt_z_cap_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre2_impl_(__zterm_impl,__cap_c_impl(size))     _Pre_valid_impl_)#define _Pre_z_bytecap_c_(size)           _SAL1_1_Source_(_Pre_z_bytecap_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre2_impl_(__zterm_impl,__bytecap_c_impl(size)) _Pre_valid_impl_)#define _Pre_opt_z_bytecap_c_(size)       _SAL1_1_Source_(_Pre_opt_z_bytecap_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre2_impl_(__zterm_impl,__bytecap_c_impl(size)) _Pre_valid_impl_)

#define _Pre_z_cap_x_(size)               _SAL1_1_Source_(_Pre_z_cap_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre2_impl_(__zterm_impl,__cap_x_impl(size))     _Pre_valid_impl_)#define _Pre_opt_z_cap_x_(size)           _SAL1_1_Source_(_Pre_opt_z_cap_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre2_impl_(__zterm_impl,__cap_x_impl(size))     _Pre_valid_impl_)#define _Pre_z_bytecap_x_(size)           _SAL1_1_Source_(_Pre_z_bytecap_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre2_impl_(__zterm_impl,__bytecap_x_impl(size)) _Pre_valid_impl_)#define _Pre_opt_z_bytecap_x_(size)       _SAL1_1_Source_(_Pre_opt_z_bytecap_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre2_impl_(__zterm_impl,__bytecap_x_impl(size)) _Pre_valid_impl_)



#define _Pre_valid_cap_(size)             _SAL1_1_Source_(_Pre_valid_cap_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_impl(size))       _Pre_valid_impl_)#define _Pre_opt_valid_cap_(size)         _SAL1_1_Source_(_Pre_opt_valid_cap_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_impl(size))       _Pre_valid_impl_)#define _Pre_valid_bytecap_(size)         _SAL1_1_Source_(_Pre_valid_bytecap_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecap_impl(size))   _Pre_valid_impl_)#define _Pre_opt_valid_bytecap_(size)     _SAL1_1_Source_(_Pre_opt_valid_bytecap_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecap_impl(size))   _Pre_valid_impl_)

#define _Pre_valid_cap_c_(size)           _SAL1_1_Source_(_Pre_valid_cap_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_c_impl(size))     _Pre_valid_impl_)#define _Pre_opt_valid_cap_c_(size)       _SAL1_1_Source_(_Pre_opt_valid_cap_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_c_impl(size))     _Pre_valid_impl_)#define _Pre_valid_bytecap_c_(size)       _SAL1_1_Source_(_Pre_valid_bytecap_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecap_c_impl(size)) _Pre_valid_impl_)#define _Pre_opt_valid_bytecap_c_(size)   _SAL1_1_Source_(_Pre_opt_valid_bytecap_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecap_c_impl(size)) _Pre_valid_impl_)

#define _Pre_valid_cap_x_(size)           _SAL1_1_Source_(_Pre_valid_cap_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_x_impl(size))     _Pre_valid_impl_)#define _Pre_opt_valid_cap_x_(size)       _SAL1_1_Source_(_Pre_opt_valid_cap_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_x_impl(size))     _Pre_valid_impl_)#define _Pre_valid_bytecap_x_(size)       _SAL1_1_Source_(_Pre_valid_bytecap_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecap_x_impl(size)) _Pre_valid_impl_)#define _Pre_opt_valid_bytecap_x_(size)   _SAL1_1_Source_(_Pre_opt_valid_bytecap_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecap_x_impl(size)) _Pre_valid_impl_)





#define _Pre_count_(size)                 _SAL1_1_Source_(_Pre_count_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__count_impl(size))       _Pre_valid_impl_)#define _Pre_opt_count_(size)             _SAL1_1_Source_(_Pre_opt_count_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__count_impl(size))       _Pre_valid_impl_)#define _Pre_bytecount_(size)             _SAL1_1_Source_(_Pre_bytecount_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecount_impl(size))   _Pre_valid_impl_)#define _Pre_opt_bytecount_(size)         _SAL1_1_Source_(_Pre_opt_bytecount_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecount_impl(size))   _Pre_valid_impl_)



#define _Pre_count_c_(size)               _SAL1_1_Source_(_Pre_count_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__count_c_impl(size))     _Pre_valid_impl_)#define _Pre_opt_count_c_(size)           _SAL1_1_Source_(_Pre_opt_count_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__count_c_impl(size))     _Pre_valid_impl_)#define _Pre_bytecount_c_(size)           _SAL1_1_Source_(_Pre_bytecount_c_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecount_c_impl(size)) _Pre_valid_impl_)#define _Pre_opt_bytecount_c_(size)       _SAL1_1_Source_(_Pre_opt_bytecount_c_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecount_c_impl(size)) _Pre_valid_impl_)



#define _Pre_count_x_(size)               _SAL1_1_Source_(_Pre_count_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__count_x_impl(size))     _Pre_valid_impl_)#define _Pre_opt_count_x_(size)           _SAL1_1_Source_(_Pre_opt_count_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__count_x_impl(size))     _Pre_valid_impl_)#define _Pre_bytecount_x_(size)           _SAL1_1_Source_(_Pre_bytecount_x_, (size), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__bytecount_x_impl(size)) _Pre_valid_impl_)#define _Pre_opt_bytecount_x_(size)       _SAL1_1_Source_(_Pre_opt_bytecount_x_, (size), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__bytecount_x_impl(size)) _Pre_valid_impl_)



#define _Pre_ptrdiff_count_(ptr)          _SAL1_1_Source_(_Pre_ptrdiff_count_, (ptr), _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__count_x_impl(__ptrdiff(ptr))) _Pre_valid_impl_)#define _Pre_opt_ptrdiff_count_(ptr)      _SAL1_1_Source_(_Pre_opt_ptrdiff_count_, (ptr), _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__count_x_impl(__ptrdiff(ptr))) _Pre_valid_impl_)







#define _Post_maybez_                    _SAL_L_Source_(_Post_maybez_, (), _Post1_impl_(__maybezterm_impl))



#define _Post_cap_(size)                 _SAL1_1_Source_(_Post_cap_, (size), _Post1_impl_(__cap_impl(size)))#define _Post_bytecap_(size)             _SAL1_1_Source_(_Post_bytecap_, (size), _Post1_impl_(__bytecap_impl(size)))



#define _Post_count_(size)               _SAL1_1_Source_(_Post_count_, (size), _Post1_impl_(__count_impl(size))       _Post_valid_impl_)#define _Post_bytecount_(size)           _SAL1_1_Source_(_Post_bytecount_, (size), _Post1_impl_(__bytecount_impl(size))   _Post_valid_impl_)#define _Post_count_c_(size)             _SAL1_1_Source_(_Post_count_c_, (size), _Post1_impl_(__count_c_impl(size))     _Post_valid_impl_)#define _Post_bytecount_c_(size)         _SAL1_1_Source_(_Post_bytecount_c_, (size), _Post1_impl_(__bytecount_c_impl(size)) _Post_valid_impl_)#define _Post_count_x_(size)             _SAL1_1_Source_(_Post_count_x_, (size), _Post1_impl_(__count_x_impl(size))     _Post_valid_impl_)#define _Post_bytecount_x_(size)         _SAL1_1_Source_(_Post_bytecount_x_, (size), _Post1_impl_(__bytecount_x_impl(size)) _Post_valid_impl_)



#define _Post_z_count_(size)             _SAL1_1_Source_(_Post_z_count_, (size), _Post2_impl_(__zterm_impl,__count_impl(size))       _Post_valid_impl_)#define _Post_z_bytecount_(size)         _SAL1_1_Source_(_Post_z_bytecount_, (size), _Post2_impl_(__zterm_impl,__bytecount_impl(size))   _Post_valid_impl_)#define _Post_z_count_c_(size)           _SAL1_1_Source_(_Post_z_count_c_, (size), _Post2_impl_(__zterm_impl,__count_c_impl(size))     _Post_valid_impl_)#define _Post_z_bytecount_c_(size)       _SAL1_1_Source_(_Post_z_bytecount_c_, (size), _Post2_impl_(__zterm_impl,__bytecount_c_impl(size)) _Post_valid_impl_)#define _Post_z_count_x_(size)           _SAL1_1_Source_(_Post_z_count_x_, (size), _Post2_impl_(__zterm_impl,__count_x_impl(size))     _Post_valid_impl_)#define _Post_z_bytecount_x_(size)       _SAL1_1_Source_(_Post_z_bytecount_x_, (size), _Post2_impl_(__zterm_impl,__bytecount_x_impl(size)) _Post_valid_impl_)











#define _Prepost_opt_z_                  _SAL1_1_Source_(_Prepost_opt_z_, (), _Pre_opt_z_  _Post_z_)

#define _Prepost_count_(size)            _SAL1_1_Source_(_Prepost_count_, (size), _Pre_count_(size)           _Post_count_(size))#define _Prepost_opt_count_(size)        _SAL1_1_Source_(_Prepost_opt_count_, (size), _Pre_opt_count_(size)       _Post_count_(size))#define _Prepost_bytecount_(size)        _SAL1_1_Source_(_Prepost_bytecount_, (size), _Pre_bytecount_(size)       _Post_bytecount_(size))#define _Prepost_opt_bytecount_(size)    _SAL1_1_Source_(_Prepost_opt_bytecount_, (size), _Pre_opt_bytecount_(size)   _Post_bytecount_(size))#define _Prepost_count_c_(size)          _SAL1_1_Source_(_Prepost_count_c_, (size), _Pre_count_c_(size)         _Post_count_c_(size))#define _Prepost_opt_count_c_(size)      _SAL1_1_Source_(_Prepost_opt_count_c_, (size), _Pre_opt_count_c_(size)     _Post_count_c_(size))#define _Prepost_bytecount_c_(size)      _SAL1_1_Source_(_Prepost_bytecount_c_, (size), _Pre_bytecount_c_(size)     _Post_bytecount_c_(size))#define _Prepost_opt_bytecount_c_(size)  _SAL1_1_Source_(_Prepost_opt_bytecount_c_, (size), _Pre_opt_bytecount_c_(size) _Post_bytecount_c_(size))#define _Prepost_count_x_(size)          _SAL1_1_Source_(_Prepost_count_x_, (size), _Pre_count_x_(size)         _Post_count_x_(size))#define _Prepost_opt_count_x_(size)      _SAL1_1_Source_(_Prepost_opt_count_x_, (size), _Pre_opt_count_x_(size)     _Post_count_x_(size))#define _Prepost_bytecount_x_(size)      _SAL1_1_Source_(_Prepost_bytecount_x_, (size), _Pre_bytecount_x_(size)     _Post_bytecount_x_(size))#define _Prepost_opt_bytecount_x_(size)  _SAL1_1_Source_(_Prepost_opt_bytecount_x_, (size), _Pre_opt_bytecount_x_(size) _Post_bytecount_x_(size))

#define _Prepost_valid_                   _SAL1_1_Source_(_Prepost_valid_, (), _Pre_valid_     _Post_valid_)#define _Prepost_opt_valid_               _SAL1_1_Source_(_Prepost_opt_valid_, (), _Pre_opt_valid_ _Post_valid_)













#define _Deref_prepost_z_                         _SAL1_1_Source_(_Deref_prepost_z_, (), _Deref_pre_z_      _Deref_post_z_)#define _Deref_prepost_opt_z_                     _SAL1_1_Source_(_Deref_prepost_opt_z_, (), _Deref_pre_opt_z_  _Deref_post_opt_z_)

#define _Deref_prepost_cap_(size)                 _SAL1_1_Source_(_Deref_prepost_cap_, (size), _Deref_pre_cap_(size)                _Deref_post_cap_(size))#define _Deref_prepost_opt_cap_(size)             _SAL1_1_Source_(_Deref_prepost_opt_cap_, (size), _Deref_pre_opt_cap_(size)            _Deref_post_opt_cap_(size))#define _Deref_prepost_bytecap_(size)             _SAL1_1_Source_(_Deref_prepost_bytecap_, (size), _Deref_pre_bytecap_(size)            _Deref_post_bytecap_(size))#define _Deref_prepost_opt_bytecap_(size)         _SAL1_1_Source_(_Deref_prepost_opt_bytecap_, (size), _Deref_pre_opt_bytecap_(size)        _Deref_post_opt_bytecap_(size))

#define _Deref_prepost_cap_x_(size)               _SAL1_1_Source_(_Deref_prepost_cap_x_, (size), _Deref_pre_cap_x_(size)              _Deref_post_cap_x_(size))#define _Deref_prepost_opt_cap_x_(size)           _SAL1_1_Source_(_Deref_prepost_opt_cap_x_, (size), _Deref_pre_opt_cap_x_(size)          _Deref_post_opt_cap_x_(size))#define _Deref_prepost_bytecap_x_(size)           _SAL1_1_Source_(_Deref_prepost_bytecap_x_, (size), _Deref_pre_bytecap_x_(size)          _Deref_post_bytecap_x_(size))#define _Deref_prepost_opt_bytecap_x_(size)       _SAL1_1_Source_(_Deref_prepost_opt_bytecap_x_, (size), _Deref_pre_opt_bytecap_x_(size)      _Deref_post_opt_bytecap_x_(size))

#define _Deref_prepost_z_cap_(size)               _SAL1_1_Source_(_Deref_prepost_z_cap_, (size), _Deref_pre_z_cap_(size)              _Deref_post_z_cap_(size))#define _Deref_prepost_opt_z_cap_(size)           _SAL1_1_Source_(_Deref_prepost_opt_z_cap_, (size), _Deref_pre_opt_z_cap_(size)          _Deref_post_opt_z_cap_(size))#define _Deref_prepost_z_bytecap_(size)           _SAL1_1_Source_(_Deref_prepost_z_bytecap_, (size), _Deref_pre_z_bytecap_(size)          _Deref_post_z_bytecap_(size))#define _Deref_prepost_opt_z_bytecap_(size)       _SAL1_1_Source_(_Deref_prepost_opt_z_bytecap_, (size), _Deref_pre_opt_z_bytecap_(size)      _Deref_post_opt_z_bytecap_(size))

#define _Deref_prepost_valid_cap_(size)           _SAL1_1_Source_(_Deref_prepost_valid_cap_, (size), _Deref_pre_valid_cap_(size)          _Deref_post_valid_cap_(size))#define _Deref_prepost_opt_valid_cap_(size)       _SAL1_1_Source_(_Deref_prepost_opt_valid_cap_, (size), _Deref_pre_opt_valid_cap_(size)      _Deref_post_opt_valid_cap_(size))#define _Deref_prepost_valid_bytecap_(size)       _SAL1_1_Source_(_Deref_prepost_valid_bytecap_, (size), _Deref_pre_valid_bytecap_(size)      _Deref_post_valid_bytecap_(size))#define _Deref_prepost_opt_valid_bytecap_(size)   _SAL1_1_Source_(_Deref_prepost_opt_valid_bytecap_, (size), _Deref_pre_opt_valid_bytecap_(size)  _Deref_post_opt_valid_bytecap_(size))

#define _Deref_prepost_valid_cap_x_(size)           _SAL1_1_Source_(_Deref_prepost_valid_cap_x_, (size), _Deref_pre_valid_cap_x_(size)          _Deref_post_valid_cap_x_(size))#define _Deref_prepost_opt_valid_cap_x_(size)       _SAL1_1_Source_(_Deref_prepost_opt_valid_cap_x_, (size), _Deref_pre_opt_valid_cap_x_(size)      _Deref_post_opt_valid_cap_x_(size))#define _Deref_prepost_valid_bytecap_x_(size)       _SAL1_1_Source_(_Deref_prepost_valid_bytecap_x_, (size), _Deref_pre_valid_bytecap_x_(size)      _Deref_post_valid_bytecap_x_(size))#define _Deref_prepost_opt_valid_bytecap_x_(size)   _SAL1_1_Source_(_Deref_prepost_opt_valid_bytecap_x_, (size), _Deref_pre_opt_valid_bytecap_x_(size)  _Deref_post_opt_valid_bytecap_x_(size))

#define _Deref_prepost_count_(size)             _SAL1_1_Source_(_Deref_prepost_count_, (size), _Deref_pre_count_(size)            _Deref_post_count_(size))#define _Deref_prepost_opt_count_(size)         _SAL1_1_Source_(_Deref_prepost_opt_count_, (size), _Deref_pre_opt_count_(size)        _Deref_post_opt_count_(size))#define _Deref_prepost_bytecount_(size)         _SAL1_1_Source_(_Deref_prepost_bytecount_, (size), _Deref_pre_bytecount_(size)        _Deref_post_bytecount_(size))#define _Deref_prepost_opt_bytecount_(size)     _SAL1_1_Source_(_Deref_prepost_opt_bytecount_, (size), _Deref_pre_opt_bytecount_(size)    _Deref_post_opt_bytecount_(size))

#define _Deref_prepost_count_x_(size)           _SAL1_1_Source_(_Deref_prepost_count_x_, (size), _Deref_pre_count_x_(size)          _Deref_post_count_x_(size))#define _Deref_prepost_opt_count_x_(size)       _SAL1_1_Source_(_Deref_prepost_opt_count_x_, (size), _Deref_pre_opt_count_x_(size)      _Deref_post_opt_count_x_(size))#define _Deref_prepost_bytecount_x_(size)       _SAL1_1_Source_(_Deref_prepost_bytecount_x_, (size), _Deref_pre_bytecount_x_(size)      _Deref_post_bytecount_x_(size))#define _Deref_prepost_opt_bytecount_x_(size)   _SAL1_1_Source_(_Deref_prepost_opt_bytecount_x_, (size), _Deref_pre_opt_bytecount_x_(size)  _Deref_post_opt_bytecount_x_(size))

#define _Deref_prepost_valid_                    _SAL1_1_Source_(_Deref_prepost_valid_, (), _Deref_pre_valid_     _Deref_post_valid_)#define _Deref_prepost_opt_valid_                _SAL1_1_Source_(_Deref_prepost_opt_valid_, (), _Deref_pre_opt_valid_ _Deref_post_opt_valid_)











#define _Deref_out_z_cap_c_(size)  _SAL1_1_Source_(_Deref_out_z_cap_c_, (size), _Deref_pre_cap_c_(size) _Deref_post_z_)#define _Deref_inout_z_cap_c_(size)  _SAL1_1_Source_(_Deref_inout_z_cap_c_, (size), _Deref_pre_z_cap_c_(size) _Deref_post_z_)#define _Deref_out_z_bytecap_c_(size)  _SAL1_1_Source_(_Deref_out_z_bytecap_c_, (size), _Deref_pre_bytecap_c_(size) _Deref_post_z_)#define _Deref_inout_z_bytecap_c_(size)  _SAL1_1_Source_(_Deref_inout_z_bytecap_c_, (size), _Deref_pre_z_bytecap_c_(size) _Deref_post_z_)#define _Deref_inout_z_  _SAL1_1_Source_(_Deref_inout_z_, (), _Deref_prepost_z_)

#pragma endregion Input Buffer SAL 1 compatibility macros















































#if _USE_ATTRIBUTES_FOR_SAL || _USE_DECLSPECS_FOR_SAL // [









define _Always_impl_(annos)            _Group_(annos _SAL_nop_impl_) _On_failure_impl_(annos _SAL_nop_impl_)

define _Bound_impl_                    _SA_annotes0(SAL_bound)

define _Field_range_impl_(min,max)     _Range_impl_(min,max)

define _Literal_impl_                  _SA_annotes1(SAL_constant, __yes)

define _Maybenull_impl_                _SA_annotes1(SAL_null, __maybe)

define _Maybevalid_impl_               _SA_annotes1(SAL_valid, __maybe)

define _Must_inspect_impl_ _Post_impl_ _SA_annotes0(SAL_mustInspect)

define _Notliteral_impl_               _SA_annotes1(SAL_constant, __no)

define _Notnull_impl_                  _SA_annotes1(SAL_null, __no)

define _Notvalid_impl_                 _SA_annotes1(SAL_valid, __no)

define _NullNull_terminated_impl_      _Group_(_SA_annotes1(SAL_nullTerminated, __yes) _SA_annotes1(SAL_readableTo,inexpressibleCount("NullNull terminated string")))

define _Null_impl_                     _SA_annotes1(SAL_null, __yes)

define _Null_terminated_impl_          _SA_annotes1(SAL_nullTerminated, __yes)

define _Out_impl_                      _Pre1_impl_(__notnull_impl_notref) _Pre1_impl_(__cap_c_one_notref_impl) _Post_valid_impl_

define _Out_opt_impl_                  _Pre1_impl_(__maybenull_impl_notref) _Pre1_impl_(__cap_c_one_notref_impl) _Post_valid_impl_

define _Points_to_data_impl_           _At_(*_Curr_, _SA_annotes1(SAL_mayBePointer, __no))

define _Post_satisfies_impl_(cond)     _Post_impl_ _Satisfies_impl_(cond)

define _Post_valid_impl_               _Post1_impl_(__valid_impl)

define _Pre_satisfies_impl_(cond)      _Pre_impl_ _Satisfies_impl_(cond)

define _Pre_valid_impl_                _Pre1_impl_(__valid_impl)

define _Range_impl_(min,max)           _SA_annotes2(SAL_range, min, max)

define _Readable_bytes_impl_(size)     _SA_annotes1(SAL_readableTo, byteCount(size))

define _Readable_elements_impl_(size)  _SA_annotes1(SAL_readableTo, elementCount(size))

define _Ret_valid_impl_                _Ret1_impl_(__valid_impl)

define _Satisfies_impl_(cond)          _SA_annotes1(SAL_satisfies, cond)

define _Valid_impl_                    _SA_annotes1(SAL_valid, __yes)

define _Writable_bytes_impl_(size)     _SA_annotes1(SAL_writableTo, byteCount(size))

define _Writable_elements_impl_(size)  _SA_annotes1(SAL_writableTo, elementCount(size))



define _In_range_impl_(min,max)        _Pre_impl_ _Range_impl_(min,max)

define _Out_range_impl_(min,max)       _Post_impl_ _Range_impl_(min,max)

define _Ret_range_impl_(min,max)       _Post_impl_ _Range_impl_(min,max)

define _Deref_in_range_impl_(min,max)  _Deref_pre_impl_ _Range_impl_(min,max)

define _Deref_out_range_impl_(min,max) _Deref_post_impl_ _Range_impl_(min,max)

define _Deref_ret_range_impl_(min,max) _Deref_post_impl_ _Range_impl_(min,max)



define _Deref_pre_impl_                _Pre_impl_  _Notref_impl_ _Deref_impl_

define _Deref_post_impl_               _Post_impl_ _Notref_impl_ _Deref_impl_









define __AuToQuOtE                     _SA_annotes0(SAL_AuToQuOtE)







define __deferTypecheck                _SA_annotes0(SAL_deferTypecheck)



define _SA_SPECSTRIZE( x ) #x

define _SAL_nop_impl_       

define __nop_impl(x)            x

#endif // ]



#if _USE_ATTRIBUTES_FOR_SAL // [





include "codeanalysis\sourceannotations.h"





define _SA_annotes0(n)                [SAL_annotes(Name=#n)]

define _SA_annotes1(n,pp1)            [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1))]

define _SA_annotes2(n,pp1,pp2)        [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1), p2=_SA_SPECSTRIZE(pp2))]

define _SA_annotes3(n,pp1,pp2,pp3)    [SAL_annotes(Name=#n, p1=_SA_SPECSTRIZE(pp1), p2=_SA_SPECSTRIZE(pp2), p3=_SA_SPECSTRIZE(pp3))]



define _Pre_impl_                     [SAL_pre]

define _Post_impl_                    [SAL_post]

define _Deref_impl_                   [SAL_deref]

define _Notref_impl_                  [SAL_notref]











define __ANNOTATION(fun)              _SA_annotes0(SAL_annotation)  void __SA_##fun;

define __PRIMOP(type, fun)            _SA_annotes0(SAL_primop)  type __SA_##fun;

define __QUALIFIER(fun)               _SA_annotes0(SAL_qualifier)  void __SA_##fun;





define __In_impl_ [SA_Pre(Valid=SA_Yes)] [SA_Pre(Deref=1, Notref=1, Access=SA_Read)] __declspec("SAL_pre SAL_valid")



#elif _USE_DECLSPECS_FOR_SAL // ][





define _SA_annotes0(n)                __declspec(#n)

define _SA_annotes1(n,pp1)            __declspec(#n "(" _SA_SPECSTRIZE(pp1) ")" )

define _SA_annotes2(n,pp1,pp2)        __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) ")")

define _SA_annotes3(n,pp1,pp2,pp3)    __declspec(#n "(" _SA_SPECSTRIZE(pp1) "," _SA_SPECSTRIZE(pp2) "," _SA_SPECSTRIZE(pp3) ")")



define _Pre_impl_                     _SA_annotes0(SAL_pre)

define _Post_impl_                    _SA_annotes0(SAL_post)

define _Deref_impl_                   _SA_annotes0(SAL_deref)

define _Notref_impl_                  _SA_annotes0(SAL_notref)









define __ANNOTATION(fun)              _SA_annotes0(SAL_annotation) void __SA_##fun

 

define __PRIMOP(type, fun)            _SA_annotes0(SAL_primop) type __SA_##fun



define __QUALIFIER(fun)               _SA_annotes0(SAL_qualifier)  void __SA_##fun;



define __In_impl_ _Pre_impl_ _SA_annotes0(SAL_valid) _Pre_impl_ _Deref_impl_ _Notref_impl_ _SA_annotes0(SAL_readonly)



#else // ][





#define _SA_annotes0(n)#define _SA_annotes1(n,pp1)#define _SA_annotes2(n,pp1,pp2)#define _SA_annotes3(n,pp1,pp2,pp3)

#define __ANNOTATION(fun)              #define __PRIMOP(type, fun)            #define __QUALIFIER(type, fun)            

#endif // ]

#if _USE_ATTRIBUTES_FOR_SAL || _USE_DECLSPECS_FOR_SAL // [



__ANNOTATION(SAL_useHeader(void));

__ANNOTATION(SAL_bound(void));

__ANNOTATION(SAL_allocator(void));   

__ANNOTATION(SAL_file_parser(__AuToQuOtE __In_impl_ char *, __In_impl_ char *));

__ANNOTATION(SAL_source_code_content(__In_impl_ char *));

__ANNOTATION(SAL_analysisHint(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_untrusted_data_source(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_untrusted_data_source_this(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_validated(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_validated_this(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_encoded(void));

__ANNOTATION(SAL_adt(__AuToQuOtE __In_impl_ char *, __AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_add_adt_property(__AuToQuOtE __In_impl_ char *, __AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_remove_adt_property(__AuToQuOtE __In_impl_ char *, __AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_transfer_adt_property_from(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_post_type(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_volatile(void));

__ANNOTATION(SAL_nonvolatile(void));

__ANNOTATION(SAL_entrypoint(__AuToQuOtE __In_impl_ char *, __AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_blocksOn(__In_impl_ void*));

__ANNOTATION(SAL_mustInspect(void));





__ANNOTATION(SAL_TypeName(__AuToQuOtE __In_impl_ char *));





__ANNOTATION(SAL_interlocked(void);)



__QUALIFIER(SAL_name(__In_impl_ char *, __In_impl_ char *, __In_impl_ char *);)



__PRIMOP(char *, _Macro_value_(__In_impl_ char *));

__PRIMOP(int, _Macro_defined_(__In_impl_ char *));

__PRIMOP(char *, _Strstr_(__In_impl_ char *, __In_impl_ char *));



#endif // ]

#if _USE_ATTRIBUTES_FOR_SAL // [

define _Check_return_impl_           [SA_Post(MustCheck=SA_Yes)]



define _Success_impl_(expr)          [SA_Success(Condition=#expr)]

define _On_failure_impl_(annos)      [SAL_context(p1="SAL_failed")] _Group_(_Post_impl_ _Group_(annos _SAL_nop_impl_))



define _Printf_format_string_impl_   [SA_FormatString(Style="printf")]

define _Scanf_format_string_impl_    [SA_FormatString(Style="scanf")]

define _Scanf_s_format_string_impl_  [SA_FormatString(Style="scanf_s")]



define _In_bound_impl_               [SA_PreBound(Deref=0)]

define _Out_bound_impl_              [SA_PostBound(Deref=0)]

define _Ret_bound_impl_              [SA_PostBound(Deref=0)]

define _Deref_in_bound_impl_         [SA_PreBound(Deref=1)]

define _Deref_out_bound_impl_        [SA_PostBound(Deref=1)]

define _Deref_ret_bound_impl_        [SA_PostBound(Deref=1)]



define __valid_impl                  Valid=SA_Yes

define __maybevalid_impl             Valid=SA_Maybe

define __notvalid_impl               Valid=SA_No



define __null_impl                   Null=SA_Yes

define __maybenull_impl              Null=SA_Maybe

define __notnull_impl                Null=SA_No



define __null_impl_notref        Null=SA_Yes,Notref=1

define __maybenull_impl_notref   Null=SA_Maybe,Notref=1

define __notnull_impl_notref     Null=SA_No,Notref=1



define __zterm_impl              NullTerminated=SA_Yes

define __maybezterm_impl         NullTerminated=SA_Maybe

define __maybzterm_impl          NullTerminated=SA_Maybe

define __notzterm_impl           NullTerminated=SA_No



define __readaccess_impl         Access=SA_Read

define __writeaccess_impl        Access=SA_Write

define __allaccess_impl          Access=SA_ReadWrite



define __readaccess_impl_notref  Access=SA_Read,Notref=1

define __writeaccess_impl_notref Access=SA_Write,Notref=1

define __allaccess_impl_notref   Access=SA_ReadWrite,Notref=1



#if _MSC_VER >= 1610 // [





define __cap_impl(size)          WritableElements="\n"#size

define __bytecap_impl(size)      WritableBytes="\n"#size

define __bytecount_impl(size)    ValidBytes="\n"#size

define __count_impl(size)        ValidElements="\n"#size



#else // ][

define __cap_impl(size)          WritableElements=#size

define __bytecap_impl(size)      WritableBytes=#size

define __bytecount_impl(size)    ValidBytes=#size

define __count_impl(size)        ValidElements=#size



#endif // ]

define __cap_c_impl(size)        WritableElementsConst=size

define __cap_c_one_notref_impl   WritableElementsConst=1,Notref=1

define __cap_for_impl(param)     WritableElementsLength=#param

define __cap_x_impl(size)        WritableElements="\n@"#size



define __bytecap_c_impl(size)    WritableBytesConst=size

define __bytecap_x_impl(size)    WritableBytes="\n@"#size



define __mult_impl(mult,size)    __cap_impl((mult)*(size))



define __count_c_impl(size)      ValidElementsConst=size

define __count_x_impl(size)      ValidElements="\n@"#size



define __bytecount_c_impl(size)  ValidBytesConst=size

define __bytecount_x_impl(size)  ValidBytes="\n@"#size





define _At_impl_(target, annos)       [SAL_at(p1=#target)] _Group_(annos)

define _At_buffer_impl_(target, iter, bound, annos)  [SAL_at_buffer(p1=#target, p2=#iter, p3=#bound)] _Group_(annos)

define _When_impl_(expr, annos)       [SAL_when(p1=#expr)] _Group_(annos)



define _Group_impl_(annos)            [SAL_begin] annos [SAL_end]

define _GrouP_impl_(annos)            [SAL_BEGIN] annos [SAL_END]



define _Use_decl_anno_impl_               _SA_annotes0(SAL_useHeader) 



define _Pre1_impl_(p1)                    [SA_Pre(p1)]

define _Pre2_impl_(p1,p2)                 [SA_Pre(p1,p2)]

define _Pre3_impl_(p1,p2,p3)              [SA_Pre(p1,p2,p3)]



define _Post1_impl_(p1)                   [SA_Post(p1)]

define _Post2_impl_(p1,p2)                [SA_Post(p1,p2)]

define _Post3_impl_(p1,p2,p3)             [SA_Post(p1,p2,p3)]



define _Ret1_impl_(p1)                    [SA_Post(p1)]

define _Ret2_impl_(p1,p2)                 [SA_Post(p1,p2)]

define _Ret3_impl_(p1,p2,p3)              [SA_Post(p1,p2,p3)]



define _Deref_pre1_impl_(p1)              [SA_Pre(Deref=1,p1)]

define _Deref_pre2_impl_(p1,p2)           [SA_Pre(Deref=1,p1,p2)]

define _Deref_pre3_impl_(p1,p2,p3)        [SA_Pre(Deref=1,p1,p2,p3)]





define _Deref_post1_impl_(p1)             [SA_Post(Deref=1,p1)]

define _Deref_post2_impl_(p1,p2)          [SA_Post(Deref=1,p1,p2)]

define _Deref_post3_impl_(p1,p2,p3)       [SA_Post(Deref=1,p1,p2,p3)]



define _Deref_ret1_impl_(p1)              [SA_Post(Deref=1,p1)]

define _Deref_ret2_impl_(p1,p2)           [SA_Post(Deref=1,p1,p2)]

define _Deref_ret3_impl_(p1,p2,p3)        [SA_Post(Deref=1,p1,p2,p3)]



define _Deref2_pre1_impl_(p1)             [SA_Pre(Deref=2,Notref=1,p1)]

define _Deref2_post1_impl_(p1)            [SA_Post(Deref=2,Notref=1,p1)]

define _Deref2_ret1_impl_(p1)             [SA_Post(Deref=2,Notref=1,p1)]





define __inner_typefix(ctype)             [SAL_typefix(p1=_SA_SPECSTRIZE(ctype))]

define __inner_exceptthat                 [SAL_except]





#elif _USE_DECLSPECS_FOR_SAL // ][

define _Check_return_impl_ __post      _SA_annotes0(SAL_checkReturn)



define _Success_impl_(expr)            _SA_annotes1(SAL_success, expr)

define _On_failure_impl_(annos)        _SA_annotes1(SAL_context, SAL_failed) _Group_(_Post_impl_ _Group_(_SAL_nop_impl_ annos))



define _Printf_format_string_impl_     _SA_annotes1(SAL_IsFormatString, "printf")

define _Scanf_format_string_impl_      _SA_annotes1(SAL_IsFormatString, "scanf")

define _Scanf_s_format_string_impl_    _SA_annotes1(SAL_IsFormatString, "scanf_s")



define _In_bound_impl_                 _Pre_impl_ _Bound_impl_

define _Out_bound_impl_                _Post_impl_ _Bound_impl_

define _Ret_bound_impl_                _Post_impl_ _Bound_impl_

define _Deref_in_bound_impl_           _Deref_pre_impl_ _Bound_impl_

define _Deref_out_bound_impl_          _Deref_post_impl_ _Bound_impl_

define _Deref_ret_bound_impl_          _Deref_post_impl_ _Bound_impl_





define __null_impl              _SA_annotes0(SAL_null) 

define __notnull_impl           _SA_annotes0(SAL_notnull) 

define __maybenull_impl         _SA_annotes0(SAL_maybenull) 



define __valid_impl             _SA_annotes0(SAL_valid) 

define __notvalid_impl          _SA_annotes0(SAL_notvalid) 

define __maybevalid_impl        _SA_annotes0(SAL_maybevalid) 



define __null_impl_notref       _Notref_ _Null_impl_

define __maybenull_impl_notref  _Notref_ _Maybenull_impl_

define __notnull_impl_notref    _Notref_ _Notnull_impl_



define __zterm_impl             _SA_annotes1(SAL_nullTerminated, __yes)

define __maybezterm_impl        _SA_annotes1(SAL_nullTerminated, __maybe)

define __maybzterm_impl         _SA_annotes1(SAL_nullTerminated, __maybe)

define __notzterm_impl          _SA_annotes1(SAL_nullTerminated, __no)



define __readaccess_impl        _SA_annotes1(SAL_access, 0x1)

define __writeaccess_impl       _SA_annotes1(SAL_access, 0x2)

define __allaccess_impl         _SA_annotes1(SAL_access, 0x3)



define __readaccess_impl_notref  _Notref_ _SA_annotes1(SAL_access, 0x1)

define __writeaccess_impl_notref _Notref_ _SA_annotes1(SAL_access, 0x2)

define __allaccess_impl_notref   _Notref_ _SA_annotes1(SAL_access, 0x3)



define __cap_impl(size)         _SA_annotes1(SAL_writableTo,elementCount(size))

define __cap_c_impl(size)       _SA_annotes1(SAL_writableTo,elementCount(size))

define __cap_c_one_notref_impl  _Notref_ _SA_annotes1(SAL_writableTo,elementCount(1))

define __cap_for_impl(param)    _SA_annotes1(SAL_writableTo,inexpressibleCount(sizeof(param)))

define __cap_x_impl(size)       _SA_annotes1(SAL_writableTo,inexpressibleCount(#size))



define __bytecap_impl(size)     _SA_annotes1(SAL_writableTo,byteCount(size))

define __bytecap_c_impl(size)   _SA_annotes1(SAL_writableTo,byteCount(size))

define __bytecap_x_impl(size)   _SA_annotes1(SAL_writableTo,inexpressibleCount(#size))



define __mult_impl(mult,size)   _SA_annotes1(SAL_writableTo,(mult)*(size))



define __count_impl(size)       _SA_annotes1(SAL_readableTo,elementCount(size))

define __count_c_impl(size)     _SA_annotes1(SAL_readableTo,elementCount(size))

define __count_x_impl(size)     _SA_annotes1(SAL_readableTo,inexpressibleCount(#size))



define __bytecount_impl(size)   _SA_annotes1(SAL_readableTo,byteCount(size))

define __bytecount_c_impl(size) _SA_annotes1(SAL_readableTo,byteCount(size))

define __bytecount_x_impl(size) _SA_annotes1(SAL_readableTo,inexpressibleCount(#size))



define _At_impl_(target, annos)     _SA_annotes0(SAL_at(target)) _Group_(annos)

define _At_buffer_impl_(target, iter, bound, annos)  _SA_annotes3(SAL_at_buffer, target, iter, bound) _Group_(annos)

define _Group_impl_(annos)          _SA_annotes0(SAL_begin) annos _SA_annotes0(SAL_end)

define _GrouP_impl_(annos)          _SA_annotes0(SAL_BEGIN) annos _SA_annotes0(SAL_END)

define _When_impl_(expr, annos)     _SA_annotes0(SAL_when(expr)) _Group_(annos)



define _Use_decl_anno_impl_         __declspec("SAL_useHeader()") 



define _Pre1_impl_(p1)              _Pre_impl_ p1

define _Pre2_impl_(p1,p2)           _Pre_impl_ p1 _Pre_impl_ p2

define _Pre3_impl_(p1,p2,p3)        _Pre_impl_ p1 _Pre_impl_ p2 _Pre_impl_ p3



define _Post1_impl_(p1)             _Post_impl_ p1

define _Post2_impl_(p1,p2)          _Post_impl_ p1 _Post_impl_ p2

define _Post3_impl_(p1,p2,p3)       _Post_impl_ p1 _Post_impl_ p2 _Post_impl_ p3



define _Ret1_impl_(p1)              _Post_impl_ p1

define _Ret2_impl_(p1,p2)           _Post_impl_ p1 _Post_impl_ p2

define _Ret3_impl_(p1,p2,p3)        _Post_impl_ p1 _Post_impl_ p2 _Post_impl_ p3



define _Deref_pre1_impl_(p1)        _Deref_pre_impl_ p1

define _Deref_pre2_impl_(p1,p2)     _Deref_pre_impl_ p1 _Deref_pre_impl_ p2

define _Deref_pre3_impl_(p1,p2,p3)  _Deref_pre_impl_ p1 _Deref_pre_impl_ p2 _Deref_pre_impl_ p3



define _Deref_post1_impl_(p1)       _Deref_post_impl_ p1

define _Deref_post2_impl_(p1,p2)    _Deref_post_impl_ p1 _Deref_post_impl_ p2

define _Deref_post3_impl_(p1,p2,p3) _Deref_post_impl_ p1 _Deref_post_impl_ p2 _Deref_post_impl_ p3



define _Deref_ret1_impl_(p1)        _Deref_post_impl_ p1

define _Deref_ret2_impl_(p1,p2)     _Deref_post_impl_ p1 _Deref_post_impl_ p2

define _Deref_ret3_impl_(p1,p2,p3)  _Deref_post_impl_ p1 _Deref_post_impl_ p2 _Deref_post_impl_ p3



define _Deref2_pre1_impl_(p1)       _Deref_pre_impl_ _Notref_impl_ _Deref_impl_ p1

define _Deref2_post1_impl_(p1)      _Deref_post_impl_ _Notref_impl_ _Deref_impl_ p1

define _Deref2_ret1_impl_(p1)       _Deref_post_impl_ _Notref_impl_ _Deref_impl_ p1



define __inner_typefix(ctype)             _SA_annotes1(SAL_typefix, ctype)

define __inner_exceptthat                 _SA_annotes0(SAL_except)



#elif defined(_MSC_EXTENSIONS) && !defined( MIDL_PASS ) && !defined(__midl) && !defined(RC_INVOKED) && defined(_PFT_VER) && _MSC_VER >= 1400 // ][





pragma push_macro( "SA" )

pragma push_macro( "REPEATABLE" )



#ifdef __cplusplus // [define SA( id ) id

define REPEATABLE [repeatable]

#else  // !__cplusplus // ][define SA( id ) SA_##id

define REPEATABLE

#endif  // !__cplusplus // ]

REPEATABLE

[source_annotation_attribute( SA( Parameter ) )]

struct __P_impl

{

#ifdef __cplusplus // [    __P_impl();

#endif // ]   int __d_;

};

typedef struct __P_impl __P_impl;



REPEATABLE

[source_annotation_attribute( SA( ReturnValue ) )]

struct __R_impl

{

#ifdef __cplusplus // [    __R_impl();

#endif // ]   int __d_;

};

typedef struct __R_impl __R_impl;



[source_annotation_attribute( SA( Method ) )]

struct __M_

{

#ifdef __cplusplus // [    __M_();

#endif // ]   int __d_;

};

typedef struct __M_ __M_;



[source_annotation_attribute( SA( All ) )]

struct __A_

{

#ifdef __cplusplus // [    __A_();

#endif // ]   int __d_;

};

typedef struct __A_ __A_;



[source_annotation_attribute( SA( Field ) )]

struct __F_

{

#ifdef __cplusplus // [    __F_();

#endif // ]   int __d_;

};

typedef struct __F_ __F_;



pragma pop_macro( "REPEATABLE" )

pragma pop_macro( "SA" )





define _SAL_nop_impl_



define _At_impl_(target, annos)        [__A_(__d_=0)]

define _At_buffer_impl_(target, iter, bound, annos)  [__A_(__d_=0)]

define _When_impl_(expr, annos)        annos

define _Group_impl_(annos)             annos

define _GrouP_impl_(annos)             annos

define _Use_decl_anno_impl_            [__M_(__d_=0)]



define _Points_to_data_impl_           [__P_impl(__d_=0)]

define _Literal_impl_                  [__P_impl(__d_=0)]

define _Notliteral_impl_               [__P_impl(__d_=0)]



define _Pre_valid_impl_                [__P_impl(__d_=0)]

define _Post_valid_impl_               [__P_impl(__d_=0)]

define _Ret_valid_impl_                [__R_impl(__d_=0)]



define _Check_return_impl_             [__R_impl(__d_=0)]

define _Must_inspect_impl_             [__R_impl(__d_=0)]



define _Success_impl_(expr)            [__M_(__d_=0)]

define _On_failure_impl_(expr)         [__M_(__d_=0)]

define _Always_impl_(expr)             [__M_(__d_=0)]



define _Printf_format_string_impl_     [__P_impl(__d_=0)]

define _Scanf_format_string_impl_      [__P_impl(__d_=0)]

define _Scanf_s_format_string_impl_    [__P_impl(__d_=0)]



define _Raises_SEH_exception_impl_         [__M_(__d_=0)]

define _Maybe_raises_SEH_exception_impl_   [__M_(__d_=0)]



define _In_bound_impl_                 [__P_impl(__d_=0)]

define _Out_bound_impl_                [__P_impl(__d_=0)]

define _Ret_bound_impl_                [__R_impl(__d_=0)]

define _Deref_in_bound_impl_           [__P_impl(__d_=0)]

define _Deref_out_bound_impl_          [__P_impl(__d_=0)]

define _Deref_ret_bound_impl_          [__R_impl(__d_=0)]



define _Range_impl_(min,max)           [__P_impl(__d_=0)]

define _In_range_impl_(min,max)        [__P_impl(__d_=0)]

define _Out_range_impl_(min,max)       [__P_impl(__d_=0)]

define _Ret_range_impl_(min,max)       [__R_impl(__d_=0)]

define _Deref_in_range_impl_(min,max)  [__P_impl(__d_=0)]

define _Deref_out_range_impl_(min,max) [__P_impl(__d_=0)]

define _Deref_ret_range_impl_(min,max) [__R_impl(__d_=0)]



define _Field_range_impl_(min,max)     [__F_(__d_=0)]



define _Pre_satisfies_impl_(cond)      [__A_(__d_=0)]

define _Post_satisfies_impl_(cond)     [__A_(__d_=0)]

define _Satisfies_impl_(cond)          [__A_(__d_=0)]



define _Null_impl_                     [__A_(__d_=0)]

define _Notnull_impl_                  [__A_(__d_=0)]

define _Maybenull_impl_                [__A_(__d_=0)]



define _Valid_impl_                    [__A_(__d_=0)]

define _Notvalid_impl_                 [__A_(__d_=0)]

define _Maybevalid_impl_               [__A_(__d_=0)]



define _Readable_bytes_impl_(size)     [__A_(__d_=0)]

define _Readable_elements_impl_(size)  [__A_(__d_=0)]

define _Writable_bytes_impl_(size)     [__A_(__d_=0)]

define _Writable_elements_impl_(size)  [__A_(__d_=0)]



define _Null_terminated_impl_          [__A_(__d_=0)]

define _NullNull_terminated_impl_      [__A_(__d_=0)]



define _Pre_impl_                      [__P_impl(__d_=0)]

define _Pre1_impl_(p1)                 [__P_impl(__d_=0)]

define _Pre2_impl_(p1,p2)              [__P_impl(__d_=0)]

define _Pre3_impl_(p1,p2,p3)           [__P_impl(__d_=0)]



define _Post_impl_                     [__P_impl(__d_=0)]

define _Post1_impl_(p1)                [__P_impl(__d_=0)]

define _Post2_impl_(p1,p2)             [__P_impl(__d_=0)]

define _Post3_impl_(p1,p2,p3)          [__P_impl(__d_=0)]



define _Ret1_impl_(p1)                 [__R_impl(__d_=0)]

define _Ret2_impl_(p1,p2)              [__R_impl(__d_=0)]

define _Ret3_impl_(p1,p2,p3)           [__R_impl(__d_=0)]



define _Deref_pre1_impl_(p1)           [__P_impl(__d_=0)]

define _Deref_pre2_impl_(p1,p2)        [__P_impl(__d_=0)]

define _Deref_pre3_impl_(p1,p2,p3)     [__P_impl(__d_=0)]



define _Deref_post1_impl_(p1)          [__P_impl(__d_=0)]

define _Deref_post2_impl_(p1,p2)       [__P_impl(__d_=0)]

define _Deref_post3_impl_(p1,p2,p3)    [__P_impl(__d_=0)]



define _Deref_ret1_impl_(p1)           [__R_impl(__d_=0)]

define _Deref_ret2_impl_(p1,p2)        [__R_impl(__d_=0)]

define _Deref_ret3_impl_(p1,p2,p3)     [__R_impl(__d_=0)]



define _Deref2_pre1_impl_(p1)          

define _Deref2_post1_impl_(p1)         

define _Deref2_ret1_impl_(p1)          



#else // ][



#define _SAL_nop_impl_ X

#define _At_impl_(target, annos)#define _When_impl_(expr, annos)#define _Group_impl_(annos)#define _GrouP_impl_(annos)#define _At_buffer_impl_(target, iter, bound, annos)#define _Use_decl_anno_impl_#define _Points_to_data_impl_#define _Literal_impl_#define _Notliteral_impl_#define _Notref_impl_

#define _Pre_valid_impl_#define _Post_valid_impl_#define _Ret_valid_impl_

#define _Check_return_impl_#define _Must_inspect_impl_

#define _Success_impl_(expr)#define _On_failure_impl_(annos)#define _Always_impl_(annos)

#define _Printf_format_string_impl_#define _Scanf_format_string_impl_#define _Scanf_s_format_string_impl_

#define _In_bound_impl_#define _Out_bound_impl_#define _Ret_bound_impl_#define _Deref_in_bound_impl_#define _Deref_out_bound_impl_#define _Deref_ret_bound_impl_

#define _Range_impl_(min,max)#define _In_range_impl_(min,max)#define _Out_range_impl_(min,max)#define _Ret_range_impl_(min,max)#define _Deref_in_range_impl_(min,max)#define _Deref_out_range_impl_(min,max)#define _Deref_ret_range_impl_(min,max)

#define _Satisfies_impl_(expr)#define _Pre_satisfies_impl_(expr)#define _Post_satisfies_impl_(expr)

#define _Null_impl_#define _Notnull_impl_#define _Maybenull_impl_

#define _Valid_impl_#define _Notvalid_impl_#define _Maybevalid_impl_

#define _Field_range_impl_(min,max)

#define _Pre_impl_#define _Pre1_impl_(p1)#define _Pre2_impl_(p1,p2)#define _Pre3_impl_(p1,p2,p3)

#define _Post_impl_#define _Post1_impl_(p1)       #define _Post2_impl_(p1,p2)#define _Post3_impl_(p1,p2,p3)

#define _Ret1_impl_(p1)      #define _Ret2_impl_(p1,p2)#define _Ret3_impl_(p1,p2,p3)

#define _Deref_pre1_impl_(p1)       #define _Deref_pre2_impl_(p1,p2)#define _Deref_pre3_impl_(p1,p2,p3)

#define _Deref_post1_impl_(p1)#define _Deref_post2_impl_(p1,p2)#define _Deref_post3_impl_(p1,p2,p3)

#define _Deref_ret1_impl_(p1)#define _Deref_ret2_impl_(p1,p2)#define _Deref_ret3_impl_(p1,p2,p3)

#define _Deref2_pre1_impl_(p1)#define _Deref2_post1_impl_(p1)#define _Deref2_ret1_impl_(p1)

#define _Readable_bytes_impl_(size)#define _Readable_elements_impl_(size)#define _Writable_bytes_impl_(size)#define _Writable_elements_impl_(size)

#define _Null_terminated_impl_#define _NullNull_terminated_impl_



#define __inner_typefix(ctype)#define __inner_exceptthat

#endif // ]









#define __specstrings

#ifdef  __cplusplus // [#ifndef __nothrow // [define __nothrow __declspec(nothrow)

#endif // ]extern "C" {

#else // ][#ifndef __nothrow // [# define __nothrow#endif // ]#endif  /* __cplusplus */ // ]











#if !defined(__midl) && defined(_PREFAST_) // [

    



    define _SA_SPECSTRIZE( x ) #x



    



    define __null                  _Null_impl_

    define __notnull               _Notnull_impl_

    define __maybenull             _Maybenull_impl_



    



    define __readonly              _Pre1_impl_(__readaccess_impl)

    define __notreadonly           _Pre1_impl_(__allaccess_impl)

    define __maybereadonly         _Pre1_impl_(__readaccess_impl)



    



    define __valid                 _Valid_impl_

    define __notvalid              _Notvalid_impl_

    define __maybevalid            _Maybevalid_impl_



    



    define __readableTo(extent)    _SA_annotes1(SAL_readableTo, extent)



    



    define __elem_readableTo(size)   _SA_annotes1(SAL_readableTo, elementCount( size ))

    

    

    define __byte_readableTo(size)   _SA_annotes1(SAL_readableTo, byteCount(size))

    

    

    define __writableTo(size)   _SA_annotes1(SAL_writableTo, size)



    

    define __elem_writableTo(size)   _SA_annotes1(SAL_writableTo, elementCount( size ))

    

    

    define __byte_writableTo(size)   _SA_annotes1(SAL_writableTo, byteCount( size))



    

    define __deref                 _Deref_impl_

    

    

    define __pre                   _Pre_impl_

    

    

    define __post                  _Post_impl_

    

    

    define __precond(expr)         __pre



    

    define __postcond(expr)        __post



    

    define __exceptthat                __inner_exceptthat

 

    

    define __refparam                  _Notref_ __deref __notreadonly



    



    

    define __inner_control_entrypoint(category) _SA_annotes2(SAL_entrypoint, controlEntry, #category)





    

    define __inner_data_entrypoint(category)    _SA_annotes2(SAL_entrypoint, dataEntry, #category)



    define __inner_override                    _SA_annotes0(__override)

    define __inner_callback                    _SA_annotes0(__callback)

    define __inner_blocksOn(resource)          _SA_annotes1(SAL_blocksOn, resource)

    define __inner_fallthrough_dec             __inline __nothrow void __FallThrough() {}

    define __inner_fallthrough                 __FallThrough();



    define __post_except_maybenull     __post __inner_exceptthat _Maybenull_impl_

    define __pre_except_maybenull      __pre  __inner_exceptthat _Maybenull_impl_



    define __post_deref_except_maybenull       __post __deref __inner_exceptthat _Maybenull_impl_

    define __pre_deref_except_maybenull    __pre  __deref __inner_exceptthat _Maybenull_impl_



    define __inexpressible_readableTo(size)  _Readable_elements_impl_(_Inexpressible_(size))

    define __inexpressible_writableTo(size)  _Writable_elements_impl_(_Inexpressible_(size))





#else // ][    #define __null    #define __notnull    #define __maybenull    #define __readonly    #define __notreadonly    #define __maybereadonly    #define __valid    #define __notvalid    #define __maybevalid    #define __readableTo(extent)    #define __elem_readableTo(size)    #define __byte_readableTo(size)    #define __writableTo(size)    #define __elem_writableTo(size)    #define __byte_writableTo(size)    #define __deref    #define __pre    #define __post    #define __precond(expr)    #define __postcond(expr)    #define __exceptthat    #define __inner_override    #define __inner_callback    #define __inner_blocksOn(resource)    #define __inner_fallthrough_dec    #define __inner_fallthrough    #define __refparam    #define __inner_control_entrypoint(category)    #define __inner_data_entrypoint(category)

    #define __post_except_maybenull    #define __pre_except_maybenull    #define __post_deref_except_maybenull    #define __pre_deref_except_maybenull

    #define __inexpressible_readableTo(size)    #define __inexpressible_writableTo(size)

#endif /* !defined(__midl) && defined(_PREFAST_) */ // ]





#define __ecount(size)                                           _SAL1_Source_(__ecount, (size), __notnull __elem_writableTo(size))#define __bcount(size)                                           _SAL1_Source_(__bcount, (size), __notnull __byte_writableTo(size))#define __in                                                     _SAL1_Source_(__in, (), _In_)#define __in_ecount(size)                                        _SAL1_Source_(__in_ecount, (size), _In_reads_(size))#define __in_bcount(size)                                        _SAL1_Source_(__in_bcount, (size), _In_reads_bytes_(size))#define __in_z                                                   _SAL1_Source_(__in_z, (), _In_z_)#define __in_ecount_z(size)                                      _SAL1_Source_(__in_ecount_z, (size), _In_reads_z_(size))#define __in_bcount_z(size)                                      _SAL1_Source_(__in_bcount_z, (size), __in_bcount(size) __pre __nullterminated)#define __in_nz                                                  _SAL1_Source_(__in_nz, (), __in)#define __in_ecount_nz(size)                                     _SAL1_Source_(__in_ecount_nz, (size), __in_ecount(size))#define __in_bcount_nz(size)                                     _SAL1_Source_(__in_bcount_nz, (size), __in_bcount(size))#define __out                                                    _SAL1_Source_(__out, (), _Out_)#define __out_ecount(size)                                       _SAL1_Source_(__out_ecount, (size), _Out_writes_(size))#define __out_bcount(size)                                       _SAL1_Source_(__out_bcount, (size), _Out_writes_bytes_(size))#define __out_ecount_part(size,length)                           _SAL1_Source_(__out_ecount_part, (size,length), _Out_writes_to_(size,length))#define __out_bcount_part(size,length)                           _SAL1_Source_(__out_bcount_part, (size,length), _Out_writes_bytes_to_(size,length))#define __out_ecount_full(size)                                  _SAL1_Source_(__out_ecount_full, (size), _Out_writes_all_(size))#define __out_bcount_full(size)                                  _SAL1_Source_(__out_bcount_full, (size), _Out_writes_bytes_all_(size))#define __out_z                                                  _SAL1_Source_(__out_z, (), __post __valid __refparam __post __nullterminated)#define __out_z_opt                                              _SAL1_Source_(__out_z_opt, (), __post __valid __refparam __post __nullterminated __pre_except_maybenull)#define __out_ecount_z(size)                                     _SAL1_Source_(__out_ecount_z, (size), __ecount(size) __post __valid __refparam __post __nullterminated)#define __out_bcount_z(size)                                     _SAL1_Source_(__out_bcount_z, (size), __bcount(size) __post __valid __refparam __post __nullterminated)#define __out_ecount_part_z(size,length)                         _SAL1_Source_(__out_ecount_part_z, (size,length), __out_ecount_part(size,length) __post __nullterminated)#define __out_bcount_part_z(size,length)                         _SAL1_Source_(__out_bcount_part_z, (size,length), __out_bcount_part(size,length) __post __nullterminated)#define __out_ecount_full_z(size)                                _SAL1_Source_(__out_ecount_full_z, (size), __out_ecount_full(size) __post __nullterminated)#define __out_bcount_full_z(size)                                _SAL1_Source_(__out_bcount_full_z, (size), __out_bcount_full(size) __post __nullterminated)#define __out_nz                                                 _SAL1_Source_(__out_nz, (), __post __valid __refparam)#define __out_nz_opt                                             _SAL1_Source_(__out_nz_opt, (), __post __valid __refparam __post_except_maybenull_)#define __out_ecount_nz(size)                                    _SAL1_Source_(__out_ecount_nz, (size), __ecount(size) __post __valid __refparam)#define __out_bcount_nz(size)                                    _SAL1_Source_(__out_bcount_nz, (size), __bcount(size) __post __valid __refparam)#define __inout                                                  _SAL1_Source_(__inout, (), _Inout_)#define __inout_ecount(size)                                     _SAL1_Source_(__inout_ecount, (size), _Inout_updates_(size))#define __inout_bcount(size)                                     _SAL1_Source_(__inout_bcount, (size), _Inout_updates_bytes_(size))#define __inout_ecount_part(size,length)                         _SAL1_Source_(__inout_ecount_part, (size,length), _Inout_updates_to_(size,length))#define __inout_bcount_part(size,length)                         _SAL1_Source_(__inout_bcount_part, (size,length), _Inout_updates_bytes_to_(size,length))#define __inout_ecount_full(size)                                _SAL1_Source_(__inout_ecount_full, (size), _Inout_updates_all_(size))#define __inout_bcount_full(size)                                _SAL1_Source_(__inout_bcount_full, (size), _Inout_updates_bytes_all_(size))#define __inout_z                                                _SAL1_Source_(__inout_z, (), _Inout_z_)#define __inout_ecount_z(size)                                   _SAL1_Source_(__inout_ecount_z, (size), _Inout_updates_z_(size))#define __inout_bcount_z(size)                                   _SAL1_Source_(__inout_bcount_z, (size), __inout_bcount(size) __pre __nullterminated __post __nullterminated)#define __inout_nz                                               _SAL1_Source_(__inout_nz, (), __inout)#define __inout_ecount_nz(size)                                  _SAL1_Source_(__inout_ecount_nz, (size), __inout_ecount(size))#define __inout_bcount_nz(size)                                  _SAL1_Source_(__inout_bcount_nz, (size), __inout_bcount(size))#define __ecount_opt(size)                                       _SAL1_Source_(__ecount_opt, (size), __ecount(size)                              __pre_except_maybenull)#define __bcount_opt(size)                                       _SAL1_Source_(__bcount_opt, (size), __bcount(size)                              __pre_except_maybenull)#define __in_opt                                                 _SAL1_Source_(__in_opt, (), _In_opt_)#define __in_ecount_opt(size)                                    _SAL1_Source_(__in_ecount_opt, (size), _In_reads_opt_(size))#define __in_bcount_opt(size)                                    _SAL1_Source_(__in_bcount_opt, (size), _In_reads_bytes_opt_(size))#define __in_z_opt                                               _SAL1_Source_(__in_z_opt, (), _In_opt_z_)#define __in_ecount_z_opt(size)                                  _SAL1_Source_(__in_ecount_z_opt, (size), __in_ecount_opt(size) __pre __nullterminated)#define __in_bcount_z_opt(size)                                  _SAL1_Source_(__in_bcount_z_opt, (size), __in_bcount_opt(size) __pre __nullterminated)#define __in_nz_opt                                              _SAL1_Source_(__in_nz_opt, (), __in_opt)#define __in_ecount_nz_opt(size)                                 _SAL1_Source_(__in_ecount_nz_opt, (size), __in_ecount_opt(size))#define __in_bcount_nz_opt(size)                                 _SAL1_Source_(__in_bcount_nz_opt, (size), __in_bcount_opt(size))#define __out_opt                                                _SAL1_Source_(__out_opt, (), _Out_opt_)#define __out_ecount_opt(size)                                   _SAL1_Source_(__out_ecount_opt, (size), _Out_writes_opt_(size))#define __out_bcount_opt(size)                                   _SAL1_Source_(__out_bcount_opt, (size), _Out_writes_bytes_opt_(size))#define __out_ecount_part_opt(size,length)                       _SAL1_Source_(__out_ecount_part_opt, (size,length), __out_ecount_part(size,length)              __pre_except_maybenull)#define __out_bcount_part_opt(size,length)                       _SAL1_Source_(__out_bcount_part_opt, (size,length), __out_bcount_part(size,length)              __pre_except_maybenull)#define __out_ecount_full_opt(size)                              _SAL1_Source_(__out_ecount_full_opt, (size), __out_ecount_full(size)                     __pre_except_maybenull)#define __out_bcount_full_opt(size)                              _SAL1_Source_(__out_bcount_full_opt, (size), __out_bcount_full(size)                     __pre_except_maybenull)#define __out_ecount_z_opt(size)                                 _SAL1_Source_(__out_ecount_z_opt, (size), __out_ecount_opt(size) __post __nullterminated)#define __out_bcount_z_opt(size)                                 _SAL1_Source_(__out_bcount_z_opt, (size), __out_bcount_opt(size) __post __nullterminated)#define __out_ecount_part_z_opt(size,length)                     _SAL1_Source_(__out_ecount_part_z_opt, (size,length), __out_ecount_part_opt(size,length) __post __nullterminated)#define __out_bcount_part_z_opt(size,length)                     _SAL1_Source_(__out_bcount_part_z_opt, (size,length), __out_bcount_part_opt(size,length) __post __nullterminated)#define __out_ecount_full_z_opt(size)                            _SAL1_Source_(__out_ecount_full_z_opt, (size), __out_ecount_full_opt(size) __post __nullterminated)#define __out_bcount_full_z_opt(size)                            _SAL1_Source_(__out_bcount_full_z_opt, (size), __out_bcount_full_opt(size) __post __nullterminated)#define __out_ecount_nz_opt(size)                                _SAL1_Source_(__out_ecount_nz_opt, (size), __out_ecount_opt(size) __post __nullterminated)#define __out_bcount_nz_opt(size)                                _SAL1_Source_(__out_bcount_nz_opt, (size), __out_bcount_opt(size) __post __nullterminated)#define __inout_opt                                              _SAL1_Source_(__inout_opt, (), _Inout_opt_)#define __inout_ecount_opt(size)                                 _SAL1_Source_(__inout_ecount_opt, (size), __inout_ecount(size)                        __pre_except_maybenull)#define __inout_bcount_opt(size)                                 _SAL1_Source_(__inout_bcount_opt, (size), __inout_bcount(size)                        __pre_except_maybenull)#define __inout_ecount_part_opt(size,length)                     _SAL1_Source_(__inout_ecount_part_opt, (size,length), __inout_ecount_part(size,length)            __pre_except_maybenull)#define __inout_bcount_part_opt(size,length)                     _SAL1_Source_(__inout_bcount_part_opt, (size,length), __inout_bcount_part(size,length)            __pre_except_maybenull)#define __inout_ecount_full_opt(size)                            _SAL1_Source_(__inout_ecount_full_opt, (size), __inout_ecount_full(size)                   __pre_except_maybenull)#define __inout_bcount_full_opt(size)                            _SAL1_Source_(__inout_bcount_full_opt, (size), __inout_bcount_full(size)                   __pre_except_maybenull)#define __inout_z_opt                                            _SAL1_Source_(__inout_z_opt, (), __inout_opt __pre __nullterminated __post __nullterminated)#define __inout_ecount_z_opt(size)                               _SAL1_Source_(__inout_ecount_z_opt, (size), __inout_ecount_opt(size) __pre __nullterminated __post __nullterminated)#define __inout_ecount_z_opt(size)                               _SAL1_Source_(__inout_ecount_z_opt, (size), __inout_ecount_opt(size) __pre __nullterminated __post __nullterminated)#define __inout_bcount_z_opt(size)                               _SAL1_Source_(__inout_bcount_z_opt, (size), __inout_bcount_opt(size))#define __inout_nz_opt                                           _SAL1_Source_(__inout_nz_opt, (), __inout_opt)#define __inout_ecount_nz_opt(size)                              _SAL1_Source_(__inout_ecount_nz_opt, (size), __inout_ecount_opt(size))#define __inout_bcount_nz_opt(size)                              _SAL1_Source_(__inout_bcount_nz_opt, (size), __inout_bcount_opt(size))#define __deref_ecount(size)                                     _SAL1_Source_(__deref_ecount, (size), _Notref_ __ecount(1) __post _Notref_ __elem_readableTo(1) __post _Notref_ __deref _Notref_ __notnull __post __deref __elem_writableTo(size))#define __deref_bcount(size)                                     _SAL1_Source_(__deref_bcount, (size), _Notref_ __ecount(1) __post _Notref_ __elem_readableTo(1) __post _Notref_ __deref _Notref_ __notnull __post __deref __byte_writableTo(size))#define __deref_out                                              _SAL1_Source_(__deref_out, (), _Outptr_)#define __deref_out_ecount(size)                                 _SAL1_Source_(__deref_out_ecount, (size), _Outptr_result_buffer_(size))#define __deref_out_bcount(size)                                 _SAL1_Source_(__deref_out_bcount, (size), _Outptr_result_bytebuffer_(size))#define __deref_out_ecount_part(size,length)                     _SAL1_Source_(__deref_out_ecount_part, (size,length), _Outptr_result_buffer_to_(size,length))#define __deref_out_bcount_part(size,length)                     _SAL1_Source_(__deref_out_bcount_part, (size,length), _Outptr_result_bytebuffer_to_(size,length))#define __deref_out_ecount_full(size)                            _SAL1_Source_(__deref_out_ecount_full, (size), __deref_out_ecount_part(size,size))#define __deref_out_bcount_full(size)                            _SAL1_Source_(__deref_out_bcount_full, (size), __deref_out_bcount_part(size,size))#define __deref_out_z                                            _SAL1_Source_(__deref_out_z, (), _Outptr_result_z_)#define __deref_out_ecount_z(size)                               _SAL1_Source_(__deref_out_ecount_z, (size), __deref_out_ecount(size) __post __deref __nullterminated)#define __deref_out_bcount_z(size)                               _SAL1_Source_(__deref_out_bcount_z, (size), __deref_out_bcount(size) __post __deref __nullterminated)#define __deref_out_nz                                           _SAL1_Source_(__deref_out_nz, (), __deref_out)#define __deref_out_ecount_nz(size)                              _SAL1_Source_(__deref_out_ecount_nz, (size), __deref_out_ecount(size))#define __deref_out_bcount_nz(size)                              _SAL1_Source_(__deref_out_bcount_nz, (size), __deref_out_ecount(size))#define __deref_inout                                            _SAL1_Source_(__deref_inout, (), _Notref_ __notnull _Notref_ __elem_readableTo(1) __pre __deref __valid __post _Notref_ __deref __valid __refparam)#define __deref_inout_z                                          _SAL1_Source_(__deref_inout_z, (), __deref_inout __pre __deref __nullterminated __post _Notref_ __deref __nullterminated)#define __deref_inout_ecount(size)                               _SAL1_Source_(__deref_inout_ecount, (size), __deref_inout __pre __deref __elem_writableTo(size) __post _Notref_ __deref __elem_writableTo(size))#define __deref_inout_bcount(size)                               _SAL1_Source_(__deref_inout_bcount, (size), __deref_inout __pre __deref __byte_writableTo(size) __post _Notref_ __deref __byte_writableTo(size))#define __deref_inout_ecount_part(size,length)                   _SAL1_Source_(__deref_inout_ecount_part, (size,length), __deref_inout_ecount(size) __pre __deref __elem_readableTo(length) __post __deref __elem_readableTo(length))#define __deref_inout_bcount_part(size,length)                   _SAL1_Source_(__deref_inout_bcount_part, (size,length), __deref_inout_bcount(size) __pre __deref __byte_readableTo(length) __post __deref __byte_readableTo(length))#define __deref_inout_ecount_full(size)                          _SAL1_Source_(__deref_inout_ecount_full, (size), __deref_inout_ecount_part(size,size))#define __deref_inout_bcount_full(size)                          _SAL1_Source_(__deref_inout_bcount_full, (size), __deref_inout_bcount_part(size,size))#define __deref_inout_ecount_z(size)                             _SAL1_Source_(__deref_inout_ecount_z, (size), __deref_inout_ecount(size) __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_inout_bcount_z(size)                             _SAL1_Source_(__deref_inout_bcount_z, (size), __deref_inout_bcount(size) __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_inout_nz                                         _SAL1_Source_(__deref_inout_nz, (), __deref_inout)#define __deref_inout_ecount_nz(size)                            _SAL1_Source_(__deref_inout_ecount_nz, (size), __deref_inout_ecount(size))#define __deref_inout_bcount_nz(size)                            _SAL1_Source_(__deref_inout_bcount_nz, (size), __deref_inout_ecount(size))#define __deref_ecount_opt(size)                                 _SAL1_Source_(__deref_ecount_opt, (size), __deref_ecount(size)                        __post_deref_except_maybenull)#define __deref_bcount_opt(size)                                 _SAL1_Source_(__deref_bcount_opt, (size), __deref_bcount(size)                        __post_deref_except_maybenull)#define __deref_out_opt                                          _SAL1_Source_(__deref_out_opt, (), __deref_out                                 __post_deref_except_maybenull)#define __deref_out_ecount_opt(size)                             _SAL1_Source_(__deref_out_ecount_opt, (size), __deref_out_ecount(size)                    __post_deref_except_maybenull)#define __deref_out_bcount_opt(size)                             _SAL1_Source_(__deref_out_bcount_opt, (size), __deref_out_bcount(size)                    __post_deref_except_maybenull)#define __deref_out_ecount_part_opt(size,length)                 _SAL1_Source_(__deref_out_ecount_part_opt, (size,length), __deref_out_ecount_part(size,length)        __post_deref_except_maybenull)#define __deref_out_bcount_part_opt(size,length)                 _SAL1_Source_(__deref_out_bcount_part_opt, (size,length), __deref_out_bcount_part(size,length)        __post_deref_except_maybenull)#define __deref_out_ecount_full_opt(size)                        _SAL1_Source_(__deref_out_ecount_full_opt, (size), __deref_out_ecount_full(size)               __post_deref_except_maybenull)#define __deref_out_bcount_full_opt(size)                        _SAL1_Source_(__deref_out_bcount_full_opt, (size), __deref_out_bcount_full(size)               __post_deref_except_maybenull)#define __deref_out_z_opt                                        _SAL1_Source_(__deref_out_z_opt, (), _Outptr_result_maybenull_z_)#define __deref_out_ecount_z_opt(size)                           _SAL1_Source_(__deref_out_ecount_z_opt, (size), __deref_out_ecount_opt(size) __post __deref __nullterminated)#define __deref_out_bcount_z_opt(size)                           _SAL1_Source_(__deref_out_bcount_z_opt, (size), __deref_out_bcount_opt(size) __post __deref __nullterminated)#define __deref_out_nz_opt                                       _SAL1_Source_(__deref_out_nz_opt, (), __deref_out_opt)#define __deref_out_ecount_nz_opt(size)                          _SAL1_Source_(__deref_out_ecount_nz_opt, (size), __deref_out_ecount_opt(size))#define __deref_out_bcount_nz_opt(size)                          _SAL1_Source_(__deref_out_bcount_nz_opt, (size), __deref_out_bcount_opt(size))#define __deref_inout_opt                                        _SAL1_Source_(__deref_inout_opt, (), __deref_inout                               __pre_deref_except_maybenull __post_deref_except_maybenull)#define __deref_inout_ecount_opt(size)                           _SAL1_Source_(__deref_inout_ecount_opt, (size), __deref_inout_ecount(size)                  __pre_deref_except_maybenull __post_deref_except_maybenull)#define __deref_inout_bcount_opt(size)                           _SAL1_Source_(__deref_inout_bcount_opt, (size), __deref_inout_bcount(size)                  __pre_deref_except_maybenull __post_deref_except_maybenull)#define __deref_inout_ecount_part_opt(size,length)               _SAL1_Source_(__deref_inout_ecount_part_opt, (size,length), __deref_inout_ecount_part(size,length)      __pre_deref_except_maybenull __post_deref_except_maybenull)#define __deref_inout_bcount_part_opt(size,length)               _SAL1_Source_(__deref_inout_bcount_part_opt, (size,length), __deref_inout_bcount_part(size,length)      __pre_deref_except_maybenull __post_deref_except_maybenull)#define __deref_inout_ecount_full_opt(size)                      _SAL1_Source_(__deref_inout_ecount_full_opt, (size), __deref_inout_ecount_full(size)             __pre_deref_except_maybenull __post_deref_except_maybenull)#define __deref_inout_bcount_full_opt(size)                      _SAL1_Source_(__deref_inout_bcount_full_opt, (size), __deref_inout_bcount_full(size)             __pre_deref_except_maybenull __post_deref_except_maybenull)#define __deref_inout_z_opt                                      _SAL1_Source_(__deref_inout_z_opt, (), __deref_inout_opt __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_inout_ecount_z_opt(size)                         _SAL1_Source_(__deref_inout_ecount_z_opt, (size), __deref_inout_ecount_opt(size) __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_inout_bcount_z_opt(size)                         _SAL1_Source_(__deref_inout_bcount_z_opt, (size), __deref_inout_bcount_opt(size) __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_inout_nz_opt                                     _SAL1_Source_(__deref_inout_nz_opt, (), __deref_inout_opt)#define __deref_inout_ecount_nz_opt(size)                        _SAL1_Source_(__deref_inout_ecount_nz_opt, (size), __deref_inout_ecount_opt(size))#define __deref_inout_bcount_nz_opt(size)                        _SAL1_Source_(__deref_inout_bcount_nz_opt, (size), __deref_inout_bcount_opt(size))#define __deref_opt_ecount(size)                                 _SAL1_Source_(__deref_opt_ecount, (size), __deref_ecount(size)                        __pre_except_maybenull)#define __deref_opt_bcount(size)                                 _SAL1_Source_(__deref_opt_bcount, (size), __deref_bcount(size)                        __pre_except_maybenull)#define __deref_opt_out                                          _SAL1_Source_(__deref_opt_out, (), _Outptr_opt_)#define __deref_opt_out_z                                        _SAL1_Source_(__deref_opt_out_z, (), _Outptr_opt_result_z_)#define __deref_opt_out_ecount(size)                             _SAL1_Source_(__deref_opt_out_ecount, (size), __deref_out_ecount(size)                    __pre_except_maybenull)#define __deref_opt_out_bcount(size)                             _SAL1_Source_(__deref_opt_out_bcount, (size), __deref_out_bcount(size)                    __pre_except_maybenull)#define __deref_opt_out_ecount_part(size,length)                 _SAL1_Source_(__deref_opt_out_ecount_part, (size,length), __deref_out_ecount_part(size,length)        __pre_except_maybenull)#define __deref_opt_out_bcount_part(size,length)                 _SAL1_Source_(__deref_opt_out_bcount_part, (size,length), __deref_out_bcount_part(size,length)        __pre_except_maybenull)#define __deref_opt_out_ecount_full(size)                        _SAL1_Source_(__deref_opt_out_ecount_full, (size), __deref_out_ecount_full(size)               __pre_except_maybenull)#define __deref_opt_out_bcount_full(size)                        _SAL1_Source_(__deref_opt_out_bcount_full, (size), __deref_out_bcount_full(size)               __pre_except_maybenull)#define __deref_opt_inout                                        _SAL1_Source_(__deref_opt_inout, (), _Inout_opt_)#define __deref_opt_inout_ecount(size)                           _SAL1_Source_(__deref_opt_inout_ecount, (size), __deref_inout_ecount(size)                  __pre_except_maybenull)#define __deref_opt_inout_bcount(size)                           _SAL1_Source_(__deref_opt_inout_bcount, (size), __deref_inout_bcount(size)                  __pre_except_maybenull)#define __deref_opt_inout_ecount_part(size,length)               _SAL1_Source_(__deref_opt_inout_ecount_part, (size,length), __deref_inout_ecount_part(size,length)      __pre_except_maybenull)#define __deref_opt_inout_bcount_part(size,length)               _SAL1_Source_(__deref_opt_inout_bcount_part, (size,length), __deref_inout_bcount_part(size,length)      __pre_except_maybenull)#define __deref_opt_inout_ecount_full(size)                      _SAL1_Source_(__deref_opt_inout_ecount_full, (size), __deref_inout_ecount_full(size)             __pre_except_maybenull)#define __deref_opt_inout_bcount_full(size)                      _SAL1_Source_(__deref_opt_inout_bcount_full, (size), __deref_inout_bcount_full(size)             __pre_except_maybenull)#define __deref_opt_inout_z                                      _SAL1_Source_(__deref_opt_inout_z, (), __deref_opt_inout __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_opt_inout_ecount_z(size)                         _SAL1_Source_(__deref_opt_inout_ecount_z, (size), __deref_opt_inout_ecount(size) __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_opt_inout_bcount_z(size)                         _SAL1_Source_(__deref_opt_inout_bcount_z, (size), __deref_opt_inout_bcount(size) __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_opt_inout_nz                                     _SAL1_Source_(__deref_opt_inout_nz, (), __deref_opt_inout)#define __deref_opt_inout_ecount_nz(size)                        _SAL1_Source_(__deref_opt_inout_ecount_nz, (size), __deref_opt_inout_ecount(size))#define __deref_opt_inout_bcount_nz(size)                        _SAL1_Source_(__deref_opt_inout_bcount_nz, (size), __deref_opt_inout_bcount(size))#define __deref_opt_ecount_opt(size)                             _SAL1_Source_(__deref_opt_ecount_opt, (size), __deref_ecount_opt(size)                    __pre_except_maybenull)#define __deref_opt_bcount_opt(size)                             _SAL1_Source_(__deref_opt_bcount_opt, (size), __deref_bcount_opt(size)                    __pre_except_maybenull)#define __deref_opt_out_opt                                      _SAL1_Source_(__deref_opt_out_opt, (), _Outptr_opt_result_maybenull_)#define __deref_opt_out_ecount_opt(size)                         _SAL1_Source_(__deref_opt_out_ecount_opt, (size), __deref_out_ecount_opt(size)                __pre_except_maybenull)#define __deref_opt_out_bcount_opt(size)                         _SAL1_Source_(__deref_opt_out_bcount_opt, (size), __deref_out_bcount_opt(size)                __pre_except_maybenull)#define __deref_opt_out_ecount_part_opt(size,length)             _SAL1_Source_(__deref_opt_out_ecount_part_opt, (size,length), __deref_out_ecount_part_opt(size,length)    __pre_except_maybenull)#define __deref_opt_out_bcount_part_opt(size,length)             _SAL1_Source_(__deref_opt_out_bcount_part_opt, (size,length), __deref_out_bcount_part_opt(size,length)    __pre_except_maybenull)#define __deref_opt_out_ecount_full_opt(size)                    _SAL1_Source_(__deref_opt_out_ecount_full_opt, (size), __deref_out_ecount_full_opt(size)           __pre_except_maybenull)#define __deref_opt_out_bcount_full_opt(size)                    _SAL1_Source_(__deref_opt_out_bcount_full_opt, (size), __deref_out_bcount_full_opt(size)           __pre_except_maybenull)#define __deref_opt_out_z_opt                                    _SAL1_Source_(__deref_opt_out_z_opt, (), __post __deref __valid __refparam __pre_except_maybenull __pre_deref_except_maybenull __post_deref_except_maybenull __post __deref __nullterminated)#define __deref_opt_out_ecount_z_opt(size)                       _SAL1_Source_(__deref_opt_out_ecount_z_opt, (size), __deref_opt_out_ecount_opt(size) __post __deref __nullterminated)#define __deref_opt_out_bcount_z_opt(size)                       _SAL1_Source_(__deref_opt_out_bcount_z_opt, (size), __deref_opt_out_bcount_opt(size) __post __deref __nullterminated)#define __deref_opt_out_nz_opt                                   _SAL1_Source_(__deref_opt_out_nz_opt, (), __deref_opt_out_opt)#define __deref_opt_out_ecount_nz_opt(size)                      _SAL1_Source_(__deref_opt_out_ecount_nz_opt, (size), __deref_opt_out_ecount_opt(size))#define __deref_opt_out_bcount_nz_opt(size)                      _SAL1_Source_(__deref_opt_out_bcount_nz_opt, (size), __deref_opt_out_bcount_opt(size))#define __deref_opt_inout_opt                                    _SAL1_Source_(__deref_opt_inout_opt, (), __deref_inout_opt                           __pre_except_maybenull)#define __deref_opt_inout_ecount_opt(size)                       _SAL1_Source_(__deref_opt_inout_ecount_opt, (size), __deref_inout_ecount_opt(size)              __pre_except_maybenull)#define __deref_opt_inout_bcount_opt(size)                       _SAL1_Source_(__deref_opt_inout_bcount_opt, (size), __deref_inout_bcount_opt(size)              __pre_except_maybenull)#define __deref_opt_inout_ecount_part_opt(size,length)           _SAL1_Source_(__deref_opt_inout_ecount_part_opt, (size,length), __deref_inout_ecount_part_opt(size,length)  __pre_except_maybenull)#define __deref_opt_inout_bcount_part_opt(size,length)           _SAL1_Source_(__deref_opt_inout_bcount_part_opt, (size,length), __deref_inout_bcount_part_opt(size,length)  __pre_except_maybenull)#define __deref_opt_inout_ecount_full_opt(size)                  _SAL1_Source_(__deref_opt_inout_ecount_full_opt, (size), __deref_inout_ecount_full_opt(size)         __pre_except_maybenull)#define __deref_opt_inout_bcount_full_opt(size)                  _SAL1_Source_(__deref_opt_inout_bcount_full_opt, (size), __deref_inout_bcount_full_opt(size)         __pre_except_maybenull)#define __deref_opt_inout_z_opt                                  _SAL1_Source_(__deref_opt_inout_z_opt, (), __deref_opt_inout_opt  __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_opt_inout_ecount_z_opt(size)                     _SAL1_Source_(__deref_opt_inout_ecount_z_opt, (size), __deref_opt_inout_ecount_opt(size)  __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_opt_inout_bcount_z_opt(size)                     _SAL1_Source_(__deref_opt_inout_bcount_z_opt, (size), __deref_opt_inout_bcount_opt(size)  __pre __deref __nullterminated __post __deref __nullterminated)#define __deref_opt_inout_nz_opt                                 _SAL1_Source_(__deref_opt_inout_nz_opt, (), __deref_opt_inout_opt)#define __deref_opt_inout_ecount_nz_opt(size)                    _SAL1_Source_(__deref_opt_inout_ecount_nz_opt, (size), __deref_opt_inout_ecount_opt(size))#define __deref_opt_inout_bcount_nz_opt(size)                    _SAL1_Source_(__deref_opt_inout_bcount_nz_opt, (size), __deref_opt_inout_bcount_opt(size))





#define __success(expr)                      _SAL1_1_Source_(__success, (expr), _Success_(expr))#define __nullterminated                     _SAL1_Source_(__nullterminated, (), _Null_terminated_)#define __nullnullterminated                 _SAL1_Source_(__nullnulltermiated, (), _SAL_nop_impl_)#define __reserved                           _SAL1_Source_(__reserved, (), _Reserved_)#define __checkReturn                        _SAL1_Source_(__checkReturn, (), _Check_return_)#define __typefix(ctype)                     _SAL1_Source_(__typefix, (ctype), __inner_typefix(ctype))#define __override                           __inner_override#define __callback                           __inner_callback#define __format_string                      _SAL1_1_Source_(__format_string, (), _Printf_format_string_)#define __blocksOn(resource)                 _SAL_L_Source_(__blocksOn, (resource), __inner_blocksOn(resource))#define __control_entrypoint(category)       _SAL_L_Source_(__control_entrypoint, (category), __inner_control_entrypoint(category))#define __data_entrypoint(category)          _SAL_L_Source_(__data_entrypoint, (category), __inner_data_entrypoint(category))

#ifdef _USING_V110_SDK71_ // [#ifndef _PREFAST_ // [define __useHeader

#else // ][error Code analysis is not supported when using Visual C++ 11.0/12.0 with the Windows 7.1 SDK.

#endif // ]#else // ][#define __useHeader                          _Use_decl_anno_impl_#endif // ]

#ifdef _USING_V110_SDK71_ // [#ifndef _PREFAST_ // [define __on_failure(annotes)

#else // ][error Code analysis is not supported when using Visual C++ 11.0/12.0 with the Windows 7.1 SDK.

#endif // ]#else // ][#define __on_failure(annotes)                _SAL1_1_Source_(__on_failure, (annotes), _On_failure_impl_(annotes _SAL_nop_impl_))#endif // ]

#ifndef __fallthrough // [    __inner_fallthrough_dec 

    #define __fallthrough __inner_fallthrough#endif // ]

#ifndef __analysis_assume // [#ifdef _PREFAST_ // [define __analysis_assume(expr) __assume(!!(expr))

#else // ][#define __analysis_assume(expr) #endif // ]#endif // ]

#ifndef _Analysis_assume_ // [#ifdef _PREFAST_ // [define _Analysis_assume_(expr) __assume(!!(expr))

#else // ][#define _Analysis_assume_(expr) #endif // ]#endif // ]

#define _Analysis_noreturn_    _SAL2_Source_(_Analysis_noreturn_, (), _SA_annotes0(SAL_terminates))

#ifdef _PREFAST_ // [__inline __nothrow 

void __AnalysisAssumeNullterminated(_Post_ _Null_terminated_ const void *p);



define _Analysis_assume_nullterminated_(x) __AnalysisAssumeNullterminated(x)



#else // ][#define _Analysis_assume_nullterminated_(x)#endif // ]















#define ___MKID(x, y) x ## y#define __MKID(x, y) ___MKID(x, y)#define __GENSYM(x) __MKID(x, __COUNTER__)

__ANNOTATION(SAL_analysisMode(__AuToQuOtE __In_impl_ char *mode);) 



#define _Analysis_mode_impl_(mode) _SAL2_Source_(_Analysis_mode_impl_, (mode), _SA_annotes1(SAL_analysisMode, #mode))









#ifndef _M_IX86 // [

define _Analysis_mode_(mode)                                                     __pragma(warning(disable: 28110 28111 28161 28162))                           typedef _Analysis_mode_impl_(mode) int                                            __GENSYM(__prefast_analysis_mode_flag);



#else // ][

#define _Analysis_mode_(mode)                                                     typedef _Analysis_mode_impl_(mode) int                                            __GENSYM(__prefast_analysis_mode_flag);

#endif // ]















__ANNOTATION(SAL_functionClassNew(__In_impl_ char*);) 

__PRIMOP(int, _In_function_class_(__In_impl_ char*);) 

#define _In_function_class_(x)  _In_function_class_(#x)#define _Called_from_function_class_(x) _In_function_class_(x)

#define _Function_class_(x)  _SAL2_Source_(_Function_class_, (x), _SA_annotes1(SAL_functionClassNew, _SA_SPECSTRIZE(x)))

#define _Enum_is_bitflag_    _SAL2_Source_(_Enum_is_bitflag_, (), _SA_annotes0(SAL_enumIsBitflag))#define _Strict_type_match_  _SAL2_Source_(_Strict_type_match, (), _SA_annotes0(SAL_strictType2))

#define _Maybe_raises_SEH_exception_   _SAL2_Source_(_Maybe_raises_SEH_exception_, (x), _Pre_ _SA_annotes1(SAL_inTry,__yes))#define _Raises_SEH_exception_         _SAL2_Source_(_Raises_SEH_exception_, (x), _Maybe_raises_SEH_exception_ _Analysis_noreturn_)



__ANNOTATION(SAL_externalIntf(void);) 

#define _Published_ _SAL2_Source_(_Published_, (), _SA_annotes0(SAL_externalIntf))

#ifdef  __cplusplus // [}

#endif // ]

#include <ConcurrencySal.h>



#ifndef CONCURRENCYSAL_H#define CONCURRENCYSAL_H

#pragma once

#ifdef  __cplusplus // [extern "C" {

#endif  // ]

#if !defined(__midl) && defined(_PREFAST_) && _MSC_VER >= 1000 && !defined(_SDV_)

__ANNOTATION(SAL_guarded_by(__deferTypecheck void *));

__ANNOTATION(SAL_write_guarded_by(__deferTypecheck void *));

__ANNOTATION(SAL_requires_lock_held(__deferTypecheck void *));

__ANNOTATION(SAL_requires_exclusive_lock_held(__deferTypecheck void *));

__ANNOTATION(SAL_requires_shared_lock_held(__deferTypecheck void *));

__ANNOTATION(SAL_requires_lock_not_held(__deferTypecheck void *));

__ANNOTATION(SAL_requires_no_locks_held(void));

__ANNOTATION(SAL_set_lock_count_to_zero(__deferTypecheck void *));

__ANNOTATION(SAL_set_lock_count_to_one(__deferTypecheck void *));

__ANNOTATION(SAL_acquires_lock(__deferTypecheck void *));

__ANNOTATION(SAL_acquires_exclusive_lock(__deferTypecheck void *));

__ANNOTATION(SAL_acquires_shared_lock(__deferTypecheck void *));

__ANNOTATION(SAL_releases_lock(__deferTypecheck void *));

__ANNOTATION(SAL_releases_exclusive_lock(__deferTypecheck void *));

__ANNOTATION(SAL_releases_shared_lock(__deferTypecheck void *));

__ANNOTATION(SAL_ignore_lock_match(__deferTypecheck void *));

__ANNOTATION(SAL_has_lock_property(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_has_lock_level(__AuToQuOtE __In_impl_ char *));

__ANNOTATION(SAL_lock_level_order(__deferTypecheck void *, __deferTypecheck void *));

__ANNOTATION(SAL_no_competing_thread(void));

__ANNOTATION(SAL_set_same_lock(__deferTypecheck void *, __deferTypecheck void *));





extern int _Global_interlock_;

extern int _Global_cancel_spin_lock_;

extern int _Global_critical_region_;





define _Internal_create_CSAL_identifier_(id) const char id##[] = "";



_Internal_create_CSAL_identifier_(_Lock_kind_mutex_)

_Internal_create_CSAL_identifier_(_Lock_kind_event_)

_Internal_create_CSAL_identifier_(_Lock_kind_semaphore_)

_Internal_create_CSAL_identifier_(_Lock_kind_spin_lock_)

_Internal_create_CSAL_identifier_(_Lock_kind_critical_section_)





define _Guarded_by_(lock) _SAL2_Source_(_Guarded_by_, (lock), _SA_annotes1(SAL_guarded_by,lock))

define _Write_guarded_by_(lock) _SAL2_Source_(_Write_guarded_by_, (lock), _SA_annotes1(SAL_write_guarded_by,lock))

define _Interlocked_ _Guarded_by_(_Global_interlock_)





#ifndef _Interlocked_operand_define _Interlocked_operand_ _SAL2_Source_(_Interlocked_operand_, (), _Pre_ _SA_annotes0(SAL_interlocked))

#endif



define _Requires_lock_held_(lock)  _SAL2_Source_(_Requires_lock_held_, (lock), _Pre_ _SA_annotes1(SAL_requires_lock_held,lock))

define _Requires_exclusive_lock_held_(lock)  _SAL2_Source_(_Requires_exclusive_lock_held_, (lock), _Pre_ _SA_annotes1(SAL_requires_exclusive_lock_held,lock))

define _Requires_shared_lock_held_(lock)  _SAL2_Source_(_Requires_shared_lock_held_, (lock), _Pre_ _SA_annotes1(SAL_requires_shared_lock_held,lock))



define _Requires_lock_not_held_(lock)  _SAL2_Source_(_Requires_lock_not_held_, (lock), _Pre_ _SA_annotes1(SAL_requires_lock_not_held,lock))

define _Requires_no_locks_held_  _SAL2_Source_(_Requires_no_locks_held_, (), _Pre_ _SA_annotes0(SAL_requires_no_locks_held))





define _Acquires_lock_(lock)  _SAL2_Source_(_Acquires_lock_, (lock), _Post_ _SA_annotes1(SAL_acquires_lock,lock))

define _Acquires_exclusive_lock_(lock)  _SAL2_Source_(_Acquires_exclusive_lock_, (lock), _Post_ _SA_annotes1(SAL_acquires_exclusive_lock,lock))

define _Acquires_shared_lock_(lock)  _SAL2_Source_(_Acquires_shared_lock_, (lock), _Post_ _SA_annotes1(SAL_acquires_shared_lock,lock))



define _Releases_lock_(lock)  _SAL2_Source_(_Releases_lock_, (lock), _Post_ _SA_annotes1(SAL_releases_lock,lock))

define _Releases_exclusive_lock_(lock)  _SAL2_Source_(_Releases_exclusive_lock_, (lock), _Post_ _SA_annotes1(SAL_releases_exclusive_lock,lock))

define _Releases_shared_lock_(lock)  _SAL2_Source_(_Releases_shared_lock_, (lock), _Post_ _SA_annotes1(SAL_releases_shared_lock,lock))





define _Acquires_nonreentrant_lock_(lock)      _SAL2_Source_(_Acquires_nonreentrant_lock_, (lock),     _Requires_lock_not_held_(lock)     _Acquires_lock_(lock))



define _Releases_nonreentrant_lock_(lock)      _SAL2_Source_(_Releases_nonreentrant_lock_, (lock),     _Requires_lock_held_(lock)     _Releases_lock_(lock))



define _Post_same_lock_(a,b)  _SAL2_Source_(_Post_same_lock_, (a,b), _Post_ _SA_annotes2(SAL_set_same_lock,a,b))





define _Create_lock_level_(level) _Internal_create_CSAL_identifier_(level)



define _Has_lock_level_(level)  _SAL2_Source_(_Has_lock_level_, (level), _SA_annotes1(SAL_has_lock_level,#level))



define _Internal_lock_level_order_(a,b)  _SAL2_Source_(_Internal_lock_level_order_, (a,b), _SA_annotes2(SAL_lock_level_order,a,b))

define _Csalcat1_(x,y) x##y

define _Csalcat2_(x,y) _Csalcat1_(x,y)



define _Lock_level_order_(a,b)     extern _Internal_lock_level_order_(a,b) void _Sal_order_##a##_##b(_In_z_ char*a, _In_z_ char*b);     static __inline void CSALCAT2(CSAL_LockOrder,__COUNTER__)(void){_Sal_order_##a##_##b(#a,#b);}





define _No_competing_thread_  _SAL2_Source_(_No_competing_thread_, (), _Pre_ _SA_annotes0(SAL_no_competing_thread))





extern _Acquires_lock_(*plock) void _Internal_acquires_lock_(void* plock);

extern _Releases_lock_(*plock) void _Internal_releases_lock_(void* plock);



define _Internal_set_lock_count_to_zero_(lock)  _SAL2_Source_(Internal_set_lock_count_to_zero_, (lock), _Post_ _SA_annotes1(SAL_set_lock_count_to_zero,lock))

define _Internal_set_lock_count_to_one_(lock)  _SAL2_Source_(_Internal_set_lock_count_to_one_, (lock), _Post_ _SA_annotes1(SAL_set_lock_count_to_one,lock))



extern _Internal_set_lock_count_to_one_(*plock) void _Internal_lock_held_(void* plock);

extern _Internal_set_lock_count_to_zero_(*plock) void _Internal_lock_not_held_(void* plock);

extern _Post_same_lock_(*plock1, *plock2) void _Internal_same_lock_(void* plock1, void* plock2);



define _Analysis_assume_lock_acquired_(lock)  _Internal_acquires_lock_((void*)(&(lock)))

define _Analysis_assume_lock_released_(lock)  _Internal_releases_lock_((void*)(&(lock)))



define _Analysis_assume_lock_held_(lock) _Internal_lock_held_((void*)(&(lock)))

define _Analysis_assume_lock_not_held_(lock) _Internal_lock_not_held_((void*)(&(lock)))

define _Analysis_assume_same_lock_(lock1, lock2) _Internal_same_lock_((void*)(&(lock1)), (void*)(&(lock2)))





define _Function_ignore_lock_checking_(lock)  _SAL2_Source_(_Function_ignore_lock_checking_, (lock), _Pre_ _SA_annotes1(SAL_ignore_lock_match,lock))

extern _Function_ignore_lock_checking_(*plock) void _Internal_suppress_lock_checking_(void* plock);





define _Analysis_suppress_lock_checking_(lock) _Internal_suppress_lock_checking_((void*)(&(lock)));



define _Benign_race_begin_ __pragma(warning(push)) __pragma(warning(disable:26100 26101 26150 26130 26180 26131 26181 28112))

define _Benign_race_end_ __pragma(warning(pop))



define _No_competing_thread_begin_ __pragma(warning(push)) __pragma(warning(disable:26100 26101 26150 26101 26151 26110 26160 26130 26180 26131 26181 28112))

define _No_competing_thread_end_ __pragma(warning(pop))





define _Has_lock_kind_(kind)  _SAL2_Source_(_Has_lock_kind_, (kind), _SA_annotes1(SAL_has_lock_property,#kind))







extern int __system_interlock;

extern int __system_cancel_spinlock;

extern int __system_critical_region;



define __guarded_by(lock) _SAL1_1_Source_(__guarded_by, (lock), _SA_annotes1(SAL_guarded_by,lock))

define __write_guarded_by(lock) _SAL1_1_Source_(__write_guarded_by, (lock), _SA_annotes1(SAL_write_guarded_by,lock))

define __interlocked __guarded_by(_Global_interlock_)





define __requires_lock_held(lock) _SAL1_1_Source_(__requires_lock_held, (lock), __pre _SA_annotes1(SAL_requires_lock_held,lock))

define __requires_exclusive_lock_held(lock) _SAL1_1_Source_(__requires_exclusive_lock_held, (lock), __pre _SA_annotes1(SAL_requires_exclusive_lock_held,lock))

define __requires_shared_lock_held(lock) _SAL1_1_Source_(__requires_shared_lock_held, (lock), __pre _SA_annotes1(SAL_requires_shared_lock_held,lock))



define __requires_lock_not_held(lock) _SAL1_1_Source_(__requires_lock_not_held, (lock), __pre _SA_annotes1(SAL_requires_lock_not_held,lock))

define __requires_no_locks_held _SAL1_1_Source_(__requires_no_locks_held, (), __pre _SA_annotes0(SAL_requires_no_locks_held))





define __acquires_lock(lock) _SAL1_1_Source_(__acquires_lock, (lock), __post _SA_annotes1(SAL_acquires_lock,lock))

define __acquires_exclusive_lock(lock) _SAL1_1_Source_(__acquires_exclusive_lock, (lock), __post _SA_annotes1(SAL_acquires_exclusive_lock,lock))

define __acquires_shared_lock(lock) _SAL1_1_Source_(__acquires_shared_lock, (lock), __post _SA_annotes1(SAL_acquires_shared_lock,lock))



define __releases_lock(lock) _SAL1_1_Source_(__releases_lock, (lock), __post _SA_annotes1(SAL_releases_lock,lock))

define __releases_exclusive_lock(lock) _SAL1_1_Source_(__releases_exclusive_lock, (lock),__post _SA_annotes1(SAL_releases_exclusive_lock,lock))

define __releases_shared_lock(lock) _SAL1_1_Source_(__releases_shared_lock, (lock), __post _SA_annotes1(SAL_releases_shared_lock,lock))





define __has_lock_property(kind) _SAL1_1_Source_(__has_lock_property, (kind), _SA_annotes1(SAL_has_lock_property,#kind))





define __declare_lock_level(level) _Internal_create_CSAL_identifier_(level)

define __has_lock_level(level) _SAL1_1_Source_(__has_lock_level, (level), _SA_annotes1(SAL_has_lock_level,#level))



define __internal_lock_level_order(a,b) _SAL1_1_Source_(__internal_lock_level_order, (a,b), _SA_annotes2(SAL_lock_level_order,#a,#b))

define CSALCAT1(x,y) x##y

define CSALCAT2(x,y) CSALCAT1(x,y)



define __lock_level_order(a,b)     extern __internal_lock_level_order(a,b) void __sal_order_##a##_##b(__in_z char*a, __in_z char*b);     static __inline void CSALCAT2(CSAL_LockOrder,__COUNTER__)(void){__sal_order_##a##_##b(#a,#b);}





define __no_competing_thread _SAL1_1_Source_(__no_competing_thread, (), __pre _SA_annotes0(SAL_no_competing_thread))





extern __acquires_lock(*plock) void __internal_acquires_lock(void* plock);

extern __releases_lock(*plock) void __internal_releases_lock(void* plock);



define __analysis_assume_lock_acquired(lock) __internal_acquires_lock((void*)(&(lock)))

define __analysis_assume_lock_released(lock) __internal_releases_lock((void*)(&(lock)))



define __function_ignore_lock_checking(lock) _SAL1_1_Source_(__function_ignore_lock_cleanup, (lock), __pre _SA_annotes1(SAL_ignore_lock_match,lock))

extern __function_ignore_lock_checking(*plock) void __internal_suppress_lock_checking(void* plock);



define __analysis_suppress_lock_checking(lock) __internal_suppress_lock_checking((void*)(&(lock)));



define BENIGN_RACE_BEGIN __pragma(warning(push)) __pragma(warning(disable:26100 26150 26130 26180 26131 26181))

define BENIGN_RACE_END __pragma(warning(pop))



define NO_COMPETING_THREAD_BEGIN __pragma(warning(push)) __pragma(warning(disable:26100 26150 26101 26151 26110 26160 26130 26180 26131 26181))

define NO_COMPETING_THREAD_END __pragma(warning(pop))



#else

#ifndef _Interlocked_operand_#define _Interlocked_operand_#endif

#define _Guarded_by_(lock)#define _Write_guarded_by_(lock)#define _Interlocked_#define _Requires_lock_held_(lock)#define _Requires_exclusive_lock_held_(lock)#define _Requires_shared_lock_held_(lock)#define _Requires_lock_not_held_(lock)#define _Requires_no_locks_held_#define _Acquires_lock_(lock)#define _Acquires_exclusive_lock_(lock)#define _Acquires_shared_lock_(lock)#define _Releases_lock_(lock)#define _Releases_exclusive_lock_(lock)#define _Releases_shared_lock_(lock)#define _Acquires_nonreentrant_lock_(lock)#define _Releases_nonreentrant_lock_(lock)

#define _Post_same_lock_(lock1,lock2)

#define _Internal_set_lock_count_(lock, count)

#define _Create_lock_level_(level)#define _Has_lock_level_(level)#define _Internal_lock_level_order_(a,b)#define _Csalcat1_(x,y)#define _Csalcat2_(x,y)#define _Lock_level_order_(a,b)#define _No_competing_thread_#define _Analysis_assume_lock_acquired_(lock)#define _Analysis_assume_lock_released_(lock)#define _Analysis_assume_lock_held_(lock)#define _Analysis_assume_lock_not_held_(lock)#define _Analysis_assume_same_lock_(lock1, lock2)#define _Function_ignore_lock_checking_(lock)#define _Analysis_suppress_lock_checking_(lock)

#define _Benign_race_begin_ __pragma(warning(push))#define _Benign_race_end_ __pragma(warning(pop))

#define _No_competing_thread_begin_ __pragma(warning(push))#define _No_competing_thread_end_ __pragma(warning(pop))

#define _Has_lock_kind_(kind)



#define __guarded_by(lock)#define __write_guarded_by(lock)#define __interlocked#define __requires_lock_held(lock)#define __requires_exclusive_lock_held(lock)#define __requires_shared_lock_held(lock)#define __requires_lock_not_held(lock)#define __requires_no_locks_held#define __acquires_lock(lock)#define __acquires_exclusive_lock(lock)#define __acquires_shared_lock(lock)#define __releases_lock(lock)#define __releases_exclusive_lock(lock)#define __releases_shared_lock(lock)

#define __has_lock_property(kind)#define __declare_lock_level(level)#define __has_lock_level(level)#define __internal_lock_level_order(a,b)#define CSALCAT1(x,y)#define CSALCAT2(x,y)#define __lock_level_order(a,b)#define __no_competing_thread#define __analysis_assume_lock_acquired(lock)#define __analysis_assume_lock_released(lock)#define __function_ignore_lock_checking(lock)#define __analysis_suppress_lock_checking(lock) 

#define BENIGN_RACE_BEGIN __pragma(warning(push))#define BENIGN_RACE_END __pragma(warning(pop))

#define NO_COMPETING_THREAD_BEGIN __pragma(warning(push))#define NO_COMPETING_THREAD_END __pragma(warning(pop))

#endif

#ifdef __cplusplus}

#endif

#endif // CONCURRENCYSAL_H

#include <vadefs.h>



















#pragma once#define _INC_VADEFS

#define _CRT_PACKING 8#pragma pack(push, _CRT_PACKING)

#ifdef __cplusplusextern "C" {

#endif

#if !defined _W64#define _W64#endif

#ifndef _UINTPTR_T_DEFINED    #define _UINTPTR_T_DEFINED    #ifdef _WIN64        typedef unsigned __int64  uintptr_t;

    #else        typedef unsigned int uintptr_t;

    #endif#endif

#ifndef _VA_LIST_DEFINED    #define _VA_LIST_DEFINED    #ifdef _M_CEE_PURE        typedef System::ArgIterator va_list;

    #else        typedef char* va_list;

    #endif#endif

#ifdef __cplusplus    define _ADDRESSOF(v) (&const_cast<char&>(reinterpret_cast<const volatile char&>(v)))

#else    #define _ADDRESSOF(v) (&(v))#endif

#if defined _M_ARM && !defined _M_CEE_PURE    define _VA_ALIGN       4

    define _SLOTSIZEOF(t)  ((sizeof(t) + _VA_ALIGN - 1) & ~(_VA_ALIGN - 1))

    define _APALIGN(t,ap)  (((va_list)0 - (ap)) & (__alignof(t) - 1))

#elif defined _M_ARM64 && !defined _M_CEE_PURE    define _VA_ALIGN       8

    define _SLOTSIZEOF(t)  ((sizeof(t) + _VA_ALIGN - 1) & ~(_VA_ALIGN - 1))

    define _APALIGN(t,ap)  (((va_list)0 - (ap)) & (__alignof(t) - 1))

#else    #define _SLOTSIZEOF(t)  (sizeof(t))    #define _APALIGN(t,ap)  (__alignof(t))#endif

#if defined _M_CEE_PURE || (defined _M_CEE && !defined _M_ARM && !defined _M_ARM64)

    void  __cdecl __va_start(va_list*, ...);

    void* __cdecl __va_arg(va_list*, ...);

    void  __cdecl __va_end(va_list*);



    define __crt_va_start_a(ap, v) ((void)(__va_start(&ap, _ADDRESSOF(v), _SLOTSIZEOF(v), __alignof(v), _ADDRESSOF(v))))

    define __crt_va_arg(ap, t)     (*(t *)__va_arg(&ap, _SLOTSIZEOF(t), _APALIGN(t,ap), (t*)0))

    define __crt_va_end(ap)        ((void)(__va_end(&ap)))



#elif defined _M_IX86

    #define _INTSIZEOF(n)          ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

    #define __crt_va_start_a(ap, v) ((void)(ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v)))    #define __crt_va_arg(ap, t)     (*(t*)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)))    #define __crt_va_end(ap)        ((void)(ap = (va_list)0))

#elif defined _M_ARM

    #ifdef __cplusplus        void __cdecl __va_start(va_list*, ...);

        define __crt_va_start_a(ap, v) ((void)(__va_start(&ap, _ADDRESSOF(v), _SLOTSIZEOF(v), _ADDRESSOF(v))))

    #else        define __crt_va_start_a(ap, v) ((void)(ap = (va_list)_ADDRESSOF(v) + _SLOTSIZEOF(v)))

    #endif

    define __crt_va_arg(ap, t) (*(t*)((ap += _SLOTSIZEOF(t) + _APALIGN(t,ap)) - _SLOTSIZEOF(t)))

    define __crt_va_end(ap)    ((void)(ap = (va_list)0))



#elif defined _M_ARM64

    void __cdecl __va_start(va_list*, ...);



    define __crt_va_start_a(ap,v) ((void)(__va_start(&ap, _ADDRESSOF(v), _SLOTSIZEOF(v), __alignof(v), _ADDRESSOF(v))))

    define __crt_va_arg(ap, t)                                                         ((sizeof(t) > (2 * sizeof(__int64)))                                               ? **(t**)((ap += sizeof(__int64)) - sizeof(__int64))                           : *(t*)((ap += _SLOTSIZEOF(t) + _APALIGN(t,ap)) - _SLOTSIZEOF(t)))

    define __crt_va_end(ap)       ((void)(ap = (va_list)0))





#elif defined _M_X64

    void __cdecl __va_start(va_list* , ...);



    define __crt_va_start_a(ap, x) ((void)(__va_start(&ap, x)))

    define __crt_va_arg(ap, t)                                                       ((sizeof(t) > sizeof(__int64) || (sizeof(t) & (sizeof(t) - 1)) != 0)             ? **(t**)((ap += sizeof(__int64)) - sizeof(__int64))                         :  *(t* )((ap += sizeof(__int64)) - sizeof(__int64)))

    define __crt_va_end(ap)        ((void)(ap = (va_list)0))



#endif

#ifdef __cplusplus} 

#endif

#if defined __cplusplus && !defined _CRT_NO_VA_START_VALIDATION    extern "C++"

    {

        template <typename _Ty>

        struct __vcrt_va_list_is_reference

        {

            enum : bool { __the_value = false };

        };



        template <typename _Ty>

        struct __vcrt_va_list_is_reference<_Ty&>

        {

            enum : bool { __the_value = true };

        };



        template <typename _Ty>

        struct __vcrt_va_list_is_reference<_Ty&&>

        {

            enum : bool { __the_value = true };

        };



        template <typename _Ty>

        void __vcrt_va_start_verify_argument_type() throw()

        {

            static_assert(!__vcrt_va_list_is_reference<_Ty>::__the_value, "va_start argument must not have reference type and must not be parenthesized");

        }

    } 



    define __crt_va_start(ap, x) ((void)(__vcrt_va_start_verify_argument_type<decltype(x)>(), __crt_va_start_a(ap, x)))



#else // ^^^ __cplusplus ^^^ // vvv !__cplusplus vvv //

    #define __crt_va_start(ap, x) __crt_va_start_a(ap, x)

#endif

#pragma pack(pop)







#if defined __cplusplus

    define _CRT_BEGIN_C_HEADER                    __pragma(pack(push, _CRT_PACKING))         extern "C" {



    define _CRT_END_C_HEADER         }                             __pragma(pack(pop))



#elif defined __midl

    define _CRT_BEGIN_C_HEADER                                 cpp_quote("__pragma(pack(push, _CRT_PACKING))")         cpp_quote("extern \"C\" {")



    define _CRT_END_C_HEADER                    cpp_quote("}")                           cpp_quote("__pragma(pack(pop))")



#else

    #define _CRT_BEGIN_C_HEADER                    __pragma(pack(push, _CRT_PACKING))

    #define _CRT_END_C_HEADER         __pragma(pack(pop))

#endif

_CRT_BEGIN_C_HEADER 







#ifndef _HAS_EXCEPTIONS    #define _HAS_EXCEPTIONS 1 // Predefine as 0 to disable exceptions#endif





#define _CRT_STRINGIZE_(x) #x#define _CRT_STRINGIZE(x) _CRT_STRINGIZE_(x)

#define _CRT_WIDE_(s) L ## s#define _CRT_WIDE(s) _CRT_WIDE_(s)

#define _CRT_CONCATENATE_(a, b) a ## b#define _CRT_CONCATENATE(a, b)  _CRT_CONCATENATE_(a, b)

#define _CRT_UNPARENTHESIZE_(...) __VA_ARGS__#define _CRT_UNPARENTHESIZE(...)  _CRT_UNPARENTHESIZE_ __VA_ARGS__





#ifndef _VCRTIMP    #if defined _CRTIMP && !defined _VCRT_DEFINED_CRTIMP        define _VCRTIMP _CRTIMP

    #elif defined _VCRT_BUILD && defined CRTDLL        define _VCRTIMP __declspec(dllexport)

    #elif defined _CORECRT_BUILD        define _VCRTIMP

    #elif defined _DLL        define _VCRTIMP __declspec(dllimport)

    #else        #define _VCRTIMP    #endif#endif

#ifndef _MRTIMP    #if defined MRTDLL && defined _CRTBLD        #if !defined _M_CEE_PURE            define _MRTIMP __declspec(dllexport)

        #else            define _MRTIMP

        #endif    #else        #define _MRTIMP __declspec(dllimport)    #endif#endif





#ifdef _M_CEE_PURE    define _VCRTIMP_PURE

#elif (defined _VCRT_BUILD || defined _CRTBLD) && defined MRTDLL    define _VCRTIMP_PURE

#else    #define _VCRTIMP_PURE _VCRTIMP#endif



#if defined _M_CEE_PURE || defined MRTDLL    define __CLRCALL_OR_CDECL __clrcall

    define __CLR_OR_THIS_CALL __clrcall

#else    #define __CLRCALL_OR_CDECL __cdecl    #define __CLR_OR_THIS_CALL#endif

#ifdef _M_CEE_PURE    define __CLRCALL_PURE_OR_CDECL __clrcall

#else    #define __CLRCALL_PURE_OR_CDECL __cdecl#endif

#define __CRTDECL __CLRCALL_PURE_OR_CDECL



#define _VCRT_NOALIAS __declspec(noalias)#define _VCRT_RESTRICT __declspec(restrict)

#if !defined _MSC_VER || _MSC_VER >= 1900    #define _VCRT_ALLOCATOR __declspec(allocator)#else    define _VCRT_ALLOCATOR

#endif

#if defined _M_CEE && defined _M_X64    define _VCRT_JIT_INTRINSIC __declspec(jitintrinsic)

#else    #define _VCRT_JIT_INTRINSIC#endif

#ifdef __midl    define _VCRT_ALIGN(x)

#else    #define _VCRT_ALIGN(x) __declspec(align(x))#endif

#ifndef _CONST_RETURN    #ifdef __cplusplus        define _CRT_CONST_CORRECT_OVERLOADS

        define _CONST_RETURN  const

    #else      #define _CONST_RETURN    #endif#endif



#define _WConst_return _CONST_RETURN



#ifdef _WIN64    typedef unsigned __int64 size_t;

    typedef __int64          ptrdiff_t;

    typedef __int64          intptr_t;

#else    typedef unsigned int     size_t;

    typedef int              ptrdiff_t;

    typedef int              intptr_t;

#endif

#if defined __cplusplus    typedef bool  __vcrt_bool;

#elif defined __midl    

    

    typedef char __vcrt_bool;

#else    typedef _Bool __vcrt_bool;

#endif



#ifndef _SIZE_T_DEFINED    #define _SIZE_T_DEFINED#endif

#ifndef _PTRDIFF_T_DEFINED    #define _PTRDIFF_T_DEFINED#endif

#ifndef _INTPTR_T_DEFINED    #define _INTPTR_T_DEFINED#endif



#ifndef _WCHAR_T_DEFINED    #define _WCHAR_T_DEFINED    typedef unsigned short wchar_t;

#endif

#ifndef NULL    #ifdef __cplusplus        define NULL 0

    #else        #define NULL ((void *)0)    #endif#endif

#if defined _M_X64 || defined _M_ARM || defined _M_ARM64    define _UNALIGNED __unaligned

#else    #define _UNALIGNED#endif

#ifdef __cplusplus    extern "C++"

    {

        template <typename _CountofType, size_t _SizeOfArray>

        char (*__countof_helper(_UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];



        define __crt_countof(_Array) (sizeof(*__countof_helper(_Array)) + 0)

    }

#else    #define __crt_countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))#endif



#define _CRT_DEPRECATE_TEXT(_Text) __declspec(deprecated(_Text))

#if defined _CRT_SECURE_NO_DEPRECATE && !defined _CRT_SECURE_NO_WARNINGS    define _CRT_SECURE_NO_WARNINGS

#endif

#ifndef _CRT_INSECURE_DEPRECATE    #ifdef _CRT_SECURE_NO_WARNINGS        define _CRT_INSECURE_DEPRECATE(_Replacement)

    #else        #define _CRT_INSECURE_DEPRECATE(_Replacement) _CRT_DEPRECATE_TEXT(                "This function or variable may be unsafe. Consider using "                    #_Replacement                                                                 " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. "             "See online help for details.")    #endif#endif

#if defined _CRT_SECURE_DEPRECATE_MEMORY && !defined _CRT_SECURE_WARNINGS_MEMORY    define _CRT_SECURE_WARNINGS_MEMORY

#endif

#ifndef _CRT_INSECURE_DEPRECATE_MEMORY    #ifndef _CRT_SECURE_WARNINGS_MEMORY        #define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement)    #else        define _CRT_INSECURE_DEPRECATE_MEMORY(_Replacement)             _CRT_INSECURE_DEPRECATE(_Replacement)

    #endif#endif





#define _CRT_WARNING(description)                       message("" __FILE__ "(" _CRT_STRINGIZE(__LINE__) ") : warning CRT0000 : " _CRT_STRINGIZE(description))





#if !defined _M_CEE && !defined __midl    void __cdecl  __security_init_cookie(void);



    #ifdef _M_IX86        void __fastcall  __security_check_cookie(_In_  uintptr_t _StackCookie);

        __declspec(noreturn)  void __cdecl  __report_gsfailure(void);

    #else  /* _M_IX86 */        void __cdecl __security_check_cookie(_In_ uintptr_t _StackCookie);

        __declspec(noreturn) void __cdecl __report_gsfailure(_In_ uintptr_t _StackCookie);

    #endif#endif

extern uintptr_t __security_cookie;



#ifndef _VCRT_BUILD    #define __vcrt_malloc_normal(_Size) malloc(_Size)    #define __vcrt_calloc_normal(_Count, _Size) calloc(_Count, _Size)    #define __vcrt_free_normal(_Memory) free(_Memory)#endif

_CRT_END_C_HEADER 



#endif // _VCRUNTIME_H

_CRT_BEGIN_C_HEADER 

















#ifndef _ACRTIMP    #if defined _CRTIMP && !defined _VCRT_DEFINED_CRTIMP        define _ACRTIMP _CRTIMP

    #elif !defined _CORECRT_BUILD && defined _DLL        define _ACRTIMP __declspec(dllimport)

    #else        #define _ACRTIMP    #endif#endif





#ifndef _ACRTIMP_ALT    #define _ACRTIMP_ALT _ACRTIMP#endif

#ifndef _DCRTIMP    #if defined _CRTIMP && !defined _VCRT_DEFINED_CRTIMP        define _DCRTIMP _CRTIMP

    #elif !defined _CORECRT_BUILD && defined _DLL        define _DCRTIMP __declspec(dllimport)

    #else        #define _DCRTIMP    #endif#endif

#if defined _CRT_SUPPRESS_RESTRICT || defined _CORECRT_BUILD    define _CRTRESTRICT

#else    #define _CRTRESTRICT __declspec(restrict)#endif

#if defined _MSC_VER && _MSC_VER >= 1900 && !defined _CORECRT_BUILD    define _CRTALLOCATOR __declspec(allocator)

#else    #define _CRTALLOCATOR#endif

#if defined _M_CEE && defined _M_X64    

    

    define _CRT_JIT_INTRINSIC __declspec(jitintrinsic)

#else    #define _CRT_JIT_INTRINSIC#endif



#ifdef _GUARDOVERFLOW_CRT_ALLOCATORS    define _CRT_GUARDOVERFLOW __declspec(guard(overflow))

#else    #define _CRT_GUARDOVERFLOW#endif

#ifndef _CONST_RETURN    #ifdef __cplusplus        define _CONST_RETURN const

        define _CRT_CONST_CORRECT_OVERLOADS

    #else        define _CONST_RETURN

    #endif#endif

#define _WConst_return _CONST_RETURN // For backwards compatibility

#ifndef _CRT_ALIGN    #ifdef __midl        define _CRT_ALIGN(x)

    #else        #define _CRT_ALIGN(x) __declspec(align(x))    #endif#endif

#if defined _PREFAST_ && defined _CA_SHOULD_CHECK_RETURN    define _Check_return_opt_ _Check_return_

#else    #define _Check_return_opt_#endif

#if defined _PREFAST_ && defined _CA_SHOULD_CHECK_RETURN_WER    define _Check_return_wat_ _Check_return_

#else    #define _Check_return_wat_#endif

#if !defined __midl && !defined MIDL_PASS && defined _PREFAST_    define __crt_typefix(ctype) __declspec("SAL_typefix(" _CRT_STRINGIZE(ctype) ")")

#else    #define __crt_typefix(ctype)#endif















#ifdef __cplusplusextern "C++"

{

    template<bool _Enable, typename _Ty>

    struct _CrtEnableIf;



    template<typename _Ty>

    struct _CrtEnableIf<true, _Ty>

    {

        typedef _Ty _Type;

    };

}

#endif

#if defined __cplusplus    typedef bool  __crt_bool;

#elif defined __midl    

    

    typedef char __crt_bool;

#else    typedef _Bool __crt_bool;

#endif

#define _ARGMAX   100#define _TRUNCATE ((size_t)-1)#define _CRT_INT_MAX 2147483647#define _CRT_SIZE_MAX ((size_t)-1)

#define __FILEW__     _CRT_WIDE(__FILE__)#define __FUNCTIONW__ _CRT_WIDE(__FUNCTION__)

#ifndef _STATIC_ASSERT    #define _STATIC_ASSERT(expr) typedef char __static_assert_t[(expr) != 0]#endif

#ifndef NULL    #ifdef __cplusplus        define NULL 0

    #else        define NULL ((void *)0)

    #endif#endif



















#if !defined _CRT_FUNCTIONS_REQUIRED    #if defined __assembler || defined __midl || defined RC_INVOKED        define _CRT_FUNCTIONS_REQUIRED 0

    #else        #define _CRT_FUNCTIONS_REQUIRED 1    #endif#endif

#if !defined _NO_INLINING && !_CRT_FUNCTIONS_REQUIRED        define _NO_INLINING 

#endif

#ifndef _CRT_UNUSED    #define _CRT_UNUSED(x) (void)x#endif















#ifndef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP    #ifdef WINAPI_FAMILY        include <winapifamily.h>

        #if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP | WINAPI_PARTITION_SYSTEM)            define _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

        #else            #ifdef WINAPI_FAMILY_PHONE_APP                #if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP                    define _CRT_USE_WINAPI_FAMILY_PHONE_APP

                #endif            #endif        #endif    #else        #define _CRT_USE_WINAPI_FAMILY_DESKTOP_APP    #endif#endif

#ifndef _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE    #define _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE 0#endif

#ifndef _CRT_BUILD_DESKTOP_APP    #ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP        #define _CRT_BUILD_DESKTOP_APP 1    #else        define _CRT_BUILD_DESKTOP_APP 0

    #endif#endif



#ifdef _M_ARM    #if _CRT_BUILD_DESKTOP_APP && !_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE        error Compiling Desktop applications for the ARM platform is not supported.

    #endif#endif















#ifdef _DEBUG    _ACRTIMP void __cdecl _invalid_parameter(

        _In_opt_z_ wchar_t const*,

        _In_opt_z_ wchar_t const*,

        _In_opt_z_ wchar_t const*,

        _In_       unsigned int,

        _In_       uintptr_t

        );

#endif

_ACRTIMP_ALT  void __cdecl  _invalid_parameter_noinfo(void);

_ACRTIMP  __declspec(noreturn)  void __cdecl  _invalid_parameter_noinfo_noreturn(void);



__declspec(noreturn) 

_ACRTIMP  void __cdecl  _invoke_watson(

    _In_opt_z_  wchar_t const*,

    _In_opt_z_  wchar_t const*,

    _In_opt_z_  wchar_t const*,

    _In_        unsigned int,

    _In_        uintptr_t);



#ifndef _CRT_SECURE_INVALID_PARAMETER    #ifdef _DEBUG        define _CRT_SECURE_INVALID_PARAMETER(expr)             ::_invalid_parameter(_CRT_WIDE(#expr), __FUNCTIONW__, __FILEW__, __LINE__, 0)

    #else        

        

        

        

        

        

        

        

        

        

        

        #define _CRT_SECURE_INVALID_PARAMETER(expr)             ::_invalid_parameter_noinfo_noreturn()    #endif#endif















#define _CRT_INTERNAL_NONSTDC_NAMES                                                (                                                                                  ( defined _CRT_DECLARE_NONSTDC_NAMES && _CRT_DECLARE_NONSTDC_NAMES) ||         (!defined _CRT_DECLARE_NONSTDC_NAMES && !__STDC__                 )        )

#if defined _CRT_NONSTDC_NO_DEPRECATE && !defined _CRT_NONSTDC_NO_WARNINGS    define _CRT_NONSTDC_NO_WARNINGS

#endif

#ifndef _CRT_NONSTDC_DEPRECATE    #ifdef _CRT_NONSTDC_NO_WARNINGS        define _CRT_NONSTDC_DEPRECATE(_NewName)

    #else        #define _CRT_NONSTDC_DEPRECATE(_NewName) _CRT_DEPRECATE_TEXT(                         "The POSIX name for this item is deprecated. Instead, use the ISO C "             "and C++ conformant name: " #_NewName ". See online help for details.")    #endif#endif















#ifndef _PGLOBAL    #ifdef _M_CEE        #ifdef __cplusplus_cli            define _PGLOBAL __declspec(process)

        #else            define _PGLOBAL

        #endif    #else        #define _PGLOBAL    #endif#endif

#ifndef _AGLOBAL    #ifdef _M_CEE        define _AGLOBAL __declspec(appdomain)

    #else        #define _AGLOBAL    #endif#endif

#if defined _M_CEE && !defined _M_CEE_PURE    define _M_CEE_MIXED

#endif















#if defined _CRTBLD || defined _CORECRT_BUILD || defined _VCRT_BUILD    

    define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES       0

    define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 0

    define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES         0

#endif

#if !_CRT_FUNCTIONS_REQUIRED    

    

    undef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES

    undef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT

    undef  _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES

    undef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY

    undef  _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY



    define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 0

    define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 0

    define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 0

    define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY 0

    define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY 0

#endif

#define __STDC_SECURE_LIB__ 200411L#define __GOT_SECURE_LIB__ __STDC_SECURE_LIB__ // For backwards compatibility

#ifndef __STDC_WANT_SECURE_LIB__    #define __STDC_WANT_SECURE_LIB__ 1#endif

#if !__STDC_WANT_SECURE_LIB__ && !defined _CRT_SECURE_NO_WARNINGS    define _CRT_SECURE_NO_WARNINGS

#endif

#ifndef RC_INVOKED    #if defined _CRT_SECURE_NO_DEPRECATE_GLOBALS && !defined _CRT_SECURE_NO_WARNINGS_GLOBALS        define _CRT_SECURE_NO_WARNINGS_GLOBALS

    #endif#endif

#ifndef _CRT_INSECURE_DEPRECATE_GLOBALS    #ifdef RC_INVOKED        define _CRT_INSECURE_DEPRECATE_GLOBALS(replacement)

    #else        #ifdef _CRT_SECURE_NO_WARNINGS_GLOBALS            define _CRT_INSECURE_DEPRECATE_GLOBALS(replacement)

        #else            #define _CRT_INSECURE_DEPRECATE_GLOBALS(replacement) _CRT_INSECURE_DEPRECATE(replacement)        #endif    #endif#endif

#if defined _CRT_MANAGED_HEAP_NO_DEPRECATE && !defined _CRT_MANAGED_HEAP_NO_WARNINGS    define _CRT_MANAGED_HEAP_NO_WARNINGS

#endif

#define _SECURECRT_FILL_BUFFER_PATTERN 0xFE

#if defined _CRT_OBSOLETE_NO_DEPRECATE && !defined _CRT_OBSOLETE_NO_WARNINGS    define _CRT_OBSOLETE_NO_WARNINGS

#endif

#ifndef _CRT_OBSOLETE    #ifdef _CRT_OBSOLETE_NO_WARNINGS        define _CRT_OBSOLETE(_NewItem)

    #else        #define _CRT_OBSOLETE(_NewItem) _CRT_DEPRECATE_TEXT(                               "This function or variable has been superceded by newer library "              "or operating system functionality. Consider using " #_NewItem " "             "instead. See online help for details.")    #endif#endif

#ifndef RC_INVOKED    #ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES        #define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 0    #else        #if !__STDC_WANT_SECURE_LIB__ && _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES            error Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0

        #endif    #endif

    #ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT        

        

        #define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 0    #else        #if !__STDC_WANT_SECURE_LIB__ && _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT            error Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0

        #endif    #endif

    #ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES        #if __STDC_WANT_SECURE_LIB__              #define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1        #else              define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 0

        #endif    #else        #if !__STDC_WANT_SECURE_LIB__ && _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES            error Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0

        #endif    #endif

    #ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY        #define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY 0    #else        #if !__STDC_WANT_SECURE_LIB__ && _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY            error Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0

        #endif    #endif

    #ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY        #define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY 0    #else        #if !__STDC_WANT_SECURE_LIB__ && _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY           error Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0

        #endif    #endif#endif

#ifndef _CRT_SECURE_CPP_NOTHROW    #define _CRT_SECURE_CPP_NOTHROW throw()#endif















typedef int                           errno_t;

typedef unsigned short                wint_t;

typedef unsigned short                wctype_t;

typedef long                          __time32_t;

typedef __int64long long                       __time64_t;



typedef struct __crt_locale_data_public

{

      unsigned short const* _locale_pctype;

    _Field_range_(1, 2)  int _locale_mb_cur_max;

               unsigned int _locale_lc_codepage;

} __crt_locale_data_public;



typedef struct __crt_locale_pointers

{

    struct __crt_locale_data*    locinfo;

    struct __crt_multibyte_data* mbcinfo;

} __crt_locale_pointers;



typedef __crt_locale_pointers* _locale_t;



typedef struct _Mbstatet

{ 

    unsigned long _Wchar;

    unsigned short _Byte, _State;

} _Mbstatet;



typedef _Mbstatet mbstate_t;



#if defined _USE_32BIT_TIME_T && defined _WIN64    error You cannot use 32-bit time_t (_USE_32BIT_TIME_T) with _WIN64

#endif

#if defined _VCRT_BUILD || defined _CORECRT_BUILD    define _CRT_NO_TIME_T

#endif

#ifndef _CRT_NO_TIME_T    #ifdef _USE_32BIT_TIME_T        typedef __time32_t time_t;

    #else        typedef __time64_t time_t;

    #endif#endif



#ifndef _TIME_T_DEFINED    #define _TIME_T_DEFINED#endif

#if __STDC_WANT_SECURE_LIB__    typedef size_t rsize_t;

#endif

















#ifndef RC_INVOKED    #if defined __cplusplus && _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES

        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(_ReturnType, _FuncName, _DstType, _Dst)                 extern "C++"                                                                                      {                                                                                                     template <size_t _Size>                                                                           inline                                                                                            _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size]) _CRT_SECURE_CPP_NOTHROW                  {                                                                                                     return _FuncName(_Dst, _Size);                                                                }                                                                                             }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1)               extern "C++"                                                                                                     {                                                                                                                    template <size_t _Size>                                                                                          inline                                                                                                           _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW                 {                                                                                                                    return _FuncName(_Dst, _Size, _TArg1);                                                                       }                                                                                                            }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)              extern "C++"                                                                                                                     {                                                                                                                                    template <size_t _Size>                                                                                                          inline                                                                                                                           _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW                 {                                                                                                                                    return _FuncName(_Dst, _Size, _TArg1, _TArg2);                                                                               }                                                                                                                            }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)             extern "C++"                                                                                                                                     {                                                                                                                                                    template <size_t _Size>                                                                                                                          inline                                                                                                                                           _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW                 {                                                                                                                                                    return _FuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3);                                                                                       }                                                                                                                                            }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)             extern "C++"                                                                                                                                                      {                                                                                                                                                                     template <size_t _Size>                                                                                                                                           inline                                                                                                                                                            _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) _CRT_SECURE_CPP_NOTHROW                  {                                                                                                                                                                     return _FuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3, _TArg4);                                                                                                }                                                                                                                                                             }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1)              extern "C++"                                                                                                                     {                                                                                                                                    template <size_t _Size>                                                                                                          inline                                                                                                                           _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW                 {                                                                                                                                    return _FuncName(_HArg1, _Dst, _Size, _TArg1);                                                                               }                                                                                                                            }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)             extern "C++"                                                                                                                                     {                                                                                                                                                    template <size_t _Size>                                                                                                                          inline                                                                                                                                           _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW                 {                                                                                                                                                    return _FuncName(_HArg1, _Dst, _Size, _TArg1, _TArg2);                                                                                       }                                                                                                                                            }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)             extern "C++"                                                                                                                                                      {                                                                                                                                                                     template <size_t _Size>                                                                                                                                           inline                                                                                                                                                            _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW                  {                                                                                                                                                                     return _FuncName(_HArg1, _Dst, _Size, _TArg1, _TArg2, _TArg3);                                                                                                }                                                                                                                                                             }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(_ReturnType, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst)              extern "C++"                                                                                                                     {                                                                                                                                    template <size_t _Size>                                                                                                          inline                                                                                                                           _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType (&_Dst)[_Size]) _CRT_SECURE_CPP_NOTHROW                 {                                                                                                                                    return _FuncName(_HArg1, _HArg2, _Dst, _Size);                                                                               }                                                                                                                            }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1)             extern "C++"                                                                                                                       {                                                                                                                                      __pragma(warning(push));                                                                                                           __pragma(warning(disable: 4793));                                                                                                  template <size_t _Size>                                                                                                            inline                                                                                                                             _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, ...) _CRT_SECURE_CPP_NOTHROW                              {                                                                                                                                      va_list _ArgList;                                                                                                                  __crt_va_start(_ArgList, _TArg1);                                                                                                  return _VFuncName(_Dst, _Size, _TArg1, _ArgList);                                                                              }                                                                                                                                  __pragma(warning(pop));                                                                                                        }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)             extern "C++"                                                                                                                                        {                                                                                                                                                       __pragma(warning(push));                                                                                                                            __pragma(warning(disable: 4793));                                                                                                                   template <size_t _Size>                                                                                                                             inline                                                                                                                                              _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, ...) _CRT_SECURE_CPP_NOTHROW                               {                                                                                                                                                       va_list _ArgList;                                                                                                                                   __crt_va_start(_ArgList, _TArg2);                                                                                                                   return _VFuncName(_Dst, _Size, _TArg1, _TArg2, _ArgList);                                                                                       }                                                                                                                                                   __pragma(warning(pop));                                                                                                                         }



        define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(_ReturnType, _FuncName, _DstType, _Src)                           extern "C++"                                                                                                      {                                                                                                                     template <size_t _DriveSize, size_t _DirSize, size_t _NameSize, size_t _ExtSize>                                  inline                                                                                                            _ReturnType __CRTDECL _FuncName(                                                                                      _In_z_ _DstType const* _Src,                                                                                      _Post_z_ _DstType (&_Drive)[_DriveSize],                                                                          _Post_z_ _DstType (&_Dir)[_DirSize],                                                                              _Post_z_ _DstType (&_Name)[_NameSize],                                                                            _Post_z_ _DstType (&_Ext)[_ExtSize]                                                                               ) _CRT_SECURE_CPP_NOTHROW                                                                                     {                                                                                                                     return _FuncName(_Src, _Drive, _DriveSize, _Dir, _DirSize, _Name, _NameSize, _Ext, _ExtSize);                 }                                                                                                             }



    #else  // ^^^ _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES ^^^ // vvv !_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES vvv //

        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(_ReturnType, _FuncName, _DstType, _Dst)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4(_ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3(_ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0(_ReturnType, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(_ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)        #define __DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH(_ReturnType, _FuncName, _DstType, _Src)

    #endif // !_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES#endif





#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _FuncName##_s, _VFuncName, _VFuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _VFuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE(_DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE(_DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)     __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)





#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, __cdecl, _FuncName, _FuncName##_s, _VFuncName, _VFuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE(_DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

#define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE(_DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)     __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)















#ifndef RC_INVOKED    #if defined __cplusplus && _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES

        define __RETURN_POLICY_SAME(_FunctionCall, _Dst) return (_FunctionCall)

        define __RETURN_POLICY_DST(_FunctionCall, _Dst)  return ((_FunctionCall) == 0 ? _Dst : 0)

        define __RETURN_POLICY_VOID(_FunctionCall, _Dst) (_FunctionCall); return

        define __EMPTY_DECLSPEC



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst)             {                 _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);                 return _FuncName(_Dst);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst));             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst));             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size]) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1]) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst)             {                 _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);                 return _FuncName(_Dst);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName(_T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst));             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName(const _T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst));             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size]) _CRT_SECURE_CPP_NOTHROW             {                 size_t _SizeRead = 0;                 errno_t _Err = _FuncName##_s(_Dst + 2, (_Size - 2) < ((size_t)_Dst[0]) ? (_Size - 2) : ((size_t)_Dst[0]), &_SizeRead);                 _Dst[1] = (_DstType)(_SizeRead);                 return (_Err == 0 ? _Dst + 2 : 0);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1]) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName((_DstType *)_Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName<2>(_DstType (&_Dst)[2]) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName((_DstType *)_Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1)             {                 _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1);                 return _FuncName(_Dst, _TArg1);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);                 return _FuncName(_Dst, _TArg1, _TArg2);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1, _TArg2);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3)             {                 _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);                 return _FuncName(_Dst, _TArg1, _TArg2, _TArg3);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1, _TArg2, _TArg3);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2, _TArg3), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4)             {                 _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4);                 return _FuncName(_Dst, _TArg1, _TArg2, _TArg3, _TArg4);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3, _TArg4);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3, _TArg4);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1, _TArg2, _TArg3, _TArg4);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3, _TArg4), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2, _TArg3, _TArg4), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_HType1 _HArg1, _SalAttributeDst _DstType *_Dst, _TType1 _TArg1)             {                 _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _DstType *_Dst, _TType1 _TArg1);                 return _FuncName(_HArg1, _Dst, _TArg1);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _T &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_HArg1, static_cast<_DstType *>(_Dst), _TArg1);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, const _T &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_HArg1, static_cast<_DstType *>(_Dst), _TArg1);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _DstType * &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_HArg1, _Dst, _TArg1);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _DstType (&_Dst)[_Size], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_HArg1, _Dst, _Size, _TArg1), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_HType1 _HArg1, _DstType (&_Dst)[1], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_HArg1, _Dst, 1, _TArg1), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_HType1 _HArg1, _HType2 _HArg2, _SalAttributeDst _DstType *_Dst)             {                 _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType *_Dst);                 return _FuncName(_HArg1, _HArg2, _Dst);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _HType2 _HArg2, _T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_HArg1, _HArg2, static_cast<_DstType *>(_Dst));             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _HType2 _HArg2, const _T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_HArg1, _HArg2, static_cast<_DstType *>(_Dst));             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType * &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_HArg1, _HArg2, _Dst);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_HType1 _HArg1, _HType2 _HArg2, _DstType (&_Dst)[_Size]) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_HArg1, _HArg2, _Dst, _Size), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_HType1 _HArg1, _HType2 _HArg2, _DstType (&_Dst)[1]) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_HArg1, _HArg2, _Dst, 1), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)             __inline             _ReturnType __CRTDECL __insecure_##_VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, va_list _ArgList)             {                 _DeclSpec _ReturnType _CC _VFuncName(_DstType *_Dst, _TType1 _TArg1, va_list _ArgList);                 return _VFuncName(_Dst, _TArg1, _ArgList);             }             extern "C++"             {                 __pragma(warning(push));                 __pragma(warning(disable: 4793));             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg1);                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _ArgList);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg1);                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _ArgList);             }                 __pragma(warning(pop));                                 __pragma(warning(push));                 __pragma(warning(disable: 4793));                 template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg1);                 return __insecure_##_VFuncName(_Dst, _TArg1, _ArgList);             }                 __pragma(warning(pop));                                 __pragma(warning(push));                 __pragma(warning(disable: 4793));                 template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg1);                 _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _ArgList), _Dst);             }                 __pragma(warning(pop));                                 __pragma(warning(push));                 __pragma(warning(disable: 4793));             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg1);                 _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _ArgList), _Dst);             }                 __pragma(warning(pop));                             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName(_T &_Dst, _TType1 _TArg1, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _ArgList);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName(const _T &_Dst, _TType1 _TArg1, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _ArgList);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName(_DstType *&_Dst, _TType1 _TArg1, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_VFuncName(_Dst, _TArg1, _ArgList);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _VFuncName(_DstType (&_Dst)[_Size], _TType1 _TArg1, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _ArgList), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _ArgList), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _SecureVFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)             __inline             _ReturnType __CRTDECL __insecure_##_VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList)             {                 _DeclSpec _ReturnType _CC _VFuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList);                 return _VFuncName(_Dst, _TArg1, _TArg2, _ArgList);             }             extern "C++"             {                 __pragma(warning(push));                 __pragma(warning(disable: 4793));             template <typename _T>             inline                 _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg2);                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _ArgList);             }             template <typename _T>             inline                 _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg2);                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _ArgList);             }                 __pragma(warning(pop));                                 __pragma(warning(push));                 __pragma(warning(disable: 4793));             template <>             inline                 _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg2);                 return __insecure_##_VFuncName(_Dst, _TArg1, _TArg2, _ArgList);             }                 __pragma(warning(pop));                                 __pragma(warning(push));                 __pragma(warning(disable: 4793));             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg2);                 _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _TArg2, _ArgList), _Dst);             }                 __pragma(warning(pop));                                 __pragma(warning(push));                 __pragma(warning(disable: 4793));             template <>             inline                 _CRT_INSECURE_DEPRECATE(_FuncName##_s)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, ...) _CRT_SECURE_CPP_NOTHROW             {                 va_list _ArgList;                 __crt_va_start(_ArgList, _TArg2);                 _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _TArg2, _ArgList), _Dst);             }                 __pragma(warning(pop));                             template <typename _T>             inline                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _ArgList);             }             template <typename _T>             inline                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_VFuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _ArgList);             }             template <>             inline                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName(_DstType *&_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_VFuncName(_Dst, _TArg1, _TArg2, _ArgList);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _VFuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureVFuncName(_Dst, _Size, _TArg1, _TArg2, _ArgList), _Dst);             }             template <>             inline                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName)             _ReturnType __CRTDECL _VFuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, va_list _ArgList) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureVFuncName(_Dst, 1, _TArg1, _TArg2, _ArgList), _Dst);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)             __inline             size_t __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2)             {                 _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);                 return _FuncName(_Dst, _TArg1, _TArg2);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1, _TArg2);             }             template <size_t _Size>             inline             size_t __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 size_t _Ret = 0;                 _SecureFuncName(&_Ret, _Dst, _Size, _TArg1, _TArg2);                 return (_Ret > 0 ? (_Ret - 1) : _Ret);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 size_t _Ret = 0;                 _SecureFuncName(&_Ret, _Dst, 1, _TArg1, _TArg2);                 return (_Ret > 0 ? (_Ret - 1) : _Ret);             }             }



        define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)             __inline             size_t __CRTDECL __insecure_##_FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3)             {                 _DeclSpec size_t __cdecl _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);                 return _FuncName(_Dst, _TArg1, _TArg2, _TArg3);             }             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1, _TArg2, _TArg3);             }             template <size_t _Size>             inline             size_t __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 size_t _Ret = 0;                 _SecureFuncName(&_Ret, _Dst, _Size, _TArg1, _TArg2, _TArg3);                 return (_Ret > 0 ? (_Ret - 1) : _Ret);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             size_t __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 size_t _Ret = 0;                 _SecureFuncName(&_Ret, _Dst, 1, _TArg1, _TArg2, _TArg3);                 return (_Ret > 0 ? (_Ret - 1) : _Ret);             }             }



        define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_DstType *_Dst)



        define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst));             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst));             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size]) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1]) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1), _Dst);             }             }



        define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1)



        define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1), _Dst);             }             }



        define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2)



        define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1, _TArg2);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2), _Dst);             }             }



        define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)             __inline             _ReturnType __CRTDECL __insecure_##_FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3)



        define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)             extern "C++"             {             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3);             }             template <typename _T>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(const _T &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(static_cast<_DstType *>(_Dst), _TArg1, _TArg2, _TArg3);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName(_DstType * &_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 return __insecure_##_FuncName(_Dst, _TArg1, _TArg2, _TArg3);             }             template <size_t _Size>             inline             _ReturnType __CRTDECL _FuncName(_SecureDstType (&_Dst)[_Size], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, _Size, _TArg1, _TArg2, _TArg3), _Dst);             }             template <>             inline             _CRT_INSECURE_DEPRECATE(_SecureFuncName)             _ReturnType __CRTDECL _FuncName<1>(_DstType (&_Dst)[1], _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3) _CRT_SECURE_CPP_NOTHROW             {                 _ReturnPolicy(_SecureFuncName(_Dst, 1, _TArg1, _TArg2, _TArg3), _Dst);             }             }



        #if _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, __cdecl, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _VFuncName##_s, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)





            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)                 __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType _DstType, _Dst)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)                 __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)



            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)                 __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType _DstType, _Dst, _TType1, _TArg1)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)                 __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)



            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)



            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)



        #else // ^^^ _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT ^^^ // vvv _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT vvv //

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst)                     _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst)                     _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _SalAttributeDst _DstType *_Dst, _TType1 _TArg1);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _SalAttributeDst _DstType *_Dst);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _SecureFuncName,_VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType _CC _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, ...);                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName) _DeclSpec _ReturnType _CC _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, va_list _Args);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...);                 _CRT_INSECURE_DEPRECATE(_VFuncName##_s) _DeclSpec _ReturnType __cdecl _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType _CC _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...);                 _CRT_INSECURE_DEPRECATE(_VFuncName##_s) _DeclSpec _ReturnType _CC _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec size_t __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);



            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec size_t __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);





            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)



            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)



            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)



            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3)



            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)



        #endif // !_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT

    #else  // ^^^ _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES ^^^ // vvv !_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES vvv //

        #define __RETURN_POLICY_SAME(_FunctionCall)        #define __RETURN_POLICY_DST(_FunctionCall)        #define __RETURN_POLICY_VOID(_FunctionCall)        #define __EMPTY_DECLSPEC

        #if _CRT_FUNCTIONS_REQUIRED

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _SalAttributeDst _DstType *_Dst, _TType1 _TArg1);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _SalAttributeDst _DstType *_Dst);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType _CC _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, ...);                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName) _DeclSpec _ReturnType _CC _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, va_list _Args);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _SecureVFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType _CC _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...);                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName) _DeclSpec _ReturnType _CC _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec size_t __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec size_t __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3, _TType4 _TArg4);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _SalAttributeDst _DstType *_Dst, _TType1 _TArg1);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_HType1 _HArg1, _HType2 _HArg2, _SalAttributeDst _DstType *_Dst);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType _CC _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, ...);                 _CRT_INSECURE_DEPRECATE(_SecureVFuncName) _DeclSpec _ReturnType _CC _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, va_list _Args);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...);                 _CRT_INSECURE_DEPRECATE(_VFuncName##_s) _DeclSpec _ReturnType __cdecl _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _CC, _FuncName, _VFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType _CC _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, ...);                 _CRT_INSECURE_DEPRECATE(_VFuncName##_s) _DeclSpec _ReturnType _CC _VFuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, va_list _Args);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec size_t __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2);

            #define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec size_t __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3);



            #define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst)

            #define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)

            #define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1)

            #define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)

            #define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2)

            #define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

            #define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3)

            #define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

            #define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst)

            #define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)

            #define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1)

            #define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)

            #define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2)

            #define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)

            #define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)                 _CRT_INSECURE_DEPRECATE(_SecureFuncName)                 __inline                 _ReturnType __CRTDECL _FuncName(_DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2, _TType3 _TArg3)

            #define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)

        #else // ^^^ _CRT_FUNCTIONS_REQUIRED ^^^ // vvv !_CRT_FUNCTIONS_REQUIRED vvv //

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(...)

            define __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX(...)

            define __DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(...)

            define __DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX(...)



        #endif // !_CRT_FUNCTIONS_REQUIRED    #endif // !_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES#endif





_CRT_END_C_HEADER 

#include <corecrt_wstdio.h>

















#pragma once

#include <corecrt.h>pragma once file#include <corecrt_stdio_config.h>













#pragma once

#include <corecrt.h>pragma once file

_CRT_BEGIN_C_HEADER 



#if !defined _NO_CRT_STDIO_INLINE && !_CRT_FUNCTIONS_REQUIRED    define _NO_CRT_STDIO_INLINE

#endif

#if defined _NO_CRT_STDIO_INLINE    undef _CRT_STDIO_INLINE

    define _CRT_STDIO_INLINE

#elif !defined _CRT_STDIO_INLINE    #define _CRT_STDIO_INLINE __inline#endif

#if !defined RC_INVOKED // RC has no target architecture    #if defined _M_IX86        #define _CRT_INTERNAL_STDIO_SYMBOL_PREFIX "_"    #elif defined _M_X64 || defined _M_ARM || defined _M_ARM64        define _CRT_INTERNAL_STDIO_SYMBOL_PREFIX ""

    #else        error Unsupported architecture

    #endif#endif

























#if !defined RC_INVOKED // _CRT_STDIO_LEGACY_WIDE_SPECIFIERS et al. are too long for rc    #if defined _CRT_STDIO_ISO_WIDE_SPECIFIERS        #if defined _CRT_STDIO_LEGACY_WIDE_SPECIFIERS            error _CRT_STDIO_ISO_WIDE_SPECIFIERS and _CRT_STDIO_LEGACY_WIDE_SPECIFIERS cannot be defined together.

        #endif

        #if !defined _M_CEE_PURE            pragma comment(lib, "iso_stdio_wide_specifiers")

            pragma comment(linker, "/include:" _CRT_INTERNAL_STDIO_SYMBOL_PREFIX "__PLEASE_LINK_WITH_iso_stdio_wide_specifiers.lib")

        #endif    #elif defined _CRT_STDIO_LEGACY_WIDE_SPECIFIERS        #if !defined _M_CEE_PURE            pragma comment(lib, "legacy_stdio_wide_specifiers")

            pragma comment(linker, "/include:" _CRT_INTERNAL_STDIO_SYMBOL_PREFIX "__PLEASE_LINK_WITH_legacy_stdio_wide_specifiers.lib")

        #endif    #endif

    #if defined __cplusplus && !defined _CRT_STDIO_ARBITRARY_WIDE_SPECIFIERS        #ifdef _CRT_STDIO_ISO_WIDE_SPECIFIERS            pragma detect_mismatch("_CRT_STDIO_ISO_WIDE_SPECIFIERS", "1")

        #else            pragma detect_mismatch("_CRT_STDIO_ISO_WIDE_SPECIFIERS", "0")

        #endif    #endif#endif







#if defined _M_CEE && !defined _M_CEE_PURE    pragma managed(push, off)

#endif

#if _CRT_FUNCTIONS_REQUIRED    

    

    _Check_return_  _Ret_notnull_ 

    __declspec(noinline)  __inline  unsigned __int64long long* __CRTDECL  __local_stdio_printf_options(void)

    {

        static unsigned __int64long long _OptionsStorage;

        return &_OptionsStorage;

    }



    

    

    _Check_return_  _Ret_notnull_ 

    __declspec(noinline)  __inline  unsigned __int64long long* __CRTDECL  __local_stdio_scanf_options(void)

    {

        static unsigned __int64long long _OptionsStorage;

        return &_OptionsStorage;

    }

#endif

#if defined _M_CEE && !defined _M_CEE_PURE    pragma managed(pop)

#endif

#define _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS (*__local_stdio_printf_options())#define _CRT_INTERNAL_LOCAL_SCANF_OPTIONS  (*__local_stdio_scanf_options ())





#define _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION (1ULL << 0)#define _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR       (1ULL << 1)#define _CRT_INTERNAL_PRINTF_LEGACY_WIDE_SPECIFIERS           (1ULL << 2)#define _CRT_INTERNAL_PRINTF_LEGACY_MSVCRT_COMPATIBILITY      (1ULL << 3)#define _CRT_INTERNAL_PRINTF_LEGACY_THREE_DIGIT_EXPONENTS     (1ULL << 4)



#define _CRT_INTERNAL_SCANF_SECURECRT                   (1ULL << 0)#define _CRT_INTERNAL_SCANF_LEGACY_WIDE_SPECIFIERS      (1ULL << 1)#define _CRT_INTERNAL_SCANF_LEGACY_MSVCRT_COMPATIBILITY (1ULL << 2)





_CRT_END_C_HEADER 



_CRT_BEGIN_C_HEADER 















#ifndef _FILE_DEFINED    #define _FILE_DEFINED    typedef struct _iobuf

    {

        void* _Placeholder;

    } FILE;

#endif

_ACRTIMP_ALT  FILE* __cdecl  __acrt_iob_func(unsigned);



#define stdin  (__acrt_iob_func(0))#define stdout (__acrt_iob_func(1))#define stderr (__acrt_iob_func(2))

#define WEOF ((wint_t)(0xFFFF))





#if _CRT_FUNCTIONS_REQUIRED    

    

    

    

    

    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  fgetwc(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  _fgetwchar(void);



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  fputwc(

        _In_     wchar_t _Character,

        _Inout_  FILE*   _Stream);



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  _fputwchar(

        _In_  wchar_t _Character

        );



    _Check_return_ 

    _ACRTIMP  wint_t __cdecl  getwc(

        _Inout_  FILE* _Stream

        );



    _Check_return_ 

    _ACRTIMP  wint_t __cdecl  getwchar(void);





    _Check_return_opt_ 

    _Success_(return == _Buffer) 

    _ACRTIMP  wchar_t* __cdecl  fgetws(

        _Out_writes_z_(_BufferCount)  wchar_t* _Buffer,

        _In_                          int      _BufferCount,

        _Inout_                       FILE*    _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fputws(

        _In_z_   wchar_t const* _Buffer,

        _Inout_  FILE*          _Stream

        );



    _Check_return_opt_ 

    _Success_(return != 0) 

    _ACRTIMP  wchar_t* __cdecl  _getws_s(

        _Out_writes_z_(_BufferCount)  wchar_t* _Buffer,

        _In_                          size_t   _BufferCount

        );



    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(
        _Success_(return != 0)
        wchar_t*, _getws_s,
        _Always_(_Post_z_) wchar_t, _Buffer
        ) 



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  putwc(

        _In_     wchar_t _Character,

        _Inout_  FILE*   _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  putwchar(

        _In_  wchar_t _Character

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _putws(

        _In_z_  wchar_t const* _Buffer

        );



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  ungetwc(

        _In_     wint_t _Character,

        _Inout_  FILE*  _Stream

        );



    _Check_return_ 

    _ACRTIMP  FILE * __cdecl  _wfdopen(

        _In_    int            _FileHandle,

        _In_z_  wchar_t const* _Mode

        );



    _Check_return_  _CRT_INSECURE_DEPRECATE(_wfopen_s) 

    _ACRTIMP  FILE* __cdecl  _wfopen(

        _In_z_  wchar_t const* _FileName,

        _In_z_  wchar_t const* _Mode

        );



    _Check_return_wat_ 

    _ACRTIMP  errno_t __cdecl  _wfopen_s(

        _Outptr_result_maybenull_  FILE**         _Stream,

        _In_z_                     wchar_t const* _FileName,

        _In_z_                     wchar_t const* _Mode

        );



    _Check_return_ 

    _CRT_INSECURE_DEPRECATE(_wfreopen_s) 

    _ACRTIMP  FILE* __cdecl  _wfreopen(

        _In_z_   wchar_t const* _FileName,

        _In_z_   wchar_t const* _Mode,

        _Inout_  FILE*          _OldStream

        );



    _Check_return_wat_ 

    _ACRTIMP  errno_t __cdecl  _wfreopen_s(

        _Outptr_result_maybenull_  FILE**         _Stream,

        _In_z_                     wchar_t const* _FileName,

        _In_z_                     wchar_t const* _Mode,

        _Inout_                    FILE*          _OldStream

        );



    _Check_return_ 

    _ACRTIMP  FILE* __cdecl  _wfsopen(

        _In_z_  wchar_t const* _FileName,

        _In_z_  wchar_t const* _Mode,

        _In_    int            _ShFlag

        );



    _ACRTIMP  void __cdecl  _wperror(

        _In_opt_z_  wchar_t const* _ErrorMessage

        );



    #ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

        _Check_return_ 

        _DCRTIMP  FILE* __cdecl  _wpopen(

            _In_z_  wchar_t const* _Command,

            _In_z_  wchar_t const* _Mode

            );



    #endif

    _ACRTIMP  int __cdecl  _wremove(

        _In_z_  wchar_t const* _FileName

        );



    #pragma push_macro("_wtempnam")    #undef _wtempnam

    _Check_return_ 

    _ACRTIMP  _CRTALLOCATOR  wchar_t* __cdecl  _wtempnam(

        _In_opt_z_  wchar_t const* _Directory,

        _In_opt_z_  wchar_t const* _FilePrefix

        );



    #pragma pop_macro("_wtempnam")

    _Success_(return == 0) 

    _Check_return_wat_ 

    _ACRTIMP  errno_t __cdecl  _wtmpnam_s(

        _Out_writes_z_(_BufferCount)  wchar_t* _Buffer,

        _In_                          size_t   _BufferCount

        );



    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(
        _Success_(return == 0)
        errno_t, _wtmpnam_s,
        _Always_(_Post_z_) wchar_t, _Buffer
        ) 



    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(
        _Success_(return != 0)
        wchar_t*, __RETURN_POLICY_DST, _ACRTIMP, _wtmpnam,
        _Pre_maybenull_ _Always_(_Post_z_), wchar_t, _Buffer
        )    

  

 wchar_t*    _wtmpnam( 

      wchar_t *  _Buffer

 );







    

    

    

    

    

    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  _fgetwc_nolock(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  _fputwc_nolock(

        _In_     wchar_t _Character,

        _Inout_  FILE*   _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  _getwc_nolock(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  _putwc_nolock(

        _In_     wchar_t _Character,

        _Inout_  FILE*   _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  wint_t __cdecl  _ungetwc_nolock(

        _In_     wint_t _Character,

        _Inout_  FILE*  _Stream

        );



    #if defined _CRT_DISABLE_PERFCRIT_LOCKS && !defined _DLL        define fgetwc(stream)     _getwc_nolock(stream)

        define fputwc(c, stream)  _putwc_nolock(c, stream)

        define ungetwc(c, stream) _ungetwc_nolock(c, stream)

    #endif





    

    #ifdef _M_CEE_MIXED        pragma managed(push, off)

    #endif





    

    

    

    

    

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vfwprintf(

        _In_                                     unsigned __int64long long _Options,

        _Inout_                                  FILE*            _Stream,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vfwprintf_s(

        _In_                                     unsigned __int64long long _Options,

        _Inout_                                  FILE*            _Stream,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vfwprintf_p(

        _In_                                     unsigned __int64long long _Options,

        _Inout_                                  FILE*            _Stream,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfwprintf_l(

        _Inout_                                  FILE*          const _Stream,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfwprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vfwprintf(

        _Inout_                        FILE*          const _Stream,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwprintf_l(_Stream, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfwprintf_s_l(

        _Inout_                                  FILE*          const _Stream,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfwprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vfwprintf_s(

            _Inout_                        FILE*          const _Stream,

            _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                          va_list              _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfwprintf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfwprintf_p_l(

        _Inout_                                  FILE*          const _Stream,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfwprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfwprintf_p(

        _Inout_                        FILE*          const _Stream,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwprintf_p_l(_Stream, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vwprintf_l(

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwprintf_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vwprintf(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwprintf_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vwprintf_s_l(

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwprintf_s_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vwprintf_s(

            _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                          va_list              _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfwprintf_s_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vwprintf_p_l(

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwprintf_p_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vwprintf_p(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwprintf_p_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fwprintf_l(

        _Inout_                                  FILE*          const _Stream,

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  fwprintf(

        _Inout_                        FILE*          const _Stream,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_l(_Stream, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fwprintf_s_l(

        _Inout_                                  FILE*          const _Stream,

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_s_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  fwprintf_s(

            _Inout_                        FILE*          const _Stream,

            _In_z_  _Printf_format_string_  wchar_t const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfwprintf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fwprintf_p_l(

        _Inout_                                  FILE*          const _Stream,

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_p_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fwprintf_p(

        _Inout_                        FILE*          const _Stream,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_p_l(_Stream, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _wprintf_l(

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  wprintf(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _wprintf_s_l(

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_s_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  wprintf_s(

            _In_z_  _Printf_format_string_  wchar_t const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfwprintf_s_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _wprintf_p_l(

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_p_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _wprintf_p(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwprintf_p_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif



    

    

    

    

    

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vfwscanf(

        _In_                                    unsigned __int64long long _Options,

        _Inout_                                 FILE*            _Stream,

        _In_z_  _Scanf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                _locale_t        _Locale,

                                               va_list          _ArgList

        );



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfwscanf_l(

        _Inout_  FILE*                                const _Stream,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        _In_opt_                       _locale_t      const _Locale,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfwscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()),

            _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vfwscanf(

        _Inout_  FILE*                                const _Stream,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwscanf_l(_Stream, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfwscanf_s_l(

        _Inout_                        FILE*          const _Stream,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        _In_opt_                       _locale_t      const _Locale,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfwscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()) | _CRT_INTERNAL_SCANF_SECURECRT(1ULL << 0),

            _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vfwscanf_s(

            _Inout_                        FILE*          const _Stream,

            _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                          va_list              _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfwscanf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _CRT_STDIO_INLINE  int __CRTDECL  _vwscanf_l(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        _In_opt_                       _locale_t      const _Locale,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwscanf_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vwscanf(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwscanf_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vwscanf_s_l(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        _In_opt_                       _locale_t      const _Locale,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfwscanf_s_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vwscanf_s(

            _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                          va_list              _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfwscanf_s_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_fwscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _fwscanf_l(

        _Inout_                                 FILE*          const _Stream,

        _In_z_  _Scanf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwscanf_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_  _CRT_INSECURE_DEPRECATE(fwscanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  fwscanf(

        _Inout_                       FILE*          const _Stream,

        _In_z_  _Scanf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwscanf_l(_Stream, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fwscanf_s_l(

        _Inout_                                   FILE*          const _Stream,

        _In_z_  _Scanf_s_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                  _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwscanf_s_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  fwscanf_s(

            _Inout_                         FILE*          const _Stream,

            _In_z_  _Scanf_s_format_string_  wchar_t const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfwscanf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_wscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _wscanf_l(

        _In_z_  _Scanf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwscanf_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_  _CRT_INSECURE_DEPRECATE(wscanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  wscanf(

        _In_z_  _Scanf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwscanf_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _wscanf_s_l(

        _In_z_  _Scanf_s_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                  _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfwscanf_s_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  wscanf_s(

            _In_z_  _Scanf_s_format_string_  wchar_t const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF            ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfwscanf_s_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif





    

    

    

    

    

    #ifndef _CRT_NON_CONFORMING_SWPRINTFS        #define _SWPRINTFS_DEPRECATED _CRT_DEPRECATE_TEXT(                                       "function has been changed to conform with the ISO C standard, "                 "adding an extra character count parameter. To use the traditional "                 "Microsoft version, set _CRT_NON_CONFORMING_SWPRINTFS.")    #else        define _SWPRINTFS_DEPRECATED

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vswprintf(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_opt_z_(_BufferCount)         wchar_t*         _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vswprintf_s(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_z_(_BufferCount)             wchar_t*         _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vsnwprintf_s(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_opt_z_(_BufferCount)         wchar_t*         _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_                                     size_t           _MaxCount,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  __stdio_common_vswprintf_p(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_z_(_BufferCount)             wchar_t*         _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_vsnwprintf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnwprintf_l(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  wchar_t*       const _Buffer,

        _In_                                          size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)       wchar_t const* const _Format,

        _In_opt_                                      _locale_t      const _Locale,

                                                     va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vswprintf(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()) | _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION(1ULL << 0),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    #pragma warning(push)    #pragma warning(disable: 4793)

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnwprintf_s_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_                                               size_t         const _MaxCount,

        _In_z_  _Printf_format_string_params_(2)            wchar_t const* const _Format,

        _In_opt_                                           _locale_t      const _Locale,

                                                          va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsnwprintf_s(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnwprintf_s(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_                                               size_t         const _MaxCount,

        _In_z_  _Printf_format_string_                      wchar_t const* const _Format,

                                                          va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vsnwprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(
        _Success_(return >= 0)
        int, __RETURN_POLICY_SAME, _CRT_STDIO_INLINE, __CRTDECL, _snwprintf, _vsnwprintf,
        _Pre_notnull_ _Post_maybez_                   wchar_t,
        _Out_writes_opt_(_BufferCount) _Post_maybez_, wchar_t,        _Buffer,
        _In_                                          size_t,         _BufferCount,
        _In_z_ _Printf_format_string_                 wchar_t const*, _Format
        )   

  

 int    _snwprintf(

      wchar_t * _Buffer, 

   size_t  _BufferCount, 

     wchar_t const*  _Format

 , ...);     

  

 int    _vsnwprintf(

      wchar_t * _Buffer, 

   size_t  _BufferCount, 

     wchar_t const*  _Format

 , va_list _Args);



    #pragma warning(pop)

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_vsnwprintf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnwprintf(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  wchar_t*       _Buffer,

        _In_                                          size_t         _BufferCount,

        _In_z_  _Printf_format_string_                 wchar_t const* _Format,

                                                     va_list        _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        return _vsnwprintf_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        #pragma warning(pop)    }

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(
        _Success_(return >= 0)
        int, _vsnwprintf_s,
        _Always_(_Post_z_)            wchar_t,        _Buffer,
        _In_                          size_t,         _BufferCount,
        _In_z_ _Printf_format_string_ wchar_t const*, _Format,
                                      va_list,        _ArgList
        ) 



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswprintf_c_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)            wchar_t const* const _Format,

        _In_opt_                                           _locale_t      const _Locale,

                                                          va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vswprintf(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswprintf_c(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_                      wchar_t const* const _Format,

                                                          va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vswprintf_c_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswprintf_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)            wchar_t const* const _Format,

        _In_opt_                                           _locale_t      const _Locale,

                                                          va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        return _vswprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        #pragma warning(pop)    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  __vswprintf_l(

        _Pre_notnull_  _Always_(_Post_z_)         wchar_t*       const _Buffer,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vswprintf_l(_Buffer, (size_t)-1, _Format, _Locale, _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswprintf(

        _Pre_notnull_  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_z_  _Printf_format_string_     wchar_t const* const _Format,

                                         va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vswprintf_l(_Buffer, (size_t)-1, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vswprintf(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(1)            wchar_t const* const _Format,

                                                          va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vswprintf_c_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswprintf_s_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                           size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)        wchar_t const* const _Format,

        _In_opt_                                       _locale_t      const _Locale,

                                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vswprintf_s(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Success_(return >= 0) 

        _CRT_STDIO_INLINE  int __CRTDECL  vswprintf_s(

            _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

            _In_                                           size_t         const _BufferCount,

            _In_z_  _Printf_format_string_                  wchar_t const* const _Format,

                                                          va_list              _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vswprintf_s_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(
        _Success_(return >= 0)
        int, vswprintf_s,
        _Always_(_Post_z_)            wchar_t,        _Buffer,
        _In_z_ _Printf_format_string_ wchar_t const*, _Format,
                                      va_list,        _ArgList
        ) 



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswprintf_p_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                           size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)        wchar_t const* const _Format,

        _In_opt_                                       _locale_t      const _Locale,

                                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vswprintf_p(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswprintf_p(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                           size_t         const _BufferCount,

        _In_z_  _Printf_format_string_                  wchar_t const* const _Format,

                                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vswprintf_p_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscwprintf_l(

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vswprintf(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()) | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR(1ULL << 1),

            NULL((void *)0), 0, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscwprintf(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vscwprintf_l(_Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscwprintf_p_l(

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

                                                va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vswprintf_p(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()) | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR(1ULL << 1),

            NULL((void *)0), 0, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscwprintf_p(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vscwprintf_p_l(_Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  __swprintf_l(

        _Pre_notnull_  _Always_(_Post_z_)         wchar_t*       const _Buffer,

        _In_z_  _Printf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = __vswprintf_l(_Buffer, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swprintf_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)            wchar_t const* const _Format,

        _In_opt_                                           _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swprintf(

        _Pre_notnull_  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_z_  _Printf_format_string_     wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = __vswprintf_l(_Buffer, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  swprintf(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_                      wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #pragma warning(push)    

    

    #pragma warning(disable:4793 4996)

    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(
        _Success_(return >= 0)
        int, __RETURN_POLICY_SAME, _CRT_STDIO_INLINE, __CRTDECL, __swprintf_l, __vswprintf_l, _vswprintf_s_l,
        _Pre_notnull_ _Always_(_Post_z_)        wchar_t,
        _Pre_notnull_ _Always_(_Post_z_),       wchar_t,        _Buffer,
        _In_z_ _Printf_format_string_params_(2) wchar_t const*, _Format,
        _In_opt_                                _locale_t,      _Locale
        )   

  

 int    __swprintf_l(

     wchar_t * _Buffer, 

     wchar_t const*  _Format, 

   _locale_t  _Locale

 , ...);     

  

 int    __vswprintf_l(

     wchar_t * _Buffer, 

     wchar_t const*  _Format, 

   _locale_t  _Locale

 , va_list _Args);



    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(
        _Success_(return >= 0)
        int, __RETURN_POLICY_SAME, _CRT_STDIO_INLINE, __CRTDECL, _swprintf, _swprintf_s, _vswprintf, vswprintf_s,
        _Pre_notnull_ _Always_(_Post_z_), wchar_t,        _Buffer,
        _In_z_ _Printf_format_string_     wchar_t const*, _Format
        )   

  

 int    _swprintf(

     wchar_t * _Buffer, 

     wchar_t const*  _Format

 , ...);     

  

 int    _vswprintf(

     wchar_t * _Buffer, 

     wchar_t const*  _Format

 , va_list _Args);



    #pragma warning(pop)

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swprintf_s_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                           size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)        wchar_t const* const _Format,

        _In_opt_                                       _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswprintf_s_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Success_(return >= 0) 

        _CRT_STDIO_INLINE  int __CRTDECL  swprintf_s(

            _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

            _In_                                           size_t         const _BufferCount,

            _In_z_  _Printf_format_string_                  wchar_t const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vswprintf_s_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(
        _Success_(return >= 0)
        int, swprintf_s, vswprintf_s,
        _Always_(_Post_z_)            wchar_t,        _Buffer,
        _In_z_ _Printf_format_string_ wchar_t const*, _Format
        ) 



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swprintf_p_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                           size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)        wchar_t const* const _Format,

        _In_opt_                                       _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswprintf_p_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swprintf_p(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                           size_t         const _BufferCount,

        _In_z_  _Printf_format_string_                  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswprintf_p_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swprintf_c_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)            wchar_t const* const _Format,

        _In_opt_                                           _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swprintf_c(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_z_  _Printf_format_string_                      wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswprintf_c_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_snwprintf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwprintf_l(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  wchar_t*       const _Buffer,

        _In_                                          size_t         const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)       wchar_t const* const _Format,

        _In_opt_                                      _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        _Result = _vsnwprintf_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        #pragma warning(pop)

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwprintf(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  wchar_t*       _Buffer,

        _In_                                          size_t         _BufferCount,

        _In_z_  _Printf_format_string_                 wchar_t const* _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        _Result = _vsnwprintf_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        #pragma warning(pop)

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwprintf_s_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_                                               size_t         const _MaxCount,

        _In_z_  _Printf_format_string_params_(0)            wchar_t const* const _Format,

        _In_opt_                                           _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnwprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwprintf_s(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  wchar_t*       const _Buffer,

        _In_                                               size_t         const _BufferCount,

        _In_                                               size_t         const _MaxCount,

        _In_z_  _Printf_format_string_                      wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnwprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(
        _Success_(return >= 0)
        int, _snwprintf_s, _vsnwprintf_s,
        _Always_(_Post_z_)            wchar_t,        _Buffer,
        _In_                          size_t,         _BufferCount,
        _In_z_ _Printf_format_string_ wchar_t const*, _Format
        ) 



    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scwprintf_l(

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscwprintf_l(_Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scwprintf(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscwprintf_l(_Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scwprintf_p_l(

        _In_z_  _Printf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                 _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscwprintf_p_l(_Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scwprintf_p(

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscwprintf_p_l(_Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif



    #if !defined RC_INVOKED && !defined __midl && !defined _INC_SWPRINTF_INL_        #pragma warning(push)        #pragma warning(disable: 4141 4412 4793 4996 6054)

        #ifdef __cplusplus

            extern "C++" _SWPRINTFS_DEPRECATED _CRT_INSECURE_DEPRECATE(swprintf_s)

            inline int swprintf(

                _Pre_notnull_ _Post_z_        wchar_t*       const _Buffer,

                _In_z_ _Printf_format_string_ wchar_t const* const _Format,

                ...) throw()

            {

                int _Result;

                va_list _ArgList;

                __crt_va_start(_ArgList, _Format);

                pragma warning(suppress: 28719)

                _Result = vswprintf(_Buffer, _CRT_INT_MAX, _Format, _ArgList);

                __crt_va_end(_ArgList);

                return _Result;

            }



            extern "C++" _SWPRINTFS_DEPRECATED _CRT_INSECURE_DEPRECATE(vswprintf_s)

            inline int __CRTDECL vswprintf(

                _Pre_notnull_ _Post_z_        wchar_t*       const _Buffer,

                _In_z_ _Printf_format_string_ wchar_t const* const _Format,

                                              va_list              _ArgList

                ) throw()

            {

                pragma warning(suppress: 28719)

                return vswprintf(_Buffer, _CRT_INT_MAX, _Format, _ArgList);

            }



            extern "C++" _SWPRINTFS_DEPRECATED _CRT_INSECURE_DEPRECATE(_swprintf_s_l)

            inline int _swprintf_l(

                _Pre_notnull_ _Post_z_                  wchar_t*       const _Buffer,

                _In_z_ _Printf_format_string_params_(0) wchar_t const* const _Format,

                _In_opt_                                _locale_t      const _Locale,

                ...) throw()

            {

                int _Result;

                va_list _ArgList;

                __crt_va_start(_ArgList, _Locale);

                _Result = _vswprintf_l(_Buffer, (size_t)-1, _Format, _Locale, _ArgList);

                __crt_va_end(_ArgList);

                return _Result;

            }



            extern "C++" _SWPRINTFS_DEPRECATED _CRT_INSECURE_DEPRECATE(_vswprintf_s_l)

            inline int __CRTDECL _vswprintf_l(

                _Pre_notnull_ _Post_z_                  wchar_t*       const _Buffer,

                _In_z_ _Printf_format_string_params_(2) wchar_t const* const _Format,

                _In_opt_                                _locale_t      const _Locale,

                                                        va_list              _ArgList

                ) throw()

            {

                return _vswprintf_l(_Buffer, (size_t)-1, _Format, _Locale, _ArgList);

            }



        #endif  // __cplusplus

        #pragma warning(pop)    #endif  // !_INC_SWPRINTF_INL_

    #if defined _CRT_NON_CONFORMING_SWPRINTFS && !defined __cplusplus        define swprintf     _swprintf

        define vswprintf    _vswprintf

        define _swprintf_l  __swprintf_l

        define _vswprintf_l __vswprintf_l

    #endif



    

    

    

    

    

    _Success_(return >= 0) 

    _ACRTIMP  int __cdecl  __stdio_common_vswscanf(

        _In_                                    unsigned __int64long long _Options,

        _In_reads_(_BufferCount)  _Pre_z_        wchar_t const*   _Buffer,

        _In_                                    size_t           _BufferCount,

        _In_z_  _Scanf_format_string_params_(2)  wchar_t const*   _Format,

        _In_opt_                                _locale_t        _Locale,

                                               va_list          _ArgList

        );



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswscanf_l(

        _In_z_                         wchar_t const* const _Buffer,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        _In_opt_                       _locale_t      const _Locale,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vswscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()),

            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vswscanf(

        _In_z_                         wchar_t const* _Buffer,

        _In_z_  _Printf_format_string_  wchar_t const* _Format,

                                      va_list        _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vswscanf_l(_Buffer, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vswscanf_s_l(

        _In_z_                         wchar_t const* const _Buffer,

        _In_z_  _Printf_format_string_  wchar_t const* const _Format,

        _In_opt_                       _locale_t      const _Locale,

                                      va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vswscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()) | _CRT_INTERNAL_SCANF_SECURECRT(1ULL << 0),

            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Success_(return >= 0) 

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vswscanf_s(

            _In_z_                         wchar_t const* const _Buffer,

            _In_z_  _Printf_format_string_  wchar_t const* const _Format,

                                          va_list              _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vswscanf_s_l(_Buffer, _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(
        _Success_(return >= 0)
        int, vswscanf_s,
        _Always_(_Post_z_)            wchar_t,        _Buffer,
        _In_z_ _Printf_format_string_ wchar_t const*, _Format,
                                      va_list,        _Args
        ) 



    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_vsnwscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnwscanf_l(

        _In_reads_(_BufferCount)  _Pre_z_        wchar_t const* const _Buffer,

        _In_                                    size_t         const _BufferCount,

        _In_z_  _Scanf_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                _locale_t      const _Locale,

                                               va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vswscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnwscanf_s_l(

        _In_reads_(_BufferCount)  _Pre_z_          wchar_t const* const _Buffer,

        _In_                                      size_t         const _BufferCount,

        _In_z_  _Scanf_s_format_string_params_(2)  wchar_t const* const _Format,

        _In_opt_                                  _locale_t      const _Locale,

                                                 va_list              _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vswscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()) | _CRT_INTERNAL_SCANF_SECURECRT(1ULL << 0),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_swscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _swscanf_l(

        _In_z_                                  wchar_t const* const _Buffer,

        _In_z_  _Scanf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                _locale_t            _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswscanf_l(_Buffer, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_  _CRT_INSECURE_DEPRECATE(swscanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  swscanf(

        _In_z_                        wchar_t const* const _Buffer,

        _In_z_  _Scanf_format_string_  wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswscanf_l(_Buffer, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _swscanf_s_l(

        _In_z_                                    wchar_t const* const _Buffer,

        _In_z_  _Scanf_s_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                  _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vswscanf_s_l(_Buffer, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Success_(return >= 0) 

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  swscanf_s(

            _In_z_                          wchar_t const* const _Buffer,

            _In_z_  _Scanf_s_format_string_  wchar_t const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vswscanf_s_l(_Buffer, _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_snwscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwscanf_l(

        _In_reads_(_BufferCount)  _Pre_z_        wchar_t const* const _Buffer,

        _In_                                    size_t         const _BufferCount,

        _In_z_  _Scanf_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        _Result = _vsnwscanf_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        #pragma warning(pop)

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_snwscanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwscanf(

        _In_reads_(_BufferCount)  _Pre_z_  wchar_t const* const _Buffer,

        _In_                              size_t         const _BufferCount,

        _In_z_  _Scanf_format_string_      wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        _Result = _vsnwscanf_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        #pragma warning(pop)

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwscanf_s_l(

        _In_reads_(_BufferCount)  _Pre_z_          wchar_t const* const _Buffer,

        _In_                                      size_t         const _BufferCount,

        _In_z_  _Scanf_s_format_string_params_(0)  wchar_t const* const _Format,

        _In_opt_                                  _locale_t      const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnwscanf_s_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snwscanf_s(

        _In_reads_(_BufferCount)  _Pre_z_   wchar_t const* const _Buffer,

        _In_                               size_t         const _BufferCount,

        _In_z_  _Scanf_s_format_string_     wchar_t const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnwscanf_s_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #ifdef _M_CEE_MIXED        pragma managed(pop)

    #endif#endif // _CRT_FUNCTIONS_REQUIRED





_CRT_END_C_HEADER 



_CRT_BEGIN_C_HEADER 







#define BUFSIZ  512







#define _NFILE      _NSTREAM_

#define _NSTREAM_   512



#define _IOB_ENTRIES 3

#define EOF    (-1)

#define _IOFBF 0x0000#define _IOLBF 0x0040#define _IONBF 0x0004





#define L_tmpnam   260 // _MAX_PATH#if __STDC_WANT_SECURE_LIB__    #define L_tmpnam_s L_tmpnam#endif









#define SEEK_CUR    1#define SEEK_END    2#define SEEK_SET    0



#define FILENAME_MAX    260#define FOPEN_MAX       20#define _SYS_OPEN       20#define TMP_MAX         _CRT_INT_MAX#if __STDC_WANT_SECURE_LIB__    #define TMP_MAX_S       TMP_MAX    #define _TMP_MAX_S      TMP_MAX#endif



typedef __int64long long fpos_t;







#if _CRT_FUNCTIONS_REQUIRED

    _Check_return_opt_ 

    _ACRTIMP  errno_t __cdecl  _get_stream_buffer_pointers(

        _In_       FILE*   _Stream,

        _Out_opt_  char*** _Base,

        _Out_opt_  char*** _Pointer,

        _Out_opt_  int**   _Count

        );





    

    

    

    

    

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_wat_ 

        _ACRTIMP  errno_t __cdecl  clearerr_s(

            _Inout_  FILE* _Stream

            );



        _Check_return_wat_ 

        _ACRTIMP  errno_t __cdecl  fopen_s(

            _Outptr_result_maybenull_  FILE**      _Stream,

            _In_z_                     char const* _FileName,

            _In_z_                     char const* _Mode

            );



        _Check_return_opt_ 

        _Success_(return != 0) 

        _ACRTIMP  size_t __cdecl  fread_s(

            _Out_writes_bytes_to_(_BufferSize, _ElementSize * _ElementCount)    void*  _Buffer,

            _In_range_(>=, _ElementSize * _ElementCount)                        size_t _BufferSize,

            _In_                                                                size_t _ElementSize,

            _In_                                                                size_t _ElementCount,

            _Inout_                                                             FILE*  _Stream

            );



        _Check_return_wat_ 

        _ACRTIMP  errno_t __cdecl  freopen_s(

            _Outptr_result_maybenull_  FILE**      _Stream,

            _In_z_                     char const* _FileName,

            _In_z_                     char const* _Mode,

            _Inout_                    FILE*       _OldStream

            );



        _Success_(return != 0) 

        _ACRTIMP  char* __cdecl  gets_s(

            _Out_writes_z_(_Size)  char*   _Buffer,

            _In_                   rsize_t _Size

            );



        _Check_return_wat_ 

        _ACRTIMP  errno_t __cdecl  tmpfile_s(

            _Out_opt_  _Deref_post_valid_  FILE** _Stream

            );



        _Success_(return == 0) 

        _Check_return_wat_ 

        _ACRTIMP  errno_t __cdecl  tmpnam_s(

            _Out_writes_z_(_Size)  char*   _Buffer,

            _In_                   rsize_t _Size

            );



    #endif

    _ACRTIMP  void __cdecl  clearerr(

        _Inout_  FILE* _Stream

        );



    _Success_(return != -1) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fclose(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fcloseall(void);



    _Check_return_ 

    _ACRTIMP  FILE* __cdecl  _fdopen(

        _In_    int         _FileHandle,

        _In_z_  char const* _Mode

        );



    _Check_return_ 

    _ACRTIMP  int __cdecl  feof(

        _In_  FILE* _Stream

        );



    _Check_return_ 

    _ACRTIMP  int __cdecl  ferror(

        _In_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fflush(

        _Inout_opt_  FILE* _Stream

        );



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fgetc(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fgetchar(void);



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fgetpos(

        _Inout_  FILE*   _Stream,

        _Out_    fpos_t* _Position

        );



    _Success_(return == _Buffer) 

    _Check_return_opt_ 

    _ACRTIMP  char* __cdecl  fgets(

        _Out_writes_z_(_MaxCount)  char* _Buffer,

        _In_                       int   _MaxCount,

        _Inout_                    FILE* _Stream

        );



    _Check_return_ 

    _ACRTIMP  int __cdecl  _fileno(

        _In_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _flushall(void);



    _Check_return_  _CRT_INSECURE_DEPRECATE(fopen_s) 

    _ACRTIMP  FILE* __cdecl  fopen(

        _In_z_  char const* _FileName,

        _In_z_  char const* _Mode

        );





    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fputc(

        _In_     int   _Character,

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fputchar(

        _In_  int _Character

        );



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fputs(

        _In_z_   char const* _Buffer,

        _Inout_  FILE*       _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  size_t __cdecl  fread(

        _Out_writes_bytes_(_ElementSize * _ElementCount)  void*  _Buffer,

        _In_                                              size_t _ElementSize,

        _In_                                              size_t _ElementCount,

        _Inout_                                           FILE*  _Stream

        );



    _Success_(return != 0) 

    _Check_return_  _CRT_INSECURE_DEPRECATE(freopen_s) 

    _ACRTIMP  FILE* __cdecl  freopen(

        _In_z_   char const* _FileName,

        _In_z_   char const* _Mode,

        _Inout_  FILE*       _Stream

        );



    _Check_return_ 

    _ACRTIMP  FILE* __cdecl  _fsopen(

        _In_z_  char const* _FileName,

        _In_z_  char const* _Mode,

        _In_    int         _ShFlag

        );



    _Success_(return == 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fsetpos(

        _Inout_  FILE*         _Stream,

        _In_     fpos_t const* _Position

        );



    _Success_(return == 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  fseek(

        _Inout_  FILE* _Stream,

        _In_     long  _Offset,

        _In_     int   _Origin

        );



    _Success_(return == 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fseeki64(

        _Inout_  FILE*   _Stream,

        _In_     __int64long long _Offset,

        _In_     int     _Origin

        );



    _Success_(return != -1) 

    _Check_return_ 

    _ACRTIMP  long __cdecl  ftell(

        _Inout_  FILE* _Stream

        );



    _Success_(return != -1) 

    _Check_return_ 

    _ACRTIMP  __int64long long __cdecl  _ftelli64(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  size_t __cdecl  fwrite(

        _In_reads_bytes_(_ElementSize * _ElementCount)  void const* _Buffer,

        _In_                                            size_t      _ElementSize,

        _In_                                            size_t      _ElementCount,

        _Inout_                                         FILE*       _Stream

        );



    _Success_(return != EOF) 

    _Check_return_ 

    _ACRTIMP  int __cdecl  getc(

        _Inout_  FILE* _Stream

        );



    _Check_return_ 

    _ACRTIMP  int __cdecl  getchar(void);



    _Check_return_ 

    _ACRTIMP  int __cdecl  _getmaxstdio(void);



    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(
        char*, gets_s,
        char, _Buffer) 



    _Check_return_ 

    _ACRTIMP  int __cdecl  _getw(

        _Inout_  FILE* _Stream

        );



    _ACRTIMP  void __cdecl  perror(

        _In_opt_z_  char const* _ErrorMessage

        );



    #if defined _CRT_USE_WINAPI_FAMILY_DESKTOP_APP

        _Success_(return != -1) 

        _Check_return_opt_ 

        _DCRTIMP  int __cdecl  _pclose(

            _Inout_  FILE* _Stream

            );



        _Check_return_ 

        _DCRTIMP  FILE* __cdecl  _popen(

            _In_z_  char const* _Command,

            _In_z_  char const* _Mode

            );



    #endif

    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  putc(

        _In_     int   _Character,

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  putchar(

        _In_  int _Character

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  puts(

        _In_z_  char const* _Buffer

        );



    _Success_(return != -1) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _putw(

        _In_     int   _Word,

        _Inout_  FILE* _Stream

        );



    _ACRTIMP  int __cdecl  remove(

        _In_z_  char const* _FileName

        );



    _Check_return_ 

    _ACRTIMP  int __cdecl  rename(

        _In_z_  char const* _OldFileName,

        _In_z_  char const* _NewFileName

        );



    _ACRTIMP  int __cdecl  _unlink(

        _In_z_  char const* _FileName

        );



    #if _CRT_INTERNAL_NONSTDC_NAMES

        _CRT_NONSTDC_DEPRECATE(_unlink) 

        _ACRTIMP  int __cdecl  unlink(

            _In_z_  char const* _FileName

            );



    #endif

    _ACRTIMP  void __cdecl  rewind(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _rmtmp(void);



    _CRT_INSECURE_DEPRECATE(setvbuf) 

    _ACRTIMP  void __cdecl  setbuf(

        _Inout_                                              FILE* _Stream,

        _Inout_updates_opt_(BUFSIZ)  _Post_readable_size_(0)  char* _Buffer

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _setmaxstdio(

        _In_  int _Maximum

        );



    _Success_(return == 0) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  setvbuf(

        _Inout_                       FILE*  _Stream,

        _Inout_updates_opt_(_Size)    char*  _Buffer,

        _In_                          int    _Mode,

        _In_                          size_t _Size

        );



    #if defined _DEBUG && defined _CRTDBG_MAP_ALLOC        pragma push_macro("_tempnam")

        undef _tempnam

    #endif

    _Check_return_ 

    _ACRTIMP  _CRTALLOCATOR  char* __cdecl  _tempnam(

        _In_opt_z_  char const* _DirectoryName,

        _In_opt_z_  char const* _FilePrefix

        );



    #if defined _DEBUG && defined _CRTDBG_MAP_ALLOC        pragma pop_macro("_tempnam")

    #endif

    _Check_return_  _CRT_INSECURE_DEPRECATE(tmpfile_s) 

    _ACRTIMP  FILE* __cdecl  tmpfile(void);



    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0(
        _Success_(return == 0)
        errno_t, tmpnam_s,
        _Always_(_Post_z_) char, _Buffer
        ) 



    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0(
        _Success_(return != 0)
        char*, __RETURN_POLICY_DST, _ACRTIMP, tmpnam,
        _Pre_maybenull_ _Always_(_Post_z_), char, _Buffer
        )    

  

 char*    tmpnam( 

      char *  _Buffer

 );



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  ungetc(

        _In_     int   _Character,

        _Inout_  FILE* _Stream

        );







    

    

    

    

    

    _ACRTIMP  void __cdecl  _lock_file(

        _Inout_  FILE* _Stream

        );



    _ACRTIMP  void __cdecl  _unlock_file(

        _Inout_  FILE* _Stream

        );



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fclose_nolock(

        _Inout_  FILE* _Stream

        );



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fflush_nolock(

        _Inout_opt_  FILE* _Stream

        );



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fgetc_nolock(

        _Inout_  FILE* _Stream

        );



    _Success_(return != EOF) 

    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fputc_nolock(

        _In_     int   _Character,

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  size_t __cdecl  _fread_nolock(

        _Out_writes_bytes_(_ElementSize * _ElementCount)  void*  _Buffer,

        _In_                                              size_t _ElementSize,

        _In_                                              size_t _ElementCount,

        _Inout_                                           FILE*  _Stream

        );



    _Check_return_opt_ 

    _Success_(return != 0) 

    _ACRTIMP  size_t __cdecl  _fread_nolock_s(

        _Out_writes_bytes_to_(_BufferSize, _ElementSize * _ElementCount)  void*  _Buffer,

        _In_range_(>=, _ElementSize * _ElementCount)                      size_t _BufferSize,

        _In_                                                              size_t _ElementSize,

        _In_                                                              size_t _ElementCount,

        _Inout_                                                           FILE*  _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fseek_nolock(

        _Inout_  FILE* _Stream,

        _In_     long  _Offset,

        _In_     int   _Origin

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _fseeki64_nolock(

        _Inout_  FILE*   _Stream,

        _In_     __int64long long _Offset,

        _In_     int     _Origin

        );



    _Check_return_ 

    _ACRTIMP  long __cdecl  _ftell_nolock(

        _Inout_  FILE* _Stream

        );



    _Check_return_ 

    _ACRTIMP  __int64long long __cdecl  _ftelli64_nolock(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  size_t __cdecl  _fwrite_nolock(

        _In_reads_bytes_(_ElementSize * _ElementCount)  void const* _Buffer,

        _In_                                            size_t      _ElementSize,

        _In_                                            size_t      _ElementCount,

        _Inout_                                         FILE*       _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _getc_nolock(

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _putc_nolock(

        _In_     int   _Character,

        _Inout_  FILE* _Stream

        );



    _Check_return_opt_ 

    _ACRTIMP  int __cdecl  _ungetc_nolock(

        _In_     int   _Character,

        _Inout_  FILE* _Stream

        );



    #define _getchar_nolock()     _getc_nolock(stdin)    #define _putchar_nolock(_Ch)  _putc_nolock(_Ch, stdout)    #define _getwchar_nolock()    _getwc_nolock(stdin)    #define _putwchar_nolock(_Ch) _putwc_nolock(_Ch, stdout)





    #if defined _CRT_DISABLE_PERFCRIT_LOCKS && !defined _DLL        define fclose(_Stream)                                           _fclose_nolock(_Stream)

        define fflush(_Stream)                                           _fflush_nolock(_Stream)

        define fgetc(_Stream)                                            _fgetc_nolock(_Stream)

        define fread(_DstBuf, _ElementSize, _Count, _Stream)             _fread_nolock(_DstBuf, _ElementSize, _Count, _Stream)

        define fread_s(_DstBuf, _DstSize, _ElementSize, _Count, _Stream) _fread_nolock_s(_DstBuf, _DstSize, _ElementSize, _Count, _Stream)

        define fseek(_Stream, _Offset, _Origin)                          _fseek_nolock(_Stream, _Offset, _Origin)

        define _fseeki64(_Stream, _Offset, _Origin)                      _fseeki64_nolock(_Stream, _Offset, _Origin)

        define ftell(_Stream)                                            _ftell_nolock(_Stream)

        define _ftelli64(_Stream)                                        _ftelli64_nolock(_Stream)

        define fwrite(_SrcBuf, _ElementSize, _Count, _Stream)            _fwrite_nolock(_SrcBuf, _ElementSize, _Count, _Stream)

        define getc(_Stream)                                             _getc_nolock(_Stream)

        define putc(_Ch, _Stream)                                        _fputc(_Ch, _Stream)

        define ungetc(_Ch, _Stream)                                      _ungetc_nolock(_Ch, _Stream)

    #endif





    _ACRTIMP  int* __cdecl  __p__commode(void);



    #ifdef _CRT_DECLARE_GLOBAL_VARIABLES_DIRECTLY        extern int _commode;

    #else        #define _commode (*__p__commode())    #endif





    

    #if defined _M_CEE_MIXED        pragma managed(push, off)

    #endif

    

    

    

    

    

    _ACRTIMP  int __cdecl  __stdio_common_vfprintf(

        _In_                                     unsigned __int64long long _Options,

        _Inout_                                  FILE*            _Stream,

        _In_z_  _Printf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _ACRTIMP  int __cdecl  __stdio_common_vfprintf_s(

        _In_                                     unsigned __int64long long _Options,

        _Inout_                                  FILE*            _Stream,

        _In_z_  _Printf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _ACRTIMP  int __cdecl  __stdio_common_vfprintf_p(

        _In_                                     unsigned __int64long long _Options,

        _Inout_                                  FILE*            _Stream,

        _In_z_  _Printf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfprintf_l(

        _Inout_   FILE*       const _Stream,

        _In_z_    char const* const _Format,

        _In_opt_  _locale_t   const _Locale,

                 va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfprintf(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vfprintf(

        _Inout_                        FILE*       const _Stream,

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfprintf_l(_Stream, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfprintf_s_l(

        _Inout_   FILE*       const _Stream,

        _In_z_    char const* const _Format,

        _In_opt_  _locale_t   const _Locale,

                 va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfprintf_s(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vfprintf_s(

            _Inout_                        FILE*       const _Stream,

            _In_z_  _Printf_format_string_  char const* const _Format,

                                          va_list           _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfprintf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfprintf_p_l(

        _Inout_   FILE*       const _Stream,

        _In_z_    char const* const _Format,

        _In_opt_  _locale_t   const _Locale,

                 va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfprintf_p(_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()), _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfprintf_p(

        _Inout_                        FILE*       const _Stream,

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfprintf_p_l(_Stream, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vprintf_l(

        _In_z_  _Printf_format_string_params_(2)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

                                                va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfprintf_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vprintf(

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfprintf_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vprintf_s_l(

        _In_z_  _Printf_format_string_params_(2)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

                                                va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfprintf_s_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vprintf_s(

            _In_z_  _Printf_format_string_  char const* const _Format,

                                          va_list           _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfprintf_s_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vprintf_p_l(

        _In_z_  _Printf_format_string_params_(2)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

                                                va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfprintf_p_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vprintf_p(

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfprintf_p_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fprintf_l(

        _Inout_                                  FILE*       const _Stream,

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  fprintf(

        _Inout_                        FILE*       const _Stream,

        _In_z_  _Printf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_l(_Stream, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _ACRTIMP  int __cdecl  _set_printf_count_output(

        _In_  int _Value

        );



    _ACRTIMP  int __cdecl  _get_printf_count_output(void);



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fprintf_s_l(

        _Inout_                                  FILE*       const _Stream,

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_s_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  fprintf_s(

            _Inout_                        FILE*       const _Stream,

            _In_z_  _Printf_format_string_  char const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfprintf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fprintf_p_l(

        _Inout_                                  FILE*       const _Stream,

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_p_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fprintf_p(

        _Inout_                        FILE*       const _Stream,

        _In_z_  _Printf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_p_l(_Stream, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _printf_l(

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  printf(

        _In_z_  _Printf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _printf_s_l(

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_s_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  printf_s(

            _In_z_  _Printf_format_string_  char const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfprintf_s_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _printf_p_l(

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_p_l(stdout(__acrt_iob_func(1)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _printf_p(

        _In_z_  _Printf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfprintf_p_l(stdout(__acrt_iob_func(1)), _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif



    

    

    

    

    

    _ACRTIMP  int __cdecl  __stdio_common_vfscanf(

        _In_                                    unsigned __int64long long _Options,

        _Inout_                                 FILE*            _Stream,

        _In_z_  _Scanf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                _locale_t        _Locale,

                                               va_list          _Arglist

        );



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfscanf_l(

        _Inout_                        FILE*       const _Stream,

        _In_z_  _Printf_format_string_  char const* const _Format,

        _In_opt_                       _locale_t   const _Locale,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()),

            _Stream, _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vfscanf(

        _Inout_                        FILE*       const _Stream,

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfscanf_l(_Stream, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vfscanf_s_l(

        _Inout_                        FILE*       const _Stream,

        _In_z_  _Printf_format_string_  char const* const _Format,

        _In_opt_                       _locale_t   const _Locale,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vfscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()) | _CRT_INTERNAL_SCANF_SECURECRT(1ULL << 0),

            _Stream, _Format, _Locale, _ArgList);

    }

    #endif



    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vfscanf_s(

            _Inout_                        FILE*       const _Stream,

            _In_z_  _Printf_format_string_  char const* const _Format,

                                          va_list           _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfscanf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscanf_l(

        _In_z_  _Printf_format_string_  char const* const _Format,

        _In_opt_                       _locale_t   const _Locale,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfscanf_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vscanf(

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfscanf_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscanf_s_l(

        _In_z_  _Printf_format_string_  char const* const _Format,

        _In_opt_                       _locale_t   const _Locale,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vfscanf_s_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vscanf_s(

            _In_z_  _Printf_format_string_  char const* const _Format,

                                          va_list           _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vfscanf_s_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

        }

    #endif

    #endif

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_fscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _fscanf_l(

        _Inout_                                 FILE*       const _Stream,

        _In_z_  _Scanf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfscanf_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_  _CRT_INSECURE_DEPRECATE(fscanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  fscanf(

        _Inout_                       FILE*       const _Stream,

        _In_z_  _Scanf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfscanf_l(_Stream, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _fscanf_s_l(

        _Inout_                                   FILE*       const _Stream,

        _In_z_  _Scanf_s_format_string_params_(0)  char const* const _Format,

        _In_opt_                                  _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfscanf_s_l(_Stream, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  fscanf_s(

            _Inout_                         FILE*       const _Stream,

            _In_z_  _Scanf_s_format_string_  char const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfscanf_s_l(_Stream, _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_scanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _scanf_l(

        _In_z_  _Scanf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfscanf_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_  _CRT_INSECURE_DEPRECATE(scanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  scanf(

        _In_z_  _Scanf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfscanf_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scanf_s_l(

        _In_z_  _Scanf_s_format_string_params_(0)  char const* const _Format,

        _In_opt_                                  _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vfscanf_s_l(stdin(__acrt_iob_func(0)), _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  scanf_s(

            _In_z_  _Scanf_s_format_string_  char const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vfscanf_s_l(stdin(__acrt_iob_func(0)), _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif





    

    

    

    

    

    _Success_(return >= 0) 

    _ACRTIMP  int __cdecl  __stdio_common_vsprintf(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_opt_z_(_BufferCount)         char*            _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_z_  _Printf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _ACRTIMP  int __cdecl  __stdio_common_vsprintf_s(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_z_(_BufferCount)             char*            _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_z_  _Printf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _ACRTIMP  int __cdecl  __stdio_common_vsnprintf_s(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_opt_z_(_BufferCount)         char*            _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_                                     size_t           _MaxCount,

        _In_z_  _Printf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _ACRTIMP  int __cdecl  __stdio_common_vsprintf_p(

        _In_                                     unsigned __int64long long _Options,

        _Out_writes_z_(_BufferCount)             char*            _Buffer,

        _In_                                     size_t           _BufferCount,

        _In_z_  _Printf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                 _locale_t        _Locale,

                                                va_list          _ArgList

        );



    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_vsnprintf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnprintf_l(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  char*       const _Buffer,

        _In_                                          size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)       char const* const _Format,

        _In_opt_                                      _locale_t   const _Locale,

                                                     va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsprintf(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()) | _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION(1ULL << 0),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnprintf(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  char*       const _Buffer,

        _In_                                         size_t      const _BufferCount,

        _In_z_  _Printf_format_string_                char const* const _Format,

                                                    va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        return _vsnprintf_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        #pragma warning(pop)    }

    #endif

    #if defined vsnprintf        

        

        

        pragma warning(push, 1)

        pragma warning(1: 4005)

        define vsnprintf Do not define vsnprintf as a macro

        pragma warning(pop)

        error Macro definition of vsnprintf conflicts with Standard Library function declaration

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vsnprintf(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                               size_t      const _BufferCount,

        _In_z_  _Printf_format_string_                      char const* const _Format,

                                                          va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsprintf(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()) | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR(1ULL << 1),

            _Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_vsprintf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsprintf_l(

        _Pre_notnull_  _Always_(_Post_z_)  char*       const _Buffer,

        _In_z_                            char const* const _Format,

        _In_opt_                          _locale_t   const _Locale,

                                         va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        return _vsnprintf_l(_Buffer, (size_t)-1, _Format, _Locale, _ArgList);

        #pragma warning(pop)    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(vsprintf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  vsprintf(

        _Pre_notnull_  _Always_(_Post_z_)  char*       const _Buffer,

        _In_z_  _Printf_format_string_     char const* const _Format,

                                         va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        return _vsnprintf_l(_Buffer, (size_t)-1, _Format, NULL((void *)0), _ArgList);

        #pragma warning(pop)    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsprintf_s_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                           size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)        char const* const _Format,

        _In_opt_                                       _locale_t   const _Locale,

                                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsprintf_s(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Success_(return >= 0) 

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vsprintf_s(

            _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

            _In_                                           size_t      const _BufferCount,

            _In_z_  _Printf_format_string_                  char const* const _Format,

                                                          va_list           _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vsprintf_s_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        }

    #endif

        __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(
            _Success_(return >= 0)
            int, vsprintf_s,
            _Always_(_Post_z_)            char,        _Buffer,
            _In_z_ _Printf_format_string_ char const*, _Format,
                                          va_list,     _ArgList
            ) 



    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsprintf_p_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                           size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)        char const* const _Format,

        _In_opt_                                       _locale_t   const _Locale,

                                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsprintf_p(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsprintf_p(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                           size_t      const _BufferCount,

        _In_z_  _Printf_format_string_                  char const* const _Format,

                                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vsprintf_p_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnprintf_s_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                               size_t      const _BufferCount,

        _In_                                               size_t      const _MaxCount,

        _In_z_  _Printf_format_string_params_(2)            char const* const _Format,

        _In_opt_                                           _locale_t   const _Locale,

                                                          va_list          _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsnprintf_s(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnprintf_s(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                               size_t      const _BufferCount,

        _In_                                               size_t      const _MaxCount,

        _In_z_  _Printf_format_string_                      char const* const _Format,

                                                          va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(
        _Success_(return >= 0)
        int, _vsnprintf_s,
        _Always_(_Post_z_)            char,        _Buffer,
        _In_                          size_t,      _BufferCount,
        _In_z_ _Printf_format_string_ char const*, _Format,
                                      va_list,     _ArgList
        ) 



    #if __STDC_WANT_SECURE_LIB__

        _Success_(return >= 0) 

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vsnprintf_s(

            _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

            _In_                                               size_t      const _BufferCount,

            _In_                                               size_t      const _MaxCount,

            _In_z_  _Printf_format_string_                      char const* const _Format,

                                                              va_list           _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, NULL((void *)0), _ArgList);

        }

    #endif

        __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3(
            _Success_(return >= 0)
            int, vsnprintf_s,
            _Always_(_Post_z_)            char,        _Buffer,
            _In_                          size_t,      _BufferCount,
            _In_z_ _Printf_format_string_ char const*, _Format,
                                          va_list,     _ArgList
            ) 



    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscprintf_l(

        _In_z_  _Printf_format_string_params_(2)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

                                                va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsprintf(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()) | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR(1ULL << 1),

            NULL((void *)0), 0, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscprintf(

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vscprintf_l(_Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscprintf_p_l(

        _In_z_  _Printf_format_string_params_(2)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

                                                va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsprintf_p(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()) | _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR(1ULL << 1),

            NULL((void *)0), 0, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vscprintf_p(

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vscprintf_p_l(_Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnprintf_c_l(

        _Out_writes_opt_(_BufferCount)           char*       const _Buffer,

        _In_                                     size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(2)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

                                                va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int const _Result = __stdio_common_vsprintf(

            _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS(*__local_stdio_printf_options()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        return _Result < 0 ? -1 : _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsnprintf_c(

        _Out_writes_opt_(_BufferCount)  char*       const _Buffer,

        _In_                            size_t      const _BufferCount,

        _In_z_  _Printf_format_string_   char const* const _Format,

                                       va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vsnprintf_c_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_sprintf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _sprintf_l(

        _Pre_notnull_  _Always_(_Post_z_)         char*       const _Buffer,

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        _Result = _vsprintf_l(_Buffer, _Format, _Locale, _ArgList);

        #pragma warning(pop)

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  sprintf(

        _Pre_notnull_  _Always_(_Post_z_)  char*       const _Buffer,

        _In_z_  _Printf_format_string_     char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        _Result = _vsprintf_l(_Buffer, _Format, NULL((void *)0), _ArgList);

        #pragma warning(pop)

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #pragma warning(push)    #pragma warning(disable: 4996)    __DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST(
        _Success_(return >= 0)
        int, __RETURN_POLICY_SAME, __EMPTY_DECLSPEC, __CRTDECL, sprintf, vsprintf,
        _Pre_notnull_ _Always_(_Post_z_), char,        _Buffer,
        _In_z_ _Printf_format_string_     char const*, _Format
        )    

  

 int      sprintf( 

      char *  _Buffer,  

     char const*   _Format

 , ...);      

  

 int      vsprintf( 

      char *  _Buffer,  

     char const*   _Format

 , va_list _Args);

    #pragma warning(pop)

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _sprintf_s_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                           size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)        char const* const _Format,

        _In_opt_                                       _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsprintf_s_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Success_(return >= 0) 

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  sprintf_s(

            _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

            _In_                                           size_t      const _BufferCount,

            _In_z_  _Printf_format_string_                  char const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

            _Result = _vsprintf_s_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST(
        int, sprintf_s, vsprintf_s,
        _Always_(_Post_z_)            char,        _Buffer,
        _In_z_ _Printf_format_string_ char const*, _Format
        ) 



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _sprintf_p_l(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                           size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)        char const* const _Format,

        _In_opt_                                       _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsprintf_p_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _sprintf_p(

        _Out_writes_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                           size_t      const _BufferCount,

        _In_z_  _Printf_format_string_                  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsprintf_p_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_snprintf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _snprintf_l(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  char*       const _Buffer,

        _In_                                          size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)       char const* const _Format,

        _In_opt_                                      _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        #pragma warning(push)        #pragma warning(disable: 4996) // Deprecation        _Result = _vsnprintf_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        #pragma warning(pop)

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if defined snprintf        

        

        

        pragma warning(push, 1)

        pragma warning(1: 4005)

        define snprintf Do not define snprintf as a macro

        pragma warning(pop)

        error Macro definition of snprintf conflicts with Standard Library function declaration

    #endif

    _Success_(return >= 0) 

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  snprintf(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                               size_t      const _BufferCount,

        _In_z_  _Printf_format_string_                      char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

    #pragma warning(suppress:28719)    // __WARNING_BANNED_API_USAGE        _Result = vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _CRT_STDIO_INLINE  int __CRTDECL  _snprintf(

        _Out_writes_opt_(_BufferCount)  _Post_maybez_  char*       const _Buffer,

        _In_                                          size_t      const _BufferCount,

        _In_z_  _Printf_format_string_                 char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

    #pragma warning(suppress:28719)    // __WARNING_BANNED_API_USAGE        _Result = _vsnprintf(_Buffer, _BufferCount, _Format, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    __DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX(
        _Success_(return >= 0)
        int, __RETURN_POLICY_SAME, __EMPTY_DECLSPEC, __CRTDECL, _snprintf, _vsnprintf,
        _Pre_notnull_ _Post_maybez_                   char,
        _Out_writes_opt_(_BufferCount) _Post_maybez_, char,        _Buffer,
        _In_                                          size_t,      _BufferCount,
        _In_z_ _Printf_format_string_                 char const*, _Format
        )   

  

 int    _snprintf(

      char * _Buffer, 

   size_t  _BufferCount, 

     char const*  _Format

 , ...);     

  

 int    _vsnprintf(

      char * _Buffer, 

   size_t  _BufferCount, 

     char const*  _Format

 , va_list _Args);



    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snprintf_c_l(

        _Out_writes_opt_(_BufferCount)           char*       const _Buffer,

        _In_                                     size_t      const _BufferCount,

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnprintf_c_l(_Buffer, _BufferCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snprintf_c(

        _Out_writes_opt_(_BufferCount)  char*       const _Buffer,

        _In_                            size_t      const _BufferCount,

        _In_z_  _Printf_format_string_   char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnprintf_c_l(_Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snprintf_s_l(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                               size_t      const _BufferCount,

        _In_                                               size_t      const _MaxCount,

        _In_z_  _Printf_format_string_params_(0)            char const* const _Format,

        _In_opt_                                           _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Success_(return >= 0) 

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snprintf_s(

        _Out_writes_opt_(_BufferCount)  _Always_(_Post_z_)  char*       const _Buffer,

        _In_                                               size_t      const _BufferCount,

        _In_                                               size_t      const _MaxCount,

        _In_z_  _Printf_format_string_                      char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsnprintf_s_l(_Buffer, _BufferCount, _MaxCount, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST(
        _Success_(return >= 0)
        int, _snprintf_s, _vsnprintf_s,
        _Always_(_Post_z_)            char,        _Buffer,
        _In_                          size_t,      _BufferCount,
        _In_z_ _Printf_format_string_ char const*, _Format
        ) 



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scprintf_l(

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscprintf_l(_Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scprintf(

        _In_z_  _Printf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscprintf_l(_Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scprintf_p_l(

        _In_z_  _Printf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                 _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscprintf_p_l(_Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _scprintf_p(

        _In_z_  _Printf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vscprintf_p(_Format, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    

    

    

    

    

    _ACRTIMP  int __cdecl  __stdio_common_vsscanf(

        _In_                                    unsigned __int64long long _Options,

        _In_reads_(_BufferCount)  _Pre_z_        char const*      _Buffer,

        _In_                                    size_t           _BufferCount,

        _In_z_  _Scanf_format_string_params_(2)  char const*      _Format,

        _In_opt_                                _locale_t        _Locale,

                                               va_list          _ArgList

        );



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsscanf_l(

        _In_z_                         char const* const _Buffer,

        _In_z_  _Printf_format_string_  char const* const _Format,

        _In_opt_                       _locale_t   const _Locale,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vsscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()),

            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  vsscanf(

        _In_z_                         char const* const _Buffer,

        _In_z_  _Printf_format_string_  char const* const _Format,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return _vsscanf_l(_Buffer, _Format, NULL((void *)0), _ArgList);

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _vsscanf_s_l(

        _In_z_                         char const* const _Buffer,

        _In_z_  _Printf_format_string_  char const* const _Format,

        _In_opt_                       _locale_t   const _Locale,

                                      va_list           _ArgList

        )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else    {

        return __stdio_common_vsscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()) | _CRT_INTERNAL_SCANF_SECURECRT(1ULL << 0),

            _Buffer, (size_t)-1, _Format, _Locale, _ArgList);

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        #pragma warning(push)        #pragma warning(disable:6530)

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  vsscanf_s(

            _In_z_                         char const* const _Buffer,

            _In_z_  _Printf_format_string_  char const* const _Format,

                                          va_list           _ArgList

            )

    #if defined _NO_CRT_STDIO_INLINE    ;

    #else        {

            return _vsscanf_s_l(_Buffer, _Format, NULL((void *)0), _ArgList);

        }

    #endif

        __DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2(
            int, vsscanf_s,
            _Always_(_Post_z_)            char const,  _Buffer,
            _In_z_ _Printf_format_string_ char const*, _Format,
                                          va_list,     _ArgList
            ) 



        #pragma warning(pop)

    #endif

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_sscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _sscanf_l(

        _In_z_                                  char const* const _Buffer,

        _In_z_  _Scanf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsscanf_l(_Buffer, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_  _CRT_INSECURE_DEPRECATE(sscanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  sscanf(

        _In_z_                        char const* const _Buffer,

        _In_z_  _Scanf_format_string_  char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsscanf_l(_Buffer, _Format, NULL((void *)0), _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _sscanf_s_l(

        _In_z_                                    char const* const _Buffer,

        _In_z_  _Scanf_s_format_string_params_(0)  char const* const _Format,

        _In_opt_                                  _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));

        _Result = _vsscanf_s_l(_Buffer, _Format, _Locale, _ArgList);

        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #if __STDC_WANT_SECURE_LIB__

        _Check_return_opt_ 

        _CRT_STDIO_INLINE  int __CRTDECL  sscanf_s(

            _In_z_                          char const* const _Buffer,

            _In_z_  _Scanf_s_format_string_  char const* const _Format,

            ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF            ;

    #else        {

            int _Result;

            va_list _ArgList;

            __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



            #pragma warning(push)            #pragma warning(disable: 4996) // Deprecation            _Result = vsscanf_s(_Buffer, _Format, _ArgList);

            #pragma warning(pop)

            __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

            return _Result;

        }

    #endif

    #endif

    #pragma warning(push)    #pragma warning(disable:6530)

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_snscanf_s_l) 

    _CRT_STDIO_INLINE  int __CRTDECL  _snscanf_l(

        _In_reads_bytes_(_BufferCount)  _Pre_z_  char const* const _Buffer,

        _In_                                    size_t      const _BufferCount,

        _In_z_  _Scanf_format_string_params_(0)  char const* const _Format,

        _In_opt_                                _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        _Result = __stdio_common_vsscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_  _CRT_INSECURE_DEPRECATE(_snscanf_s) 

    _CRT_STDIO_INLINE  int __CRTDECL  _snscanf(

        _In_reads_bytes_(_BufferCount)  _Pre_z_  char const* const _Buffer,

        _In_                                    size_t      const _BufferCount,

        _In_z_  _Scanf_format_string_            char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        _Result = __stdio_common_vsscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()),

            _Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);



        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif



    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snscanf_s_l(

        _In_reads_bytes_(_BufferCount)  _Pre_z_    char const* const _Buffer,

        _In_                                      size_t      const _BufferCount,

        _In_z_  _Scanf_s_format_string_params_(0)  char const* const _Format,

        _In_opt_                                  _locale_t   const _Locale,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Locale)((void)(_ArgList = (va_list)(&(  _Locale)) + ((sizeof(  _Locale) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        _Result = __stdio_common_vsscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()) | _CRT_INTERNAL_SCANF_SECURECRT(1ULL << 0),

            _Buffer, _BufferCount, _Format, _Locale, _ArgList);



        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    _Check_return_opt_ 

    _CRT_STDIO_INLINE  int __CRTDECL  _snscanf_s(

        _In_reads_bytes_(_BufferCount)  _Pre_z_  char const* const _Buffer,

        _In_                                    size_t      const _BufferCount,

        _In_z_  _Scanf_s_format_string_          char const* const _Format,

        ...)

    #if defined _NO_CRT_STDIO_INLINE // SCANF        ;

    #else    {

        int _Result;

        va_list _ArgList;

        __crt_va_start(_ArgList, _Format)((void)(_ArgList = (va_list)(&(  _Format)) + ((sizeof(  _Format) + sizeof(int) - 1) & ~(sizeof(int) - 1))));



        _Result = __stdio_common_vsscanf(

            _CRT_INTERNAL_LOCAL_SCANF_OPTIONS(*__local_stdio_scanf_options ()) | _CRT_INTERNAL_SCANF_SECURECRT(1ULL << 0),

            _Buffer, _BufferCount, _Format, NULL((void *)0), _ArgList);



        __crt_va_end(_ArgList)((void)(_ArgList = (va_list)0));

        return _Result;

    }

    #endif

    #pragma warning(pop)

    #if defined _M_CEE_MIXED        pragma managed(pop)

    #endif





    

    

    

    

    

    #if _CRT_INTERNAL_NONSTDC_NAMES

        #define SYS_OPEN  _SYS_OPEN

        #if defined _DEBUG && defined _CRTDBG_MAP_ALLOC            pragma push_macro("tempnam")

            undef tempnam

        #endif

        _CRT_NONSTDC_DEPRECATE(_tempnam) 

        _ACRTIMP  char* __cdecl  tempnam(

            _In_opt_z_  char const* _Directory,

            _In_opt_z_  char const* _FilePrefix

            );



        #if defined _DEBUG && defined _CRTDBG_MAP_ALLOC            pragma pop_macro("tempnam")

        #endif

        _Check_return_opt_  _CRT_NONSTDC_DEPRECATE(_fcloseall)  _ACRTIMP  int   __cdecl  fcloseall(void);

        _Check_return_      _CRT_NONSTDC_DEPRECATE(_fdopen)     _ACRTIMP  FILE* __cdecl  fdopen(_In_  int _FileHandle, _In_z_  char const* _Format);

        _Check_return_opt_  _CRT_NONSTDC_DEPRECATE(_fgetchar)   _ACRTIMP  int   __cdecl  fgetchar(void);

        _Check_return_      _CRT_NONSTDC_DEPRECATE(_fileno)     _ACRTIMP  int   __cdecl  fileno(_In_  FILE* _Stream);

        _Check_return_opt_  _CRT_NONSTDC_DEPRECATE(_flushall)   _ACRTIMP  int   __cdecl  flushall(void);

        _Check_return_opt_  _CRT_NONSTDC_DEPRECATE(_fputchar)   _ACRTIMP  int   __cdecl  fputchar(_In_  int _Ch);

        _Check_return_      _CRT_NONSTDC_DEPRECATE(_getw)       _ACRTIMP  int   __cdecl  getw(_Inout_  FILE* _Stream);

        _Check_return_opt_  _CRT_NONSTDC_DEPRECATE(_putw)       _ACRTIMP  int   __cdecl  putw(_In_  int _Ch, _Inout_  FILE* _Stream);

        _Check_return_      _CRT_NONSTDC_DEPRECATE(_rmtmp)      _ACRTIMP  int   __cdecl  rmtmp(void);



    #endif // _CRT_INTERNAL_NONSTDC_NAMES#endif // _CRT_FUNCTIONS_REQUIRED





_CRT_END_C_HEADER 

#include "h0.h"#ifndef X#define X #endif

void f1();



#ifndef Y#define Y 2#endif

int i;



typedef enum E

{

    E1,

    E2

} E;



typedef struct Point

{

    int x = 1;

    int y = 2;

} Point;



#define NULL  0#define F(a) a + 1

#if 1int i = 1;

#elseint i = 2;

#endif





int main()

{

    Point pt = {1, 2};

    int* p = NULL0;

    p = 0;

    p = (0 );

    F(2)2 + 1;



}