using namespace std;
TGraphErrors *g1;//scaled pp
TGraph* g2;//scaled pp plus sys errors
TGraph* g3;//scaled pp minus sys errors
TGraph* s1;//PbPb with stat errors
TGraph* Sloss_graph;//Graph that shows Sloss
TCanvas* cc[4];
TCanvas* c1[4];
TCanvas* c2[4];
TCanvas* Sloss_showcase[4];//Sloss canvas
Double_t a[4];//paramter a
Double_t b[4];//parameter b
Double_t a_err[4];//a errors
Double_t b_err[4];//b errors
Double_t a_pp_plus_sys[4];//parameter a from scaled pp plus sys errors
Double_t b_pp_plus_sys[4];//parameter b from scaled pp plus sys errors
Double_t a_pp_plus_par_err[4];//associated parameter errors for a from scaled pp plus sys errors
Double_t b_pp_plus_par_err[4];//associated parameter errors for b from scaled pp plus sys errors
Double_t a_pp_minus_sys[4];//parameter a from scaled pp minus sys errors
Double_t b_pp_minus_sys[4];//parameter b from scaled pp minus sys errors
Double_t a_pp_minus_par_err[4];//associated parameter errors for a from scaled pp minus sys errors
Double_t b_pp_minus_par_err[4];//associated parameter errors for b from scaled pp minus sys errors

//general fit
void Fit(const int file_selection=0) {
	
		
		
		
		switch (file_selection) {
		case 0:
			
			
		    g1 = new TGraphErrors("C:/root/ppScaledByTAA(0-0.3).txt", "%lg %lg %lg", "");//0-0.3
			g1->SetTitle("pp spectra with a fit(0-10%)(0-0.3);p_{T}(GeV);Cross Section");
			
			break;
			
		case 1:
			
			 g1 = new TGraphErrors("C:/root/ppScaledByTAA(0.3-0.8).txt", "%lg %lg %lg", "");//0.3-0.8
			g1->SetTitle("pp spectra with a fit(0-10%)(0.3-0.8);p_{T}(GeV);Cross Section");
		    
			break;
		case 2:
			
			 g1 = new TGraphErrors("C:/root/ppScaledByTAA(0.8-1.2).txt", "%lg %lg %lg", "");//0.8-1.2
			g1->SetTitle("pp spectra with a fit(0-10%)(0.8-1.2);p_{T}(GeV);Cross Section");
			
			break;
		case 3:
			
			 g1 = new TGraphErrors("C:/root/ppScaledByTAA(1.2-2.1).txt", "%lg %lg %lg", "");//1.2-2.1
			g1->SetTitle("pp spectra with a fit(0-10%)(1.2-2.1);p_{T}(GeV);Cross Section");
			
			break;
		default:
			cout << "Invalid file selection!" << endl;
		}
		
		g1->SetMarkerStyle(21);
		g1->SetFillStyle(0);
		g1->SetMinimum(0.0000000004851);
		g1->SetMaximum(30);
		g1->Draw("AP");
		g1->SetMarkerColor(kRed);

		TF1* f1 = new TF1("f1", "[0]*x^[1]", 50, 200);

		f1->SetParNames("A", "B");
		f1->SetParameters(2.03008e+007, -6.00790e+000);
		f1->SetLineColor(kBlack);

		f1->Draw("same");
		f1->SetTitle("Fitting");



		g1->Fit(f1);
		a[file_selection] = f1->GetParameter("A");//input the parameter a to the array
		b[file_selection] = f1->GetParameter("B");//input the parameter b to the array
		a_err[file_selection] = f1->GetParError(0);
		b_err[file_selection] = f1->GetParError(1);



		
		cc[file_selection]->BuildLegend();
		cc[file_selection]->SetLogy();
		
		 
}

