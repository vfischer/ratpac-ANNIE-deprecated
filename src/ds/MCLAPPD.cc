#include <RAT/DS/MCLAPPD.hh>

ClassImp(RAT::DS::MCLAPPD)

namespace RAT {
  namespace DS {

Float_t MCLAPPD::GetCharge() const {
  Float_t charge = 0.0;
  for (unsigned int i=0; i < photon.size(); i++)
    charge += photon[i].GetCharge();
  return charge;
}
    
  } // namespace DS
} // namespace RAT

