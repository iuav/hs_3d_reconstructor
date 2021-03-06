﻿#ifndef _HS_3D_RECONSTRUCTOR_WORKFLOW_INCREMENTAL_PHOTO_ORIENTATION_HPP_
#define _HS_3D_RECONSTRUCTOR_WORKFLOW_INCREMENTAL_PHOTO_ORIENTATION_HPP_

#include "hs_sfm/sfm_utility/camera_type.hpp"
#include "hs_sfm/sfm_utility/match_type.hpp"
#include "hs_sfm/sfm_utility/key_type.hpp"

#include "hs_3d_reconstructor/config/hs_config.hpp"

#include "workflow/common/workflow_step.hpp"

namespace hs
{
namespace recon
{
namespace workflow
{

class HS_EXPORT PhotoOrientationConfig : public WorkflowStepConfig
{
public:
  typedef double Scalar;
  typedef hs::sfm::CameraIntrinsicParams<Scalar> IntrinsicParams;
  typedef EIGEN_STD_VECTOR(IntrinsicParams) IntrinsicParamsContainer;

  struct PosEntry
  {
    Scalar x;
    Scalar y;
    Scalar z;
  };
  typedef std::map<size_t, PosEntry> PosEntryContainer;

public:
  PhotoOrientationConfig();

  void set_image_intrinsic_map(
    const hs::sfm::ObjectIndexMap& image_intrinsic_map);
  void set_matches_path(const std::string& matches_path);
  void set_image_paths(const std::vector<std::string>& image_paths);
  void set_keysets_path(const std::string& keysets_path);
  void set_image_ids(const std::vector<int>& image_ids);
  void set_intrinsic_params_set(
    const IntrinsicParamsContainer& intrinsic_params_set);
  void set_intrinsic_ids(const std::vector<int>& intrinsic_ids);
  void set_intrinsic_path(const std::string& intrinsic_path);
  void set_extrinsic_path(const std::string& extrinsic_path);
  void set_point_cloud_path(const std::string& point_cloud_path);
  void set_tracks_path(const std::string& tracks_path);
  void set_track_point_map_path(const std::string& track_point_map_path);
  void set_similar_transform_path(const std::string& similar_transform_path);
  void set_workspace_path(const std::string& workspace_path);
  void set_number_of_threads(int number_of_threads);
  void set_pos_entries(const PosEntryContainer& pos_entries);

  const hs::sfm::ObjectIndexMap& image_intrinsic_map() const;
  const std::string& matches_path() const;
  const std::vector<std::string>& image_paths() const;
  const std::string& keysets_path() const;
  const std::vector<int>& image_ids() const;
  const IntrinsicParamsContainer& intrinsic_params_set() const;
  const std::vector<int>& intrinsic_ids() const;
  const std::string& intrinsic_path() const;
  const std::string& extrinsic_path() const;
  const std::string& point_cloud_path() const;
  const std::string& tracks_path() const;
  const std::string& track_point_map_path() const;
  const std::string& similar_transform_path() const;
  const std::string& workspace_path() const;
  int number_of_threads() const;
  const PosEntryContainer& pos_entries() const;

private:
  hs::sfm::ObjectIndexMap image_intrinsic_map_;
  std::string matches_path_;
  std::vector<std::string> image_paths_;
  std::string keysets_path_;
  std::vector<int> image_ids_;
  IntrinsicParamsContainer intrinsic_params_set_;
  std::vector<int> intrinsic_ids_;
  std::string intrinsic_path_;
  std::string extrinsic_path_;
  std::string point_cloud_path_;
  std::string tracks_path_;
  std::string track_point_map_path_;
  std::string similar_transform_path_;
  std::string workspace_path_;
  PosEntryContainer pos_entries_;
  int number_of_threads_;
};

typedef std::shared_ptr<PhotoOrientationConfig> PhotoOrientationConfigPtr;

class HS_EXPORT IncrementalPhotoOrientation : public WorkflowStep
{
public:
  enum ResultCode
  {
    RESULT_COMPLETE = 1,
    RESULT_GEOREFERENCE = 2
  };

  IncrementalPhotoOrientation();

private:
  typedef PhotoOrientationConfig::Scalar Scalar;
  typedef hs::sfm::ImageKeys<Scalar> Keyset;
  typedef EIGEN_STD_VECTOR(Keyset) KeysetContainer;
  typedef hs::sfm::CameraExtrinsicParams<Scalar> ExtrinsicParams;
  typedef EIGEN_STD_VECTOR(ExtrinsicParams) ExtrinsicParamsContainer;
  typedef hs::sfm::CameraIntrinsicParams<Scalar> IntrinsicParams;
  typedef EIGEN_STD_VECTOR(IntrinsicParams) IntrinsicParamsContainer;
  typedef EIGEN_VECTOR(Scalar, 3) Point;
  typedef EIGEN_STD_VECTOR(Point) PointContainer;

  int LoadKeysets(WorkflowStepConfig* config, KeysetContainer& keysets);
  int LoadMatches(WorkflowStepConfig* config,
                  hs::sfm::MatchContainer& matches);
  int RunSFM(WorkflowStepConfig* config,
             const KeysetContainer& keysets,
             const hs::sfm::MatchContainer& matches,
             IntrinsicParamsContainer& intrinsic_params_set,
             ExtrinsicParamsContainer& extrinsic_params_set,
             hs::sfm::ObjectIndexMap& image_extrinsic_map,
             PointContainer& points,
             hs::sfm::TrackContainer& tracks,
             hs::sfm::ObjectIndexMap& track_point_map,
             hs::sfm::ViewInfoIndexer& view_info_indexer);
  int SimilarTransformByPosEntries(
    WorkflowStepConfig* config,
    const ExtrinsicParamsContainer& extrinsic_params_set,
    const hs::sfm::ObjectIndexMap& image_extrinsic_map);
  int SaveIntrinsics(WorkflowStepConfig* config,
                     const IntrinsicParamsContainer& intrinsic_params_set);
  int SaveExtrinsics(WorkflowStepConfig* config,
                     const ExtrinsicParamsContainer& extrinsic_params_set,
                     const hs::sfm::ObjectIndexMap& image_extrinsic_map);
  int SavePointCloud(WorkflowStepConfig* config,
                     const KeysetContainer& keysets,
                     const hs::sfm::TrackContainer& tracks,
                     const hs::sfm::ObjectIndexMap& track_point_map,
                     const hs::sfm::ObjectIndexMap& image_extrinsic_map,
                     const ExtrinsicParamsContainer& extrinsic_params_set,
                     const IntrinsicParamsContainer& intrinsic_params_set,
                     const PointContainer& points);
  int SaveTracks(WorkflowStepConfig* config,
                 const hs::sfm::TrackContainer& tracks,
                 const hs::sfm::ObjectIndexMap& track_point_map,
                 const hs::sfm::ViewInfoIndexer& view_info_indexer);

protected:
  virtual int RunImplement(WorkflowStepConfig* config);
};

}
}
}

#endif