//fit for scaled pp plus sys errors
void Fit_plus_systematic_errors(const int file_selection = 0) {
	switch (file_selection) {
	case 0:


		g2 = new TGraph("C:/root_6/ppScaledByTAAPlusSystematicErrors(0-0.3).txt");
		g2->SetTitle("pp spectra plus sys err with a fit(0-10%)(0-0.3);p_{T}(GeV);Cross Section");
		
		break;

	case 1:

		g2 = new TGraph("C:/root_6/ppScaledByTAAPlusSystematicErrors(0.3-0.8).txt");
		g2->SetTitle("pp spectra plus sys err with a fit(0-10%)(0.3-0.8);p_{T}(GeV);Cross Section");
		

		break;
	case 2:
		g2 = new TGraph("C:/root_6/ppScaledByTAAPlusSystematicErrors(0.8-1.2).txt");
		g2->SetTitle("pp spectra plus sys err with a fit(0-10%)(0.8-1.2);p_{T}(GeV);Cross Section");
		
		

		break;
	case 3:
		g2 = new TGraph("C:/root_6/ppScaledByTAAPlusSystematicErrors(1.2-2.1).txt");
		g2->SetTitle("pp spectra plus sys err with a fit(0-10%)(1.2-2.1);p_{T}(GeV);Cross Section");
		

		break;
	default:
		cout << "Invalid file selection!" << endl;
	}

	g2->SetMarkerStyle(21);
	g2->SetFillStyle(0);
	g2->SetMinimum(0.0000000004851);
	g2->SetMaximum(30);
	g2->Draw("AP");
	g2->SetMarkerColor(kRed);

	TF1* f2 = new TF1("f2", "[0]*x^[1]", 50, 200);

	f2->SetParNames("A", "B");
	if (file_selection == 2 ) f2->SetParameters(17.63008e+007, -4.7);
	else if(file_selection == 3) f2->SetParameters(11.069e+007, -5.0);
	else f2->SetParameters(14.23008e+007, -4.5);
	f2->SetLineColor(kBlack);

	f2->Draw("same");
	f2->SetTitle("Fitting");



	g2->Fit(f2);
	a_pp_plus_sys[file_selection] = f2->GetParameter("A");
	b_pp_plus_sys[file_selection] = f2->GetParameter("B");
	a_pp_plus_par_err[file_selection]=f2->GetParError(0);
	b_pp_plus_par_err[file_selection] = f2->GetParError(1);

	c1[file_selection]->BuildLegend();
	c1[file_selection]->SetLogy();
}

//fit for scaled pp minus sys errors
void Fit_minus_systematic_errors(const int file_selection = 0) {

	switch (file_selection) {
	case 0:


		
		g3 = new TGraph("C:/root_6/ppScaledByTAAMinusSystematicErrors(0-0.3).txt");
		g3->SetTitle("pp spectra minus sys err with a fit(0-10%)(0-0.3);p_{T}(GeV);Cross Section");
		break;

	case 1:

		
		g3 = new TGraph("C:/root_6/ppScaledByTAAMinusSystematicErrors(0.3-0.8).txt");
		g3->SetTitle("pp spectra minus sys err with a fit(0-10%)(0.3-0.8);p_{T}(GeV);Cross Section");

		break;
	case 2:
		
		g3 = new TGraph("C:/root_6/ppScaledByTAAMinusSystematicErrors(0.8-1.2).txt");
		g3->SetTitle("pp spectra minus sys err with a fit(0-10%)(0.8-1.2);p_{T}(GeV);Cross Section");


		break;
	case 3:
		
		g3 = new TGraph("C:/root_6/ppScaledByTAAMinusSystematicErrors(1.2-2.1).txt");
		g3->SetTitle("pp spectra minus sys err with a fit(0-10%)(1.2-2.1);p_{T}(GeV);Cross Section");

		break;
	default:
		cout << "Invalid file selection!" << endl;
	}

	g3->SetMarkerStyle(21);
	g3->SetFillStyle(0);
	g3->SetMinimum(0.0000000004851);
	g3->SetMaximum(30);
	g3->Draw("AP");
	g3->SetMarkerColor(kRed);

	TF1* f3 = new TF1("f3", "[0]*x^[1]", 50, 200);

	f3->SetParNames("A", "B");
	if (file_selection == 2 ) f3->SetParameters(4.82725e+07, -4.6);
	else if(file_selection==3) f3->SetParameters(12.038e+007, -5.0);
	else f3->SetParameters(11.23008e+007, -4.5);
	f3->SetLineColor(kBlack);

	f3->Draw("same");
	f3->SetTitle("Fitting");



	g3->Fit(f3);

	a_pp_minus_sys[file_selection] = f3->GetParameter("A");
	b_pp_minus_sys[file_selection] = f3->GetParameter("B");
	a_pp_minus_par_err[file_selection] = f3->GetParError(0);
	b_pp_minus_par_err[file_selection] = f3->GetParError(1);

	c2[file_selection]->BuildLegend();
	c2[file_selection]->SetLogy();

}


