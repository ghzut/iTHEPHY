/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "RooArg_posPdf.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(RooArg_posPdf); 

 RooArg_posPdf::RooArg_posPdf(const char *name, const char *title, 
                        RooAbsReal& _DTF_Mass,
                        RooAbsReal& _a2,
                        RooAbsReal& _b2) :
   RooAbsPdf(name,title), 
   DTF_Mass("DTF_Mass","DTF_Mass",this,_DTF_Mass),
   a2("a2","a2",this,_a2),
   b2("b2","b2",this,_b2)
 { 
 } 


 RooArg_posPdf::RooArg_posPdf(const RooArg_posPdf& other, const char* name) :  
   RooAbsPdf(other,name), 
   DTF_Mass("DTF_Mass",this,other.DTF_Mass),
   a2("a2",this,other.a2),
   b2("b2",this,other.b2)
 { 
 } 



 Double_t RooArg_posPdf::evaluate() const 
 { 
   // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
   return pow(DTF_Mass-a2,b2) ; 
 } 



