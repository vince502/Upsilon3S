#pragma once
#include "TMath.h"

#define dat std::map<  int, double  >

dat AIC_statistic(double Nll1, int dof1, double Nll2, int dof2){
	double AIC_1 = 2*Nll1 + 2*dof1;
	double AIC_2 = 2*Nll2 + 2*dof2;
	double minAIC =min(AIC_1, AIC_2);
	double B[2];
	B[0] = TMath::Exp( ( minAIC - AIC_1 ) / 2);
	B[1] = TMath::Exp( ( minAIC - AIC_2 ) / 2);
	double sumB = B[0] + B[1];
	double p[2];
	p[0] = B[0]/sumB;
	p[1] = B[1]/sumB;
	return dat{{0,p[0]}, {1,p[1]}};
};

dat AIC_statistic(double Nll1, int dof1, double Nll2, int dof2, double Nll3, int dof3){
	double AIC_1 = 2*Nll1 + 2*dof1;
	double AIC_2 = 2*Nll2 + 2*dof2;
	double AIC_3 = 2*Nll3 + 2*dof3;
	double minAIC =min(min(AIC_1, AIC_2),AIC_3);
	double B[3];
	B[0] = TMath::Exp( ( minAIC - AIC_1 ) / 2);
	B[1] = TMath::Exp( ( minAIC - AIC_2 ) / 2);
	B[2] = TMath::Exp( ( minAIC - AIC_3 ) / 2);
	double sumB = B[0] + B[1] +B[2];
	double p[3];
	p[0] = B[0]/sumB;
	p[1] = B[1]/sumB;
	p[2] = B[2]/sumB;
	return dat{{0,p[0]}, {1,p[1]}, {2,p[2]}};
};