//Sloss computation
void Sloss(const int file_num = 0) {
	Sloss_graph = new TGraph();
	switch (file_num) {
	case 0:
		s1 = new TGraph("C:/root/JetPbPb010(0-0.3).txt");
		Sloss_graph->SetTitle("S_{loss}(0-0.3);p^{pp}_{T}(GeV);S_{loss}");
		break;

	case 1:
		s1 = new TGraph("C:/root/JetPbPb010(0.3-0.8).txt");
		Sloss_graph->SetTitle("S_{loss}(0.3-0.8);p^{pp}_{T}(GeV);S_{loss}");
		break;
	case 2:
		s1 = new TGraph("C:/root/JetPbPb010(0.8-1.2).txt");
		Sloss_graph->SetTitle("S_{loss}(0.8-1.2);p^{pp}_{T}(GeV);S_{loss}");
		break;
	case 3:
		s1 = new TGraph("C:/root/JetPbPb010(1.2-2.1).txt");
		Sloss_graph->SetTitle("S_{loss}(1.2-2.1);p^{pp}_{T}(GeV);S_{loss}");
		break;
	default:
		cout << "Invalid file selection!" << endl;
	}
	
	ofstream Sloss_file(Form("C:/root/Sloss_info_%d.txt",file_num));
	Sloss_file << "pp_pt" << "\t\t\t\t\t\t\t\t\t\t" << "Sloss: " << endl;
	double pp_pt[6] = { 0 };
	double Sloss[6] = { 0 };
	for (int i = 0; i < 6; i++) {
		//say that PbPb pT is Pbx
		Double_t Pbx = s1->GetX()[i];
		//say that PbPb yield is Pby
		Double_t Pby = s1->GetY()[i];

		Double_t PPx = pow((Pby) / a[file_num], 1 / b[file_num]);//supposed scaled pp pt

		//print out the corresponding pp pt and the Sloss
		cout << "pp pt: " << PPx <<"\t\t\t\t\t\t\t\t\t\t" <<"Sloss: "<< (PPx - Pbx) / PPx<< endl;
		pp_pt[i] = PPx;//pp pt
		Sloss[i] = (PPx - Pbx) / PPx;//Sloss
		Sloss_file<< pp_pt[i] << "\t\t\t\t\t\t\t\t\t" << Sloss[i] << endl;
		Sloss_graph->SetPoint(i, PPx, (PPx - Pbx) / PPx);
	}
	Sloss_file.close();
	
	Sloss_graph->SetMarkerStyle(20);
	Sloss_graph->SetFillStyle(0);
	Sloss_graph->SetMinimum(0);
	Sloss_graph->SetMaximum(0.5);
	Sloss_graph->Draw("AP");

	Sloss_showcase[file_num]->BuildLegend()->SetTextSize(0.05);

	
}

void CalculateSloss() {
	ofstream file1("C:/root/fitting_parameters.txt");
	file1 << "a " << "\t\t\t\t\t\t\t\t\t\t" << "b " << endl;
	ofstream file2("C:/root/fitting_parameters_errors.txt");
	file2 << "ea " << "\t\t\t\t\t\t\t\t\t\t" << "eb " << endl;

	//loops which will compute all info respect to different y
	for (int i = 0; i < 4; i++) {
		
		cc[i] = new TCanvas(Form("cc_%d",i), Form("cc_%d", i), 5000, 2000);
		
		
		Fit(i);
		
		file1 << a[i] << "\t\t\t\t\t\t\t\t\t" << b[i] << endl;
		file2 <<a_err[i]<<"\t\t\t\t\t\t\t\t\t" << b_err[i] << endl;
		Sloss_showcase[i]= new TCanvas(Form("Sloss_showcase_%d", i), Form("Sloss_showcase_%d", i), 5000, 2000);
		Sloss(i);
		
		
		
		
	}
	file1.close();
	file2.close();

	ofstream file3("C:/root/fitting_parameters_plus_sys.txt");
	file3 << "a " << "\t\t\t\t\t\t\t\t\t\t" << "b " << endl;
	ofstream file4("C:/root/fitting_parameters_plus_sys_errors.txt");
	file4 << "ea " << "\t\t\t\t\t\t\t\t\t\t" << "eb " << endl;
	for (int i = 0; i < 4; i++) {
		c1[i] = new TCanvas(Form("c1_%d", i), Form("c1_%d", i), 5000, 2000);
		Fit_plus_systematic_errors(i);
		file3 << a_pp_plus_sys[i] << "\t\t\t\t\t\t\t\t\t\t" << b_pp_plus_sys[i] << endl;
		file4 << a_pp_plus_par_err[i] << "\t\t\t\t\t\t\t\t\t\t" << b_pp_plus_par_err[i] << endl;

	}
	file3.close();
	file4.close();

	ofstream file5("C:/root/fitting_parameters_minus_sys.txt");
	file5 << "a " << "\t\t\t\t\t\t\t\t\t\t" << "b " << endl;
	ofstream file6("C:/root/fitting_parameters_minus_sys_errors.txt");
	file6 << "ea " << "\t\t\t\t\t\t\t\t\t\t" << "eb " << endl;
	for (int i = 0; i < 4; i++) {

		c2[i] = new TCanvas(Form("c2_%d", i), Form("c2_%d", i), 5000, 2000);
		Fit_minus_systematic_errors(i);
		file5 << a_pp_minus_sys[i] << "\t\t\t\t\t\t\t\t\t\t" << b_pp_minus_sys[i] << endl;
		file6 << a_pp_minus_par_err[i] << "\t\t\t\t\t\t\t\t\t\t" << b_pp_minus_par_err[i] << endl;

	}

	file5.close();
	file6.close();
	
}

	