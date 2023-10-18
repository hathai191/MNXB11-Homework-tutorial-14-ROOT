// include C++ STL headers 
#include <iostream>

using namespace std;

// ROOT library objects
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void rootfuncgenerate(Int_t nEvents, Double_t v2); // ROOT method

//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents, Double_t v2) 
{
  cout << "Generating " << nEvents << " events" << endl << endl;

  // create histogram that we will fill with random values
  TH1D* hPhi = new TH1D("hPhi", "Generated distribution; #phi; Counts", 
                        100, 0, TMath::TwoPi());

  // Define the function we want to generate (f(φ) distribution)
  TF1* functionf = new TF1("functionf", Form("1 + 2*%f*cos(2*(x - 0))", v2), 0, TMath::TwoPi());
  
  // make a loop for the number of events
  for(Int_t n = 0; n < nEvents; n++) {
    
    if((n+1)%1000==0)
      cout << "event " << n+1 << endl;
    
    // fill our distribution histogram
    hPhi->Fill(functionf->GetRandom()); 
  }
  
  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hPhi
  TCanvas* c1 = new TCanvas("c1", "Event Plane Distribution", 900, 600);
  hPhi->SetMinimum(0);
  hPhi->Draw();
  
  // create 1d function that we will use to fit our generated data to determine Ψ2
  TF1* fitFunc = new TF1("fitFunc", "[0]*(1 + 2*[1]*cos(2*(x - 0)))", 0, TMath::TwoPi());
  fitFunc->SetParameter(0, v2);
  fitFunc->SetParLimits(1, 0, 1);
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
  
  // Save the canvas as a picture
  c1->SaveAs("event_plane_rootfunc.jpg");
}