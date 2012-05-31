//----------------------------------------------------------------------------
// photonmap.cc
// An example implementation of the photon map data structure
//
// Henrik Wann Jensen - February 2001
//----------------------------------------------------------------------------

#ifndef PHOTONMAP_H_
#define PHOTONMAP_H_

#include "math/Vec3.h"
#include "SpectralQuantity.h"
#include <vector>

//FIXME mudar pra PhotonNode - Guardar Photon + flag?
struct Photon {
    Vec3 pos;                 // photon position
    short plane;                  // splitting plane for kd-tree
    Vec3 dir;
    Vec3 power;               // photon power (uncompressed)
};

/* This structure is used only to locate the
 * nearest photons */
struct NearestPhotons {
    int max;
    int found;
    int got_heap;
    Vec3 pos;
    float *dist2;
    const Photon **index;
};


class PhotonMap {
public:
    //PhotonMap();
    PhotonMap(std::vector<Photon> map);
    ~PhotonMap();

    //void store(Photon p);

    void scalePhotonPower(const float scale);

    // balance the kd-tree (before use!)
    void balance();

    // returned irradiance
    // surface position
    // surface normal at pos
    // max distance to look for photons
    // number of photons to use
    void irradianceEstimate(Vec3* irrad, const Vec3& pos, const Vec3& normal, const float max_dist, const int nphotons) const;

    // np is used to locate the photons
    // call with index = 1
    void locatePhotons(NearestPhotons *const np, const int index) const;

    //void photonDir(float *dir, const Photon *p) const;

//private:
    void balance_segment(Photon **pbal, Photon **porg, const int index, const int start, const int end);

    void median_split(Photon **p, const int start, const int end, const int median, const int axis);

    Photon *photons;
    //std::vector<Photon> photons;

    int stored_photons;
    int half_stored_photons;
    int max_photons;
    int prev_scale;

    float bbox_min[3];		// use bbox_min;
    float bbox_max[3];		// use bbox_max;
};


#endif
