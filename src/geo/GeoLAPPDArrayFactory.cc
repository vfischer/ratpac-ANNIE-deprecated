#include <RAT/GeoLAPPDArrayFactory.hh>
#include <vector>
#include <RAT/Log.hh>

using namespace std;

namespace RAT {

  G4VPhysicalVolume *GeoLAPPDArrayFactory::Construct(DBLinkPtr table){
    info << "GeoLAPPDArrayFactory: Constructing volume " + table->GetIndex()  
         << newline;
    // Read LAPPD positions                   
    string pos_table_name = table->GetS("pos_table");
    DBLinkPtr lpos_table = DB::Get()->GetLink(pos_table_name);
    const vector<double> &lappd_x = lpos_table->GetDArray("x");
    const vector<double> &lappd_y = lpos_table->GetDArray("y");
    const vector<double> &lappd_z = lpos_table->GetDArray("z");
    return ConstructLAPPDs(table, lappd_x, lappd_y, lappd_z);
  }
    
} // namespace RAT
