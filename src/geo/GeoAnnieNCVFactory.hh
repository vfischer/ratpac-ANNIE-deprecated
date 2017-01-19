#ifndef __RAT_GeoAnnieNCVFactory__
#define __RAT_GeoAnnieNCVFactory__

#include <GeoFactory.hh>

#include <G4VPhysicalVolume.hh>
#include <G4VisAttributes.hh>
#include <G4OpticalSurface.hh>

namespace RAT {
    class GeoAnnieNCVFactory : public GeoFactory {
        public:
            GeoAnnieNCVFactory() : GeoFactory("annieNCV") {};
            virtual G4VPhysicalVolume *Construct(DBLinkPtr table);
        protected:
            G4VisAttributes *GetVisAttributes(DBLinkPtr table);
            G4OpticalSurface *GetSurface(std::string surface_name);
    };
  
} // namespace RAT

#endif
