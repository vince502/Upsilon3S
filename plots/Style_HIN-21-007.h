#pragma once

double RAACENTYUP = 1.3;
double RAACENTYDOWN = 0.0;

double RAAPTYUP = 1.3;
double RAAPTYDOWN = 0.0;

double DRCENTYUP = 1.6;
double DRCENTYDOWN = 0.0;

double DRPTYUP = 1.6;
double DRPTYDOWN = 0.0;

double kGLBp2scale = 1.;
double kGLBMarkerSize = 1.4;
double kGLBFillAlpha = 0.25;
unsigned int kGLBLineWidth = 1;
unsigned int kGLBLineStyle = 1;


struct GraphSetAttr{
	unsigned int kLineColor		=0;	
	unsigned int kLineWidth		=0;
	unsigned int kLineStyle		=0;
	unsigned int kMarkerColor	=0;
	double 	     kMarkerSize	=0;
	unsigned int kMarkerStyle	=0;

	unsigned int kSystLineColor	=0;
	unsigned int kSystLineWidth	=0;
	unsigned int kSystLineStyle	=0;
	unsigned int kFillColor		=0;
	double		 kFillAlpha		=0;
};

///////////////////////Current Analysis, RAA/////////////////////////
GraphSetAttr kCA2SCENT{ 
	kBlue, kGLBLineWidth, 	kGLBLineStyle, kBlue+2, kGLBMarkerSize, kFullSquare,
	kBlue, kGLBLineWidth, 0				   			, kAzure-3 	, kGLBFillAlpha
};
GraphSetAttr kCA3SCENT{ 
	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kGreen+3, kGLBMarkerSize, kFullSquare,
	kGreen+2, kGLBLineWidth, 0				   			, kTeal+5 	, kGLBFillAlpha
};

GraphSetAttr kCA2SPT = kCA2SCENT; 
//GraphSetAttr kCA2SPT{ 
//	kBlue, kGLBLineWidth, 	kGLBLineStyle, kBlue+2, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kAzure-3 	, kGLBFillAlpha
//};
GraphSetAttr kCA3SPT = kCA3SCENT; 
//GraphSetAttr kCA3SPT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kTeal+5, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
///////////////////////Current Analysis, Double Ratio/////////////////////////
GraphSetAttr kCADRCENT = kCA3SCENT;
//GraphSetAttr kCADRCENT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
GraphSetAttr kCADRPT = kCA3SCENT;
//GraphSetAttr kCADRPT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};

//////////////////////////////////////////////////////////////////
///////////////////////Past Analysis, RAA/////////////////////////
GraphSetAttr kPA1SCENT{ 
	kRed+2, kGLBLineWidth, 	kGLBLineStyle, kRed -3, kGLBMarkerSize, kFullCircle,
	kRed+2, kGLBLineWidth, 0				   			, kRed-3  	, kGLBFillAlpha - 0.1
};
GraphSetAttr kPA2SCENT{ 
	kViolet-5, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullCircle,
	kViolet-3, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
};
GraphSetAttr kPA1SPT = kPA1SCENT;
//GraphSetAttr kPA1SPT{ 
//	kViolet-5, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullCircle,
//	kViolet-3, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
GraphSetAttr kPA2SPT = kPA2SCENT;
//GraphSetAttr kPA2SPT{ 
//	kViolet-5, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullCircle,
//	kViolet-3, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
///////////////////////Past Analysis, UpperLimit/////////////////////////
GraphSetAttr kPA3SCENT{ 
};
GraphSetAttr kPA3SPT{ 
};

std::map<string, GraphSetAttr> map_GraphStyle ={
	{"CA2SCENT", kCA2SCENT},
	{"CA2SINT", kCA2SCENT},
	{"CA3SCENT", kCA3SCENT},
	{"CA3SINT", kCA3SCENT},
	{"CA3SPT", kCA3SPT},
	{"CA2SPT", kCA2SPT},
	{"CADRPT", kCADRPT},
	{"CADRCENT", kCADRCENT},
	{"CADRINT", kCADRCENT},
	{"PA1SCENT", kPA1SCENT},
	{"PA2SCENT", kPA2SCENT},
	{"PA3SCENT", kPA3SCENT},
	{"PA1SINT", kPA1SCENT},
	{"PA2SINT", kPA2SCENT},
	{"PA3SINT", kPA3SCENT},
	{"PA3SPT", kPA3SPT},
	{"PA2SPT", kPA2SPT},
	{"PA1SPT", kPA1SPT},
};

