/////////////////////////////////////////////////////////////////////////////
////    copyright (c) 2012-2017 project_ntke_cpprtl
////    mailto:kt133a@seznam.cz
////    license: the MIT license
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////
////
////  testing a try-catch block rethrow in another catch scope
////  MT-safe
/////////////////////////////////////////////


#include "context.h"


namespace
{
  enum
  {
    EH_OK              = 0
  , MAGIC_VALUE13      = 130
  , UNEXPECTED_CATCH1  = 131
  , UNEXPECTED_CATCH2  = 132
  , UNEXPECTED_CATCH3  = 133
  , UNEXPECTED_CATCH4  = 134
  };
}


namespace cpprtl { namespace test { namespace eh
{

  int test13()
  {
    context ctx(MAGIC_VALUE13);
    {
      eh_test et(ctx);
      try
      {
        eh_test et(ctx);
        try 
        {
          eh_test et(ctx);
          throw eh_test(ctx, MAGIC_VALUE13);
        }
        catch (eh_test& ex)
        {
          eh_test et(ctx);
          if (MAGIC_VALUE13 == ex.i)
          {
            try
            {
              eh_test et(ctx);
              throw;
            }
            catch (eh_test/*&*/ ex)
            {
              eh_test et(ctx);
              ctx.state = ex.i;
            }
            catch (...)
            {
              ctx.state = UNEXPECTED_CATCH4;
            }
          }
          else
          {
            ctx.state = UNEXPECTED_CATCH3;
          }
        }
        catch (...)
        {
          ctx.state = UNEXPECTED_CATCH2;
        }
      }
      catch (...)
      {
        ctx.state = UNEXPECTED_CATCH1;
      }
    }
    return ctx.balance();
  }

}  }  }

