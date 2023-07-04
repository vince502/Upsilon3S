void RootCondorScript()
{
  ofstream submit_macro("submit.sh");

    TString name = Form("rundoConstFit2.sh");
    ofstream submit_file(name);

    submit_file << "Executable   = /software/ROOT/ROOT-v6.24.06/root-6.24.06-install/bin/root " << endl;
    submit_file << "Arguments    = \"-l -b -q '/home/vince402/Upsilon3S/doConstraintFit_NOM_v2.cxx()'\""  << endl;
    submit_file << "Initialdir   = /home/vince402/Upsilon3S/condortest" << endl;
    submit_file << "#Log          = example_.log" << endl;
    submit_file << "#Error        = example_.err" << endl;
    submit_file << "#Output       = example_.out" << endl;
    submit_file << "#Input        = WHEN_YOU_HAVE_INPUT_FILES" << endl;
    submit_file << "Universe     = vanilla" << endl;
    submit_file << "GetEnv       = True" << endl;
    // 여기에 필요한 core 수 작성!
    submit_file << "Request_cpus = 40" << endl;
    submit_file << "Request_memory = 2000" << endl;
    submit_file << "Notification = Always" << endl;
    // 여기는 최신 노드 컴퓨터들!
    submit_file << "#Requirements = \(machine != \"kunpl-node09\" || machine != \"kunpl-node10\" || machine != \"kunpl-node11\"\)" << endl;
    submit_file << "#Notify_user  = wjd1004ip@naver.com" << endl;
    submit_file << "Queue" << endl;

    submit_macro << "condor_submit " << name << endl;
}
