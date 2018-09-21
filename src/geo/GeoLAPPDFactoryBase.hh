#ifndef __RAT_GeoLAPPDFactoryBase__
#define __RAT_GeoLAPPDFactoryBase__

#include <RAT/GeoFactory.hh>
#include <RAT/DS/PMTInfo.hh>
#include <RAT/DS/LAPPDInfo.hh>

namespace RAT {
  class GeoLAPPDFactoryBase : public GeoFactory {
  public:
    GeoLAPPDFactoryBase(const std::string &name) : GeoFactory(name) { };
    static const DS::LAPPDInfo& GetLAPPDInfo() { return lappdinfo; }
  protected:
    virtual G4VPhysicalVolume *ConstructLAPPDs(DBLinkPtr table, std::vector<double> lappd_x, std::vector<double> lappd_y, std::vector<double> lappd_z);
    
    static DS::LAPPDInfo lappdinfo; ///keeps track of all the LAPPDs built into the geometry
  };
  
} // namespace RAT

#endif


