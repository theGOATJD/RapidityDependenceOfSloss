#include<algorithm>
using namespace std;

TGraphErrors* s1;//PbPb with stat errors
TGraphErrors* s2;//PbPb with sys errors

TGraph* Parameter;//parameter a and b for power law fit
TGraph* Parameter_err;//parameter errors
TGraph* Parameter_plus_sys;//parameter a and b for power law fit from scaled pp plus sys errors
TGraph* Parameter_minus_sys;//parameter a and b for power law fit from scaled pp minus sys errors
TGraph* Actual_Sloss;//The actual Sloss

TCanvas* cc;
Double_t a[4];//parameter a
Double_t b[4];//parameter b
Double_t a_err[4];//a error
Double_t b_err[4];//b error
Double_t a_pp_plus_sys[4];//parameter a for power law fit from scaled pp plus sys errors
Double_t b_pp_plus_sys[4];//parameter b for power law fit from scaled pp plus sys errors
Double_t a_pp_minus_sys[4];//parameter a for power law fit from scaled pp minus sys errors
Double_t b_pp_minus_sys[4];//parameter b for power law fit from scaled pp minus sys errors

TMultiGraph* mg;


void errors(const int file_num = 0) {
	TGraphMultiErrors* g1 = new TGraphMultiErrors();
	Parameter = new TGraph("C:/root/fitting_parameters.txt");//parameters
	Parameter_err = new TGraph("C:/root/fitting_parameters_errors.txt");//parameters errors
	Parameter_plus_sys = new TGraph("C:/root/fitting_parameters_plus_sys.txt");//parameters of pp plus sys
	Parameter_minus_sys = new TGraph("C:/root/fitting_parameters_minus_sys.txt");//parameters of pp minus sys
	Actual_Sloss = new TGraph(Form("C:/root/Sloss_info_%d.txt", file_num));//actual sloss 
	a[file_num] = Parameter->GetX()[file_num];//parameter a
	b[file_num] = Parameter->GetY()[file_num];//parameter b
	a_err[file_num] = Parameter_err->GetX()[file_num];//parameter a error
	b_err[file_num] = Parameter_err->GetY()[file_num];//parameter b error
	a_pp_plus_sys[file_num] = Parameter_plus_sys->GetX()[file_num];//parameter a of scaled pp fit after adding the sys errors
	b_pp_plus_sys[file_num] = Parameter_plus_sys->GetY()[file_num];//parameter b of scaled pp fit after adding the sys errors
	a_pp_minus_sys[file_num] = Parameter_minus_sys->GetX()[file_num];//parameter a of scaled pp fit after subtracting the sys errors
	b_pp_minus_sys[file_num] = Parameter_minus_sys->GetY()[file_num];//parameter b of scaled pp fit after subtracting the sys errors


	switch (file_num) {
	case 0:
		s1 = new TGraphErrors("C:/root/JetPbPb010(0-0.3).txt","%lg %lg %lg","");//0-0.3
		s2 = new TGraphErrors("C:/root_6/JetPbPbSysErr(0-0.3).txt", "%lg %lg %lg", "");
		break;

	case 1:
		s1 = new TGraphErrors("C:/root/JetPbPb010(0.3-0.8).txt", "%lg %lg %lg", "");//0.3-0.8
		s2 = new TGraphErrors("C:/root_6/JetPbPbSysErr(0.3-0.8).txt", "%lg %lg %lg", "");
		break;
	case 2:
		s1 = new TGraphErrors("C:/root/JetPbPb010(0.8-1.2).txt", "%lg %lg %lg", "");//0.8-1.2
		s2 = new TGraphErrors("C:/root_6/JetPbPbSysErr(0.8-1.2).txt", "%lg %lg %lg", "");
		break;
	case 3:
		s1 = new TGraphErrors("C:/root/JetPbPb010(1.2-2.1).txt", "%lg %lg %lg", "");//1.2-2.1
		s2 = new TGraphErrors("C:/root_6/JetPbPbSysErr(1.2-2.1).txt", "%lg %lg %lg", "");
		break;
	default:
		cout << "Invalid file selection!" << endl;
	}
	
	//statistical errors propagation
	
	
	
	
	double Sloss[6] = { 0 };//Actual Sloss
	double Actual_PPx[6] = {0};//Actual Scaled pp pt 
	double PP_pt[6]={0};//All possible pp pt dealing with stat errors
	double Sloss_stat[6] = { 0 };//All possible Sloss dealing with stat errors
	double stat_err[6] = { 0 };//stat errors
	for (int i = 0; i < 6; i++) {
		
		Double_t Pbx = s1->GetX()[i];//PbPb pT
		Double_t Pby = s1->GetY()[i];//PbPb yield

		Double_t Pby_err = s1->GetEY()[i];//PbPb yield stat errors
		//All possible pp pt after considering all possible stat errors(first 4 are parameter errors and last 2 are PbPb yield statistical errors)
		 PP_pt[0] = pow((Pby) / (a[file_num] + a_err[file_num]), 1 / b[file_num]);
		 PP_pt[1] = pow((Pby) / (a[file_num] - a_err[file_num]), 1 / b[file_num]);
		 PP_pt[2] = pow((Pby) / a[file_num], 1 / (b[file_num] + b_err[file_num]));
		 PP_pt[3] = pow((Pby) / a[file_num], 1 / (b[file_num] - b_err[file_num]));
		 PP_pt[4] = pow((Pby + Pby_err) / a[file_num], 1 / b[file_num]);
		 PP_pt[5] = pow((Pby - Pby_err) / a[file_num], 1 / b[file_num]);

		 for (int j = 0; j < 6; j++) {
			 Sloss_stat[j]= (PP_pt[j] - Pbx) / PP_pt[j];
			 cout << "All possible Sloss: " << Sloss_stat[j] << endl;
		 }


		 //dealing stat errors with parameter a and b errors
		int count = 0;
		double max_Sloss_1 = 0;//maximum Sloss for Sloss that are calculated with parameter errors
		while (count < 4) {
			max_Sloss_1 = fmax(max_Sloss_1, Sloss_stat[count]);
			count++;
			
			cout << "max Sloss_1 each time: " << max_Sloss_1 << endl;
		}
		cout << "final max Sloss_1: " << max_Sloss_1 << endl;//max stat error 1

		//dealing stat errors with PbPb stat errors
		int num = 6;
		double max_Sloss_2 = 0;
		while (num > 4) {
			max_Sloss_2 = fmax(max_Sloss_2, Sloss_stat[num]);
			num--;
			cout<< "max Sloss_2 each time: " << max_Sloss_2 << endl;
		}
		cout << "final max Sloss_2: " << max_Sloss_2 << endl;//max stat error 2

		 Sloss[i] = Actual_Sloss->GetY()[i];
		 Actual_PPx[i] = Actual_Sloss->GetX()[i];
		 stat_err[i] = sqrt(pow((max_Sloss_1 - Sloss[i]), 2) + pow((max_Sloss_2 - Sloss[i]), 2));
		 cout << "stat err: " << stat_err[i] << endl;//actual stat errors
		 
		
	}

	//systematic errors propagation


	double PPx_plus_sys[6]={0};//actual scaled pp pt for scaled pp plus sys errors
	double PPx_minus_sys[6]={0};//actural scaled pp pt for scaled pp minus sys errors
	double syst_err[6];//sys errors
	for (int i = 0; i < 6; i++) {
		Double_t Pbx = s1->GetX()[i];//PbPb pT
		Double_t Pby = s1->GetY()[i];//PbPb yield

		PPx_plus_sys[i] = pow(Pby / a_pp_plus_sys[file_num], 1 / b_pp_plus_sys[file_num]);
		Double_t Sloss_I = (PPx_plus_sys[i] - Pbx) / PPx_plus_sys[i];//Sloss(spectra pp + syst.err.(spectra pp), spectra AA)
		PPx_minus_sys[i]= pow(Pby / a_pp_minus_sys[file_num], 1 / b_pp_minus_sys[file_num]);
		Double_t Sloss_II= (PPx_minus_sys[i] - Pbx) / PPx_minus_sys[i];//Sloss(spectra pp - syst.err.(spectra pp), spectra AA)

		Double_t Pby_err = s2->GetEY()[i];//PbPb systematic errors
		Double_t PP_pt_plus_PbPb_err= pow((Pby+Pby_err) / a[file_num], 1 / b[file_num]);
		Double_t Sloss_III = (PP_pt_plus_PbPb_err - Pbx) / PP_pt_plus_PbPb_err;//Sloss(spectra pp, spectra AA + syst.err.(spectra AA))
		Double_t PP_pt_minus_PbPb_err= pow((Pby - Pby_err) / a[file_num], 1 / b[file_num]);
		Double_t Sloss_IV = (PP_pt_minus_PbPb_err - Pbx) / PP_pt_minus_PbPb_err;//Sloss(spectra pp, spectra AA - syst.err.(spectra AA))

		double max_sys_1 = fabs(Sloss[i] - Sloss_I) > fabs(Sloss[i] - Sloss_II) ? fabs(Sloss[i] - Sloss_I) : fabs(Sloss[i] - Sloss_II);
		double max_sys_2 = fabs(Sloss[i] - Sloss_III) > fabs(Sloss[i] - Sloss_IV) ? fabs(Sloss[i] - Sloss_III) : fabs(Sloss[i] - Sloss_IV);
		cout << "sys err candidate 1: " << max_sys_1 << endl;
		cout << "sys err candidate 2: " << max_sys_2 << endl;
		double max_sys = max_sys_1 > max_sys_2 ? max_sys_1 : max_sys_2;
		cout << "Winner:) " << max_sys << endl;
		syst_err[i] = max_sys;//sys errors

		


	}
	double exl1[6] = { 0.005,0.005,0.005,0.005,0.005,0.005 };
	double exh1[6] = { 0.005,0.005,0.005,0.005,0.005,0.005 };
	g1 = new TGraphMultiErrors(6, Actual_PPx, Sloss,exl1,exh1,stat_err,stat_err);//#points,pp_pt,Sloss,pp_pt err low,pp_pt err high,stat err low, stat err high
	g1->AddYError(6, syst_err, syst_err);//sys err low, sys err high
	
	g1->SetMarkerSize(0.65);
	g1->SetLineColor(kRed);
	g1->GetAttLine(0)->SetLineColor(kRed);
	g1->GetAttLine(1)->SetLineColor(kBlue);
	g1->GetAttFill(1)->SetFillStyle(0);
	switch(file_num)
	{
	case 0:
		g1->SetTitle("S_{loss}(0<y<0.3)");
		g1->SetMarkerColor(kRed);
		break;
	case 1:
		g1->SetTitle("S_{loss}(0.3<y<0.8)");
		g1->SetMarkerColor(kViolet);
		break;
	case 2:
		g1->SetTitle("S_{loss}(0.8<y<1.2)");
		g1->SetMarkerColor(kBlack);
		break;
	case 3:
		g1->SetTitle("S_{loss}(1.2<y<2.1)");
		g1->SetMarkerColor(kBlue);
		break;

	default:
		cout << "Invalid file selection" << endl;
		break;
	}
	
	g1->SetMarkerStyle(20);
	g1->SetFillStyle(0);
	mg->Add(g1, "APS ; Z ; 5 s=75 ");

	
}

void Sloss_With_All_Errors() {
	
	cc = new TCanvas("cc", "cc", 5000, 2000);
	mg = new TMultiGraph();
	for (int i = 0; i < 4; i++) {
		errors(i);	
	}
	
	mg->SetTitle("S_{loss}(0-10%,#sqrt{S_{NN}}=2.76 TeV);p_{T}(GeV/c);S_{loss}");
	mg->SetMinimum(0);
	mg->SetMaximum(0.25);
	
	mg->Draw("a");//Draw the comprehensive Sloss info

	cc->BuildLegend();

	
		
	
}

	