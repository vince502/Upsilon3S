#pragma once
#include "CMS_lumi_square.h"
//#include "CMS_lumi_v2mass.h"
#include <iostream>

void CMS_lumi_square( TPad* pad, int iPeriod=101, int iPosX=10, int extra = 0, bool writeOneLine = false )
{            
	if( extra < 0 ) writeExtraText = false;
	if( extra >= 0 ) writeExtraText = true;

	TString extraText  = ( extra == 0 ) ? extraText1 : (extra == 1) ? extraText2 : extraText3;
	bool outOfFrame    = false;
	if( iPosX/10==0 ) 
	{
		outOfFrame = true;
	}
	int alignY_=3;
	int alignX_=2;
	if( iPosX/10==0 ) alignX_=1;
	if( iPosX==0    ) alignX_=1;
	if( iPosX==0    ) alignY_=1;
	if( iPosX/10==1 ) alignX_=1;
	if( iPosX/10==2 ) alignX_=2;
	if( iPosX/10==3 ) alignX_=3;
	//if( iPosX == 0  ) relPosX = 0.12;
	int align_ = 10*alignX_ + alignY_;
	
	float H = pad->GetWh();
	float W = pad->GetWw();
	float l = pad->GetLeftMargin();
	float t = pad->GetTopMargin() * 0.93;
	float r = pad->GetRightMargin();
	float b = pad->GetBottomMargin();
	//  float e = 0.025;
	
	pad->cd();
	
	TString lumiText;
	if( iPeriod==1 )
	{
		lumiText += "pp ";
		lumiText += lumi_pp502TeV;
		lumiText += " (5.02 TeV)";
	}
	else if( iPeriod==2 )
	{
		lumiText += "PbPb ";
		lumiText += lumi_PbPb502TeV;
		lumiText += " (5.02 TeV)";
	}
	else if( iPeriod==3 )
	{
		lumiText += "PbPb ";
		lumiText += lumi_PbPb502TeV_blind;
		lumiText += " (5.02 TeV)";
	}
	else if( iPeriod==31 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_quarter;
	  lumiText += " (5.02 TeV)";
	}
	else if( iPeriod==4 )
	{
	  lumiText += "pPb ";
	  lumiText += lumi_pPb502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==101 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_blind;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==102 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_quarter;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==103 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==1030 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_projected_0;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==1031 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_projected_1;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==1032 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_projected_2;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==1033 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_projected_3;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==1034 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_projected_4;
	  lumiText += ", pp ";
	  lumiText += lumi_pp502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==10001 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV_blind;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==10001 )
	{
	  lumiText += "PbPb ";
	  lumiText += lumi_PbPb502TeV;
	  lumiText += " (5.02 TeV)";
	}
	else if ( iPeriod==0 )
	{
	  lumiText += lumi_sqrtS;
	}
	
	std::cout << lumiText << endl;
	
	TLatex latex;
	latex.SetNDC();
	latex.SetTextAngle(0);
	latex.SetTextColor(kBlack);    
	
	float extraTextSize = extraOverCmsTextSize*cmsTextSize;
	
	latex.SetTextFont(42);
	latex.SetTextAlign(31); 
	latex.SetTextSize(lumiTextSize*t);    
	latex.DrawLatex(1-r,1-t+lumiTextOffset*t-0.008,lumiText);
	
	if( outOfFrame )
	{
	  latex.SetTextFont(cmsTextFont);
	  latex.SetTextAlign(11); 
	  latex.SetTextSize(cmsTextSize*t);    
	  latex.DrawLatex(l,1-t+lumiTextOffset*t +0.002,cmsText);
	}
	
	pad->cd();
	
	float posX_=0;
	if( iPosX%10<=1 )
	{
	  posX_ =   l + relPosX*(1-l-r);
	}
	else if( iPosX%10==2 )
	{
	  posX_ =  l + 0.5*(1-l-r);
	}
	else if( iPosX%10==3 )
	{
	  posX_ =  1-r - relPosX*(1-l-r);
	}
	float posY_ = 1-t - relPosY*(1-t-b);
	if( !outOfFrame )
	{
	  if( drawLogo )
	  {
	    posX_ =   l + 0.045*(1-l-r)*W/H;
	    posY_ = 1-t - 0.045*(1-t-b);
	    float xl_0 = posX_;
	    float yl_0 = posY_ - 0.15;
	    float xl_1 = posX_ + 0.15*H/W;
	    float yl_1 = posY_;
	    TASImage* CMS_logo = new TASImage("CMS-BW-label.png");
	    TPad* pad_logo = new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
	    pad_logo->Draw();
	    pad_logo->cd();
	    CMS_logo->Draw("X");
	    pad_logo->Modified();
	    pad->cd();
	  }
	  else
	  {
		if( writeOneLine )
		{
	    	latex.SetTextFont(extraTextFont);
	    	latex.SetTextAlign(align_);
	    	latex.SetTextSize(extraTextSize*t);
	    	latex.DrawLatex(posX_ - 0.01, posY_ - 0.02, extraText);
	    	latex.SetTextFont(cmsTextFont);
	    	latex.SetTextSize(cmsTextSize*t);
	    	latex.SetTextAlign(align_);
	    	posX_ -= 0.01; posY_-=0.02; // KYO
	    	latex.DrawLatex(posX_ - ( (extraText.Sizeof() -1) * cmsTextSize*t *  0.5  *cmsTextSize ), posY_, cmsText);
		}
		else
		{
	    	latex.SetTextFont(cmsTextFont);
	    	latex.SetTextSize(cmsTextSize*t);
	    	latex.SetTextAlign(align_);
	    	posX_ -= 0.01; posY_-=0.02; // KYO
	    	latex.DrawLatex(posX_, posY_, cmsText);
	    	if( writeExtraText ) 
	    	{
	    	  latex.SetTextFont(extraTextFont);
	    	  latex.SetTextAlign(align_);
	    	  latex.SetTextSize(extraTextSize*t);
	    	  latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText);
	    	}
		}
	  }
	}
	else if( writeExtraText )
	{
	  if( iPosX==0) 
	  {
	    posX_ =   l +  relPosX*(1-l-r);
	    posY_ =   1-t+lumiTextOffset*t;
	  }
	  latex.SetTextFont(extraTextFont);
	  latex.SetTextSize(extraTextSize*t);
	  latex.SetTextAlign(align_);
	  latex.DrawLatex(posX_, posY_, extraText);      
	}
	return;
}
