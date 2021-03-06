/////////////////////////////////////////////////////////////////////////////
////    copyright (c) 2012-2017 project_ntke_cpprtl
////    mailto:kt133a@seznam.cz
////    license: the MIT license
/////////////////////////////////////////////////////////////////////////////


#ifndef EH_ENGINE_DEFS_H_
#define EH_ENGINE_DEFS_H_


#include "eh_config.h"
#include <check_ct.h>


////////////////////////////////////////////////////////
////////  EH engine values
////////////////////////////////////////////////////////
namespace cpprtl
{
namespace eh
{
namespace eh_engine
{

  ////////////////////////////////////////////////////
  ////  ::EXCEPTION_RECORD -related stuff


  ////  exception opcodes for ExceptionCode=EXCEPTION_CODE_CPP residing at the ExceptionInformation[EXCPTR_OPCODE]
  enum
  {
    EXCEPTION_OPCODE_THROW               = 'ehop'
  , EXCEPTION_OPCODE_STACK_CONSOLIDATE
  , EXCEPTION_OPCODE_NO_EXC_OBJ
  , EXCEPTION_OPCODE_STACKWALKER_UNWIND
  };


  //// exception flags residing at the ExceptionInformation[EXCPTR_FLAGS]
  enum
  {
    EXCEPTION_FLAG_TRANSLATED          = 1 << 0
  , EXCEPTION_FLAG_OBJECT_RETHROWED    = 1 << 1
  , EXCEPTION_FLAG_STACKWALKER_UNWIND  = 1 << 2
  };


  ////  ExceptionInformation common layout for exceptions generated by this lib
  enum 
  {
    EXCPTR_RESERVED     // because of EXCEPTION_OPCODE_STACK_CONSOLIDATE's the [0] is mandatory held by callback address
  , EXCPTR_OPCODE       // EXCEPTION_OPCODE_xxx
  , EXCPTR_FLAGS        // EXCEPTION_FLAG_xxx
  , EXCPTR_COMMON_LAST 
  };


  ////  ExceptionInformation layout for opcode EXCEPTION_OPCODE_THROW
  enum 
  {
    EXCPTR_THR_THROWOBJECT     = EXCPTR_COMMON_LAST
  , EXCPTR_THR_THROWINFO 
  , EXCPTR_THR_IMAGEBASE 
  , EXCPTR_THR_PREV_EXCEPTION 
  , EXCPTR_THR_UNWIND_EXCREC   // the pointer to the eh-dispatching routine's c++-specific context (the unwind exception record)
  , ARRAYSIZE_EXCPTR_THROW
  };
  COMPILE_TIME_CHECK (ARRAYSIZE_EXCPTR_THROW <= EXCEPTION_MAXIMUM_PARAMETERS , EXCEPTION_MAXIMUM_PARAMETERS_EXCEEDED_THR)


  ////  ExceptionInformation layout for opcode EXCEPTION_OPCODE_STACK_CONSOLIDATE
  enum
  {
    EXCPTR_UNW_CALLBACK_ADDR      // target frame unwind callback address should be at [0],  void* (*)(EXCEPTION_RECORD*)
  , EXCPTR_UNW_FUNCTION_FRAME  = EXCPTR_COMMON_LAST  // funcframe_ptr_t
  , EXCPTR_UNW_HANDLER_ADDR       // catch_handler_ft
  , EXCPTR_UNW_TARGET_STATE       // int
  , EXCPTR_UNW_TARGET_FRAME       // frame_ptr_t
  , EXCPTR_UNW_CONTEXT            // CONTEXT*
  , EXCPTR_UNW_FUNC_DESCRIPTOR    // func_descriptor*
  , EXCPTR_UNW_CURRENT_EXCEPTION  // EXCEPTION_RECORD*
  , EXCPTR_UNW_ARM_NV_CONTEXT     // _M_ARM specific: void* (pointer to the {r4-r11} array filled by RtlUnwindEx(), carefully keep it at [10])
  , ARRAYSIZE_EXCPTR_UNW
  };
  COMPILE_TIME_CHECK (ARRAYSIZE_EXCPTR_UNW <= EXCEPTION_MAXIMUM_PARAMETERS , EXCEPTION_MAXIMUM_PARAMETERS_EXCEEDED_UNW)
  COMPILE_TIME_CHECK (EXCPTR_UNW_CALLBACK_ADDR  == 0 , EXCPTR_UNW_CALLBACK_ADDR_WRONG_VALUE)
  COMPILE_TIME_CHECK (EXCPTR_UNW_ARM_NV_CONTEXT == 10 , EXCPTR_UNW_ARM_NV_CONTEXT_WRONG_VALUE)


  ////  ExceptionInformation layout for opcode EXCEPTION_OPCODE_NO_EXC_OBJ
  enum
  {
    EXCPTR_NOOBJ_EXCREC_PTR  = EXCPTR_COMMON_LAST 
  , ARRAYSIZE_EXCPTR_NOOBJ
  };
  COMPILE_TIME_CHECK (ARRAYSIZE_EXCPTR_NOOBJ <= EXCEPTION_MAXIMUM_PARAMETERS , EXCEPTION_MAXIMUM_PARAMETERS_EXCEEDED_NOOBJ)

}  // namespace eh_engine
}  // namespace eh
}  // namespace cpprtl


#endif  // include guard

