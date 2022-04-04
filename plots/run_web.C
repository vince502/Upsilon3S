#include "analysis_plots_combine.cxx"

auto serv = new THttpServer("http:8081");
void run_web(){
	analysis_plots_combine();
}


