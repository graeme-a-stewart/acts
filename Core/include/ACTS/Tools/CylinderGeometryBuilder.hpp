 ///////////////////////////////////////////////////////////////////
// CylinderGeometryBuilder.h, ACTS project
///////////////////////////////////////////////////////////////////

#ifndef ACTS_GEOMETRYTOOLS_TRACKINGGEOMETRYBUILDER_H
#define ACTS_GEOMETRYTOOLS_TRACKINGGEOMETRYBUILDER_H 1

// STL include(s)
#include <memory>
#include <list>

#include "ACTS/Utilities/Definitions.hpp"
#include "ACTS/Tools/ITrackingGeometryBuilder.hpp"
#include "ACTS/Tools/ITrackingVolumeBuilder.hpp"
#include "ACTS/Tools/ITrackingVolumeHelper.hpp"

namespace Acts
{
  class TrackingGeometry;

  /** @class GeometryBuilder

      The Acts::TrackingGeometry Builder for volumes that wrap around another

      It retrieves ITrackingVolumeBuilders as configured and builds one
      detector around the other one.

      @author Andreas.Salzburger@cern.ch   
  */

  class CylinderGeometryBuilder : public ITrackingGeometryBuilder
  {
    public:
      /** @struct Config
        Configuration for the CylinderVolumeBuilder */
      struct Config {  
    
        std::shared_ptr<ITrackingVolumeBuilder>              beamPipeBuilder;        //!< a special builder for the beam pipe (for post-insertion)
        std::list<std::shared_ptr<ITrackingVolumeBuilder> >  trackingVolumeBuilders; //!< the sub detector TrackingVolume builder
        std::shared_ptr<ITrackingVolumeHelper>               trackingVolumeHelper;   //!< used for creating a container
    
        Config() :
          beamPipeBuilder(nullptr),       
          trackingVolumeBuilders(),
          trackingVolumeHelper(nullptr)  
        {}
      };        
        
      /** Constructor */
      CylinderGeometryBuilder(const Config& cgbConfig);
          
      /** Destructor */
      virtual ~CylinderGeometryBuilder() = default;
    
      /** TrackingGeometry Interface method */
      virtual std::unique_ptr<TrackingGeometry> trackingGeometry() const override;
      
      /** Set configuration method */
      void setConfiguration(const Config& cgbConfig);
   
      /** Get configuration method */
      Config getConfiguration() const;   
      
    protected: 
      /** Configuration member */    
      Config  m_config;     

  };
  
  inline CylinderGeometryBuilder::Config CylinderGeometryBuilder::getConfiguration() const 
      { return m_config; }
  
} // end of namespace

#endif // ACTS_GEOMETRYTOOLS_TRACKINGGEOMETRYBUILDER_H
