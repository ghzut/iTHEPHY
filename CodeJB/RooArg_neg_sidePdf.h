/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ROOARG_NEG_SIDEPDF
#define ROOARG_NEG_SIDEPDF

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class RooArg_neg_sidePdf : public RooAbsPdf {
public:
  RooArg_neg_sidePdf() {} ; 
  RooArg_neg_sidePdf(const char *name, const char *title,
	      RooAbsReal& _dtf_neg_low,
	      RooAbsReal& _N,
	      RooAbsReal& _a,
	      RooAbsReal& _b);
  RooArg_neg_sidePdf(const RooArg_neg_sidePdf& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooArg_neg_sidePdf(*this,newname); }
  inline virtual ~RooArg_neg_sidePdf() { }

protected:

  RooRealProxy dtf_neg_low ;
  RooRealProxy N ;
  RooRealProxy a ;
  RooRealProxy b ;
  
  Double_t evaluate() const ;

private:

  ClassDef(RooArg_neg_sidePdf,1) // Your description goes here...
};
 
#endif