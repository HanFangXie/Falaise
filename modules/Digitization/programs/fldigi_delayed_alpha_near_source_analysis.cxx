//fldigi_delayed_alpha_near_source_analysis.cxx
// Standard libraries :
#include <iostream>
#include <fstream>

// - Bayeux/datatools:
#include <datatools/io_factory.h>

// Falaise:
#include <falaise/falaise.h>

// Third part : 
// Root : 
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"

int main(int  argc_ , char ** argv_)
{  
  FALAISE_INIT();
  int error_code = EXIT_SUCCESS;
  datatools::logger::priority logging = datatools::logger::PRIO_FATAL;

  // Process
  try {  
    std::clog << "Little test program for analysis of alpha delayed number of geiger cells hit !" << std::endl;
    
    std::string input_filename = "${FALAISE_DIGITIZATION_DIR}/programs/validation.root";
    std::string output_filename = "${FALAISE_DIGITIZATION_DIR}/programs/analysis.root";
    datatools::fetch_path_with_env(input_filename);
    datatools::fetch_path_with_env(output_filename);

    // Creation and openning of ROOT file , and get the infile tree :
    TFile * input_file = new TFile(input_filename.c_str() , "READ");
    TFile * output_file = new TFile(output_filename.c_str(), "RECREATE");

    TTree * input_gg_cells_tree = (TTree *)input_file->Get("GGCellsTree");
    TTree * input_delayed_cells_tree = (TTree *)input_file->Get("DelayedCellsTree");
    TTree * output_tree = new TTree("TrackerTreeAnalysis", "Alpha track analysis");

    Int_t event_id    = 0;
    std::vector<Int_t> * vect_number_of_gg_cells = 0;
    std::vector<Int_t> * vect_number_of_delayed_gg_cells = 0;
    std::vector<Int_t> * vect_number_of_not_delayed_gg_cells = 0;
    std::vector<Int_t> * vect_delayed_time_shift = 0;

    std::vector<Int_t> * vect_hit_id = 0;
    std::vector<Double_t> * vect_time_start = 0;
    std::vector<Double_t> * vect_x_start = 0;
    std::vector<Double_t> * vect_y_start = 0;
    std::vector<Double_t> * vect_z_start = 0;
    std::vector<Double_t> * vect_x_stop = 0;
    std::vector<Double_t> * vect_y_stop = 0;
    std::vector<Double_t> * vect_z_stop = 0;
    std::vector<Double_t> * vect_px_start = 0;
    std::vector<Double_t> * vect_py_start = 0;
    std::vector<Double_t> * vect_pz_start = 0;

    // Input tree Set all Branch Address :
    input_delayed_cells_tree->SetBranchAddress("event_id",   &event_id);
    input_delayed_cells_tree->SetBranchAddress("number_of_gg_cells", &vect_number_of_gg_cells);
    input_delayed_cells_tree->SetBranchAddress("number_of_delayed_gg_cells", &vect_number_of_delayed_gg_cells);
    input_delayed_cells_tree->SetBranchAddress("number_of_not_delayed_gg_cells", &vect_number_of_not_delayed_gg_cells);  
    input_delayed_cells_tree->SetBranchAddress("delayed_time_shift", &vect_delayed_time_shift);
    input_gg_cells_tree->SetBranchAddress("event_id",        &event_id);
    input_gg_cells_tree->SetBranchAddress("hit_id_vector",   &vect_hit_id);
    input_gg_cells_tree->SetBranchAddress("time_start_vector", &vect_time_start);
    input_gg_cells_tree->SetBranchAddress("x_start_vector",  &vect_x_start);
    input_gg_cells_tree->SetBranchAddress("y_start_vector",  &vect_y_start);
    input_gg_cells_tree->SetBranchAddress("z_start_vector",  &vect_z_start);
    input_gg_cells_tree->SetBranchAddress("x_stop_vector",   &vect_x_stop);
    input_gg_cells_tree->SetBranchAddress("y_stop_vector",   &vect_y_stop);
    input_gg_cells_tree->SetBranchAddress("z_stop_vector",   &vect_z_stop);
    input_gg_cells_tree->SetBranchAddress("px_start_vector", &vect_px_start);
    input_gg_cells_tree->SetBranchAddress("py_start_vector", &vect_py_start);
    input_gg_cells_tree->SetBranchAddress("pz_start_vector", &vect_pz_start);

    TH2F * histo_delayed_geiger_cells_delayed_time = new TH2F( "Delayed Geiger Cells" , "Delayed GG cells" , 60 , 0. , 60., 20, 0., 20.) ;

    // Begining of the analysis
    std::clog << "Number of Entries in TTree = " <<  input_delayed_cells_tree->GetEntries() << std::endl; 
    Int_t n_entry = input_delayed_cells_tree->GetEntries();
    
    
    const int geiger_threshold = 2; // number of geiger cells threshold     

    for( int i = 0 ; i < n_entry; i++ )
      {
    	input_delayed_cells_tree->GetEntry(i) ;
     
    	std::clog << "Event ID  = " << event_id << std::endl;
	size_t vector_size = vect_number_of_gg_cells->size();
	for (size_t j = 0; j < vector_size; j++)
	  {
	    int delayed_time_shift = vect_delayed_time_shift->at(j);
	    int number_of_gg_cells = vect_number_of_gg_cells->at(j);
	    int number_of_delayed_gg_cells = vect_number_of_delayed_gg_cells->at(j);
	    int number_of_not_delayed_gg_cells = vect_number_of_not_delayed_gg_cells->at(j);
	    histo_delayed_geiger_cells_delayed_time->Fill(delayed_time_shift, number_of_delayed_gg_cells);
	    // std::clog << "Delayed time shift              = " << delayed_time_shift << std::endl;
	    // std::clog << "Number of gg cells             = " << number_of_gg_cells << std::endl;
	    // std::clog << "Number of delayed gg cells     = " << number_of_delayed_gg_cells << std::endl;
	    // std::clog << "Number of not delayed gg cells = " << number_of_not_delayed_gg_cells << std::endl << std::endl;
	  }
      }
    histo_delayed_geiger_cells_delayed_time->Write();

    //output_tree->Fill();
    output_file->Write();
    output_file->Close();
   
    std::clog << "The end." << std::endl;
  }
  
  
  catch (std::exception & error) {
    DT_LOG_FATAL(logging, error.what());
    error_code = EXIT_FAILURE;
  }

  catch (...) {
    DT_LOG_FATAL(logging, "Unexpected error!");
    error_code = EXIT_FAILURE;
  }

  FALAISE_FINI();
  return error_code;
}


