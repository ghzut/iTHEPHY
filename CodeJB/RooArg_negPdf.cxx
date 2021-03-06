/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "RooArg_negPdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(RooArg_negPdf); 

 RooArg_negPdf::RooArg_negPdf(const char *name, const char *title, 
                        RooAbsReal& _DTF_Mass,
                        RooAbsReal& _a1,
                        RooAbsReal& _b1) :
   RooAbsPdf(name,title), 
   DTF_Mass("DTF_Mass","DTF_Mass",this,_DTF_Mass),
   a1("a1","a1",this,_a1),
   b1("b1","b1",this,_b1)
 { 
 } 


 RooArg_negPdf::RooArg_negPdf(const RooArg_negPdf& other, const char* name) :  
   RooAbsPdf(other,name), 
   DTF_Mass("DTF_Mass",this,other.DTF_Mass),
   a1("a1",this,other.a1),
   b1("b1",this,other.b1)
 { 
 } 



 Double_t RooArg_negPdf::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   return pow(DTF_Mass-a1,b1) ; 
 } 



