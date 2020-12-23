#!/bin/bash
root -l -b -q 'extractRooDataSet.C+(false, false, false, 2, "OniaFlowSkim_L1DoubleMuOpen50100Trig_DBPD_isMC0_HFNom_190813.root")'
root -l -b -q 'extractRooDataSet.C+(false, false, false, 2, "OniaFlowSkim_L1DoubleMuOpen50100Trig_DBPeriPD_isMC0_HFNom_190813.root")'
root -l -b -q 'extractRooDataSet.C+(false, false, false, 2, "OniaFlowSkim_L1DoubleMuOpenOS40100Trig_DBPD_isMC0_HFNom_190813.root")'
