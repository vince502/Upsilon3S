#include "simple_DS.h"

void create_simple_DS ()
{
gInterpreter->GenerateDictionary("std::map<ana_bins,string>", "map");
	DB_base a;
	ana_bins ab = ana_bm["2c"][0];
	a.insert_bin(ab);
}
