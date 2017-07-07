#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/registration/ppf_registration.h>

typedef pcl::PointNormal Point_N;
typedef pcl::PointCloud<Point_N> Point_Cloud_N;

typedef pcl::PPFSignature PPF_Feature;
typedef pcl::PointCloud<PPF_Feature> PPF_Feature_Cloud;

int main(int argc, char** argv) {
  Point_Cloud_N::Ptr object (new Point_Cloud_N);
  Point_Cloud_N::Ptr scene (new Point_Cloud_N);

  pcl::io::loadPCDFile<Point_N>("object.pcd", *object);
  pcl::io::loadPCDFile<Point_N>("scene.pcd", *scene);

  pcl::console::print_highlight("Training model...\n");
  PPF_Feature_Cloud::Ptr object_ppf (new PPF_Feature_Cloud);
  pcl::PPFEstimation<Point_N, Point_N, PPF_Feature> ppf_estimator;
  ppf_estimator.setInputCloud(object);
  ppf_estimator.setInputNormals(object);
  ppf_estimator.compute(*object_ppf);

  pcl::PPFHashMapSearch::Ptr object_hashmap_search (new pcl::PPFHashMapSearch (1.0f/8.0f * float(M_PI), 0.1f)); // This discretization step works, however change the 8 to a 7 and it does not work.
  object_hashmap_search->setInputFeatureCloud(object_ppf);

  pcl::console::print_highlight("Registering model to scene...\n");
  pcl::PPFRegistration<Point_N, Point_N> ppf_registration;
  ppf_registration.setSceneReferencePointSamplingRate(10);
  ppf_registration.setPositionClusteringThreshold(0.1f);
  ppf_registration.setRotationClusteringThreshold(20.0f / 180.0f * float(M_PI));
  ppf_registration.setSearchMethod(object_hashmap_search);
  ppf_registration.setInputSource(object);
  ppf_registration.setInputTarget(scene);

  Point_Cloud_N::Ptr output (new Point_Cloud_N);
  ppf_registration.align(*output);

  return 1;
}
