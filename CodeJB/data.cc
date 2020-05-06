#include "eff.h"
#include <chrono>
#include "RooRealVar.h"
#include "RooBreitWigner.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooAddPdf.h"
#include "RooUniform.h"
#include "RooArgusBG.h"
#include "RooGaussian.h"

void printhists(TH1F *h)
{
  TCanvas *c = new TCanvas();
  h->Draw();
  h->Draw("hist same");
  string title_name = h->GetName();
  string save_name = "output/data/plots/"+title_name+".pdf";
  c->SaveAs(save_name.c_str());
}

void data(string dir, string sample)
{
  uint64_t start_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
  string input_name = dir+"/"+sample+".root";
  TChain *ntp = new TChain();
  ntp->AddFile(input_name.c_str(),-1,"ntp;25");
  ntp->AddFile(input_name.c_str(),-1,"ntp;26");
  int nEvents = ntp->GetEntries();


  TFile *f = new TFile("output/histOut_minisample_Dst2D0pi_D02Kpi_2016_Up_GEN.root");
  TH1F *h_pT_Dst = (TH1F*)f->Get("h_pT_reco_Dst");
  int nMCEvents = h_pT_Dst->GetEntries();

  h_pT_Dst->Scale(double(nEvents)/nMCEvents);

  double nDst_pos = 0.; double nDst_neg = 0.;
  int Dst_ID, D0_ID, Pi_ID, K_ID;
  double D0_mass;
  double DTF_mass;

/*  RooRealVar *y = new RooRealVar("Dst_DTF_PT", "Dstar pT/GeV", 2000.,11100.);
  RooDataSet *datahist = new RooDataSet("data_pT", "Dstar pT data", ntp, RooArgSet(*y));
  RooPlot *yframe = y->frame();
  datahist->plotOn(yframe, RooFit::Binning(182));
  yframe->Draw();
  h_pT_Dst->Draw("same");
  h_pT_Dst->Draw("same hist");
  canvas2->SaveAs("output/data/plots/pT_MC_data.pdf");

  RooRealVar *x = new RooRealVar("DTF_Mass", "DTF mass [MeV]", 2004., 2020.);
  RooDataSet *dataset = new RooDataSet("data", "DTF_Mass data", ntp, RooArgSet(*x));
  RooPlot *xframe = x->frame();
  dataset->plotOn(xframe, RooFit::Binning(80));
  xframe->Draw();
  canvas2->SaveAs("output/data/plots/RooData.pdf");

  RooRealVar *mean = new RooRealVar("mean", "mean", 2011., 2008., 2014.);
  RooRealVar *sigma = new RooRealVar("sigma", "sigma", 1., 0., 3.);
  RooRealVar *rel_frac = new RooRealVar("rel_frac", "Relative Fraction", 0.7, 0.0, 1.0);
  RooBreitWigner *bw = new RooBreitWigner("BW", "BW", *x, *mean, *sigma);
  RooUniform *bkg = new RooUniform("bkg", "bkg", *x);
  RooAddPdf *model = new RooAddPdf("model", "model", RooArgList(*bw,*bkg), RooArgList(*rel_frac));
  model->fitTo(*dataset, RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1));
  RooPlot * xframe2 = x->frame();
  dataset->plotOn(xframe2);
  model->plotOn(xframe2);
  model->plotOn(xframe2, RooFit::Components("bkg"), RooFit::LineColor(kAzure), RooFit::LineStyle(kDashed));
  model->plotOn(xframe2);
  model->paramOn(xframe2, RooFit::Label("Fit Results"), RooFit::Format("NEU", RooFit::AutoPrecision(1)), RooFit::Layout(0.5,0.9,0.8));
  xframe2->Draw();
  canvas2->SaveAs("output/data/plots/RooFit.pdf");

*/
  ntp->SetBranchStatus("*",0);
  ntp->SetBranchStatus("D0_M",1); ntp->SetBranchAddress("D0_M", &(D0_mass));
  ntp->SetBranchStatus("DTF_Mass",1); ntp->SetBranchAddress("DTF_Mass", &(DTF_mass));

  ntp->SetBranchStatus("Dst_ID",1); ntp->SetBranchAddress("Dst_ID", &(Dst_ID));
  ntp->SetBranchStatus("D0_ID",1); ntp->SetBranchAddress("D0_ID", &(D0_ID));
  ntp->SetBranchStatus("P1_ID",1); ntp->SetBranchAddress("P1_ID", &(Pi_ID));
  ntp->SetBranchStatus("P2_ID",1); ntp->SetBranchAddress("P2_ID", &(K_ID));


  TH1F *h_Dst_pos_D0m = new TH1F("h_Dst_pos_D0m", ";invariant D0 mass/MeV; Events", 92, 1842., 1888.);
  TH1F *h_Dst_neg_D0m = new TH1F("h_Dst_neg_D0m", ";invariant D0 mass/MeV; Events", 92, 1842., 1888.);
  TH1F *h_Dst_asym_D0m = new TH1F("h_Dst_asym_D0m", ";invariant D0 mass/MeV; assymmetry", 92, 1842., 1888.);

  h_Dst_pos_D0m->Sumw2();
  h_Dst_neg_D0m->Sumw2();
  h_Dst_asym_D0m->Sumw2();

  TH1F *h_Dst_pos_DTFm = new TH1F("h_Dst_pos_DTFm", ";invariant DTF mass/MeV; Events", 80, 2004., 2020.);
  TH1F *h_Dst_neg_DTFm = new TH1F("h_Dst_neg_DTFm", ";invariant DTF mass/MeV; Events", 80, 2004., 2020.);
  TH1F *h_Dst_asym_DTFm = new TH1F("h_Dst_asym_DTFm", ";invariant DTF mass/MeV; assymmetry", 80, 2004., 2020.);

  TH1F *h_delta_m_pos = new TH1F("h_delta_m_pos", "; #Delta m; Events", 124, 116., 178.);
  TH1F *h_delta_m_neg = new TH1F("h_delta_m_neg", ";#Delta m; Events", 124, 116., 178.);
  TH1F *h_delta_m_asym = new TH1F("h_delta_m_asym", ";#Delta m; assymmetry", 124, 116., 178.);

  h_Dst_pos_DTFm->Sumw2();
  h_Dst_neg_DTFm->Sumw2();
  h_Dst_asym_DTFm->Sumw2();

  h_delta_m_neg->Sumw2();
  h_delta_m_pos->Sumw2();
  h_delta_m_asym->Sumw2();

  for (int i = 0; i < nEvents; ++i)
  {
    if (i % (nEvents/10) == 0)
    {
      std::cout << "=== Event " << i/(nEvents/10) * 10 << "%" << std::endl;
    }
    ntp->GetEvent(i);
    if(Dst_ID < 0)
    {
      h_Dst_neg_D0m->Fill(D0_mass);
      h_Dst_neg_DTFm->Fill(DTF_mass);
      h_delta_m_neg->Fill(DTF_mass - D0_mass);
      ++nDst_neg;
    }
    else
    {
      h_Dst_pos_D0m->Fill(D0_mass);
      h_Dst_pos_DTFm->Fill(DTF_mass);
      h_delta_m_pos->Fill(DTF_mass-D0_mass);
      ++nDst_pos;
    }
  }
  double Dst_asym = (nDst_pos-nDst_neg)/(nDst_pos+nDst_neg);

  cout << "Number of reconstructed -: " << nDst_neg << endl;
  cout << "Number of reconstructed +: " << nDst_pos << endl;
  cout << "The total Dst assymmetry is: " << Dst_asym << endl;

  printhists(h_Dst_pos_D0m);
  printhists(h_Dst_neg_D0m);
  printhists(h_Dst_pos_DTFm);
  printhists(h_Dst_neg_DTFm);
  printhists(h_delta_m_neg);
  printhists(h_delta_m_pos);

  string output_hist_name;
  output_hist_name = "output/data/histOut_"+sample+".root";
  TFile *out_hist_fi = new TFile(output_hist_name.c_str(),"RECREATE");

  h_Dst_pos_D0m->Write();
  h_Dst_neg_D0m->Write();
  h_Dst_pos_DTFm->Write();
  h_Dst_neg_DTFm->Write();



  h_Dst_pos_D0m->Add(h_Dst_neg_D0m,-1);
  h_Dst_neg_D0m->Scale(2.);
  h_Dst_neg_D0m->Add(h_Dst_pos_D0m);
  h_Dst_pos_D0m->Divide(h_Dst_neg_D0m);
  h_Dst_asym_D0m = h_Dst_pos_D0m;
  h_Dst_asym_D0m->SetName("h_Dst_asym_D0m");
  h_Dst_asym_D0m->SetTitle(";invariant D0 mass/MeV; assymmetry");
  printhists(h_Dst_asym_D0m);

  h_Dst_pos_DTFm->Add(h_Dst_neg_DTFm,-1);
  h_Dst_neg_DTFm->Scale(2.);
  h_Dst_neg_DTFm->Add(h_Dst_pos_DTFm);
  h_Dst_pos_DTFm->Divide(h_Dst_neg_DTFm);
  h_Dst_asym_DTFm = h_Dst_pos_DTFm;
  h_Dst_asym_DTFm->SetName("h_Dst_asym_DTFm");
  h_Dst_asym_DTFm->SetTitle(";invariant DTF mass/MeV; assymmetry");
  printhists(h_Dst_asym_DTFm);


  //RooFit things

  RooRealVar *dm_neg = new RooRealVar("dm_neg", "dm_neg", 116., 178.);
  RooRealVar *dm_pos = new RooRealVar("dm_neg", "dm_neg", 116., 178.);
  RooDataHist *data = new RooDataHist("data", "datahist", RooArgList(*dm_neg), h_delta_m_neg);

  RooDataHist *data2 =  new RooDataHist("data2", "datahist2", RooArgList(*dm_pos), h_delta_m_pos);

  RooPlot *frame1 = dm_neg->frame();  RooPlot *frame2 = dm_pos->frame(); RooPlot *frame3 = dm_pos->frame();



  RooRealVar *m0 = new RooRealVar("m0", "m0", 178., 170., 200.);
  RooRealVar *c = new RooRealVar("c", "c", -2., -10., 10.);
  RooRealVar *mean = new RooRealVar("mean", "mean", 146., 135., 155.);
  RooRealVar *sigma = new RooRealVar("sigma", "sigma", 8., 4., 10.);
  RooRealVar *m02 = new RooRealVar("m02", "m02", 177., 170., 190.);
  RooRealVar *c2 = new RooRealVar("c2", "c2", -3., -10., 10.);
  RooRealVar *mean2 = new RooRealVar("mean2", "mean2", 145., 140., 150.);
  RooRealVar *sigma2 = new RooRealVar("sigm2a", "sigma2", 8.3, 6., 10.);
  RooRealVar *rel_frac = new RooRealVar("rel_frac", "rel_frac", 0.9, 0.2, 1.);
  RooArgusBG *bkg_neg = new RooArgusBG("bkg_neg", "bkg_neg", *dm_neg, *m0, *c);
  RooGaussian *sig_neg = new RooGaussian("sig_neg", "sig_neg", *dm_neg, *mean, *sigma);
  RooArgusBG *bkg_pos = new RooArgusBG("bkg_neg", "bkg_pos", *dm_pos, *m0, *c);
  RooGaussian *sig_pos = new RooGaussian("sig_neg", "sig_pos", *dm_pos, *mean, *sigma);
  //RooAddPdf *model_neg = new RooAddPdf("model_neg", "model_neg", RooArgList(*sig_neg,*bkg_neg), RooArgList(*rel_frac));
  //RooAddPdf *model_pos = new RooAddPdf("model_pos", "model_pos", RooArgList(*sig_pos,*bkg_pos), RooArgList(*rel_frac));

  //RooAddPdf *model_neg = new RooAddPdf("model_neg", "model_neg", RooArgList(*sig_neg));
  //RooAddPdf *model_pos = new RooAddPdf("model_pos", "model_pos", RooArgList(*sig_pos));


  //model_neg->fitTo(*data, RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1));
  //model_pos->fitTo(*data2, RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1));
  sig_neg->fitTo(*data, RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1));
  data->plotOn(frame1);
  sig_neg->plotOn(frame1);
  sig_neg->paramOn(frame1, RooFit::Label("Fit Results"), RooFit::Format("NEU", RooFit::AutoPrecision(1)), RooFit::Layout(0.65,0.9,0.8));

  //model_neg->plotOn(frame1);
  //model_neg->paramOn(frame1, RooFit::Label("Fit Results"), RooFit::Format("NEU", RooFit::AutoPrecision(1)), RooFit::Layout(0.8,0.9,0.8));

  bkg_pos->plotOn(frame3);

  //model_neg->plotOn(frame1, RooFit::Components("bkg_neg"), RooFit::LineColor(kAzure), RooFit::LineStyle(kDashed));
  //model_pos->plotOn(frame2, RooFit::Components("bkg_pos"), RooFit::LineColor(kAzure), RooFit::LineStyle(kDashed));
  sig_pos->fitTo(*data2, RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1));
  data2->plotOn(frame2);
  sig_pos->plotOn(frame2);
  sig_pos->paramOn(frame2, RooFit::Label("Fit Results"), RooFit::Format("NEU", RooFit::AutoPrecision(1)), RooFit::Layout(0.65,0.9,0.8));

  //model_pos->plotOn(frame2);
  //model_pos->paramOn(frame2, RooFit::Label("Fit Results"), RooFit::Format("NEU", RooFit::AutoPrecision(1)), RooFit::Layout(0.8,0.9,0.8));


  TCanvas *canvas2 = new TCanvas();
  frame1->Draw();
  canvas2->SaveAs("output/data/plots/datahist.pdf");
  frame2->Draw();
  canvas2->SaveAs("output/data/plots/datahist2.pdf");
  frame3->Draw();
  canvas2->SaveAs("output/data/plots/datahist3.pdf");

  h_delta_m_pos->Add(h_delta_m_neg,-1);
  h_delta_m_neg->Scale(2.);
  h_delta_m_neg->Add(h_delta_m_pos);
  h_delta_m_pos->Divide(h_delta_m_neg);
  h_delta_m_asym = h_delta_m_pos;
  h_delta_m_asym->SetName("h_delta_m_asym");
  h_delta_m_asym->SetTitle(";#Delta m/MeV; assymmetry");
  h_delta_m_asym->SetAxisRange(-0.05, 0.05, "Y");
  printhists(h_delta_m_asym);

  h_Dst_asym_D0m->Write();
  h_Dst_asym_DTFm->Write();
  out_hist_fi->Write();
  out_hist_fi->Close();

  uint64_t end_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
  float elapsed = (end_time - start_time)*0.000001;
  std::cout << "computation time/s: " << elapsed << std::endl;
  std::cout << "computation time/min: " << elapsed/60. << std::endl;
}
