#ifndef __RAT_GeoLAPPDParser__
#define __RAT_GeoLAPPDParser__

#include <G4RotationMatrix.hh>
#include <RAT/LAPPDConstruction.hh>
#include <RAT/DB.hh>
#include <vector>



namespace RAT {

  /** Helper class which reads the attributes stored in a GEO table
   *  describing LAPPD placement and construction.  Creates a LAPPD
   *  "sensitive detector" if useSD is true.  Only set to true if this
   *  GeoLAPPDParser will be used to construct real LAPPDs. */
  class GeoLAPPDParser {
  public:
    GeoLAPPDParser(DBLinkPtr table, bool useSD=false);
    ~GeoLAPPDParser() { delete fConstruction; };

    /** Returns total number of LAPPDs described by the RATDB table. */
    int GetLAPPDCount() const { return fDir.size(); };

    /** Fills lappd_x, lappd_y and lappd_z with LAPPD positions.
     *  By convention, this is the location of point in center of plane
     *  cutting through the LAPPD equator. */
    const std::vector<G4ThreeVector> &GetLAPPDLocations() const {
      return fPos;
    };

    
    /** Return LAPPD orientation vectors.
     *  Gives direction of LAPPD frame +z axis (face of LAPPD).  Vectors are
     *  guaranteed to be normalized. */
    const std::vector<G4ThreeVector> &GetLAPPDDirections() const {
      return fDir;
    };

    /** Returns the rotation matrix required to orient LAPPD of index i
     *  in a G4PVPlacement.  By GEANT4 convention, this is a passive rotation.
     *  Use the invert() method to convert it to an active rotation if you
     *  want to apply it to a vector.*/
    G4RotationMatrix GetLAPPDRotation(int i) const;

    /** Returns LAPPD parameter structure describing LAPPD geometry */
    LAPPDConstructionParams GetLAPPDParams() const { return fParam; };

    /** Returns pointer to LAPPDConstruction object which can be used
     *  to make LAPPDs.  GeoLAPPDParser owns this object, so do not delete! */
    LAPPDConstruction *GetLAPPDConstruction() { return fConstruction; };

  protected:
    DBLinkPtr fTable;
    std::vector<G4ThreeVector> fPos;
    std::vector<G4ThreeVector> fDir;
    LAPPDConstructionParams fParam;
    LAPPDConstruction *fConstruction;
  };


} // namespace RAT

#endif
