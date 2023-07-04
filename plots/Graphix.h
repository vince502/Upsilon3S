#ifndef _GRAPHIX_
#define _GRAPHIX_

enum histOp{
	kDiv = 0,
	kMult = 1,
	kAdd = 2,
	kSub = 3,
	kOther = 4,
};

template <typename A>
class Graphix{
	public : 
		Graphix(){};
		Graphix(A* obj){
			theObject = new A(*obj);
		};
		Graphix(A& obj){
			theObject = obj;
		};
		~Graphix(){};
		A* getObject(){
			return theObject;
		};
		A* getDerivedObject(){
			return derivedObject;
		};
		void shiftBins(double offset, bool isPercent = false){
		    if (std::is_same<A, TGraphAsymmErrors>::value){
				for( auto idx : ROOT::TSeqI(theObject->GetN()) ){
					if(!isPercent) theObject->SetPointX(idx, theObject->GetPointX(idx) + offset);
					if(isPercent) theObject->SetPointX(idx, theObject->GetPointX(idx) * ( 1.0 + 0.01 * offset));
				}
			}
		};
		void operator/(Graphix<TGraphAsymmErrors> theDen){
			if( std::is_same<A, TGraphAsymmErrors>::value){
				derivedObject= new TGraphAsymmErrors();
//				else derivedObject->Clear();
				if(theDen.getObject()->GetN() != theObject->GetN()){
//					std::err << "mismatch in number of points\n";
					return;
				}
				for( auto idx : ROOT::TSeqI(theDen.getObject()->GetN()) ){
					derivedObject->AddPoint(theObject->GetPointX(idx), theObject->GetPointY(idx)/ theDen.getObject()->GetPointY(idx));
				//	double EYh = TMath::Sqrt( TMath::Power( theObject->GetErrorYhigh(idx) / theDen.getObject()->GetPointY(idx), 2) + TMath::Power( (theDen.getObject()->GetErrorYhigh(idx) * theObject->GetPointY(idx) ) / TMath::Power(theDen.getObject()->GetPointY(idx),2), 2));
				//	double EYl = TMath::Sqrt( TMath::Power( theObject->GetErrorYlow(idx) / theDen.getObject()->GetPointY(idx), 2) + TMath::Power( (theDen.getObject()->GetErrorYlow(idx) * theObject->GetPointY(idx) ) / TMath::Power(theDen.getObject()->GetPointY(idx),2), 2));
					double EYh = theObject->GetErrorYhigh(idx) * ( theDen.getObject()->GetPointY(idx) / TMath::Power( theObject->GetPointY(idx), 2));
					double EYl = theObject->GetErrorYlow(idx) * ( theDen.getObject()->GetPointY(idx) / TMath::Power( theObject->GetPointY(idx), 2));
					derivedObject->SetPointError(idx, theObject->GetErrorXlow(idx), theObject->GetErrorXhigh(idx),  EYl, EYh);
				}
				isArithmatic = histOp::kDiv;
			}
//			else std::cerr << "wrong type of " << typeid(theObject) << std::endl;
		};

	protected :
		virtual void checkType(){};
	private :
		A* theObject;
		A* derivedObject;
		bool isDerived;
		int isArithmatic;
};

template <typename A>
void globalOffSetY(double absVal, A* obj){
	if( std::is_same<A, TGraphAsymmErrors>::value){
		for( auto idx : ROOT::TSeqI(obj->GetN() )){
			obj->SetPointY(idx, obj->GetPointY(idx) + absVal);
		}
	}
};

template <typename A>
void globalOffSetX(double absVal, A* obj){
	if( std::is_same<A, TGraphAsymmErrors>::value){
		for( auto idx : ROOT::TSeqI(obj->GetN() )){
			obj->SetPointX(idx, obj->GetPointX(idx) + absVal);
		}
	}
};



#endif