// for ggcells tree :
// double px_tot = 0;
// double py_tot = 0;
// double pz_tot = 0;
// double p_tot = 0;
// for (int j = 0; j < vect_time_start->size(); j++)
//   {
//     Int_t hit_id      = vect_hit_id->at(j); 
//     Double_t time_start = vect_time_start->at(j);
//     Double_t x_start  = vect_x_start->at(j);
//     Double_t y_start  = vect_y_start->at(j);
//     Double_t z_start  = vect_z_start->at(j);
//     Double_t x_stop   = vect_x_stop->at(j);
//     Double_t y_stop   = vect_y_stop->at(j);
//     Double_t z_stop   = vect_z_stop->at(j);
//     Double_t px_start = vect_px_start->at(j);
//     Double_t py_start = vect_py_start->at(j);
//     Double_t pz_start = vect_pz_start->at(j);

//     // std::clog << "Hit id = " << hit_id << std::endl;
//     // std::clog << "Time start = " << time_start << std::endl;
//     // std::clog << "XYZ start = " << x_start << " , " <<  y_start << " , " << z_start << std::endl;
//     // std::clog << "XYZ stop = " << x_stop << " , " <<  y_stop << " , " << z_stop << std::endl;
//     // std::clog << "PxPyPz start = " << px_start << " , " <<  py_start << " , " << pz_start << std::endl << std::endl;
//     px_tot += px_start ;
//     py_tot += py_start;
//     pz_tot += pz_start;
//   }
// p_tot = std::sqrt(std::pow(px_tot, 2) + std::pow(py_tot, 2) + std::pow(pz_tot, 2));
