﻿#ifndef _HS_3D_RECONSTRUCTOR_DATABASE_PHOTOGROUP_RESOURCE_HPP_
#define _HS_3D_RECONSTRUCTOR_DATABASE_PHOTOGROUP_RESOURCE_HPP_

#include "hs_3d_reconstructor/config/hs_config.hpp"
#include "database/resource_utility.hpp"

namespace hs
{
namespace recon
{
namespace db
{

class HS_EXPORT PhotogroupResource
{
public:
  enum FieldIdentifier
  {
    PHOTOGROUP_FIELD_ID = 0,
    PHOTOGROUP_FIELD_NAME,
    PHOTOGROUP_FIELD_DESCRIPTION,
    PHOTOGROUP_FIELD_WIDTH,
    PHOTOGROUP_FIELD_HEIGHT,
    PHOTOGROUP_FIELD_PIXEL_X_SIZE,
    PHOTOGROUP_FIELD_PIXEL_Y_SIZE,
    PHOTOGROUP_FIELD_FOCAL_LENGTH,
    PHOTOGROUP_FIELD_PRINCIPAL_X,
    PHOTOGROUP_FIELD_PRINCIPAL_Y,
    PHOTOGROUP_FIELD_SKEW,
    PHOTOGROUP_FIELD_RADIAL1,
    PHOTOGROUP_FIELD_RADIAL2,
    PHOTOGROUP_FIELD_RADIAL3,
    PHOTOGROUP_FIELD_DECENTERING1,
    PHOTOGROUP_FIELD_DECENTERING2,
    NUMBER_OF_PHOTOGROUP_FIELDS
  };
  static const int number_of_fields_ = NUMBER_OF_PHOTOGROUP_FIELDS;
  DECLARE_RESOURCE_COMMON_MEMBERS(PhotogroupResource)
};

}
}
}

#endif
