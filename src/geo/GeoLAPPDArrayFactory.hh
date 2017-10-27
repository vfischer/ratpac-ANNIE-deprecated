#ifndef __RAT_GeoLAPPDArrayFactory__
#define __RAT_GeoLAPPDArrayFactory__

#include <RAT/GeoLAPPDFactoryBase.hh>

namespace RAT {
 class GeoLAPPDArrayFactory : public GeoLAPPDFactoryBase {
 public:
   GeoLAPPDArrayFactory() : GeoLAPPDFactoryBase("lappdarray") {};
   virtual G4VPhysicalVolume *Construct(DBLinkPtr table);
 };
  
} // namespace RAT

#endif
