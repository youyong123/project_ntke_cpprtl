/////////////////////////////////////////////////////////////////////////////
////    copyright (c) 2012-2017 project_ntke_cpprtl
////    mailto:kt133a@seznam.cz
////    license: the MIT license
/////////////////////////////////////////////////////////////////////////////


#ifndef EH_INVOKE_FUNCLET_H_
#define EH_INVOKE_FUNCLET_H_


extern "C"
{
  void* _CPPRTL_invoke_funclet
  (
    void* funclet_entry
  , void* frame_ptr
  );
}


#endif  // include guard

