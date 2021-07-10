#include "get_stdout.h"

Double_t myline(Double_t *x,Double_t *par) {
 	return par[0]*x[0] + par[1];
 }



Double_t myline2(Double_t *x,Double_t *par) {
	// run an external command and get its output in a TString
	TString s = get_stdout(Form("./a_line_in_external_file %f %f %f",x[0], par[0], par[1]));
	// split the TString using space as delimiter
	// Example taken from here: https://root-forum.cern.ch/t/split-tstring-by-delimeter-in-root-c/18228/2
	TObjArray *ts = s.Tokenize(" ");
	// get the 1st element in a Double_t and returns to the program
	Double_t ret = atof( ((TObjString *) (ts->At(0)) )->String());
	return ret;
}

void myfit(){

	// this is just to record the execution time
	TStopwatch t;

	/*
		Read the data to from an external file and 
		create 3 TGraphs with errors
	*/
	TGraphErrors * g = new TGraphErrors("data.dat","%lg %lg %lg");
	g->SetTitle("Fit with default pol1 ROOT function");

	TGraphErrors * g2 = (TGraphErrors *) g->Clone();
	g2->SetTitle("Fit with a custom TF1 function");

	TGraphErrors * g3 = (TGraphErrors *) g->Clone();
	g3->SetTitle("Fit with a custom TF1 function using an external program");

	gStyle->SetOptFit(1);
	TCanvas * c = new TCanvas("c", "c", 800,800);

	c->Divide(1,3);

	/*
		Nr 1: 
		simple fit with a ROOT "pol1"
	*/

	c->cd(1);
	g->Draw("APL");
	t.Start();
	g->Fit("pol1");
	t.Stop();
	t.Print("u");

	/*
		Nr 2:
		fit with a TF1 created from a user function
		See ROOT docs here
		https://root.cern.ch/root/htmldoc/guides/users-guide/FittingHistograms.html#the-tf1-function-class
	*/

	TF1 *mylinef = new TF1("mylinef",myline,1,6,2);
	mylinef->SetParameters(0,0);
	mylinef->SetParNames("m", "q");
	c->cd(2);
	g2->Draw("APL");

	t.Start();
	g2->Fit("mylinef");
	t.Stop();
	t.Print("u");

	/*
		Nr 3:
		fit with a TF1 created from a user function which
		actually runs an external program and uses its 
		output 
	*/
	
	TF1 *mylinef2 = new TF1("mylinef2",myline2,1,6,2);
	mylinef2->SetParameters(0,0);
	mylinef2->SetParNames("mm", "qq");
	c->cd(3);
	g3->Draw("APL");

	t.Start();
	g3->Fit("mylinef2");
	t.Stop();
	t.Print("u");


	c->Print("output.pdf");
}