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
double kGLBMarkerSize = 1.6;
double kGLBFillAlpha = 0.35;
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
	void operator++(){
		//kLineColor = kLineColor+1;
		//kSystLineColor =kSystLineColor+1;
		//kMarkerColor = kMarkerColor+1;
		//kFillColor = kFillColor+1;
//		++kLineColor;
//		++kSystLineColor;
//		++kMarkerColor;
		++kFillColor;
	};
};


///////////////////////Current Analysis, RAA/////////////////////////
GraphSetAttr kCA2SCENT{ 
	kBlue, kGLBLineWidth, 	kGLBLineStyle, kBlue+1, kGLBMarkerSize, kFullSquare,
	kBlue, kGLBLineWidth, 0				   			, kAzure-6 	, kGLBFillAlpha
};
GraphSetAttr kCA3SCENT{ 
	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kGreen+2, kGLBMarkerSize * 1.6 , kFullDiamond,
	kGreen+2, kGLBLineWidth, 0				   			, kTeal+9 	, kGLBFillAlpha
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

///////////////////////Auxiliary Pallete, RAA/////////////////////////
GraphSetAttr kAA1SCENT{ 
	kPink+8, kGLBLineWidth, 	kGLBLineStyle, kPink+7, kGLBMarkerSize, kFullTriangleUp,
	kPink+8, kGLBLineWidth, 0				   			, kPink+7  	, kGLBFillAlpha - 0.1
};
GraphSetAttr kAA2SCENT{ 
	kMagenta+1, kGLBLineWidth, 	kGLBLineStyle, kMagenta+2, kGLBMarkerSize, kFullTriangleUp,
	kMagenta+1, kGLBLineWidth, 0				   			, kMagenta-3 	, kGLBFillAlpha
};
GraphSetAttr kAA3SCENT{ 
	kCyan-6, kGLBLineWidth, 	kGLBLineStyle, kCyan-7, kGLBMarkerSize, kFullTriangleUp,
	kCyan-6, kGLBLineWidth, 0				   			, kTeal-8 	, kGLBFillAlpha
};

GraphSetAttr kAA2SPT = kAA2SCENT; 
//GraphSetAttr kCA2SPT{ 
//	kBlue, kGLBLineWidth, 	kGLBLineStyle, kBlue+2, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kAzure-3 	, kGLBFillAlpha
//};
GraphSetAttr kAA3SPT = kAA3SCENT; 
//GraphSetAttr kCA3SPT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kTeal+5, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
///////////////////////Auxiliary Pallete, Double Ratio/////////////////////////
GraphSetAttr kAADRCENT = kAA3SCENT;
//GraphSetAttr kCADRCENT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
GraphSetAttr kAADRPT = kAA3SCENT;
//GraphSetAttr kCADRPT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
GraphSetAttr kAA1SPT = kAA1SCENT;
GraphSetAttr kAA1SINT = kAA1SCENT;
///////////////////////Auxiliary Pallete2, RAA/////////////////////////
GraphSetAttr kA2A1SCENT{ 
	kOrange+7, kGLBLineWidth, 	kGLBLineStyle, kOrange +8, kGLBMarkerSize, kFullStar,
	kOrange+7, kGLBLineWidth, 0				   			, kOrange +8  	, kGLBFillAlpha - 0.1
};
GraphSetAttr kA2A2SCENT{ 
	kAzure-9, kGLBLineWidth, 	kGLBLineStyle, kAzure-8, kGLBMarkerSize, kFullStar,
	kAzure-9, kGLBLineWidth, 0				   			, kAzure+10 	, kGLBFillAlpha
};
GraphSetAttr kA2A3SCENT{ 
	kYellow-3, kGLBLineWidth, 	kGLBLineStyle, kYellow-7, kGLBMarkerSize, kFullStar,
	kYellow-3, kGLBLineWidth, 0				   			, kOrange-4 	, kGLBFillAlpha
};

GraphSetAttr kA2A2SPT = kA2A2SCENT; 
//GraphSetAttr kCA2SPT{ 
//	kBlue, kGLBLineWidth, 	kGLBLineStyle, kBlue+2, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kAzure-3 	, kGLBFillAlpha
//};
GraphSetAttr kA2A3SPT = kA2A3SCENT; 
//GraphSetAttr kCA3SPT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kTeal+5, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
///////////////////////Auxiliary Pallete2, Double Ratio/////////////////////////
GraphSetAttr kA2ADRCENT = kA2A3SCENT;
//GraphSetAttr kCADRCENT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
GraphSetAttr kA2ADRPT = kA2A3SCENT;
//GraphSetAttr kCADRPT{ 
//	kGreen+2, kGLBLineWidth, 	kGLBLineStyle, kViolet+1, kGLBMarkerSize, kFullSquare,
//	0		, 0			, 0				   			, kViolet+1 	, kGLBFillAlpha
//};
GraphSetAttr kA2A1SPT = kA2A1SCENT;
GraphSetAttr kA2A1SINT = kA2A1SCENT;

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

	{"AA1SCENT", kAA1SCENT},
	{"AA1SPT", kAA1SPT},
	{"AA1SINT", kAA1SCENT},
	{"AA2SCENT", kAA2SCENT},
	{"AA2SINT", kAA2SCENT},
	{"AA3SCENT", kAA3SCENT},
	{"AA3SINT", kAA3SCENT},
	{"AA3SPT", kAA3SPT},
	{"AA2SPT", kAA2SPT},
	{"AADRPT", kAADRPT},
	{"AADRCENT", kAADRCENT},
	{"AADRINT", kAADRCENT},

	{"A2A1SCENT", kA2A1SCENT},
	{"A2A1SPT", kA2A1SPT},
	{"A2A1SINT", kA2A1SCENT},
	{"A2A2SCENT", kA2A2SCENT},
	{"A2A2SINT", kA2A2SCENT},
	{"A2A3SCENT", kA2A3SCENT},
	{"A2A3SINT", kA2A3SCENT},
	{"A2A3SPT", kA2A3SPT},
	{"A2A2SPT", kA2A2SPT},
	{"A2ADRPT", kA2ADRPT},
	{"A2ADRCENT", kA2ADRCENT},
	{"A2ADRINT", kA2ADRCENT},
};

